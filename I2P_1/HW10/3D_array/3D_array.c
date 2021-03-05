#include "3D_array.h"
#include <stdlib.h>
#include <stdio.h>

unsigned*** new_3d_array(unsigned n,unsigned m,unsigned k){
    unsigned* ptr = (unsigned*)malloc(n*m*k*sizeof(unsigned));
    unsigned** pptr = (unsigned**)malloc(n*m*sizeof(unsigned*));
    unsigned*** ppptr = (unsigned***)malloc(n*sizeof(unsigned**));

    for(unsigned i = 0;i<n;i++){
        ppptr[i] = pptr + i*m;
        for(unsigned j = 0;j<m;j++){
            pptr[i*m+j] = ptr+(i*m+j)*k;
        }
    }
    return ppptr;
}
void delete_3d_array(unsigned ***arr){
    /*
    for(int i = 0;i<sizeof(arr)/sizeof(unsigned**);i++){
        for(int j = 0;j<sizeof(arr[i])/sizeof(unsigned*);j++){
            free(arr[i][j]);
        }
    }
    */
    /*
    int i = 0;
    while(arr[i] != NULL){
        int j = 0;
        while(arr[i][j] != NULL){
            free(arr[i][j]);
            printf("Freed memory on i = %d,j = %d\n",i,j);
            j++;
        }
        free(arr[i]);
        printf("Freed memory on i = %d\n",i);
        i++;
    }
    */
    free(arr[0][0]);
    free(arr[0]);
    free(arr);
}