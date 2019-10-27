#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "safeinput.h"
#include <stdbool.h>

typedef struct
{
	char name[50];
	int jerseynumber;
} USER;


typedef struct
{
	USER* allaSpelare;
	int AntalSpelare;
}SYSTEM_STATE;




void listUsers(SYSTEM_STATE *state)
{
	printf("Listing all users...\n");
	for (int i = 0; i < state->AntalSpelare; i++)
	{
		USER p = state->allaSpelare[i];
		printf("%s %d %ld", p.name, p.jerseynumber);
	}
	getch();
}

void newUser(SYSTEM_STATE *state)
{
	printf("New User");

	int indexForTheNewOne;
	if (state->AntalSpelare == 0)
	{
		state->allaSpelare = malloc(sizeof(USER));
		state->AntalSpelare = 1;
		indexForTheNewOne = 0;
		//state.AntalSpelare[0] �r den vi ska l�gga in nya data p�
	}
	else
	{
		state->allaSpelare = realloc(state->allaSpelare,
			sizeof(USER) * (state->AntalSpelare + 1));
		indexForTheNewOne = state->AntalSpelare;
		state->AntalSpelare++;
	}


	GetInput("Username: ", state->allaSpelare[indexForTheNewOne].name,
		sizeof(state->allaSpelare[indexForTheNewOne].name));

	int jersey;
	GetInputInt("Jersey", &jersey);
	state->allaSpelare[indexForTheNewOne].jerseynumber = jersey;


	printf("Press key to continue");
	getch();

}

void manageUser(SYSTEM_STATE *state)
{
	printf("Change access of user");
	printf("Press key to continue");
	getch();

}

void adminPanel(SYSTEM_STATE *state)
{
	while (true)
	{
		printf("---Admin Panel---\n");
		printf("1. New User\n2. List users\n3. Manage\n");
		printf("4. exit\n5. TEST");
		int selection;
		if (!GetInputInt("Choose an option: ", &selection))
			continue;
		switch (selection)
		{
		case 1:
			newUser(state);
			break;
		case 2:
			manageUser(state);
			break;
		case 3:
			return;
		}
	}

}


void mainMenu(SYSTEM_STATE *state)
{
	while (true)
	{
		printf("***HOCKEYMENYN***\n");
		printf("1. Lista spelare\n2. Admin\n3. Avsluta\n");
		int selection;
		if (GetInputInt("Ange val:>", &selection) == false)
			continue;
		switch (selection)
		{
		case 1:
			listUsers(state);
			break;
		case 2:
			adminPanel(state);
			break;
		case 3:
			return 0;
		}

	}

}

void Add(int x)
{
	x = x + 1;
}


int main()
{
	int x = 13;
	Add(x);
	printf("%d", x);

	SYSTEM_STATE state;
	state.allaSpelare = NULL;
	state.AntalSpelare = 0;
	mainMenu(&state);

	return 0;
}
