#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define NUMBER_OF_TIMES_CHAR_FIRST_PRINT 20//const variable for printing
#define NUMBER_OF_GROUPS 3//const variable for number of groups
#define NUMBER_OF_STUDENTS_EACH_GROUP 6//const variable for number of students each group
#define MAX_NAME_LEN 30//const variable for maximun name length
#define MAX_FULL_NAME_LEN 30//const variable for maximun name length
#define MAX_COURSES 10//const variable for maximun courses amount
#define NUMBER_OF_MINUS 32//const variable for printing
#define GROUP_STUDENT_NUMBER 6//const variable for maximun students in group
#define GROUP_NAME_LENGTH 7//const variable for group name length
#define WHICH_NAME_TO_PUT_IN "Lane"//const variable for which name to put in 
#define WHICH_NAME_TO_CHECK "Lois"//const variable for which name to search
#define WHAT_TO_DELETE "Lex"//const variable for which name to delete
#define SPACE_STRING " "//const variable for space
#define SPACE_CHAR ' '//const variable for space
#define SPACE_STRING_LEN 1 //const variable for char(space) length
#define NOT_INSIDE -1//const variable for indicator that the char is not inside
#define END_OF_STRING '\0'//const variable for indicator of end of string
#define FIRST_CELL 0//const variable for index indicator of string start
#define NOT_STUDING_IT_CODE -1//const variable for indicating that the student does not studies this course
#define NAME_MAX_CHARACTERS 10//const variable for maximun name length
#define GROUP_A_NAME "GroupA"//const variable for groups names
#define GROUP_B_NAME "GroupB"//const variable for groups names
#define GROUP_C_NAME "GroupC"//const variable for groups names
#define GROUP_A_NAME_WITH_SPACE "GroupA "//const variable for groups names(with space at the end)
#define GROUP_B_NAME_WITH_SPACE "GroupB "//const variable for groups names(with space at the end)
#define GROUP_C_NAME_WITH_SPACE "GroupC "//const variable for groups names(with space at the end)

typedef struct CourseInfo
{
	//The following struct defines what course includes :
	//Course's number
	//Course's grade
	int courseNum;
	int grade;
} COURSE_INFO;

typedef struct Student
{
	//The following struct defines what student includes :
	//Student's name
	//Student's ID
	//Student's number of course he studies
	//Student's array of courses he studies
	char name[MAX_NAME_LEN];
	int identity;
	int nofCourses; //number of courses taken in semesterA
	COURSE_INFO course_info[MAX_COURSES];
} STUDENT;


void printingTheSecondBestGrade(int gradesArray[][NUMBER_OF_STUDENTS_EACH_GROUP + 1],int courseNum);
int checkGradeIfStuding(STUDENT student, int courseNum);
void matrixByCourseNum(STUDENT studentArray[][NUMBER_OF_STUDENTS_EACH_GROUP], int courseNum, int gradesArray[][NUMBER_OF_STUDENTS_EACH_GROUP + 1]);
void deleteLineFromArray(char names[][MAX_FULL_NAME_LEN], int whichLine, int howManyNames);
void deleteFromArray(char names[][MAX_FULL_NAME_LEN], int howManyNames, char whatToCheck[]);
int checkIfInside(char name[], char whatToCheck[]);
void deleteFromFullName(char name[], char whatToDelete[]);
void deleteWord(char name[], char whatToDelete[]);
void changeNameToWord(char name[], int k, int wordLen, char word[]);
bool compareString(char name[], int k, int wordLen, char word[]);
void changingNameToNewName(char name[], char word[]);
void onlyLastName(char name[], char lastName[]);
void onlyFirstName(char name[], char firstName[]);
void onlyGroupName(char name[], char groupName[]);
void splitName(char name[]);
void printArrayOfStudentsInCourses(char stuNames[][MAX_FULL_NAME_LEN], int size, int courseNum);
void pushToString(char groupNnmber[], char name[], char stuNames[]);
void pushToStuNames(char stuNames[], STUDENT stuData, int numOfGroup);
bool isHeStudingIt(STUDENT student, int courseNum);
int getStudentNames(STUDENT stuData[][GROUP_STUDENT_NUMBER], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN]);
STUDENT gettingCourses(STUDENT student);
void putLastCellZero(char array[]);
void getStudent(STUDENT studentArray[], int size);
void getGroupA(STUDENT studentArray[], int size);
void getGroupB(STUDENT studentArray[], int size);
void getGroupC(STUDENT studentArray[], int size);
int getCourseNum();
void printLine(char ch, int num);
void changeLoisToLane(char namesArray[][MAX_FULL_NAME_LEN], int howManyNames);
void printStringArray(char studingCourseNames[][MAX_FULL_NAME_LEN], int howManyStuding);
void printCourseNumMatrix(int gradesArray[][NUMBER_OF_STUDENTS_EACH_GROUP + 1], int courseNum);
void welcome();

