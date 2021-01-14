//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//List of tasks ADT
#include "taskList.h"

/// <summary>
/// Creates a new empty task list
/// </summary>
/// <returns>new empty Tasklist</returns>
/// <author>Everybody</author>
TASKLIST createTaskList()
{
	TASKLIST newTaskList = { NULL };
	return newTaskList;
}

/// <summary>
/// Sets the first element of the task list
/// </summary>
/// <param name="taskList">task list to modify</param>
/// <param name="node">task node to set as head</param>
/// <author>Everybody</author>
void setHead(PTASKLIST taskList, PTASKNODE node)
{
	taskList->tasklistHead = node;
}

/// <summary>
/// Appends a task node to the end of the task list
/// </summary>
/// <param name="taskList">task list to append to</param>
/// <param name="newTask">task node to be appended</param>
/// <author>Everybody</author>
void appendToTaskList(PTASKLIST taskList, TASK newTask)
{
	PTASKNODE currentNode = taskList->tasklistHead;
	if (currentNode == NULL)
	{
		setHead(taskList, createTaskNode(newTask));
		return;
	}
	PTASKNODE nextNode = getNextTaskNode(currentNode);

	while (nextNode != NULL)
	{
		currentNode = nextNode;
		nextNode = getNextTaskNode(currentNode);
	}

	PTASKNODE newNode = createTaskNode(newTask);
	setNextTaskNode(currentNode, newNode);
}

/// <summary>
/// Removes an existing task from the task list
/// </summary>
/// <param name="taskList">task list to have task removed</param>
/// <param name="task">task held in task list to be removed</param>
/// <author>Everybody</author>
void removeFromTaskList(PTASKLIST taskList, TASK task)
{
	PTASKNODE previousNode = taskList->tasklistHead;
	PTASKNODE currentNode = taskList->tasklistHead;
	if (currentNode == NULL)
	{
		return;
	}
	PTASKNODE nextNode = getNextTaskNode(currentNode);

	while (currentNode != NULL && !compareTasks(task, *getTaskFromTaskNode(currentNode)))
	{
		previousNode = currentNode;
		currentNode = nextNode;
		nextNode = getNextTaskNode(currentNode);
	}

	if (previousNode == currentNode && nextNode == NULL)
	{
		setHead(taskList, NULL);
	}
	else if (previousNode == currentNode)
	{
		setHead(taskList, nextNode);
	}
	else
	{
		setNextTaskNode(previousNode, nextNode);
	}
	disposeTaskNode(currentNode);
}

/// <summary>
/// Gets a task from task list based on index
/// </summary>
/// <param name="taskList">task list containing task</param>
/// <param name="index">index of the task</param>
/// <returns>the task at index</returns>
/// <author>Everybody</author>
PTASK getTaskFromTaskList(PTASKLIST taskList, int index)
{
	PTASKNODE currentNode = taskList->tasklistHead;
	for (int i = 0; i < index; i++)
	{
		if (currentNode == NULL)
		{
			exit(1);
		}
		currentNode = getNextTaskNode(currentNode);
	}
	return getTaskFromTaskNode(currentNode);
}


/// <summary>
/// Gets the length of the task list
/// </summary>
/// <param name="taskList">task list to get length of</param>
/// <returns>length of task list</returns>
/// <author>Everybody</author>
int getTaskListLength(PTASKLIST taskList)
{
	PTASKNODE currentNode = taskList->tasklistHead;
	int counter = 0;
	while (currentNode != NULL)
	{
		counter++;
		currentNode = getNextTaskNode(currentNode);
	}
	return counter;
}

/// <summary>
/// Removes all tasks from task list and disposed them
/// </summary>
/// <param name="taskList">task list to empty</param>
/// <author>Everybody</author>
void emptyTaskList(PTASKLIST taskList)
{
	int length = getTaskListLength(taskList);
	for (int i = length; i > 0; i--)
	{
		removeFromTaskList(taskList, *getTaskFromTaskList(taskList, i-1));
	}
}

