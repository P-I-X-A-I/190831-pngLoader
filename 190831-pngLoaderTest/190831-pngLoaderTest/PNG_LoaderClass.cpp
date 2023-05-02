#include "stdafx.h"
#include "PNG_LoaderClass.h"


PNG_LoaderClass::PNG_LoaderClass()
{
	SAME_TABLE[0] = 3;	SAME_EX_BIT[0] = 0;
	SAME_TABLE[1] = 4;	SAME_EX_BIT[1] = 0;
	SAME_TABLE[2] = 5;	SAME_EX_BIT[2] = 0;
	SAME_TABLE[3] = 6;	SAME_EX_BIT[3] = 0;
	SAME_TABLE[4] = 7;	SAME_EX_BIT[4] = 0;
	SAME_TABLE[5] = 8;	SAME_EX_BIT[5] = 0;
	SAME_TABLE[6] = 9;	SAME_EX_BIT[6] = 0;
	SAME_TABLE[7] = 10;	SAME_EX_BIT[7] = 0;
	SAME_TABLE[8] = 11;	SAME_EX_BIT[8] = 1;
	SAME_TABLE[9] = 13;	SAME_EX_BIT[9] = 1;

	SAME_TABLE[10] = 15;	SAME_EX_BIT[10] = 1;
	SAME_TABLE[11] = 17;	SAME_EX_BIT[11] = 1;
	SAME_TABLE[12] = 19;	SAME_EX_BIT[12] = 2;
	SAME_TABLE[13] = 23;	SAME_EX_BIT[13] = 2;
	SAME_TABLE[14] = 27;	SAME_EX_BIT[14] = 2;
	SAME_TABLE[15] = 31;	SAME_EX_BIT[15] = 2;
	SAME_TABLE[16] = 35;	SAME_EX_BIT[16] = 3;
	SAME_TABLE[17] = 43;	SAME_EX_BIT[17] = 3;
	SAME_TABLE[18] = 51;	SAME_EX_BIT[18] = 3;
	SAME_TABLE[19] = 59;	SAME_EX_BIT[19] = 3;

	SAME_TABLE[20] = 67;	SAME_EX_BIT[20] = 4;
	SAME_TABLE[21] = 83;	SAME_EX_BIT[21] = 4;
	SAME_TABLE[22] = 99;	SAME_EX_BIT[22] = 4;
	SAME_TABLE[23] = 115;	SAME_EX_BIT[23] = 4;
	SAME_TABLE[24] = 131;	SAME_EX_BIT[24] = 5;
	SAME_TABLE[25] = 163;	SAME_EX_BIT[25] = 5;
	SAME_TABLE[26] = 195;	SAME_EX_BIT[26] = 5;
	SAME_TABLE[27] = 227;	SAME_EX_BIT[27] = 5;
	SAME_TABLE[28] = 258;	SAME_EX_BIT[28] = 0;

	///////////////////////////////////////////////////

	DIST_TABLE[0] = 1;	DIST_EX_BIT[0] = 0;
	DIST_TABLE[1] = 2;	DIST_EX_BIT[1] = 0;
	DIST_TABLE[2] = 3;	DIST_EX_BIT[2] = 0;
	DIST_TABLE[3] = 4;	DIST_EX_BIT[3] = 0;
	DIST_TABLE[4] = 5;	DIST_EX_BIT[4] = 1;
	DIST_TABLE[5] = 7;	DIST_EX_BIT[5] = 1;
	DIST_TABLE[6] = 9;	DIST_EX_BIT[6] = 2;
	DIST_TABLE[7] = 13;	DIST_EX_BIT[7] = 2;
	DIST_TABLE[8] = 17;	DIST_EX_BIT[8] = 3;
	DIST_TABLE[9] = 25;	DIST_EX_BIT[9] = 3;

	DIST_TABLE[10] = 33;	DIST_EX_BIT[10] = 4;
	DIST_TABLE[11] = 49;	DIST_EX_BIT[11] = 4;
	DIST_TABLE[12] = 65;	DIST_EX_BIT[12] = 5;
	DIST_TABLE[13] = 97;	DIST_EX_BIT[13] = 5;
	DIST_TABLE[14] = 129;	DIST_EX_BIT[14] = 6;
	DIST_TABLE[15] = 193;	DIST_EX_BIT[15] = 6;
	DIST_TABLE[16] = 257;	DIST_EX_BIT[16] = 7;
	DIST_TABLE[17] = 385;	DIST_EX_BIT[17] = 7;
	DIST_TABLE[18] = 513;	DIST_EX_BIT[18] = 8;
	DIST_TABLE[19] = 769;	DIST_EX_BIT[19] = 8;

	DIST_TABLE[20] = 1025;	DIST_EX_BIT[20] = 9;
	DIST_TABLE[21] = 1537;	DIST_EX_BIT[21] = 9;
	DIST_TABLE[22] = 2049;	DIST_EX_BIT[22] = 10;
	DIST_TABLE[23] = 3073;	DIST_EX_BIT[23] = 10;
	DIST_TABLE[24] = 4097;	DIST_EX_BIT[24] = 11;
	DIST_TABLE[25] = 6145;	DIST_EX_BIT[25] = 11;
	DIST_TABLE[26] = 8193;	DIST_EX_BIT[26] = 12;
	DIST_TABLE[27] = 12289;	DIST_EX_BIT[27] = 12;
	DIST_TABLE[28] = 16385;	DIST_EX_BIT[28] = 13;
	DIST_TABLE[29] = 24577;	DIST_EX_BIT[29] = 13;


}


