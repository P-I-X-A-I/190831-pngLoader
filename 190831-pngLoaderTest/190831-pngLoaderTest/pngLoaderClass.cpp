#include "stdafx.h"
#include "pngLoaderClass.h"


pngLoaderClass::pngLoaderClass()
{
	std::cout << "*** pngLoaderClass init ***\n" << std::endl;

	// 257 - 285
	SAMELEN_TABLE[0] = 3;	SAMELEN_EXBIT_TABLE[0] = 0;
	SAMELEN_TABLE[1] = 4;	SAMELEN_EXBIT_TABLE[1] = 0;
	SAMELEN_TABLE[2] = 5;	SAMELEN_EXBIT_TABLE[2] = 0;
	SAMELEN_TABLE[3] = 6;	SAMELEN_EXBIT_TABLE[3] = 0;
	SAMELEN_TABLE[4] = 7;	SAMELEN_EXBIT_TABLE[4] = 0;
	SAMELEN_TABLE[5] = 8;	SAMELEN_EXBIT_TABLE[5] = 0;
	SAMELEN_TABLE[6] = 9;	SAMELEN_EXBIT_TABLE[6] = 0;
	SAMELEN_TABLE[7] = 10;	SAMELEN_EXBIT_TABLE[7] = 0;
	SAMELEN_TABLE[8] = 11;	SAMELEN_EXBIT_TABLE[8] = 1;
	SAMELEN_TABLE[9] = 13;	SAMELEN_EXBIT_TABLE[9] = 1;

	SAMELEN_TABLE[10] = 15;	SAMELEN_EXBIT_TABLE[10] = 1;
	SAMELEN_TABLE[11] = 17;	SAMELEN_EXBIT_TABLE[11] = 1;
	SAMELEN_TABLE[12] = 19;	SAMELEN_EXBIT_TABLE[12] = 2;
	SAMELEN_TABLE[13] = 23;	SAMELEN_EXBIT_TABLE[13] = 2;
	SAMELEN_TABLE[14] = 27;	SAMELEN_EXBIT_TABLE[14] = 2;
	SAMELEN_TABLE[15] = 31;	SAMELEN_EXBIT_TABLE[15] = 2;
	SAMELEN_TABLE[16] = 35;	SAMELEN_EXBIT_TABLE[16] = 3;
	SAMELEN_TABLE[17] = 43;	SAMELEN_EXBIT_TABLE[17] = 3;
	SAMELEN_TABLE[18] = 51;	SAMELEN_EXBIT_TABLE[18] = 3;
	SAMELEN_TABLE[19] = 59;	SAMELEN_EXBIT_TABLE[19] = 3;

	SAMELEN_TABLE[20] = 67;	SAMELEN_EXBIT_TABLE[20] = 4;
	SAMELEN_TABLE[21] = 83;	SAMELEN_EXBIT_TABLE[21] = 4;
	SAMELEN_TABLE[22] = 99;	SAMELEN_EXBIT_TABLE[22] = 4;
	SAMELEN_TABLE[23] = 115;	SAMELEN_EXBIT_TABLE[23] = 4;
	SAMELEN_TABLE[24] = 131;	SAMELEN_EXBIT_TABLE[24] = 5;
	SAMELEN_TABLE[25] = 163;	SAMELEN_EXBIT_TABLE[25] = 5;
	SAMELEN_TABLE[26] = 195;	SAMELEN_EXBIT_TABLE[26] = 5;
	SAMELEN_TABLE[27] = 227;	SAMELEN_EXBIT_TABLE[27] = 5;
	SAMELEN_TABLE[28] = 258;	SAMELEN_EXBIT_TABLE[28] = 0;


	DIST_TABLE[0] = 1;		DIST_EXBIT_TABLE[0] = 0;
	DIST_TABLE[1] = 2;		DIST_EXBIT_TABLE[1] = 0;
	DIST_TABLE[2] = 3;		DIST_EXBIT_TABLE[2] = 0;
	DIST_TABLE[3] = 4;		DIST_EXBIT_TABLE[3] = 0;
	DIST_TABLE[4] = 5;		DIST_EXBIT_TABLE[4] = 1;
	DIST_TABLE[5] = 7;		DIST_EXBIT_TABLE[5] = 1;
	DIST_TABLE[6] = 9;		DIST_EXBIT_TABLE[6] = 2;
	DIST_TABLE[7] = 13;		DIST_EXBIT_TABLE[7] = 2;
	DIST_TABLE[8] = 17;		DIST_EXBIT_TABLE[8] = 3;
	DIST_TABLE[9] = 25;		DIST_EXBIT_TABLE[9] = 3;

	DIST_TABLE[10] = 33;		DIST_EXBIT_TABLE[10] = 4;
	DIST_TABLE[11] = 49;		DIST_EXBIT_TABLE[11] = 4;
	DIST_TABLE[12] = 65;		DIST_EXBIT_TABLE[12] = 5;
	DIST_TABLE[13] = 97;		DIST_EXBIT_TABLE[13] = 5;
	DIST_TABLE[14] = 129;		DIST_EXBIT_TABLE[14] = 6;
	DIST_TABLE[15] = 193;		DIST_EXBIT_TABLE[15] = 6;
	DIST_TABLE[16] = 257;		DIST_EXBIT_TABLE[16] = 7;
	DIST_TABLE[17] = 385;		DIST_EXBIT_TABLE[17] = 7;
	DIST_TABLE[18] = 513;		DIST_EXBIT_TABLE[18] = 8;
	DIST_TABLE[19] = 769;		DIST_EXBIT_TABLE[19] = 8;

	DIST_TABLE[20] = 1025;		DIST_EXBIT_TABLE[20] = 9;
	DIST_TABLE[21] = 1537;		DIST_EXBIT_TABLE[21] = 9;
	DIST_TABLE[22] = 2049;		DIST_EXBIT_TABLE[22] = 10;
	DIST_TABLE[23] = 3073;		DIST_EXBIT_TABLE[23] = 10;
	DIST_TABLE[24] = 4097;		DIST_EXBIT_TABLE[24] = 11;
	DIST_TABLE[25] = 6145;		DIST_EXBIT_TABLE[25] = 11;
	DIST_TABLE[26] = 8193;		DIST_EXBIT_TABLE[26] = 12;
	DIST_TABLE[27] = 12289;		DIST_EXBIT_TABLE[27] = 12;
	DIST_TABLE[28] = 16385;		DIST_EXBIT_TABLE[28] = 13;
	DIST_TABLE[29] = 24577;		DIST_EXBIT_TABLE[29] = 13;



	// FIXED HUFFMAN TABLE
	// 0 - 143 : 8bit, 00110000 - 10111111
	unsigned int base = 48; // 00110000
	for (int i = 0; i <= 143; i++)
	{
		FIX_LIT_LEN[i] = 8; // 8bit bitwidth

		unsigned int cp = base;

		for (int k = 7; k >= 0; k--)
		{
			FIX_LIT_HUFFMAN[i][k] = cp & 1;
			cp >>= 1;
		}

		base++;
	}

	// 144 - 255 9bit
	base = 256 + 128 + 16; // 110010000
	for (int i = 144; i <= 255; i++)
	{
		FIX_LIT_LEN[i] = 9;

		unsigned int cp = base;

		for (int k = 8; k >= 0; k--)
		{
			FIX_LIT_HUFFMAN[i][k] = cp & 1;
			cp >>= 1;
		}

		base++;
	}


	// 256 - 279 7bit
	base = 0; //0000000
	for (int i = 256; i <= 279; i++)
	{
		FIX_LIT_LEN[i] = 7;

		unsigned int cp = base;

		for (int k = 6; k >= 0; k--)
		{
			FIX_LIT_HUFFMAN[i][k] = cp & 1;
			cp >>= 1;
		}

		base++;
	}


	// 280 - 287 8bit
	base = 128 + 64; // 11000000
	for (int i = 280; i <= 287; i++)
	{
		FIX_LIT_LEN[i] = 8;

		unsigned int cp = base;

		for (int k = 7; k >= 0; k--)
		{
			FIX_LIT_HUFFMAN[i][k] = cp & 1;
			cp >>= 1;
		}
		base++;
	}


	// fixd dist huffman
	base = 0;
	for (int i = 0; i <= 31; i++)
	{
		unsigned int cp = base;

		for (int k = 4; k >= 0; k--)
		{
			FIX_DIST_HUFFMAN[i][k] = cp & 1;
			cp >>= 1;
		}

		base++;
	}

}


