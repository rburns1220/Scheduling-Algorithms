// Armand Alvarez
// Ryan Burns
// Sean Simonian
// COP 4600 Spring 2018 Programming Assignment 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// -------------- Description -----------------
/*
  Objective: Parse the input file and return a Data object.

  Data Object Elements:
    - int processcount - The number of processes to be scheduled.
    - int runfor - The amount of total time alotted to schedule them.
    - int quantum - The quantum size for running RR algorithm.
    - char* algorithm - String identifying the algorithm to be used (rr, fcfs, sjf)
    - PCB** pcbArray - An Array of PCBs to be scheduled (includes their name, burst, and arrivalTime)
  Function Data* parsefile(char* filename)
    - Receives a string of the file to be parsed and returns an a pointer to a Data object containing the parsed info.

*/

typedef struct
{
	int processcount;
	int runfor;
	int quantum;
	int initializedPCBs;
	char* algorithm;
	PCB** pcbArray;

} Data;

Data* parseFile (char* filename);
void destroyData(Data*);
int strToInt(char* str);

Data* parseFile (char* filename)
{
	FILE* fp = fopen(filename, "r");
	Data* data;
	char* line = malloc(sizeof(char) * 128);
	char* word = NULL;
	char* num;
	char* arrival;
	char* burst;
	int i, k, length;
	int wordLen, nameLen, arrivalLen, burstLen;

	if(fp == NULL)
        return NULL;

    data = malloc(sizeof(Data));
	data->initializedPCBs = 0;

    while (fgets(line, 128, fp) != NULL)
    {
		length = strlen(line);
        word = malloc(sizeof(char) * (strlen(line) + 1));
		k = 0;

		for (i = 0; i < length; i++)
		{
			// Ignore #
			if (*(line + i) == '#' || *(line + i) == '\n')
				break;

			// Skip Spaces
			else if (*(line + i) == ' ' || *(line + i) == '\t' )
				continue;

			else
			{
				*(word + k) = *(line + i);
				k++;
			}

		}
		*(word + k) = '\0';
		wordLen = strlen(word);

		// Processcount
		if (strstr(word, "processcount") != NULL)
		{
			// I give num the room of the word minus the "processcount" space.
			num = malloc(sizeof(char) * ((wordLen) - 12 + 1));

			// Start at the index where the value is and add it to a string. Then convert that string
			// into the integer it represents.
			for (i = 12; i < wordLen; i++)
				*(num + (i - 12)) = *(word + i);

			*(num + (i - 12)) = '\0';
			data->processcount = strToInt(num);
			data->pcbArray = malloc(sizeof(PCB*) * data->processcount);

			for (i = 0; i < data->processcount; i++)
				data->pcbArray[i] = createEmptyPCB();


			free(num);
		}
		// Run For
		else if (strstr(word, "runfor") != NULL)
		{
			num = malloc(sizeof(char) * ((wordLen) - 6 + 1));

			for (i = 6; i < wordLen; i++)
				*(num + (i - 6)) = *(word + i);

			*(num + i - 6) = '\0';
			data->runfor = strToInt(num);
			free(num);
		}
		// Use
		else if(strstr(word, "use") != NULL)
		{
			// The algorithm will be after the "use".
			data->algorithm = malloc(sizeof(char) * (wordLen - 3 + 1));

			for (i = 3; i < wordLen; i++)
				data->algorithm[i - 3] = *(word + i);

			data->algorithm[i - 3] = '\0';
		}
		// Quantum
		else if (strstr(word, "quantum") != NULL)
		{

			num = malloc(sizeof(char) * ((wordLen) - 7));

			for (i = 7; i < wordLen; i++)
				*(num + (i - 7)) = *(word + i);

			*(num + (i - 7)) = '\0';
			data->quantum = strToInt(num);
			free(num);
		}
		else if (strstr(word, "processname") != NULL)
		{
			arrival = strstr(word, "arrival");
			burst = strstr(word, "burst");
			int j = data->initializedPCBs;

			// Find Length of Name & save name
			nameLen = arrival - word - 11;
			data->pcbArray[j]->name = malloc(sizeof(char) * (nameLen + 1));

			for (i = 11; i < arrival - word; i++)
				data->pcbArray[data->initializedPCBs]->name[+ i - 11] = *(word + i);

			data->pcbArray[data->initializedPCBs]->name[+ i - 11] = '\0';

			// Find Arrival Time
			arrivalLen = burst - arrival - 7;
			num = malloc(sizeof(char) * (arrivalLen + 1));

			for (i = 0; i < arrivalLen; i++)
				*(num + i) = *(burst - arrivalLen + i);

			*(num + i) = '\0';
			data->pcbArray[data->initializedPCBs]->arrivalTime = strToInt(num);
			free(num);

			// Find Burst Time
			burstLen = 0;
			for(i = 5;; i++)
			{
				if (*(burst + i) == '\0' || *(burst + i) == '\n')
					break;

				burstLen++;
			}

			num = malloc(sizeof(char) * (burstLen + 1));

			for (i = 5; i < burstLen + 5; i++)
				*(num + i - 5) = *(burst + i);

			*(num + i - 5) = '\0';
			data->pcbArray[data->initializedPCBs]->burst = strToInt(num);
			data->pcbArray[data->initializedPCBs]->burstRemaining= strToInt(num);
			data->initializedPCBs++;
			free(num);
		}
		else if (strstr(word, "end") != NULL)
			break;


		free(word);
    }

    if (word != NULL)
        free(word);
    free(line);
    fclose(fp);
	return data;
}

void destroyData(Data* data)
{
    int i;
    for (i = 0; i < data->processcount; i++)
    {
        free(data->pcbArray[i]->name);
        free(data->pcbArray[i]);
    }
    free(data->pcbArray);
    free(data->algorithm);
    free(data);
}

int strToInt(char* str)
{
	int i;
	int len = strlen(str);
	int num = 0;

	for (i = 0; i < len; i++)
		num += (*(str + i) - '0') * pow(10, len - i - 1);

	return num;
}


