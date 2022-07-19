#include <stdio.h>
#include <stdint.h>

static const uint16_t current_limit1 = 32600U;  // 30A in CurrentLimit_T form: Scale: 0.05, Offset: -1600
static const uint16_t current_limit2 = 43178U;  // 558.9 in CurrentLimit_T --> The max that can be multiplied by 3 before upper limit of CurrentLimit_T
static const uint16_t num_of_packs = 3u;
static const uint16_t dc_bus_voltage = 7842U; // 392.1V /w Scale: 0.05
static const uint16_t current_limit3 = 34064U; // 103.2A /w Scale: 0.05, Offset: -1600


int main(void) {

    uint16_t assembly_current_limit1;
    uint16_t assembly_current_limit2;
    uint16_t power_limit;

    assembly_current_limit1 = (uint16_t) ( ( ( (int32_t) current_limit1 * num_of_packs ) + (32000L * (1L - ((int32_t)num_of_packs) )) ) );
    assembly_current_limit2 = (uint16_t) ( ( ( (int32_t) current_limit2 * num_of_packs ) + (32000L * (1L - ((int32_t)num_of_packs) )) ) );

    printf("Current Limit 1:\t\t%.2f\nCurrent Limit 2:\t\t%.2f\n\n", ((float)current_limit1 * 0.05 - 1600.0), ((float)current_limit2 * 0.05 - 1600.0));
    printf("Assembly Limit 1:\t\t%.2f\nAssembly Limit 2:\t\t%.2f\n\n", ((float)assembly_current_limit1 * 0.05 - 1600.0), ((float)assembly_current_limit2 * 0.05 - 1600.0));

    // Now let's try the power calc
    power_limit = (uint16_t) ( ((uint32_t)(dc_bus_voltage / 20)) * ((uint32_t)((((int32_t)current_limit3) / 20) - 1600) ) / 50);
    printf("DC Bus Voltage (V):\t\t%.2f\nCurrent Limit (A):\t\t%.2f\n", ((float)dc_bus_voltage * 0.05), ((float)current_limit3 * 0.05 - 1600.0));
    printf("Power Limit (kW):\t\t%.2f\n\n", ((float)power_limit * 0.05));

    // Debugging
    uint32_t val1 = ((uint32_t)(dc_bus_voltage / 20));
    uint32_t val2 = ((uint32_t)(((int32_t)current_limit3) / 20) - 1600);
    uint32_t val3 = val1 * val2;
    uint32_t val4 = val3 / 50;
    uint16_t val5 = (uint16_t) val4;

    return 0;
}







//#include "circular_queue.h"


//#define NUM_OF_RELEVANT_MSGS_RX 24U

//const static uint16_t RELEVANT_ID_TABLE[NUM_OF_RELEVANT_MSGS_RX] =
//        {
//                128U, 129U, 130U,
//                160U, 161U, 162U,
//                288U, 289U, 290U,
//                352U, 353U, 354U,
//                448U, 449U, 450U,
//                608U, 609U, 610U,
//                704U, 705U, 706U,
//                896U, 897U, 898U
//        };
//#define RELEVANT_ID_TABLE_MID_INDEX     (NUM_OF_RELEVANT_MSGS_RX / 2)
//#define RELEVANT_ID_TABLE_MAX_INDEX     (NUM_OF_RELEVANT_MSGS_RX - 1)
//
//static uint16_t example_ids[10u] =
//        { 898U, 128U, 449U, 898U, 2900U, 610U, 615U, 285U, 1000U, 447U };
//const static uint8_t example_ids_expected_relevancy[10U] =
//        { 1U,   1U,   1U,   1U,   0U,    1U,   0U,   0U,   0U,    0U };


//uint8_t std_queue_id_relevant(uint16_t id) {