pngLoaderClass::~pngLoaderClass()
{
}


bool pngLoaderClass::load_png24_from_path(const char* filePath)
{
	// init variables *****************************************
	if (PNG_dataPtr != NULL)
	{
		free(PNG_dataPtr);
		PNG_width = 0;
		PNG_height = 0;
	}

	// init variables end **********************************************************


	// load file ***********************
	std::ifstream sFile;
	FILE* fh;
	errno_t error;

	// open file
	error = fopen_s(&fh, filePath, "rb");

	if (error != 0)
	{
		std::cout << "can't load PNG file... return " << std::endl;
		return false;
	}


	// check file length
	fseek(fh, 0, SEEK_END);
	fpos_t fLength = ftell(fh);
	std::cout << "File length : " << fLength << std::endl;

	// reset file position
	fseek(fh, 0, SEEK_SET);


	// check png signature
	std::cout << "\n*** CHECK PNG SIGNATURE ***" << std::endl;
	unsigned char signature[8] = {137, 80, 78, 71, 13, 10, 26, 10 };

	for (int i = 0; i < 8; i++)
	{
		unsigned char head;
		fread_s(&head, 1, 1, 1, fh);
		
		if (head != signature[i])
		{
			std::cout << "this file don't have PNG signature... return" << std::endl;
			int ret = fclose(fh);
			return false;
		}
	}



	// check IHDR chunk ( the first chunk )
	std::cout << "\n*** CHECK IHDR CHUNK ***" << std::endl;

	// chunk length
	uint32_t IHDR_length;
	fread_s(&IHDR_length, 4, 4, 1, fh);
	IHDR_length = ntohl(IHDR_length);
	std::cout << " -chunk length : " << IHDR_length << std::endl;

	// chunk type (4byte )
	unsigned char IHDR_type[5] = { 0, 0, 0, 0, 0 };
	fread_s(IHDR_type, 4, 4, 1, fh);
	std::cout << " -chunk type : " << IHDR_type << std::endl;

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
	

	// only png24 is supported.
	if (IHDR_colortype != 6 || IHDR_depth != 8 || IHDR_interlace != 0 )
	{
		std::cout << "only RGBA 8bit, non-interlaced,  PNG-24 is supported... return" << std::endl;
		fclose(fh);
		return false;
	}


	// skip CRC checksum
	uint32_t IHDR_CRC;
	fread_s(&IHDR_CRC, 4, 4, 1, fh);





	// **************** alloc PNG data pointer ****************
	long pngsize = (PNG_width+1) * PNG_height * 4 * sizeof(unsigned char);
	PNG_dataPtr = (unsigned char*)malloc(pngsize);

	unsigned char* restore_PNG_dataPtr = PNG_dataPtr;





	//***** find IDAT chunk ****************************
	std::cout << "\n FIND IDAT CHUNK ***" << std::endl;



	bool loop = true;

	unsigned char* IDAT_ptr = NULL;
	unsigned char* IDAT_stream = (unsigned char*)malloc(1024*1024*100); // 100MB
	unsigned char* restoreStream = IDAT_stream;

	long total_idat_length = 0;
	int idat_count = 0;


	while (loop) // loop untile find IEND chunk
	{
		uint32_t chunk_data_length;

		// chunk length
		fread_s(&chunk_data_length, 4, 4, 1, fh);
		chunk_data_length = ntohl(chunk_data_length);

		// chunk type
		char chunk_type[5] = { 0 };
		fread_s(chunk_type, 4, 4, 1, fh);
		std::cout << " -chunk type : " << chunk_type << std::endl;


		if (strcmp(chunk_type, "IDAT") == 0)
		{
				std::cout << " -chunk length : " << chunk_data_length << std::endl;

				// alloc memory

				for (int k = 0; k < chunk_data_length; k++)
				{
					fread_s(IDAT_stream, 1, 1, 1, fh);
					IDAT_stream++;
				}

				total_idat_length += chunk_data_length;
				idat_count++;
		}
		else if (strcmp(chunk_type, "IEND") == 0)
		{
			loop = false;
		}
		else
		{
			unsigned char* skipData = (unsigned char*)malloc(chunk_data_length);
			fread_s(skipData, chunk_data_length, chunk_data_length, 1, fh);
			free(skipData);
			// skip data
		}


		// skip CRC
		uint32_t skipCRC;
		fread_s(&skipCRC, 4, 4, 1, fh);

	}// while

	// close file handle
	fclose(fh);

	// concat IDAT chunk
	IDAT_stream = restoreStream;
	IDAT_ptr = (unsigned char*)malloc(total_idat_length);

	memcpy(IDAT_ptr, IDAT_stream, total_idat_length);
	free(IDAT_stream);





	// restore pointer for IDAT
	unsigned char* IDAT_restore = IDAT_ptr;


	// Now I got IDAT data *********************************
	bool isSuccess = this->decode_IDAT_data(IDAT_ptr, total_idat_length);
	//********************************************************

	// free IDAT
	IDAT_ptr = IDAT_restore;
	free(IDAT_ptr);







	// restore png pointer
	PNG_dataPtr = restore_PNG_dataPtr;

	// decode png filter *****************************************
	if (isSuccess)
	{
		// decode png filter
	}
	else
	{
		std::cout << "decode IDAT data fail.... return" << std::endl;
		return false;
	}
	//************************************************************


	return true;
}








