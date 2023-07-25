/// rolling-code - generates random arbitrary-length text symmetric with anyone having any same file that
///                you have (file used as seeds and overwritten per roll. 6,570-bit seed per generated char.)
///                Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net)


/*  Version 2.0.0   Place any file named "Seeds" in working directory, it should
contain at least 1,000 random Bytes or characters  (overwrites this file.) Share
this Seeds file securely and in person, with whom the codes are to be symmetric.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Use these codes for symmetric authentication as opposed to  symmetry-independent
authentication of Authorship. Use these codes for Multiway when sharing files.*/

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	//                               user knobs
	
	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  /////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    ////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\      ///////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\        //////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\            ////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\              ///////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                  /////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\                      ///////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\                              ///////////////////////
	\\\\\\\\\\\\\\\\\\                                        ////////////////*/
	
	
	long long code_length = 60;
	
	
	/*////////////////                                        \\\\\\\\\\\\\\\\\\
	///////////////////////                              \\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////                      \\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
	
	ifstream in_stream;
	ofstream out_stream;
	
	//Checks if file Seeds is missing, and contains at least 1kB.
	in_stream.open("Seeds");
	if(in_stream.fail() == true)
	{	cout << "\n\n\nMissing file \"Seeds\". Create it."
		     << "\n(Must contain at least random 1kB.)\n\n";
		
		in_stream.close();
		return 0;
	}
	
	int thousand = 0;
	char garbage_byte;
	in_stream.get(garbage_byte);
	for(; in_stream.eof() == false;)
	{	thousand++;
		in_stream.get(garbage_byte);
	}
	in_stream.close();
	
	if(thousand < 1000) {cout << "\n\n\nFile \"Seeds\" must be at least 1kB.\n\n"; return 0;}
	
	//Loads temp_seeds[].
	int seeds                [1000];
	int temp_seeds           [1000];
	long long secondary_seeds[ 100];
	in_stream.open("Seeds");
	for(int a = 0; a < 1000; a++)
	{	in_stream.get(garbage_byte);
		int normal_byte = garbage_byte;
		if(normal_byte < 0) {normal_byte += 256;}
		
		temp_seeds[a] = normal_byte;
	}
	in_stream.close();
	
	//Makes proper seeds[] out of temp_seeds[].
	for(int a = 0; a < 1000; a++)
	{	srand(temp_seeds[a]);
		
		if(temp_seeds[a] % 2 == 0)
		{	//..........Constructively fills seeds[] LEFT to right based on temp_seeds[].
			for(int b = 0; b < 1000; b++)
			{	seeds[b] += rand();
				seeds[b] %= 95;
			}
		}
		else
		{	//..........Constructively fills seeds[] RIGHT to left based on temp_seeds[].
			for(int b = 999; b >= 0; b--)
			{	seeds[b] += rand();
				seeds[b] %= 95;
			}
		}
	}
	
	//Generates code.
	out_stream.open("Code");
	int table[1001];
	for(int a = 0; a < code_length; a++)
	{	for(int b = 0; b < 1001; b++) {table[b] = 0;}
		
		//..........Uses seeds[].
		for(int b = 0; b < 1000; b++)
		{	srand(seeds[b]);
			
			if(seeds[b] % 2 == 0)
			{	//..........Constructively fills table[] LEFT to right based on seeds.
				for(int c = 0; c < 1001; c++)
				{	table[c] += rand();
					table[c] %= 95;
				}
			}
			else
			{	//..........Constructively fills table[] RIGHT to left based on seeds.
				for(int c = 1000; c >= 0; c--)
				{	table[c] += rand();
					table[c] %= 95;
				}
			}
		}
		
		//..........Creates secondary_seeds[] based on seeds[].
		for(int b = 0; b < 100; b++) {secondary_seeds[b] = 36;}
		int seeds_read_bookmark = 0;
		for(int b = 0; b < 100; b++) //..........Creates 100 (mostly 10-digit) seeds.
		{	for(int c = 0; c < 10; c++)
			{	secondary_seeds[b] *= (seeds[seeds_read_bookmark] + 1);
				secondary_seeds[b] %= 10000000000;
				if(secondary_seeds[b] == 0) {secondary_seeds[b]++;}
				
				seeds_read_bookmark++;
			}
		}
		
		//..........Uses secondary_seeds[].
		for(int b = 0; b < 100; b++)
		{	srand(secondary_seeds[b]);
			
			if(secondary_seeds[b] % 2 == 0)
			{	//..........Constructively fills table[] LEFT to right based on secondary seeds.
				for(int c = 0; c < 1001; c++)
				{	table[c] += rand();
					table[c] %= 95;
				}
			}
			else
			{	//..........Constructively fills table[] RIGHT to left based on secondary seeds.
				for(int c = 1000; c >= 0; c--)
				{	table[c] += rand();
					table[c] %= 95;
				}
			}
		}
		
		//..........Copies first 1,000 char from table[] to seeds[].
		for(int b = 0; b < 1000; b++) {seeds[b] = table[b];}
		
		//..........Writes 1,001st character from table[] to file "Code".
		out_stream.put(table[1000] + 32);
	}
	out_stream.close();
	
	//Overwrites file "Seeds".
	out_stream.open("Seeds");
	for(int a = 0; a < 1000; a++) {out_stream.put(seeds[a] + 32);}
	out_stream << "\n\n\n\n\n          PRIVATE!  DO NOT SHARE!"
	           << "\n-------------------------------------------"
	           << "\nThe other party retains this file verbatim."
	           << "\n(Transformed symmetrically here and there.)"
	           << "\n-------------------------------------------\n";
	out_stream.close();
	
	//Overwrites seeds[] and temp_seeds[].
	for(int a = 0; a < 1000; a++)
	{	seeds[a] =  0;
		seeds[a] = -2147483648;
		seeds[a] =  2147483647;
		
		temp_seeds[a] =  0;
		temp_seeds[a] = -2147483648;
		temp_seeds[a] =  2147483647;
	}
	
	//Overwrites secondary_seeds[].
	for(int a = 0; a < 100; a++)
	{	secondary_seeds[a] =  0;
		secondary_seeds[a] = -9223372036854775807;
		secondary_seeds[a] =  9223372036854775807;
	}
	
	//Overwrites table[].
	for(int a = 0; a < 1001; a++)
	{	table[a] =  0;
		table[a] = -2147483648;
		table[a] =  2147483647;
	}
	
	cout << "\n" << code_length << "-character code now resides in file \"Code\"."
	     << "\nFile \"Seeds\" has been overwritten, keep it safe.\n";
}
