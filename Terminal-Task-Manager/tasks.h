//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Framework for a task
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "labels.h"

#define MAX_LENGTH 256
#define TITLE_LENGTH 120
#define DATE_STRING_LENGTH 11

static int taskCounter = 1;

typedef enum priorityRating
{
    PRIORITY_INVALID = -1, LOW, MEDIUM, HIGH
} PRIORITYRATING;

typedef struct Task {
    int id;
    char title[TITLE_LENGTH];
    char *note;

    int dueDay;    
    int dueMonth;
    int dueYear;

    PRIORITYRATING priority;
    LABEL label;

} TASK, *PTASK;

TASK createTask(char[], char[], char[], PRIORITYRATING, LABEL);
TASK copyTask(TASK);
bool compareTasks(TASK, TASK);
void disposeTask(TASK);
PRIORITYRATING getPriorityFromString(char[]);
char* getStringFromPriority(PRIORITYRATING);
void updateTaskTitle(PTASK, char[]);
void updateTaskNote(PTASK, char[]);
void updateTaskDate(PTASK, char[]);
void updateTaskPriority(PTASK, PRIORITYRATING);
void updateTaskLabel(PTASK, LABEL);
void saveTask(TASK, FILE*);
TASK readTask(FILE*);
int getTaskID(TASK);
void getTaskTitle(TASK, char[]);
char* getTaskNote(TASK);
void getTaskDate(TASK, char[]);
PRIORITYRATING getTaskPriority(TASK);
LABEL getTaskLabel(TASK);
bool readTaskIdCounter(FILE*);
void saveTaskIdCounter(FILE*);