#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "AnalyzerTypes.h"
#include "SimpleLexAnalyzer.h"
#include "ReaderFile.h"

int line = 1;
int isMultilineComment = 1;

void recognizeId(TInformationAtom *, char **);
void recognizeNum(TInformationAtom *, char **);
int getSimpleAttribute(TInformationAtom *, char **);
int getArithmeticOperator(TInformationAtom *, char **);
int compareInsensitiveString(char *, char *, char *);
int getRelationalOpertor(TInformationAtom *, char **);
void recognizeCharacter(TInformationAtom *, char **);
double getDoubleValueFromString(char *, int);

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

int main(void)
{
    char *buffer;
    char *bufferToFree = buffer;
    buffer = readFile("input.pas");
    printf("%s\n\n", buffer);
    TInformationAtom atom;

    while (atom.atom != EOS)
    {
        atom = getAtom(&buffer);
        if (atom.atom == IDENTIFIER)
            printf("linha %d: IDENTIFICADOR : %s\n", atom.line, atom.idAttribute);
        if (atom.atom == INTEGER_NUMBER)
            printf("linha %d: NUMERO_INTEIRO %d\n", atom.line, atom.integerAttribute);
        if (atom.atom == ASSIGNMENT)
            printf("linha %d: ATRIBUIÇÃO\n", atom.line);
        if (atom.atom == WHILE)
            printf("linha %d: WILHE : %s\n", atom.line, atom.idAttribute);
        if (atom.atom == AND)
            printf("linha %d: AND: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == BEGIN)
            printf("linha %d: BEGIN: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == BOOLEAN)
            printf("linha %d: BOOLEAN: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == CHAR)
            printf("linha %d: CHAR: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == DO)
            printf("linha %d: DO: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == ELSE)
            printf("linha %d: ELSE: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == END)
            printf("linha %d: END: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == FALSE)
            printf("linha %d: FALSE: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == IF)
            printf("linha %d: IF: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == INTEGER)
            printf("linha %d: INTEGER: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == MOD)
            printf("linha %d: MOD: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == NOT)
            printf("linha %d: NOT: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == OR)
            printf("linha %d: OR: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == PROGRAM)
            printf("linha %d: PROGRAM: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == READ)
            printf("linha %d: READ: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == REAL)
            printf("linha %d: REAL: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == THEN)
            printf("linha %d: THEN: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == TRUE)
            printf("linha %d: TRUE: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == WRITE)
            printf("linha %d: WRITE: %s\n", atom.line, atom.idAttribute);
        if (atom.atom == OPEN_PARENTHESES)
            printf("linha %d: ABRE_PAR\n", atom.line);
        if (atom.atom == CLOSE_PARENTHESES)
            printf("linha %d: FECHA_PAR\n", atom.line);
        if (atom.atom == DOT)
            printf("linha %d: PONTO\n", atom.line);
        if (atom.atom == SEMICOLON)
            printf("linha %d: PONTO_VIRGULA\n", atom.line);
        if (atom.atom == COMMA)
            printf("linha %d: VIRGULA\n", atom.line);
        if (atom.atom == SUBTRACTION)
            printf("linha %d: SUBTRACAO\n", atom.line);
        if (atom.atom == ADDITION)
            printf("linha %d: ADICAO\n", atom.line);
        if (atom.atom == DIVISION)
            printf("linha %d: DIVISAO\n", atom.line);
        if (atom.atom == MULTIPLICATION)
            printf("linha %d: MULTIPLICACAO\n", atom.line);
        if (atom.atom == REAL_NUMBER)
            printf("linha %d: NUMERO_REAL: %f\n", atom.line, atom.doubleAttribute);
        if (atom.atom == CHARACTER)
            printf("linha %d: CARACTERE: %c\n", atom.line, atom.charAttribute);
        if (atom.atom == RELATIONAL_OPERATOR)
        {
            switch (atom.relationalOperator)
            {
            case LT:
                printf("linha %d: MENOR\n", atom.line);
                break;
            case LE:
                printf("linha %d: MENOR_IGUAL\n", atom.line);
                break;
            case EQ:
                printf("linha %d: IGUAL\n", atom.line);
                break;
            case NE:
                printf("linha %d: DIFERENTE\n", atom.line);
                break;
            case GT:
                printf("linha %d: MAIOR\n", atom.line);
                break;
            case GE:
                printf("linha %d: MAIOR_IGUAL\n", atom.line);
                break;
            }
        }
        if (atom.atom == COMMENT)
            printf("linha %d: COMENTÁRIO\n", atom.line);
        if (atom.atom == ERROR)
        {
            printf("linha %d: ERRO\n", atom.line);
            break;
        }
    }

    free(bufferToFree);

    return 0;
}

TInformationAtom getAtom(char **buffer)
{
    TInformationAtom atom;
    atom.atom = ERROR;

    while (**buffer == ' ' || **buffer == '\n')
    {
        if (**buffer == '\n')
            line++;
        (*buffer)++;
    }

    atom.line = line;
    if (**buffer == '\x0')
    {
        atom.atom = EOS;
        atom.line = line;
    }
    else if (**buffer == '#')
    {
        atom.atom = COMMENT;
        (*buffer)++;
        while (**buffer != '\n')
        {
            (*buffer)++;
        }
    }
    else if (**buffer == '{')
    {
        atom.atom = COMMENT;
        (*buffer)++;
        while (**buffer != '}' && **buffer != '\x0')
        {
            if (**buffer == '\n')
                line++;

            (*buffer)++;
        }
        if (**buffer == '\x0')
            atom.atom = ERROR;
        else
            (*buffer)++;
    }
    else if (**buffer == '\'')
    {
        recognizeCharacter(&atom, buffer);
    }
    else if (isalpha(**buffer))
    {
        recognizeId(&atom, buffer);
    }
    else if (isdigit(**buffer))
    {
        recognizeNum(&atom, buffer);
    }
    else if (getSimpleAttribute(&atom, buffer) == 1)
    {
        if (getArithmeticOperator(&atom, buffer) == 1)
        {
            getRelationalOpertor(&atom, buffer);
        }
    }

    return atom;
}

void recognizeId(TInformationAtom *atom, char **buffer)
{
    char *initId = *buffer;
    int length = 0;
r0:
    if (isalpha(**buffer))
    {
        (*buffer)++;
        goto r1;
    }
r1:
    if (isalpha(**buffer) || isdigit(**buffer) || **buffer == '_')
    {
        (*buffer)++;
        goto r1;
    }
    if (**buffer != '\x0')
    {
        goto r2;
    }
r2:
    length = *buffer - initId;
    if (length <= 16)
    {
        strncpy(atom->idAttribute, initId, length);
        atom->idAttribute[length] = '\x0';
        if (compareInsensitiveString(atom->idAttribute, "WHILE", "while") == 0)
            atom->atom = WHILE;
        else if (compareInsensitiveString(atom->idAttribute, "AND", "and") == 0)
            atom->atom = AND;
        else if (compareInsensitiveString(atom->idAttribute, "BEGIN", "begin") == 0)
            atom->atom = BEGIN;
        else if (compareInsensitiveString(atom->idAttribute, "BOOLEAN", "boolean") == 0)
            atom->atom = BOOLEAN;
        else if (compareInsensitiveString(atom->idAttribute, "CHAR", "char") == 0)
            atom->atom = CHAR;
        else if (compareInsensitiveString(atom->idAttribute, "DO", "do") == 0)
            atom->atom = DO;
        else if (compareInsensitiveString(atom->idAttribute, "ELSE", "else") == 0)
            atom->atom = ELSE;
        else if (compareInsensitiveString(atom->idAttribute, "END", "end") == 0)
            atom->atom = END;
        else if (compareInsensitiveString(atom->idAttribute, "FALSE", "false") == 0)
            atom->atom = FALSE;
        else if (compareInsensitiveString(atom->idAttribute, "IF", "if") == 0)
            atom->atom = IF;
        else if (compareInsensitiveString(atom->idAttribute, "INTEGER", "integer") == 0)
            atom->atom = INTEGER;
        else if (compareInsensitiveString(atom->idAttribute, "MOD", "mod") == 0)
            atom->atom = MOD;
        else if (compareInsensitiveString(atom->idAttribute, "NOT", "not") == 0)
            atom->atom = NOT;
        else if (compareInsensitiveString(atom->idAttribute, "OR", "or") == 0)
            atom->atom = OR;
        else if (compareInsensitiveString(atom->idAttribute, "PROGRAM", "program") == 0)
            atom->atom = PROGRAM;
        else if (compareInsensitiveString(atom->idAttribute, "READ", "read") == 0)
            atom->atom = READ;
        else if (compareInsensitiveString(atom->idAttribute, "REAL", "real") == 0)
            atom->atom = REAL;
        else if (compareInsensitiveString(atom->idAttribute, "THEN", "then") == 0)
            atom->atom = THEN;
        else if (compareInsensitiveString(atom->idAttribute, "TRUE", "true") == 0)
            atom->atom = TRUE;
        else if (compareInsensitiveString(atom->idAttribute, "WRITE", "write") == 0)
            atom->atom = WRITE;
        else
            atom->atom = IDENTIFIER;
    }
    else
    {
        atom->atom = ERROR;
    }
}

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

void recognizeNum(TInformationAtom *atom, char **buffer)
{
    char *initNum = *buffer;
    int length = 0;
    char stringNum[20];
r0:
    if (isdigit(**buffer))
    {
        (*buffer)++;
        goto r1;
    }
r1:
    if (isdigit(**buffer))
    {
        (*buffer)++;
        goto r1;
    }

    if (isalpha(**buffer))
    {
        goto r3;
    }

    if (**buffer != '\x0')
    {
        goto r2;
    }
r2:
    if (**buffer == '.' && (*(*buffer + 1) == 'e' || *(*buffer + 1) == 'E'))
    {
        (*buffer)++;
        (*buffer)++;
        if (**buffer == '+' || **buffer == '-')
            (*buffer)++;

        if (isdigit(**buffer))
            goto r1;
        else
            goto r3;
    }
    else
    {
        length = *buffer - initNum;
        strncpy(stringNum, initNum, length);
        char eValue[] = "e";
        char bigEValue[] = "E";
        if (strstr(stringNum, eValue) != NULL || strstr(stringNum, bigEValue) != NULL)
        {
            atom->atom = REAL_NUMBER;
            atom->doubleAttribute = getDoubleValueFromString(stringNum, length);
        }
        else
        {
            atom->atom = INTEGER_NUMBER;
            atom->integerAttribute = atoi(stringNum);
        }
        return;
    }
r3:
    atom->atom = ERROR;
    return;
}

int getSimpleAttribute(TInformationAtom *atom, char **buffer)
{
    if (**buffer == ':' && *(*buffer + 1) == '=')
    {
        (*buffer)++;
        (*buffer)++;

        atom->atom = ASSIGNMENT;
        return 0;
    }
    else if (**buffer == '(')
    {
        (*buffer)++;
        atom->atom = OPEN_PARENTHESES;
        return 0;
    }
    else if (**buffer == ')')
    {
        (*buffer)++;
        atom->atom = CLOSE_PARENTHESES;
        return 0;
    }
    else if (**buffer == '.')
    {
        (*buffer)++;
        atom->atom = DOT;
        return 0;
    }
    else if (**buffer == ';')
    {
        (*buffer)++;
        atom->atom = SEMICOLON;
        return 0;
    }
    else if (**buffer == ',')
    {
        (*buffer)++;
        atom->atom = COMMA;
        return 0;
    }

    return 1;
}

int getArithmeticOperator(TInformationAtom *atom, char **buffer)
{
    if (**buffer == '-')
    {
        (*buffer)++;
        atom->atom = SUBTRACTION;
        return 0;
    }
    else if (**buffer == '+')
    {
        (*buffer)++;
        atom->atom = ADDITION;
        return 0;
    }
    else if (**buffer == '/')
    {
        (*buffer)++;
        atom->atom = DIVISION;
        return 0;
    }
    else if (**buffer == '*')
    {
        (*buffer)++;
        atom->atom = MULTIPLICATION;
        return 0;
    }

    return 1;
}

int getRelationalOpertor(TInformationAtom *atom, char **buffer)
{
    if (**buffer == '<' && *(*buffer + 1) == '=')
    {
        (*buffer)++;
        (*buffer)++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = LE;
        return 0;
    }
    else if (**buffer == '<')
    {
        (*buffer)++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = LT;
        return 0;
    }
    else if (**buffer == '=')
    {
        (*buffer)++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = EQ;
        return 0;
    }
    else if (**buffer == '!' && *(*buffer + 1) == '=')
    {
        (*buffer)++;
        (*buffer)++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = NE;
        return 0;
    }
    else if (**buffer == '>' && *(*buffer + 1) == '=')
    {
        (*buffer)++;
        (*buffer)++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = GE;
        return 0;
    }
    else if (**buffer == '>')
    {
        (*buffer)++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = GT;
        return 0;
    }

    return 1;
}

void recognizeCharacter(TInformationAtom *atom, char **buffer)
{
    if (**buffer == '\'' && isascii(*(*buffer + 1)) && *(*buffer + 2) == '\'')
    {
        (*buffer)++;
        char value = **buffer;
        (*buffer)++;
        (*buffer)++;
        atom->atom = CHARACTER;
        atom->charAttribute = value;
    }
    else
        atom->atom = ERROR;
}

double getDoubleValueFromString(char *stringNumber, int length)
{
    char beforeE[20];
    int beforeELength;
    char *afterDotValue;
    char afterE[20];
    int afterELength;
    char finalNumber[20];
    for (int i = 0; i < length; i++)
    {
        if (stringNumber[i] == 'e' || stringNumber[i] == 'E')
        {
            beforeELength = i;
            afterELength = length - (i + 1);
            if (stringNumber[i + 1] == '+' || stringNumber[i + 1] == '-')
                afterDotValue = &(stringNumber[i + 2]);
            else
                afterDotValue = &(stringNumber[i + 1]);
            break;
        }
    }
    strncpy(beforeE, stringNumber, beforeELength);
    strncpy(afterE, afterDotValue, afterELength);
    strcat(beforeE, afterE);
    strncpy(finalNumber, beforeE, length - 1);
    return atof(finalNumber);
}
