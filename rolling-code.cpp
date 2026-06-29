//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
long long generate_bytes = 100000;



/*Version 6.0.0
Write secure pseudorandom bytes to file based on SHA3-512, symmetric
with whom you share any file (used once to make a rolling-seed file
you can alter in any way). Ready for any future hash. */

#include <fstream>
#include <iostream>
#include <string>
int main()
{	char file_byte;
	std::ifstream in_stream;
	std::ofstream out_stream;
	
	std::string SHA3_512_input;
	std::string SHA3_512_output;
	
	//Creates seed file if missing.
	in_stream.open("rolling-seed");
	if(!in_stream)
	{	//Gets path.
		std::cout << "\nJust once, drop/enter any file, preferably one with many random bytes.\n"
		          << "(Create a rolling-seed file containing the SHA3-512 hash of your file).\n";
		std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
		if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
		in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
		
		//Loads user's file.
		in_stream.open(path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Loads user's file).\n"; return 1;}
		SHA3_512_input = ""; for(; in_stream.get(file_byte);) {SHA3_512_input.push_back(file_byte);}
		in_stream.close();
		
		//Takes SHA3-512 of user's file.
		{std::string msg = SHA3_512_input; unsigned long long state[25] = {0}; const unsigned long long RC[24] = {0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL, 0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL, 0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL, 0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL, 0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL, 0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL, 0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL, 0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL}; const int r[25] = {0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43, 25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14}; msg.push_back(0x06); for(; (msg.length() % 72) != 71;) {msg.push_back(0x00);} msg.push_back(0x80); for(unsigned long long block_offset = 0; block_offset < msg.length(); block_offset += 72) {for(int i = 0; i < 9; i++) {unsigned long long word = 0; for(int j = 0; j < 8; j++) {unsigned long long idx = block_offset + (i * 8 + j); word |= (unsigned long long)(unsigned char)msg[idx] << (j * 8);} state[i] ^= word;} for(int round = 0; round < 24; round++) {unsigned long long C[5], D[5]; for(int x = 0; x < 5; x++) {C[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];} for(int x = 0; x < 5; x++) {D[x] = C[(x + 4) % 5] ^ ((C[(x + 1) % 5] << 1) | (C[(x + 1) % 5] >> 63));} for(int x = 0; x < 5; x++) {for(int y = 0; y < 5; y++) {state[x + y * 5] ^= D[x];}} unsigned long long next_state[25]; for(int x = 0; x < 5; x++) {for(int y = 0; y < 5; y++) {int idx = x + y * 5; unsigned long long rot = (state[idx] << r[idx]) | (state[idx] >> (64 - r[idx])); next_state[y + ((2 * x + 3 * y) % 5) * 5] = rot;}} for(int y = 0; y < 5; y++) {for(int x = 0; x < 5; x++) {state[x + y * 5] = next_state[x + y * 5] ^ ((~next_state[(x + 1) % 5 + y * 5]) & next_state[(x + 2) % 5 + y * 5]);}} state[0] ^= RC[round];}} SHA3_512_output = ""; const char symbols[] = "0123456789abcdef"; for(int a = 0; a < 8; a++) {for(int b = 0; b < 8; b++) {int byte_val = (state[a] >> (b * 8)) & 0xFF; SHA3_512_output += symbols[(byte_val >> 4) & 0x0F]; SHA3_512_output += symbols[byte_val & 0x0F];}}}
		
		//Writes the hash.
		out_stream.open("rolling-seed"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Writes the hash).\n"; return 1;}
		out_stream << SHA3_512_output;
		out_stream.close();
	}
	in_stream.close();
	
	//Loads seed.
	in_stream.open("rolling-seed"); if(!in_stream) {std::cout << "\nCan't open file for reading. (Loads seed).\n"; return 1;}
	std::string seed = ""; for(; in_stream.get(file_byte);) {seed.push_back(file_byte);}
	in_stream.close();
	
	//Generates pseudorandomness.
	out_stream.open("pseudorandom_bytes"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Generates pseudorandomness).\n"; return 1;}
	SHA3_512_input = seed;
	for(long long a = 0; a < generate_bytes; a++)
	{	SHA3_512_input += SHA3_512_input;
		{std::string msg = SHA3_512_input; unsigned long long state[25] = {0}; const unsigned long long RC[24] = {0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL, 0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL, 0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL, 0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL, 0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL, 0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL, 0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL, 0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL}; const int r[25] = {0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43, 25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14}; msg.push_back(0x06); for(; (msg.length() % 72) != 71;) {msg.push_back(0x00);} msg.push_back(0x80); for(unsigned long long block_offset = 0; block_offset < msg.length(); block_offset += 72) {for(int i = 0; i < 9; i++) {unsigned long long word = 0; for(int j = 0; j < 8; j++) {unsigned long long idx = block_offset + (i * 8 + j); word |= (unsigned long long)(unsigned char)msg[idx] << (j * 8);} state[i] ^= word;} for(int round = 0; round < 24; round++) {unsigned long long C[5], D[5]; for(int x = 0; x < 5; x++) {C[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];} for(int x = 0; x < 5; x++) {D[x] = C[(x + 4) % 5] ^ ((C[(x + 1) % 5] << 1) | (C[(x + 1) % 5] >> 63));} for(int x = 0; x < 5; x++) {for(int y = 0; y < 5; y++) {state[x + y * 5] ^= D[x];}} unsigned long long next_state[25]; for(int x = 0; x < 5; x++) {for(int y = 0; y < 5; y++) {int idx = x + y * 5; unsigned long long rot = (state[idx] << r[idx]) | (state[idx] >> (64 - r[idx])); next_state[y + ((2 * x + 3 * y) % 5) * 5] = rot;}} for(int y = 0; y < 5; y++) {for(int x = 0; x < 5; x++) {state[x + y * 5] = next_state[x + y * 5] ^ ((~next_state[(x + 1) % 5 + y * 5]) & next_state[(x + 2) % 5 + y * 5]);}} state[0] ^= RC[round];}} SHA3_512_output = ""; const char symbols[] = "0123456789abcdef"; for(int a = 0; a < 8; a++) {for(int b = 0; b < 8; b++) {int byte_val = (state[a] >> (b * 8)) & 0xFF; SHA3_512_output += symbols[(byte_val >> 4) & 0x0F]; SHA3_512_output += symbols[byte_val & 0x0F];}}}
		std::string first_16_hex = SHA3_512_output.substr(0, 16);
		unsigned long long pseudorandom_byte = std::stoull(first_16_hex, 0, 16);
		out_stream.put(pseudorandom_byte % 256);
		SHA3_512_input = SHA3_512_output;
	}
	out_stream.close();
	
	//Updates seed file.
	out_stream.open("rolling-seed"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Updates seed file).\n"; return 1;}
	out_stream << SHA3_512_output;
	out_stream.close();
}
