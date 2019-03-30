#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

int main(void)
{
    int* matrix[10];
    for(int i=0;i<10;i++){
        matrix[i]=smalloc(10*sizeof(int));
        for(int j = 0;j<10;j++){
            matrix[i][j]=i*10+j;
        }
    }
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<10;i++){
        sfree(matrix[i]);
        matrix[i]=NULL;
    }

    // dump_addr();
    return 0;
}