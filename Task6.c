#define _SECURE_CRT_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define NUMBER_OF_TIMES_CHAR_FIRST_PRINT 20
#define NUMBER_OF_GROUPS 3
#define NUMBER_OF_STUDENTS_EACH_GROUP 6
#define MAX_NAME_LEN 22
#define MAX_COURSES 10
#define NUMBER_OF_MINUS 32



void welcome();
STUDENT gettingCourses(STUDENT student);
void putLastCellZero(char array[]);
void getStudent(STUDENT studentArray[], int size);
void getGroupA(STUDENT studentArray[], int size);
void printLine(char ch, int num);

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

