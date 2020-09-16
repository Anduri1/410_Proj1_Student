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
	ifstream file;
	process_stats stats;
	bool ignore = true;
	file.open(filename);
	string line;
	//if (!file) {
		//return COULD_NOT_OPEN_FILE;
	//}
	int ch;
	while ((ch = file.get())) { //!eof() does not work, I think. Also try (ch = file.get()) != EOF ALSO .good()
		//cout << "ENTERED";
		if (ignoreFirstRow and ignore) {
				getline(file, line); // Should skip
				cout << "SKIP :" << line << endl;
				//cout << "Skipped" << endl;
				ignore = false;

			} else {
				vector<int> str;
				// WHY is this being skipped??????? No sense??????
				while(getline(file, line)) {

					cout << "HERE: " << line << endl;
				}
				while (getline(file, line)) {
					if (line == "/n") {
						break;
					}
					cout << "MADE IT";
					istringstream sub(line);
					string s;
					getline(sub, s, CHAR_TO_SEARCH_FOR);
					//Somehow parse stuff here
					int convert = stoi(s);
					cout << "Convert: " << convert;
					str.push_back(convert);
					//cout << str;

				}
				//if (stats.cpu_time == UNINITIALIZED || stats.io_time  == UNINITIALIZED || stats.process_number  == UNINITIALIZED || stats.start_time  == UNINITIALIZED) {
				if (str.size() < 4) {
						cout << "Corrupt line" << endl;
					} else {
						stats.process_number = str[0];
						stats.start_time = str[1];
						stats.cpu_time = str[2];
						stats.io_time = str[3];

						vec.push_back(stats);
						cout << "Line added";
					}
			}
	}
	//cout << "DONE";
	file.close();
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	//for (int i = 0; i < vec.size(); i++) {
		//for (int j = 0; j < 4; j++) {
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
		//}
	//}
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
