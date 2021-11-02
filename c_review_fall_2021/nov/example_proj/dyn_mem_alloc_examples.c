//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//
//    // USE OF malloc() for run-time allocation of memory for an array
//
////    // This pointer will hold the
////    // base address of the block created
////    int* ptr;
////    int n, i;
////
////    // Get the number of elements for the array
////    printf("Enter number of elements:");
////    scanf("%d",&n);
////    printf("Entered number of elements: %d\n", n);
////
////    // Dynamically allocate memory using malloc()
////    ptr = (int*)malloc(n * sizeof(int));
////
////    // Check if the memory has been successfully
////    // allocated by malloc or not
////    if (ptr == NULL) {
////        printf("Memory not allocated.\n");
////        exit(0);
////    }
////    else {
////
////        // Memory has been successfully allocated
////        printf("Memory successfully allocated using malloc.\n");
////
////        // Get the elements of the array
////        for (i = 0; i < n; ++i) {
////            ptr[i] = i + 1;
////        }
////
////        // Print the elements of the array
////        printf("The elements of the array are: ");
////        for (i = 0; i < n; ++i) {
////            printf("%d, ", ptr[i]);
////        }
////    }
//
//    // USE OF calloc()
//    /* void* calloc(size_t nitems, size_t size);
//     * Has a very similar use to malloc() except the memory it allocates will be initialized with zeros instead of
//     * left containing garbage. Also, calloc() takes two arguments instead of one, one for the # of items and the other
//     * for the size of each item.
//     */
//
//    // You can use the exact same example as the last one except replace the line ptr = (int*)malloc(n * sizeof(int));
//    // with ptr = (int*) calloc(n, sizeof(int));
//    // This pointer will hold the
//    // base address of the block created
//    int* ptr;
//    int n, i;
//
//    // Get the number of elements for the array
//    printf("Enter number of elements:");
//    scanf("%d",&n);
//    printf("Entered number of elements: %d\n", n);
//
//    // Dynamically allocate memory using malloc()
//    ptr = (int*) calloc(n, sizeof(int));
//
//    // Check if the memory has been successfully
//    // allocated by malloc or not
//    if (ptr == NULL) {
//        printf("Memory not allocated.\n");
//        exit(0);
//    }
//    else {
//
//        // Memory has been successfully allocated
//        printf("Memory successfully allocated using calloc.\n");
//
//        // Get the elements of the array
//        for (i = 0; i < n; ++i) {
//            ptr[i] = i + 1;
//        }
//
//        // Print the elements of the array
//        printf("The elements of the array are: ");
//        for (i = 0; i < n; ++i) {
//            printf("%d, ", ptr[i]);
//        }
//    }
//
//    // And then, as you should ALWAYS do when using dynamic memory allocation, make sure to free up the dynamically
//    // allocated memory after you're done using it! Such memory is NOT automatically freed up and may unnecessarily
//    // take up heap space!
//    free(ptr);
//    printf("\n\nMemory has now been freed using free().\n");
//
//    return 0;
//}