//The following program gets 3 groups of students and courses and outputting who is studing this specific course(prints by group).
//The program also changes (from the list of students that studies this specific course) every time it sees the "WHICH_NAME_TO_CHECK" to "WHICH_NAME_TO_PUT_IN".
//The program also deletes lines (from the list of students that studies this specific course) that the student's name contains "WHAT_TO_DELETE".
//The program also outputs the best and the second best grades for this specific course(prints by group).

void main()
{
	welcome();
	STUDENT studentsArray[NUMBER_OF_GROUPS][NUMBER_OF_STUDENTS_EACH_GROUP];//creating students matrix
	getGroupA(studentsArray[0], NUMBER_OF_STUDENTS_EACH_GROUP);//getting specific group details
	getGroupB(studentsArray[1], NUMBER_OF_STUDENTS_EACH_GROUP);//getting specific group details
	getGroupC(studentsArray[2], NUMBER_OF_STUDENTS_EACH_GROUP);//getting specific group details
	char studingCourseNames[NUMBER_OF_STUDENTS_EACH_GROUP * NUMBER_OF_GROUPS][MAX_FULL_NAME_LEN];//creating students names matrix for who actually studies this specific course
	int courseNum;
	printf("\n");
	courseNum = getCourseNum();//getting the course number
	int howManyStuding = getStudentNames(studentsArray, NUMBER_OF_GROUPS, NUMBER_OF_STUDENTS_EACH_GROUP, courseNum, studingCourseNames);//getting how many students are studing this specific course and updating the other matrix with their details
	changeLoisToLane(studingCourseNames, howManyStuding);//changing each time we sees the "WHICH_NAME_TO_CHECK" to "WHICH_NAME_TO_PUT_IN"
	printf("\n");
	printf("Names after changing \"%s\" to \"%s\": ",WHICH_NAME_TO_CHECK,WHICH_NAME_TO_PUT_IN);//printing the matrix after "changeLoisToLane"
	printStringArray(studingCourseNames, howManyStuding);//printing the matrix after "changeLoisToLane"
	deleteFromArray(studingCourseNames, howManyStuding, WHAT_TO_DELETE);//deleting lines that the student's name contains "WHAT_TO_DELETE"
	printf("\n");
	printf("Names after deleting names with \"%s\":", WHAT_TO_DELETE);//printing the matrix after "deleteFromArray"
	printStringArray(studingCourseNames, howManyStuding);//printing the matrix after "deleteFromArray"
	int gradesArray[NUMBER_OF_GROUPS][NUMBER_OF_STUDENTS_EACH_GROUP+1];//creating matrix of grades for the specific course(by groups)
	matrixByCourseNum(studentsArray, courseNum, gradesArray);//updating the matrix of grades for the specific course
	printCourseNumMatrix(gradesArray, courseNum);//printing the course grades matrix
	printingTheSecondBestGrade(gradesArray,courseNum);//printing the best and the second best grades for each group(for the specific course)

}

