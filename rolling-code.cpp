//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
long long generate_bytes = 2000;                                                //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
int         digit_length =  200; //50000 max
//digit_length is the length of a jumping value (rolling-seed)
//near which prime gaps are found for generating pseudorandomness.



/*Version 5.0.2
Writes secure pseudorandom bytes to file based on prime
gaps,  symmetric with whom  you have in common  any file
(used once to make a rolling-seed file you can alter). */

#include <filesystem>
#include <fstream>
#include <gmp.h>
#include <iostream>
#include <string>
int main()
{	int raw_byte;
	char file_byte;
	std::ifstream in_stream;
	std::ofstream out_stream;
	
	//Creates seed file if missing.
	in_stream.open("rolling-seed");
	if(!in_stream)
	{	std::cout << "\n(Since digit_length = " << digit_length << ", you'll get a rolling-seed file containing"
		          << "\na " << digit_length << "-digit value, near which prime gaps are found. Continued gaps are"
		          << "\nthen used for pseudorandomness in changing that value, end of each run).\n"
		          << "\nBecause digit_length = " << digit_length << ",\njust once, drop/enter any file\nof " << digit_length << "+ random first bytes:\n";
		
		//Gets path.
		std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
		if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
		in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
		
		//Checks file size.
		if(std::filesystem::file_size(path) < (unsigned long long)digit_length) {std::cout << "\nFile too small.\n"; return 0;}
		
		//Copies bytes, writes them modified.
		in_stream.open(path);            if( !in_stream) {std::cout << "\nCan't open file for reading. (Copies bytes, writes them modified).\n"; return 1;}
		out_stream.open("rolling-seed"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Copies bytes, writes them modified).\n"; return 1;}
		for(int a = 0; a < digit_length; a++)
		{	if(in_stream.get(file_byte)) {raw_byte = file_byte & 0xFF; out_stream.put((raw_byte % 10) + 48);}
		}
		in_stream.close();
		out_stream.close();
	}
	in_stream.close();
	
	//Loads seed.
	if(std::filesystem::file_size("rolling-seed") != (unsigned long long)digit_length) {std::cout << "\nBad rolling-seed.\n"; return 1;} //Checks file size.
	in_stream.open("rolling-seed"); if(!in_stream) {std::cout << "\nCan't open file for reading. (Loads seed).\n"; return 1;}            //Opens seed file.
	char seed[50001] = {'\0'}; for(int a = 0; in_stream.get(seed[a]); a++) {} in_stream.close();                                         //Loads seed.
	if(seed[0] == '0') {seed[0] = '5';}                                                                                                  //Forces its length.
	mpz_t in, out; mpz_init(in); mpz_init(out); mpz_set_str(in, seed, 10); mpz_nextprime(out, in); mpz_get_str(seed, 10, out);           //Makes it prime.
	mpz_t prime, two; mpz_init(prime); mpz_init(two); mpz_set_str(prime, seed, 10); mpz_set_ui(two, 2);                                  //Dedicates.
	
	//Generates pseudorandomness.
	std::cout << "\nWriting bytes...\n";
	out_stream.open("pseudorandom_bytes"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Generates pseudorandomness).\n"; return 1;}
	char next_prime[50001] = {'\0'};
	for(long long gap = 2, a = 0; a < generate_bytes;)
	{	mpz_add(prime, prime, two);
		if(mpz_probab_prime_p(prime, 25) == 0) {gap += 2;}
		else
		{	mpz_get_str(next_prime, 10, prime);
			gap *= 10; gap += next_prime[digit_length - 3] - 48;
			gap *= 10; gap += next_prime[digit_length - 2] - 48;
			gap %= 256; out_stream.put(gap);
			gap = 2; a++; std::cout << a << " of " << generate_bytes << "\n";
		}
	}
	out_stream.close();
	
	//Updates seed file.
	std::cout << "Rolling seed...\n";
	out_stream.open("rolling-seed"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Updates seed file).\n"; return 1;}
	for(long long gap = 2, a = 0; a < digit_length;)
	{	mpz_add(prime, prime, two);
		if(mpz_probab_prime_p(prime, 25) == 0) {gap += 2;}
		else
		{	mpz_get_str(next_prime, 10, prime);
			out_stream << next_prime[digit_length - 2];
			gap = 2; a++;
		}
	}
	out_stream.close();
}
