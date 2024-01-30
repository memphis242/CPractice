#include <stdio.h>
#include "float_func.h"

struct myFloats
{
   float engine_speed;
   float battery_soc;
   float temperature;
};

struct myFloats struct_arr[10] =
{
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 },
   { 0.0, 1.0, 2.0 }
};

int main(void)
{

   printf("Printing struct_arr through its original type:\n\n");
   for( int i = 0; i < 10; i++ )
   {
      printf("struct_arr[%d].engine_speed: %.1f\t\tstruct_arr[%d].battery_soc: %.1f\t\tstruct_arr[%d].temperature: %.1f\n",
                  i, struct_arr[i].engine_speed, i, struct_arr[i].battery_soc, i, struct_arr[i].temperature);
   }

   print_float_array( (float *) struct_arr, 10 );
}