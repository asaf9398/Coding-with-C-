#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ORIG_PIZZAS_WIDTH 40.0//pizzas width constant value
#define ORIG_PIZZAS_LENGTH 40.0//pizzas length constant value
#define ORIG_PIZZAS_SIZE ORIG_PIZZAS_LENGTH*ORIG_PIZZAS_WIDTH//pizzas size constant value
#define ORIG_PIZZA_PRICE 60.0//pizzas price constant value
#define ORIG_DELIVERY_PRICE 15.0//pizzas delivery price constant value
#define MUSHROOMS_PRICE 12.0//mushrooms toping price constant value
#define OLIVES_PRICE 10.0//olives toping price constant value
#define REGULAR_DOUGH_PRICE 0.0//regular dough price constant value
#define VEGAN_DOUGH_PRICE 5.0//vegan dough price constant value
#define WHOLE_WHEAT_PIZZA_PRICE 3.0//whole wheat dough price constant value
#define GLUTEN_FREE_DOUGH_PRICE 4.0//gluten free dough price constant value
#define SMALLEST_LEGAL_PIZZA_WIDTH 10//smallest legal pizza width constant value
#define MAX_LEGAL_PIZZA_WIDTH 80//max legal pizza width constant value
#define SMALLEST_LEGAL_PIZZA_LENGTH 10//smallest legal pizza length constant value
#define MAX_LEGAL_PIZZA_LENGTH 40//max legal pizza length constant value
#define REGULAR_PIZZA_DOUGH_SIGN 'r'//regular pizza dough sign constant value
#define VEGETERIAN_PIZZA_DOUGH_SIGN 'v'//vegan pizza dough sign constant value
#define WHOLE_WHEAT_PIZZA_DOUGH_SIGN 'w'//whole wheat pizza dough sign constant value
#define GLUTEN_FREE_PIZZA_DOUGH_SIGN 'f'//gluten free pizza dough sign constant value
#define HALF_PIZZA 0.5//half pizza calculation constant value
#define QUARTER_PIZZA 0.25//quarter pizza calculation constant value
#define TEN_ILS 10//ten ILS constant value
#define FIVE_ILS 5//five ILS constant value
#define TWO_ILS 2//two ILS constant value
#define ONE_ILS 1//one ILS constant value
#define WITH_DELIVERY 1//confirm delivery for calculation constant value
#define WITHOUT_DELIVERY 0//decline delivery for calculation constant value
#define NO_TOPPING 0//no toppings value (if the toppings combination is more than 1 pizza) constant value
#define TAX 1.17//tax constant value
/*
	The program asks from the user :
	-ID 
	-How many pizzas he wants
	-Size of the pizza he wants
	-Amount of toppings
	-If he want delivery
	And returns his ID (9 digits) + reservation summary + total price of the pizza + the price with TAX(17%)
	The program will also ask to pay from the user and if he has any change the program will print the change with the smallest coins option

*/