//The following function gets an array of grades(int) and prints it
void printCourseNumMatrix(int gradesArray[][NUMBER_OF_STUDENTS_EACH_GROUP + 1],int courseNum)
{	
	printf("Grades in course#%d:\n", courseNum);
	int k;
	for (k = 0;k < NUMBER_OF_GROUPS;k++)
	{
		switch (k)//checking which group we are
		{
		case 0:
			printf("%s:",GROUP_A_NAME);
			break;
		case 1:
			printf("%s:", GROUP_B_NAME);
			break;
		case 2:
			printf("%s:", GROUP_C_NAME);
			break;
		default:
			break;
		}
		int howManyStudents = gradesArray[k][0];//number of students that actually studies this course
		int i;//indicator for where we're on the matrix
		for (i = 1;i < howManyStudents+1;i++)
		{
			printf(" %d", gradesArray[k][i]);
		}
		printf("\n");
	}
}
//The following function gets array of strings and prints it
void printStringArray(char studingCourseNames[][MAX_FULL_NAME_LEN], int howManyStuding)
{
	printf("\n");
	int k;
	for (k = 0;k < howManyStuding;k++)
	{
		printf("%s\n", studingCourseNames[k]);
	}

}

/*The following function gets a matrix of grades(by group) of a specific course -
the matrix contains on the first cell each collum the number of students that studing this course.
The function will return for each group the second best grade in class.
If the group has less than 2 students the function will print a proper answer(0/1 students)*/
void printingTheSecondBestGrade(int gradesArray[][NUMBER_OF_STUDENTS_EACH_GROUP + 1], int courseNum)
{
	printf("\nMaximum grades in course#%d:\n", courseNum);
	int bestGradeInGroup, secondBestGradeInGroup;
	int k, j;
	for (k = 0;k < NUMBER_OF_GROUPS;k++)
	{
		if (gradesArray[k][0] == 0)
		{
			//there is not student that student studies it
		}
		else//maybe someone actually studies it
		{
			if (gradesArray[k][0] == 1)
			{
				//only 1 student studies it
				bestGradeInGroup = gradesArray[k][1];
			}
			else//that's means that there is at least 2 students that studing this course 
			{
				if (gradesArray[k][1] > gradesArray[k][2])//checkes who is bigger first cell or second
				{
					bestGradeInGroup = gradesArray[k][1];
					secondBestGradeInGroup = gradesArray[k][2];
				}
				else
				{
					bestGradeInGroup = gradesArray[k][2];
					secondBestGradeInGroup = gradesArray[k][1];
				}
			}
		}

		for (j = 3; j < gradesArray[k][0] + 1; j++)//starting from fourth cell because we checked the first 2 cells
		{
			if (gradesArray[k][j] >= bestGradeInGroup)//checking if it is the biggest
			{
				if (gradesArray[k][j] == bestGradeInGroup)//checking if the second biggest is equal to the best grade
				{
					secondBestGradeInGroup = gradesArray[k][j];
				}
				else
				{
					secondBestGradeInGroup = bestGradeInGroup;
					bestGradeInGroup = gradesArray[k][j];
				}
			}
			if (gradesArray[k][j] < bestGradeInGroup && gradesArray[k][j] > secondBestGradeInGroup)//checking if it is the second biggest
			{
				secondBestGradeInGroup = gradesArray[k][j];
			}
		}
		if (gradesArray[k][0] >= 2)//if at least 2 students studies this course
		{
			switch (k)
			{
			case 0:
				printf("%s: max grade is: %d and second max is: %d\n", GROUP_A_NAME,bestGradeInGroup, secondBestGradeInGroup);
				break;
			case 1:
				printf("%s: max grade is: %d and second max is: %d\n", GROUP_B_NAME,bestGradeInGroup, secondBestGradeInGroup);
				break;
			case 2:
				printf("%s: max grade is: %d and second max is: %d", GROUP_C_NAME, bestGradeInGroup, secondBestGradeInGroup);
				break;
			default:
				break;
			}
		}
		else
		{
			if (gradesArray[k][0] == 0)//checking if no one studies it
			{
				switch (k)
				{
				case 0:
					printf("%s: no grades found in group\n", GROUP_A_NAME);
					break;
				case 1:
					printf("%s: no grades found in group\n", GROUP_B_NAME);
					break;
				case 2:
					printf("%s: no grades found in group", GROUP_C_NAME);
					break;
				default:
					break;
				}
			}
			else
			{
				if (gradesArray[k][0] == 1)//checking if only 1 student studies it
				{
					switch (k)
					{
					case 0:
						printf("%s: max grade is: %d (no second max found)\n", GROUP_A_NAME, bestGradeInGroup);
						break;
					case 1:
						printf("%s: max grade is: %d (no second max found)\n", GROUP_B_NAME, bestGradeInGroup);
						break;
					case 2:
						printf("%s: max grade is: %d (no second max found)", GROUP_C_NAME, bestGradeInGroup);
						break;
					default:
						break;
					}
				}

			}

		}


	}
}

