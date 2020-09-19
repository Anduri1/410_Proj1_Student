/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

vector<process_stats> vec;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	try {
		bool ignore = true;
		string line;
		ifstream file(filename);

		if (!file.is_open()) {
			return COULD_NOT_OPEN_FILE;
		}
		vec.clear();
		vector<int> str;
		while (file.peek() != ifstream::traits_type::eof()) {
			if (ignoreFirstRow and ignore) {
					getline(file, line); // Should skip
					ignore = false;
				} else {
					str.clear();
					getline(file, line);
					istringstream sub(line);
					string s;
					while (sub.good()) {
						getline(sub, s, CHAR_TO_SEARCH_FOR);
						if (s == "") {
							continue;
						} else {
							int convert = stringToInt(s.c_str());
							str.push_back(convert);
						}
					}

					if (str.size() < 4) {
						continue;
						//cout << "Corrupt line" << endl;
						} else {
							process_stats stats;
							stats.process_number = str[0];
							stats.start_time = str[1];
							stats.cpu_time = str[2];
							stats.io_time = str[3];

							vec.push_back(stats);
							//str.clear();
							//cout << "Line added" << endl;
						}
				}
		}

		file.close();
		return SUCCESS;
	} catch (fstream::failure& err) { return COULD_NOT_OPEN_FILE;}
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder) {
		case CPU_TIME:
			sort(vec.begin(), vec.end(), [](const process_stats& ps1, const process_stats& ps2){ return ps1.cpu_time < ps2.cpu_time;}); //Think this works?
			break;
		case PROCESS_NUMBER:
			sort(vec.begin(), vec.end(), [](const process_stats& ps1, const process_stats& ps2){ return ps1.process_number < ps2.process_number;});
			break;
		case START_TIME:
			sort(vec.begin(), vec.end(), [](const process_stats& ps1, const process_stats& ps2){ return ps1.start_time < ps2.start_time;});
			break;
		case IO_TIME:
			sort(vec.begin(), vec.end(), [](const process_stats& ps1, const process_stats& ps2){ return ps1.io_time < ps2.io_time;});
			break;
	}
}

process_stats getNext() {
	process_stats myFirst;
	myFirst = vec.front(); //Front is a reference to first vector element
	vec.erase(vec.begin()); //Begin is a pointer to first vector element
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	int x = vec.size();
	return x;
}
