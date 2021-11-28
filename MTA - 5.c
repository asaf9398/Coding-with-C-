#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ARRAY_MAX_SIZE 20
#define STARTING_FROM_ZERO 0
typedef struct CourseInfo
{
	int courseNum;
	int grade;
}COURSE_INFO;

void welcome();
int numCoursesInSemesterA();
int numCoursesInSemesterB();
void updateArrayFirstSemester(COURSE_INFO array[], int numOfCourses);
void updateArraySecondSemester(COURSE_INFO array[], int numOfCourses, int whereToStart);
void sortingArray(COURSE_INFO array[], int whereToStart, int whereToFinish);
int findSmallest(COURSE_INFO array[], int start, int finish);


void main()
{
	COURSE_INFO array[ARRAY_MAX_SIZE];
	welcome();
	int numOfCouresesSemesterA = numCoursesInSemesterA();//getting the num of courses on 1st semester
	updateArrayFirstSemester(array, numOfCouresesSemesterA);//getting the details of courses on 1st semester
	int numOfCouresesSemesterB = numCoursesInSemesterB();//getting the num of courses on 2nd semester
	updateArraySecondSemester(array, numOfCouresesSemesterB, numOfCouresesSemesterA);//getting the details of courses on 2nd semester
	sortingArray(array,STARTING_FROM_ZERO,numCoursesInSemesterA);//sorting only 1st semester courses
	sortingArray(array, numCoursesInSemesterA, numCoursesInSemesterB);//sorting only 2nd semester courses
}
/*The following function gets an array, where to search and retrns the index of the
struct with the smallest course number*/ 
int findSmallest(COURSE_INFO array[], int start, int finish)
{/*Efficiency O(n)*/
	int temp = start;//taking the first index as start
	while (start < finish)//checking that start didn't pass the finish
	{
		if (array[start].courseNum <= array[temp].courseNum)//if you find new smallest number save it
		{
			temp = start;
		}
		start++;//promoting the index for checking all the little array
	}
	return temp;//returning the index of the smallest course number
}
//The following function gets an array and start&stop points and sorting it by the course number
void sortingArray(COURSE_INFO array[], int whereToStart, int whereToFinish)
{/*This is a kind of "Bubble Sort", we running on all over the array 1 time with the loop(n cells)
 & using findSmallest function that runs over the array also n times(not the same n every time)
 this is why the efficiency is O(n^2)*/
	int k;
	for (k = whereToStart; k < whereToFinish + whereToStart; k++)//running all over the places in the array
	{
		int indexSmallest =findSmallest(array, k, whereToFinish);//finding the lowest course number index
		COURSE_INFO temp = array[k];//saving the array[k] info
		array[k] = array[indexSmallest];//putting the smallest course number strtuct in array[k] 
		array[indexSmallest] = temp;//putting the other struct we saved where the smallest was(for not losing any data)
	}
}
/*The following function gets an array, how much courses to put in and where to start in the array 
and using the users input to put the courses data to the array*/
void updateArraySecondSemester(COURSE_INFO array[], int numOfCourses,int whereToStart)
{
	int k;
	for (k = whereToStart; k < whereToStart + numOfCourses; k++)
	{
		printf("Enter course number and grade:");
		scanf("%d%d", &array[k].courseNum, &array[k].grade);
	}
}
/*The following function gets an array and how much courses to put in and using
the users input to put the courses data to the array*/ 
void updateArrayFirstSemester(COURSE_INFO array[],int numOfCourses)
{
	int k;
	for(k=0;k<numOfCourses;k++)
	{ 
		printf("Enter course number and grade:");
		scanf("%d%d", &array[k].courseNum, &array[k].grade);
	}	
}
//The following function asks from the user to enter how many courses he took on the 2nd semester and returns this number
int numCoursesInSemesterB()
{
	printf("Please enter number of courses in semester B:");
	int num = scanf("%d", &num);
	return num;
}
//The following function asks from the user to enter how many courses he took on the 1st semester and returns this number
int numCoursesInSemesterA()
{
	printf("Please enter number of courses in semester A:");
	int num = scanf("%d", &num);
	return num;
}
//The following function prints a welcome message to the user 
void welcome()
{
	printf("Welcome students!!\n");
	printf("and bye bye Pizzeria\n");
}