bool pngLoaderClass::decode_IDAT_data(unsigned char* idat_pointer, long dataLength)
{
	std::cout << "\n*** DECODE IDAT DATA ***" << std::endl;

	unsigned char* idatPtr = idat_pointer;

	// IDAT data contens ( first byte )

	// [7][6][5][4][3][2][1][0].....
	// [   CINFO  ][    CM    ]

	// get compression method and flag ( 1byte )
	uint8_t CMF;
	memcpy(&CMF, idatPtr, 1);
	idatPtr += 1;


	uint8_t CM = CMF & (8 + 4 + 2 + 1); //00001111
	if (CM == 8)
	{
		std::cout << " -CM : 8" << std::endl;
	}

	CMF >>= 4;
	uint8_t CINFO = CMF & (8 + 4 + 2 + 1);
	uint32_t window_size = 1;
	window_size <<= (CINFO + 8);
	std::cout << " -deflate window size : " << window_size << std::endl;



	// ***************************************************

	// IDAT data contens ( second byte )

	// ...[7][6][5][4][3][2][1][0].....
	// ...[FLEV][D][  CHECK BIT  ]

		// get FLG
	uint8_t FLG;
	memcpy(&FLG, idatPtr, 1);
	idatPtr += 1;

	// skip checksum
	FLG >>= 5;

	// check DICTIONARY
	int FDICT = FLG & (1); // 00000001

	std::cout << " -FDICT : " << FDICT << std::endl;

	if (FDICT != 0)
	{
		std::cout << "ERROR. preset Dictionary is not supported.... return" << std::endl;
		return false;
	}


	FLG >>= 1;

	//SKIP FLEV ( compression level )
	//
	//
	//



	long compressed_data_length = dataLength - 6; // excluding 2byte header, 4byte last checksum
	unsigned char* compData = (unsigned char*)malloc(compressed_data_length);
	unsigned char* comp_restore = compData;

	// read into 
	memcpy(compData, idatPtr, compressed_data_length);


	// unarchive compressed data ************************
	bool isSuccess = this->unarchive_compressed_data(compData, compressed_data_length);
	//****************************************************


	compData = comp_restore;
	free(compData);


	if (isSuccess == false)
	{
		std::cout << "unarchiving compressed data fail.... return" << std::endl;
		return false;
	}


	// if OK
	return true;
}





