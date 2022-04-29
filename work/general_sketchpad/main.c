#include <stdio.h>
#include <stdint.h>
#include "circular_queue.h"

#define QUEUE_SIZE  30U

typedef enum Current_State { NOT_BLINKING, BLINKING } Current_State_E;
typedef enum BatteryAvailability_Array {BATTERY_UNAVAILABLE = 0, BATTERY_AVAIALBLE} BatteryAvailability_E;

static Current_State_E current_state = NOT_BLINKING;
static uint8_t has_been_reset = 0u;

uint16_t conv_float_to_PackCurrent_T(float currentval);
const static float pack_current_slope = 0.06F;
const static float pack_current_bias = -2000.0F;

// Testing out my circular_queue implementation
uint8_t buffer[QUEUE_SIZE];
queue_t my_queue;
queue_handle_t my_queue_handle = &my_queue;

int main() {

    // Reset buffer to all zeros
    for(size_t i=0; i<QUEUE_SIZE; i++){
        buffer[i] = 0u;
    }
    // Testing out my circular queue implementation
    queue_init(my_queue_handle, buffer, QUEUE_SIZE);
    // Let's add in some items
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    queue_put(my_queue_handle, 1);
    // Print current queue
    print_queue(my_queue_handle);
    // Let's remove some items and add in a second round of items
    uint8_t data1 = 0u;
    queue_get(my_queue_handle, &data1);
    queue_get(my_queue_handle, &data1);
    queue_get(my_queue_handle, &data1);
    queue_put(my_queue_handle, 2);
    queue_put(my_queue_handle, 2);
    queue_put(my_queue_handle, 2);
    queue_put(my_queue_handle, 2);
    // Print current queue
    print_queue(my_queue_handle);
    // Now let's add in a bunch, allowing overwriting beyond the head of the queue
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    queue_put(my_queue_handle, 3);
    // Print current queue
    print_queue(my_queue_handle);



//    // Testing out the ternary operation counter = (current_state == NOT_BLINKING) ? ++counter : 0u;
//    uint8_t counter = 0u;
//
//    while(counter < 10u) {
//        if(counter >= 5u && has_been_reset == 0u) {
//            current_state = BLINKING;
//            has_been_reset = 1u;
//        }
//        else if (has_been_reset == 1u) current_state = NOT_BLINKING;
//
//        counter = (current_state == NOT_BLINKING) ? ++counter : 0u;
//        printf("%d\n", counter);
//    }

    // Testing out MATLAB's accumpos generated code --> line 1541
//    float example_curr_val = 45.22F;
//    uint16_t example_curr_val_fixdt = conv_float_to_PackCurrent_T(example_curr_val);
//    printf("Example Current Value:\t\t\t\t\t%.2f\nExample Current Value Converted to Fixed-Point: \t%i\n",
//           example_curr_val, example_curr_val_fixdt);

//    BatteryAvailability_E batt_avail_array[6U] = {BATTERY_AVAIALBLE, BATTERY_AVAIALBLE, BATTERY_AVAIALBLE,
//                                                  BATTERY_UNAVAILABLE, BATTERY_UNAVAILABLE, BATTERY_UNAVAILABLE};
//    float pack_current_vals[6] = {43.2F, 44.1F, 45.1F, 0.0F, 0.0F, 0.0F};
////    float pack_current_vals[6] = {1932.1F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
////    float pack_current_vals[6] = {-2000.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
//    uint16_t PackCurrent_Array[6];
//    for (uint8_t i = 0; i < 6; i++) {
//        PackCurrent_Array[i] = conv_float_to_PackCurrent_T(pack_current_vals[i]);
//    }
//    uint16_t total_pack_curr_filtered = 33333U;
//    float total_pack_curr_float = 0.0F;
//    int16_t sigIdx;
//    for (sigIdx = 0; sigIdx < 10; sigIdx++) {
//        if (batt_avail_array[sigIdx] == BATTERY_AVAIALBLE) {
//            total_pack_curr_filtered = (uint16_t)((uint16_t)(total_pack_curr_filtered + PackCurrent_Array[sigIdx]) - 33333U);
//            total_pack_curr_float += pack_current_vals[sigIdx];
//        }
//    }
//    // Print out results to see if this worked
//    // First pack current values
//    printf("\t\t\tRWV\t\tSI\n");
//    for (uint8_t i = 0; i < 6; i++) {
//        printf("Index %i:\t\t%.2f\t\t%i\n", i,pack_current_vals[i],PackCurrent_Array[i]);
//    }
//    // Now the total_pack_curr variables...
//    printf("\nTotal Pack Current (float):\t\t%.2f\nTotal Pack Current (computed SI):\t%i\nTotal Pack Current (expected SI):\t%i\n",
//           total_pack_curr_float, total_pack_curr_filtered, conv_float_to_PackCurrent_T(total_pack_curr_float));
//
//    printf("\nExample first computation: (uint16_t)(33333U + 34053U):\t\t\t\t\t%i\n", (uint16_t)(33333U + 34053U));
//    printf("Example second part of computation: (uint16_t)(33333U + 34053U) - 33333U:\t\t%d\n", (uint16_t)(33333U + 34053U) - 33333U);
//    printf("Example last part of computation: (uint16_t)((uint16_t)(33333U + 34053U) - 33333U):\t%i\n", (uint16_t)((uint16_t)(33333U + 34053U) - 33333U));


    return 0;
}

// PackCurrent_Standard_CAN_T is a fixed-point type with slope/bias of 0.06/-2000
// Recall RWV = SI * slope + bias
//        SI  = (RWV - bias) / slope
uint16_t conv_float_to_PackCurrent_T(float currentval) {
    uint16_t PackCurrent_T_val = 0u;

    PackCurrent_T_val = (uint16_t) ( (currentval - pack_current_bias) / pack_current_slope );

    return PackCurrent_T_val;
}
