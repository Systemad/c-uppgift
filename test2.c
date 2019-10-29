#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "safeinput.h"
#include <stdbool.h>

typedef struct
{
	struct tm* date;
//	char date;

	char name[20];

} USER;


typedef struct
{
	USER* allUsers;
	int amountOfUsers;
}SYSTEM_STATE;

// kanske
typedef struct
{
	bool access;
	bool noaccess;
}ifAcsess;




void listUsers(SYSTEM_STATE *state)
{
	printf("Listing all users...\n");
	for (int i = 0; i < state->amountOfUsers; i++)
	{
		USER p = state->allUsers[i];
		printf("%s , %d\n", p.name, p.date);
	}
	getch();
}

void newUsers(SYSTEM_STATE *state)
{
	printf("--New User--\n");

	int index;
	if (state->amountOfUsers == 0)
	{
		state->allUsers = malloc(sizeof(USER));
		state->amountOfUsers = 1;
		index = 0;
	}
	else
	{
		state->allUsers = realloc(state->allUsers,
			sizeof(USER) * (state->amountOfUsers + 1));
		index = state->amountOfUsers;
		state->amountOfUsers++;
	}


	GetInput("Username: ", state->allUsers[index].name,
		sizeof(state->allUsers[index].name));

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

	time_t now = time(NULL);
	struct tm* currentDate = localtime(&now);
	state->allUsers[index].date = currentDate;

}


void manageUser(SYSTEM_STATE *state)
{
	printf("Change access of user\n which\n");
	printf("Press key to continue");

}

void adminPanel(SYSTEM_STATE *state)
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
