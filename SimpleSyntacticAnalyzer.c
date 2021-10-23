#include <stdio.h>
#include <stdlib.h>
#include "AnalyzerTypes.h"

char *buffer = "a";
char *iniBuffer;
TInformationAtom lookahead;

void consume(TInformationAtom atom);

int main(void)
{
    iniBuffer = buffer;
    lookahead = obter_atomo();

    E();
    if (lookahead.atom == EOS)
    {
        printf("palavra aceita");
    }
    else
    {
        printf("\nErro sintatico 2. Nao cheguei ao final da palavra");
    }

    printf("\nfim de analise sintatica.");
    return 0;
}
void consume(TInformationAtom atom)
{
    if (lookahead == atomo)
        lookahead = *buffer++; // obter_atomo();
    else
    {
        printf("erro sintatico: esperado [%c] encontrado [%c] indice [%d]\n", atomo, lookahead, (buffer - iniBuffer) - 1);
        exit(1);
    }
}
