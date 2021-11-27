//ID 319094322 Asaf Yosef
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define PIZZA_LOGO_SIZE 5
#define ORIG_PIZZAS_WIDTH 50.0//pizzas width constant value
#define ORIG_PIZZAS_LENGTH 40.0//pizzas length constant value
#define ORIG_PIZZAS_SIZE ORIG_PIZZAS_LENGTH*ORIG_PIZZAS_WIDTH//pizzas size constant value
#define ORIG_PIZZA_PRICE 70.0//pizzas price constant value
#define ORIG_DELIVERY_PRICE 15.0//pizzas delivery price constant value
#define ORIG_NO_DELIVERY_PRICE 0.0//pizzas no delivery price constant value
#define FREE_PIZZA 0.0//the first price of pizza before calculaing
#define MUSHROOMS_PRICE 12.0//mushrooms toping price constant value
#define OLIVES_PRICE 10.0//olives toping price constant value
#define TOMATOES_PRICE 9.0//tomatoes toping price constant value
#define PINEAPLLE_PRICE 14.0//pineapple toping price constant value
#define REGULAR_DOUGH_PRICE 0.0//regular dough price constant value
#define VEGAN_DOUGH_PRICE 5.0//vegan dough price constant value
#define MAX_LEGAL_ID 999999999//the biggest legal value for ID 
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
#define FULL_PIZZA 1.0//full pizza calculation constant value
#define HALF_PIZZA 0.5//half pizza calculation constant value
#define QUARTER_PIZZA 0.25//quarter pizza calculation constant value
#define TEN_ILS 10//ten ILS constant value
#define FIVE_ILS 5//five ILS constant value
#define TWO_ILS 2//two ILS constant value
#define ONE_ILS 1//one ILS constant value
#define NO_CHARGE 0 //the price for things that not cost money - as regular doguh(for calculation-multiplying by one)
#define WITH_DELIVERY 1//confirm delivery for calculation constant value
#define WITHOUT_DELIVERY 0//decline delivery for calculation constant value
#define NO_TOPPING 0//no toppings value (if the toppings combination is more than 1 pizza) constant value
#define NO_TOPPING_SIGN ' '//no toping sign
#define TOO_MUCH_TOPPINGS false
#define OLIVES_TOPPING_SIGN 'O'//olives topping sign
#define MUSHROOMS_TOPPING_SIGN 'M'//mushrooms topping sign
#define TOMATOES_TOPPING_SIGN 'T'//tomatoes topping sign
#define PINEAPPLE_TOPPING_SIGN 'P'//pineapple topping sign
#define TAX 1.17//tax constant value
#define FOUR_QUARTERS 4//same topping for all pizza
#define TWO_QUARTERS 2//same topping for half pizza
#define ONE_QUARTERS 1//same topping for quarter pizza
typedef struct pizza//creating a typedef of PIZZA that contains pizza struct
{
	/*
	This struct contains all the pizza's fields :
		price
		amount of toppings that has been already chosen
		every quarter and it's topping
		choice for delivery
		choice for pizzas length
		choice for pizzas width
		choice for pizzas dough
	*/
	double price,amountOfToppings;
	int mushrooms, olives, delivery,pineapple,tomatoes, pizzaLength, pizzaWidth;
	char dough, firstQuarterTopping, secondQuarterTopping, thirdQuarterTopping, fourthQuarterTopping;
}PIZZA;

typedef struct person 
{	/*
	This struct contains all the customer's details:
		ID
		Number of pizzas
		If the customer wants delivery
		Total price of the order
	*/
	int id, numberOfPizzas,delivery;
	double totalPrice;
}PERSON;

