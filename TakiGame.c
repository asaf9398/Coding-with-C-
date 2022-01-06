#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX_SIGN_LENGTH 6
#define MAX_NAME_LEN 21
#define CARD_CHAR '*'
#define OPENING_MESSAGE_NUM_OF_CHAR 12
#define CARD_WIDTH 9
#define CARD_LENGTH 4
#define NO_COLOR ' '
#define EMPTY_DECK 0
#define NUM_OF_CARDS_TYPES 14
#define GAME_ORDER_BEGGINING true
#define GAME_ORDER_FALSE false
#define GAME_IS_STOP_BEGGINING false
#define NUM_OF_CARDS_INITIALIZATION 0
#define NUM_OF_CARDS_AT_BEGGINING 4
#define PLAYER_CHOICE_ADD_CARD_TO_DECK 0
#define ADD_CARD_TO_DECK 1
#define BEGGINING_OF_PLAYERS_ARRAY 0
#define NUMBER_OF_TIMES_CARD_IN_GAME_INITIALIZATION 0
#define WIDTH_OF_CARD_WITHOUT_CORNERS 7
#define NUMBER_OF_SPACES_AFTER_CARD_SIGN 4
#define MIN_LEGAL_COLOR_CHOICE 1
#define MAX_LEGAL_COLOR_CHOICE 4
#define YELLO_CHAR 'Y'
#define RED_CHAR 'R'
#define BLUE_CHAR 'B'
#define GREEN_CHAR 'G'
#define YELLO_CHOICE_NUMBER 1
#define RED_CHOICE_NUMBER 2
#define BLUE_CHOICE_NUMBER 3
#define GREEN_CHOICE_NUMBER 4
#define FINISH_TURN_OPTION_ON_TAKI_FALL 0
#define NUM_OF_PLAYERS_FOR_ADDING_CARD_ON_STOP_CARD 2
#define EQUAL_STRINGS_COMPARE_NUM 0
#define PLUS_STRING "+"
#define STOP_STRING "STOP"
#define CHANGE_DIRECTION_STRING "<->"
#define TAKI_STRING "TAKI"
#define COLOR_STRING "COLOR"
#define DECREASE_CARD_FROM_DECK 1
#define TAKE_CARD_FROM_DECK_OPTION 0
#define NUM_OF_SPACES_IN_CARD_COLOR_LINE 3
#define CARD_CHAR '*'
#define CARD_STRING "*"
#define RAND_ONLY_REGULAR_CARD_SIGN_INDEXES 9
#define RAND_ONLY_REGULAR_CARD_COLOR_INDEXES 4
#define RAND_GENERAL_CARD_SIGN_INDEXES 14
#define RAND_GENERAL_CARD_COLOR_INDEXES 4
#define COLOR_COLOR_CHAR ' '
#define COLOR_INDEX_IN_ARR 13
#define SECOND_PLAYER_INDEX 1


//structs here
typedef struct card
{
	char color;
	char sign[MAX_SIGN_LENGTH];
}
CARD;
typedef struct player
{
	char name[MAX_NAME_LEN];
	CARD* cardsArray;//deck of cards
	int numOfCards;//num of cards
}PLAYER;
typedef struct statiscics
{
	char cardSign[MAX_SIGN_LENGTH];
	int numberOfTimesInGame;
}STATISTICS;

typedef struct game
{
	int numOfPlayers;//num of players in game
	bool correctOrder;//will be true if the order of turns is from 1 to n, false if from n to 1
	bool isStop;//will be always false until someone will use stop and we will skip the next player turn
	STATISTICS gameStatistics[NUM_OF_CARDS_TYPES];//the statistics for the game
	PLAYER* playersArr;
}GAME;



