/*
 * constants.h
 *
 *  Created on: Oct 5, 2017
 *      Author: keith
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include <string>
namespace KP {
	const char SEPERATOR_CHAR = ' ';
	
	const int SUCCESS = 0;
	const int USER_CHOSE_TO_EXIT = -1;
	const int COULD_NOT_OPEN_FILE = -2;
	const int VECTOR_CONTAINS_NO_STUDENTS = -3;
	
	const std::string ORIGINAL_STUDENT_DATA = "OrigData.txt";
	const std::string CALCULATED_STUDENT_DATA = "CalcData.txt";
	
	const double UNINITIALIZED = -1.0;
	struct studentData {
		std::string name;
		double midterm1, midterm2;
		double finalgrade;
		void clear() {
			name.clear();
			midterm1 = midterm2 = finalgrade = UNINITIALIZED;
		}
	};
	
	//FINAL_GRADE should go from high to low
	enum SORT_TYPE {
		NAME, FINAL_GRADE
	};
}

#endif /* CONSTANTS_H_ */
