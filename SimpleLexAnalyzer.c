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
    EOS,
    AND,
    BEGIN,
    BOOLEAN,
    CHAR,
    DO,
    ELSE,
    END,
    FALSE,
    IF,
    INTEGER,
    MOD,
    NOT,
    OR,
    PROGRAM,
    READ,
    REAL,
    THEN,
    TRUE,
    WRITE,
    OPEN_PARENTHESES,
    CLOSE_PARENTHESES,
    DOT,
    SEMICOLON,
    COMMA,
    SUBTRACTION,
    ADDITION,
    DIVISION,
    MULTIPLICATION,
    RELATIONAL_OPERATOR,
    COMMENT,
    REAL_NUMBER,
    CHARACTER
} TAtom;

typedef enum
{
    LT,
    LE,
    EQ,
    NE,
    GT,
    GE,
} TRelationalOperator;

typedef struct
{
    TAtom atom;
    int line;
    int integerAttribute;
    char idAttribute[15];
    double doubleAttribute;
    char charAttribute;
    TRelationalOperator relationalOperator;
} TInformationAtom;

char *buffer;
int line = 1;
int isMultilineComment = 1;

char *readFile(char *);
void recognizeId(TInformationAtom *);
void recognizeNum(TInformationAtom *);
TInformationAtom getAtom();
int getSimpleAttribute(TInformationAtom *);
int getArithmeticOperator(TInformationAtom *);
int compareInsensitiveString(char *, char *, char *);
int getRelationalOpertor(TInformationAtom *);
void recognizeCharacter(TInformationAtom *);

int main(void)
{
    char *bufferToFree = buffer;
    buffer = readFile("input.pas");
    printf("%s\n\n", buffer);
    TInformationAtom atom;

    while (atom.atom != EOS)
    {
        atom = getAtom();
        if (atom.atom == IDENTIFIER)
            printf("linha %d: IDENTIFICADOR : %s\n", atom.line, atom.idAttribute);
        if (atom.atom == INTEGER_NUMBER)
            printf("linha %d: NUMERO_INTEIRO %d\n", atom.line, atom.integerAttribute);
        if (atom.atom == ASSIGNMENT)
            printf("linha %d: ATRIBUIÇÃO\n", atom.line);
        if (atom.atom == WHILE)
            printf("linha %d: WILHE : %s\n", atom.line, atom.idAttribute);
        if (atom.atom == COMMENT)
            printf("linha %d: Comentário\n", atom.line);
        if (atom.atom == ERROR)
        {
            printf("linha %d: ERRO\n", atom.line);
            break;
        }
    }

    free(bufferToFree);

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

TInformationAtom getAtom()
{
    TInformationAtom atom;
    atom.atom = ERROR;

    if (*buffer == ' ')
    {
        buffer++;
    }
    else if (*buffer == '\n')
    {
        buffer++;
        line++;
    }

    atom.line = line;
    if (*buffer == '\x0')
    {
        atom.atom = EOS;
        atom.line = line;
    }
    else if (*buffer == '#')
    {
        atom.atom = COMMENT;
        buffer++;
        while (*buffer != '\n')
        {
            buffer++;
        }
    }
    else if (*buffer == '{')
    {
        atom.atom = COMMENT;
        buffer++;
        while (*buffer != '}' && *buffer != '\x0')
        {
            if (*buffer == '\n')
                line++;

            buffer++;
        }
        if (*buffer == '\x0')
            atom.atom = ERROR;
        else
            buffer++;
    }
    else if (*buffer == '\'')
    {
        recognizeCharacter(&atom);
    }
    else if (isalpha(*buffer))
    {
        recognizeId(&atom);
    }
    else if (isdigit(*buffer))
    {
        recognizeNum(&atom);
    }
    else if (getSimpleAttribute(&atom) == 1)
    {
        if (getArithmeticOperator(&atom) == 1)
        {
            getRelationalOpertor(&atom);
        }
    }

    return atom;
}

void recognizeId(TInformationAtom *atom)
{
    char *initId = buffer;
    int length = 0;
r0:
    if (isalpha(*buffer))
    {
        buffer++;
        goto r1;
    }
r1:
    if (isalpha(*buffer) || isdigit(*buffer) || *buffer == '_')
    {
        buffer++;
        goto r1;
    }
    if (*buffer != '\x0')
    {
        goto r2;
    }
r2:
    length = buffer - initId;
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

void recognizeNum(TInformationAtom *atom)
{
    char *initNum = buffer;
    int length = 0;
    char stringNum[20];
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
    if (*buffer == '.' && *buffer == 'e')
    {
        buffer++;
        buffer++;
        if (*buffer == '+' || *buffer == '-')
            buffer++;

        goto r1;
    }
    else
    {
        length = buffer - initNum;
        strncpy(stringNum, initNum, length);
        if (strstr(stringNum, 'e') != NULL)
        {
            atom->atom = REAL_NUMBER;
            atom->doubleAttribute = atof(stringNum);
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

int getSimpleAttribute(TInformationAtom *atom)
{
    if (*buffer == ':' && *(buffer + 1) == '=')
    {
        buffer++;
        buffer++;

        atom->atom = ASSIGNMENT;
        return 0;
    }
    else if (*buffer == '(')
    {
        buffer++;
        atom->atom = OPEN_PARENTHESES;
        return 0;
    }
    else if (*buffer == ')')
    {
        buffer++;
        atom->atom = CLOSE_PARENTHESES;
        return 0;
    }
    else if (*buffer == '.')
    {
        buffer++;
        atom->atom = DOT;
        return 0;
    }
    else if (*buffer == ';')
    {
        buffer++;
        atom->atom = SEMICOLON;
        return 0;
    }
    else if (*buffer == ',')
    {
        buffer++;
        atom->atom = COMMA;
        return 0;
    }

    return 1;
}

int getArithmeticOperator(TInformationAtom *atom)
{
    if (*buffer == '-')
    {
        buffer++;
        atom->atom = SUBTRACTION;
        return 0;
    }
    else if (*buffer == '+')
    {
        buffer++;
        atom->atom = ADDITION;
        return 0;
    }
    else if (*buffer == '/')
    {
        buffer++;
        atom->atom = DIVISION;
        return 0;
    }
    else if (*buffer == '*')
    {
        buffer++;
        atom->atom = MULTIPLICATION;
        return 0;
    }

    return 1;
}

int getRelationalOpertor(TInformationAtom *atom)
{
    if (*buffer == '<')
    {
        buffer++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = LT;
        return 0;
    }
    else if (*buffer == '<' && *(buffer + 1) == '=')
    {
        buffer++;
        buffer++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = LE;
        return 0;
    }
    else if (*buffer == '=')
    {
        buffer++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = EQ;
        return 0;
    }
    else if (*buffer == '!' && *(buffer + 1) == '=')
    {
        buffer++;
        buffer++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = NE;
        return 0;
    }
    else if (*buffer == '>')
    {
        buffer++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = GT;
        return 0;
    }
    else if (*buffer == '>' && *(buffer + 1) == '=')
    {
        buffer++;
        buffer++;
        atom->atom = RELATIONAL_OPERATOR;
        atom->relationalOperator = GE;
        return 0;
    }

    return 1;
}

void recognizeCharacter(TInformationAtom *atom)
{
    if (*buffer == '\'' && isascii(*(buffer + 1)) && *(buffer + 2) == '\'')
    {
        buffer++;
        char value = *buffer;
        buffer++;
        buffer++;
        atom->atom = CHARACTER;
        atom->charAttribute = value;
    }
    else
        atom->atom = ERROR;
}