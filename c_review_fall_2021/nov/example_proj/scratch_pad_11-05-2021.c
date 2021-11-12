////
//// Created by abdullah on 11/09/21.
////
//
//#include <stdio.h>
//#include <stdint.h>
//#include <stdlib.h>
//
//
//void main(void){
//
//    uint32_t elapsed_time = 0x0FAEF381u;
//    uint32_t division_result1 = elapsed_time / 10000000u;
//    uint16_t division_result2 = (uint16_t) (elapsed_time / 10000000u);
//
//    uint16_t num_of_seconds = (uint16_t) (elapsed_time / 10000000u);
////    uint32_t num_of_ms = elapsed_time - ((uint32_t) num_of_seconds * 10000000u);    // Take remainder and then that / 10,000 is ms
////    uint32_t num_of_ms = elapsed_time % 10000000u;    // Take remainder and then that / 10,000 is ms
//    uint16_t num_of_ms = (uint16_t) ((elapsed_time % 10000000u) / 10000u);    // Take remainder and then that / 10,000 is ms
//    uint16_t num_of_us = (uint16_t) ((elapsed_time % 10000000u) % 10000u) / 10u;
//
//    printf("Elapsed Time: %u\n\n", elapsed_time);
//    printf("Division Result 1 (no type-casting, 32-bit, integer division by 10,000,000): %d\n", division_result1);
//    printf("Division Result 2 (type-cast to 16-bit AFTER 32-bit division, integer division by 10,000,000: %d\n\n", division_result2);
//
//    printf("Number of seconds: %d seconds\n", num_of_seconds);
//    printf("Number of milliseconds: %d ms\n", num_of_ms);
//    printf("Number of microseconds: %d us", num_of_us);
//
//
//}