bool pngLoaderClass::unarchive_compressed_data(unsigned char* comp_pointer, long dataLength)
{
	std::cout << "\n*** UN-ARCHIVE COMPRESSED DATA ***" << std::endl;


	// read from
	unsigned char* compPtr = comp_pointer;


	// convert binary to unsigned char[000] array
	unsigned char* bitPtr = (unsigned char*)malloc(dataLength * 8);
	unsigned char* bit_restore = bitPtr;
	unsigned char* endPtr = bitPtr + (dataLength * 8);

	
	for (int i = 0; i < dataLength; i++)
	{
		uint8_t temp;
		memcpy(&temp, compPtr, 1);
		compPtr++;

		for (int k = 0; k < 8; k++)
		{
			*bitPtr = temp & 1;
			bitPtr++;
			temp >>= 1;
		}
	}

	bitPtr = bit_restore;



	// decode huffman
	bool isLoop = true;

	while (isLoop)
	{
		// read 3bit
		unsigned char head[3];
		head[0] = *bitPtr;	bitPtr++;
		head[1] = *bitPtr;	bitPtr++;
		head[2] = *bitPtr;	bitPtr++;


		// check final block
		if (head[0] == 1)
		{
			isLoop = false;
		}


		// check huffman method
		if (head[2] == 0 && head[1] == 0) // not compressed
		{
			std::cout << "encount non-compressed block... not supported.. return" << std::endl;
			isLoop = false;
			break;
		}
		else if (head[2] == 0 && head[1] == 1) // fixed huffman block
		{
			std::cout << "FIXED HUFFMAN BLOCK" << std::endl;
			bitPtr = this->decode_fixed_huffman(bitPtr);
		}
		else if (head[2] == 1 && head[1] == 0)// custom huffman block
		{
			std::cout << "CUSTOM HUFFMAN BLOCK" << std::endl;
			bitPtr = this->decode_custom_huffman(bitPtr);
		}
		else
		{
			std::cout << "encount error... return" << std::endl;
			isLoop = false;
			break;
		}


		// break while loop
		if (bitPtr >= endPtr)
		{
			isLoop = false;
			break;
		}
	}


	// free 
	bitPtr = bit_restore;
	free(bitPtr);



	// if OK
	return true;
}


//**************************** DECODE FIXED HUFFMAN BLOCK ***************

unsigned char* pngLoaderClass::decode_fixed_huffman(unsigned char* bit_pointer)
{
	unsigned char* bitPtr = bit_pointer;

	bool isLoop = true;

	while (isLoop) // read until find 256
	{
		// read first 7bit ( max 9bit )
		unsigned char compareBit[9] = {255, 255, 255, 255, 255, 255, 255, 255, 255};

		for (int i = 0; i < 7; i++)
		{
			compareBit[i] = *bitPtr;
			bitPtr++;
		}


		// compare loop from 7bit to 9 bit
		for (int i = 7; i <= 9; i++)
		{
			int matchCount = this->check_fixed_lit_huffman_identity(compareBit, i);
			
			if (matchCount <= 255)
			{
				//*PNG_dataPtr = (unsigned char)matchCount;
				//PNG_dataPtr++;
				break;
			}
			else if (matchCount == 256)
			{
				isLoop = false;
				break;
			}
			else if (matchCount >= 257 && matchCount < 286)
			{
				// repeated value
				// num of extra bit
				int ex_bit_len = SAMELEN_EXBIT_TABLE[matchCount - 257];
				int ex_length = 0;
				for (int E = 0; E < ex_bit_len; E++)
				{
					ex_length <<= 1;
					ex_length |= (*bitPtr);
					bitPtr++;
				}

				ex_length = this->reverse_bit(ex_length, ex_bit_len);

				//******************************************************
				int SAME_LENGTH = SAMELEN_TABLE[matchCount - 257] + ex_length;
				//******************************************************


				// read extra 5 bit ( distance )
				unsigned char inCompare[5];

				inCompare[0] = *bitPtr;	bitPtr++;
				inCompare[1] = *bitPtr;	bitPtr++;
				inCompare[2] = *bitPtr;	bitPtr++;
				inCompare[3] = *bitPtr;	bitPtr++;
				inCompare[4] = *bitPtr;	bitPtr++;

				int match = this->check_fixed_dist_huffman_identity(inCompare, 5);

				if (matchCount == 9999)
				{
					std::cout << "fixed dist huffman doesnt match... error" << std::endl;
					return bitPtr;
				}

				// get distance
				int baseDist = DIST_TABLE[match];
				int ex_dist_bit = DIST_EXBIT_TABLE[match];

				int ex_dist = 0;
				for (int E = 0; E < ex_dist_bit; E++)
				{
					ex_dist <<= 1;
					ex_dist = ex_dist | (*bitPtr);
					bitPtr++;
				}

				ex_dist = this->reverse_bit(ex_dist, ex_dist_bit);

				int ACTUAL_DIST = baseDist + ex_dist;


				// set deflate window value to PNG pointer
				unsigned char* prev_PNG_pointer = PNG_dataPtr - ACTUAL_DIST;
				for (int rep = 0; rep < SAME_LENGTH; rep++)
				{
					//*PNG_dataPtr = *prev_PNG_pointer;
					//PNG_dataPtr++;
					prev_PNG_pointer++;
				}

				break;
			}
			else // doesnt match
			{
				if (i == 9)
				{
					std::cout << "fixed huffman doesnt match until 9bit width. error...." << std::endl;
				}
				compareBit[i] = *bitPtr;
				bitPtr++;
			}
			
		}

	}// while


	return bitPtr;
}