PNG_LoaderClass::~PNG_LoaderClass()
{
}


unsigned char* PNG_LoaderClass::construct_custom_huffman_table(unsigned char* bit_pointer)
{
	std::cout << "\n*** CONSTRUCT CUSTOM HUFFMAN TABLE ***" << std::endl;

	unsigned char* bitP = bit_pointer;

	// HLIT (5bit)
	unsigned char HLIT = 0;
	HLIT |= (*bitP);	bitP++;		HLIT <<= 1;
	HLIT |= (*bitP);	bitP++;		HLIT <<= 1;
	HLIT |= (*bitP);	bitP++;		HLIT <<= 1;
	HLIT |= (*bitP);	bitP++;		HLIT <<= 1;
	HLIT |= (*bitP);	bitP++;

	HLIT = this->revert_bit(HLIT, 5);
	std::cout << "HLIT : " << HLIT + 257 << std::endl;

	// HDIST (5bit)
	unsigned char HDIST = 0;
	HDIST |= (*bitP);	bitP++;		HDIST <<= 1;
	HDIST |= (*bitP);	bitP++;		HDIST <<= 1;
	HDIST |= (*bitP);	bitP++;		HDIST <<= 1;
	HDIST |= (*bitP);	bitP++;		HDIST <<= 1;
	HDIST |= (*bitP);	bitP++;

	HDIST = this->revert_bit(HDIST, 5);
	std::cout << "HDIST : " << HDIST + 1 << std::endl;

	// HCLEN (4bit)
	unsigned char HCLEN = 0;
	HCLEN |= (*bitP);	bitP++;		HCLEN <<= 1;
	HCLEN |= (*bitP);	bitP++;		HCLEN <<= 1;
	HCLEN |= (*bitP);	bitP++;		HCLEN <<= 1;
	HCLEN |= (*bitP);	bitP++;	

	HCLEN = this->revert_bit(HCLEN, 4);
	std::cout << "HCLEN : " << HCLEN + 4 << std::endl;


	//***************************************
	unsigned char ORDER[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

	memset(HC_LEN, 0, 19);
	memset(HC_HUFFMAN, 255, 19 * 7);
	//***************************************


	// read (HCLEN+4) * 3bit
	int MIN_HCLEN = 255;

	for (int i = 0; i < (HCLEN + 4); i++)
	{
		unsigned int tempVal = 0;
		tempVal |= (*bitP);		bitP++;	tempVal <<= 1;
		tempVal |= (*bitP);		bitP++;	tempVal <<= 1;
		tempVal |= (*bitP);		bitP++;

		tempVal = this->revert_bit(tempVal, 3);
		HC_LEN[ ORDER[i] ] = tempVal;
		
		// find minimu bitlength
		if (tempVal < MIN_HCLEN && tempVal != 0)
		{
			MIN_HCLEN = tempVal;
		}
	}


	// set HC_HUFFMAN table
	unsigned char base = 0;
	for (int len = MIN_HCLEN; len <= 7; len++)
	{
		base <<= 1; // 110 -> 1100

		for (int i = 0; i < (HCLEN + 4); i++)
		{
			if (HC_LEN[i] == len)
			{
				int cp = base;
				for (int k = len - 1; k >= 0; k--)
				{
					HC_HUFFMAN[i][k] = cp & 1;
					cp >>= 1;
				}

				base++;
			}
		}
	}


	//******************************************************
	//******************************************************

	// get CUSTOM_LIT_LEN & CUSTOM_DIST_LEN

	// init
	memset(CUSTOM_LIT_LEN, 0, 286);
	memset(CUSTOM_DIST_LEN, 0, 30);

	bool isLoop = true;
	unsigned char compare[7];
	int IDX = 0;

	while (isLoop)
	{
		// init
		memset(compare, 255, 7);

		// first MIN_HCLEN bit
		for (int i = 0; i < MIN_HCLEN; i++)
		{
			compare[i] = (*bitP);
			bitP++;
		}


		// compare
		for (int i = MIN_HCLEN; i <= 7; i++)
		{
			int match = this->check_hc_huffman_identity(compare, i);

			if (match <= 15)
			{
				// set length value directly
				CUSTOM_LIT_LEN[IDX] = match;
				IDX++;
				break;
			}
			else if (match == 16)
			{
				// set prev value repeatedly
				// read extra 2bit
				int ex_repeat = 0;
				ex_repeat |= (*bitP);	bitP++;
				ex_repeat <<= 1;
				ex_repeat |= (*bitP);	bitP++;
				
				ex_repeat = this->revert_bit(ex_repeat, 2);
				ex_repeat += 3; // actual repeat count

				// prev value
				int PREV = CUSTOM_LIT_LEN[IDX - 1];

				// set value
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_LIT_LEN[IDX] = PREV;
					IDX++;
				}

				break;
			}
			else if (match == 17 || match == 18)
			{
				// set 0 repeatedly
				int bWidth;
				int Bias;

				if (match == 17) { bWidth = 3; Bias = 3; }
				else { bWidth = 7;	Bias = 11; }

				// read extra bit
				int ex_repeat = 0;
				for (int E = 0; E < bWidth; E++)
				{
					ex_repeat <<= 1;
					ex_repeat |= (*bitP);
					bitP++;
				}
				ex_repeat = this->revert_bit(ex_repeat, bWidth);
				ex_repeat += Bias;	// actual repeat count

				// set 0
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_LIT_LEN[IDX] = 0;
					IDX++;
				}

				break;
			}
			else
			{
				// doesnt match
				compare[i] = *bitP;
				bitP++;
			}
			
		}// for <= 7

		//*******************
		if (IDX == (HLIT+257))
		{
			isLoop = false;
			break;
		}
		else if (IDX > (HLIT + 257)) // DEBUGGGGGGG
		{
			std::cout << "over IDX.... error.." << std::endl;
		}
	}// while


	//********************** GET HDIST LEN ****************************
	isLoop = true;
	IDX = 0;

	while (isLoop)
	{
		// init
		memset(compare, 255, 7);

		// set first MIN_HCLEN bit
		for (int i = 0; i < MIN_HCLEN; i++)
		{
			compare[i] = *bitP;
			bitP++;
		}

		// compare
		for (int i = MIN_HCLEN; i <= 7; i++)
		{
			int match = this->check_hc_huffman_identity(compare, i);

			if (match <= 15)
			{
				CUSTOM_DIST_LEN[IDX] = match;
				IDX++;
				break;
			}
			else if (match == 16)
			{
				// set prev value repeatedly
				// read extra 2bit
				int ex_repeat = 0;
				ex_repeat |= (*bitP);	bitP++;
				ex_repeat <<= 1;
				ex_repeat |= (*bitP);	bitP++;
				ex_repeat = this->revert_bit(ex_repeat, 2);

				ex_repeat += 3; // actual repeat count

				// prev value
				int PREV = CUSTOM_DIST_LEN[IDX - 1];

				// repeat
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_DIST_LEN[IDX] = PREV;
					IDX++;
				}

				break;
			}
			else if (match == 17 || match == 18)
			{
				int bWidth;
				int Bias;

				if (match == 17) { bWidth = 3;	Bias = 3; }
				else { bWidth = 7;	Bias = 11; }

				// read extra bit
				int ex_repeat = 0;
				for (int E = 0; E < bWidth; E++)
				{
					ex_repeat <<= 1;
					ex_repeat |= (*bitP);
					bitP++;
				}
				ex_repeat = this->revert_bit(ex_repeat, bWidth);
				ex_repeat += Bias; //actual repeat count

				// set 0
				for (int R = 0; R < ex_repeat; R++)
				{
					CUSTOM_DIST_LEN[IDX] = 0;

					IDX++;
				}

				break;
			}
			else
			{
				// doesnt match
				if (i == 7)
				{
					std::cout << "doesnt match until 7bit... error" << std::endl;
				}
				compare[i] = *bitP;
				bitP++;
			}
		
		}// for i <= 7

		if (IDX == (HDIST + 1))
		{
			isLoop = false;
			break;
		}
		else if (IDX > (HDIST + 1)) // DEBUGGGGG
		{
			std::cout << "IDX is over (HDIST+1)... error.." << std::endl;
		}

	}// while




	// construct CUSTOM_HUFFMAN table

	// find minimum length
	MIN_CUSTOM_LIT = 255;
	MIN_CUSTOM_DIST = 255;
	for (int i = 0; i < 286; i++)
	{
		if (CUSTOM_LIT_LEN[i] < MIN_CUSTOM_LIT && CUSTOM_LIT_LEN[i] != 0)
		{
			MIN_CUSTOM_LIT = CUSTOM_LIT_LEN[i];
		}

		if (i < 30)
		{
			if (CUSTOM_DIST_LEN[i] < MIN_CUSTOM_DIST && CUSTOM_DIST_LEN[i] != 0)
			{
				MIN_CUSTOM_DIST = CUSTOM_DIST_LEN[i];
			}
		}
	}

	// construct CUSTOM HUFFMAN table
	// init
	memset(CUSTOM_LIT_HUFFMAN, 255, 286 * 15);
	memset(CUSTOM_DIST_HUFFMAN, 255, 30 * 15);

	unsigned int base16 = 0;

	for (int len = MIN_CUSTOM_LIT; len <= 15; len++)
	{
		base16 <<= 1; // 110 -> 1100

		for (int i = 0; i < 286; i++)
		{
			if (CUSTOM_LIT_LEN[i] == len)
			{
				//printf("%d : ", i);
				int cp = base16;
				for (int k = len - 1; k >= 0; k--)
				{
					CUSTOM_LIT_HUFFMAN[i][k] = cp & 1;
					//printf("%d", CUSTOM_LIT_HUFFMAN[i][k]);
					cp >>= 1;
				}
				//printf("\n");
				base16++;
			}
		}
	}


	//// dist table
	base16 = 0;

	for (int len = MIN_CUSTOM_DIST; len <= 15; len++)
	{
		base16 <<= 1; //110 -> 1100

		for (int i = 0; i < 30; i++)
		{
			if (CUSTOM_DIST_LEN[i] == len)
			{
				//printf("%d : ", i);

				int cp = base16;
				for (int k = len - 1; k >= 0; k--)
				{
					CUSTOM_DIST_HUFFMAN[i][k] = cp & 1;
					//printf("%d", CUSTOM_DIST_HUFFMAN[i][k]);
					cp >>= 1;
				}
				//printf("\n");
				base16++;
			}
		}
	}


	return bitP;
}