//functions declarations here
void printLine(char ch, int num);
void enterGameMessage();
void randCardToDeck(GAME* game, PLAYER* player, char signArr[][MAX_SIGN_LENGTH], char colorArr[]);
void randRegularCard(CARD* card, char signArr[][MAX_SIGN_LENGTH], char colorArr[]);
bool isHasWinner(PLAYER* playersArr, int numberOfPlayers, int* winnerIndex);
void printCard(CARD card);
void printCardSecondLine(CARD card);
void printCardFirstLine(CARD card);
void ptintCardBlankLine();
void printPlayersTurn(PLAYER* player);
int choiceOnTurn(PLAYER* player);
void decreaseCardFromDeck(PLAYER* player, int numOfCard);
void checkCardMalloc(CARD* card);
CARD* reallocCardsArray(PLAYER* player, int numOfCardsToAdd);
bool checkColor(CARD cardA, CARD cardB);
void putCardOnTop(GAME* game, CARD* topCard, CARD card);
void updateGameStatistics(GAME* game, CARD* topCard);
int whichIndexIsInArr(GAME* game, char sign[]);
void usingPlus(GAME* game, PLAYER* player, int choice, CARD* topCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[]);
void turnInGame(GAME* game, PLAYER* player, CARD* topCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[]);
bool checkRules(GAME* game, PLAYER* player, int choice, CARD* topCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[]);
void usingTaki(GAME* game, PLAYER* player, CARD* topCard, int numOfPlayersCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[]);
void usingChangeDirection(GAME* game, PLAYER* player, CARD* topCard, int cardsNum);
void usingStop(GAME* game, PLAYER* player, CARD* topCard, int cardsNum, char signArr[][MAX_SIGN_LENGTH], char colorArr[]);
int choiceOnTakiCard(PLAYER* player);
void changeUpperCard(GAME* game, PLAYER* player, CARD* userCard, CARD* topCard);
void usingChangeColor(GAME* game, PLAYER* player, int playersCardNum, CARD* topCard);
char chooseNewColor();
void printStatistics(GAME* game);
void gameStatisticsMessage();
void initiateGameStatistics(STATISTICS* statisticsArr, char signArr[][MAX_SIGN_LENGTH]);
void freeAllDecks(PLAYER* playersArr, int numberOfPlayers);
void copyArr(STATISTICS dest[], STATISTICS src[], int size);
void merge(STATISTICS a1[], int n1, STATISTICS a2[], int n2, STATISTICS res[]);
void mergeSort(STATISTICS arr[], int size);
void winnerWhileTakiFall(GAME* game, PLAYER* player);
void checkPlayersMalloc(PLAYER *playersArr);


void main()
{
	GAME game;
	game.correctOrder = GAME_ORDER_BEGGINING;
	game.isStop = GAME_IS_STOP_BEGGINING;
	char colorArr[] = { 'R','B','G','Y',' ','\0' };
	char signArr[][MAX_SIGN_LENGTH] = { "1","2","3","4","5","6","7","8","9","STOP","<->","TAKI","+","COLOR","\0" };
	initiateGameStatistics(game.gameStatistics, signArr);//initializing the game statistics
	srand(time(NULL));
	int randNum;
	int k;
	int numberOfPlayers;
	enterGameMessage();
	printf("Please enter number of players:\n");
	scanf("%d", &numberOfPlayers);
	game.numOfPlayers = numberOfPlayers;
	game.playersArr = (PLAYER*)malloc(numberOfPlayers * sizeof(PLAYER));//creating array of players
	checkPlayersMalloc(game.playersArr);
	for (k = 0; k < numberOfPlayers; k++)//entering players details and giving them cards
	{
		
		printf("Please enter the first name of player #%d\n", k + 1);
		scanf("%s", game.playersArr[k].name);
		game.playersArr[k].numOfCards = NUM_OF_CARDS_INITIALIZATION;
		randNum = rand() % 14;
		int i;
		game.playersArr[k].cardsArray= (CARD*)malloc(sizeof(CARD) * NUM_OF_CARDS_AT_BEGGINING);
		checkCardMalloc(game.playersArr[k].cardsArray);
		for (i = 0; i < NUM_OF_CARDS_AT_BEGGINING; i++)
		{
			randCardToDeck(&game,&game.playersArr[k], signArr, colorArr);
		}
	}
	CARD topCard;
	randRegularCard(&topCard, signArr, colorArr);
	int winnerIndex, playersCoice;
	int i = 0;
	while (!isHasWinner(game.playersArr, numberOfPlayers, &winnerIndex))//starting to play
	{
		
			printf("Upper card:\n");
			printCard(topCard);
			printPlayersTurn((game.playersArr + i));
			playersCoice = choiceOnTurn((game.playersArr + i));
			if (playersCoice == PLAYER_CHOICE_ADD_CARD_TO_DECK)//add card to the player's deck
			{
				(game.playersArr + i)->cardsArray = reallocCardsArray((game.playersArr + i), ADD_CARD_TO_DECK);
				randCardToDeck(&game,(game.playersArr + i), signArr, colorArr);
			}
			else//decrease card from the player's deck
			{
				//we will check the rules and then decrease it from deck
				if (checkRules(&game,(game.playersArr + i), playersCoice, &topCard, signArr, colorArr))
				{
					//the card is compatible and inner function deals with his actions
				}
				else
				{
					//this is not compatibale card
					//Try your turn again
					turnInGame(&game,(game.playersArr + i), &topCard, signArr, colorArr);
				}

			}
			//promoting i by checking game's direction
			if (game.correctOrder)
			{
				if (!game.isStop)//if stop is not working work as usual
				{
					if (i == numberOfPlayers - 1)
					{
						i = BEGGINING_OF_PLAYERS_ARRAY;
					}
					else
					{
						i++;
					}
				}
				else//if the game's direction is ok and stop is also working
				{
					if (i==numberOfPlayers-2)//need to skip the last player
					{
						i = BEGGINING_OF_PLAYERS_ARRAY;
					}
					else
					{
						i += 2;//if you didn't get to the last player - skip the next one
					}
					//turn the stop off
					game.isStop = GAME_IS_STOP_BEGGINING;

				}
				
			}
			else
			{
				if (!game.isStop)//if the stop cards isn't on
				{
					if (i == BEGGINING_OF_PLAYERS_ARRAY)
					{
						i = numberOfPlayers - 1;
					}
					else
					{
						i--;
					}
				}
				else//if the stop card is on and direction is from n to 1
				{
					if (i == BEGGINING_OF_PLAYERS_ARRAY)
					{
						i = numberOfPlayers - 2;//if you are on the first player - skip the last one
					}
					else
					{
						if(i==SECOND_PLAYER_INDEX)
						{ 
							i = numberOfPlayers - 1;//if you are on the second player - skip to the last one
						}
						else
						{
							i -= 2;//if you are not on the first player - skip the one before you in the array
						}
						
					}
					//turn the stop off
					game.isStop = GAME_IS_STOP_BEGGINING;
				}
				
			}



	}
	
	printf("The winner is... %s Congratulations!\n", game.playersArr[winnerIndex].name);
	printStatistics(&game);

	//free all the memory that left in the computer's heap at the end of the game(all the player's decks + players)
	freeAllDecks(game.playersArr, numberOfPlayers);//getting all cards free
	free(game.playersArr);//getting all players free
}