int pngLoaderClass::check_fixed_lit_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[9]; // max bitwidth = 9
	unsigned char* readPtr = pointer;

	// read compare bit
	for (int i = 0; i < bitWidth; i++)
	{
		bits[i] = *readPtr;		readPtr++;
	}


	// compare
	bool isMatch;
	int matchCount = 9999;

	for (int i = 0; i < 286; i++)
	{
		isMatch = true;

		if (bitWidth == FIX_LIT_LEN[i])
		{
			for (int k = 0; k < bitWidth; k++)
			{
				if (bits[k] != FIX_LIT_HUFFMAN[i][k])
				{
					isMatch = false;
					break;
				}
			}
		}
		else
		{
			isMatch = false;
		}


		if (isMatch == true)
		{
			matchCount = i;
			break;
		}
	}// for 286

	return matchCount;
}


int pngLoaderClass::check_fixed_dist_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[5]; // max 5bits
	unsigned char* readP = pointer;

	for (int i = 0; i < 5; i++)
	{
		bits[i] = *readP;	readP++;
	}


	// compare
	bool isMatch;
	int matchCount = 9999;

	for (int i = 0; i < 32; i++)
	{
		isMatch = true;

		for (int k = 0; k < bitWidth; k++) // bitwidth is always 5
		{
			if (bits[k] != FIX_DIST_HUFFMAN[i][k])
			{
				isMatch = false;
				break;
			}
		}

		if (isMatch == true)
		{
			matchCount = i;
			break;
		}
	}


	return matchCount;
}





//**************************** DECODE CUSTOM HUFFMAN BLOCK ******************

unsigned char* pngLoaderClass::decode_custom_huffman(unsigned char* bit_pointer)
{
	unsigned char* bitPtr = bit_pointer;

	// get custom huffman table's bit length
	bitPtr = this->setup_custom_huffman_table_length(bitPtr);
	std::cout << "get custom huffman table's bit-width table"<< std::endl;


	// get custom huffman table
	bool isSuccess = this->setup_custom_huffman_table_itself();
	std::cout << "get custom huffman table" << std::endl;




	// decode data by huffman table

	bitPtr = this->inflate_custom_huffman(bitPtr);



	return bitPtr;
}





