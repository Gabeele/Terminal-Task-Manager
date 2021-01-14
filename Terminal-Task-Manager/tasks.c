//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Framework for a task
#include "tasks.h"

/// <summary>
/// Creates a new task, initializing all data
/// </summary>
/// <param name="taskTitle">main title of the task</param>
/// <param name="taskNote">additional notes for the task</param>
/// <param name="dueDate">due date of the task</param>
/// <param name="priority">priority of completion</param>
/// <param name="label">given label for the task</param>
/// <returns>new task</returns>
/// <author>Everybody</author>
TASK createTask(char taskTitle[], char taskNote[], char dueDate[], PRIORITYRATING priority, LABEL label) {

	TASK newTask;

	newTask.id = taskCounter++;	//taskCounter stored in file

	strncpy_s(newTask.title, TITLE_LENGTH, taskTitle, TITLE_LENGTH);
	
	newTask.note = (char*)malloc(strlen(taskNote) + 1);

	if (newTask.note == NULL)
	{
		exit(1);
	}

	strncpy_s(newTask.note, strlen(taskNote) + 1, taskNote, strlen(taskNote));

	sscanf_s(dueDate, "%d/%d/%d", &newTask.dueYear, &newTask.dueMonth, &newTask.dueDay);

	newTask.priority = priority;

	newTask.label = label;

	return newTask;
}

/// <summary>
/// Compares 2 tasks to determine if they are the same task
/// </summary>
/// <param name="task1">task to be compared</param>
/// <param name="task2">task to be compared</param>
/// <returns>true if tasks are the same</returns>
/// <author>Everybody</author>
bool compareTasks(TASK task1, TASK task2) 
{
	if (task1.id == task2.id)
	{
		return true;
	}
	return false;
}

/// <summary>
/// Frees allocated memory of given task
/// </summary>
/// <param name="task">task to dispose</param>
/// <author>Everybody</author>
void disposeTask(TASK task) {

	if (task.note) {
		free(task.note);
	}
};

/// <summary>
/// Get the priority value from string
/// </summary>
/// <param name="input">String from input</param>
/// <returns>Enum value</returns>
/// <author>Everybody</author>
PRIORITYRATING getPriorityFromString(char input[]) {

	char upperInput[MAX_LENGTH];
	for (int i = 0; i < strlen(input); i++)
	{
		upperInput[i] = toupper(input[i]);

	}
	upperInput[strlen(input)] = '\0';

	if (strcmp(upperInput, "LOW") == 0)
	{
		return LOW;
	}
	else if (strcmp(upperInput, "MEDIUM") == 0)
	{
		return MEDIUM;
	}
	else if (strcmp(upperInput, "HIGH") == 0)
	{
		return HIGH;
	}
	else {
		return PRIORITY_INVALID;
	}

}

/// <summary>
/// Get priority string from value
/// </summary>
/// <param name="priority">priority enum value</param>
/// <returns>string representation of enum</returns>
/// <author>Everybody</author>
char* getStringFromPriority(PRIORITYRATING priority)
{
	switch (priority)
	{
	case LOW:
		return "Low";
	case MEDIUM:
		return "Medium";
	case HIGH:
		return "High";
	default:
		break;
	}
}

/// <summary>
/// Update task title
/// </summary>
/// <param name="task">task to be updated</param>
/// <param name="updatedTitle">new title for task</param>
/// <author>Everybody</author>
void updateTaskTitle(PTASK task, char updatedTitle[]) {

	strncpy_s(task->title, TITLE_LENGTH, updatedTitle, TITLE_LENGTH);

}

/// <summary>
/// Update task note
/// </summary>
/// <param name="task">task to be updated</param>
/// <param name="updatedTitle">new note for task</param>
/// <author>Everybody</author>
void updateTaskNote(PTASK task, char updatedNote[]) {

	free(task->note);

	task->note = (char*)malloc(strlen(updatedNote) + 1);

	if (task->note == NULL)
	{
		exit(1);
	}

	strncpy_s(task->note, strlen(updatedNote) + 1, updatedNote, strlen(updatedNote));

}

/// <summary>
/// Update task due date
/// </summary>
/// <param name="task">task to be updated</param>
/// <param name="updatedTitle">new due date for task</param>
/// <author>Everybody</author>
void updateTaskDate(PTASK task, char updatedDate[]) {

	sscanf_s(updatedDate, "%d/%d/%d", &task->dueYear, &task->dueMonth, &task->dueDay);

}

/// <summary>
/// Update task priority
/// </summary>
/// <param name="task">task to be updated</param>
/// <param name="updatedTitle">new priority for task</param>
/// <author>Everybody</author>
void updateTaskPriority(PTASK task, PRIORITYRATING updatedRating) {

	task->priority = updatedRating;
	
}