typedef struct pizza//creating a typedef of PIZZA that contains pizza struct
{
/*
This struct contains all the pizza's fields :
	price
	choice for mushrooms toppins
	choice for olives toppins
	choice for delivery
	choice for pizzas length
	choice for pizzas width
	choice for pizzas dough
*/
	double price;
	int mushrooms, olives, delivery,pizzaLength, pizzaWidth;
	char dough;
}PIZZA;
void main()
{
	printf(" Welcome to MTA-Pizza!\n\n");
	
	//The next code is an automatic printing of piramade on screen(as big a you want)
	//Printing general upside down piramade with any non parity number
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
	int id;
	printf("\n");
	printf("Please enter your ID number:\n");
	scanf("%d",&id);//getting the ID from the user
	printf("\n");
	printf("Our menu:\n");
	printf("*********\n");
	printf("Basic pizza: %.2lf NIS for %.0lfx%.0lf size pizza\n\n",ORIG_PIZZA_PRICE,ORIG_PIZZAS_LENGTH,ORIG_PIZZAS_WIDTH);
	printf("Toppings for basic size pizza:\n");
	printf("Olives: %.0lf NIS\n",OLIVES_PRICE);
	printf("Mushrooms: %.0lf NIS\n\n",MUSHROOMS_PRICE);
	printf("Dough type for basic size pizza:\n");
	printf("Regular: %.0lf NIS\n",REGULAR_DOUGH_PRICE);
	printf("Vegan: %.0lf NIS\n", VEGAN_DOUGH_PRICE);
	printf("Whole wheat: %.0lf NIS\n", WHOLE_WHEAT_PIZZA_PRICE);
	printf("Gluten free: %.0lf NIS\n\n", GLUTEN_FREE_DOUGH_PRICE);
	int numberOfPizzas;
	PIZZA pizza;//creating new struct of PIZZA
	printf("How many pizzas would you like to order? ");
	scanf(" %d", &numberOfPizzas);//getting number of pizzas from the user
	printf("\n\n");
	if (numberOfPizzas > 0)//if the user orders a positive number of pizzas we can continue . Else - get out
	{
		double totalPrice = 0;
		int k;
		for (k = 1;k <= numberOfPizzas;k++)//running about all the pizzas reservation template
		{
			printf("*************************************************\n");
			printf("Pizza #%d:\n\n",k);
			pizza.pizzaLength = 0, pizza.pizzaWidth = 0;//you don't want to save the last pizza length&width
			pizza.price = 0;//new pizza - new price calculation
			printf("Please enter your pizza's length (cm):");
			scanf(" %d", &pizza.pizzaLength);//inserting pizza's length
			printf("\n");
			if (pizza.pizzaLength < SMALLEST_LEGAL_PIZZA_LENGTH || pizza.pizzaLength> MAX_LEGAL_PIZZA_LENGTH||pizza.pizzaLength % 2 != 0)//checking about the pizza's length validity
			{
				printf("Invalid length! Basic length was chosen as a default.\n");
				pizza.pizzaLength = ORIG_PIZZAS_LENGTH;
			}
			printf("Please enter your pizza's width (cm):");
			scanf(" %d", &pizza.pizzaWidth);//inserting pizza's width
			printf("\n");
			if (pizza.pizzaWidth < SMALLEST_LEGAL_PIZZA_WIDTH || pizza.pizzaWidth> MAX_LEGAL_PIZZA_WIDTH || pizza.pizzaWidth % 2 != 0)//checking about the pizza's width validity
			{
				printf("Invalid width! Basic width was chosen as a default.\n");
				pizza.pizzaWidth = ORIG_PIZZAS_WIDTH;
			}
			printf("\n");
			printf("Please enter the pizza's dough type:\n");
			printf("r - for regular\n");
			printf("v - for vegan\n");
			printf("w - for whole wheat\n");
			printf("f - for gluten-free\n");
			scanf(" %c", &pizza.dough);//getting the pizza's dough type from the user
			if (pizza.dough != REGULAR_PIZZA_DOUGH_SIGN && pizza.dough != VEGETERIAN_PIZZA_DOUGH_SIGN && pizza.dough != WHOLE_WHEAT_PIZZA_DOUGH_SIGN && pizza.dough != GLUTEN_FREE_PIZZA_DOUGH_SIGN)//checking about the pizza's dough validity
			{
				printf("Invalid choice! Regular dough was chosen as a default.\n");
				pizza.dough = REGULAR_PIZZA_DOUGH_SIGN;
			}
			printf("\n");
			printf("Please choose the toppings: \n\n");
			printf("Olives (choose 0-3):\n");
			printf("0. None\n");
			printf("1. Whole pizza\n");
			printf("2. Half pizza\n");
			printf("3. Quarter pizza\n");
			scanf(" %d", &pizza.olives);//inserting how much olives as toppings - calculated in double for total accurate price
			if (!(pizza.olives >= 0 && pizza.olives <= 3))//checking about the pizza's olives amount validity
			{
				printf("Invalid choice! Current topping not added.");
				pizza.olives = 0;
			}
			printf("\n");
			printf("Mushrooms (choose 0-3):\n");
			printf("0. None\n");
			printf("1. Whole pizza\n");
			printf("2. Half pizza\n");
			printf("3. Quarter pizza\n");
			scanf(" %d", &pizza.mushrooms);//inserting how much mushrooms as toppings - calculated in double for total accurate price
			if (!(pizza.mushrooms >= 0 && pizza.mushrooms <= 3))//checking about the pizza's mushrooms amount validity
			{
				printf("Invalid choice! Current topping not added.\n");
				pizza.mushrooms = NO_TOPPING;
			}
			else
			{
				if ((pizza.olives == 1 && pizza.mushrooms >= 1)||(pizza.olives >=2&& pizza.mushrooms ==1))//checking about the pizza's maximum toppings amount
				{
					printf("You have exceeded the maximum amount of toppings allowed on one pizza! Current topping not added.\n");
					pizza.mushrooms = NO_TOPPING;//if the pizza is alredy full/has too much olives -> you can't put mushrooms on it
				}
			}
			printf("\n");
			pizza.price += ORIG_PIZZA_PRICE*(pizza.pizzaLength * pizza.pizzaWidth) / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);//calculation of pizzas price(only width&length)
			switch (pizza.mushrooms)//mushrooms topping calculation
			{
			case 0:
				break;
			case 1:
				pizza.price += MUSHROOMS_PRICE * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH*ORIG_PIZZAS_WIDTH);
				break;
			case 2:
				pizza.price += MUSHROOMS_PRICE*HALF_PIZZA * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			case 3:
				pizza.price += MUSHROOMS_PRICE * QUARTER_PIZZA * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			default:
				break;
			}
			switch (pizza.olives)//olives topping calculation
			{
			case 0:
				break;
			case 1:
				pizza.price += OLIVES_PRICE * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			case 2:
				pizza.price += OLIVES_PRICE * HALF_PIZZA * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			case 3:
				pizza.price += OLIVES_PRICE * QUARTER_PIZZA * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			default:
				break;
			}
			switch (pizza.dough)//dough topping calculation
			{
			case REGULAR_PIZZA_DOUGH_SIGN:
				break;
			case VEGETERIAN_PIZZA_DOUGH_SIGN:
				pizza.price += VEGAN_DOUGH_PRICE * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			case WHOLE_WHEAT_PIZZA_DOUGH_SIGN:
				pizza.price += WHOLE_WHEAT_PIZZA_PRICE * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			case GLUTEN_FREE_PIZZA_DOUGH_SIGN:
				pizza.price += GLUTEN_FREE_DOUGH_PRICE * pizza.pizzaLength * pizza.pizzaWidth / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
				break;
			default:
				break;
			}
			printf("Pizza #%d details:\n",k);
			printf("*******************\n");
			printf("Pizza size: %dx%d\n",pizza.pizzaLength,pizza.pizzaWidth);
			printf("Pizza price (without tax): %.2lf\n\n", pizza.price);
			totalPrice += pizza.price;//adding the specific pizza's price to the reservation total price
		}
		double delivery;
		printf("*************************************************\n");
		printf("Do you want delivery for the price of %.0lf NIS? Enter %d for delivery or %d for pick-up:", ORIG_DELIVERY_PRICE,WITH_DELIVERY,WITHOUT_DELIVERY);
		scanf(" %lf", &delivery);//inserting delivery 1/0 - calculated in double for total accurate price
		printf("\n");
		if (delivery != WITHOUT_DELIVERY && delivery != WITH_DELIVERY)//checking if delivery input is invalid
		{
			printf("Invalid choice! Pick-up was chosen as a default.\n");
			delivery = WITHOUT_DELIVERY;
		}
		//printing all reservation details
		printf("\n");
		printf("Your order details:\n");
		printf("*******************\n");
		printf("ID number: %09d\n", id);//printing the ID in 9 numbers
		printf("Number of pizzas: %d\n", numberOfPizzas);//printing the pizzas size
		double deliveryPrice = delivery * ORIG_DELIVERY_PRICE;//calculating delivery price
		totalPrice += deliveryPrice;//calculating price without TAX
		printf("Total price: %.2lf\n", totalPrice);//printing price without TAX(2 digits after the point)
		int priceWithTAX = totalPrice * TAX;//calculating total price
		printf("Total price with tax (rounded down): %d\n\n", priceWithTAX);//printing total price
		double payment,remaining;
		printf("Please enter your payment:");
		scanf(" %lf", &payment);
		printf("\n");
		remaining = priceWithTAX - payment;//precalculation for the change calculation
		while (remaining>0)//if the user need to pay more the loop will enter until the user will pay at least the reservation total price
		{
			printf("Your remaining balance is: %.0lf\n",remaining);
			printf("Please enter your payment: ");
			scanf("%lf", &payment);
			printf("\n");
			remaining -= payment;

		}
		if (remaining < 0)//if the user had paid more than the reservation total price he need to get change
		{
			int change = (int)(remaining) * (-1);//calculation for the absulut value for the change(if remaining<0 -> change=Math.abs(remaining))
			printf("Your change is %d NIS using:\n", change);
			if (change >= TEN_ILS)//checking if the change is at least ten ILS 
			{
				printf("%d coin(s) of ten\n",change/TEN_ILS);
				change = change % TEN_ILS;//calculating the remaining change
			}
			if (change>=FIVE_ILS)//checking if the change is at least five ILS 
			{
				printf("%d coin(s) of five\n", change / FIVE_ILS);
				change = change % FIVE_ILS;//calculating the remaining change
			}
			if (change >= TWO_ILS)//checking if the change is at least two ILS 
			{
				printf("%d coin(s) of two\n", change / TWO_ILS);
				change = change % TWO_ILS;//calculating the remaining change
			}
			if (change >= ONE_ILS)//checking if the change is at least one ILS 
			{
				printf("%d coin(s) of one\n", change / ONE_ILS);
				change = change % ONE_ILS;//calculating the remaining change
			}

		}
		printf("Thank you for your order!");//ending the program after payment&change has been calculated and paid
	}
	else//if the number of pizzas that the user wants to order is not positive -> the program will get out
	{
		printf("Thank you and goodbye.");
	}
}