//The following function gets an players array and doing check for memory allocation and exits if it has been failed
void checkPlayersMalloc(PLAYER* playersArr)
{
	if (playersArr == NULL)
	{
		printf("Memory allocation failed! Exiting");
		exit(1);
	}
	else
	{
		//allocation succeed
	}
}
//The following function enters only when the player has won the game while finishing all of his cards in the taki "fall"
//The function will finish the game and release the memory
void winnerWhileTakiFall(GAME* game, PLAYER* player)
{
	printf("The winner is... %s Congratulations!\n", player->name);
	printStatistics(game);
	//free all the memory that left in the computer's heap at the end of the game(all the player's decks + players)
	freeAllDecks(game->playersArr, game->numOfPlayers);//getting all cards free
	free(game->playersArr);//getting all players free
	exit(0);
}
//The following function gets the statistics arr and doing sorting to the array using merge sort efficiency O(n)=nlogn=size*log(size)
void mergeSort(STATISTICS arr[], int size)
{
	STATISTICS* tmpArr = NULL;
	if (size <= 1)
		return;

	mergeSort(arr, size / 2);
	mergeSort(arr + size / 2, size - size / 2);

	tmpArr = (STATISTICS*)malloc(size * sizeof(STATISTICS));
	if (tmpArr)
	{
		merge(arr, size / 2, arr + size / 2, size - size / 2, tmpArr);
		copyArr(arr, tmpArr, size); // copy values from tmpArr to arr
		free(tmpArr);
	}
	else
	{
		printf("Memory allocation failure!!!\n");
		exit(1);	// end program immediately with code 1 (indicating an error)
	}
}

//The following function gets 2 arrays and merging them into the res array by order
void merge(STATISTICS a1[], int n1, STATISTICS a2[], int n2, STATISTICS res[])
{
	int ind1, ind2, resInd;
	ind1 = ind2 = resInd = 0;

	while ((ind1 < n1) && (ind2 < n2))
	{
		if (a1[ind1].numberOfTimesInGame <= a2[ind2].numberOfTimesInGame)
		{
			res[resInd] = a1[ind1];
			ind1++;
		}
		else
		{
			res[resInd] = a2[ind2];
			ind2++;
		}
		resInd++;
	}

	while (ind1 < n1)
	{
		res[resInd] = a1[ind1];
		ind1++;
		resInd++;
	}
	while (ind2 < n2)
	{
		res[resInd] = a2[ind2];
		ind2++;
		resInd++;
	}
}

//The following function gets src&dst arrays and copies src into dst
void copyArr(STATISTICS dest[], STATISTICS src[], int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		strcpy(dest[i].cardSign, src[i].cardSign);
		dest[i].numberOfTimesInGame = src[i].numberOfTimesInGame;
	}

}


//The following function gets players array + size and let all the players decks arrays free from the memory
void freeAllDecks(PLAYER* playersArr, int numberOfPlayers)
{
	int i;
	for (i = 0; i < numberOfPlayers; i++)
	{
		free((playersArr + i)->cardsArray);
	}
}


