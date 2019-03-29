#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    void* p = malloc(64);
    void* p1 = malloc(64);
    void* p2 = malloc(64);

    printf("p:%p, p1:%p, p2:%p\n", p, p1, p2);

    free(p);
    free(p1);
    free(p2);

    return 0;
}