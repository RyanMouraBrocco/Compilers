#ifndef Utils
#define Utils

#include <stdio.h>
#include <string.h>

int compareInsensitiveString(char *, char *, char *);
char *readFile(char *);

int compareInsensitiveString(char *valueToCompare, char *upperCaseValue, char *lowerCaseValue)
{
    int toCompareLen = strlen(valueToCompare);
    int len = strlen(upperCaseValue);
    if (len != toCompareLen)
        return 1;

    for (int i = 0; i < len; i++)
    {
        if (valueToCompare[i] != upperCaseValue[i] && valueToCompare[i] != lowerCaseValue[i])
            return 1;
    }

    return 0;
}

char *readFile(char *fileName)
{
    FILE *file;
    char *readBuffer;
    long inputSize;
    file = fopen(fileName, "r");
    if (!file)
    {
        printf("erro na abertura do arquivo de entrada !");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    inputSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    readBuffer = (char *)calloc(inputSize, sizeof(char));

    fread(readBuffer, sizeof(char), inputSize, file);

    fclose(file);
    return readBuffer;
}

#endif