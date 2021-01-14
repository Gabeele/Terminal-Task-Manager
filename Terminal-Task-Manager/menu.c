//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//User interfacing menu options

#include "menu.h"

/// <summary>
/// Initialize program with user history if found, otherwise create new
/// </summary>
/// <returns>loaded taskList or new taskList</returns>
/// <author>Kevin, Brayden</author>
TASKLIST initialization()
{
	TASKLIST tasklist = createTaskList();
	if (!loadTaskListFile(&tasklist))
	{
		printf("Unable to find TaskList configuration file, creating new.\n");
	}
	
	if (!loadLabels())
	{
		printf("Unable to find Label configuration file, using defaults.\n");
		saveLabels(); //creates new file
	}

	//Sets the pointers to the functions
	setCounterFunctionPointer(printListNumbering);	
	setTaskFunctionPointer(printTask);
	return tasklist;
}

/// <summary>
/// Prints the main menu and allows user to select operation
/// </summary>
/// <author>Everybody</author>
void mainMenu(PTASKLIST taskList) {

	printf("To Do Menu------------\n");
	printf("1. Add Task\n");

	if (getTaskListLength(taskList) != 0) { 

		printf("2. Delete Task\n");
		printf("3. Update Task\n"); 
		printf("4. Display Single Task\n"); 
		printf("5. Display Range of Tasks\n"); 
		printf("6. Display All Tasks\n"); 
		printf("7. Search for Task\n");
		printf("8. Alter Labels\n");
		printf("9. Save Tasks\n");

	}

	printf("10. Load Tasks\n");
	printf("0. Quit Program\n");

	printf("\nEnter in numeric menu option: ");
	int menuInput =  integerValidation();

	//variable declarations used in switch
	PTASK selectedTask;

		switch (menuInput) {
		
		case 0:
			//Quit program
			saveTaskListFile(*taskList);
			exit(0);
			break;
		
		case 1:
			//Add Task
			addTask(taskList);
			system("cls");

			break;
		
		case 2:
			//Delete Task
			
			printTaskList(taskList);
			selectedTask = selectTaskByNumber(taskList);
			if(selectedTask != NULL)
				removeFromTaskList(taskList, *selectedTask);
			system("cls");

			break;
		
		case 3:
			//Updating a single task

			printTaskList(taskList);
			selectedTask = selectTaskByNumber(taskList);
			if (selectedTask != NULL)
				updateTask(selectedTask);
			system("cls");
						
			break;
		
		case 4:
			//Display a single task
			
			printTaskList(taskList);
			selectedTask = selectTaskByNumber(taskList);
			if (selectedTask != NULL){	
				system("cls");
				printTask(*selectedTask);
			}
			else {
				system("cls");
			}
		
			break;
		
		case 5:
			//Display range menu
			displayRangeMenu(taskList);
			system("cls");
			break;
		
		case 6:
			//Display all tasks
			printTaskList(taskList);
			break;
		
		case 7:
			//Displays search menu
			searchMenu(taskList);
			system("cls");
			break;
		case 8: 
			//Alter the labels names
			modifyLabelsMenu();
			system("cls");
			break;
		
		case 9:
			//Save tasks to external file.

			if (saveTaskListFile(*taskList))
			{
				printf("Your tasks have been successfully saved.\n");
			}
			else
			{
				printf("Unable to save tasks.\n");
			}
			break;
		
		case 10:
			//Load tasks from external file.
			if (loadTaskListFile(taskList))
			{
				printf("Your tasks have been successfully loaded.\n");
			}
			else
			{
				printf("Unable to load tasks.\n");
			}
			break;

		default:
			printf("\nERROR: Invalid Numeric Entry.\n\n");
			break;
		
		}

}

/// <summary>
/// Prints the given task data to terminal
/// </summary>
/// <param name="task">task to be printed</param>
/// <author>Everybody</author>
void printTask(TASK task)
{
	char dueDate[DATE_STRING_LENGTH];
	char title[TITLE_LENGTH];

	getTaskDate(task, dueDate);
	getTaskTitle(task, title);

	printf("%s | Due Date: %s | %s | %s\n", 
		title, dueDate, getStringFromPriority(getTaskPriority(task)), getLabelName(getTaskLabel(task)));
	printf("\t%s\n\n", getTaskNote(task));
}

