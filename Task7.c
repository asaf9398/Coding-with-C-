#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 10
#define MAX_INT_SIZE 10
#define FUNC_COUNT 9
#define EXIT 0
#define ONLY_ONE 1
#define NEXT_CELL 1
#define NOTHING 0
#define MIN_CELLS 2
#define END_OF_STRING '\0'
#define FIRST_CELL 0
#define ZERO_ASCII '0'



// Add your recursive functions declarations here
bool isEven(int num, int dig);
int howManyPaths(int x, int y);
int biggestLowPower(int x, int num);
int partSum(int num);
void intToStr(int num, char s[]);
void fillMaxPrefixesArray(int numbers[], int n, int maxPrefixesArray[]);
void getMinToStart(int numbers[], int n);
void combineArrays(int sortedArr1[], int size1, int sortedArr2[], int size2);
int countSmaller(int arr[], int start, int end, int num);

// Testing functions
int readArray(int data[], int maxSize);
void printArray(int data[], int size);
void bubbleSort(int arr[], int size);
void swap(int arr[], int i, int j);
void checkQ1();
void checkQ2();
void checkQ3();
void checkQ4();
void checkQ5();
void checkQ6();
void checkQ7();
void checkQ8();
void checkQ9();


/*********** main - don't make any changes here !!! ***************************/
void main()
{
	int funcNum;
	bool exit = false;

	while (!exit)
	{
		printf("Enter the number of function you want to check (1-%d) or %d to exit the program: ", FUNC_COUNT, EXIT);
		scanf("%d", &funcNum);

		switch (funcNum)
		{
		case 1:
			checkQ1();
			break;
		case 2:
			checkQ2();
			break;
		case 3:
			checkQ3();
			break;
		case 4:
			checkQ4();
			break;
		case 5:
			checkQ5();
			break;
		case 6:
			checkQ6();
			break;
		case 7:
			checkQ7();
			break;
		case 8:
			checkQ8();
			break;
		case 9:
			checkQ9();
			break;
		case EXIT:
			exit = true;
			break;
		default:
			printf("Invalid choice.\n");
		}
		printf("\n");
	}

}

/***************** Testing functions - don't make any changes here!!! ***************/
void checkQ1()
{
	int num, dig;

	printf("Enter a positive integer: ");
	scanf("%d", &num);
	printf("Enter a digit: ");
	scanf("%d", &dig);
	if (isEven(num, dig))
	{
		printf("%d appears even number of times in %d\n", dig, num);
	}
	else
	{
		printf("%d appears odd number of times in %d\n", dig, num);
	}
}

void checkQ2()
{
	int x, y;

	printf("Enter two non-negative integers: ");
	scanf("%d%d", &x, &y);
	printf("There are %d paths from (0,0) to (%d,%d)\n", howManyPaths(x, y), x, y);
}

void checkQ3()
{
	int x, num;

	printf("Enter two positive integers: ");
	scanf("%d%d", &x, &num);
	printf("The biggest power of %d which is smaller than %d is %d\n", x, num, biggestLowPower(x, num));
}

void checkQ4()
{
	int num;

	printf("Enter a positive integer: ");
	scanf("%d", &num);
	printf("The partial sum of %d digits is %d\n", num, partSum(num));
}

void checkQ5()
{
	int num;
	char string[MAX_INT_SIZE + 1];

	printf("Enter a positive integer: ");
	scanf("%d", &num);
	intToStr(num, string);
	printf("The string representing the integer %d is %s\n", num, string);
}

void checkQ6()
{
	int numbers[SIZE];
	int maxPrefixes[SIZE];
	int size;

	size = readArray(numbers, SIZE);
	fillMaxPrefixesArray(numbers, size, maxPrefixes);
	printf("Max prefixes array: ");
	printArray(maxPrefixes, size);
}
// This function prints the first size elements of data array (integers).
void printArray(int data[], int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");
}

// This function reads a series of integers from user into data array.
// The function will first ask the user to enter the number of integers he wishes
// to enter to array. If number is bigger than maxSize, then only the first masSize
// numbers will be read.
// The fucntion returns the arrays logical size (number of elements inserted into array).
int readArray(int data[], int maxSize)
{
	int count;
	int i;	// number of elements inserted into array

	printf("How many numbers would you like to enter to array ? (no more than %d) ", maxSize);
	scanf("%d", &count);
	if (count > maxSize)
	{
		count = maxSize;
	}
	printf("Please enter %d integers: ", count);

	for (i = 0; i < count; i++)
	{
		scanf("%d", &data[i]);	// read current input number
	}

	return count;
}