//The following fucntion gets a student and a course num and returns the grade if the student studies the course num, otherwise return -1
int checkGradeIfStuding(STUDENT student, int courseNum)
{
	int k;
	for (k = 0; k < student.nofCourses; k++)
	{
		if (student.course_info[k].courseNum == courseNum)//checking if the student studies this specific course
		{
			return student.course_info[k].grade;//if the student studies this course return his grade
		}
	}
	return NOT_STUDING_IT_CODE;
}


/*The following function gets an matrix of students, course number and empty (int)matrix
 the function will update the empty matrix with the number of students that studing this course(by group)
 and the num grades of each student from the group*/
void matrixByCourseNum(STUDENT studentArray[][NUMBER_OF_STUDENTS_EACH_GROUP], int courseNum, int gradesArray[][NUMBER_OF_STUDENTS_EACH_GROUP + 1])
{
	int k, j;
	int counter = 0;
	for (k = 0;k < NUMBER_OF_GROUPS;k++)
	{
		for (j = 0; j < NUMBER_OF_STUDENTS_EACH_GROUP; j++)
		{
			int grade = checkGradeIfStuding(studentArray[k][j], courseNum);
			if (grade != NOT_STUDING_IT_CODE)
			{
				gradesArray[k][counter + 1] = grade;//if the student studies this course enter his grade to the array
				counter++;//if the student studies this course increase the counter
				
			}
		}
		gradesArray[k][0] = counter;//enter the students counter to the firse cell in the row(as the demand)
		counter = 0;//change the counter to 0 becuase we're getting a new group

	}


}

//The following function gets an array of names(with size) and which line to delete and deletes it
void deleteLineFromArray(char names[][MAX_FULL_NAME_LEN], int whichLine, int howManyNames)
{
	int k;
	if (whichLine + 1 != howManyNames)//checking if the line is the last one
	{
		//taking the lower rows and copying them instead of this one
		for (k = whichLine; k < howManyNames; k++)
		{
			strcpy(names[k], names[k + 1]);//deleting the whole line by coping the next line on it
		}
		//avoiding copy of names by putting on the last line in the array '\0' instead of the first cell
		names[k][FIRST_CELL] = END_OF_STRING;
	}
	else//if it is the last line in the array - just put '\0' instead of the first cell
	{
		names[whichLine][FIRST_CELL] = END_OF_STRING;
	}
}

//The following function gets an array of names(with size) + name to check and deletes from the array all the names that contains it
void deleteFromArray(char names[][MAX_FULL_NAME_LEN], int howManyNames, char whatToCheck[])
{
	int k = 0;
	int howManyDeleted = 0;
	int indexFirstName, indexLastName;
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	
	/*the loop will end when the counter of the those who has the name +
	the counter of those who doesn't has the name will be the amount of names in the array*/
	while (k + howManyDeleted != howManyNames)
	{
		onlyLastName(names[k], lastName);
		onlyFirstName(names[k], firstName);
		indexFirstName = checkIfInside(firstName, whatToCheck);//checking if the first name has it 
		indexLastName = checkIfInside(lastName, whatToCheck);//checking if the last name has it 
		
		if (indexFirstName !=NOT_INSIDE|| indexLastName != NOT_INSIDE)
		{
			deleteLineFromArray(names, k, howManyNames);
			howManyDeleted++;//promoting howManyDeleted already
		}
		else//if not inside - continue to next name
		{
			k++;
		}

	}

}

//The following function gets a string "name" and string "whatToCheck" and if it's inside "name" returns the index of the first letter, if not returns -1 
int checkIfInside(char name[], char whatToCheck[])
{
	int size = strlen(name);
	int k;
	int whatToCheckLen = strlen(whatToCheck);
	for (k = 0; k < size; k++)
	{
		if (name[k] == whatToCheck[0])//if the first letter inside - check if the word is inside
		{
			if (k + whatToCheckLen <= size)//checking if we're not going out of the string
			{
				if (compareString(name, k, whatToCheckLen, whatToCheck))//checking only wordLen of the name to compare
				{
					return k;
				}
			}
		}
	}
	return NOT_INSIDE;
}

