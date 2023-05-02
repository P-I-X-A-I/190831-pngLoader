#pragma once
#include <fstream>
#include <iostream>

// to use htonl function
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib")

class PNG_LoaderClass
{

public:

	unsigned char* PNG_dataPtr = NULL;
	unsigned char* FiltPNG_dataPtr = NULL;
	int PNG_width = 0;
	int PNG_height = 0;

	unsigned char* compPtr = NULL;

	// for HUFFMAN
	unsigned char HC_LEN[19];
	unsigned char HC_HUFFMAN[19][7];

	int MIN_CUSTOM_LIT, MIN_CUSTOM_DIST;
	unsigned char CUSTOM_LIT_LEN[286];
	unsigned char CUSTOM_DIST_LEN[30];
	unsigned char CUSTOM_LIT_HUFFMAN[286][15];
	unsigned char CUSTOM_DIST_HUFFMAN[30][15];

	int SAME_TABLE[29];
	int SAME_EX_BIT[29];
	int DIST_TABLE[30];
	int DIST_EX_BIT[30];

	PNG_LoaderClass();
	~PNG_LoaderClass();

	//**********************************************

	unsigned char* construct_custom_huffman_table(unsigned char* bit_pointer);
	unsigned char* decode_custom_huffman_datapart(unsigned char* bit_pointer);
	unsigned char* repeat_window_value(unsigned char* pointer, int match);
	int check_hc_huffman_identity(unsigned char* pointer, int bitWidth);
	int check_lit_huffman_identity(unsigned char* pointer, int bitWidth);
	int check_dist_huffman_identity(unsigned char* pointer, int bitWidth);
	//*********************************************

	bool load_png_from_path(const char* filePath)
	{
		if (PNG_dataPtr != NULL)
		{
			free(PNG_dataPtr);
			PNG_dataPtr = NULL;
			PNG_width = 0;
			PNG_height = 0;
		}

		if (FiltPNG_dataPtr != NULL)
		{
			free(FiltPNG_dataPtr);
		}

		if (compPtr != NULL)
		{
			free(compPtr);
			compPtr = NULL;
		}

		// Open File
		std::ifstream sFile;
		FILE* fh;
		errno_t error;

		// open file
		error = fopen_s(&fh, filePath, "rb"); // read as binary

		if (error != 0)
		{
			std::cout << "PNG file path is invalid, can't open this file.... return" << std::endl;
			return false;
		}
		// get file length
		fseek(fh, 0, SEEK_END);

		fpos_t fLength = ftell(fh);

		if (fLength == 0)
		{
			std::cout << "this PNG file data length is 0.... return" << std::endl;
			fclose(fh);
			return false;
		}
		else
		{
			std::cout << "\n" << filePath << " : file length : " << fLength << std::endl;
		}


		// reset file's position to the beginning
		fseek(fh, 0, SEEK_SET);



		//*********************** PNG **********************************
		// check png header signature
		std::cout << "\n*** CHECK PNG SIGNATURE ***" << std::endl;
		unsigned char header[8];
		unsigned char signature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };

		fread_s(header, 8, 8, 1, fh);

		bool isPng = true;
		for (int i = 0; i < 8; i++)
		{
			if (header[i] != signature[i])
			{
				isPng = false;
				std::cout << "this file don't have PNG Signature... return" << std::endl;
				fclose(fh);
				return false;
			}
		}

		//************************************************
		// check IHDR chunk ( the first chunk )
		uint32_t IHDR_length;
		fread_s(&IHDR_length, 4, 4, 1, fh);
		IHDR_length = ntohl(IHDR_length);
		std::cout << " - chunk length : " << IHDR_length << std::endl;

		// type
		char IHDR_type[5] = { 0, 0, 0, 0, 0 };
		fread_s(IHDR_type, 4, 4, 1, fh);
		std::cout << " - chunk type : " << IHDR_type << std::endl;

		// width and height
		uint32_t IHDR_width, IHDR_height;
		fread_s(&IHDR_width, 4, 4, 1, fh);
		fread_s(&IHDR_height, 4, 4, 1, fh);

		PNG_width = ntohl(IHDR_width);
		PNG_height = ntohl(IHDR_height);
		std::cout << " -width, height : " << PNG_width << " : " << PNG_height << std::endl;


		// bitdepth and color type
		uint8_t IHDR_depth;
		uint8_t IHDR_colortype;
		fread_s(&IHDR_depth, 1, 1, 1, fh);
		fread_s(&IHDR_colortype, 1, 1, 1, fh);

