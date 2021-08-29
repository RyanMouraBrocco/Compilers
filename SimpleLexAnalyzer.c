#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum
{
    ERROR,
    IDENTIFIER,
    INTEGER_NUMBER,
    ASSIGNMENT,
    WHILE,
    EOS
} TAtom;

char *buffer;
int line = 1;

char *readFile(char *);
int recognizeId();
int recognizeNum();
int getAtom();
int recognizeAssigment();
int isWhile(char *);
char *appendString(char *baseString, char value, int length);

int main(void)
{
    buffer = readFile("input.pas");
    printf("%s\n\n", buffer);
    int atomo = ERROR;

    while (atomo != EOS)
    {
        if (*buffer == ' ')
        {
            buffer++;
        }
        else if (*buffer == '\n')
        {
            buffer++;
            line++;
        }
        else
        {
            atomo = getAtom();
            if (atomo == IDENTIFIER)
                printf("linha %d: IDENTIFICADOR\n", line);
            if (atomo == INTEGER_NUMBER)
                printf("linha %d: NUMERO_INTEIRO\n", line);
            if (atomo == ASSIGNMENT)
                printf("linha %d: ATRIBUIÇÃO\n", line);
            if (atomo == WHILE)
                printf("linha %d: WILHE\n", line);
            if (atomo == ERROR)
            {
                printf("linha %d: ERRO\n", line);
                break;
            }
        }
    }

    // free(buffer);

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

int getAtom()
{
    int atomo = ERROR;

    if (*buffer == ':')
    {
        atomo = recognizeAssigment();
    }
    else if (isalpha(*buffer))
    {
        atomo = recognizeId();
    }
    else if (isdigit(*buffer))
    {
        atomo = recognizeNum();
    }
    else if (*buffer == NULL)
    {
        atomo = EOS;
    }

    return atomo;
}

int recognizeId()
{
    char *word = NULL;
    int length = 0;
r0:
    if (isalpha(*buffer))
    {
        word = appendString(word, *buffer, length++);
        buffer++;
        goto r1;
    }
r1:
    if (isalpha(*buffer) || isdigit(*buffer))
    {
        word = appendString(word, *buffer, length++);
        buffer++;
        goto r1;
    }
    if (*buffer != '\x0')
    {
        goto r2;
    }
r2:
    if (isWhile(word))
    {
        return WHILE;
    }

    return IDENTIFIER;
}

int recognizeNum()
{
r0:
    if (isdigit(*buffer))
    {
        buffer++;
        goto r1;
    }
r1:
    if (isdigit(*buffer))
    {
        buffer++;
        goto r1;
    }

    if (isalpha(*buffer))
    {
        goto r3;
    }

    if (*buffer != '\x0')
    {
        goto r2;
    }
r2:
    return INTEGER_NUMBER;
r3:
    return ERROR;
}

int recognizeAssigment()
{
r0:
    if (*buffer == ':')
    {
        buffer++;
        goto r1;
    }
r1:
    if (*buffer == '=')
    {
        buffer++;
        return ASSIGNMENT;
    }

    return ERROR;
}

int isWhile(char *localBuffer)
{
    char whileUpperName[] = "WHILE";
    char whileLowerName[] = "while";
    int index = 0;
    while (isalpha(*localBuffer) || isdigit(*localBuffer))
    {
        if (index > 4)
        {
            return 0;
        }

        if (*localBuffer == whileUpperName[index] || *localBuffer == whileLowerName[index])
        {
            localBuffer++;
            index++;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}

char *appendString(char *baseString, char value, int length)
{
    if (baseString == NULL)
    {
        char *newString = malloc(1);
        newString[0] = value;
        return newString;
    }
    else
    {
        char *newString = malloc((length + 2) * sizeof(char));
        for (int i = 0; i < length; i++)
        {
            newString[i] = baseString[i];
        }

        newString[length] = value;
        newString[length + 1] = '\0';
        return newString;
    }
}