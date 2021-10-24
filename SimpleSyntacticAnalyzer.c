#include <stdio.h>
#include <stdlib.h>
#include "AnalyzerTypes.h"
#include "SimpleLexAnalyzer.h"
#include "ReaderFile.h"

char *buffer;
char *iniBuffer;
TInformationAtom lookahead;

void consume(TInformationAtom atom);

int main(void)
{
    buffer = readFile("input.c");
    iniBuffer = buffer;
    lookahead = getAtom();

    syntaticAnalyze();
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

void consume(TInformationAtom atom)
{
    if (lookahead.atom == atom.atom)
        lookahead = getAtom(buffer++);
    else
    {
        printf("erro sintatico: esperado [%c] encontrado [%c] indice [%d]\n", atom.atom, lookahead.atom, (buffer - iniBuffer) - 1);
        exit(1);
    }
}

void syntacticAnalyze()
{
}