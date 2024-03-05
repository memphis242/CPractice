#include <stdio.h>
#include <string.h>

typedef int InverterIMM_Int_Array[10];

int main(void)
{
    InverterIMM_Int_Array arr = {0};
    arr[5] = 10;

    printf("\nsizeof(arr):\t\t\t\t\t%d", sizeof(arr));
    printf("\nsizeof(InverterIMM_Int_Array):\t\t\t%d", sizeof(InverterIMM_Int_Array));
    printf("\nsizeof(InverterIMM_Int_Array) / sizeof(int):\t%d", sizeof(InverterIMM_Int_Array) / sizeof(int));
    printf("\narr[0]:\t\t\t\t\t\t%d", arr[0]);
    printf("\narr[5]:\t\t\t\t\t\t%d\n\n", arr[5]);
    
    return 0;
}