/// <summary>
/// Retrieves user input, creates a new task and assigns it to the list
/// </summary>
/// <param name="taskList">tasklist to add to</param>
/// <author>Gavin</author>
void addTask(PTASKLIST taskList) {	
	char title[TITLE_LENGTH];
	char note[MAX_LENGTH];
	char priority[MAX_LENGTH];
	int priorityNum;
	char label[MAX_LABEL_LEN];
	int labelNum;
	char dueDate[DATE_STRING_LENGTH];
	int dueDay;
	int dueMonth;
	int dueYear;

	printf("-------------Create Task-------------\n");
	do {

		printf("Task title: ");
		fgets(title, TITLE_LENGTH, stdin);
		if (strlen(title) + 1 == TITLE_LENGTH)
		{
			clearStdin();
		}
		else
		{
			title[strlen(title) - 1] = '\0';
		}

	} while (strlen(title) == 0);
	if(verifyAbortChar(title))
		return;

	printf("\nTask note: ");
	fgets(note, MAX_LENGTH, stdin);
	if (strlen(note) + 1 == MAX_LENGTH)
	{
		clearStdin();
	}
	else
	{
		note[strlen(note) - 1] = '\0';
	}
	if (strlen(note) == 0) {

		strcpy_s(note, MAX_LENGTH, "No note created.");

	}
	if (verifyAbortChar(note))
		return;

	do {
		printf("\nDue date (YYYY/MM/DD): ");
		scanf_s("%d/%d/%d", &dueYear, &dueMonth, &dueDay);
		clearStdin();
		if (verifyAbortInt(dueYear))
			return;
	} while (!dateValidation(dueYear, dueMonth, dueDay));

	snprintf(dueDate, DATE_STRING_LENGTH, "%d/%d/%d", dueYear, dueMonth, dueDay);

	do { //invalid if not Low, Medium, High: user chooses again
		printf("\nPriority (Low, Medium, High): ");
		scanf_s("%s", priority, MAX_LENGTH);
		clearStdin();
		if (verifyAbortChar(priority))
			return;

		priorityNum = getPriorityFromString(priority);
		if (priorityNum == PRIORITY_INVALID)
		{
			printf("Invalid Input.\n");
		}
	} while (priorityNum == PRIORITY_INVALID); 


	do {
		//print list of labels for user to select
		printf("\nLabel (");
		printLabels();
		printf("): ");
		scanf_s("%s", label, MAX_LABEL_LEN);
		clearStdin();
		if (verifyAbortChar(label))
			return;
		labelNum = getLabelNumber(label);
		if (labelNum == LABEL_INVALID)
		{
			printf("Invalid Input.\n");
		}
	} while (labelNum == LABEL_INVALID);

	appendToTaskList(taskList, createTask(title, note, dueDate, priorityNum, labelNum));

}

/// <summary>
/// Select a task by list numbering
/// </summary>
/// <param name="taskList">tasklist to select from</param>
/// <returns>pointer to selected task</returns>
/// <author>Brayden</author>
PTASK selectTaskByNumber(PTASKLIST taskList) {

	int taskIndex;

	do {

		printf("Enter the task number: ");
		taskIndex = integerValidation();

		if (verifyAbortInt(taskIndex))
			return NULL;

		taskIndex--;
	} while (taskIndex >= getTaskListLength(taskList) || taskIndex < 0); //ensure number within limits of tasklist

	return getTaskFromTaskList(taskList, taskIndex);

}

