#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define ARRAY_MAX_SIZE 10//const value for maximum cells in courses array
#define MERGED_ARRAY_MAX_SIZE 20//const value for maximum cells in unite array
#define MAX_GRADE_ARRAY 13//const value for maximum cells in grades array
#define MIN_EXERCISE_GRADE 30//const value for first cell in grades array
#define MAX_EXERCISE_GRADE 100//const value for maximum grade for exercise
#define PASS_TEST_GRADE 60//const value for minimum grade passing an exercise
typedef struct CourseInfo//struct than has courses 
{//each course has number and a grade
	int courseNum;
	int grade;
}COURSE_INFO;

void welcome();
int numCoursesInSemesterA();
int numCoursesInSemesterB();
void updateArrayFirstSemester(COURSE_INFO array[], int numOfCourses);
void updateArraySecondSemester(COURSE_INFO array[], int numOfCourses);
void sortCourses(COURSE_INFO data[], int size);
void swap(COURSE_INFO array[], int indexA, int indexB);
void printCourses(COURSE_INFO data[], int size);
void printCoursesSemesterA();
void printCoursesSemesterB();
int unite(COURSE_INFO dataA[], int sizeA, COURSE_INFO dataB[], int sizeB, int uniteCourse[]);
bool searchingCourseInArray(int courseNum, int array[], int size);
int intersect(COURSE_INFO dataA[], int sizeA, COURSE_INFO dataB[], int sizeB, int interCourse[]);
bool searchingCoursesInCoursesArray(COURSE_INFO array[], int size, int courseNum);
COURSE_INFO findMinGrade(COURSE_INFO data[], int size);
void printMinGradeSemesterA(COURSE_INFO min);
void printCNum(int data[], int size);
void swapInt(int array[], int indexA, int indexB);
void sortCoursesInt(int data[], int size);
void printInstersect(int array[], int size);
void printUnion(int array[], int size);
void printExercisesArray(int array[], int size);
int exercisesArray(int array[], COURSE_INFO minGrade);
int findFailPass(int grades[], int size);
void printFindFailPass(int grades[], int size);
void gettingLimitGrade(int grades[], int size);
int reorderGrades(int grades[], int size, int limit);