//The following function gets a full name and string of whatToDelete and deletes it from the full name
void deleteFromFullName(char name[], char whatToDelete[])
{
	char groupName[MAX_NAME_LEN];//srting of only group name
	onlyGroupName(name, groupName);//putting group name into groupName 
	char firstName[MAX_NAME_LEN];//srting of only first name
	onlyFirstName(name, firstName);//putting first name into firstName 
	char lastName[MAX_NAME_LEN];//srting of only last name
	onlyLastName(name, lastName);//putting name into lastName
	deleteWord(groupName, whatToDelete);//deleting word from string
	deleteWord(firstName, whatToDelete);//deleting word from string
	deleteWord(lastName, whatToDelete);//deleting word from string
	strcat(groupName, SPACE_STRING);//combining back the updated name with spaces
	strcat(groupName, firstName);
	strcat(groupName, SPACE_STRING);
	strcat(groupName, lastName);
	strcpy(name, groupName);//coping the new updated array to the old array
}

//The following function gets a string "name" and string "whatToDelete" and deletes it from "name"
void deleteWord(char name[], char whatToDelete[])
{
	int index = checkIfInside(name, whatToDelete);
	if (index != NOT_INSIDE)//checking if the specific word is inside
	{//if the word is inside - delete it
		int nameLen = strlen(name);//getting the length of the name we want to check if the word is inside
		int whatToDeleteLen = strlen(whatToDelete);//getting the length of the word we want to delete
		if (index + 1 + whatToDeleteLen == nameLen)//checking that we're not getting to the end of the string
		{
			name[index] = END_OF_STRING;
		}
		else
		{
			int k;
			for (k = index; k < nameLen; k++)
			{
				name[k] = name[k + whatToDeleteLen];//getting the front cells instead of the current cell(the cells with whatToDelete)
			}
		}
	}
}

//The following function replacing cells in name from word in range of k to k+wordLen 
void changeNameToWord(char name[], int k, int wordLen, char word[])
{
	int i;
	for (i = 0; i < wordLen; i++)
	{
		name[k + i] = word[i];//chagning each cell from name to the one we want 
	}
}
//The following function checking if there is a word inside name from k to k+wordLen
bool compareString(char name[], int k, int wordLen, char word[])
{
	int i;
	for (i = 0; i < wordLen; i++)
	{
		if (name[k + i] != word[i])
		{
			return false;//if even 1 character is not the same - return false
		}
	}
	return true;
}
//The follwing function checking if "word" is inside "name" and putting "word" instead 
void changingNameToNewName(char name[], char word[])
{
	int size = strlen(name);
	int k;
	int wordLen = strlen(word);
	for (k = 0; k < size; k++)
	{
		if (name[k] == word[0])//if the first letter inside - check if the word is inside
		{
			if (k + wordLen <= size)//checking if we're not going out of the string
			{
				if (compareString(name, k, wordLen, word))//checking only wordLen of the name to compare
				{
					changeNameToWord(name, k, wordLen, WHICH_NAME_TO_PUT_IN);//changing name to word
				}
			}
		}
	}
}

//The following function gets full name and putting last name into another array
void onlyLastName(char name[], char lastName[])
{
	int numOfSpaces = 0;
	int k;
	for (k = 0; numOfSpaces < 2; k++)//we are jumping over the 2 first spaces and getting only the last name
	{
		if (name[k] == SPACE_CHAR)
			numOfSpaces++;
	}
	int i = 0;
	while (name[k] != END_OF_STRING)
	{
		lastName[i] = name[k];
		i++;
		k++;
	}
	lastName[i] = END_OF_STRING;//putting \0 at the end of the string
}