/// <summary>
/// Update an existing task
/// </summary>
/// <param name="task">task to be updated</param>
/// <author>Brayden, Kevin</author>
void updateTask(PTASK task) {
	//variable declarations used in switch
	char newTitle[TITLE_LENGTH];
	char newTaskNote[MAX_LENGTH];
	char newPriority[MAX_LENGTH];
	int newPriorityNum;
	char newLabel[MAX_LABEL_LEN];
	int newLabelNum;
	char newDueDate[DATE_STRING_LENGTH];
	int newDueDay;
	int newDueMonth;
	int newDueYear;
	bool shouldQuit = false;

	do {

		printf("Choose a component of the task to change:\n");
		printf("1. Title\n");
		printf("2. Note\n");
		printf("3. Due Date\n");
		printf("4. Priority\n");
		printf("5. Label\n");
		printf("0. Exit update menu\n");

		int menuInput = integerValidation();

		switch (menuInput) {

		case 0:
			shouldQuit = true;
			break;

		case 1:
			//Update Title
			
			do {

				printf("Updated task title: ");
				fgets(newTitle, TITLE_LENGTH, stdin);
				if (strlen(newTitle) + 1 == TITLE_LENGTH)
				{
					clearStdin();
				}
				else
				{
					newTitle[strlen(newTitle) - 1] = '\0';
				}

			} while (strlen(newTitle) == 0);
			
			if (verifyAbortChar(newTitle))
				return;

			updateTaskTitle(task, newTitle);
			break;

		case 2:
			//Update Note

			printf("Updated task note: ");
			fgets(newTaskNote, MAX_LENGTH, stdin);
			if (strlen(newTaskNote) + 1 == MAX_LENGTH)
			{
				clearStdin();
			}
			else
			{
				newTaskNote[strlen(newTaskNote) - 1] = '\0';
			}
			
			if (strlen(newTaskNote) == 0) {

				strcpy_s(newTaskNote, MAX_LENGTH, "No note created.");

			}
			
			if (verifyAbortChar(newTaskNote))
				return;

			updateTaskNote(task, newTaskNote);
			break;

		case 3:
			//Update Due Date
			do {
				printf("Updated due date (YYYY/MM/DD): ");
				scanf_s("%d/%d/%d", &newDueYear, &newDueMonth, &newDueDay);
				clearStdin();
				if (verifyAbortInt(newDueYear))
					return;

			} while (!dateValidation(newDueYear, newDueMonth, newDueDay));

			snprintf(newDueDate, DATE_STRING_LENGTH, "%d/%d/%d", newDueYear, newDueMonth, newDueDay);
			updateTaskDate(task, newDueDate);
			break;

		case 4:
			//Update Priority
			do {
				printf("Updated priority (Low, Medium, High): ");
				scanf_s("%s", newPriority, MAX_LENGTH);
				clearStdin();
				if (verifyAbortChar(newPriority))
					return;

				newPriorityNum = getPriorityFromString(newPriority);
				if (newPriorityNum == PRIORITY_INVALID)
				{
					printf("Invalid Input.\n");
				}
			} while (newPriorityNum == PRIORITY_INVALID);
			updateTaskPriority(task, newPriorityNum);
			break;

		case 5:
			//Update Label
			do {
				printf("Updated label (");
				printLabels();
				printf("): ");
				scanf_s("%s", newLabel, MAX_LABEL_LEN);
				clearStdin();
				if (verifyAbortChar(newLabel))
					return;

				newLabelNum = getLabelNumber(newLabel);
				if (newLabelNum == LABEL_INVALID)
				{
					printf("Invalid Input.\n");
				}
			} while (newLabelNum == LABEL_INVALID);

			updateTaskLabel(task, newLabelNum);
			break;

		default:
			printf("ERROR: Invalid Numeric Entry.");
			break;
		}
	} while (!shouldQuit);

}

/// <summary>
/// Displays the search menu
/// </summary>
/// <param name="taskList">Pointer of taskList</param>
/// <author>Gavin</author>
void searchMenu(PTASKLIST taskList) {	
	bool shouldQuit = false;

	do {
		
		printf("Search Menu---------------\n");
		printf("1. Search by keyword\n");
		printf("2. Search by label\n");
		printf("0. Back\n");

		printf("\nEnter in numeric menu option: ");
		int menuInput = integerValidation();

		switch (menuInput)
		{
		case 1:
			searchByString(taskList);
			break;
		case 2:
			searchByLabel(taskList);
			break;
		case 0:
			shouldQuit = true;
			break;
		default:
			printf("ERROR: Invalid Numeric Entry.");
			break;

		}
	} while (!shouldQuit);

}

/// <summary>
/// Searches the list via a label input
/// </summary>
/// <param name="taskList">Task list being searched</param>
/// <author>Everybody</author>
void searchByLabel(PTASKLIST taskList) {
	char searchInput[MAX_LABEL_LEN];

	printf("Search by labels: ");

	fgets(searchInput, MAX_LABEL_LEN, stdin);
	if (strlen(searchInput) + 1 == MAX_LABEL_LEN)
	{
		clearStdin();
	}
	else
	{
		searchInput[strlen(searchInput) - 1] = '\0';
	}
	if (verifyAbortChar(searchInput))
		return;

	printf("\n");

	if (!displayLabelMatch(taskList, searchInput)) {
		printf("No matches found.");
	 }

	printf("\n");

}

/// <summary>
/// Searches by string via title and note
/// </summary>
/// <param name="taskList">TaskList being searched</param>
/// <author>Everybody</author>
void searchByString(PTASKLIST taskList) {
	char searchInput[MAX_LENGTH];

	printf("Search titles and notes by entering a keyword: ");

	fgets(searchInput, MAX_LENGTH, stdin);
	if (strlen(searchInput) + 1 == MAX_LENGTH)
	{
		clearStdin();
	}
	else
	{
		searchInput[strlen(searchInput) - 1] = '\0';
	}
	if (verifyAbortChar(searchInput))
		return;

	printf("\n");

	if (!displayStringMatch(taskList, searchInput)) {
		printf("No matches found.");
	}

	printf("\n");
}

/// <summary>
/// Displays the menu for search by range options
/// </summary>
/// <param name="taskList">Tasklist pointer</param>
/// <author>Gavin</author>
void displayRangeMenu(PTASKLIST taskList) {
	bool shouldQuit = false;

	do {

		printf("Range Menu---------------\n");
		printf("1. Search range of dates\n");
		printf("2. Search range of priority\n");
		printf("0. Back\n");

		printf("\nEnter in numeric menu option: ");
		int menuInput = integerValidation();

		switch (menuInput)
		{
		case 1:
			searchDateRange(taskList);
			break;
		case 2:
			searchPriorityRange(taskList);
			break;
		case 0:
			shouldQuit = true;
			break;
		default:
			printf("ERROR: Invalid Numeric Entry.");
			break;

		}
	} while (!shouldQuit);

}