void main()
{
	COURSE_INFO arrayFirstSemester[ARRAY_MAX_SIZE];
	COURSE_INFO arraySecondSemester[ARRAY_MAX_SIZE];
	welcome();
	int numOfCouresesSemesterA = numCoursesInSemesterA();//getting the num of courses on 1st semester
	updateArrayFirstSemester(arrayFirstSemester, numOfCouresesSemesterA);//getting the details of courses on 1st semester
	int numOfCouresesSemesterB = numCoursesInSemesterB();//getting the num of courses on 2nd semester
	updateArraySecondSemester(arraySecondSemester, numOfCouresesSemesterB);//getting the details of courses on 2nd semester
	sortCourses(arrayFirstSemester, numOfCouresesSemesterA);//sorting the array
	sortCourses(arraySecondSemester, numOfCouresesSemesterB);//sorting the array
	printCoursesSemesterA();//printing courses in semester A
	printCourses(arrayFirstSemester, numOfCouresesSemesterA);//printing courses in semester A
	printCoursesSemesterB();//printing courses in semester B
	printCourses(arraySecondSemester, numOfCouresesSemesterB);//printing courses in semester B
	int uniteArrays[MERGED_ARRAY_MAX_SIZE];//creating array of uniting
	int intersectArrays[ARRAY_MAX_SIZE];//creating array of intersecting
	int howManyCoursesUnited = unite(arrayFirstSemester,numOfCouresesSemesterA,arraySecondSemester,numOfCouresesSemesterB,uniteArrays);//uniting the array
	int howManyCoursesIntersected=intersect(arrayFirstSemester,numOfCouresesSemesterA,arraySecondSemester,numOfCouresesSemesterB,intersectArrays);//intersecting the array
	sortCoursesInt(uniteArrays, howManyCoursesUnited);//sorting the array
	sortCoursesInt(intersectArrays, howManyCoursesIntersected);//sorting the array
	printUnion(uniteArrays, howManyCoursesUnited);//printing union array
	printInstersect(intersectArrays, howManyCoursesIntersected);//printing intersecting array
	printMinGradeSemesterA(findMinGrade(arrayFirstSemester, numOfCouresesSemesterA));//finding&printing the min course grade
	COURSE_INFO minGrade = findMinGrade(arrayFirstSemester, numOfCouresesSemesterA);
	int grades[MAX_GRADE_ARRAY];//creating grades array
	int numOfExercises =exercisesArray(grades,minGrade);
	printExercisesArray(grades,numOfExercises);//printing grades array
	printFindFailPass(grades, numOfExercises);//prints findFailPass function output
	gettingLimitGrade(grades,numOfExercises);//getting s limit grade and using reorderGrades function + printing output

}
//The following function getting an input for reorderGrades function and updates the array
//The function also prints the grades that are smaller than "limit" by order 
void gettingLimitGrade(int grades[], int size)
{//efficiency O(n)=size+logicSize=n=size
	int limit;
	printf("Please enter a limit grade: ");
	scanf("%d", &limit);
	printf("\n");
	int logicSize=reorderGrades(grades, size, limit);
	int k;
	printf("After reordering grades, the grades smaller than %d are: ",limit);
	for (k = 0; k < logicSize;k++)
	{
		printf("%d ", grades[k]);
	}
	printf("\n");

}
/* The following fucntion gets an array(with size) and a limit and sorting the grades by the order of appearance
before limit , the funciton also returns how much values are smaller than limit*/
int reorderGrades(int grades[], int size, int limit)
{//effciency O(n)=n=size
	int counter = 0,write=0;
	int read;
	for (read=0;read<size;read++)
	{
		if (grades[read]<limit)
		{
			swapInt(grades, read, write);
			write++;
			counter++;
		}

	}
	return counter;
}
//The following function gets an grades array and prints findFailPass function output
void printFindFailPass(int grades[], int size)
{
	printf("Index of Fail-Pass is: %d\n",findFailPass(grades,size));
}
/*The following function gets an array of gradesand returns the index of
the first grade that is F and the one after it is a pass*/
int findFailPass(int grades[], int size)
{//effciency O(n)=n=size
	//Linear search
	int k;
	for (k = 0;k < size;k++)
	{
		if (k == 0)//checking for the first cell
		{
			if (grades[k]<PASS_TEST_GRADE && grades[k + 1]>=PASS_TEST_GRADE)//checking only the right cell
			{
				return k;
			}
			else
			{
				//continue
			}
			
		}
		else 
		{
			if (k == size - 1)//checking for the last cell
			{
				if (grades[k - 1] < PASS_TEST_GRADE && grades[k] >= PASS_TEST_GRADE)//checking only the left cell
				{
					return k - 1;
				}
			}
			else 
			{
				if (grades[k] < PASS_TEST_GRADE && grades[k + 1] >= PASS_TEST_GRADE)//checking the mid from the right
				{
					return k;
				}
				else
				{
					if (grades[k] >= PASS_TEST_GRADE && grades[k - 1] < PASS_TEST_GRADE)//checking the mid from the left
					{
						return k - 1;
					}
					else 
					{
						//continue
					}
				}
			}
		}
	}
	return k-1;//returning k-1 no matter what(for not getting "not always return a value") 
}

//The following function gets an array of grades(with size) and prints it
void printExercisesArray(int array[], int size)
{//efficiency O(n)=n=size
	int k;
	printf("Exercise grades:");
	for (k = 0;k < size;k++)
	{
		printf(" %d", array[k]);
	}
	printf("\n");
}
//The following funtion gets an grades array and the minGrade course and returns the number of exercises
//The function also saves the grades into the array
int exercisesArray(int array[],COURSE_INFO minGrade)
{//efficiency O(n)=n=numOfExercises
	printf("How many exercises were given in course #%d?", minGrade.courseNum);
	int numOfExercises; 
	scanf("%d", &numOfExercises);
	printf("\n");
	printf("Enter exercises grades:");
	int k;
	for (k = 0;k < numOfExercises;k++)
	{
		scanf(" %d ", &array[k]);
	}
	printf("\n");
	array[0] = MIN_EXERCISE_GRADE;
	array[numOfExercises - 1]= MAX_EXERCISE_GRADE;
	return numOfExercises;
}
//The following function gets an array and swapping 2 cells in it(by index)
void swapInt(int array[], int indexA, int indexB)
{//efficiency is O(1)
	int temp = array[indexA];//saving the first cell
	array[indexA] = array[indexB];//replacing
	array[indexB] = temp;//changing the second sell
}
//The following sort is bubble sort - putting all the big course numbers on the end
void sortCoursesInt(int data[], int size)
{//efficiency O(n)=size^2
	int i, k;
	for (i = 0; i < size; i++)
	{
		for (k = 0; k < size - 1 - i; k++)
		{
			if (data[k] > data[k + 1])
				swapInt(data, k, k + 1);
		}
	}
}
//The following function prints the intersect of the courses
void printInstersect(int array[], int size)
{//efficiency O(n)=n=size
	printf("courses taken in semester A and semester B: ");
	printCNum(array, size);
	printf("\n");
}
//The following function prints the union of the courses
void printUnion(int array[], int size)
{//efficiency O(n)=n=size
	printf("\n");
	printf("courses taken in semester A or semester B: ");
	printCNum(array, size);
}
//The following function gets an int array with his size and prints it
void printCNum(int data[], int size)
{//efficiency O(n)=n=size
	int k;
	for (k = 0;k < size;k++)
	{
		printf("%d ", data[k]);
	}
	printf("\n");
}
//The foolowing function gets a minimun grade course of semester A and prints it
void printMinGradeSemesterA(COURSE_INFO min)
{//efficiency O(1)
	printf("Minimum grade in semester A is: %d in course #%d\n\n",min.grade,min.courseNum);
}
//The following function gets an array of courses data (with his size) and returns the course with the lowest grade
COURSE_INFO findMinGrade(COURSE_INFO data[], int size)
{//running on all over the array to find the lowest grade 
	//efficiency O(n)=size
	int index = 0;//saving the index of the lowest grade
	int k;
	for (k = 0;k < size;k++)
	{
		if (data[k].grade < data[index].grade)
		{
			index = k;
		}
	}
	return data[index];

}