//****************************************
int PNG_LoaderClass::check_hc_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[7];
	
	// read compare bit
	for (int i = 0; i < bitWidth; i++)
	{
		bits[i] = *pointer;
		pointer++;
	}

	// compare
	bool isMatch;
	int matchCount = 9999;

	for (int k = 0; k < 19; k++)
	{
		isMatch = true;

		if (HC_LEN[k] == bitWidth)
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
	///////////////////////////////////////////
		if (isMatch == true)
		{
			matchCount = k;
			break;
		}
	}

	return matchCount;
}




//********************************************************

unsigned char* PNG_LoaderClass::decode_custom_huffman_datapart(unsigned char* bit_pointer)
{
	unsigned char* bitP = bit_pointer;

	unsigned char compare[15];
	bool isLoop = true;

	while (isLoop)
	{
		// init
		memset(compare, 255, 15);

		// read first MIN_CUSTOM_LIT bit
		for (int i = 0; i < MIN_CUSTOM_LIT; i++)
		{
			compare[i] = (*bitP);
			bitP++;
		}
	

		// compare
		for (int i = MIN_CUSTOM_LIT; i <= 15; i++)
		{
			int match = this->check_lit_huffman_identity(compare, i);

			if (match <= 255)
			{
				// set data directly
				*FiltPNG_dataPtr = (unsigned char)match;
				FiltPNG_dataPtr++;
				break;
			}
			else if (match == 256)
			{
				// end
				isLoop = false;
				break;
			}
			else if (match > 256 && match < 286)
			{
				// repeat value in window
				bitP = this->repeat_window_value(bitP, match);
				break;
			}
			else
			{
				// doesnt match
				if (i == 15) // DEBUGGGGGGG
				{
					std::cout << "doesnt match until 15 bit.... error " << std::endl;
				}
				compare[i] = (*bitP);
				bitP++;
			}
		}

	}// while


	return bitP;
}


