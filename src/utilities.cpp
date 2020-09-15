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
	string str;
	if (file.open(filename)) {}
	else {return COULD_NOT_OPEN_FILE;}

	if (ignoreFirstRow) {
		vec.erase(vec.begin());
	}

	while (!file.eof()) {
		string sub;
		getline(file, sub, CHAR_TO_SEARCH_FOR);
		//cout << sub << endl;
		//Somehow parse stuff here

	}

	vec.push_back(stats);
	file.close();
/*
	if(vec.empty()) {
		return FAIL;
	}
*/
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	//for (int i = 0; i < vec.size(); i++) {
		//for (int j = 0; j < 4; j++) {
			switch(mySortOrder) {
				case CPU_TIME:
					sort(vec.begin(), vec.end(), [](const process_stats ps1, const process_stats ps2){ return ps1.cpu_time < ps2.cpu_time;}); //Think this works?
					break;
				case PROCESS_NUMBER:
					sort(vec.begin(), vec.end(), [](const process_stats ps1, const process_stats ps2){ return ps1.process_number < ps2.process_number;});
					break;
				case START_TIME:
					sort(vec.begin(), vec.end(), [](const process_stats ps1, const process_stats ps2){ return ps1.start_time < ps2.start_time;});
					break;
				case IO_TIME:
					sort(vec.begin(), vec.end(), [](const process_stats ps1, const process_stats ps2){ return ps1.io_time < ps2.io_time;});
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
	return vec.size();
}


