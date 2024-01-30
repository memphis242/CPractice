#include <stdio.h>

void print_float_array( const float * float_arr, size_t arr_size )
{
   printf("\n\nPrinting struct_arr through a float pointer:\n\n");
   for( int i = 0; i < arr_size; i++ )
   {
      int j = i*3;
      printf("float_arr[%3d]: %.1f\t\tfloat_arr[%3d+1]: %.1f\t\tfloat_arr[%3d+2]: %.1f\n",
                  j, float_arr[j], j, float_arr[j+1], j, float_arr[j+2]);
   }

}