		// colortype
		switch (IHDR_colortype)
		{
		case 0:
			std::cout << " -color_type : Grayscale" << std::endl;
			break;
		case 2:
			std::cout << " -color_type : RGB" << std::endl;
			break;
		case 3:
			std::cout << " -color_type : Index color" << std::endl;
			break;
		case 4:
			std::cout << " -color_type : Grayscale with Alpha" << std::endl;
			break;
		case 6:
			std::cout << " -color_type : RGBA" << std::endl;
			break;
		}


		// compression method ( always 0 )
		uint8_t IHDR_compression;
		fread_s(&IHDR_compression, 1, 1, 1, fh);


		// filter method ( always 0 )
		uint8_t IHDR_filter;
		fread_s(&IHDR_filter, 1, 1, 1, fh);

		// interlaced
		uint8_t IHDR_interlace;
		fread_s(&IHDR_interlace, 1, 1, 1, fh);
		std::cout << " -interlaced : " << IHDR_interlace << std::endl;

		// only png24 is supported.
		if (IHDR_colortype != 6 || IHDR_depth != 8 || IHDR_interlace != 0)
		{
			std::cout << "only RGBA 8bit, non-interlaced,  PNG-24 is supported... return" << std::endl;
			fclose(fh);
			return false;
		}


		// skip CRC checksum
		uint32_t IHDR_CRC;
		fread_s(&IHDR_CRC, 4, 4, 1, fh);

		// end of IHDR chunk ********************************


		// FIND ALL IDAT CHUNK
		std::cout << "\n*** FIND IDAT CHUNK ***" << std::endl;

		bool isLoop = true;
		int IDAT_COUNT = 0;
		unsigned char* IDAT_ptr = NULL;
		long IDAT_length = 0;

		while (isLoop)
		{
			// data length
			uint32_t data_length;
			fread_s(&data_length, 4, 4, 1, fh);
			data_length = ntohl(data_length);

			// chunk type
			char types[5] = { 0, 0, 0, 0, 0 };
			fread_s(types, 4, 4, 1, fh);
			std::cout << " -chunk type : " << types << std::endl;
			std::cout << " -length : " << data_length << std::endl;

			// data
			//******* check chunk type *********

			if (strcmp(types, "IDAT") == 0)
			{
				if (IDAT_COUNT == 0)
				{
					IDAT_ptr = (unsigned char*)malloc(data_length);
					fread_s(IDAT_ptr, data_length, data_length, 1, fh);

					IDAT_length = data_length;
				}
				else
				{
					std::cout << "Find 2nd IDAT chunk... error" << std::endl;
					free(IDAT_ptr);
					IDAT_ptr = NULL;
					isLoop = false;
					break;
				}
			}
			else if (strcmp(types, "IEND") == 0)
			{
				isLoop = false;
				break;
			}
			else
			{
				unsigned char* skip = (unsigned char*)malloc(data_length);
				fread_s(skip, data_length, data_length, 1, fh);
				free(skip);
			}



			// CRC checksum( skip )
			uint32_t CRC;
			fread_s(&CRC, 4, 4, 1, fh);

		}// while

		// close file
		fclose(fh);


		// alloc Filtered PNG_dataPtr**************************
		FiltPNG_dataPtr = (unsigned char*)malloc( (PNG_width+1) * PNG_height * 4);
		unsigned char* restoreFiltPng = FiltPNG_dataPtr;


		// go to next process ****************
		if (IDAT_ptr != NULL)
		{
			unsigned char* restore = IDAT_ptr;

			//****************************************
			this->find_compressed_data_part(IDAT_ptr, IDAT_length);
			//****************************************

			IDAT_ptr = restore;
			free(IDAT_ptr);
		}
		//*************************************


		// decode final filter ********************
		FiltPNG_dataPtr = restoreFiltPng;
		
		//PNG_dataPtr = (unsigned char*)malloc(PNG_width*PNG_height * 4);
		// decode filter


		FiltPNG_dataPtr = restoreFiltPng;
		free(FiltPNG_dataPtr);
		FiltPNG_dataPtr = NULL;
		//*****************************************


	}// load png from path



