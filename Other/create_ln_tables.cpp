//Run it: "apt install g++ geany libmpfr-dev". Open the .cpp in Geany.
//Append "-lmpfr" to Geany's compile & build commands. Hit F9 once. F5 to run.

#include <fstream>
#include <iostream>
#include <mpfr.h>
using namespace std;
int main()
{	ofstream out_stream;
	
	int precision_in_bits = 100;
	char n[500000] = {"50000000000000000000000000000000000000000000000000"};
	mpfr_t input, result; mpfr_init2(input, precision_in_bits); mpfr_init2(result, precision_in_bits);
	
	int normal_table[49951] = {0};
	int compressed_table[49950] = {0};
	int bookmark = 0;
	
	out_stream.open("normal_table");
	for(int a = 50; a < 50001; a++)
	{	mpfr_set_str(input, n, 10, MPFR_RNDN);
		mpfr_log(result, input, MPFR_RNDN);
		long long ln_n = mpfr_get_d(result, MPFR_RNDN);
		
		cout << a << "-digit: " << ln_n << "\n";
		out_stream << ln_n << "\n";
		normal_table[bookmark] = ln_n; bookmark++;
		
		n[a] = '0';
	}
	out_stream.close();
	
	for(int a = 0; a < 49950; a++) {compressed_table[a] = normal_table[a + 1] - normal_table[a];}
	
	out_stream.open("compressed_table");
	out_stream << "114,";
	for(int a = 0; a < 49950; a++) {out_stream << compressed_table[a] << ",";}
	out_stream.close();
}