//The following function gets full name and putting first name into another array
void onlyFirstName(char name[], char firstName[])
{
	int numOfSpaces = 0;
	int k;
	for (k = 0; numOfSpaces < 1; k++)//we are jumping over the first space and getting only the first name
	{
		if (name[k] == SPACE_CHAR)
		{
			numOfSpaces++;
		}
	}
	int i;
	for (i = 0; numOfSpaces < 2; i++)//we are stopping to get the first name when we're finding the second space
	{
		if (name[k + i] == SPACE_CHAR)
		{
			numOfSpaces++;
		}
		else
		{
			firstName[i] = name[k + i];
		}

	}
	firstName[i - 1] = END_OF_STRING;//putting \0 at the end of the string

}

//The following function gets full name and putting group name into another array
void onlyGroupName(char name[], char groupName[])
{

	int numOfSpaces = 0;
	int k;
	for (k = 0; numOfSpaces < 1; k++)//we are getting only the group name by stopping at the first space
	{
		groupName[k] = name[k];
		if (name[k] == SPACE_CHAR)
		{
			numOfSpaces++;
		}
	}
	groupName[k - 1] = END_OF_STRING;//putting \0 at the end of the string
	return;
}
//The following function gets an matrix of names and updating wherever there is the name "Lois" to "Lane"
void changeLoisToLane(char namesArray[][MAX_FULL_NAME_LEN], int howManyNames)
{
	int k;
	for (k = 0; k < howManyNames; k++)
	{
		splitName(namesArray[k]);
	}

}

//The following function gets a string and changing each time the name "Lois" is appeared to "Lane"
void splitName(char name[])
{
	char groupName[GROUP_NAME_LENGTH];//srting of only group name
	onlyGroupName(name, groupName);//putting group name into groupName 
	char firstName[NAME_MAX_CHARACTERS];//srting of only first name
	onlyFirstName(name, firstName);//putting first name into firstName 
	changingNameToNewName(firstName, WHICH_NAME_TO_CHECK);//changing name to newName(if it's in)
	char lastName[NAME_MAX_CHARACTERS];//srting of only last name
	onlyLastName(name, lastName);//putting name into lastName
	changingNameToNewName(lastName, WHICH_NAME_TO_CHECK);//changing name to newName(if it's in)
	char fullName[MAX_FULL_NAME_LEN];
	strcpy(fullName, groupName);
	strcat(fullName, SPACE_STRING);//combining back the updated name
	strcat(fullName, firstName);
	strcat(fullName, SPACE_STRING);
	strcat(fullName, lastName);
	strcpy(name, fullName);//coping the new updated array to the old array

}


//The following function gets an array of names and course num they all went and prints their names 
void printArrayOfStudentsInCourses(char stuNames[][MAX_FULL_NAME_LEN], int size, int courseNum)
{
	printf("Names of students in course#%d:\n", courseNum);//printing all students in the specific course
	int k;
	for (k = 0; k < size; k++)
	{
		printf("%s\n", stuNames[k]);
	}
}

//The following function gets an arrays of group name + name and insters it into stuNames
void pushToString(char groupNnmber[], char name[], char stuNames[])
{
	int k;
	for (k = 0; k < GROUP_NAME_LENGTH; k++)//running on the group name 
	{
		stuNames[k] = groupNnmber[k];
	}
	for (k = 0; k < MAX_NAME_LEN; k++)//running on the name 
	{
		stuNames[k + GROUP_NAME_LENGTH] = name[k];
	}
	stuNames[MAX_FULL_NAME_LEN] = END_OF_STRING;/*putting \0 to finish string*/
}

//The following function gets an array of strings and a student and puts it inside by the group number
void pushToStuNames(char stuNames[], STUDENT stuData, int numOfGroup)
{
	switch (numOfGroup + 1)//adding the group's name to the full name
	{
	case 1:
		pushToString(GROUP_A_NAME_WITH_SPACE, stuData.name, stuNames);
		break;
	case 2:
		pushToString(GROUP_B_NAME_WITH_SPACE, stuData.name, stuNames);
		break;
	case 3:
		pushToString(GROUP_C_NAME_WITH_SPACE, stuData.name, stuNames);
		break;
	default:
		break;
	}

}