void opening();
void printPizzaLogo(int pizzaSize);
int enteringId();
bool checkId(int id);
int checkIdDigit(int id);
void printMenu();
int startingToOrder();
double orderingPizzas(int numberOfPizzas, PIZZA pizza);
PIZZA settingPizzaLength(PIZZA pizza);
PIZZA settingPizzaWidth(PIZZA pizza);
PIZZA settingDoughType(PIZZA pizza);
PIZZA setToppings(PIZZA pizza);
PIZZA setToppingOlives(PIZZA pizza, bool isOK);
PIZZA setToppingMushrooms(PIZZA pizza,bool isOK);
PIZZA setToppingTomatoes(PIZZA pizza, bool isOK);
PIZZA setToppingPineapples(PIZZA pizza, bool isOK);
PIZZA setPizzaQuarters(PIZZA pizza, int quarters, char toppingSign);
void printLine(char ch, int numOfTimes);
PIZZA printPizzaDetails(PIZZA pizza);
double getDoughPrice(char doughType);
double pizzaSizePriceCalculation(PIZZA pizza);
double pizzaDoughPriceCalculation(PIZZA pizza);
PIZZA calculatePizzaPrice(PIZZA pizza);
PERSON deliveryOption(PERSON man);
void payment(int price);
void printOrderDetails(PERSON man);
PIZZA initializingPizza(PIZZA pizza);
void main()
{
	PERSON man;
	opening();
	man.id = enteringId();
	printMenu();
	man.numberOfPizzas=startingToOrder();
	PIZZA pizza = {FREE_PIZZA,NO_TOPPING,NO_TOPPING,NO_TOPPING,ORIG_NO_DELIVERY_PRICE,NO_TOPPING,NO_TOPPING,ORIG_PIZZAS_LENGTH,ORIG_PIZZAS_WIDTH,REGULAR_PIZZA_DOUGH_SIGN,NO_TOPPING_SIGN,NO_TOPPING_SIGN,NO_TOPPING_SIGN,NO_TOPPING_SIGN};
	man.totalPrice=orderingPizzas(man.numberOfPizzas,pizza);
	man= deliveryOption(man);
	printOrderDetails(man);
	int priceWithTax = (int)(man.totalPrice * TAX);
	payment(priceWithTax);
}
 //The following function initialize pizza to original values - everything becomes to be the default values
