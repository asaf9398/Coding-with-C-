#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define origPizzasWidth 40.0//pizzas width constant value
#define origPizzasLength 40.0//pizzas length constant value
#define origPizzasSize origPizzasLength*origPizzasWidth//pizzas size constant value
#define origPizzaPrice 60.0//pizzas price constant value
#define origDeliveryPrice 15.0//pizzas delivery price constant value
#define mushroomsPrice 12.0//mushrooms toping price constant value
#define olivesPrice 10.0//olives toping price constant value
#define tax 1.17//tax constant value
/*
	The program asks from the user :
	-ID 
	-Size of the pizza he wants
	-Amount of toppings
	-If he want delivery
	And returns his ID (9 digits) + reservation summary + total price of the pizza + the price with tax(17%)

*/
void main()
{
	printf("Welcome to MTA-Pizza!\n\n");
	
	//The next code is an automatic printing of piramade on screen(as big a you want) - is not being used(yet) because I belive we didn't learned it on class
	/*
	Printing general upside down piramade with any non parity number
	int n = 5;//number of "*" in first line - can be changed to any non parity number
	int space = 0;
	
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
	*/
	int id;
	printf("*****\n");
	printf(" ***\n");
	printf("  *\n\n");
	printf("Please enter your ID number:\n");
	scanf("%d",&id);//getting the ID from the user
	/*
	Checking ID validity
	while (id>999999999)//checking ID is valid - if not re enter the ID again
	{
		printf("The insereted ID is illegal\n");
		printf("Please enter your ID number again:\n");
		scanf("%d", &id);
	}
	*/
	printf("Our menu:\n");
	printf("*********\n");
	printf("Basic pizza: %.2lf NIS for %.0lfx%.0lf size pizza\n",origPizzaPrice,origPizzasLength,origPizzasWidth);
	printf("Toppings for basic size pizza:\n");
	printf("Olives: %.0lf NIS\n",olivesPrice);
	printf("Mushrooms: %.0lf NIS\n\n",mushroomsPrice);
	printf("Please enter your pizza's length (cm):");
	int length;
	scanf("\n%d", &length);//inserting pizza's length
	printf("Please enter your pizza's width (cm):");
	int width;
	scanf("\n%d", &width);//inserting pizza's width
	printf("\n");
	printf("Please choose the toppings: \n\n");		
	printf("Olives - Enter 1 for the whole pizza\n");
	printf("0.5 for half\n");
	printf("0.25 for quarter\n");
	printf("or 0 for none:");
	double olives;
	scanf("%lf", &olives);//inserting how much olives as toppings - calculated in double for total accurate price
	printf("\n");
	printf("Mushrooms - Enter 1 for the whole pizza\n");
	printf("0.5 for half\n");
	printf("0.25 for quarter\n");
	printf("or 0 for none:");
	double mushrooms;
	scanf("%lf", &mushrooms);//inserting how much mushrooms as toppings - calculated in double for total accurate price
	printf("\n");
	double delivery;
	printf("Do you want delivery for the price of %.0lf NIS? Enter 1 for delivery or 0 for pick-up:",origDeliveryPrice);
	scanf("%lf", &delivery);//inserting delivery 1/0 - calculated in double for total accurate price
	printf("\n");
	printf("Your order details:\n");
	printf("*******************\n");
	printf("ID number: %09d\n",id);//printing the ID in 9 numbers
	printf("Pizza size: %dx%d\n",length,width);//printing the pizzas size
	double toppingsPrice = (mushrooms * mushroomsPrice + olives * olivesPrice)*(width*length)/(origPizzasSize);//calculating topping's price
	double pizzasPrice = (length * width * origPizzaPrice) / (origPizzasSize);//calculating pizza's price - I've added .0 because length&width are integers -> now the price is more accurate
	double deliveryPrice = delivery * origDeliveryPrice;//calculating delivery price
	double price = toppingsPrice+pizzasPrice+deliveryPrice;//calculating price without tax
	printf("Total price: %.2lf\n", price);//printing price without tax(2 digits after the point)
	int priceWithTax = price * tax;//calculating total price
	printf("Total price with tax (rounded down): %d\n", priceWithTax);//printing total price
	printf("Thank you for your order!");
}
