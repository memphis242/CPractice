#include <stdio.h>
#include <stdint.h>

int main(void)
{
   // Input Scale: 1/32768 (2^-16) deg/bit
   // Input Offset: -250 deg

   // RWV = 60 deg
   // SI = ( RWV - OFFSET ) / SCALE = ( 60 - (-250) ) / (2^-16) = 20,316,160

   const int32_t deg_in = 20316160u;
}