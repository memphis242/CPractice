#include "ch1to10.h"
#include "ch11.h"
#include "ch12.h"

#define EXAMPLE_STR_LITERAL "I am an example string literal"

static int static_internal_var = 5; //A static variable of file scope with internal linkage
int static_extern_var = 10;         //A static variable of file scope with external linkage

void auto_func_ex(void);    //Including prototype here instead of header because function's purpose needs to be here.
extern void function_without_header(void);

int main()
{

////USE OF STATIC MODIFIER
//    print_title("Difference between static and non-static variables in static_var_ex() function.");
//    for(int i=0; i<10; i++) {
//        static_var_ex();
//    }
//
////DIFFERENCE BETWEEN AUTO AND FILE-SCOPE VARIABLES
//    print_title("Difference between Automatic Variables and Variables of File-Scope");
//    printf("Static Internal Variable: %d\n"
//            "Static External Variable: %d\n", static_internal_var, static_extern_var);
//    puts("");
//    auto_func_ex();
//
////REFERENCING A FILE-SCOPE STATIC VARIABLE WITH INTERNAL LINKAGE IN A FUNCTION
//    print_title("Referencing a File-Scope Variable With Internal Linkage in a Function Using extern");
//    //auto static_internal_var = 25;    --> NOPE. DOESN'T WORK.
//    extern int static_internal_var; //Even though it has internal linkage, the keyword extern here is just used to explicitly state this is using the file-scope variable
//
//    printf("static_internal_val: %d\n", static_internal_var);
//
////USING AN EXTERNAL VARIABLE INITIALIZED IN THIS FILE IN ANOTHER FILE
//    char title_str[200] = "Using an External Variable Initialized in ";
//    strcat(title_str, __FILE__);
//    strcat(title_str, " in Another File");
//    print_title(title_str);
//
//    print_external();
//
////TRYING TO USE A STATIC FUNCTION IN ANOTHER FILE
//    print_title("Trying to Use a Static Function in Another File");
//
////    useless_function(); //--> Compiler doesn't recognize.
//
////USING AN EXTERNAL FUNCTION IN ANOTHER FILE WITHOUT HEADER IN ANOTHER FILE
//    print_title("Using an External Function in Another File Without Including Header File for It");
//
//    function_without_header();

//USE OF MALLOC() FOR DYNAMIC ARRAY!
//    print_title("Use of malloc() to Make a Dynamic Array!");
//
//    int* int_arr_ptr;
//    int num_of_elements, start_of_range, end_of_range, range_width;
//
//    printf("How many elemnts would you like in this array? ");
//    scanf("%d", &num_of_elements);
//    printf("What would you like the range of the random numbers to be? (Enter start and end inclusive) ");
//    scanf("%d%d", &start_of_range, &end_of_range);
//    range_width = end_of_range - start_of_range;
//
//    int_arr_ptr = (int*) malloc(num_of_elements * sizeof(int));   //THE MAGIC!
//
//    if(!int_arr_ptr) {   //Precaution.
//        puts("Memory allocation failed :(.");
//        exit(EXIT_FAILURE);
//    }
//
//    for(int i=0; i<num_of_elements; i++) {
//        int_arr_ptr[i] = start_of_range + (rand() % range_width);
//    }
//
//    print_array(int_arr_ptr, num_of_elements);
//
//    free(int_arr_ptr);  //GARBAGE MANAGEMENT

//DIFFERENCES BETWEEN REGIONS OF MEMORY - STATIC, AUTOMATIC (STACK), AND DYNAMICALLY-ALLOCATED (HEAP)
    print_title("Differences Between Regions of Memory At Runtime: Static, Automatic (Stack), and Dynamically Allocated (Heap)");

    static int static_var;

    auto int auto_int_var;
    auto char* auto_str;
    double auto_double;

    int* int_ptr = (int*) (malloc(1 * sizeof(int)));
    char* char_ptr = (char*) (malloc(20 * sizeof(char)));
    double* double_ptr = (double*) (malloc(10 * sizeof(double)));

    printf("Static Types:\n");
    printf("%-25s %p\n", "static_var:" , &static_var);
    printf("%-25s %p\n", "static_extern_var:" , &static_extern_var);
    printf("%-25s %p\n", "static_intern_var:" , &static_internal_var);
    printf("%-25s %p\n", "String Literal:" , &EXAMPLE_STR_LITERAL);

    new_line();

    printf("Automatic Types (Stack):\n");
    printf("%-25s %p\n", "auto_int_var:" , &auto_int_var);
    printf("%-25s %p\n", "auto_str:" , &auto_str);
    printf("%-25s %p\n", "auto_double:", &auto_double);
    printf("%-25s %p\n", "Integer Array Literal:", (int[5]) {1, 2, 3, 4, 5});
    printf("%-25s %p\n", "Double Array Literal:", (double[2]) {1.20, 2.40});

    new_line();

    printf("Dynamically Allocated Types (using malloc()) (Heap):\n");
    printf("%-25s %p\n", "int_ptr:", int_ptr);
    printf("%-25s %p\n", "char_ptr:", char_ptr);
    printf("%-25s %p\n", "double_ptr:", double_ptr);

    new_line();

    return 0;
}

void auto_func_ex(void) {
    auto int static_internal_var = 8;   //Automatic variable with block scope and no linkage that shadows file scope variable
    auto int static_extern_var = 15;    //Automatic variable with block scope and no linkage that shadows file scope variable

    printf("Static Internal Variable in Function %s : %d\n"
            "Static External Variable in Function %s : %d\n", __func__, static_internal_var, __func__, static_extern_var);
}