//The following function gets array of statistics and array of signs in game and initiates the game statistics to be 0
void initiateGameStatistics(STATISTICS *statisticsArr,char signArr[][MAX_SIGN_LENGTH])
{
	int i;
	for ( i = 0; i < NUM_OF_CARDS_TYPES; i++)
	{
		strcpy((statisticsArr + i)->cardSign, signArr[i]);
		(statisticsArr+i)->numberOfTimesInGame = NUMBER_OF_TIMES_CARD_IN_GAME_INITIALIZATION;
	}
}
//The following function prints the statistics message
void gameStatisticsMessage()
{
	printLine(CARD_CHAR, OPENING_MESSAGE_NUM_OF_CHAR);
	printf(" Game Statistics ");
	printLine(CARD_CHAR, OPENING_MESSAGE_NUM_OF_CHAR);
	printf("\n");
}
//The following function get the game settings and prints out the game statistics when its over
void printStatistics(GAME *game)
{
	mergeSort(game->gameStatistics,NUM_OF_CARDS_TYPES);
	gameStatisticsMessage();
	printf("CARD # | Frequency\n");
	printLine('_', 18);
	printf("\n");
	int i, wordLen;
	for (i = 0; i < NUM_OF_CARDS_TYPES; i++)
	{
		wordLen = strlen(game->gameStatistics[NUM_OF_CARDS_TYPES-1-i].cardSign);
		int numOfSpacesBeforeWord = (WIDTH_OF_CARD_WITHOUT_CORNERS - wordLen) / 2;
		int numOfSpacesAfterWord;
		if (wordLen % 2 == 0)
		{
			numOfSpacesAfterWord = ((WIDTH_OF_CARD_WITHOUT_CORNERS - wordLen) / 2)+1;
		}
		else
		{
			numOfSpacesAfterWord = (WIDTH_OF_CARD_WITHOUT_CORNERS - wordLen) / 2;
		}
		printLine(' ', numOfSpacesBeforeWord);
		printf("%s", game->gameStatistics[NUM_OF_CARDS_TYPES - 1 - i].cardSign);
		printLine(' ', numOfSpacesAfterWord);
		printf("|");
		printLine(' ', NUMBER_OF_SPACES_AFTER_CARD_SIGN);
		printf("%d\n", game->gameStatistics[NUM_OF_CARDS_TYPES - 1 - i].numberOfTimesInGame);
	}


}

//The following function asks from the user to choose a new color and returns it
char chooseNewColor()
{
	int usersChoice = -1;
	while (usersChoice < MIN_LEGAL_COLOR_CHOICE || usersChoice>MAX_LEGAL_COLOR_CHOICE)
	{
		printf("Please enter your choice:\n");
		printf("%d - Yellow\n", YELLO_CHOICE_NUMBER);
		printf("%d - Red\n", RED_CHOICE_NUMBER);
		printf("%d - Blue\n", BLUE_CHOICE_NUMBER);
		printf("%d - Green\n", GREEN_CHOICE_NUMBER);
		scanf("%d", &usersChoice);
		if (usersChoice < MIN_LEGAL_COLOR_CHOICE || usersChoice>MAX_LEGAL_COLOR_CHOICE)
		{
			printf("Invalid choice! Try again\n");
		}
	}
	switch (usersChoice)//returning the char that match to the choosing
	{
	case YELLO_CHOICE_NUMBER:
		return YELLO_CHAR;
		break;
	case RED_CHOICE_NUMBER:
		return RED_CHAR;
		break;
	case BLUE_CHOICE_NUMBER:
		return BLUE_CHAR;
		break;
	case GREEN_CHOICE_NUMBER:
		return GREEN_CHAR;
		break;
	default:
		break;
	}
	
}

//The following function get player + the specific card(change color)and changes the top card to be with the chosen color
void usingChangeColor(GAME *game,PLAYER *player,int playersCardNum,CARD *topCard)
{
	CARD newCard;//new card for updated upper card
	//asking to choose the new color
	char newColor = chooseNewColor();
	newCard.color = newColor;
	strcpy(newCard.sign,"COLOR");
	//changing the topCard by the choosing
	changeUpperCard(game,player, &newCard, topCard);
	//decreasing the card from the deck
	decreaseCardFromDeck(player, playersCardNum);

}

