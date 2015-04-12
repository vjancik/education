#include <stdio.h>
#include <stdlib.h>

long long totalComp = 0;

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int* median(int *a, int *b, int *c) {
    int array[3] = {*a,*b,*c};
    qsort(array, 3, sizeof(int), cmpfunc);

    return (*a==array[1]) ? a : ((*b==array[1]) ? b : c);
}

void swap(int *a, int *b) {
    if(*a!=*b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

int partition(int arr[], int l, int r) {
    totalComp += r-l - 1;
    //int* medianI = median(&arr[l],&arr[(r-1-l)/2  + l], &arr[r-1]);
    //swap(&arr[l],medianI);
    //swap(&arr[l],&arr[r-1]);
    //printf("Variables:%d %d; Median %d, %d, %d: %d\n", l, r, arr[l], arr[(r-l)/2+l], arr[r-1], *medianI);
    int pivot = arr[l];
    int i = l + 1;

    for (int j = l + 1; j < r; ++j) {
        if (arr[j] < pivot) {
            swap (&arr[i], &arr[j]);
            ++i;
        }
    }
    swap (&arr[i-1], &arr[l]);
    return (i-1);
}
void quickSort(int arr[], int l, int r)
{
    if(l + 1< r)
    {
        int p = partition(arr, l, r);
        quickSort(arr, l , p);
        quickSort(arr, p + 1, r);
    }
}

int main(int argc, const char *argv[])
{
    int array[10000];
    FILE * fp;

    fp = fopen("QuickSort.txt","r");
    if(ferror(fp) ) {
        printf("Error in opening file.\n");
        return 0;
    }

    for (int i=0; i<10000; ++i) {
        fscanf(fp, "%d", &array[i]);
    }

    quickSort(array, 0, 10000);
    for (int i=0; i<10; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("Total comparisons: %lld\n",totalComp);
    return 0;
}
