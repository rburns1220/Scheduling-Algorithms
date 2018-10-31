// Armand Alvarez
// Ryan Burns
// Sean Simonian
// COP 4600 Spring 2018 Programming Assignment 1
//this is a program to do fcfs,round robin and shortest job first scheduling 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "data.h"
#include "queue.h"
#include "sjf.h"
#include "rr.h"
#include "fcfs.h"

int main()
{
	FILE* out;
	Data* data;

	out = fopen("processes.out", "w");
	data = parseFile("processes.in");

	if (strcmp(data->algorithm, "sjf") == 0)
	{
		shortestJobFirst(data, out);//calling sjf function 
	}
	else if (strcmp(data->algorithm, "rr") == 0)
	{
		rr(data, out);//calling shortest job first function 
	}
	else if (strcmp(data->algorithm, "fcfs") == 0)
	{
		firstComeFirstServed(data, out);//calling fcfs function 
	}

	destroyData(data);
	fclose(out);
	return 0;
}
