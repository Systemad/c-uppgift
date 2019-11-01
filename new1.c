#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "safeinput.h"
#include <stdbool.h>

typedef struct
{
	int cardName;
	char dateAcess[20];
	bool access;

} CARD;


typedef struct
{
	CARD* allUsers;
	int amountOfUsers;
}SYSTEM_STATE;



void listUsers(SYSTEM_STATE* state)
{
	printf("Listing all users...\n");
	for (int i = 0; i < state->amountOfUsers; i++)
	{
		CARD p = state->allUsers[i];
		printf("%d\n", p.cardName);
		if (p.access == true)
			printf("Has access");
		else
			printf("Has no access");
	}
	getch();
}

void newUsers(SYSTEM_STATE* state)
{
	printf("--New User--\n");

	time_t justNu = time(NULL);
	struct tm* datum = localtime(&justNu);

	int index;
	if (state->amountOfUsers == 0)
	{
		state->allUsers = malloc(sizeof(CARD));
		state->amountOfUsers = 1;
		index = 0;
	}
	else
	{
		state->allUsers = realloc(state->allUsers,
			sizeof(CARD) * (state->amountOfUsers + 1));
		index = state->amountOfUsers;
		state->amountOfUsers++;
	}

	int newCard;
	GetInputInt("\nENTER NEW PASSCARD NUMBER:> ", &newCard);

	state->allUsers[index].cardName = newCard;
	char accessDatumKort[20];
	snprintf(accessDatumKort, 20, "%d-%d-%02d", datum->tm_year + 1900, datum->tm_mon + 1, datum->tm_mday);
	strcpy(state->allUsers[index].dateAcess, accessDatumKort);


	printf("What access should user have: \n");
	int choice;
	printf("1. Access\n2. No Access");
	scanf("%d", &choice);

	if (choice == 1) {
		state->allUsers[index].access = true;

	}
	else {
		state->allUsers[index].access = false;
	}

}


void manageUser(SYSTEM_STATE* state)
{
	printf("Change access of user\n which\n");
	printf("Press key to continue");

}

void adminPanel(SYSTEM_STATE* state)
{
	while (true)
	{
		printf("---Admin Panel---\n");
		printf("1. New User\n2. List users\n3. Manage\n");
		printf("4. Exit\n5. TEST\n");
		int selection;
		if (!GetInputInt("Choose an option: ", &selection))
			continue;
		switch (selection)
		{
		case 1:
			newUsers(state);
			break;
		case 2:
			listUsers(state);
			break;
		case 3:
			manageUser(state);
			break;
		case 4:
			return 0;
		}
	}

}

int main()
{

	SYSTEM_STATE state;
	state.allUsers = NULL;
	state.amountOfUsers = 0;
	adminPanel(&state);

	return 0;
}
