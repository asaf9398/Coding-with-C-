#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define NUMBER_OF_TIMES_CHAR_FIRST_PRINT 20
#define NUMBER_OF_GROUPS 3
#define NUMBER_OF_STUDENTS_EACH_GROUP 6
#define MAX_NAME_LEN 22
#define MAX_FULL_NAME_LEN 30
#define MAX_COURSES 10
#define NUMBER_OF_MINUS 32
#define GROUP_STUDENT_NUMBER 6
#define GROUP_NAME_LENGTH 7
#define WHICH_NAME_TO_PUT_IN "Lane"
#define SPACE_STRING " "
#define SPACE_CHAR ' '
#define SPACE_STRING_LEN 1
#define NOT_INSIDE -1
#define END_OF_STRING '\0'
#define FIRST_CELL 0



void welcome();
STUDENT gettingCourses(STUDENT student);
void putLastCellZero(char array[]);
void getStudent(STUDENT studentArray[], int size);
void getGroupA(STUDENT studentArray[], int size);
void printLine(char ch, int num);
int getStudentNames(STUDENT stuData[][GROUP_STUDENT_NUMBER], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN]);


typedef struct CourseInfo
{
	int courseNum;
	int grade;
} COURSE_INFO;

typedef struct Student
{
	char name[MAX_NAME_LEN];
	int identity;
	int nofCourses; //number of courses taken in semesterA
	COURSE_INFO course_info[MAX_COURSES];
} STUDENT;


