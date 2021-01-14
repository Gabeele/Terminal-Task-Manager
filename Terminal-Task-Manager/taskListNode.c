//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Nodes of a linked list holding tasks
#include "taskListNode.h"

/// <summary>
/// Creates a new task node without connection
/// </summary>
/// <param name="task">task to be inserted into node</param>
/// <returns>new task node</returns>
/// <author>Everybody</author>
PTASKNODE createTaskNode(TASK task) {

	PTASKNODE newNode = (PTASKNODE)malloc(sizeof(TASKNODE));

	if (!newNode) {
		exit(1);
	}

	newNode->task = task;
	newNode->next = NULL;

	return newNode;
}

/// <summary>
/// Connects 2 task nodes
/// </summary>
/// <param name="currentNode">task node to reference next node</param>
/// <param name="nextNode">task node to be referenced</param>
/// <author>Everybody</author>
void setNextTaskNode(PTASKNODE currentNode, PTASKNODE nextNode)
{
	currentNode->next = nextNode;
}

/// <summary>
/// Get the next task node from task node
/// </summary>
/// <param name="currentNode">task node to get next task node from</param>
/// <returns>next task node of given task node</returns>
/// <author>Everybody</author>
PTASKNODE getNextTaskNode(PTASKNODE currentNode)
{
	return currentNode->next;
}

/// <summary>
/// Get task contained in task node
/// </summary>
/// <param name="currentNode">task node containing task</param>
/// <returns>task from task node</returns>
/// <author>Everybody</author>
PTASK getTaskFromTaskNode(PTASKNODE currentNode)
{
	return &currentNode->task;
}

/// <summary>
/// Frees allocated memory of given task node
/// </summary>
/// <param name="currentNode">task node to be disposed</param>
/// <author>Everybody</author>
void disposeTaskNode(PTASKNODE currentNode)
{
	disposeTask(currentNode->task);
	free(currentNode);
}