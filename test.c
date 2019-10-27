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

void newUsers(SYSTEM_STATE *state)
{
	printf("--New User--\n");

	int indexForTheNewOne;
	if (state->AntalSpelare == 0)
	{
		state->allaSpelare = malloc(sizeof(USER));
		state->AntalSpelare = 1;
		indexForTheNewOne = 0;
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
	GetInputInt("Jersey: ", &jersey);
	state->allaSpelare[indexForTheNewOne].jerseynumber = jersey;


	printf("Press key to continue");
	getch();

}

void manageUser(SYSTEM_STATE *state)
{
	printf("Change access of user\n which\n");
	printf("Press key to continue");
	int indexForTheNewOne = 0;

	int jersey;
	GetInputInt("Jersey: ", &jersey);
	state->allaSpelare[indexForTheNewOne].jerseynumber = jersey;

}

void adminPanel(SYSTEM_STATE *state)
{
	while (true)
	{
		printf("---Admin Panel---\n");
		printf("1. New User\n2. List users\n3. Manage\n");
		printf("4. exit\n5. TEST\n");
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
	state.allaSpelare = NULL;
	state.AntalSpelare = 0;
	adminPanel(&state);

	return 0;
}
