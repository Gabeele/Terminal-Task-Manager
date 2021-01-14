//PROG71985 Programing Princples 
//Assignment Group Project
//
//Gavin Abeele, Kevin McDaniel, Brayden Bowler
//
//Framework to handle Label management
#include "labels.h"

/// <summary>
/// Save label names to file
/// </summary>
/// <returns>true if successful</returns>
/// <author>Kevin</author>
bool saveLabels()
{
	FILE* fpSave;
	fopen_s(&fpSave, LABELS_FILENAME, "w+");
	if (fpSave == NULL)
	{
		return false;
	}

	for (int i = 0; i <= LABELSIX; i++)
	{
		fwrite(labels[i], sizeof(char), strlen(labels[i]), fpSave);
		fputc('\n', fpSave);
	}
	fclose(fpSave);
	return true;
}

/// <summary>
/// Load label names from file
/// </summary>
/// <returns>true if successful</returns>
/// <author>Kevin</author>
bool loadLabels()
{
	FILE* fpLoad;
	fopen_s(&fpLoad, LABELS_FILENAME, "r");
	if (fpLoad == NULL)
	{
		return false;
	}

	char inputBuffer[MAX_LABEL_LEN];
	for (int i = 0; i <= LABELSIX; i++)
	{
		fgets(inputBuffer, MAX_LABEL_LEN, fpLoad);
		if (inputBuffer == EOF)
		{
			break;
		}
		inputBuffer[strlen(inputBuffer) - 1] = '\0';
		strncpy_s(&labels[i], MAX_LABEL_LEN, inputBuffer, MAX_LABEL_LEN);
	}
	fclose(fpLoad);
	return true;
}

/// <summary>
/// Get the label number based on name
/// </summary>
/// <param name="labelName">name of label</param>
/// <returns>number of label</returns>
/// <author>Kevin</author>
LABEL getLabelNumber(char labelName[])
{
	char upperGivenLabelName[MAX_LABEL_LEN];
	for (int i = 0; i < strlen(labelName); i++)
	{
		upperGivenLabelName[i] = toupper(labelName[i]);
	}
	upperGivenLabelName[strlen(labelName)] = '\0';

	char upperExistingLabelName[MAX_LABEL_LEN];
	for (int i = 0; i <= LABELSIX; i++)
	{
		for (int j = 0; j < strlen(labels[i]); j++)
		{
			upperExistingLabelName[j] = toupper(labels[i][j]);
		}
		upperExistingLabelName[strlen(labels[i])] = '\0';

		if (!strncmp(upperExistingLabelName, upperGivenLabelName, MAX_LABEL_LEN))
		{
			return (LABEL)i;
		}
	}
	return LABEL_INVALID;
}

/// <summary>
/// Get label name from label number
/// </summary>
/// <param name="labelNum">number of label</param>
/// <returns>name of label</returns>
/// <author>Kevin</author>
char* getLabelName(LABEL labelNum)
{
	return labels[labelNum];
}

/// <summary>
/// Change the name of a label
/// </summary>
/// <param name="labelNum">number of label</param>
/// <param name="newLabelName">new label name</param>
/// <author>Kevin</author>
void modifyLabel(LABEL labelNum, char newLabelName[])
{
	strncpy_s(&labels[labelNum], MAX_LABEL_LEN, newLabelName, MAX_LABEL_LEN);
	saveLabels();
}