//The following function gets a player+his choice+top card's pointer and changes the upper card to be player's choice
void changeUpperCard(GAME *game,PLAYER* player, CARD* userCard, CARD* topCard)
{
	topCard->color = userCard->color;
	strcpy(topCard->sign, userCard->sign);
}
//The following functino gets a player and returns his choice for card(specifically on TAKI card mode)
int choiceOnTakiCard(PLAYER* player)
{
	int choice;
	printf("Please enter %d if you want to finish your turn or 1-%d if you want to put one of your card in the middle:\n", FINISH_TURN_OPTION_ON_TAKI_FALL,player->numOfCards);
	scanf("%d", &choice);
	return choice;
}
//The following function gets the game settings and turns on the stop ability
void usingStop(GAME* game,PLAYER *player,CARD *topCard,int cardsNum,char signArr[][MAX_SIGN_LENGTH], char colorArr[])
{
	//turning stop ability on
	game->isStop = true;
	CARD userCard = player->cardsArray[cardsNum - 1];
	//change top card
	putCardOnTop(game, topCard, userCard);
	//we will take the user's card out of the deck
	decreaseCardFromDeck(player, cardsNum);
	//if the user putted "STOP" card and his deck turned to be empty and there are only 2 players - give him another card 
	if (player->numOfCards == EMPTY_DECK && game->numOfPlayers== NUM_OF_PLAYERS_FOR_ADDING_CARD_ON_STOP_CARD)
	{
		randCardToDeck(game, player, signArr, colorArr);
	}

}
//The following function gets the game settings and turning the change direction ability
void usingChangeDirection(GAME *game,PLAYER* player, CARD* topCard, int cardsNum)
{
	if (game->correctOrder)
	{
		game->correctOrder = GAME_ORDER_FALSE;
	}
	else
	{
		game->correctOrder = GAME_ORDER_BEGGINING;
	}
	CARD userCard = player->cardsArray[cardsNum - 1];
	//change top card
	putCardOnTop(game, topCard, userCard);
	//we will take the user's card out of the deck
	decreaseCardFromDeck(player, cardsNum);
}
//The following function gets a user + his choice(the TAKI card) and the top card and let him to do a "fall" of cards with the same color
void usingTaki(GAME *game,PLAYER* player, CARD* topCard,int numOfPlayersCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[])
{
	int playersCoice;
	//put userCard on top
	changeUpperCard(game,player, &player->cardsArray[numOfPlayersCard-1], topCard);
	//taking the user's card out from the deck
	decreaseCardFromDeck(player, numOfPlayersCard);
	/*if the user ended his cards in this code line it means that his last card was TAKI and he is the winner*/
	if (player->numOfCards == EMPTY_DECK)
	{
		//making him the winner and exiting the game
		winnerWhileTakiFall(game, player);
	}
	//printing the current deck + current top card
	printf("Upper card:\n");
	printCard(*topCard);
	printPlayersTurn(player);
	//let the user put unlimited number of cards with same color(using while) until entering 0 or player's finished his cards
	playersCoice = choiceOnTakiCard(player);
	//check if the choice is compatible to the TAKI's color
	//if the choice is ok - update topCard
	//decreace the choice from the deck
	//if the choice isn't ok - try again
	while (playersCoice != FINISH_TURN_OPTION_ON_TAKI_FALL &&player->numOfCards!=EMPTY_DECK)
	{
		
		CARD userChoiceCard = player->cardsArray[playersCoice - 1];
		if (userChoiceCard.color == NO_COLOR)
		{
			usingChangeColor(game,player, playersCoice,topCard);
			playersCoice = FINISH_TURN_OPTION_ON_TAKI_FALL;//avoiding using brake
			return;//get out of the function - the user putted change color on taki fall , his turn has been over
		}
		else// if it's not change color card you can proceed with your turn
		{
			//check the cards that the user wants to put in the fall(just with color check for the specific fall-avoiding special cards when you don't need to)
			//if the cards in the fall are ok so put them on top + decreace from deck
			//than let the player to choose again
			if (userChoiceCard.color == topCard->color)//if the color is OK
			{
				changeUpperCard(game,player, &userChoiceCard, topCard);
				decreaseCardFromDeck(player, playersCoice);
				

			}
			else//if the chosen card is not compatible - print proper message and let him to choose again
			{
				printf("You can't put this card because it doesn't have the same color\n");
				printf("Please try again\n");
				
			}
			if (player->numOfCards != EMPTY_DECK)
			{
				printf("Upper card:\n");
				printCard(*topCard);
				printPlayersTurn(player);
				playersCoice = choiceOnTakiCard(player);
			}
		}
	}

	
	//checking if the last card is special(the current topCard) and behave properly if it does
	char topCardSign[MAX_SIGN_LENGTH];
	strcpy(topCardSign, topCard->sign);
	if (strcmp(topCardSign, PLUS_STRING) == EQUAL_STRINGS_COMPARE_NUM)
	{
		/*if the user put the last card and it was "+", in this point of code his number of cards
		will be 0(but he didn't finished his turn).
		in this case - give him a new card and let him to put another card*/
		if (player->numOfCards == EMPTY_DECK)
		{
			randCardToDeck(game, player, signArr, colorArr);
		}
		usingPlus(game,player,playersCoice,topCard,signArr,colorArr);
	}
	if (strcmp(topCardSign, STOP_STRING) == EQUAL_STRINGS_COMPARE_NUM)
	{
		/*if the user put the last card and it was "STOP" and there are only 2 players, in this point of code his number of cards
		will be 0(but he didn't finished his turn).
		in this case - give him a new card and he is not the winner*/
		if (player->numOfCards == EMPTY_DECK&&game->numOfPlayers== NUM_OF_PLAYERS_FOR_ADDING_CARD_ON_STOP_CARD)
		{
			randCardToDeck(game, player, signArr, colorArr);
		}
		usingStop(game,player,topCard,playersCoice,signArr,colorArr);
	}
	if (strcmp(topCardSign, CHANGE_DIRECTION_STRING) == EQUAL_STRINGS_COMPARE_NUM)
	{
		/*if the user ended his cards while taki fall he is the winner*/
		if (player->numOfCards == EMPTY_DECK)
		{
			//making him the winner and exiting the game
			winnerWhileTakiFall(game,player);
		}
		usingChangeDirection(game, player,topCard, playersCoice);
	}
	if (strcmp(topCardSign, TAKI_STRING) == EQUAL_STRINGS_COMPARE_NUM &&playersCoice!= FINISH_TURN_OPTION_ON_TAKI_FALL)
	{
		/*if the user ended his cards while taki fall he is the winner*/
		if (player->numOfCards == EMPTY_DECK)
		{
			//making him the winner and exiting the game
			winnerWhileTakiFall(game, player);
		}
		usingTaki(game,player, topCard,playersCoice,signArr,colorArr);//use taki function again when user's last card is also the TAKI card
	}
	if (strcmp(topCardSign, COLOR_STRING) == EQUAL_STRINGS_COMPARE_NUM)
	{
		/*if the user ended his cards while taki fall he is the winner*/
		if (player->numOfCards == EMPTY_DECK)
		{
			//making him the winner and exiting the game
			winnerWhileTakiFall(game, player);
		}
		usingChangeColor(game,player, playersCoice, topCard);
	}
	/*if the user ended his cards while taki fall he is the winner*/
	if (player->numOfCards == EMPTY_DECK)
	{
		//making him the winner and exiting the game
		winnerWhileTakiFall(game, player);
	}
}