/// <summary>
/// Prints all tasks within task list
/// </summary>
/// <param name="taskList">task list to print</param>
/// <author>Everybody</author>
void printTaskList(PTASKLIST taskList)
{
	PTASKNODE currentNode = taskList->tasklistHead;
	int counter = 0;
	while (currentNode != NULL)
	{
		//pointers to the printing functions
		(*printCounterFuncPtr)(++counter);
		(*printTaskFuncPtr)(*getTaskFromTaskNode(currentNode));
		currentNode = getNextTaskNode(currentNode);
	}
}

/// <summary>
/// Saves the entire taskList to file
/// </summary>
/// <param name="tasklist">TaskList to be saved</param>
/// <returns>true if successful</returns>
/// <author>Brayden</author>
bool saveTaskListFile(TASKLIST tasklist) {

	FILE* fpDestination;
	fopen_s(&fpDestination, TASKLIST_FILENAME, "w+");
		
	if (fpDestination == NULL) {

		fprintf(stderr, "Unable to open %s for saving\n", TASKLIST_FILENAME);
		return false;

	}

	saveTaskIdCounter(fpDestination);

	PTASKNODE currentNode = tasklist.tasklistHead;

	while (currentNode != NULL) {

		saveTask((*getTaskFromTaskNode(currentNode)), fpDestination);
		currentNode = getNextTaskNode(currentNode);

	}

	fclose(fpDestination);
	return true;
}

/// <summary>
/// Load an entire tasklist from a file
/// </summary>
/// <param name="taskList">TaskList to be loaded into</param>
/// <returns>true if successful</returns>
/// <author>Kevin</author>
bool loadTaskListFile(PTASKLIST taskList)
{
	FILE* fpLoad;
	fopen_s(&fpLoad, TASKLIST_FILENAME, "r");
	if (fpLoad == NULL)
	{
		return false;
	}
	emptyTaskList(taskList);

	if (!readTaskIdCounter(fpLoad))
	{
		return false;
	}

	PTASKNODE currentNode = taskList->tasklistHead;
	while (!feof(fpLoad))
	{
		TASK task = readTask(fpLoad);
		if (getTaskID(task) > 0) {
			if (currentNode == NULL)
			{
				setHead(taskList, createTaskNode(task));
				currentNode = taskList->tasklistHead;
			}
			else
			{
				setNextTaskNode(currentNode, createTaskNode(task));
				currentNode = getNextTaskNode(currentNode);
			}
		}
	}
	fclose(fpLoad);
	return true;
}

/// <summary>
/// Find and display range of tasks based on priority
/// </summary>
/// <param name="taskList">TaskList being searched</param>
/// <param name="leastPriority">lower priority bounds</param>
/// <param name="greatestPriority">upper priority bounds</param>
/// <returns>true if 1 or more tasks found</returns>
/// <author>Everybody</author>
bool displayPriorityRange(PTASKLIST taskList, PRIORITYRATING leastPriority, PRIORITYRATING greatestPriority) {
	int counter = 0;
	bool rangeFound = false;

	PTASKNODE currentNode = taskList->tasklistHead;	

	while (currentNode != NULL) {

		PTASK task = getTaskFromTaskNode(currentNode);
		PRIORITYRATING taskPriority = getTaskPriority(*task);

		if (leastPriority <= taskPriority && greatestPriority >= taskPriority) {
			
			(*printCounterFuncPtr)(++counter);
			(*printTaskFuncPtr)(*task);
			rangeFound = true;
		}

		currentNode = getNextTaskNode(currentNode);

	}

	return rangeFound;
}