//////////////////////////////////////////////

unsigned char* PNG_LoaderClass::repeat_window_value(unsigned char* pointer, int match)
{
	unsigned char* bitP = pointer;

	int same_length = SAME_TABLE[match - 257];
	int ex_bit = SAME_EX_BIT[match - 257];

	// read extra bit
	int ex_len = 0;
	for (int E = 0; E < ex_bit; E++)
	{
		ex_len <<= 1;
		ex_len |= (*bitP);
		bitP++;
	}
	ex_len = this->revert_bit(ex_len, ex_bit);
	same_length += ex_len;	// actual length


	// find DIST value
	unsigned char inCompare[15];
	bool inLoop = true;

	while (inLoop)
	{
		// init
		memset(inCompare, 255, 15);

		// read MIN_DIST_LEN bit
		for (int i = 0; i < MIN_CUSTOM_DIST; i++)
		{
			inCompare[i] = *bitP;
			bitP++;
		}

		// compare
		for (int i = MIN_CUSTOM_DIST; i <= 15; i++)
		{
			int match = this->check_dist_huffman_identity(inCompare, i);

			if (match < 30)
			{
				int distance = DIST_TABLE[match];
				int extra_bit = DIST_EX_BIT[match];

				// read extra bit
				int extra_dist = 0;
				for (int E = 0; E < extra_bit; E++)
				{
					extra_dist <<= 1;
					extra_dist |= (*bitP);
					bitP++;
				}
				extra_dist = this->revert_bit(extra_dist, extra_bit);
				distance += extra_dist; /// actual distance


				// read prev PNG value samelength time
				unsigned char* readPNG = FiltPNG_dataPtr - distance;
				for (int rep = 0; rep < same_length; rep++)
				{
					*FiltPNG_dataPtr = *readPNG;
					FiltPNG_dataPtr++;
					readPNG++;
				}


				inLoop = false;
				break;
			}
			else
			{
				// doesnt match
				if (i == 15) // DEBUGGGGG
				{
					std::cout << "doesnt match until 15bit (dist)... error..." << std::endl;
				}
				inCompare[i] = *bitP;
				bitP++;
			}

		}//for i <= 15

	}// while

	return bitP;
}


//////////////////////////////////////

int PNG_LoaderClass::check_lit_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[15];
	
	// read compare bit
	for (int i = 0; i < bitWidth; i++)
	{
		bits[i] = *pointer;	pointer++;
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
		///////////////////////
		if (isMatch == true)
		{
			matchCount = k;
			break;
		}
	}

	return matchCount;
}




int PNG_LoaderClass::check_dist_huffman_identity(unsigned char* pointer, int bitWidth)
{
	unsigned char bits[15];

	// read compare bit
	for (int i = 0; i < bitWidth; i++)
	{
		bits[i] = *pointer; pointer++;
	}


	// compare
	bool isMatch;
	int matchCount = 9999;

	for (int k = 0; k < 30; k++)
	{
		isMatch = true;
		if (CUSTOM_DIST_LEN[k] == bitWidth)
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
		////////////////////////
		if (isMatch == true)
		{
			matchCount = k;
			break;
		}
	}

	return matchCount;
}
