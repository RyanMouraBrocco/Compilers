#ifndef Utils
#define Utils

#include <stdio.h>
#include <string.h>
#include "AnalyzerTypes.h"

int compareInsensitiveString(char *, char *, char *);
char *readFile(char *);
char *getAtomName(TAtom);

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

char *getAtomName(TAtom atom)
{
    if (atom == IDENTIFIER)
        return "IDENTIFICADOR";
    if (atom == INTEGER_NUMBER)
        return "NUMERO_INTEIRO";
    if (atom == ASSIGNMENT)
        return "ATRIBUIÇÃO";
    if (atom == WHILE)
        return "WILHE";
    if (atom == AND)
        return "AND";
    if (atom == BEGIN)
        return "BEGIN";
    if (atom == BOOLEAN)
        return "BOOLEAN";
    if (atom == CHAR)
        return "CHAR";
    if (atom == DO)
        return "DO";
    if (atom == ELSE)
        return "ELSE";
    if (atom == END)
        return "END";
    if (atom == FALSE)
        return "FALSE";
    if (atom == IF)
        return "IF";
    if (atom == INTEGER)
        return "INTEGER";
    if (atom == MOD)
        return "MOD";
    if (atom == NOT)
        return "NOT";
    if (atom == OR)
        return "OR";
    if (atom == PROGRAM)
        return "PROGRAM";
    if (atom == READ)
        return "READ";
    if (atom == REAL)
        return "REAL";
    if (atom == THEN)
        return "THEN";
    if (atom == TRUE)
        return "TRUE";
    if (atom == WRITE)
        return "WRITE";
    if (atom == OPEN_PARENTHESES)
        return "(";
    if (atom == CLOSE_PARENTHESES)
        return ")";
    if (atom == DOT)
        return ".";
    if (atom == SEMICOLON)
        return ";";
    if (atom == COMMA)
        return ",";
    if (atom == SUBTRACTION)
        return "-";
    if (atom == ADDITION)
        return "+";
    if (atom == DIVISION)
        return "/";
    if (atom == MULTIPLICATION)
        return "*";
    if (atom == REAL_NUMBER)
        return "NUMERO_REAL";
    if (atom == CHARACTER)
        return "CARACTERE";
    if (atom == RELATIONAL_OPERATOR)
        return "OPERADOR_RELACIONAL";
}

#endif