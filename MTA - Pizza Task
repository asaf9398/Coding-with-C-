#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void main()
{
	printf("Welcome to MTA-Pizza!\n\n");
	int n = 5;//number of "*" in first line - can be changed to any prime number
	int space = 0;
	int id;
	for (int i = 1; i <= (n/2)+1; i++)//printing the piramade - running on rows
	{
		for (int j = 0; j < n-(space*2); j++)//running on all the * on one line
		{
			if (j == 0) // if j!=0 -> you have already put a space
			{
				for (int k = 0;k < space;k++)//putting space before the *
				{
					printf(" ");
				}
			}
			printf("*");
		}
		printf("\n");
		space++;
	}
	printf("Please enter your ID number:\n");
	scanf("%d",&id);
	printf("\n");
	while (id>999999999)//checking ID is valid - if not re enter the ID again
	{
		printf("The insereted ID is illegal\n");
		printf("Please enter your ID number again:\n");
		scanf("%d", &id);
	}
	printf("Our menu:\n");
	printf("*********\n");
	printf("Basic pizza: 60.00 NIS for 40x40 size pizza\n");
	printf("Toppings for basic size pizza:\n");
	printf("Olives: 10 NIS\n");
	printf("Mushrooms: 12 NIS\n\n");
	printf("Your order details:\n");
	printf("*******************\n");
	printf("ID number: %09d\n",id);//printing the ID in 9 numbers
	printf("Thank you for your order!");
}