//The following function gets a player+his choice+the top card at the moment and returns true if it's ok to put on this card
bool checkRules(GAME *game,PLAYER* player, int choice, CARD* topCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[])
{
	//checking the rules of the game

	CARD playersCard = player->cardsArray[choice - 1];
	// checking for special cards
	if (strcmp(playersCard.sign, PLUS_STRING) == EQUAL_STRINGS_COMPARE_NUM)//if plus do this
	{
		if (checkColor(playersCard, *topCard))//checking if they are in the same color
		{
			usingPlus(game,player, choice, topCard, signArr, colorArr);//go for another function of using "+" 
			return true;
		}


	}
	if (strcmp(playersCard.sign, STOP_STRING) == EQUAL_STRINGS_COMPARE_NUM)//if stop do this
	{
		if (checkColor(playersCard, *topCard))//checking if they are in the same color
		{
			usingStop(game, player, topCard, choice, signArr, colorArr);//go for another function of using "STOP"- skipping next player turn(check game direction)
			return true;
		}


	}
	if (strcmp(playersCard.sign, CHANGE_DIRECTION_STRING) == EQUAL_STRINGS_COMPARE_NUM)//if change direction do this
	{
		if (checkColor(playersCard, *topCard))//checking if they are in the same color
		{
			usingChangeDirection(game, player,topCard, choice);//go for another function of using "<->" - change game's direction
			return true;
		}


	}
	if (strcmp(playersCard.sign, TAKI_STRING) == EQUAL_STRINGS_COMPARE_NUM)//if TAKI do this
	{
		if (checkColor(playersCard, *topCard))//checking if they are in the same color
		{
			usingTaki(game,player,topCard,choice,signArr,colorArr);//go for another function of using "TAKI" - letting the user to put all of his cards from the same color(until presses something)
			return true;
		}


	}
	if (strcmp(playersCard.sign, COLOR_STRING) == EQUAL_STRINGS_COMPARE_NUM)//if change color do this
	{
		usingChangeColor(game,player, choice, topCard);//go for another function of using "COLOR" - let the player to choose the top card's color(by menu)
		return true;
	}
	//if it's not a special card so it's probably a regular card
	if (checkColor(playersCard, *topCard))//if same color - it's OK
	{
		putCardOnTop(game, topCard, playersCard);//go to another function that changes the topCard to be your card
		//decreacse this card from his deck
		decreaseCardFromDeck(player, choice);
		return true;
	}
	if (strcmp(playersCard.sign, topCard->sign) == 0)//if same sign - it's OK
	{
		putCardOnTop(game,topCard, playersCard);//go to another function that changes the topCard to be your card
		//decreacse this card from his deck
		decreaseCardFromDeck(player, choice);
		return true;
	}
	printf("Your choice is incompatible to the current top card\n");
	printf("You can't put this card\n");
	return false;//if you can't put the card on the topCard - return false


}
//The following function gets a player and he makes a turn
void turnInGame(GAME *game,PLAYER* player, CARD* topCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[])
{
	printf("Upper card:\n");
	printCard(*topCard);
	printPlayersTurn(player);
	int playersCoice = choiceOnTurn(player);
	if (playersCoice == 0)//add card to the player's deck
	{
		player->cardsArray = reallocCardsArray(player, ADD_CARD_TO_DECK);
		randCardToDeck(game,player, signArr, colorArr);
	}
	else//decrease card(if it's ok) from the player's deck
	{
		//we will check the rules and then decrease it from deck
		if (checkRules(game,player, playersCoice, topCard, signArr, colorArr))
		{
			//the card is compatible and inner function deals with his actions
		}
		else
		{
			//this is not compatibale card
			//Try your turn again
			turnInGame(game,player, topCard, signArr, colorArr);
		}

	}

}

