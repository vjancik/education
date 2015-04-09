#include <stdio.h>

long long totalInv = 0;

void mergeAndCount(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(i = 0; i < n1; ++i)
        L[i] = arr[l+i];
    for(j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
            totalInv+=n1-i;
        }
        ++k;
    }

    while(i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while(j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        mergeAndCount(arr, l, m, r);
    }
}

int main(int argc, const char *argv[])
{
    int array[100000];
    FILE * fp;
    //load file
    fp = fopen("IntegerArray.txt","r");
    if(ferror(fp) )
    {
        printf("Error in opening file.\n");
        return 0;
    }
    //read file
    for(int i=0; i<100000; ++i){
        fscanf(fp,"%d",&array[i]);
    }
    //launch algorithm
    mergeSort(array,0,99999);
    //print result
    //for (int i=0; i<100000; ++i){
    //    printf("%d ", array[i]);
    //}
    printf("\n");
    printf("Total inversions: %lld\n",totalInv);
    return 0;
}