//********************************************************************
//********************************************************************
//********************************************************************


	bool find_compressed_data_part(unsigned char* idatPtr, long idatLength)
	{
		std::cout << "\n*** FIND COMPRESSED DATA PART ***" << std::endl;
		unsigned char* idat_ptr = idatPtr;


		// IDAT data contens ( first byte )
		// [7][6][5][4][3][2][1][0].....
		// [   CINFO  ][    CM    ]

		// get compression method and flag ( 1byte )

		uint8_t CMF;
		memcpy(&CMF, idat_ptr, 1);
		idat_ptr++;

		char CM = 0;
		CM = CMF & (8 + 4 + 2 + 1); // 00001111
		
		if ( CM == 8)
		{
			std::cout << " -CM [8] OK" << std::endl;
		}

		//:::::::::::::::
		CMF >>= 4;
		uint8_t CINFO = (CMF)& (8 + 4 + 2 + 1); //00001111
		uint32_t window_size = 1;

		window_size <<= (CINFO + 8);
		std::cout << " -deflate window size : " << window_size << std::endl;

		// ***************************************************

		// IDAT data contens ( second byte )

		// ...[7][6][5][4][3][2][1][0].....
		// ...[FLEV][D][  CHECK BIT  ]

		uint8_t FLG;
		memcpy(&FLG, idat_ptr, 1);
		idat_ptr++;

		// skip checksum 
		FLG >>= 5;

		// dictionary
		int FDICT = FLG & 1;
		if (FDICT != 0)
		{
			std::cout << "Preset Dictionary exist... not supported... return" << std::endl;
			return false;
		}

		// skip compression level
		FLG >>= 1;
		int FLEVEL = FLG & (2 + 1);



		// there is no PRESET DICT ID
		//****************************************


		// compressed data
		int compLength = idatLength - 6; //2byte header, 4byte checksum

		compPtr = (unsigned char*)malloc(compLength);
		memcpy(compPtr, idat_ptr, compLength);

		/*
unsigned char* compRestore = compPtr;
		
FILE* debugFile;
fopen_s(&debugFile, "compData.txt", "w");
for (int i = 0; i < 100; i++)
{
	fprintf_s(debugFile, "%d:", *compPtr);
	compPtr++;
}

compPtr = compRestore;

fclose(debugFile);
*/

		//****** unarchive huffman ****************
		unsigned char* compRestore = compPtr;

		this->decode_compressed_data_by_huffman(compPtr, compLength);
		
		compPtr = compRestore;
		free(compPtr);
		//*****************************************

		//alder-32 (4byte)
		// SKIP





		// if OK
		return true;
	}// find_compressed_data_part



//********************************************************************
//********************************************************************
//********************************************************************



	bool decode_compressed_data_by_huffman(unsigned char* compPtr, long compLength)
	{
		std::cout << "\n*** UN-ARCHIVE COMPRESSED DATA ***" << std::endl;

		// convert compData into 01 array
		unsigned char* bitPtr = (unsigned char*)malloc(compLength * 8);
		unsigned char* bitRestore = bitPtr;
		unsigned char* endPtr = bitPtr + (compLength * 8);

		for (int i = 0; i < compLength; i++)
		{
			uint8_t compVal = *compPtr;
			compPtr++;
			
			for (int k = 0; k < 8; k++)
			{
				*bitPtr = compVal & 1;
				bitPtr++;
				compVal >>= 1;
			}
		}

		bitPtr = bitRestore;



		// decode **************
		bool isLoop = true;

		while (isLoop)
		{
			unsigned char head[3];
			head[0] = *bitPtr; bitPtr++; // final flag
			head[1] = *bitPtr; bitPtr++; // comp method
			head[2] = *bitPtr; bitPtr++;

			// check final flag
			if (head[0] == 1)
			{
				// final block
				std::cout << "final block" << std::endl;
				isLoop = false;
			}


			if (head[2] == 0 && head[1] == 0)
			{
				// not compressed
			}
			else if (head[2] == 0 && head[1] == 1)
			{
				std::cout << "FIXED HUFFMAN BLOCK" << std::endl;
				isLoop = false;
				break;
			}
			else if (head[2] == 1 && head[1] == 0)
			{
				std::cout << "CUSTOM HUFFMAN BLOCK" << std::endl;
				bitPtr = this->construct_custom_huffman_table(bitPtr);
				bitPtr = this->decode_custom_huffman_datapart(bitPtr);
			}
			else
			{
				std::cout << "ENCOUNT ERROR..." << std::endl;
				isLoop = false;
				break;
			}


			// break for safety
			if (bitPtr >= endPtr)
			{
				isLoop = false;
				break;
			}
		}// while


		//
		bitPtr = bitRestore;
		free(bitPtr);


		// if OK
		return true;
	}





	// UTILITY *****************************************

	int revert_bit(unsigned num, unsigned bitWidth)
	{
		unsigned int retVal = 0;
		unsigned int inVal = num;

		for (int i = 0; i < bitWidth; i++)
		{
			unsigned int bit = inVal & 1;
			inVal >>= 1;

			retVal <<= 1;
			retVal = retVal | bit;
		}

		return retVal;
	}
};// class End