//    uint8_t relevancy_val = 0u;
//
//    // Perform the hash function on the id
//    // FOR NOW, DON'T HAVE A GOOD HASH FUNCTION SO WILL USE TABLE INSTEAD
//    // Return the relevancy value the corresponded to this id
//
//    // Utilizing the RELEVANT_ID_TABLE... perform a binary search
//    // Go into search if value is within range of table, assuming table is sorted least to greatest
//    if ( id >= RELEVANT_ID_TABLE[0u] && id <= RELEVANT_ID_TABLE[RELEVANT_ID_TABLE_MAX_INDEX] ) {
//
//        uint8_t check_range_left = 0u;
//        uint8_t check_range_right = RELEVANT_ID_TABLE_MAX_INDEX;
//        uint8_t check_index = (check_range_right + check_range_left) >> 1;
//
//        // As long as the check range has a width greater than 1, keep searching
//        while( (check_range_right - check_range_left) > 0 ) {
//
//            // If we get an ID match...
//            if ( id == RELEVANT_ID_TABLE[check_index] ) {
//                relevancy_val = 1u;
//                break;
//
//                // Otherwise, update the check range and index
//            } else if ( id > RELEVANT_ID_TABLE[check_index] ) {
//                // To cover the corner case of the ID matching the last entry in the table...
//                if ( check_range_left == (check_range_right - 1u) ) {
//                    relevancy_val = (id == RELEVANT_ID_TABLE[check_range_right]);   // we will now check the last index
//                    break;
//                } else {
//                    check_range_left = check_index;
//                }
//
//            } else {
//                check_range_right = check_index;
//            }
//
//            check_index = (check_range_right + check_range_left) >> 1;
//
//        }
//
//    }
//
//    return relevancy_val;
//}

//uint8_t std_queue_id_relevant_linsearch(uint16_t id) {
//
//    uint8_t relevancy = 0u;
//
//    if ( id >= RELEVANT_ID_TABLE[0u] && id <= RELEVANT_ID_TABLE[RELEVANT_ID_TABLE_MAX_INDEX] ) {
//        for (uint8_t i = 0; i <= RELEVANT_ID_TABLE_MAX_INDEX; i++) {
//
//            if (id == RELEVANT_ID_TABLE[i]) {
//                relevancy = 1u;
//                break;
//            }
//        }
//    }
//
//    return relevancy;
//
//}



// WITHIN MAIN FUNCTION:
//    uint8_t quick_example = std_queue_id_relevant(615U);
//    printf("%d", quick_example);

//    // TEST 1 - Binary search wih small sample inputs
//    static uint8_t relevancy_compute[10u];
//
//    for (uint8_t i=0u; i<10u; i++) {
//        relevancy_compute[i] = std_queue_id_relevant(example_ids[i]);
//    }
//
//    printf("\nResults:\t\tComputed\tExpected\n");
//    for (uint8_t i=0u; i<10u; i++) {
//        printf("\t\t\t    %d--------------%d\n", relevancy_compute[i], example_ids_expected_relevancy[i]);
//    }

//    // TEST 2 - Linear search with small sample inputs
//    static uint8_t relevancy_compute[10u];
//
//    for (uint8_t i=0u; i<10u; i++) {
//        relevancy_compute[i] = std_queue_id_relevant_linsearch(example_ids[i]);
//    }
//
//    printf("\nResults:\t\tComputed\tExpected\n");
//    for (uint8_t i=0u; i<10u; i++) {
//        printf("\t\t\t    %d--------------%d\n", relevancy_compute[i], example_ids_expected_relevancy[i]);
//    }

//    // TEST 3 - Full range test
//    uint8_t match = 1u;
//    uint8_t val1, val2;
//    for ( uint16_t i=0u; i<=65534u; i++ ) {
//        val1 = std_queue_id_relevant_linsearch(i);
//        val2 = std_queue_id_relevant(i);
//
//        if ( val1 != val2 ) {
//            match = 0u;
//            printf("\nMismatch!\n\t\tId: %d\tLin Search: %d\tBin Search: %d\n\n", i, val1, val2);
//            break;
//        }
//    }
//
//    if ( match ) printf("Test passed!");

