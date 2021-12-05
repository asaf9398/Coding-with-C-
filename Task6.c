#define _SECURE_CRT_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define NUMBER_OF_TIMES_CHAR_FIRST_PRINT 20
#define NUMBER_OF_GROUPS 3
#define NUMBER_OF_STUDENTS_EACH_GROUP 6
#define MAX_NAME_LEN 22
#define MAX_FULL_NAME_LEN 29
#define MAX_COURSES 10
#define NUMBER_OF_MINUS 32
#define GROUP_STUDENT_NUMBER 6
#define GROUP_NAME_LENGTH 7



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
void printArrayOfStudentsInCourses(char stuNames[],int size,int courseNum)
{
	printf("Names of students in course#%d:\n",courseNum);
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
		stuNames[k+GROUP_NAME_LENGTH] = name[k];
	}
	stuNames[MAX_FULL_NAME_LEN] = '\0';//putting \0 to finish string
}

//The following function gets an array of strings and a student and puts it inside by the group number
void pushToStuNames(char stuNames[], STUDENT stuData,int numOfGroup)
{
	switch (numOfGroup+1)
	{
	case 1:
		pushToString("GroupA ", stuData.name,stuNames);
		break;
	case 2:
		pushToString("GroupB ", stuData.name, stuNames);
		break;
	case 3 :
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


//The following funtion gets a 2 demsion array of studetns and returns how many are studying a specific xourse
//The fucntion also will update the names of the students that are studing the course
int getStudentNames(STUDENT stuData[][GROUP_STUDENT_NUMBER], int rows, int cols, int courseNum, char stuNames[][MAX_FULL_NAME_LEN])
{
	int counter = 0;
	int k, n;
	for (k = 0; k < rows; k++)//running on rows
	{
		for (n = 0; n < cols; n++)//running on cols
		{
			if (isHeStudingIt(stuData[k][n],courseNum))
			{
				pushToStuNames(stuNames[counter],stuData[k][n],k);//sending the specific row
				counter++;
			}
			else 
			{
				//do nothing continue to check
			}

		}

	}
	printArrayOfStudentsInCourses(stuNames,counter,courseNum);
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
	array[MAX_NAME_LEN] = '\0';
}
//The following function gets an array of students and putting in their details
void getStudent(STUDENT studentArray[],int size)
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
		studentArray[k]=gettingCourses(studentArray[k]);

	}
}
/*The following function gets the array of the first
group and getting the students details to the array*/
void getGroupA(STUDENT studentArray[],int size)
{
	printf("Enter students data for GROUP A:\n");
	printLine('-', NUMBER_OF_MINUS);
	getStudent(studentArray,size);
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

