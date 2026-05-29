//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
long long generate_bytes = 2000;                                                //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
int        digit_length  = 200; //50 to 50000
//digit_length is the length of a (jumping) value,
//near which prime gaps are found. Bigger = more secure.

/*Version 5.0.1
Writes secure pseudorandom bytes to file based on prime
gaps,  symmetric with whom  you have in common  any file
(used once to make a rolling-seeds file you can alter.)*/

#include <filesystem>
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
	if(in_stream.fail())
	{	cout << "\n(Since digit_length = " << digit_length << ", you'll get a rolling-seeds file containing"
		     << "\na " << digit_length << "-digit value, near which prime gaps are found. Continued gaps are"
		     << "\nthen used for the randomness in changing that value, end of each run.)\n"
		     << "\nBecause digit_length = " << digit_length << ",\njust once, drop/enter any file\nof " << digit_length << "+ random first bytes:\n";
		
		//Gets path, fixes it if dropped.
		string path; getline(cin, path); if(path[0] == '\0') {getline(cin, path);}
		if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();}
		in_stream.open(path); if(in_stream.fail()) {cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
		
		//Checks file size.
		long long size = filesystem::file_size(path);
		if(size < digit_length) {cout << "\nFile too small.\n"; return 1;}
		
		//Copies bytes, writes them modified.
		in_stream.open(path);
		out_stream.open("private_seeds");
		for(int a = 0; a < digit_length; a++)
		{	in_stream.get(file_byte); raw_byte = file_byte;
			if(raw_byte < 0) {raw_byte += 256;} out_stream.put((raw_byte % 10) + 48);
		}
		in_stream.close();
		out_stream.close();
	}
	in_stream.close();
	
	//Loads seeds.
	char seeds[50001] = {'\0'};
	long long size = filesystem::file_size("private_seeds"); if(size != digit_length) {cout << "\nBad private_seeds.\n"; return 1;} //Checks file size.
	in_stream.open("private_seeds"); for(int a = 0; a < digit_length; a++) {in_stream.get(seeds[a]);} in_stream.close();            //Loads value.
	if(seeds[0] == '0') {seeds[0] = '5';}                                                                                           //Forces its length.
	mpz_t in, out; mpz_init(in); mpz_init(out); mpz_set_str(in, seeds, 10); mpz_nextprime(out, in); mpz_get_str(seeds, 10, out);    //Makes it prime.
	mpz_t prime, two; mpz_init(prime); mpz_init(two); mpz_set_str(prime, seeds, 10); mpz_set_ui(two, 2);                            //Dedicates.
	
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
			gap = 2; a++; cout << a << " of " << generate_bytes << "\n";
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
}
