/// rolling-code - generates random text symmetric with                         Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                anyone providing the same file for seeds
///                (used once.) Base for my rand-using repos.


/* Version 3.0.0
#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,         Just once, provide any file of  1,000+ random first bytes.         ,#
#'          Share it in person, with whom codes are to be symmetric.          '#
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
	
	long long code_length_in_thousands = 12;
	
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
	
	//Creates seeds file if missing.
	const char seeds_file_name[50] = {"RC_seeds"};
	char garbage_byte_for_seeds_file;
	{	//..........Checks if seeds file exists.
		in_stream.open(seeds_file_name);
		bool existence_of_seeds_file = true;
		if(in_stream.fail() == true) {existence_of_seeds_file = false;}
		in_stream.close();
		
		if(existence_of_seeds_file == false)
		{	//..........Gets path to file from user.
			cout << "\nJust once, provide any file"
			     << "\nof 1,000+ random first bytes."
			     << "\nDrag & drop it or enter path:\n";
			
			//..........Gets path then fixes it if drag-n-dropped, regardless of single-quote presence and "enter"
			//..........not being cleared, meaning you can have options before this, where the user presses enter.
			char path_to_file_for_seeds[10000] = {'\0'};
			{	for(int a = 0; a < 10000; a++) {path_to_file_for_seeds[a] = '\0';}
				cin.getline(path_to_file_for_seeds, 10000);
				if(path_to_file_for_seeds[0] == '\0')
				{	for(int a = 0; a < 10000; a++) {path_to_file_for_seeds[a] = '\0';}
					cin.getline(path_to_file_for_seeds, 10000);
				}
				if(path_to_file_for_seeds[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
				
				//..........Removes last space in path_to_file_for_seeds[].
				bool existence_of_last_space = false;
				for(int a = 9999; a > 0; a--)
				{	if(path_to_file_for_seeds[a] != '\0')
					{	if(path_to_file_for_seeds[a] == ' ') {path_to_file_for_seeds[a] = '\0'; existence_of_last_space = true;}
						break;
					}
				}
				
				//..........Removes encapsulating single-quotes in path_to_file_for_seeds[].
				bool existence_of_encapsulating_single_quotes = false;
				if(path_to_file_for_seeds[0] == '\'')
				{	for(int a = 0; a < 9999; a++)
					{	path_to_file_for_seeds[a] = path_to_file_for_seeds[a + 1];
						if(path_to_file_for_seeds[a] == '\0') 
						{	if(path_to_file_for_seeds[a - 1] != '\'') {cout << "\nBad path.\n"; return 0;}
							path_to_file_for_seeds[a - 1] = '\0';
							existence_of_encapsulating_single_quotes = true;
							break;
						}
					}
				}
				
				//..........Replaces all "'\''" with "'" in path_to_file_for_seeds[].
				int single_quote_quantity = 0;
				for(int a = 0; a < 10000; a++)
				{	if(path_to_file_for_seeds[a] == '\'') {single_quote_quantity++;}
				}
				
				if((single_quote_quantity                     >    0)
				&& (existence_of_last_space                  == true)
				&& (existence_of_encapsulating_single_quotes == true))
				{	if((single_quote_quantity % 3) != 0) {cout << "\nBad path.\n"; return 0;}
					
					for(int a = 0; a < 9997; a++)
					{	if(path_to_file_for_seeds[a] == '\'')
						{	int temp = (a + 1);
							for(; temp < 9997; temp++)
							{	path_to_file_for_seeds[temp] = path_to_file_for_seeds[temp + 3];
							}
						}
					}
				}
			}
			
			//..........Loads seeds[] with given file's 1,000 Bytes.
			in_stream.open(path_to_file_for_seeds);
			unsigned int seeds[1000];
			for(int a = 0; a < 1000; a++)
			{	in_stream.get(garbage_byte_for_seeds_file);
				if(in_stream.eof() == true)
				{	for(int b = 0; b < 1000; b++) {seeds[b] = 0; seeds[b] = 4294967295;} //..........Overwrites RAM of array unsigned int seeds[1000].
					cout << "\n\nFile too small.\n\n"; in_stream.close(); return 0;
				}
				
				int normal_byte = garbage_byte_for_seeds_file;
				if(normal_byte < 0) {normal_byte += 256;}
				seeds[a] = normal_byte;
			}
			in_stream.close();
			
			//..........Creates seeds file (digits, and better distributed.)
			out_stream.open(seeds_file_name);
			srand(seeds[0]);
			for(int a = 0; a < 1000; a++)
			{	long long temp = ((seeds[a] + rand()) % 10);
				out_stream << char(temp + 48);
			}
			out_stream << "\n\n\n\nPRIVATE! DO NOT SHARE!\n";
			out_stream.close();
			
			//..........Overwrites RAM of array unsigned int seeds[1000].
			for(int a = 0; a < 1000; a++) {seeds[a] = 0; seeds[a] = 4294967295;}
		}
	}
	
	
	
	
	
	//Generates randomness.
	{	//..........Loads seeds[] with seeds file.
		in_stream.open(seeds_file_name);
		unsigned int seeds[1000];
		for(int a = 0; a < 1000; a++)
		{	in_stream.get(garbage_byte_for_seeds_file);
			int normal_byte = garbage_byte_for_seeds_file;
			if(normal_byte < 0) {normal_byte += 256;}
			seeds[a] = normal_byte;
			
			seeds[a] -= 48;
			if((in_stream.eof() == true) || (seeds[a] > 9))
			{	for(int b = 0; b < 1000; b++) {seeds[b] = 0; seeds[b] = 4294967295;} //..........Overwrites RAM of array unsigned int seeds[1000].
				cout << "\n\nBad seeds file.\n\n"; in_stream.close(); return 0;
			}
		}
		in_stream.close();
		
		//..........Makes 100 10-digit actual seeds based on seeds[].
		long long    overflow    [100] = {0};
		unsigned int actual_seeds[100] = {0};
		int seeds_read_bookmark = 0;
		for(int a = 0; a < 100; a++)
		{	for(int b = 0; b < 10; b++)
			{	overflow[a] += seeds[seeds_read_bookmark];
				if(b < 9) {overflow[a] *= 10;}
				seeds_read_bookmark++;
			}
			
			overflow[a] %= 4294967296;
			actual_seeds[a] = overflow[a];
		}
		
		
		
		
		
		/*####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*######
		##'                                         '##
		#                  Randomness                 #
		#                     core                    #
		##,                                         ,##
		####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/
		out_stream.open("Code", ios::app);
		unsigned int randomness[1000] = {0};
		for(long long a = 0; a < code_length_in_thousands; a++)
		{	for(int b = 0; b < 100; b++)
			{	srand(actual_seeds[b]);
				
				for(int c = 0; c < 1000; c++) {randomness[c] += rand(); randomness[c] %= 256;} //..........rand() for randomness[].
				
				for(int c = 0; c < 100; c++) //..........Swaps 100 pairs of elements in randomness[]. (10,000 swaps total for each 1,000-char Code.)
				{	int element_1 = (rand() % 1000);
					int element_2 = (rand() % 1000);
					unsigned int temp_element = randomness[element_1];
					randomness[element_1] = randomness[element_2];
					randomness[element_2] = temp_element;
				}
			}
			
			//..........Makes 100 10-digit new actual seeds based on randomness[]. (!!! Adds to current actual_seeds. !!! The generated Code is NOT alone responsible for new actual_seeds. !!!)
			for(int b = 0; b < 100; b++) {overflow[b] = 0;}
			int randomness_read_bookmark = 0;
			for(int b = 0; b < 100; b++)
			{	for(int c = 0; c < 10; c++)
				{	overflow[b] += (randomness[randomness_read_bookmark] % 10);
					if(c < 9) {overflow[b] *= 10;}
					randomness_read_bookmark++;
				}
				
				overflow[b] += actual_seeds[b]; //..........(!!! See the addition? !!!)
				overflow[b] %= 4294967296;
				actual_seeds[b] = overflow[b];
			}
			
			//..........Append-writes randomness[] to file "Code".
			for(int b = 0; b < 1000; b++) {out_stream << char((randomness[b] % 94) + 33);}
		}
		out_stream << "\n";
		out_stream.close();
		
		
		
		
		
		//..........Overwrites seeds file.
		out_stream.open(seeds_file_name);
		for(int a = 0; a < 100; a++)
		{	unsigned int place = 10;
			for(int b = 0; b < 9; b++)
			{	if(actual_seeds[a] < place) {out_stream << "0";}
				place *= 10;
			}
			out_stream << actual_seeds[a];
		}
		out_stream << "\n\n\n\nPRIVATE! DO NOT SHARE!\n";
		out_stream.close();
		
		//..........Overwrites RAM of arrays unsigned int seeds[1000] and unsigned int randomness[1000].
		for(int a = 0; a < 1000; a++) {seeds[a] = 0; seeds[a] = 4294967295; randomness[a] = 0; randomness[a] = 4294967295;}
		
		//..........Overwrites RAM of array long long overflow[100].
		for(int a = 0; a < 100; a++) {overflow[a] = 0; overflow[a] = -9223372036854775807; overflow[a] = 9223372036854775807;}
		
		//..........Overwrites RAM of array unsigned int actual_seeds[100].
		for(int a = 0; a < 100; a++) {actual_seeds[a] = 0; actual_seeds[a] = 4294967295;}
		
		cout << "\n" << (code_length_in_thousands * 1000) << " characters appended to file \"Code\"."
		                                                  << "\nNew seeds overwritten to file \"RC_seeds\".\n";
	}
}