PIZZA initializingPizza(PIZZA pizza)
{
	pizza.amountOfToppings = NO_TOPPING;
	pizza.dough = REGULAR_PIZZA_DOUGH_SIGN;
	pizza.firstQuarterTopping = NO_TOPPING_SIGN;
	pizza.secondQuarterTopping = NO_TOPPING_SIGN;
	pizza.thirdQuarterTopping = NO_TOPPING_SIGN;
	pizza.fourthQuarterTopping = NO_TOPPING_SIGN;
	pizza.pizzaLength = ORIG_PIZZAS_LENGTH;
	pizza.pizzaWidth = ORIG_PIZZAS_WIDTH;
	pizza.price = FREE_PIZZA;
	pizza.delivery = ORIG_NO_DELIVERY_PRICE;
	pizza.tomatoes = NO_TOPPING;
	pizza.olives = NO_TOPPING;
	pizza.pineapple = NO_TOPPING;
	pizza.mushrooms = NO_TOPPING;
	return pizza;
}
//The following function gets the price and asking from the user to pay the bill
void payment(int price)
{
	int remaining = price;
	int payment;
	printf("\n");
	printf("Please enter your payment: ");
	scanf("%d", &payment);
	remaining -= payment;
	while (remaining > 0)
	{
		printf("Your remaining balance is : %d\n", remaining);
		printf("Please enter your payment: ");
		scanf("%d", &payment);
		printf("\n");
		remaining -= payment;
	}
	if (remaining < 0)//happens only if the customer need to get change
	{
		remaining = remaining * (-1);
		printf("Your change is %d NIS using:\n", remaining);
		if (remaining/TEN_ILS!=0)
		{
			printf("%d coin(s) of ten\n", remaining / TEN_ILS);
			remaining = remaining % TEN_ILS;
		}
		if (remaining / FIVE_ILS != 0)
		{
			printf("%d coin(s) of five\n", remaining / FIVE_ILS);
			remaining = remaining % FIVE_ILS;
		}
		if (remaining / TWO_ILS != 0)
		{
			printf("%d coin(s) of two\n", remaining / TWO_ILS);
			remaining = remaining % TWO_ILS;
		}
		if (remaining / ONE_ILS != 0)
		{
			printf("%d coin(s) of one\n", remaining / ONE_ILS);
			remaining = remaining % ONE_ILS;
		}	
	}
	printf("Thank you for your order!\n");
}
//The following function gets the customer and prints the order details
void printOrderDetails(PERSON man)
{
	printf("Your order details:\n");
	printLine('*',19);
	printf("ID number: %09d\n", man.id);
	printf("Number of pizzas: %d\n", man.numberOfPizzas);
	if (man.delivery == WITH_DELIVERY)
	{
		printf("Delivery\n");
	}
	else 
	{
		printf("Pick-Up\n");
	}
	printf("Total price: %.2lf\n", man.totalPrice);
	int priceWithTax = (int)((man.totalPrice) * TAX);
	printf("Total price with tax (rounded down): %d\n", priceWithTax);
	


}
//The following function gets the pizza struct and inserting in it the length of the pizza(by the definition)
PIZZA settingPizzaLength(PIZZA pizza)
{
	printf("Please enter your pizza's length (cm): ");
	scanf(" %d", &pizza.pizzaLength);//inserting pizza's length

	while (pizza.pizzaLength < SMALLEST_LEGAL_PIZZA_LENGTH || pizza.pizzaLength> MAX_LEGAL_PIZZA_LENGTH || pizza.pizzaLength % 2 != 0)//checking about the pizza's length validity
	{
		printf("Invalid length! Try again.\n");
		printf("Please enter your pizza's length (cm): ");
		scanf(" %d", &pizza.pizzaLength);//inserting pizza's length
	}
	return pizza;
}
//The following function gets the pizza struct and inserting in it the width of the pizza(by the definition)
PIZZA settingPizzaWidth(PIZZA pizza)
{
	printf("Please enter your pizza's width (cm): ");
	scanf(" %d", &pizza.pizzaWidth);//inserting pizza's width

	while (pizza.pizzaWidth < SMALLEST_LEGAL_PIZZA_WIDTH || pizza.pizzaWidth> MAX_LEGAL_PIZZA_WIDTH || pizza.pizzaWidth % 2 != 0)//checking about the pizza's width validity
	{
		printf("Invalid width! Try again.\n");
		printf("Please enter your pizza's width (cm): ");
		scanf(" %d", &pizza.pizzaWidth);//inserting pizza's length
	}
	return pizza;
}
//The following function gets the pizza struct and inserting in it the dough type of the pizza(by the definition)
PIZZA settingDoughType(PIZZA pizza)
{
	printf("\n");
	printf("Please enter the pizza's dough type:\n");
	printf("r - for regular\n");
	printf("v - for vegan\n");
	printf("w - for whole wheat\n");
	printf("f - for gluten-free\n");
	scanf(" %c", &pizza.dough);//getting the pizza's dough type from the user
	while (pizza.dough != REGULAR_PIZZA_DOUGH_SIGN && pizza.dough != VEGETERIAN_PIZZA_DOUGH_SIGN && pizza.dough != WHOLE_WHEAT_PIZZA_DOUGH_SIGN && pizza.dough != GLUTEN_FREE_PIZZA_DOUGH_SIGN)//checking about the pizza's dough validity
	{
		printf("Invalid choice! Try again.\n");
		printf("\n");
		printf("Please enter the pizza's dough type:\n");
		printf("r - for regular\n");
		printf("v - for vegan\n");
		printf("w - for whole wheat\n");
		printf("f - for gluten-free\n");
		scanf(" %c", &pizza.dough);//getting the pizza's dough type from the user
	}
	return pizza;
}
//The following function checks where to put the toppings(by order)
PIZZA setPizzaQuarters(PIZZA pizza, int quarters, char toppingSign)
{
	if (pizza.firstQuarterTopping == NO_TOPPING_SIGN && quarters > 0)
	{
		pizza.firstQuarterTopping = toppingSign;
		quarters--;
	}
	if (pizza.secondQuarterTopping == NO_TOPPING_SIGN && quarters > 0)
	{
		pizza.secondQuarterTopping = toppingSign;
		quarters--;
	}
	if (pizza.thirdQuarterTopping == NO_TOPPING_SIGN && quarters > 0)
	{
		pizza.thirdQuarterTopping = toppingSign;
		quarters--;
	}
	if (pizza.fourthQuarterTopping == NO_TOPPING_SIGN && quarters > 0)
	{
		pizza.fourthQuarterTopping = toppingSign;
		quarters--;
	}
	return pizza;

}
//The following function gets the pizza struct and validity to the topping situation - and inserting in it the option of the customer to put olives on his pizza(by definition) 
PIZZA setToppingOlives(PIZZA pizza, bool ifOk)
{
	if (pizza.amountOfToppings < FOUR_QUARTERS)//checking if the pizza is not already full
	{
		printf("\n");
		printf("Please choose the toppings: \n\n");
		if (ifOk)
		{
			printf("Olives (choose 0-3):\n");
		}
		else
		{
			printf("\n");
		}
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
		switch (pizza.olives)
		{
		case 1:
			if (pizza.amountOfToppings + FOUR_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += FOUR_QUARTERS;
				pizza = setPizzaQuarters(pizza,FOUR_QUARTERS,OLIVES_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.olives = NO_TOPPING;
				pizza = setToppingOlives(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 2:
			if (pizza.amountOfToppings + TWO_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += TWO_QUARTERS;
				pizza = setPizzaQuarters(pizza, TWO_QUARTERS, OLIVES_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.olives = NO_TOPPING;
				pizza = setToppingOlives(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 3:
			if (pizza.amountOfToppings + ONE_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += ONE_QUARTERS;
				pizza = setPizzaQuarters(pizza, ONE_QUARTERS, OLIVES_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.olives = NO_TOPPING;
				pizza = setToppingOlives(pizza, TOO_MUCH_TOPPINGS);
			}
			break;

		default:
			break;
		}
		return pizza;
		
	}
	else 
		return pizza;

}
//The following function gets the pizza struct and validity to the topping situation - and inserting in it the option of the customer to put mushrooms on his pizza(by definition) 
PIZZA setToppingMushrooms(PIZZA pizza,bool isOk)
{
	if (pizza.amountOfToppings < FOUR_QUARTERS)//checking if the pizza is not already full
	{
		if (isOk) 
		{
		printf("Mushrooms (choose 0-3):\n");
		}
		else
		{
			printf("\n");
		}
		printf("0. None\n");
		printf("1. Whole pizza\n");
		printf("2. Half pizza\n");
		printf("3. Quarter pizza\n");
		scanf(" %d", &pizza.mushrooms);//inserting how much mushrooms as toppings - calculated in double for total accurate price
		if (!(pizza.mushrooms >= 0 && pizza.mushrooms <= 3))//checking about the pizza's mushrooms amount validity
		{
			printf("Invalid choice! Current topping not added.");
			pizza.mushrooms = 0;
		}
		switch (pizza.mushrooms)
		{
		case 1:
			if (pizza.amountOfToppings + FOUR_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += FOUR_QUARTERS;
				pizza = setPizzaQuarters(pizza, FOUR_QUARTERS, MUSHROOMS_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.mushrooms = NO_TOPPING;
				pizza=setToppingMushrooms(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 2:
			if (pizza.amountOfToppings + TWO_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += TWO_QUARTERS;
				pizza = setPizzaQuarters(pizza, TWO_QUARTERS, MUSHROOMS_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.mushrooms = NO_TOPPING;
				pizza = setToppingMushrooms(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 3:
			if (pizza.amountOfToppings + ONE_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += ONE_QUARTERS;
				pizza = setPizzaQuarters(pizza, ONE_QUARTERS, MUSHROOMS_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.mushrooms = NO_TOPPING;
				pizza = setToppingMushrooms(pizza,TOO_MUCH_TOPPINGS);
			}
			break;

		default:
			break;
		}
		return pizza;

	}
	else
		return pizza;

}
//The following function gets the pizza struct and validity to the topping situation - and inserting in it the option of the customer to put tomatos on his pizza(by definition) 
PIZZA setToppingTomatoes(PIZZA pizza,bool isOk)
{
	if (pizza.amountOfToppings < FOUR_QUARTERS)//checking if the pizza is not already full
	{
		if (isOk)
		{
			printf("Tomatos (choose 0-3):\n");
		}
		else
		{
			printf("\n");
		}
		printf("0. None\n");
		printf("1. Whole pizza\n");
		printf("2. Half pizza\n");
		printf("3. Quarter pizza\n");
		scanf(" %d", &pizza.tomatoes);//inserting how much tomatoes as toppings - calculated in double for total accurate price
		if (!(pizza.tomatoes >= 0 && pizza.tomatoes <= 3))//checking about the pizza's tomatoes amount validity
		{
			printf("Invalid choice! Current topping not added.");
			pizza.tomatoes = 0;
		}
		switch (pizza.tomatoes)
		{
		case 1:
			if (pizza.amountOfToppings + FOUR_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += FOUR_QUARTERS;
				pizza = setPizzaQuarters(pizza, FOUR_QUARTERS, TOMATOES_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.tomatoes = NO_TOPPING;
				pizza = setToppingTomatoes(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 2:
			if (pizza.amountOfToppings + TWO_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += TWO_QUARTERS;
				pizza = setPizzaQuarters(pizza, TWO_QUARTERS, TOMATOES_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.tomatoes = NO_TOPPING;
				pizza = setToppingTomatoes(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 3:
			if (pizza.amountOfToppings + ONE_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += ONE_QUARTERS;
				pizza = setPizzaQuarters(pizza, ONE_QUARTERS, TOMATOES_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.tomatoes = NO_TOPPING;
				pizza = setToppingTomatoes(pizza,TOO_MUCH_TOPPINGS);
			}
			break;

		default:
			break;
		}
		return pizza;

	}
	else
		return pizza;
}
//The following function gets the pizza struct and validity to the topping situation - and inserting in it the option of the customer to put pineapples on his pizza(by definition) 
PIZZA setToppingPineapples(PIZZA pizza,bool isOk)
{
	if (pizza.amountOfToppings < FOUR_QUARTERS)//checking if the pizza is not already full
	{
		if (isOk)
		{
			printf("Pineapple (choose 0-3):\n");
		}
		else
		{
			printf("\n");
		}
		printf("0. None\n");
		printf("1. Whole pizza\n");
		printf("2. Half pizza\n");
		printf("3. Quarter pizza\n");
		scanf(" %d", &pizza.pineapple);//inserting how much pineapple as toppings - calculated in double for total accurate price
		if (!(pizza.pineapple >= 0 && pizza.pineapple <= 3))//checking about the pizza's pineapple amount validity
		{
			printf("Invalid choice! Current topping not added.");
			pizza.pineapple = 0;
		}
		switch (pizza.pineapple)
		{
		case 1:
			if (pizza.amountOfToppings + FOUR_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += FOUR_QUARTERS;
				pizza = setPizzaQuarters(pizza, FOUR_QUARTERS, PINEAPPLE_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.pineapple = NO_TOPPING;
				pizza = setToppingPineapples(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 2:
			if (pizza.amountOfToppings + TWO_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += TWO_QUARTERS;
				pizza = setPizzaQuarters(pizza, TWO_QUARTERS, PINEAPPLE_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.pineapple = NO_TOPPING;
				pizza = setToppingPineapples(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		case 3:
			if (pizza.amountOfToppings + ONE_QUARTERS <= FOUR_QUARTERS)//checking if the pizza won't be full
			{
				pizza.amountOfToppings += ONE_QUARTERS;
				pizza = setPizzaQuarters(pizza, ONE_QUARTERS, PINEAPPLE_TOPPING_SIGN);
			}
			else
			{
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.");
				pizza.pineapple = NO_TOPPING;
				pizza = setToppingPineapples(pizza,TOO_MUCH_TOPPINGS);
			}
			break;
		default:
			break;
		}
		return pizza;

	}
	else
		return pizza;
}
//The following function checks after entering all toppings who is not set and sets it to NO_TOPPING_SIGN
PIZZA setLeftOversOfQuarters(PIZZA pizza)
{
	switch (pizza.firstQuarterTopping)
	{case OLIVES_TOPPING_SIGN:
		break;
	case MUSHROOMS_TOPPING_SIGN:
		break;
	case PINEAPPLE_TOPPING_SIGN:
		break;
	case TOMATOES_TOPPING_SIGN:
		break;
	default:
		pizza.firstQuarterTopping = NO_TOPPING_SIGN;//if quarter does not has any topping put the no topping sign
		break;
	}
	switch (pizza.secondQuarterTopping)
	{
	case OLIVES_TOPPING_SIGN:
		break;
	case MUSHROOMS_TOPPING_SIGN:
		break;
	case PINEAPPLE_TOPPING_SIGN:
		break;
	case TOMATOES_TOPPING_SIGN:
		break;
	default:
		pizza.secondQuarterTopping = NO_TOPPING_SIGN;//if quarter does not has any topping put the no topping sign
		break;
	}
	switch (pizza.thirdQuarterTopping)
	{
	case OLIVES_TOPPING_SIGN:
		break;
	case MUSHROOMS_TOPPING_SIGN:
		break;
	case PINEAPPLE_TOPPING_SIGN:
		break;
	case TOMATOES_TOPPING_SIGN:
		break;
	default:
		pizza.thirdQuarterTopping = NO_TOPPING_SIGN;//if quarter does not has any topping put the no topping sign
		break;
	}
	switch (pizza.fourthQuarterTopping)
	{
	case OLIVES_TOPPING_SIGN:
		break;
	case MUSHROOMS_TOPPING_SIGN:
		break;
	case PINEAPPLE_TOPPING_SIGN:
		break;
	case TOMATOES_TOPPING_SIGN:
		break;
	default:
		pizza.fourthQuarterTopping = NO_TOPPING_SIGN;//if quarter does not has any topping put the no topping sign
		break;
	}
	return pizza;
}
//The fullowing function gets the struct of pizza and initiates the other functions of putting toppings on the pizza 
//The function returns the updated pizza
PIZZA setToppings(PIZZA pizza)
{
	pizza.amountOfToppings = NO_TOPPING;
	pizza = setToppingOlives(pizza,true);
	if(pizza.amountOfToppings<4)
	{ 
		printf("\n");
	}	
	pizza = setToppingMushrooms(pizza,true);
	if (pizza.amountOfToppings < 4)
	{
		printf("\n");
	}
	pizza = setToppingTomatoes(pizza,true);
	if (pizza.amountOfToppings < 4)
	{
		printf("\n");
	}
	pizza = setToppingPineapples(pizza,true);
	if (pizza.amountOfToppings < 4)
	{
		printf("\n");
	}
	pizza = setLeftOversOfQuarters(pizza);
	return pizza;
}
/*The following funtion gets a char and number of times to print it and prints a line of this character*/
void printLine(char ch, int numOfTimes)
{
	for (int i = 0;i < numOfTimes;i++)
	{
		printf("%c", ch);
	}
	printf("\n");
}
//The following fucntion gets a dough type and returns its price
double getDoughPrice(char doughType) 
{
	switch (doughType)
	{
	case REGULAR_PIZZA_DOUGH_SIGN:
		return REGULAR_DOUGH_PRICE;
	case VEGETERIAN_PIZZA_DOUGH_SIGN:
		return VEGAN_DOUGH_PRICE;
	case WHOLE_WHEAT_PIZZA_DOUGH_SIGN:
		return WHOLE_WHEAT_PIZZA_PRICE;
	case GLUTEN_FREE_PIZZA_DOUGH_SIGN:
		return GLUTEN_FREE_DOUGH_PRICE;
	default:
		return REGULAR_DOUGH_PRICE;
		break;
	}
}
//The following function gets the size of the pizza and returns only the pizza price by size
double pizzaSizePriceCalculation(PIZZA pizza)
{
	return ORIG_PIZZA_PRICE*(pizza.pizzaLength * pizza.pizzaWidth) / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
}
//The following function gets the dough type of the pizza and returns only the pizza price by size&dough
double pizzaDoughPriceCalculation(PIZZA pizza)
{
	return getDoughPrice(pizza.dough) * (pizza.pizzaLength * pizza.pizzaWidth) / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
}

//The following function gets a topping and returns its price 
double getToppingPrice(char topping)
{
	switch (topping)
	{
	case NO_TOPPING_SIGN:
		return NO_CHARGE;
	case OLIVES_TOPPING_SIGN:
		return OLIVES_PRICE;
	case MUSHROOMS_TOPPING_SIGN:
		return MUSHROOMS_PRICE;
	case PINEAPPLE_TOPPING_SIGN:
		return PINEAPLLE_PRICE;
	case TOMATOES_TOPPING_SIGN:
		return TOMATOES_PRICE;
	default:
		return NO_CHARGE;
		break;
	}
}
//The following function gets the quarters topping and returns only the pizza price by size&topping
double pizzaFirstQuarterPriceCalculation(PIZZA pizza)
{
	return (QUARTER_PIZZA * getToppingPrice(pizza.firstQuarterTopping) * (pizza.pizzaLength * pizza.pizzaWidth)) / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
}
//The following function gets the quarters topping and returns only the pizza price by size&topping
double pizzaSecondQuarterPriceCalculation(PIZZA pizza)
{
	return (QUARTER_PIZZA * getToppingPrice(pizza.secondQuarterTopping) * (pizza.pizzaLength * pizza.pizzaWidth)) / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
}
//The following function gets the quarters topping and returns only the pizza price by size&topping
double pizzaThirdQuarterPriceCalculation(PIZZA pizza)
{
	return (QUARTER_PIZZA * getToppingPrice(pizza.thirdQuarterTopping) * (pizza.pizzaLength * pizza.pizzaWidth)) / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
}
//The following function gets the quarters topping and returns only the pizza price by size&topping
double pizzaFourthQuarterPriceCalculation(PIZZA pizza)
{
	return (QUARTER_PIZZA * getToppingPrice(pizza.fourthQuarterTopping) * (pizza.pizzaLength * pizza.pizzaWidth)) / (ORIG_PIZZAS_LENGTH * ORIG_PIZZAS_WIDTH);
}
//The following fucntion gets a pizza and updates it's price
PIZZA calculatePizzaPrice(PIZZA pizza)
{
	double totalPizzaPrice = 0;
	totalPizzaPrice += pizzaSizePriceCalculation(pizza);//calculation of price by length&width
	totalPizzaPrice += pizzaDoughPriceCalculation(pizza);//calculation of price by length&width
	totalPizzaPrice += pizzaFirstQuarterPriceCalculation(pizza);//calculation of the topping price for first quarter
	totalPizzaPrice += pizzaSecondQuarterPriceCalculation(pizza);//calculation of the topping price for second quarter
	totalPizzaPrice += pizzaThirdQuarterPriceCalculation(pizza);//calculation of the topping price for thirs quarter
	totalPizzaPrice += pizzaFourthQuarterPriceCalculation(pizza);//calculation of the topping price for fourth quarter
	pizza.price = totalPizzaPrice;
	return pizza;
}
//The following function gets a X,Y point and retuns which quarter you are at
int whichQuarterAmI(int x, int y,PIZZA pizza)
{
	if (x <= (pizza.pizzaWidth-2) / 2)//checking where are you in X
	{
		if (y <= (pizza.pizzaLength-2) / 2)//checking where are you in Y
			return 4;
		else
		{
			return 3;
		}
	}
	else
	{
		if (y <= (pizza.pizzaLength - 2) / 2)//checking where are you in Y
			return 1;
		else
		{
			return 2;
		}

	}
}
//The following function gets a quarter number and returns the topping char
char whichToppingIsIt(int quarter,PIZZA pizza)
{
	switch (quarter)
	{
	case 1:
		return pizza.firstQuarterTopping;
	case 2:
		return pizza.secondQuarterTopping;
	case 3:
		return pizza.thirdQuarterTopping;
	case 4:
		return pizza.fourthQuarterTopping;
	default:
		return NO_TOPPING_SIGN;
		break;
	}
	
}
//The following function gets a pizza and prints it by length&width - with dough type and toppings
void printPizza(PIZZA pizza)
{
	int i, k;
	printLine(pizza.dough,pizza.pizzaWidth);
	for (i = 1;i <= pizza.pizzaLength-2;i++)
	{
		printf("%c", pizza.dough);
		for (k = 1;k <= pizza.pizzaWidth-2;k++)
		{
			printf("%c", whichToppingIsIt(whichQuarterAmI(k, i, pizza), pizza));//getting the specific topping char
   		}
		printf("%c\n",pizza.dough);
	}
	printLine(pizza.dough, pizza.pizzaWidth);
}
//The following function prints the specific pizza details
PIZZA printPizzaDetails(PIZZA pizza)
{
	printf("Pizza size: %dx%d\n", pizza.pizzaLength, pizza.pizzaWidth);
	pizza = calculatePizzaPrice(pizza);
	printf("Pizza price (without tax): %.2lf\n", pizza.price);
	printPizza(pizza);
	printf("\n");
	return pizza;
}
//The following function gets the number of pizzas that the user enters and doing a loop for entering pizza data and returns the sum of pizzas prices 
double orderingPizzas(int numberOfPizzas,PIZZA pizza)
{
	int i;
	double totalPrice = 0;
	for (  i = 1; i <=numberOfPizzas; i++)
	{
		printf("*************************************************\n");
		printf("Pizza #%d:\n\n", i);
		pizza = settingPizzaLength(pizza);//using other functions to set pizza's length
		pizza = settingPizzaWidth(pizza);//using other functions to set pizza's width
		pizza = settingDoughType(pizza);//using other functions to set pizza's dough type
		pizza = setToppings(pizza);//using other functions to set pizza's toppings
		printf("\n");
		printf("Pizza #%d details:\n", i);
		printLine('*', 19);
		pizza=printPizzaDetails(pizza);//prints the specific pizza details
		totalPrice += pizza.price;
		pizza = initializingPizza(pizza);//restoring the pizza's struct to the its defalt values
	}
	return totalPrice;//returing the sum of all pizzas price
	
	

}
//The fbollowing option asks from the user if he wants to pick up the pizza or get a delivery
PERSON deliveryOption(PERSON man)
{
	printLine('*', 49);
	printf("Do you want delivery for the price of %d NIS? Enter %d for delivery or %d for pick-up: ",(int)ORIG_DELIVERY_PRICE, (int)WITH_DELIVERY, (int)WITHOUT_DELIVERY);
	scanf("%d", &man.delivery);//getting the delivery option 
	while (man.delivery != WITHOUT_DELIVERY && man.delivery != WITH_DELIVERY)//checking that the input was legal - else -> continue inputting
	{
		printf("Invalid choice! Try again.\n");
		printf("Do you want delivery for the price of %d NIS? Enter %d for delivery or %d for pick-up: ", (int)ORIG_DELIVERY_PRICE, (int)WITH_DELIVERY, (int)WITHOUT_DELIVERY);
		scanf("%d", &man.delivery);
		printf("\n\n");
	}
	printf("\n");
	if (man.delivery == WITH_DELIVERY)//updating the total price by the customer's choice
	{
		man.totalPrice += ORIG_DELIVERY_PRICE;
		return man;
	}
	else
	{
		man.totalPrice += ORIG_NO_DELIVERY_PRICE;
		return man;
	}
	
}

//The following function asks from the user the number of pizzas he wants to order until its valid
int startingToOrder() 
{
	int numberOfPizzas;
	printf("How many pizzas would you like to order? ");
	scanf(" %d", &numberOfPizzas);//getting number of pizzas from the user
	while (numberOfPizzas<=0)//if number of pizzas isn't legal
	{
		printf("\n");
		printf("Invalid choice! try again.\n");
		printf("How many pizzas would you like to order? ");
		scanf(" %d", &numberOfPizzas);//getting number of pizzas from the user
	}
	printf("\n");
	return numberOfPizzas;
}
//The following functino prints the opening to the program
void opening()
{
	printf(" Welcome to MTA-Pizza!\n\n");
	printPizzaLogo(PIZZA_LOGO_SIZE);
}
/*The following function prints the menu to the customer*/
void printMenu()
{
	printf("\n");
	printf("Our menu:\n");
	printf("*********\n");
	printf("Basic pizza: %.2lf NIS for %.0lfx%.0lf size pizza\n\n", ORIG_PIZZA_PRICE, ORIG_PIZZAS_LENGTH, ORIG_PIZZAS_WIDTH);
	printf("Toppings for basic size pizza:\n");
	printf("Olives: %.0lf NIS\n", OLIVES_PRICE);
	printf("Mushrooms: %.0lf NIS\n", MUSHROOMS_PRICE);
	printf("Tomatoes: %.0lf NIS\n", TOMATOES_PRICE);
	printf("Pineapple: %.0lf NIS\n\n", PINEAPLLE_PRICE);
	printf("Dough type for basic size pizza:\n");
	printf("Regular: %.0lf NIS\n", REGULAR_DOUGH_PRICE);
	printf("Vegan: %.0lf NIS\n", VEGAN_DOUGH_PRICE);
	printf("Whole wheat: %.0lf NIS\n", WHOLE_WHEAT_PIZZA_PRICE);
	printf("Gluten free: %.0lf NIS\n\n", GLUTEN_FREE_DOUGH_PRICE);

}
/*The followig funtion returns the check digit to the user*/
int checkIdDigit(int id)
{
	int sum = 0;
	int digitNumber = 1;
	while (id != 0)
	{
		int temp;
		if (digitNumber % 2 != 0)//checking if the digit number is parity or non parity number
		{
			temp=(id % 10) * 2;//if non parity multiply it by 2
		}
		if (digitNumber % 2 == 0)//checking if the digit number is parity or non parity number
		{
			temp = (id % 10) * 1;//if parity don't multiply it (multiply it by 1)
		}
		sum += (temp % 10) + (temp / 10);//adding the sum of digits to the total digits sum
		id /= 10;//moving to the next id digit 
		digitNumber++;//moving to the next id digit
	}
	return (10 - (sum % 10));//checking only the first digit of the sum and decreasing it from 10 to return the differece

}
/*The following function checks the id validity by checking range & check digit*/
bool checkId(int id)
{
	if (id <= 0 || id> MAX_LEGAL_ID)
		return false;//if the id if not in range return false
	return true;
}
/*The following function gets the id from the user until he inputs a valid id and returns it to the user*/
int enteringId()
{
	int id;
	printf("Please enter your ID number:\n");
	scanf("%d", &id);//getting the first time the id from the user
	int idWithoutCheckDigit = id / 10;//original id without the last digit (check digit)
	int checkdigit = id % 10;//check digit variable
	while (!checkId(id) || checkIdDigit(idWithoutCheckDigit) != checkdigit)
	{
		//checking the ID validity
		if (!checkId(id))//if the validity checking is not ok - keeps asking from the user to input another id
		{
			printf("Invalid ID number! Try again.\n");
			printf("Please enter your ID number:\n");
			scanf("%d", &id);
		}
		idWithoutCheckDigit = id / 10;//original id without the last digit (check digit)
		checkdigit = id % 10;//check digit variable
		//checking the check digit validity
		if (checkIdDigit(idWithoutCheckDigit) != checkdigit)//if the calculated check digit is not compatible to the original input - return false
		{
			printf("Invalid check digit! Try again.\n");
			printf("Please enter your ID number:\n");
			scanf("%d", &id);
			idWithoutCheckDigit = id / 10;//original id without the last digit (check digit)
			checkdigit = id % 10;//check digit variable
		}
	}
	
	return id;//when the user enters a proper id it will be returned to the program(into id variable)
}
void printPizzaLogo(int pizzaSize)
{
	//The next code is an automatic printing of piramade on screen(as big a you want)
	//Printing general upside down piramade with any non parity number
	int n = pizzaSize;//number of "*" in first line - can be changed to any non parity number
	int space = 0;

	for (int i = 1; i <= (n / 2) + 1; i++)//printing the piramade - running on rows
	{
		for (int j = 0; j < n - (space * 2); j++)//running on all the * on one line
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
	printf("\n");
}
