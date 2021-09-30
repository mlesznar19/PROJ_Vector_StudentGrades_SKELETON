#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../includes/constants.h"
#include "../includes/utilities.h"
using namespace std;

//if you are debugging the file must be in the project parent directory
std::string DoubleToString(double Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behaviour, 
//this is a very fragile function
//ex. string a="3";
//    int i = stringToInt(a.c_str()); //i contains 3
//    a="s";
//    i = stringToInt(a.c_str()); //i receives 0
int stringToInt(const char *myString) {
	return atoi(myString);
}

//if myString does not contain a string rep of number returns 0
//this is a very fragile function
//ex. string b="4.5";
//    double d = stringToDouble(b.c_str()); //d receives 4.5
double stringToDouble(const char *myString) {
	return atof(myString);
}

/***
 * Clears allStudentData, Opens file, For each line; parses name, midterm1,midterm2 and an
 * optional finalgrade (if present in file)from that line. Puts this info into a studentData struct,
 * adds this struct to allstudentData vector.
 * NOTE:
 * Ignore empty lines
 * Non empty lines will contain 4 or 5 values to be parsed.
 * the default param separator_char is defined in the header file declaration of readFile ONLY, it is not in the readFile definition.
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds the student data info after it has been read from file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int readFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char) {


	separator_char = KP::SEPERATOR_CHAR;
	//clear the vector
	allstudentData.clear();

	std::string line;
	std::string token;
	KP::studentData myStudentData;
	stringstream ss;
	ifstream myInputFile;

	//opens the file
	myInputFile.open(file.c_str(), ios::in);

	while (!myInputFile.eof()){

		//get a line from the file (name, midterm1, midterm2, possibly final grade
		getline(myInputFile, line);
		ss.str(line);

		myStudentData.clear();

		//get the name
		getline(ss, myStudentData.name, KP::SEPERATOR_CHAR);

		//get midterm1
		getline(ss, token, KP::SEPERATOR_CHAR);
		myStudentData.midterm1 = stringToInt(token.c_str());

		//get midterm2
		getline(ss, token, KP::SEPERATOR_CHAR);
		myStudentData.midterm2 = stringToInt(token.c_str());

		//add the student data to vector
		allstudentData.push_back(myStudentData);
	}
	return KP::SUCCESS;
}

/***
 * Iterates over all students in vector, and averages midterm1 and midterm2 to get the finalgrade
 * @param allstudentData
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData){
	if (allstudentData.size()==0){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}

	for (unsigned long long int i=0; i < allstudentData.size(); i++){
		allstudentData[i].finalgrade = (allstudentData[i].midterm1 + allstudentData[i].midterm2)/2;
	}

	return KP::SUCCESS;
}

/***
 * Opens file, serializes data from allstudentData to file, closes file
 * the default param seperator_char is defined in the header file ONLY
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char) {
	separator_char=KP::SEPERATOR_CHAR;

	ofstream myOutputFile;
	//checks for an empty student data vector
	if (allstudentData.size()==0){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}

	//opens the file to write to
	myOutputFile.open(file.c_str());

	//checks if file cannot open
	if (!myOutputFile.is_open()){
		return KP::COULD_NOT_OPEN_FILE;
	}
	//iterate through allStudentData and write to file (name, mid1, mid2, finalgrade)
	for (unsigned long long int i=0; i < allstudentData.size(); i++){
		myOutputFile << allstudentData[i].name;
		myOutputFile << allstudentData[i].midterm1;
		myOutputFile << allstudentData[i].midterm2;
		myOutputFile << allstudentData[i].finalgrade;
		myOutputFile << "\n";
	}
	return KP::SUCCESS;
}

//sorts studentdata based on SORT_TYPE
/***
 *
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param st - how to sort the vector
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st){

	//checks for an empty student data vector
	if (allstudentData.size()==0){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}



	return KP::SUCCESS;
}