unsigned char* pngLoaderClass::setup_custom_huffman_table_length(unsigned char* pointer)
{
	unsigned char* bitPtr = pointer;

	// count num of table

	// read HLIT ( 5bit )
	unsigned char HLIT = 0;

	HLIT = HLIT | (*bitPtr);	bitPtr++;	HLIT <<= 1;
	HLIT = HLIT | (*bitPtr);	bitPtr++;	HLIT <<= 1;
	HLIT = HLIT | (*bitPtr);	bitPtr++;	HLIT <<= 1;
	HLIT = HLIT | (*bitPtr);	bitPtr++;	HLIT <<= 1;
	HLIT = HLIT | (*bitPtr);	bitPtr++;

	HLIT = this->reverse_bit(HLIT, 5);
	printf("HLIT %d\n", HLIT+257);

	// read HDIST ( 5bits )
	unsigned char HDIST = 0;

	HDIST = HDIST | (*bitPtr); bitPtr++; HDIST <<= 1;
	HDIST = HDIST | (*bitPtr); bitPtr++; HDIST <<= 1;
	HDIST = HDIST | (*bitPtr); bitPtr++; HDIST <<= 1;
	HDIST = HDIST | (*bitPtr); bitPtr++; HDIST <<= 1;
	HDIST = HDIST | (*bitPtr); bitPtr++;

	HDIST = this->reverse_bit(HDIST, 5);
	printf("HDIST %d\n", HDIST+1);

	// read HCLEN (4bit)
	unsigned char HCLEN = 0;

	HCLEN = HCLEN | (*bitPtr);	bitPtr++;	HCLEN <<= 1;
	HCLEN = HCLEN | (*bitPtr);	bitPtr++;	HCLEN <<= 1;
	HCLEN = HCLEN | (*bitPtr);	bitPtr++;	HCLEN <<= 1;
	HCLEN = HCLEN | (*bitPtr);	bitPtr++;

	HCLEN = this->reverse_bit(HCLEN, 4);
	printf("HCLEN %d\n", HCLEN+4);




	//********************* READ HUFFMAN bit length of HUFFMAN table bit length
	int IDX[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

	for (int i = 0; i < 19; i++)
	{
		HC_LEN[i] = 0;
	}

	// get length of HUFFMAN tables bit length
	// read (HCLEN+4) * 3bits

	for (int i = 0; i < (HCLEN + 4); i++)
	{
		int temp = 0;
		temp = temp | (*bitPtr);	bitPtr++;	temp <<= 1;
		temp = temp | (*bitPtr);	bitPtr++;	temp <<= 1;
		temp = temp | (*bitPtr);	bitPtr++;

		temp = this->reverse_bit(temp, 3);
		HC_LEN[IDX[i]] = temp;
		printf("%d", temp);
	}


	// find minimum HC_LEN
	int MIN_HC_LEN = 255;
	for (int i = 0; i < 19; i++)
	{
		if (HC_LEN[i] < MIN_HC_LEN && HC_LEN[i] != 0)
		{
			MIN_HC_LEN = HC_LEN[i];
		}
	}

	//****** 0 - 15, 16, 17, 18, Langlenth compression ***********

	// init huffman
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			HC_HUFFMAN[i][j] = 255;
		}
	}

	// set huffman
	unsigned char base = 0;
	for (int L = MIN_HC_LEN; L <= 7; L++)
	{
		base <<= 1; // 110 -> 1100...

		for (int i = 0; i < (HCLEN+4); i++)
		{
			if (HC_LEN[i] == L)
			{
				int cp = base;
				for (int k = L - 1; k >= 0; k--)
				{
					HC_HUFFMAN[i][k] = cp & 1;
					cp >>= 1;
				}

				base++;
			}
		}
	}




	// next, get lit & dist huffman table's bit length
	// init length
	for (int i = 0; i < 288; i++)
	{
		CUSTOM_LIT_LEN[i] = 0;

		if (i < 32)
		{
			CUSTOM_DIST_LEN[i] = 0;
		}
	}


	bool isLoop = true;
	int COUNTER = 0;
	unsigned char compareBit[7];

	while (isLoop) // loop while 286 length have got
	{
		// init compare bit
		for (int i = 0; i < 7; i++)
		{
			compareBit[i] = 255;
		}

		// read first min bit
		for (int i = 0; i < MIN_HC_LEN; i++)
		{
			compareBit[i] = (*bitPtr);	bitPtr++;
		}

		// compare
		for (int i = MIN_HC_LEN; i <= 7; i++)
		{
			int matchCount = this->check_hc_huffman_identity(compareBit, i);

			if (matchCount <= 15)
			{
				CUSTOM_LIT_LEN[COUNTER] = matchCount;
				COUNTER++;
				break;
			}
			else if (matchCount == 16) // repeat prev value
			{
				// read extra 2bit
				int ex_repeat = 0;
				ex_repeat = ex_repeat | (*bitPtr);	bitPtr++;
				ex_repeat <<= 1;
				ex_repeat = ex_repeat | (*bitPtr);	bitPtr++;

				ex_repeat = this->reverse_bit(ex_repeat, 2);
				//*****************************
				ex_repeat += 3;	// add base ( 3 )

				// prev value
				int prevVal = CUSTOM_LIT_LEN[COUNTER - 1];

				// set value
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_LIT_LEN[COUNTER] = prevVal;
					COUNTER++;
				}

				break;
			}
			else if (matchCount == 17 || matchCount == 18 ) // repeat zero 3-10, 11 - 138
			{
				int bwidth;
				int ex_repeat = 0;
				int rep_base;

				if (matchCount == 17)
				{
					bwidth = 3;// read extra 3bit
					rep_base = 3;
				}
				else if (matchCount == 18)
				{
					bwidth = 7;//read extra 7bit
					rep_base = 11;
				}


				for (int E = 0; E < bwidth; E++)
				{
					ex_repeat <<= 1;
					ex_repeat = ex_repeat | (*bitPtr);
					bitPtr++;
				}
				ex_repeat = this->reverse_bit(ex_repeat, bwidth);
				
				// get actual repeat count ******************
				ex_repeat += rep_base;

				// set zero
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_LIT_LEN[COUNTER] = 0;
					COUNTER++;
				}

				break;
			}
			else
			{
				// doesnt match
				if (i == 7)
				{
					std::cout << "doesnt match until 7 bit width... error." << std::endl;
				}
				compareBit[i] = *bitPtr;
				bitPtr++;
			}
		} // for i < 7

		if (COUNTER >= (HLIT+257))
		{
			isLoop = false;
			break;
		}

	}// while


	// I've got LIT HUFFMAN bit length ***********

	// get DIST HUFFMAN bit length 

	COUNTER = 0;
	isLoop = true;


	while (isLoop)
	{
		for (int i = 0; i < 7; i++)
		{
			compareBit[i] = 255;
		}
	
		// read first min bit
		for (int i = 0; i < MIN_HC_LEN; i++)
		{
			compareBit[i] = (*bitPtr);	bitPtr++;
		}


		for (int i = MIN_HC_LEN; i <= 7; i++)
		{
			int matchCount = this->check_hc_huffman_identity(compareBit, i);

			if (matchCount <= 15)
			{
				CUSTOM_DIST_LEN[COUNTER] = matchCount;
				COUNTER++;
				break;
			}
			else if (matchCount == 16)
			{
				// read extra 2bit
				int ex_repeat = 0;
				ex_repeat = ex_repeat | (*bitPtr);	bitPtr++;
				ex_repeat <<= 1;
				ex_repeat = ex_repeat | (*bitPtr);	bitPtr++;

				ex_repeat = this->reverse_bit(ex_repeat, 2);

				// actual repeat
				ex_repeat += 3;

				// prev value
				int prevValue = CUSTOM_DIST_LEN[COUNTER - 1];

				// repeat
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_DIST_LEN[COUNTER] = prevValue;
					COUNTER++;
				}
				break;
			}
			else if (matchCount == 17 || matchCount == 18)
			{
				int bwidth;
				int rep_base;
				if (matchCount == 17)
				{
					bwidth = 3;
					rep_base = 3;
				}
				else if (matchCount == 18)
				{
					bwidth = 7;
					rep_base = 11;
				}


				int ex_repeat = 0;
				for (int E = 0; E < bwidth; E++)
				{
					ex_repeat <<= 1;
					ex_repeat = ex_repeat | (*bitPtr);
					bitPtr++;
				}

				// actual repeat
				ex_repeat = this->reverse_bit(ex_repeat, bwidth);
				ex_repeat += rep_base;


				// set zero
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_DIST_LEN[COUNTER] = 0;
					COUNTER++;
				}


				break;
			}
			else
			{
				if (i == 7)
				{
					std::cout << "doesnt match until 7bit(dist len)... error" << std::endl;
				}

				compareBit[i] = (*bitPtr);
				bitPtr++;
			}

		}// for i < 7

		if (COUNTER >= (HDIST + 1))
		{
			isLoop = false;
			break;
		}

	}// while



		// debug
	/*
	FILE* debugFile;
	fopen_s(&debugFile, "lit_dist_len.txt", "w");

	for (int i = 0; i < 286; i++)
	{
		fprintf_s(debugFile, "CUSTOM_LIT_LEN[%d] : %d\n", i, CUSTOM_LIT_LEN[i]);
	}

	fprintf_s(debugFile, "\n DIST LEN \n");
	for (int i = 0; i < 32; i++)
	{
		fprintf_s(debugFile, "CUSTOM_DIST_LEN[%d] : %d\n", i, CUSTOM_DIST_LEN[i]);
	}

	fclose(debugFile);
	*/


	// if OK
	return bitPtr;
}