/*The following function gets a courses array(with his size) and a course number and retuns true\false
if the course number is in it*/
bool searchingCoursesInCoursesArray(COURSE_INFO array[], int size,int courseNum)
{
	//Using binari search to find the courseNum - efficiency O(n)=log(size)
	int start = 0, end = size - 1, k;
	for (k = 0;start <= end;k++)
	{
		int mid = (start + end) / 2;//using the middle between start and end to see wherever you are in the array
		if (array[mid].courseNum == courseNum)
			return true;//if found return true
		else //checking if the number is on the right/left side of the array
		{
			if (array[mid].courseNum > courseNum)
			{
				end = mid - 1;//promoting end to the center
			}
			else
			{
				start = mid + 1;//promoting start to the center
			}
		}
	}
	return false;//if we didn't find the num at all - return false
}

/*The following function gets the arrays and a new sharedCourses array, the function updates 
the sharedCourses array and returns the number of shared courses on the first and second semester*/
int intersect(COURSE_INFO dataA[], int sizeA, COURSE_INFO dataB[], int sizeB, int interCourse[])
{//using the smaller array for cheking less options with the binari search
	//efficiency of O(n)=sizeA*log(sizeB) or O(n)=sizeB*log(sizeA)
	//(depends about who is bigger - sizeA/sizeB)
	int counter = 0;
	if (numCoursesInSemesterA < numCoursesInSemesterB)
	{//if A has less courses we can check only the smaller group
		int k;
		for (k = 0;k < sizeA;k++)
		{
			if (searchingCoursesInCoursesArray(dataB, sizeB, dataA[k].courseNum))
			{
				interCourse[counter] = dataA[k].courseNum;
				counter++;
			}
		}
	}
	else
	{//if B has less courses(or even) we can check only the smaller group
		int k;
		for (k = 0;k < sizeB;k++)
		{
			if (searchingCoursesInCoursesArray(dataA, sizeA, dataB[k].courseNum))
			{
				interCourse[counter] = dataB[k].courseNum;
				counter++;
			}
		}
	}
	return counter;

}


