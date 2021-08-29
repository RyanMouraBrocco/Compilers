#include <stdio.h>
#include <stdlib.h>

int main()
{
    int valueA = 2;
    int valueB = 3;

    if (valueA > valueB)
    {
        printf("A bigger than B");
    }
    else if (valueA < valueB)
    {
        printf("B bigger than A");
    }
    else
    {
        printf("A and B have same value");
    }

    return 0;
}