/// <summary>
/// Obtains the user input and searching via date through the list 
/// </summary>
/// <param name="taskList">Task list to be searched</param>
/// <author>Everybody</author>
void searchDateRange(PTASKLIST taskList) {
	int day;
	int month;
	int year;

	char earlyDateString[DATE_STRING_LENGTH];
	char lateDateString[DATE_STRING_LENGTH];
	
	do {
		printf("\nEnter earliest date (YYYY/MM/DD): ");
		scanf_s("%d/%d/%d", &year, &month, &day);
		clearStdin();
		if (verifyAbortInt(year))
			return;

	} while (!dateValidation(year, month, day));
	sprintf_s(earlyDateString, DATE_STRING_LENGTH, "%d/%d/%d", year, month, day);


	do {
		printf("\nEnter latest date (YYYY/MM/DD): ");
		scanf_s("%d/%d/%d", &year, &month, &day);
		clearStdin();
		if (verifyAbortInt(year))
			return;

	} while (!dateValidation(year, month, day));
	sprintf_s(lateDateString, DATE_STRING_LENGTH, "%d/%d/%d", year, month, day);

	if (!displayDateRange(taskList, earlyDateString, lateDateString)) {
		printf("No results found.\n");
	}

}

/// <summary>
/// Obtains user input and searches through the list via priority range
/// </summary>
/// <param name="taskList">Tasklist begin searched</param>
/// <author>Everybody</author>
void searchPriorityRange(PTASKLIST taskList) {
	
	char leastPriority[MAX_LENGTH];
	int leastPriorityNum;

	char greatestPriority[MAX_LENGTH];
	int greatestPriorityNum;

	do {
		printf("\nLeast Priority (Low, Medium, High): ");
		scanf_s("%s", leastPriority, MAX_LENGTH);
		clearStdin();
		if (verifyAbortChar(leastPriority))
			return;

		leastPriorityNum = getPriorityFromString(leastPriority);
		if (leastPriorityNum == PRIORITY_INVALID)
		{
			printf("Invalid Input.\n");
		}
	} while (leastPriorityNum == PRIORITY_INVALID);

	do {
		printf("\nGreatest priority (Low, Medium, High): ");
		scanf_s("%s", greatestPriority, MAX_LENGTH);
		clearStdin();
		if (verifyAbortChar(greatestPriority))
			return;

		greatestPriorityNum = getPriorityFromString(greatestPriority);
		if (greatestPriorityNum == PRIORITY_INVALID)
		{
			printf("Invalid Input.\n");
		}
	} while (greatestPriorityNum == PRIORITY_INVALID);
	
	if (!displayPriorityRange(taskList, leastPriorityNum, greatestPriorityNum)) {
		printf("No results found.\n");
	}

}

/// <summary>
/// Displays a number for a list
/// </summary>
/// <param name="number">Number to be printed</param>
/// <author>Everybody</author>
void printListNumbering(int number) 
{
	printf("%d. ", number);
}

/// <summary>
/// Print the names of all the labels
/// </summary>
/// <author>Everybody</author>
void printLabels() {

	for (int i = 0; i < LABELSIX; i++) {

		printf("%s, ", getLabelName(i));

	}

	printf("%s", getLabelName(LABELSIX));

}

/// <summary>
/// Displays menu for user to change pre-defined label names
/// </summary>
/// <author>Everybody</author>
void modifyLabelsMenu() {
	char newLabelName[MAX_LABEL_LEN];
	int menuInput;
	
	printf("Alter Labels Menu--------\n");
	
	for (int i = 0; i <= LABELSIX; i++) {
		printListNumbering(i+1);
		printf("%s\n", getLabelName(i));

	}

	do {
		printf("Select a label by number to change: ");

		menuInput = integerValidation();
		if (verifyAbortInt(menuInput))
			return;

		menuInput--;
	} while (menuInput < LABELONE && menuInput > LABELSIX);

	printf("\n");

	do {
		printf("Enter new label name: ");
		fgets(newLabelName, MAX_LABEL_LEN, stdin);
		if (strlen(newLabelName) + 1 == MAX_LABEL_LEN)
		{
			clearStdin();
		}
		else
		{
			newLabelName[strlen(newLabelName) - 1] = '\0';
		}
	} while (strlen(newLabelName) == 0);

	if (verifyAbortChar(newLabelName))
		return;

	modifyLabel(menuInput, newLabelName);

}