//#define QUEUE_SIZE  30U
//
//typedef enum Current_State { NOT_BLINKING, BLINKING } Current_State_E;
//typedef enum BatteryAvailability_Array {BATTERY_UNAVAILABLE = 0, BATTERY_AVAIALBLE} BatteryAvailability_E;
//
//static Current_State_E current_state = NOT_BLINKING;
//static uint8_t has_been_reset = 0u;
//
//uint16_t conv_float_to_PackCurrent_T(float currentval);
//const static float pack_current_slope = 0.06F;
//const static float pack_current_bias = -2000.0F;
//
//// Testing out my circular_queue implementation
//uint8_t buffer[QUEUE_SIZE];
//queue_t my_queue;
//queue_handle_t my_queue_handle = &my_queue;
//
//int main() {
//
//    // Reset buffer to all zeros
//    for(size_t i=0; i<QUEUE_SIZE; i++){
//        buffer[i] = 0u;
//    }
//    // Testing out my circular queue implementation
//    queue_init(my_queue_handle, buffer, QUEUE_SIZE);
//    // Let's add in some items
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    queue_put(my_queue_handle, 1);
//    // Print current queue
//    print_queue(my_queue_handle);
//    // Let's remove some items and add in a second round of items
//    uint8_t data1 = 0u;
//    queue_get(my_queue_handle, &data1);
//    queue_get(my_queue_handle, &data1);
//    queue_get(my_queue_handle, &data1);
//    queue_put(my_queue_handle, 2);
//    queue_put(my_queue_handle, 2);
//    queue_put(my_queue_handle, 2);
//    queue_put(my_queue_handle, 2);
//    // Print current queue
//    print_queue(my_queue_handle);
//    // Now let's add in a bunch, allowing overwriting beyond the head of the queue
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    queue_put(my_queue_handle, 3);
//    // Print current queue
//    print_queue(my_queue_handle);
//
//
//
////    // Testing out the ternary operation counter = (current_state == NOT_BLINKING) ? ++counter : 0u;
////    uint8_t counter = 0u;
////
////    while(counter < 10u) {
////        if(counter >= 5u && has_been_reset == 0u) {
////            current_state = BLINKING;
////            has_been_reset = 1u;
////        }
////        else if (has_been_reset == 1u) current_state = NOT_BLINKING;
////
////        counter = (current_state == NOT_BLINKING) ? ++counter : 0u;
////        printf("%d\n", counter);
////    }
//
//    // Testing out MATLAB's accumpos generated code --> line 1541
////    float example_curr_val = 45.22F;
////    uint16_t example_curr_val_fixdt = conv_float_to_PackCurrent_T(example_curr_val);
////    printf("Example Current Value:\t\t\t\t\t%.2f\nExample Current Value Converted to Fixed-Point: \t%i\n",
////           example_curr_val, example_curr_val_fixdt);
//
////    BatteryAvailability_E batt_avail_array[6U] = {BATTERY_AVAIALBLE, BATTERY_AVAIALBLE, BATTERY_AVAIALBLE,
////                                                  BATTERY_UNAVAILABLE, BATTERY_UNAVAILABLE, BATTERY_UNAVAILABLE};
////    float pack_current_vals[6] = {43.2F, 44.1F, 45.1F, 0.0F, 0.0F, 0.0F};
//////    float pack_current_vals[6] = {1932.1F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
//////    float pack_current_vals[6] = {-2000.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F};
////    uint16_t PackCurrent_Array[6];
////    for (uint8_t i = 0; i < 6; i++) {
////        PackCurrent_Array[i] = conv_float_to_PackCurrent_T(pack_current_vals[i]);
////    }
////    uint16_t total_pack_curr_filtered = 33333U;
////    float total_pack_curr_float = 0.0F;
////    int16_t sigIdx;
////    for (sigIdx = 0; sigIdx < 10; sigIdx++) {
////        if (batt_avail_array[sigIdx] == BATTERY_AVAIALBLE) {
////            total_pack_curr_filtered = (uint16_t)((uint16_t)(total_pack_curr_filtered + PackCurrent_Array[sigIdx]) - 33333U);
////            total_pack_curr_float += pack_current_vals[sigIdx];
////        }
////    }
////    // Print out results to see if this worked
////    // First pack current values
////    printf("\t\t\tRWV\t\tSI\n");
////    for (uint8_t i = 0; i < 6; i++) {
////        printf("Index %i:\t\t%.2f\t\t%i\n", i,pack_current_vals[i],PackCurrent_Array[i]);
////    }
////    // Now the total_pack_curr variables...
////    printf("\nTotal Pack Current (float):\t\t%.2f\nTotal Pack Current (computed SI):\t%i\nTotal Pack Current (expected SI):\t%i\n",
////           total_pack_curr_float, total_pack_curr_filtered, conv_float_to_PackCurrent_T(total_pack_curr_float));
////
////    printf("\nExample first computation: (uint16_t)(33333U + 34053U):\t\t\t\t\t%i\n", (uint16_t)(33333U + 34053U));
////    printf("Example second part of computation: (uint16_t)(33333U + 34053U) - 33333U:\t\t%d\n", (uint16_t)(33333U + 34053U) - 33333U);
////    printf("Example last part of computation: (uint16_t)((uint16_t)(33333U + 34053U) - 33333U):\t%i\n", (uint16_t)((uint16_t)(33333U + 34053U) - 33333U));
//
//
//    return 0;
//}
//
//// PackCurrent_Standard_CAN_T is a fixed-point type with slope/bias of 0.06/-2000
//// Recall RWV = SI * slope + bias
////        SI  = (RWV - bias) / slope
//uint16_t conv_float_to_PackCurrent_T(float currentval) {
//    uint16_t PackCurrent_T_val = 0u;
//
//    PackCurrent_T_val = (uint16_t) ( (currentval - pack_current_bias) / pack_current_slope );
//
//    return PackCurrent_T_val;
//}
