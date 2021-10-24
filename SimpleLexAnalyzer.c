#include <stdio.h>
#include "SimpleLexAnalyzer.h"
#include "Utils.h"

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