/// <summary>
/// Find and display range of tasks based on date
/// </summary>
/// <param name="taskList">TaskList being searched</param>
/// <param name="combinedLower">lower date bounds</param>
/// <param name="combinedUpper">upper date bounds</param>
/// <returns>true if 1 or more tasks found</returns>
/// <author>Everybody</author>
bool displayDateRange(PTASKLIST taskList, char combinedLower[], char combinedUpper[]) {
	bool rangeFound = false;
	int counter = 0;
	int year;
	int month;
	int day;

	//combined dates are single int Eg. YYYYMMDD
	int combinedEarlyDate;
	int combinedLateDate;
	int combinedNodeDate;

	char taskDate[DATE_STRING_LENGTH];

	PTASKNODE currentNode = taskList->tasklistHead;	

	sscanf_s(combinedLower, "%d/%d/%d", &year, &month, &day);
	combinedEarlyDate = (year * YEAR_OFFSET_MULTIPLIER) + (month * MONTH_OFFSET_MULTIPLIER) + day;

	sscanf_s(combinedUpper, "%d/%d/%d", &year, &month, &day);
	combinedLateDate = (year * YEAR_OFFSET_MULTIPLIER) + (month * MONTH_OFFSET_MULTIPLIER) + day;

	while (currentNode != NULL) {
		PTASK task = getTaskFromTaskNode(currentNode);

		getTaskDate(*task, taskDate);
		sscanf_s(taskDate, "%d/%d/%d", &year, &month, &day);
		combinedNodeDate = (year * YEAR_OFFSET_MULTIPLIER) + (month * MONTH_OFFSET_MULTIPLIER) + day;


		if (combinedEarlyDate <= combinedNodeDate && combinedLateDate >= combinedNodeDate) {
			(*printCounterFuncPtr)(++counter);
			(*printTaskFuncPtr)(*task);
			rangeFound = true;
		}

		currentNode = getNextTaskNode(currentNode);

	}

	return rangeFound;

}

/// <summary>
/// Find and display task matches based on title and note search
/// </summary>
/// <param name="taskList">TaskList being searched</param>
/// <param name="searchInput">search keyword</param>
/// <returns>true if 1 or more tasks found</returns>
/// <author>Everybody</author>
bool displayStringMatch(PTASKLIST taskList, char searchInput[])
{
	bool matchFound = false;
	int counter = 0;
	char tempTitle[TITLE_LENGTH];
	char tempNote[MAX_LENGTH];
	PTASKNODE currentNode = taskList->tasklistHead;

	uppercaseString(searchInput, searchInput);

	while (currentNode != NULL)
	{

		PTASK task = getTaskFromTaskNode(currentNode);
		getTaskTitle(*task, tempTitle);
		uppercaseString(tempTitle, &tempTitle);
		uppercaseString(getTaskNote(*task), &tempNote);

		if ((strstr((tempTitle), (searchInput)) != NULL) || (strstr((tempNote), (searchInput)) != NULL)) {

			(*printCounterFuncPtr)(++counter);

			(*printTaskFuncPtr)(*task);
			matchFound = true;
		}

		currentNode = getNextTaskNode(currentNode);
	}
	return matchFound;
}

/// <summary>
/// Find and display task matches based on label search
/// </summary>
/// <param name="taskList">TaskList being searched</param>
/// <param name="labelInput">search keyword</param>
/// <returns>true if 1 or more tasks found</returns>
/// <author>Everybody</author>
bool displayLabelMatch(PTASKLIST taskList, char labelInput[])
{
	bool matchFound = false;
	int counter = 0;
	char tempLabel[MAX_LENGTH];
	PTASKNODE currentNode = taskList->tasklistHead;

	uppercaseString(labelInput, labelInput);

	while (currentNode != NULL)
	{
		PTASK task = getTaskFromTaskNode(currentNode);
		uppercaseString(getLabelName(getTaskLabel(*task)), &tempLabel);

		if (strstr(tempLabel, labelInput) != NULL) {

			(*printCounterFuncPtr)(++counter);

			(*printTaskFuncPtr)(*task);

			matchFound = true;
		}

		currentNode = getNextTaskNode(currentNode);
	}
	return matchFound;
}

/// <summary>
/// Sets a function pointer for the print counter function
/// </summary>
/// <param name="pointerFunction">Pointer of the function to set</param>
/// <author>Everybody</author>
void setCounterFunctionPointer(void* pointerFunction)
{
	printCounterFuncPtr = pointerFunction;

}

/// <summary>
/// Sets a function pointer for the print task function
/// </summary>
/// <param name="pointerFunction">Pointer of the function to set</param>
/// <author>Everybody</author>
void setTaskFunctionPointer(void* pointerFunction)
{
	printTaskFuncPtr = pointerFunction;
}

/// <summary>
/// Changes a string to uppercase
/// </summary>
/// <param name="string">Source string</param>
/// <param name="upperString">Destination of a upper case copy</param>
/// <author>Gavin</author>
void uppercaseString(char string[], char* upperString) {

	for (int i = 0; i < strlen(string); i++) {

		upperString[i] = toupper(string[i]);
	}

}