//The following function gets a player + his choice and gives him another regular turn
void usingPlus(GAME *game,PLAYER* player, int choice, CARD* topCard, char signArr[][MAX_SIGN_LENGTH], char colorArr[])
{

	CARD playersCard = player->cardsArray[choice - 1];//copy of player's "+" card
	//we will put the choice of the user on top
	putCardOnTop(game,topCard, playersCard);
	//we will decreacse this card from his deck
	decreaseCardFromDeck(player, choice);
	//if the user putted "+" card and his deck turned to be empty - give him another card 
	if (player->numOfCards == EMPTY_DECK)
	{
		randCardToDeck(game,player, signArr, colorArr);
	}
	//we will give him another turn with the current deck
	turnInGame(game,player, topCard, signArr, colorArr);

}
//The following function gets the game settings + string of card's sign and returns the index of the sign in the statistics array
int whichIndexIsInArr(GAME *game, char sign[])
{
	int i;
	for (i = 0; i < NUM_OF_CARDS_TYPES; i++)
	{
		if (strcmp(game->gameStatistics[i].cardSign, sign) == 0)
		{
			return i;
		}
	}
}

//The following function get the current topCard(after it has been updated) and updates the number of times it has been used in game
void updateGameStatistics(GAME *game, CARD *card)
{
	int signIndex=whichIndexIsInArr(game,card->sign);
	game->gameStatistics[signIndex].numberOfTimesInGame++;//promoting card's statistics

}

//The following function gets a pointer of top card and another card and changes the top card to be the 2nd card
void putCardOnTop(GAME *game,CARD *topCard, CARD card)
{
	topCard->color = card.color;
	strcpy(topCard->sign, card.sign);
}

//The following function gets 2 cards and returns true if the colors are the same 
bool checkColor(CARD cardA, CARD cardB)
{
	return ((int)(cardA.color - cardB.color) == EQUAL_STRINGS_COMPARE_NUM);//if they identical the answer will be true
}

//The following function gets a player + how many cards to add to the array and updates it
CARD* reallocCardsArray(PLAYER* player, int numOfCardsToAdd)
{
	CARD* tmpArr = (CARD*)malloc((player->numOfCards + numOfCardsToAdd) * sizeof(CARD));
	int i;
	checkCardMalloc(tmpArr);
	for (i = 0; i < player->numOfCards; i++)
	{
		(tmpArr + i)->color = player->cardsArray[i].color;
		strcpy((tmpArr + i)->sign, player->cardsArray[i].sign);
	}
	free(player->cardsArray);
	return tmpArr;

}
//The following function gets a pointer of card and exiting if the allocation didn't succeed
void checkCardMalloc(CARD* card)
{
	if (card == NULL)
	{
		printf("Memory allocation failed! Exiting");
		exit(1);
	}
	else
	{
		//allocation succeed
	}
}

