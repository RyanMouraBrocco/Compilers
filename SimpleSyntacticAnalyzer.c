#include <stdio.h>
#include <stdlib.h>
#include "AnalyzerTypes.h"
#include "SimpleLexAnalyzer.h"
#include "Utils.h"

char *buffer;
char *iniBuffer;
TInformationAtom lookahead;

void consume(TAtom atom);
TInformationAtom getNextAtom(char **buffer);
void syntacticAnalyze();
void consumeBlock();
void consumeVariableDeclaration();
void consumeVariableType();
void consumeVariableName();
void consumeCompoundCommand();
void consumeSimpleCommand();
void consumeAssigmentCommand();
void consumeConditionalCommand();
void consumeLoopCommand();
void consumeReadCommand();
void consumeWriteCommand();
void consumeExpression();
void consumeSimpleExpression();
void consumeSimpleOperator();
void consumeTerm();
void consumeFactor();
void consumeOperatorTerm();

int main(void)
{
    buffer = readFile("input.pas");
    iniBuffer = buffer;
    lookahead = getNextAtom(&buffer);

    syntacticAnalyze();
    if (lookahead.atom == EOS)
    {
        printf("palavra aceita");
    }
    else
    {
        printf("\nErro sintatico 2. Nao cheguei ao final da palavra");
    }

    printf("\nfim de analise sintatica.");

    free(iniBuffer);

    return 0;
}

TInformationAtom getNextAtom(char **buffer)
{
    TInformationAtom next = getAtom(buffer);
    while (next.atom == COMMENT)
    {
        next = getAtom(buffer);
    }

    return next;
}

void consume(TAtom atom)
{
    if (lookahead.atom == atom)
    {
        lookahead = getNextAtom(&buffer);
    }
    else
    {
        printf("erro sintatico: esperado [%s] encontrado [%s] indice [%ld]\n", "texto A", "textoB", (buffer - iniBuffer) - 1);
        exit(1);
    }
}

void syntacticAnalyze()
{
    consume(PROGRAM);
    consume(IDENTIFIER);
    consume(SEMICOLON);
    consumeBlock();
    consume(SEMICOLON);
}

void consumeBlock()
{
    if (lookahead.atom != BEGIN)
    {
        consumeVariableDeclaration();
    }

    consumeCompoundCommand();
}

void consumeVariableDeclaration()
{
    consumeVariableType();
    consumeVariableName();
    consume(SEMICOLON);

    if (lookahead.atom != BEGIN)
    {
        consumeVariableDeclaration();
    }
}

void consumeVariableType()
{
    if (lookahead.atom == INTEGER)
    {
        consume(INTEGER);
    }
    else if (lookahead.atom == REAL)
    {
        consume(REAL);
    }
    else if (lookahead.atom == CHAR)
    {
        consume(CHAR);
    }
    else
    {
        consume(BOOLEAN);
    }
}

void consumeVariableName()
{
    consume(IDENTIFIER);
    if (lookahead.atom == COMMA)
    {
        consume(COMMA);
        consumeVariableName();
    }
}

void consumeCompoundCommand()
{
    consume(BEGIN);
    consumeSimpleCommand();
    while (lookahead.atom != END)
    {
        consume(SEMICOLON);
        consumeSimpleCommand();
    }
    consume(END);
}

void consumeSimpleCommand()
{
    if (lookahead.atom == IDENTIFIER)
    {
        consumeAssigmentCommand();
    }
    else if (lookahead.atom == IF)
    {
        consumeConditionalCommand();
    }
    else if (lookahead.atom == WHILE)
    {
        consumeLoopCommand();
    }
    else if (lookahead.atom == READ)
    {
        consumeReadCommand();
    }
    else if (lookahead.atom == WRITE)
    {
        consumeWriteCommand();
    }
    else
    {
        consumeCompoundCommand();
    }
}

void consumeAssigmentCommand()
{
    consume(IDENTIFIER);
    consume(ASSIGNMENT);
    consumeExpression();
}

void consumeConditionalCommand()
{
    consume(IF);
    consume(OPEN_PARENTHESES);
    consumeExpression();
    consume(CLOSE_PARENTHESES);
    consume(THEN);
    consumeSimpleCommand();
    if (lookahead.atom == ELSE)
    {
        consumeSimpleCommand();
    }
}

void consumeLoopCommand()
{
    consume(WHILE);
    consume(OPEN_PARENTHESES);
    consumeExpression();
    consume(CLOSE_PARENTHESES);
    consume(DO);
    consumeSimpleCommand();
}

void consumeReadCommand()
{
    consume(READ);
    consume(OPEN_PARENTHESES);
    consumeVariableName();
    consume(CLOSE_PARENTHESES);
}

void consumeWriteCommand()
{
    consume(WRITE);
    consume(OPEN_PARENTHESES);
    consumeExpression();
    while (lookahead.atom == COMMA)
    {
        consume(COMMA);
        consumeExpression();
    }

    consume(CLOSE_PARENTHESES);
}

void consumeExpression()
{
    consumeSimpleExpression();
    if (lookahead.atom == RELATIONAL_OPERATOR)
    {
        consume(RELATIONAL_OPERATOR);
        consumeSimpleExpression();
    }
}

void consumeSimpleExpression()
{
    if (lookahead.atom == ADDITION)
    {
        consume(ADDITION);
    }
    else if (lookahead.atom == SUBTRACTION)
    {
        consume(SUBTRACTION);
    }

    consumeTerm();

    while (lookahead.atom == ADDITION || lookahead.atom == SUBTRACTION || lookahead.atom == OR)
    {
        consumeSimpleOperator();
        consumeTerm();
    }
}

void consumeSimpleOperator()
{
    if (lookahead.atom == ADDITION)
    {
        consume(ADDITION);
    }
    else if (lookahead.atom == SUBTRACTION)
    {
        consume(SUBTRACTION);
    }
    else
    {
        consume(OR);
    }
}

void consumeTerm()
{
    consumeFactor();
    while (lookahead.atom == MULTIPLICATION || lookahead.atom == DIVISION || lookahead.atom == MOD || lookahead.atom == AND)
    {
        consumeOperatorTerm();
        consumeFactor();
    }
}

void consumeFactor()
{
    if (lookahead.atom == IDENTIFIER)
    {
        consume(IDENTIFIER);
    }
    else if (lookahead.atom == INTEGER_NUMBER)
    {
        consume(INTEGER_NUMBER);
    }
    else if (lookahead.atom == REAL_NUMBER)
    {
        consume(REAL_NUMBER);
    }
    else if (lookahead.atom == CHARACTER)
    {
        consume(CHARACTER);
    }
    else if (lookahead.atom == TRUE)
    {
        consume(TRUE);
    }
    else if (lookahead.atom == FALSE)
    {
        consume(FALSE);
    }
    else if (lookahead.atom == NOT)
    {
        consume(NOT);
        consumeFactor();
    }
    else
    {
        consume(OPEN_PARENTHESES);
        consumeExpression();
        consumeExpression(CLOSE_PARENTHESES);
    }
}

void consumeOperatorTerm()
{
    if (lookahead.atom == MULTIPLICATION)
    {
        consume(MULTIPLICATION);
    }
    else if (lookahead.atom == DIVISION)
    {
        consume(DIVISION);
    }
    else if (lookahead.atom == MOD)
    {
        consume(MOD);
    }
    else
    {
        consume(AND);
    }
}