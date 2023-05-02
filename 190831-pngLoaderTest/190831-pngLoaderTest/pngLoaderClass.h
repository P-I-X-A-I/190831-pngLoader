#pragma once
#include <fstream>
#include <iostream>

// to use htonl function
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")

class pngLoaderClass
{
public:

	unsigned char* PNG_dataPtr;
	unsigned char* FiltPNG_dataPtr;
	int PNG_width;
	int PNG_height;

	// for decode
	int SAMELEN_TABLE[29];
	int SAMELEN_EXBIT_TABLE[29];

	int DIST_TABLE[30];
	int DIST_EXBIT_TABLE[30];

	// huffman table
	unsigned char FIX_LIT_LEN[288];
	unsigned char FIX_LIT_HUFFMAN[288][9];// max 9bit
	//unsigned char FIX_DIST_LEN[32]; // always 5
	unsigned char FIX_DIST_HUFFMAN[32][5];

	unsigned char HC_LEN[19];
	unsigned char HC_HUFFMAN[19][7]; // max 7bits

	unsigned char CUSTOM_LIT_LEN[288];
	unsigned char CUSTOM_DIST_LEN[32];

	unsigned char CUSTOM_LIT_HUFFMAN[288][15]; // max 15 bits
	unsigned char CUSTOM_DIST_HUFFMAN[32][15];

	int MIN_LIT_BIT = 0;
	int MIN_DIST_BIT = 0;

	pngLoaderClass();
	~pngLoaderClass();


	bool load_png24_from_path(const char* filePath);

private:
	bool decode_IDAT_data(unsigned char* idat_pointer, long dataLength);
	bool unarchive_compressed_data(unsigned char* comp_pointer, long dataLength);

	unsigned char* decode_fixed_huffman(unsigned char* bit_pointer);
	unsigned char* decode_custom_huffman(unsigned char* bit_pointer);



	int check_fixed_lit_huffman_identity(unsigned char* pointer, int bitWidth);
	int check_fixed_dist_huffman_identity(unsigned char* pointer, int bitWidth);

	unsigned char* setup_custom_huffman_table_length(unsigned char* pointer);
	bool setup_custom_huffman_table_itself();
	unsigned char* inflate_custom_huffman(unsigned char* pointer);
	unsigned char* find_actual_dist(unsigned char* pointer, int* actLength);

	int check_hc_huffman_identity(unsigned char* pointer, int bitWidth);
	int check_lit_huffman_identity(unsigned char* pointer, int bitWidth);
	int check_dist_huffman_identity(unsigned char* pointer, int bitWidth);

	unsigned int reverse_bit(unsigned int value, unsigned int bitwidth);
};

