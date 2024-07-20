/// rolling-code - generates random text symmetric with whom you                Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                share any same file (used once to set rolling
///                seeds file.) For unique codes no matter the
///                file, set Unix_time_supplement to true.


// Version 3.1.1
#include <fstream>
#include <iostream>
using namespace std;
int main()
{	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  /////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    ////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\      ///////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\        //////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\            ////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\              ///////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\       your       /////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\       controls       ///////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\                              ///////////////////////
	\\\\\\\\\\\\\\\\\\                                        ////////////////*/
	
	long long code_length_in_thousands = 12; //Must be equal with whom codes are to be symmetric. DEFAULT = 12.
	
	bool Unix_time_supplement = false;       //Set to true for codes of unique randomness, even with the same seeds file. DEFAULT = false.
	
	bool absurd_protection_against_cryptanalysis = false; //Slow, code_length_in_thousands becomes "actual code length."  DEFAULT = false.
	
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
			cout << "\nJust once, drop/enter any file"
			     << "\nof 1,000+ random first bytes:\n";
			
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
			if(in_stream.fail() == true) {cout << "\nNo such file.\n"; in_stream.close(); return 0;}
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
	{	long long temp_overflow_for_randomness;
		
		//..........Loads seeds[] with seeds file.
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
		
		//..........Makes 100 10-digit actual seeds based on seeds[]. (Strings together 10 contiguous digits, 100 times.)
		unsigned int actual_seeds[100] = {0};
		int seeds_read_bookmark = 0;
		for(int a = 0; a < 100; a++)
		{	temp_overflow_for_randomness = 0;
			for(int b = 0; b < 10; b++)
			{	temp_overflow_for_randomness += seeds[seeds_read_bookmark];
				if(b < 9) {temp_overflow_for_randomness *= 10;}
				seeds_read_bookmark++;
			}
			
			actual_seeds[a] = (temp_overflow_for_randomness % 4294967296);
		}
		
		//..........Supplements all actual_seeds[] with randomness based on Unix time.
		if(Unix_time_supplement == true)
		{	srand(time(0));
			for(int a = 0; a < 100; a++)
			{	temp_overflow_for_randomness = (rand() % 4294967296);
				temp_overflow_for_randomness += actual_seeds[a];
				actual_seeds[a] = (temp_overflow_for_randomness % 4294967296);
			}
		}
		
		
		
		
		
		//..........Generator house.
		out_stream.open("Code", ios::app);
		unsigned int randomness[1000] = {0};
		for(long long a = 0; a < code_length_in_thousands; a++)
		{	
			//..........Generator powerhouse.
			for(int b = 0; b < 100; b++)
			{	srand(actual_seeds[b]);
				/*#######*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
				#####'`                                                                  `'#####
				###'             You may freely replace the following few items.            '###
				##            Here, randomness is generated  1,000 bytes per round.           ##
				#,         What happens here, must happen 100 times.  For each time,          ,#
				#'        continue scrambling the unsigned int randomness[1000] array.        '#
				##        srand() will use a different seed for you, each time  (100.)        ##
				###,       Leave randomness[] with at least values  0 to 9  when done.      ,###
				#####,.                                                                  .,#####
				##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/
				for(int c = 0; c < 1000; c++) {randomness[c] += rand(); randomness[c] %= 256;} //..........Fills randomness[] (100x per 1,000-char code.)
				temp_overflow_for_randomness = (actual_seeds[99 - b] + rand()); //..........Modifies inverse actual_seeds[].
				actual_seeds[99 - b] = (temp_overflow_for_randomness % 4294967296);
				
				srand(actual_seeds[99 - b]);  //..........Now using that inverse seed.
				for(int c = 0; c < 1000; c++) //..........Swaps EACH & EVERY element in randomness[] with randomly chosen (100,000x per 1,000-char code.)
				{	int random_element = (rand() % 1000);
					for(; random_element == c;) {random_element = (rand() % 1000);}
					
					unsigned int temp_element = randomness[random_element];
					randomness[random_element] = randomness[c];
					randomness[c] = temp_element;
				}
				temp_overflow_for_randomness = (actual_seeds[b] + rand()); //..........Modifies current actual_seeds[].
				actual_seeds[b] = (temp_overflow_for_randomness % 4294967296);
			}
			
			//..........Makes 100 10-digit new actual seeds based on randomness[]. (!!! Adds to current actual_seeds. !!! The generated Code is NOT alone responsible for new actual_seeds. !!!) (Strings together 10 contiguous digits, 100 times.)
			int randomness_read_bookmark = 0;
			for(int b = 0; b < 100; b++)
			{	temp_overflow_for_randomness = 0;
				for(int c = 0; c < 10; c++)
				{	temp_overflow_for_randomness += (randomness[randomness_read_bookmark] % 10);
					if(c < 9) {temp_overflow_for_randomness *= 10;}
					randomness_read_bookmark++;
				}
				
				temp_overflow_for_randomness += actual_seeds[b];
				actual_seeds[b] = (temp_overflow_for_randomness % 4294967296);
			}
			
			if(absurd_protection_against_cryptanalysis == true) {out_stream << char((randomness[500] % 94) + 33);} //..........Writes only 1 code item per round.
			else
			{	/*#######*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
				#####'`                                                                  `'#####
				###'               Append-writes randomness[] to file "Code".               '###
				##                                                                            ##
				#,      Extract rand here!  unsigned int randomness[1000]  here-contains      ,#
				#'      1,000 random values 0 to 255. This array gets all new randomness      '#
				##       every time the program is here. And how many times is it here?       ##
				###,      That's equal to the direct value of code_length_in_thousands.     ,###
				#####,.                                                                  .,#####
				##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/
				for(int b = 0; b < 1000; b++) {out_stream << char((randomness[b] % 94) + 33);}
			}
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
		
		//..........Overwrites RAM of variable long long temp_overflow_for_randomness.
		temp_overflow_for_randomness = 0; temp_overflow_for_randomness = -9223372036854775807; temp_overflow_for_randomness = 9223372036854775807;
		
		//..........Overwrites RAM of arrays unsigned int seeds[1000] and unsigned int randomness[1000].
		for(int a = 0; a < 1000; a++) {seeds[a] = 0; seeds[a] = 4294967295; randomness[a] = 0; randomness[a] = 4294967295;}
		
		//..........Overwrites RAM of array unsigned int actual_seeds[100].
		for(int a = 0; a < 100; a++) {actual_seeds[a] = 0; actual_seeds[a] = 4294967295;}
		
		cout << "\n";
		if(Unix_time_supplement                    == true) {cout << "Random "                      ;}
		if(absurd_protection_against_cryptanalysis == true) {cout << code_length_in_thousands       ;}
		else                                                {cout << code_length_in_thousands * 1000;}
		
		if((absurd_protection_against_cryptanalysis == true) && (code_length_in_thousands == 1)) {cout << " character" ;}
		else                                                                                     {cout << " characters";}
		
		cout << " appended to file \"Code\"."
		     << "\nNew seeds overwritten to file \"RC_seeds\".\n\n\n";
	}
}
