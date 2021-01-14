//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Nodes of a linked list holding tasks
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

typedef struct taskNode{
	 TASK task;
	 struct taskNode* next;

} TASKNODE, *PTASKNODE;

PTASKNODE createTaskNode(TASK);

void setNextTaskNode(PTASKNODE, PTASKNODE);

PTASKNODE getNextTaskNode(PTASKNODE);

PTASK getTaskFromTaskNode(PTASKNODE);

void disposeTaskNode(PTASKNODE);
