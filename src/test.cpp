//============================================================================
// Name        : testing.cpp
// Author      : KP
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "../includes/constants.h"
#include "../includes/utilities.h"
#include "../includes/test.h"

using namespace std;
using namespace KP;

//tracks how many points you will get out of 100
//yeah, yeah its a global
int total_points =0;

//this is a template class, its mostly here as a helper for me
//the T and U are generic params, I can substitute any type for them
//they must be comparable with ==, templates are extremely hard to get right BTW
template<typename T, typename U>
bool EXPECT_EQ(T expectedVal, U actualVal,string testnumb = "", int pts=1){
	bool bout = (expectedVal == actualVal);
	if (bout){
		total_points+=pts;
		cout<<"SUCCESS test:"+testnumb<<" points:"<<total_points;
	}
	else{
		cout<<"FAIL - expected:"<<expectedVal<<" got:"<<actualVal<<" test:"<<testnumb;
	}
	cout<<endl;
	return bout;
}

void test(){
	string file = "Bogusfile.txt"; 
	vector<KP::studentData> allstudentData;
	
	//fail on bogus file
	int iret=readFile(file,allstudentData);
	
	//detect empty vector
	EXPECT_EQ(KP::COULD_NOT_OPEN_FILE, readFile(file,allstudentData),"1",3);
	EXPECT_EQ(KP::VECTOR_CONTAINS_NO_STUDENTS, calculateFinalGrade(allstudentData),"2",3);
	EXPECT_EQ(KP::VECTOR_CONTAINS_NO_STUDENTS, writeFile(file, allstudentData),"3",3);
	EXPECT_EQ(KP::VECTOR_CONTAINS_NO_STUDENTS, sortStudentData(allstudentData, KP::SORT_TYPE::NAME),"4",3);
	
	//try valid file
	file = ORIGINAL_STUDENT_DATA;	
	EXPECT_EQ(KP::SUCCESS, readFile(file,allstudentData),"5",5);
	EXPECT_EQ(4, allstudentData.size(),"6",5);
	EXPECT_EQ("tailer", allstudentData[0].name,"7");
	EXPECT_EQ(0, allstudentData[0].midterm1,"8");
	EXPECT_EQ(100, allstudentData[0].midterm2,"9");
	EXPECT_EQ(KP::UNINITIALIZED, allstudentData[0].finalgrade,"99",5);

	//calculateFinalGrade
	EXPECT_EQ(KP::SUCCESS,calculateFinalGrade(allstudentData),"10",5);
	EXPECT_EQ(50, allstudentData[0].finalgrade,"11",5);
	EXPECT_EQ(2.5, allstudentData[3].finalgrade,"12",5);
	
	//sort
	EXPECT_EQ(KP::SUCCESS,sortStudentData(allstudentData, KP::SORT_TYPE::NAME),"13",3);
	EXPECT_EQ("ansel", allstudentData[0].name,"14",5);
	EXPECT_EQ("tailer", allstudentData[3].name,"15",5);
	
	EXPECT_EQ(KP::SUCCESS,sortStudentData(allstudentData, KP::SORT_TYPE::FINAL_GRADE),"16",3);
	EXPECT_EQ("henry", allstudentData[0].name,"17",5);
	EXPECT_EQ("brian", allstudentData[3].name,"18",5);
		
	file="bogusdir//bogusfile.txt";
	EXPECT_EQ(KP::COULD_NOT_OPEN_FILE, writeFile(file,allstudentData),"19",5);
	
	file=CALCULATED_STUDENT_DATA;
	EXPECT_EQ(KP::SUCCESS, writeFile(file,allstudentData),"20",5);
	EXPECT_EQ(KP::SUCCESS, readFile(file,allstudentData),"21",5);
	EXPECT_EQ(4, allstudentData.size(),"22",3);
	EXPECT_EQ("henry", allstudentData[0].name,"23",4);	
	EXPECT_EQ(98, allstudentData[0].midterm1,"24",1);
	EXPECT_EQ(100, allstudentData[0].midterm2,"25",1);
	EXPECT_EQ(99, allstudentData[0].finalgrade,"26",5);
}
