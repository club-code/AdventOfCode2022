#include "main.h"

dynArray parseInput(char *filepath) {
    dynArray res = initDynArray(50, sizeof(int));
    size_t index = 0;

    FILE *filePointer = fopen(filepath, "r");

    while (!feof(filePointer)) {
        index += 1;
        resizeDynArray(res, index);
        int *data = res.data;
        char line[10];
        fscanf(filePointer, "%s", line);
        printf("%s\n", line);
    }
    
    fclose(filePointer);
    return res;
}

void easy(char *filepath) {
    dynArray arr = parseInput(filepath);
    printf("%d\n", getMax(arr));
}

void hard(char* filepath) {}

int getMax(dynArray arr) {
    int m = 0;
    int* data = arr.data;
    for (size_t i = 0; i < arr.length; i++)
    {
        if (data[i] > m)
        {
            m = data[i];
        }
        
    }
    return m;
}