void checkQ7()
{
	int numbers[SIZE];
	int size;

	size = readArray(numbers, SIZE);
	getMinToStart(numbers, size);
	printf("The minimal number is: %d\n", numbers[0]);

	// check if all other numbers are still inb array
	bubbleSort(numbers, size);
	printf("The sorted array: ");
	printArray(numbers, size);
}
// This functions sorts arr in increasing order using bubble sort algorithm
void bubbleSort(int arr[], int size)
{
	int i, j;

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(arr, j, j + 1);
}

void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}


void checkQ8()
{
	int arr1[SIZE], arr2[2 * SIZE];
	int size1, size2;

	size1 = readArray(arr1, SIZE);
	size2 = readArray(arr2, 2 * SIZE - size1);

	// sort arrays
	bubbleSort(arr1, size1);
	bubbleSort(arr2, size2);

	combineArrays(arr1, size1, arr2, size2);
	printf("The combined sorted array: ");
	printArray(arr2, size1 + size2);
}

void checkQ9()
{
	int numbers[SIZE];
	int size, num;

	// read numbers from user (assumption: numbers are different from each other)
	size = readArray(numbers, SIZE);
	bubbleSort(numbers, size);

	printf("Please enter an integer: ");
	scanf("%d", &num);

	printf("There are %d numbers in array that are smaller than %d\n", countSmaller(numbers, 0, size - 1, num), num);
}




/******************************* Recursive functions **************************/
// Add recursive functions implementation here

/*The following function gets a
number and a digit and returns true if the number of times
that digit is inside num is parity*/
bool isEven(int num, int dig)
{
	//need to check
	if (num < 10)
	{
		//return(!num == dig);
		return !(dig == num);
	}
	if (dig == num % 10)
	{
		return !(isEven(num / 10, dig));
	}
	else
	{
		return ((isEven(num / 10, dig)));
	}
}

/*The following function gets a dot of(x,y) and returns the number of ways to go from(0,0) to (x,y)*/
int howManyPaths(int x, int y)
{
	int counter = NOTHING;
	if (x == NOTHING || y == NOTHING)
	{
		return ONLY_ONE;//when you came to(0,0) its a full path so count it
	}

	if (x - ONLY_ONE >= NOTHING)
	{
		counter += (howManyPaths(x - ONLY_ONE, y));//if you can move more on X do it
	}
	if (y - ONLY_ONE >= NOTHING)
	{
		counter += (howManyPaths(x, y - ONLY_ONE));//if you can move more on X do it
	}

	return counter;//return all the counting you did on your path
}
/*The following function gets 2 numbers x and num(positive and whole).
The function returns the biggest power of x when  x<= num*/
int biggestLowPower(int x, int num)
{
	if (x > num)//if the base is bigger than what reamined from num return 1(for multiply)
		return ONLY_ONE;
	else
	{
		if (x == num)//if the base is equal to what reamined from num return base(for multiply)
		{
			return x;
		}
		return x * biggestLowPower(x, num / x);//if the base is smaller than what reamined from num use the recursion again with num/base
	}
}
/*The following function gets a number and returns the sum of digits without the LSD digit(the most right digit).
If the number if smaller than 10 the sum is equal to 0 */
int partSum(int num)
{
	int sum = NOTHING;
	if (num < 10)//exit point
	{
		//if the number has only one digit so sum will be 0
		return (num / 10);//if we got to the last digit it's means that it is already in the sum(because of the previous entering to the recursion) 
	}
	else
	{
		sum += ((num % 100) / 10) + (partSum(num / 10));//we're summing only the digit before the last one
	}
	return sum;//returning the final sum of digits(without right digit)
}
/*The following function gets a number and puts it into a char array(string)*/
void intToStr(int num, char s[])
{
	if (num < 10)
	{
		s[FIRST_CELL] = (char)(num + ZERO_ASCII);//if 
		s[NEXT_CELL] = END_OF_STRING;//closing the string
	}
	else
	{
		intToStr(num / 10, s);//starting from the left digit of num
		s[strlen(s) + NEXT_CELL] = END_OF_STRING;//veryfing that the character will have space for entering
		s[strlen(s)] = (char)((num % 10) + ZERO_ASCII);//putting the next digit in the next cell
	}
}
/*The following function gets an array of integers(numbers[])with length n.
The function will update maxPrefixesArray[] that in maxPrefixesArray[i]
will be the highest number from the first i numbers in number[] */
void fillMaxPrefixesArray(int numbers[], int n, int maxPrefixesArray[])
{
	if (n == FIRST_CELL)//starting point
	{
		maxPrefixesArray[n] = numbers[n];//putting in the first cell the first value(you don't have something before it)
	}
	else
	{
		fillMaxPrefixesArray(numbers, n - NEXT_CELL, maxPrefixesArray);//getting to i=0
		if (n < MAX_INT_SIZE) {
			if (maxPrefixesArray[n - NEXT_CELL] > numbers[n])//checking who is bigger: the biggest number so fur or the next number from numbers[]
			{
				maxPrefixesArray[n] = maxPrefixesArray[n - NEXT_CELL];
			}
			else
			{
				maxPrefixesArray[n] = numbers[n];
			}
		}
	}
}

