//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Framework to handle Label management
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LABEL_LEN 20
#define LABELS_FILENAME "Labels.cfg"

typedef enum label {
	LABEL_INVALID = -1, LABELONE, LABELTWO, LABELTHREE, LABELFOUR, LABELFIVE, LABELSIX
} LABEL;

static char labels[LABELSIX + 1][MAX_LABEL_LEN] = { "Work", "School", "Household", "Event", "Purchase", "Misc" };

bool saveLabels();
bool loadLabels(); 
LABEL getLabelNumber(char[]);
char* getLabelName(LABEL); 
void modifyLabel(LABEL, char[]); 