void main()
{
	STUDENT studentsArray[NUMBER_OF_GROUPS][NUMBER_OF_STUDENTS_EACH_GROUP];
	

}
//The following function gets an array of names(with size) and which line to delete and delets is
void deleteLineFromArray(char names[][MAX_FULL_NAME_LEN], int whichLine, int howManyNames)
{
	int k;
	if (whichLine+1 != howManyNames)//checking if the line is the last one
	{
		//taking the lower rows and copying them instead of this one
		for (k=whichLine;k<howManyNames;k++)
		{
			strcpy(names[k],names[k+1]);//deleting the whole line by coping the next line on it
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
void deleteFromArray(char names[][MAX_FULL_NAME_LEN],int howManyNames, char whatToCheck[])
{
	int k = 0;
	int howManyDeleted = 0;
	/*the loop will end when the counter of the those who has the name +
	the counter of those who doesn't has the name will be the amount of names in the array*/
	while(k+howManyDeleted!=howManyNames) 	
	{
		if (checkIfInside(names[k], whatToCheck))
		{
			deleteLineFromArray(names, k,howManyNames);
			howManyNames--;
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
			if (k + whatToCheckLen < size)//checking if we're not going out of the string
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
void deleteWord(char name[],char whatToDelete[])
{
	int index = checkIfInside(name, whatToDelete);
	if (index!=NOT_INSIDE)//checking if the specific word is inside
	{//if the word is inside - delete it
		int nameLen = strlen(name);
		int whatToDeleteLen = strlen(whatToDelete);
		if (index + 1 + whatToDeleteLen == nameLen)
		{
			name[index] = END_OF_STRING;
		}
		else 
		{
			int k;
			for (k = index;k < nameLen;k++)
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
	for (i = 0; k < i + wordLen; k++)
	{
		name[k + i] = word[i];
	}
}
//The following function checking if there is a word inside name from k to k+wordLen
bool compareString(char name[], int k, int wordLen, char word[])
{
	int i;
	for (i = 0; k < i + wordLen; k++)
	{
		if (name[k + i] != word[i])
		{
			return false;
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
			if (k + wordLen < size)//checking if we're not going out of the string
			{
				if (compareString(name, k, wordLen, word))//checking only wordLen of the name to compare
				{
					changeNameToWord(name, k, wordLen, word);//changing name to word
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
	for (k = 0; numOfSpaces < 2; k++)
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
	name[k] = END_OF_STRING;
}


//The following function gets full name and putting first name into another array
void onlyFirstName(char name[], char firstName[])
{
	int numOfSpaces = 0;
	int k;
	for (k = 0; numOfSpaces < 1;k++)
	{
		if (name[k] == SPACE_CHAR)
			numOfSpaces++;
	}
	for (k = 0; numOfSpaces < 2; k++)
	{
		if (name[k] == SPACE_CHAR)
		{
			numOfSpaces++;
		}
		else
		{
			firstName[k] = name[k + GROUP_NAME_LENGTH];
		}

	}
	firstName[k] = END_OF_STRING;

}

//The following function gets full name and putting group name into another array
void onlyGroupName(char name[], char groupName[])
{

	int numOfSpaces = 0;
	int k;
	for (k = 0; numOfSpaces < 1; k++)
	{
		groupName[k] = name[k];
		if (name[k] == SPACE_CHAR)
		{
			numOfSpaces++;
		}
	}
	groupName[k] = END_OF_STRING;

}

//The following function gets a string and changing each time the name "Lois" is appeared to "Lane"
void splitName(char name[], int size)
{
	char groupName[MAX_NAME_LEN];//srting of only group name
	onlyGroupName(name, groupName);//putting group name into groupName 
	char firstName[MAX_NAME_LEN];//srting of only first name
	onlyFirstName(name, firstName);//putting first name into firstName 
	changingNameToNewName(firstName, WHICH_NAME_TO_PUT_IN);//changing name to newName(if it's in)
	char lastName[MAX_NAME_LEN];//srting of only last name
	onlyLastName(name, lastName);//putting name into lastName
	changingNameToNewName(lastName, WHICH_NAME_TO_PUT_IN);//changing name to newName(if it's in)
	strcat(groupName, SPACE_STRING);//combining back the updated name
	strcat(groupName, firstName);
	strcat(groupName, SPACE_STRING);
	strcat(groupName, lastName);
	strcpy(name, groupName);//coping the new updated array to the old array
}


//The following function gets an array of names and course num they all went and prints their names 
void printArrayOfStudentsInCourses(char stuNames[][MAX_FULL_NAME_LEN], int size, int courseNum)
{
	printf("Names of students in course#%d:\n", courseNum);
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
	switch (numOfGroup + 1)
	{
	case 1:
		pushToString("GroupA ", stuData.name, stuNames);
		break;
	case 2:
		pushToString("GroupB ", stuData.name, stuNames);
		break;
	case 3:
		pushToString("GroupC ", stuData.name, stuNames);
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
		if (student.course_info[k].courseNum == courseNum)
		{
			return true;
		}
		else
		{
			//do nothing and continue to check
		}
	}
	return false;
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
	printf("\n");
	int k;
	for (k = 0; k < student.nofCourses; k++)
	{
		printf("Enter course number and grade: ");
		scanf("%d%d", &student.course_info[k].courseNum, &student.course_info[k].grade);
		printf("\n");
	}
	printf("\n");
}

//The following function gets a string and putting \0 on last cell
void putLastCellZero(char array[])
{
	array[MAX_NAME_LEN] = END_OF_STRING;
}
//The following function gets an array of students and putting in their details
void getStudent(STUDENT studentArray[], int size)
{
	int k;
	for (k = 0; k < size; k++)
	{
		printf("Enter student first name and last name (seperated by spaces): ");
		scanf("%s", &studentArray[k].name);
		putLastCellZero(studentArray[k].name);
		printf("\n");
		printf("Enter student ID: ");
		scanf("%d", &studentArray[k].identity);
		printf("\n\n");
		studentArray[k] = gettingCourses(studentArray[k]);

	}
}
/*The following function gets the array of the first
group and getting the students details to the array*/
void getGroupA(STUDENT studentArray[], int size)
{
	printf("Enter students data for GROUP A:\n");
	printLine('-', NUMBER_OF_MINUS);
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
	printLine('*', NUMBER_OF_TIMES_CHAR_FIRST_PRINT);
	printf("* Welcome Students *\n");
	printLine('*', NUMBER_OF_TIMES_CHAR_FIRST_PRINT);
}
