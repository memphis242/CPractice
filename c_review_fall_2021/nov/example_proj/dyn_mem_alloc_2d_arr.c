//
// Created by Abdullah Almosalami on 11/01/21.
//

// Source of examples: https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/?ref=lbp
/* There are at least four different ways to allocate memory dynamically for 2d arrays, and the following
 * examples present such methods.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void print_2d_arr_method_3(size_t height, size_t width, int arr[][width]);
void print_2d_arr_method_4(int * arr, size_t height, size_t width);
void print_2d_arr_method_5(size_t height, size_t width, int (*arr)[width]);


void main(void) {

//    /* 1. USING A SINGLE POINTER
//     * Essentially treat the whole 2d array as a single line of memory and just use clever indexing to access it
//     * as if it were a 2d array. The key is to realize that arr[i][j] = *(arr + i*width + j) = *(*(arr + i) + j).
//     * Also realize then that in order to work with 2d arrays in this manner, you need to know the width of the array.
//     */
//    size_t height = 3u, width = 4u;    // Numbers of height and columns
//    int * ptr;
//    ptr = (int*) malloc((height * width) * sizeof(int));
//
//    // Ensure memory was allocated successfully
//    if(ptr == NULL){
//        printf("Failed to allocated memory for 2d array using malloc(). :(");
//        exit(0);
//    }
//
//    // Let's fill up the 2d array with some values
//    unsigned int count = 1u;
//    for(int i=0; i < height; i++){
//        for(int j=0; j < width; j++){
//            *(ptr + i * width + j) = count;
//            count++;
//        }
//    }
//
//    // Now let's print out the 2d array
//    for(int i=0; i<height; i++){
//        for(int j=0; j<width; j++){
//            printf("%d\t", *(ptr + i*width + j));
//        }
//        printf("\n");
//    }
//
//    // Now free up the memory space that was dynamically allocated.
//    free(ptr);


//    /* 2. USING AN ARRAY OF POINTERS
//     * Recall that a 2d array is really an array of pointers. You can treat an array of size arr[n][m] as follows:
//     * first you have an array of n elements arr[n], whose types are all [m] - i.e., pointers to m-element arrays.
//     * So, you may begin with first allocating memory for this array of pointers, then allocating memory for each
//     * pointer element.
//     */
//
//    size_t rows = 3, cols = 4;
//    int * arr[rows];    // NOTE that post-C99, using non-literals within the size of an array is allowed. Prior to that,
//                        // such syntax was not allowed.
//
//    // Allocate memory
//    for(int i =0; i<rows; i++){
//        arr[i] = (int *) malloc(cols * sizeof(int));
//        if(arr[i] == NULL){
//            printf("Failed to allocate memory completely.");
//            exit(0);
//        }
//    }
//
//    // Fill up with values
//    unsigned int count = 1u;
//    for(int i=0; i<rows; i++){
//        for(int j=0; j<cols; j++){
//            arr[i][j] = count;
//            count++;
//        }
//    }
//
//    // Print away!
//    for(int i=0; i<rows; i++){
//        for(int j=0; j<cols; j++){
//            printf("%d\t", arr[i][j]);
//        }
//        printf("\n");
//    }
//
//    // Now free up memory space from each row
//    for(int i=0; i<rows; i++){
//        free(arr[i]);
//    }

    /* 3. USING POINTERS TO POINTERS
     * This is the exact same as method 2 except replace int * arr[rows]; with
     * int** arr = (int**) malloc(rows*sizeof(int*)). Otherwise, the code is identical.
     */

    /* 4. USING POINTER-TO-POINTERS AND ONE MALLOC CALL
     * This one didn't make much sense to me. I think I'll stick to methods 1 and 2 for now.
     */

    /* -------------------------------------------------------------------------------------------------------
     * In addition to dynamically allocating memory for 2d arrays, it is often the case that such scenarios come up
     * when you need to pass such arrays to functions. We know 1d arrays can be easily passed using a pointer and
     * another argument to indicate the size of the array. 2d arrays are a little more involved. We will look at this
     * in the following examples. I am sourcing these examples from:
     * https://www.geeksforgeeks.org/pass-2d-array-parameter-c/?ref=lbp
     */

    int arr[][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
    int height = 3, width = 3;

    // The first two examples on the page require you to use globally defined constants for the width, height, or both.
    // Let's say you don't know such sizes beforehand until the function is called. Well... voila:

    // METHOD 3: If compiler is C99 compatible...
    printf("METHOD 3:\n");
    print_2d_arr_method_3(height, width, arr);
    printf("\n\n");

    // METHOD 4: If you're using C standards preceding C99... --> Using a single pointer
    printf("METHOD 4:\n");
    print_2d_arr_method_4((int *)arr, height, width);
    printf("\n\n");

    // METHOD 5:
    printf("METHOD 5:\n");
    print_2d_arr_method_5(height, width, arr);
    printf("\n\n");

}


void print_2d_arr_method_3(size_t height, size_t width, int arr[][width]){

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

}

void print_2d_arr_method_4(int * arr, size_t height, size_t width){

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            printf("%d\t", *(arr + i*width + j));
        }
        printf("\n");
    }

}

void print_2d_arr_method_5(size_t height, size_t width, int (*arr)[width]){

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }

}




