/// rolling-code - generates random arbitrary-length text                       Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                symmetric with anyone having any same
///                file that you have (used once for seeds.)


/* Version 2.0.1
#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,          Provide any file with at least 1,000 random first Bytes.          ,#
#'        Share it in person, with whom the codes are to be symmetric.        '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/

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
	
	//Creates file "Seeds" if missing.
	in_stream.open("Seeds");
	bool existence_of_file_Seeds = true;
	if(in_stream.fail() == true) {existence_of_file_Seeds = false;}
	in_stream.close();
	
	char garbage_byte;
	if(existence_of_file_Seeds == false)
	{	//..........Gets path to file from user.
		cout << "\nJust this one time, provide any file"
		     << "\nwith at least 1,000 random first Bytes."
		     << "\nDrag & drop it into terminal or enter path:\n";
		
		//..........Gets path then fixes it if drag-n-dropped, regardless of single-quote presence and "enter"
		//..........not being cleared, meaning you can have options before this, where the user presses enter.
		char path_to_file[10000] = {'\0'};
		{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
			cin.getline(path_to_file, 10000);
			if(path_to_file[0] == '\0')
			{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
				cin.getline(path_to_file, 10000);
			}
			if(path_to_file[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
			
			//..........Removes last space in path_to_file[].
			bool existence_of_last_space = false;
			for(int a = 9999; a > 0; a--)
			{	if(path_to_file[a] != '\0')
				{	if(path_to_file[a] == ' ') {path_to_file[a] = '\0'; existence_of_last_space = true;}
					break;
				}
			}
			
			//..........Removes encapsulating single-quotes in path_to_file[].
			bool existence_of_encapsulating_single_quotes = false;
			if(path_to_file[0] == '\'')
			{	for(int a = 0; a < 9999; a++)
				{	path_to_file[a] = path_to_file[a + 1];
					if(path_to_file[a] == '\0') 
					{	if(path_to_file[a - 1] != '\'') {cout << "\nBad path.\n"; return 0;}
						path_to_file[a - 1] = '\0';
						existence_of_encapsulating_single_quotes = true;
						break;
					}
				}
			}
			
			//..........Replaces all "'\''" with "'" in path_to_file[].
			int single_quote_quantity = 0;
			for(int a = 0; a < 10000; a++)
			{	if(path_to_file[a] == '\'') {single_quote_quantity++;}
			}
			
			if((single_quote_quantity                     >    0)
			&& (existence_of_last_space                  == true)
			&& (existence_of_encapsulating_single_quotes == true))
			{	if((single_quote_quantity % 3) != 0) {cout << "\nBad path.\n"; return 0;}
				
				for(int a = 0; a < 9997; a++)
				{	if(path_to_file[a] == '\'')
					{	int temp = (a + 1);
						for(; temp < 9997; temp++)
						{	path_to_file[temp] = path_to_file[temp + 3];
						}
					}
				}
			}
		}
		
		//..........Checks if given file has at least 1,000 Bytes.
		in_stream.open(path_to_file);
		int thousand = 0;
		for(int a = 0; a < 1000; a++)
		{	in_stream.get(garbage_byte);
			if(in_stream.eof() == false) {thousand++;}
		}
		in_stream.close();
		
		if(thousand < 1000) {cout << "\n\nFile too small.\n\n"; return 0;}
		
		//..........Creates file "Seeds" (copies first 1,000 Bytes from given file.)
		in_stream.open(path_to_file);
		out_stream.open("Seeds");
		in_stream.get(garbage_byte);
		for(int a = 0; a < 1000; a++) {out_stream.put(garbage_byte); in_stream.get(garbage_byte);}
		in_stream.close();
		out_stream.close();
	}
	
	//Checks if file "Seeds" contains at least 1,000 Bytes.
	in_stream.open("Seeds");
	int thousand = 0;
	for(int a = 0; a < 1000; a++)
	{	in_stream.get(garbage_byte);
		if(in_stream.eof() == false) {thousand++;}
	}
	in_stream.close();
	
	if(thousand < 1000) {cout << "\n\nBad \"Seeds\" file. (Must be 1,000 Bytes.)\n\n"; return 0;}
	
	//Loads temp_seeds[].
	in_stream.open("Seeds");
	int temp_seeds[1000];
	for(int a = 0; a < 1000; a++)
	{	in_stream.get(garbage_byte);
		int normal_byte = garbage_byte;
		if(normal_byte < 0) {normal_byte += 256;}
		
		temp_seeds[a] = normal_byte;
	}
	in_stream.close();
	
	//Makes proper seeds[] out of temp_seeds[].
	int seeds[1000];
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
	
	
	
	
	
	//Generates code. (6,570-bit seed per generated char.)
	out_stream.open("Code", ios::app);
	long long secondary_seeds[100];
	int table[1001];
	for(int a = 0; a < code_length; a++)
	{	for(int b = 0; b < 1001; b++) {table[b] = 0;}
		
		//..........Uses seeds[].
		for(int b = 0; b < 1000; b++)
		{	srand(seeds[b]);
			
			if(seeds[b] % 2 == 0)
			{	//..........Constructively fills table[] LEFT to right based on seeds[].
				for(int c = 0; c < 1001; c++)
				{	table[c] += rand();
					table[c] %= 95;
				}
			}
			else
			{	//..........Constructively fills table[] RIGHT to left based on seeds[].
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
			{	//..........Constructively fills table[] LEFT to right based on secondary_seeds[].
				for(int c = 0; c < 1001; c++)
				{	table[c] += rand();
					table[c] %= 95;
				}
			}
			else
			{	//..........Constructively fills table[] RIGHT to left based on secondary_seeds[].
				for(int c = 1000; c >= 0; c--)
				{	table[c] += rand();
					table[c] %= 95;
				}
			}
		}
		
		//..........Copies first 1,000 char from table[] to seeds[].
		for(int b = 0; b < 1000; b++) {seeds[b] = table[b];}
		
		//..........Append-writes 1,001st character from table[] to file "Code". (One char at-a-time.)
		out_stream.put(table[1000] + 32);
	}
	out_stream << "\n";
	out_stream.close();
	
	
	
	
	
	//Overwrites file "Seeds" with new seeds.
	out_stream.open("Seeds");
	for(int a = 0; a < 1000; a++) {out_stream.put(seeds[a] + 32);}
	out_stream << "\n\n\n\n\n          PRIVATE!  DO NOT SHARE!"
	           << "\n-------------------------------------------"
	           << "\nThe other party retains this file verbatim."
	           << "\n(Transformed symmetrically here and there.)"
	           << "\n-------------------------------------------\n";
	out_stream.close();
	
	//Overwrites arrays int seeds[1000] and int temp_seeds[1000].
	for(int a = 0; a < 1000; a++)
	{	seeds[a] =  0;
		seeds[a] = -2147483648;
		seeds[a] =  2147483647;
		
		temp_seeds[a] =  0;
		temp_seeds[a] = -2147483648;
		temp_seeds[a] =  2147483647;
	}
	
	//Overwrites array long long secondary_seeds[100].
	for(int a = 0; a < 100; a++)
	{	secondary_seeds[a] =  0;
		secondary_seeds[a] = -9223372036854775807;
		secondary_seeds[a] =  9223372036854775807;
	}
	
	//Overwrites array int table[1001].
	for(int a = 0; a < 1001; a++)
	{	table[a] =  0;
		table[a] = -2147483648;
		table[a] =  2147483647;
	}
	
	cout << "\n" << code_length << " characters appended to file \"Code\"."
	                            << "\nNew seeds overwritten to file \"Seeds\".\n";
}
