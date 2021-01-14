//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//List of tasks ADT
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "taskListNode.h"

#define TASKLIST_FILENAME "Tasklist.cfg"

#define YEAR_OFFSET_MULTIPLIER 10000
#define MONTH_OFFSET_MULTIPLIER 100

static void (*printCounterFuncPtr)(int);

static void (*printTaskFuncPtr)(TASK);

typedef struct taskList
{
	PTASKNODE tasklistHead; //Pointer to the first node  of the linked list of nodes
} TASKLIST, *PTASKLIST;

TASKLIST createTaskList();

void setCounterFunctionPointer(void*);

void setTaskFunctionPointer(void*);

void setHead(PTASKLIST, PTASKNODE);

void appendToTaskList(PTASKLIST, TASK);

void removeFromTaskList(PTASKLIST, TASK);

PTASK getTaskFromTaskList(PTASKLIST, int);

int getTaskListLength(PTASKLIST);

void emptyTaskList(PTASKLIST);

void printTaskList(PTASKLIST);

bool saveTaskListFile(TASKLIST);

bool loadTaskListFile(PTASKLIST);

bool displayPriorityRange(PTASKLIST, PRIORITYRATING, PRIORITYRATING);

bool displayDateRange(PTASKLIST, char[], char[]);

bool displayStringMatch(PTASKLIST, char[]);

bool displayLabelMatch(PTASKLIST, char[]);

void uppercaseString(char[], char*);