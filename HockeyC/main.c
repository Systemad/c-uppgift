/*
#define ACCESS = 1
#define NOACCESS = 2

*/
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
	USER* userList;
	int amOfPLayers;
}USER_STATE;

void remoteDoor() {
	printf("Lamp is: Green\n");
	return;
}


void listUsers(USER_STATE *state)
{
	printf("Users in system\n");
	for (int i = 0; i < state->amOfPLayers; i++)
	{
		USER u = state->userList[i];
		printf("%s %d\n", u.name, u.jerseynumber);
	}
	return;
}

void addUser(USER_STATE *state){
	printf("NY SPELARE\n");

	int newUser;
	if (state->amOfPLayers == 0)
	{
		state->userList = malloc(sizeof(USER));
		state->amOfPLayers = 1;
		newUser = 0;
	}
	else
	{
		state->userList = realloc(state->userList,
			sizeof(USER) * (state->amOfPLayers + 1));
		newUser = state->amOfPLayers;
		state->amOfPLayers++;
	}


	GetInput("Name: ", state->userList[newUser].name,
		sizeof(state->userList[newUser].name));

	int jersey;
	GetInputInt("Jersey: ", &jersey);
	state->userList[newUser].jerseynumber = jersey;

	printf("Press key to continue");
	getch();

}

void manageUser(USER_STATE *state){
	printf("Manager User\n");
	printf("Press key to continue");
	return;

}
/*
void addUser(USER_STATE *state){
	while (true)
	{
		printf("***ADMIN***\n");
		printf("1. Ny spelare\n2. Change spelare\n3. Tillbaka\n");
		int selection;
		if (!GetInputInt("Ange val:>", &selection))
			continue;
		switch (selection)
		{
		case 1:
			addUser(state);
			break;
		case 2:
			manageUser(state);
			break;
		case 3:
			return;
		}
	}

}
*/

void Add(int x)
{
	x = x + 1;
}

void mainMenu(USER_STATE *state)
{
	while (true)
	{
		printf("---Admin Panel---\n");
		printf("1. Remote Open Door\n");
		printf("2. List Users\n");
		printf("3. Add User\n");
		printf("4. Manage User\n");
		printf("5. Exit\n");
		printf("6. TEST\n");
		int choice;
		scanf("%d", &choice);
//		if (GetInputInt("Ange val:>", &selection) == false)
//			continue;
		switch (choice)
		{
		case 1:
			remoteDoor(state);
			break;
		case 2:
			listUsers(state);
			break;
		case 3:
			addUser(state);
			break;
		case 4:
			manageUser(state);
			break;
		case 5:
			return;
		}

	}

}


int main()
{
	int x = 13;
	Add(x);
	printf("%d", x);

	USER_STATE state;
	state.userList = NULL;
	state.amOfPLayers = 0;
	mainMenu(&state);

	return;
}