//The following function gets a player and the card he wants to decrease, and deletes it 
void decreaseCardFromDeck(PLAYER* player, int numOfCard)
{
	int i;
	for (i = numOfCard - 1; i < player->numOfCards; i++)
	{
		player->cardsArray[i] = player->cardsArray[i + 1];
	}
	player->numOfCards -= DECREASE_CARD_FROM_DECK;
}
//The following function gets a player's pointer and returns his choice
int choiceOnTurn(PLAYER* player)
{
	int num;
	printf("Please enter %d if you want to take card from deck or 1-%d if you want to put one of your cards in the middle:\n", TAKE_CARD_FROM_DECK_OPTION,player->numOfCards);
	scanf("%d", &num);
	return num;
}
void printPlayersTurn(PLAYER* player)
{
	printf("%s's turn:\n\n", player->name);
	int i;
	for (i = 0; i < player->numOfCards; i++)
	{
		printf("Card #%d:\n", i + 1);
		printCard(player->cardsArray[i]);

	}

}
//The following function prints card's blank line
void ptintCardBlankLine()
{
	printf("*");
	printLine(' ', CARD_WIDTH - 2);
	printf("*");
	printf("\n");
}
//The following function prints card's first line
void printCardFirstLine(CARD card)
{
	int cardWordLen = strlen(card.sign);
	int numOfSpacesBeforeWord;
	int numOfSpacesAfterWord = (CARD_WIDTH - 2 - cardWordLen) / 2;
	if (cardWordLen % 2 == 0)
	{
		numOfSpacesBeforeWord = ((CARD_WIDTH - 2 - cardWordLen) / 2)+1;
	}
	else
	{
		numOfSpacesBeforeWord = ((CARD_WIDTH - 2 - cardWordLen) / 2);
	}
	printf("*");
	printLine(' ', numOfSpacesBeforeWord);
	printf("%s", card.sign);
	printLine(' ', numOfSpacesAfterWord);
	printf("*");
	printf("\n");
}
//The following function prints card's second line
void printCardSecondLine(CARD card)
{
	printf("%s", CARD_STRING);
	printLine(' ', NUM_OF_SPACES_IN_CARD_COLOR_LINE);
	printf("%c", card.color);
	printLine(' ', NUM_OF_SPACES_IN_CARD_COLOR_LINE);
	printf("%s", CARD_STRING);
	printf("\n");

}
//The following function gets a card and prints it
void printCard(CARD card)
{
	printLine(CARD_CHAR, CARD_WIDTH);
	printf("\n");
	ptintCardBlankLine();
	printCardFirstLine(card);
	printCardSecondLine(card);
	ptintCardBlankLine();
	printLine(CARD_CHAR, CARD_WIDTH);
	printf("\n");
}

//The following function gets a players array and checks if someone won,
//if someone won, the function returns true + updates the winner index
bool isHasWinner(PLAYER* playersArr, int numberOfPlayers, int* winnerIndex)
{
	int i;
	for (i = 0; i < numberOfPlayers; i++)
	{
		if ((playersArr + i)->numOfCards == EMPTY_DECK)
		{
			*winnerIndex = i;
			return true;
		}
	}
	return false;
}


//The following function gets a card pointer, and puts a new(regular) card instead of it
void randRegularCard(CARD* card, char signArr[][MAX_SIGN_LENGTH], char colorArr[])
{
	int randNum = rand() % RAND_ONLY_REGULAR_CARD_SIGN_INDEXES;
	strcpy(card->sign, signArr[randNum]);
	randNum = rand() % RAND_ONLY_REGULAR_CARD_COLOR_INDEXES;
	card->color = colorArr[randNum];
}


//The following function gets a player(and the cards options), and puts a new card in the end of the deck + updating game statistics
void randCardToDeck(GAME *game,PLAYER* player, char signArr[][MAX_SIGN_LENGTH], char colorArr[])
{
	CARD newCard;
	int randNum = rand() % RAND_GENERAL_CARD_SIGN_INDEXES;
	if (randNum == COLOR_INDEX_IN_ARR)
	{
		strcpy(player->cardsArray[player->numOfCards].sign, signArr[randNum]);
		player->cardsArray[player->numOfCards].color = COLOR_COLOR_CHAR;

	}
	else
	{
		strcpy(player->cardsArray[player->numOfCards].sign, signArr[randNum]);
		randNum = rand() % RAND_GENERAL_CARD_COLOR_INDEXES;
		player->cardsArray[player->numOfCards].color = colorArr[randNum];
	}
	updateGameStatistics(game, &player->cardsArray[player->numOfCards]);
	player->numOfCards += ADD_CARD_TO_DECK;
	

}
//The following function prints the welcome message
void enterGameMessage()
{
	printLine(CARD_CHAR, OPENING_MESSAGE_NUM_OF_CHAR);
	printf(" Welcome to TAKI game !!! ");
	printLine(CARD_CHAR, OPENING_MESSAGE_NUM_OF_CHAR);
	printf("\n");
}
void printLine(char ch, int num)
{
	int i;
	for (i = 0; i < num; i++)
	{
		printf("%c", ch);

	}
}
