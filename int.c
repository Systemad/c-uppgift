#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "safeinput.h"
#include <time.h>
#include <stdbool.h>




typedef struct
{

	int accessCards;
	char dateOfAccess[20];
	bool forAccess;


}PASSCARD;

typedef struct
{

	PASSCARD* allCards;
	int NumberOfCards;

}PCARDS_STATE;


void fakeTest(PCARDS_STATE* pCard)
{
	printf("lampan är OFF\n");
	int kortNummer;
	GetInputInt("Kortnummer: ", &kortNummer);
	for (int i = 0; i < pCard->NumberOfCards; i++)
	{
		if (pCard->allCards[i].accessCards == kortNummer)
		{
			if (pCard->allCards[i].accessCards == true)
			{
				printf("lampan är Grön\n");
				getch();
				return;
			}
			else
			{
				printf("lampan e Röd\n");
				getch();
			}

		}
	}
	printf("kortet finna ej i syatemet\n");
	getch();

}



bool checkCards(PCARDS_STATE* pCard, int newCard)
{
	for (int i = 0; i < pCard->NumberOfCards; i++)
	{
		PASSCARD c = pCard->allCards[i];
		if (c.accessCards == newCard) 
		{
			printf("kortet finns redan\n");
			getch();
			return true;
		}
	}
	return false;
}

void NewPassCard(PCARDS_STATE* pCard)
{

	time_t justNu = time(NULL);
	struct tm* datum = localtime(&justNu);

	int indexForTheNewCard;
	if (pCard->NumberOfCards == 0)
	{
		pCard->allCards = malloc(sizeof(PASSCARD));
		pCard->NumberOfCards = 1;
		indexForTheNewCard = 0;
	}
	else
	{
		pCard->allCards = realloc(pCard->allCards,
			sizeof(PASSCARD) * (pCard->NumberOfCards + 1));
		indexForTheNewCard = pCard->NumberOfCards;
		pCard->NumberOfCards++;
	}

	int newCard;
	GetInputInt("\n\tENTER NEW PASSCARD NUMBER:> ", &newCard);
	bool ifCardExist = checkCards(pCard, newCard);

	if (ifCardExist == false)
	{
		pCard->allCards[indexForTheNewCard].accessCards = newCard;
		char accessDatumKort[20];
		snprintf(accessDatumKort, 20, "%d-%d-%02d", datum->tm_year + 1900, datum->tm_mon + 1, datum->tm_mday);
		strcpy(pCard->allCards[indexForTheNewCard].dateOfAccess, accessDatumKort);
	}
	else
		return;



	while (true)
	{
		int forAccessYesOrNo;
		GetInputInt("\n\tThis card has access Enter -> 1 for access, -> 2 for no access:> ", &forAccessYesOrNo);

		if (forAccessYesOrNo == 1)
		{
			pCard->allCards[indexForTheNewCard].forAccess = true;
			printf("\t\t\t\t Access Added\n");
			break;
		}
		else if (forAccessYesOrNo == 2)
		{
			pCard->allCards[indexForTheNewCard].forAccess = false;
			printf("\t\t\t\t No Access Added to CARD\n");
			break;
		}
		else
			printf("\t\t\t  *** Input a number 1 or 2 ***");
	}


	printf("\tEnter any key to continue");
	getch();

}





void listAllCardsInSystem(PCARDS_STATE* pCard)
{
	printf("\tLIST OF ALL CARDS IN SYSTEM\n");
	for (int i = 0; i < pCard->NumberOfCards; i++)
	{
		PASSCARD c = pCard->allCards[i];
		printf("\n\t%d.", c.accessCards);
		if (c.forAccess == true)
			printf(" Access. ");
		else
			printf(" No access. ");
		printf("Added to system: %s", c.dateOfAccess);
	}
	getch();
	system("cls");
}

void delay(int numberOfSeconds)
{
	int milliSeconds = 1000 * numberOfSeconds;
	clock_t startTime = clock();
	while (clock() < startTime + milliSeconds);
}


void RemoteOpenDoor(PCARDS_STATE* pCard)
{
	printf("\n\n\tCURRENTLY LAMP IS:Green\n\n");
	delay(3);
}



void AddRemoveAccess(PASSCARD* pCard)
{
	
	while (true)
	{
		int selection;
		system("cls");
		printf("""\n\n\t1. Remote open door\n"""
			"""\t2. List logged in\n"""
			"""\t3. List all\n"""
			"""\t4. Add/remove access\n"""
			"""\t5. Back\n""");
		if (!GetInputInt("\tMake a choice:> ", &selection))
			continue;
		if (selection == 1)
		{
			RemoteOpenDoor(pCard);
		}
		else if (selection == 3)
		{
			listAllCardsInSystem(pCard);
		}
		else if (selection == 4)
		{
			NewPassCard(pCard);
		}
		else if (selection == 5)
		{
			return;
		}
	}
}





void Huvudmeny(PASSCARD* pCard)
{

	while (true)
	{

		int selection;
		system("cls");
		printf("""\n\t**** Admin meny ****\n\n"""
			"""\t1. Remote open door\n"""
			"""\t2. List all cards in system\n"""
			"""\t3. Add/remove access\n"""
			"""\t4. Exit\n"""
			"""\t9. FAKE TEST SCAN CARD\n""");
		if (!GetInputInt("\tMake a choice:> ", &selection))
			continue;
		if (selection == 1)
		{
			RemoteOpenDoor(pCard);
		}
		else if (selection == 2)
		{
			listAllCardsInSystem(pCard);
		}
		else if (selection == 3)
		{
			AddRemoveAccess(pCard);
		}
		else if (selection == 4)
		{
			printf("\n\n\tHave a nice day!!!\n\n");
			break;
		}
		else if (selection == 9)
		{
			fakeTest(pCard);
		}
	}
}



int main()
{

	PCARDS_STATE pCard;
	pCard.allCards = NULL;
	pCard.NumberOfCards = 0;
	Huvudmeny(&pCard);
	return 0;
}