//The following function gets an array(with his size) and course number and returns if the number in it
bool searchingCourseInArray(int courseNum, int array[], int size)
{//Using binari search to find the courseNum-efficiency O(n)=log(size)
	int start = 0, end = size - 1,k;
	for (k = 0;start <= end;k++)
	{
		int mid = (start + end)/2;//using the middle between start and end to see wherever you are in the array
		if (array[mid] == courseNum)
			return true;//if found return true
		else //checking if the number is on the right/left side of the array
		{
			if (array[mid] > courseNum)
			{
				end = mid-1;//promoting end to the center
			}
			else 
			{
				start = mid+1;//promoting start to the center
			}
		}
	}
	return false;//if we didn't find the num at all - return false
}
/*The function gets the arrays of semester Aand B, the function merging the courses
into a new array and returns the logic length of the new merged array(how many courses it has)*/
int unite(COURSE_INFO dataA[], int sizeA, COURSE_INFO dataB[], int sizeB, int uniteCourse[])
{//taking the bigger array first and than adding the another courses from the smaller array
	//efficiency O(n)=sizeB+sizeB*log(sizeA)=sizeB*log(sizeA) or sizeA+sizeA*log(sizeB)=sizeA*log(sizeB)
	//(depends who is bigger sizeA/sizeB)
	int counter = 0;
	if (sizeB > sizeA)
	{
		int k;
		for (k = 0;k < sizeB;k++)
		{//Putting all the courses from second array into the merged array(the bigger array)
			uniteCourse[counter] = dataB[k].courseNum;
			counter++;
			sortCoursesInt(uniteCourse, counter);//if adding valies to the end of the array - making sure he's sorted
		}
		for (k = 0;k < sizeA;k++)
		{//Putting all the courses that are not in second semester into the merged array
			if (!searchingCourseInArray(dataA[k].courseNum, uniteCourse,counter))
			{
				uniteCourse[counter] = dataA[k].courseNum;
				counter++;
				sortCoursesInt(uniteCourse, counter);//if adding valies to the end of the array - making sure he's sorted
			}
			
		}
	}
	else
	{
		int k;
		for (k = 0;k < sizeA;k++)
		{//Putting all the courses from first array into the merged array(the bigger array)
			uniteCourse[counter] = dataA[k].courseNum;
			counter++;
			sortCoursesInt(uniteCourse, counter);//if adding valies to the end of the array - making sure he's sorted
		}
		for (k = 0;k < sizeB;k++)
		{//Putting all the courses that are not in first semester into the merged array
			if (!searchingCourseInArray(dataB[k].courseNum, uniteCourse,counter))
			{
				uniteCourse[counter] = dataB[k].courseNum;
				counter++;
				sortCoursesInt(uniteCourse, counter);//if adding valies to the end of the array - making sure he's sorted
			}

		}
	}

	return counter;
}

//The function prints the message before printing courses details
void printCoursesSemesterA()
{//efficiency is O(1)
	printf("\n");
	printf("Sorted courses of semester A:\n");
}
//The function prints the message before printing courses details
void printCoursesSemesterB()
{//efficiency is O(1)
	printf("\n");
	printf("Sorted courses of semester B:\n");
}
//The following function prints the courses
void printCourses(COURSE_INFO data[], int size)
{//efficiency is O(n)=size
	printf("Course# Grade\n");
	printf("======= =====\n");
	int k;
	for (k = 0;k < size;k++)
	{
		printf("%-7d %-5d\n", data[k].courseNum, data[k].grade);// -(minus) is aligining to the left
	}

}
//The following function gets an array and swapping 2 cells in it(by index)
void swap(COURSE_INFO array[], int indexA, int indexB)
{//efficiency is O(1)
	COURSE_INFO temp = array[indexA];//saving the first cell
	array[indexA] = array[indexB];//replacing
	array[indexB] = temp;//changing the second sell
}
//The following sort is bubble sort - putting all the big course numbers on the end
void sortCourses(COURSE_INFO data[], int size)
{//O(n)=n^2
	int i, k;
	for (i = 0; i < size; i++)
	{
		for (k = 0; k < size - 1 - i; k++)
		{
			if (data[k].courseNum > data[k + 1].courseNum)
				swap(data, k, k + 1);
		}
	}
}

/*The following function gets an array, how much courses to put in and where to start in the array
and using the users input to put the courses data to the array*/
void updateArraySecondSemester(COURSE_INFO array[], int numOfCourses)
{//efficiency is O(n)=numOfCourses
	int k;
	for (k = 0; k < numOfCourses; k++)
	{
		printf("Enter course number and grade:");
		scanf("%d%d", &array[k].courseNum, &array[k].grade);
		printf("\n");
	}
}
/*The following function gets an array and how much courses to put in and using
the users input to put the courses data to the array*/
void updateArrayFirstSemester(COURSE_INFO array[], int numOfCourses)
{//efficiency is O(n)=numOfCourses
	int k;
	for (k = 0;k < numOfCourses;k++)
	{
		printf("Enter course number and grade:");
		scanf("%d%d", &array[k].courseNum, &array[k].grade);
		printf("\n");
	}
}
//The following function asks from the user to enter how many courses he took on the 2nd semester and returns this number
int numCoursesInSemesterB()
{//efficiency is O(1)
	printf("Please enter number of courses in semester B:");
	int num;
	scanf("%d", &num);
	printf("\n");
	return num;
}
//The following function asks from the user to enter how many courses he took on the 1st semester and returns this number
int numCoursesInSemesterA()
{//efficiency is O(1)
	printf("Please enter number of courses in semester A:");
	int num;
	scanf("%d", &num);
	printf("\n");
	return num;
}
//The following function prints a welcome message to the user 
void welcome()
{//efficiency is O(1)
	printf(" Welcome students!!\n");
	printf("and bye bye Pizzeria\n\n");
}