////////////////////////////////////////////////////////////////
bool pngLoaderClass::setup_custom_huffman_table_itself()
{
	// find minimum length
	MIN_LIT_BIT = 255;
	MIN_DIST_BIT = 255;

	for (int i = 0 ; i < 286 ; i++)
	{
		if (CUSTOM_LIT_LEN[i] < MIN_LIT_BIT && CUSTOM_LIT_LEN[i] != 0)
		{
			MIN_LIT_BIT = CUSTOM_LIT_LEN[i];
		}
	}


	for (int i = 0; i < 32; i++)
	{
		if (CUSTOM_DIST_LEN[i] < MIN_DIST_BIT && CUSTOM_DIST_LEN[i] != 0)
		{
			MIN_DIST_BIT = CUSTOM_DIST_LEN[i];
		}
	}

	//printf("MIN_LIT_BIT %d, MIN_DIST_BIT %d\n", MIN_LIT_BIT, MIN_DIST_BIT);


	// get HUFFMAN table of LIT & DIST
	unsigned int base = 0;

	for (int len = MIN_LIT_BIT; len <= 15; len++)
	{
		base <<= 1;	// 110 -> 1100

		for (int i = 0; i < 286; i++)
		{
			if (CUSTOM_LIT_LEN[i] == len)
			{
				int cp = base;
				for (int k = len - 1; k >= 0; k--)
				{
					CUSTOM_LIT_HUFFMAN[i][k] = cp & 1;
					cp >>= 1;
				}

				base++;
			}
		}
	}

	/////////////
	
	base = 0;

	for (int len = MIN_DIST_BIT; len <= 15; len++)
	{
		base <<= 1;

		for (int i = 0; i < 32; i++)
		{
			if (CUSTOM_DIST_LEN[i] == len)
			{
				int cp = base;

				for (int k = len - 1; k >= 0; k--)
				{
					CUSTOM_DIST_HUFFMAN[i][k] = cp & 1;
					cp >>= 1;
				}

				base++;
			}
		}
	}


	// debug
	/*
	FILE* debugFile;
	fopen_s(&debugFile, "lit_dist_huffman.txt", "w");

	for (int i = 0; i < 286; i++)
	{
		fprintf_s(debugFile, "bit %d : ", i);
		for (int j = 0; j < CUSTOM_LIT_LEN[i]; j++)
		{
			fprintf_s(debugFile, "%d", CUSTOM_LIT_HUFFMAN[i][j]);
		}
		fprintf_s(debugFile, "\n");
	}

	fprintf_s(debugFile, "\n DIST HUFFMAN TABLE \n");
	for (int i = 0; i < 32; i++)
	{
		fprintf_s(debugFile, "bit %d : ", i);
		for (int j = 0; j < CUSTOM_DIST_LEN[i]; j++)
		{
			fprintf_s(debugFile, "%d", CUSTOM_DIST_HUFFMAN[i][j]);
		}
		fprintf_s(debugFile, "\n");
	}
	
	fclose(debugFile);

	*/

	// if OK
	return true;
}








unsigned char* pngLoaderClass::inflate_custom_huffman(unsigned char* pointer)
{
	unsigned char* bitPtr = pointer;

	bool isLoop = true;

	unsigned char compareBit[15]; // max 15 bits

	while (isLoop)// read until find 256
	{
		// init compare
		for (int i = 0; i < 15; i++)
		{
			compareBit[i] = 255;

		}

		// read first MIN byte
		for (int i = 0; i < MIN_LIT_BIT; i++)
		{
			compareBit[i] = (*bitPtr);
			bitPtr++;
		}
	
		// compare
		for (int i = MIN_LIT_BIT; i <= 15; i++)
		{
			// match
			int matchCount = this->check_lit_huffman_identity(compareBit, i);

			if (matchCount <= 255)
			{
				// set value directly
				printf("matchCount %d\n", matchCount);
				*PNG_dataPtr = (unsigned char)matchCount;
				PNG_dataPtr++;
				break;
			}
			else if (matchCount == 256)
			{
				printf("end\n");
				isLoop = false;
				break;
			}
			else if (matchCount > 256 && matchCount < 286)
			{
				printf("SAME matchCount %d\n", matchCount);
				// find same length & distance
				// get same length
				int SAME_LENGTH = SAMELEN_TABLE[matchCount - 257];
				int exbit_len = SAMELEN_EXBIT_TABLE[matchCount - 257];
			
				// read extra bit
				int ex_len = 0;
				for (int E = 0; E < exbit_len; E++)
				{
					ex_len <<= 1;
					ex_len = ex_len | (*bitPtr);
					bitPtr++;
				}

				ex_len = this->reverse_bit(ex_len, exbit_len);
			
				//******************************
				SAME_LENGTH += ex_len;


				// get Distance*********************
				int ACT_DIST = 0;
				bitPtr = this->find_actual_dist(bitPtr, &ACT_DIST);

				// actual distance is set in ACT_DIST
				// set prev value

				printf("SAMELEN %d, ACTDIST %d\n", SAME_LENGTH, ACT_DIST);

				unsigned char* prev_pointer = PNG_dataPtr - ACT_DIST;
				for (int rep = 0; rep < SAME_LENGTH; i++)
				{
					*PNG_dataPtr = *prev_pointer;
					PNG_dataPtr++;
					prev_pointer++;
				}

				break;
			}
			else
			{
				// doesnt match
				if (i == 15)
				{
					std::cout << "doesnt match until 15 bits... error" << std::endl;
				}
				compareBit[i] = (*bitPtr);
				bitPtr++;
			}

		}// for i < 15


	}// read until find 256



	// if OK
	return bitPtr;
}




