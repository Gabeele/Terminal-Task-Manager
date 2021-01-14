//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//User interfacing menu options

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "labels.h"
#include "inputValidation.h"
#include "taskList.h"
#include "tasks.h"

TASKLIST initialization();
void mainMenu(PTASKLIST);
void printTask(TASK);
void addTask(PTASKLIST);
PTASK selectTaskByNumber(PTASKLIST);
void updateTask(PTASK);
void searchMenu(PTASKLIST);
void searchByLabel(PTASKLIST);
void searchByString(PTASKLIST);
void searchDateRange(PTASKLIST);
void displayRangeMenu(PTASKLIST);
void searchPriorityRange(PTASKLIST);
void printListNumbering(int);
void printLabels();
void modifyLabelsMenu();