/*The following function gets an array of numbers(with size n).
The function will update the array that numbers[0] will have the smallest number of numbers[]*/
void getMinToStart(int numbers[], int n)
{
	int tmp;
	if (n == MIN_CELLS)//checking when you got to the last 2 cells
	{
		if (numbers[n - MIN_CELLS] > numbers[n - NEXT_CELL])//updating if the first cell is not the smallest cell
		{
			tmp = numbers[n - MIN_CELLS];
			numbers[n - MIN_CELLS] = numbers[n - NEXT_CELL];
			numbers[n - NEXT_CELL] = tmp;
		}
	}
	else
	{
		if (n == ONLY_ONE)
		{
			return;
		}
		else
		{
			if (numbers[n - NEXT_CELL] < numbers[n - MIN_CELLS])//updating if right first cell is the smaller cell
			{
				tmp = numbers[n - MIN_CELLS];
				numbers[n - MIN_CELLS] = numbers[n - NEXT_CELL];
				numbers[n - NEXT_CELL] = tmp;
			}
			getMinToStart(numbers, n - NEXT_CELL);
		}
	}
}

/*The following function gets 2 sorted arrays and combines them(sorted)*/
void combineArrays(int sortedArr1[], int size1, int sortedArr2[], int size2)
{
	if (size1 == NOTHING || size2 == NOTHING)
	{
		if (size1 == NOTHING && size2 == NOTHING)
		{
			return;//if both equal to 0 -> it means you finished
		}
		if (size1 != NOTHING)
		{//continue to put in arr1 into arr2
			sortedArr2[size1 + size2 - NEXT_CELL] = sortedArr1[size1 - NEXT_CELL];
			return combineArrays(sortedArr1, size1 - NEXT_CELL, sortedArr2, size2);
		}
		if (size2 != NOTHING)
		{
			size2 = NOTHING;//if size2 equal to 0 -> it means you finished because all array1 is already in
			return combineArrays(sortedArr1, size1, sortedArr2, size2);
		}

	}
	else
	{

		if (sortedArr1[size1 - 1] == sortedArr2[size2 - 1])
		{//put only the arr1 into arr2(you can do both but it can be source for problems with size calculation)
			sortedArr2[size1 + size2 - NEXT_CELL] = sortedArr1[size1 - NEXT_CELL];
			return combineArrays(sortedArr1, size1 - NEXT_CELL, sortedArr2, size2);
		}
		if (sortedArr1[size1 - NEXT_CELL] < sortedArr2[size2 - NEXT_CELL])
		{
			sortedArr2[size1 + size2 - NEXT_CELL] = sortedArr2[size2 - NEXT_CELL];
			return combineArrays(sortedArr1, size1, sortedArr2, size2 - NEXT_CELL);
		}
		if (sortedArr1[size1 - NEXT_CELL] > sortedArr2[size2 - NEXT_CELL])
		{
			sortedArr2[size1 + size2 - NEXT_CELL] = sortedArr1[size1 - NEXT_CELL];
			return combineArrays(sortedArr1, size1 - NEXT_CELL, sortedArr2, size2);
		}


	}
}
/*The following function gets an array, 2 indexes and number.
The function will return how many numbers in the array(between start to end) are smaller than number*/
int countSmaller(int arr[], int start, int end, int num)
{
	if (start > end)//cheking if the array is not empty
	{
		return NOTHING;
	}
	if (start == end)//checking if we got to the last cell
	{
		if (arr[start] < num)
		{
			return ONLY_ONE;
		}
		else
		{
			return NOTHING;
		}
	}
	if (arr[start] < num)//cheking if we can go one more cell
	{
		return ONLY_ONE + countSmaller(arr, start + NEXT_CELL, end, num);
	}
	else
	{
		return NOTHING;
	}
		

}
