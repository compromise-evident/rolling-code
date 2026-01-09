//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
long long generate_bytes = 2000;                                                //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
int        digit_length  = 200; //50 to 50000
//digit_length is the length of a (jumping) value,
//near which prime gaps are found. Bigger = more secure.

/*rolling-code - version 5.0.0
Writes secure pseudorandom bytes to file based on prime
gaps,  symmetric with whom  you have in common  any file
(used once to make a rolling-seeds file you can alter.)*/

#include <fstream>
#include <gmp.h>
#include <iostream>
using namespace std;
int main()
{	int raw_byte;
	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	//Creates seeds file if missing.
	in_stream.open("private_seeds");
	if(in_stream.fail() == true)
	{	//Gets path, fixes it, tries it.
		cout << "\n(Since digit_length = " << digit_length << ", you'll get a rolling-seeds file containing"
		     << "\na " << digit_length << "-digit value, near which prime gaps are found. Continued gaps are"
		     << "\nthen used for the randomness in changing that value, end of each run.)\n"
		     << "\nBecause digit_length = " << digit_length << ",\njust once, drop/enter any file\nof " << digit_length << "+ random first bytes:\n";
		char path[100000] = {'\0'}; cin.getline(path, 100000); if(path[0] == '\0') {cin.getline(path, 100000);}
		if(path[0] == '\'') {for(int bm = 0, a = 0; a < 100000; a++) {if(path[a] != '\'') {path[bm] = path[a]; if(path[bm] == '\\') {path[bm] = '\'';} bm++;}}}
		for(int a = 99999; a >= 0; a--) {if(path[a] != '\0') {if(path[a] == ' ') {path[a] = '\0';} break;}}
		in_stream.open(path); if(in_stream.fail() == true) {cout << "\nNo path " << path << "\n"; return 0;} in_stream.close();
		
		//Copies bytes, writes them modified.
		in_stream.open(path);
		out_stream.open("private_seeds");
		for(int a = 0; a < digit_length; a++)
		{	in_stream.get(file_byte);
			if(in_stream.eof() == true) {cout << "\nFile too small.\n"; in_stream.close(); out_stream.close(); remove("private_seeds"); return 0;}
			raw_byte = file_byte; if(raw_byte < 0) {raw_byte += 256;} out_stream.put((raw_byte % 10) + 48);
		}
		in_stream.close();
		out_stream.close();
	}
	in_stream.close();
	
	//Loads seeds.
	char seeds[50001] = {'\0'};
	in_stream.open("private_seeds"); for(int a = 0; a < digit_length; a++) {in_stream.get(seeds[a]);} in_stream.close();         //Loads value.
	if(seeds[digit_length - 1] == '\0') {cout << "\n\nprivate_seeds file too small.\n\n"; return 0;}                             //Checks its length.
	if(seeds[0] == '0') {seeds[0] = '5';}                                                                                        //Forces its length.
	mpz_t in, out; mpz_init(in); mpz_init(out); mpz_set_str(in, seeds, 10); mpz_nextprime(out, in); mpz_get_str(seeds, 10, out); //Makes it prime.
	mpz_t prime, two; mpz_init(prime); mpz_init(two); mpz_set_str(prime, seeds, 10); mpz_set_ui(two, 2);                         //Dedicates.
	
	//Generates randomness.
	cout << "\nWriting bytes...\n";
	out_stream.open("random_bytes");
	for(long long gap = 2, a = 0; a < generate_bytes;)
	{	mpz_add(prime, prime, two);
		int primality = mpz_probab_prime_p(prime, 25);
		if(primality == false) {gap += 2;}
		else
		{	mpz_get_str(seeds, 10, prime);
			gap *= 10; gap += seeds[digit_length - 3] - 48;
			gap *= 10; gap += seeds[digit_length - 2] - 48; gap %= 256;
			if(gap < 128) {out_stream.put(gap);} else {out_stream.put(gap - 256);}
			gap = 2; a++;
		}
	}
	out_stream.close();
	
	//Updates seeds file.
	cout << "Rolling seed...\n";
	out_stream.open("private_seeds");
	for(long long gap = 2, a = 0; a < digit_length;)
	{	mpz_add(prime, prime, two);
		int primality = mpz_probab_prime_p(prime, 25);
		if(primality == false) {gap += 2;}
		else {mpz_get_str(seeds, 10, prime); out_stream << seeds[digit_length - 2]; gap = 2; a++;}
	}
	out_stream.close();
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//Creates analysis file about random_bytes file. You may remove all of the following blocks.
	
	//Gets byte occurrence.
	cout << "Analyzing bytes...\n";
	in_stream.open("random_bytes"); in_stream.get(file_byte); long long byte_occur[256] = {0};
	for(; in_stream.eof() == false; in_stream.get(file_byte)) {raw_byte = file_byte; if(raw_byte < 0) {raw_byte += 256;} byte_occur[raw_byte]++;}
	in_stream.close();
	
	//Gets bit occurrence.
	long long bit_occur[2] = {0};
	for(int a = 0; a < 256; a++)
	{	raw_byte = a; bool binary[8] = {0}; int place = 128, zeros = 0, ones = 0;
		for(int b = 0; b < 8; b++) {if(raw_byte >= place) {binary[b] = 1; raw_byte -= place;} place /= 2;}
		for(int b = 0; b < 8; b++) {if(binary[b] == 0) {zeros++;} else {ones++;}}
		if(byte_occur[a] > 0) {zeros *= byte_occur[a]; ones *= byte_occur[a]; bit_occur[0] += zeros; bit_occur[1] += ones;}
	}
	
	//Creates file.
	in_stream.open("random_bytes"); out_stream.open("analysis"); in_stream.get(file_byte);
	out_stream << "random_bytes\n\noccurrence of bit 0: " << bit_occur[0] << "\n"; out_stream << "occurrence of bit 1: " << bit_occur[1] << "\n\n";
	for(int a = 0; a < 256; a++) {out_stream << "occurrence of byte " << a << ": " << byte_occur[a] << "\n";}
	long long distinct = 0, total = 0; for(int a = 0; a < 256; a++) {if(byte_occur[a] != 0) {distinct++;} total += byte_occur[a];}
	out_stream << "\n" << distinct << " distinct, " << total << " total" << "\n\nEvery byte raw:\n";
	for(; in_stream.eof() == false; in_stream.get(file_byte)) {raw_byte = file_byte; if(raw_byte < 0) {raw_byte += 256;} out_stream << raw_byte << "\n";}
	in_stream.close(); out_stream.close();
	
	in_stream.open("random_bytes"); out_stream.open("analysis", ios::app); in_stream.get(file_byte);
	out_stream << "\nOnly the 97 standard text bytes (9, 10, and 32-126):\n";
	for(; in_stream.eof() == false; in_stream.get(file_byte))
	{	if      ((file_byte > 31) && (file_byte < 127)) {out_stream.put(file_byte);}
		else if ((file_byte == 9) || (file_byte == 10)) {out_stream.put(file_byte);}
	}
	in_stream.close(); out_stream.close();
}