//The following function gets a student and returns if he studies the specific course
bool isHeStudingIt(STUDENT student, int courseNum)
{
	int numOfCourses = student.nofCourses;
	int k;
	for (k = 0; k < numOfCourses; k++)
	{
		if (student.course_info[k].courseNum == courseNum)//checking if the student studies the specific course
		{
			return true;//if he does - return true and get out of the function
		}
		else
		{
			//do nothing and continue to check
		}
	}
	return false;//at the end if you didn't find it - return false
}


//The following function gets a 2 demsion array of studetns and returns how many are studying a specific course
//The function also will update the names of the students that are studing the course
int getStudentNames(STUDENT stuData[][GROUP_STUDENT_NUMBER], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN])
{
	int counter = 0;
	int k, n;
	for (k = 0; k < rows; k++)//running on rows
	{
		for (n = 0; n < cols; n++)//running on cols
		{
			if (isHeStudingIt(stuData[k][n], courseNum))
			{
				pushToStuNames(stuNames[counter], stuData[k][n], k);//sending the specific row
				counter++;
			}
			else
			{
				//do nothing continue to check
			}

		}

	}
	printArrayOfStudentsInCourses(stuNames, counter, courseNum);
	return counter;
}

//The following function gets a student and get an input of num of courses& courses he took.
//The function returns the updates student struct
STUDENT gettingCourses(STUDENT student)
{
	printf("Enter number of courses taken in semester A:");
	scanf("%d", &student.nofCourses);
	int k;
	for (k = 0; k < student.nofCourses; k++)
	{
		printf(" Enter Course number and grade:");
		scanf("%d%d", &student.course_info[k].courseNum, &student.course_info[k].grade);
	}
	return student;
}

//The following function gets a string and putting \0 on last cell
void putLastCellZero(char array[])
{
	array[MAX_NAME_LEN] = END_OF_STRING;
}
//The following function gets an array of students and putting in their details
void getStudent(STUDENT studentArray[], int size)
{
	char firstName[NAME_MAX_CHARACTERS];
	char lastName[NAME_MAX_CHARACTERS];
	char fullName[MAX_FULL_NAME_LEN];
	int k;
	for (k = 0; k < size; k++)
	{

		printf("Enter student first name and last name (seperated by spaces): ");
		scanf("%s", firstName);//getting first name
		scanf("%s", lastName);//getting last name
		strcpy(fullName, firstName);//adding first name to the name
		strcat(fullName, SPACE_STRING);//adding space to the name
		strcat(fullName, lastName);//combining names
		strcpy(studentArray[k].name, fullName);//inserting the full name to the array
		printf("Enter student ID: ");
		scanf("%d", &studentArray[k].identity);
		printf("\n");
		studentArray[k] = gettingCourses(studentArray[k]);
		if (k < size - 1)
		{
			printf("\n");//identetion
		}
	}
}
int getCourseNum()
{
	int num;
	printf("Enter a course number: ");
	scanf("%d", &num);
	return num;
}

/*The following function gets the array of the first
group and getting the students details to the array*/
void getGroupA(STUDENT studentArray[], int size)
{
	printf("Enter students data for GROUP A:\n");
	printLine('_', NUMBER_OF_MINUS);
	printf("\n");
	getStudent(studentArray, size);
}
/*The following function gets the array of the second
group and getting the students details to the array*/
void getGroupB(STUDENT studentArray[], int size)
{
	printf(" Enter students data for GROUP B:\n");
	printLine('_', NUMBER_OF_MINUS);
	printf("\n");
	getStudent(studentArray, size);
}

/*The following function gets the array of the third
group and getting the students details to the array*/
void getGroupC(STUDENT studentArray[], int size)
{
	printf(" Enter students data for GROUP C:\n");
	printLine('_', NUMBER_OF_MINUS);
	printf("\n");
	getStudent(studentArray, size);
}


//The following function gets a character and number of times and prints it
void printLine(char ch, int num)
{
	int k;
	for (k = 1; k <= num; k++)
	{
		printf("%c", ch);
	}
	printf("\n");
}

//The following function prints the welcome message
void welcome()
{
	printf(" ");
	printLine('*', NUMBER_OF_TIMES_CHAR_FIRST_PRINT);
	printf("* Welcome Students *\n");
	printLine('*', NUMBER_OF_TIMES_CHAR_FIRST_PRINT);
	printf("\n");
}
