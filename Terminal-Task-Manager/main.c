//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//December 11, 2020
//
//1.9 Dec 8, 2020: Code review: refactoring, commenting
//1.8 Dec 7, 2020: Range search functionality, task getters
//1.7 Nov 30, 2020: save,load,start search functionality
//1.6 Nov 24, 2020: User update tasks
//1.5 Nov 21, 2020: User created tasks
//1.4 Nov 17, 2020: Complete tasks, taskNode, tasklist adt
//1.3 Nov 11, 2020: Create linked list functionality
//1.2 Nov 07, 2020: Create labels adt
//1.1 Oct 29, 2020: Comment for testing of pushing.
//1.0 Oct 26, 2020: Inital 
//View README for more details
//
//Program to manage a to-do list within the command prompt. 


#include <stdio.h>
#include "menu.h"
#include "taskList.h"

int main(void) 
{
	TASKLIST taskList = initialization();

	while (true)
	{
		mainMenu(&taskList);
	}
	return 0;
}