unsigned char* pngLoaderClass::find_actual_dist(unsigned char* pointer, int* actLength)
{
	unsigned char* bitPtr = pointer;

	unsigned char compare[15];

	for (int i = 0; i < 15; i++)
	{
		compare[i] = 255;
	}

	// set first DIST MIN bit
	for (int i = 0; i < MIN_DIST_BIT; i++)
	{
		compare[i] = (*bitPtr);
		bitPtr++;
	}


	// compare
	for (int i = MIN_DIST_BIT; i <= 15; i++)
	{
		int matchCount = this->check_dist_huffman_identity(compare, i);

		if (matchCount < 30)
		{
			// get base dist and exbit
			int base_dist = DIST_TABLE[matchCount];
			int exbit_len = DIST_EXBIT_TABLE[matchCount];
			int ex_dist = 0;
			for (int E = 0; E < exbit_len; E++)
			{
				ex_dist <<= 1;
				ex_dist = ex_dist | (*bitPtr);
				bitPtr++;
			}

			ex_dist = this->reverse_bit(ex_dist, exbit_len);

			// get actual distance
			base_dist += ex_dist;

			// set distance to pointer
			*actLength = base_dist;


			break;
		}
		else
		{
			if (i == 15)
			{
				std::cout << "doesnt match until 15bits(dist)... error." << std::endl;
			}

			compare[i] = *bitPtr;
			bitPtr++;
		}
	
	}// for i < 15


	// if OK
	return bitPtr;
}


////////////////////////////////////////////////////////////////


int pngLoaderClass::check_hc_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[7]; // max 7 bits
	unsigned char* readP = pointer;

	// read compare bit
	for (int i = 0; i < bitWidth; i++)
	{
		bits[i] = *readP;	readP++;
	}


	// compare
	bool isMatch;
	int matchCount = 9999;

	for (int k = 0; k < 19; k++)
	{
		isMatch = true;

		if (bitWidth == HC_LEN[k])
		{
			for (int i = 0; i < bitWidth; i++)
			{
				if (bits[i] != HC_HUFFMAN[k][i])
				{
					isMatch = false;
					break;
				}
			}
		}
		else
		{
			isMatch = false;
		}

		if (isMatch == true)
		{
			matchCount = k;
			break;
		}
	}

	return matchCount;

}



int pngLoaderClass::check_lit_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[15];
	unsigned char* readP = pointer;

	// read compare bit
	for (int i = 0; i < bitWidth; i++)
	{
		bits[i] = *readP;	readP++;
	}


	// compare
	bool isMatch;
	int matchCount = 9999;

	for (int k = 0; k < 286; k++)
	{
		isMatch = true;

		if (CUSTOM_LIT_LEN[k] == bitWidth)
		{
			for (int i = 0; i < bitWidth; i++)
			{
				if (bits[i] != CUSTOM_LIT_HUFFMAN[k][i])
				{
					isMatch = false;
					break;
				}
			}
		}
		else
		{
			isMatch = false;
		}


		if (isMatch == true)
		{
			matchCount = k;
			break;
		}
	}

	return matchCount;
}




int pngLoaderClass::check_dist_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[15];
	unsigned char* readP = pointer;

	// read compare bit
	for (int i = 0; i < bitWidth; i++)
	{
		bits[i] = *readP;	readP++;
	}

	bool isMatch;
	int matchCount = 9999;

	// compare
	for (int k = 0; k < 32; k++)
	{
		isMatch = true;

		if (bitWidth == CUSTOM_DIST_LEN[k])
		{
			for (int i = 0; i < bitWidth; i++)
			{
				if (bits[i] != CUSTOM_DIST_HUFFMAN[k][i])
				{
					isMatch = false;
					break;
				}
			}
		}
		else
		{
			isMatch = false;
		}
	
		if (isMatch == true)
		{
			matchCount = k;
			break;
		}

	}

	return matchCount;
}

/******************************************************/


unsigned int pngLoaderClass::reverse_bit(unsigned int value, unsigned int bitwidth)
{
	unsigned int returnValue = 0;
	unsigned int inValue = value;

	for (int i = 0; i < bitwidth; i++)
	{
		unsigned int bit = inValue & 1;
		inValue >>= 1;

		returnValue <<= 1;
		returnValue = returnValue | bit;
	}

	return returnValue;
}