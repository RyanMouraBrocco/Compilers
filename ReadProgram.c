#include <stdio.h>
#include <stdlib.h>

int countLines(FILE *file);
void openFile(FILE **file, char *fileName);

int main()
{
    char fileName[] = "ExampleFile.c";
    FILE *fp;
    openFile(&fp, fileName);
    int linesCount = countLines(fp);
    fclose(fp);

    printf("Total of lines is %d", linesCount);

    return 0;
}

void openFile(FILE **file, char *fileName)
{
    *file = fopen(fileName, "r");

    if (*file == NULL)
    {
        exit(1);
    }
}

int countLines(FILE *file)
{
    int quantity = 1;
    char character;
    while ((character = fgetc(file)) != EOF)
    {
        if (character == '\n')
            quantity++;
    }

    return quantity;
}