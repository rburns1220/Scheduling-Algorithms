#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "data.h"
#include "queue.h"
#include "sjf.h"
#include "rr.h"

int main()
{
    FILE* out;
    Data* data;

    out = fopen("process.out", "w");
    data = parseFile("process.in");

    if (strcmp(data->algorithm, "sjf") == 0)
        shortestJobFirst(data, out);
    else if (strcmp(data->algorithm, "rr") == 0)
        rr(data, out);
    // Add other algorithms here *****

    destroyData(data);
    fclose(out);
    return 0;
}