/// <summary>
/// Update task label
/// </summary>
/// <param name="task">task to be updated</param>
/// <param name="updatedTitle">new label for task</param>
/// <author>Everybody</author>
void updateTaskLabel (PTASK task, LABEL updatedLabel) {

	task->label = updatedLabel;

}

/// <summary>
/// Save task to file pointer
/// </summary>
/// <param name="task">task to be saved</param>
/// <param name="fpSource">opened file pointer with write access</param>
/// <author>Brayden</author>
void saveTask(TASK task, FILE* fpSource) {

	fprintf_s(fpSource, "%d||%s||%s||%d/%d/%d||%d||%d\n", task.id, task.title, task.note, task.dueYear, task.dueMonth, task.dueDay, task.priority, task.label);
	
}

/// <summary>
/// Read task from file pointer
/// </summary>
/// <param name="fpSource">opened file pointer with read access</param>
/// <returns>new task with read data</returns>
/// <author>Kevin</author>
TASK readTask(FILE* fpLoad)
{
	TASK newTask;
	char taskNote[MAX_LENGTH];
	//since note can be size of MAX_LENGTH, 
	//inputBuffer needs to be larger to accomodate the rest of the data we multiply by 2
	char inputBuffer[MAX_LENGTH * 2]; 
	fgets(inputBuffer, MAX_LENGTH * 2, fpLoad);
	int scannedItems;

	scannedItems = sscanf_s(inputBuffer, "%d||%[^|]||%[^|]||%d/%d/%d||%d||%d", 
		&newTask.id, newTask.title, TITLE_LENGTH, &taskNote, MAX_LENGTH, 
		&newTask.dueYear, &newTask.dueMonth, &newTask.dueDay, &newTask.priority, &newTask.label);
	
	if (scannedItems == EOF) {
		newTask.id = -1; //Invalid
		return newTask;
	}

	taskNote[MAX_LENGTH - 1] = '\0';
	newTask.note = (char*)malloc(strlen(taskNote) + 1);
	if (newTask.note == NULL)
	{
		exit(1);
	}
	strncpy_s(newTask.note, strlen(taskNote) + 1, taskNote, strlen(taskNote));
	return newTask;
}

/// <summary>
/// Get id from task
/// </summary>
/// <param name="task">task to get data from</param>
/// <returns>the task id</returns>
/// <author>Gavin</author>
int getTaskID(TASK task) {
	return (task.id);

}

/// <summary>
/// Get title from task
/// </summary>
/// <param name="task">task to get data from</param>
/// <param name="taskTitlePlaceholder">the task title</param>
/// <author>Gavin</author>
void getTaskTitle(TASK task, char taskTitlePlaceholder[]) {
	strncpy_s(taskTitlePlaceholder, TITLE_LENGTH, task.title, TITLE_LENGTH);

}

/// <summary>
/// Get note from task
/// </summary>
/// <param name="task">task to get data from</param>
/// <returns>the task note</returns>
/// <author>Gavin</author>
char* getTaskNote(TASK task) {
	return (task.note);

}

/// <summary>
/// Get due date from task
/// </summary>
/// <param name="task">task to get data from</param>
/// <param name="taskTitlePlaceholder">the task due date</param>
/// <author>Gavin</author>
void getTaskDate(TASK task, char taskDate[]) {

	sprintf_s(taskDate, DATE_STRING_LENGTH, "%d/%d/%d", task.dueYear, task.dueMonth, task.dueDay);

}

/// <summary>
/// Get priority from task
/// </summary>
/// <param name="task">task to get data from</param>
/// <returns>the task priority</returns>
/// <author>Gavin</author>
PRIORITYRATING getTaskPriority(TASK task) {
	return (task.priority);

}

/// <summary>
/// Get label from task
/// </summary>
/// <param name="task">task to get data from</param>
/// <returns>the task label</returns>
/// <author>Gavin</author>
LABEL getTaskLabel(TASK task) {
	return (task.label);
}

/// <summary>
/// Read task counter value from file pointer
/// </summary>
/// <param name="fpLoad">opened file pointer with read access</param>
/// <returns>true if successful</returns>
/// <author>Brayden, Kevin</author>
bool readTaskIdCounter(FILE* fpLoad)
{
	char inputBuffer[DATE_STRING_LENGTH];
	fgets(inputBuffer, DATE_STRING_LENGTH, fpLoad);
	int scannedItems = sscanf_s(inputBuffer, "%d", &taskCounter);
	if (scannedItems == 0)
	{
		return false;
	}
	return true;
}

/// <summary>
/// Save task counter value to file pointer
/// </summary>
/// <param name="fpSave">opened file pointer with write access</param>
/// <author>Brayden, Kevin</author>
void saveTaskIdCounter(FILE* fpSave)
{
	fprintf_s(fpSave, "%d\n", taskCounter);
}