#include <stdio.h>
#include <stdint.h>

#define INVALID_TEMP        0xFFFFu
#define VALID_TEMP(T)       ( ( (T) != 0u) && ( (T) != INVALID_TEMP) )    // Temperature validity check macro; I am assuming values of 0u and 0xFFFFu are invalid values
#define DATA_GOODDATA       (-1)
#define DATA_NOTAVAILABLE   (31)
#define RWV_TO_SI_TEMP_INPUT(rwv)     ( (uint16_t) ( ( rwv + 273 ) * 32 ) )
#define RWV_TO_SI_TEMP_OUTPUT(rwv)    ( (uint16_t) ( rwv + 40 ) )

#define INLET_COOLANT_TEMP_VALUE    _vars[CAN_HVESSIntCoolantTemp].value
#define INLET_COOLANT_TEMP_STATUS   _vars[CAN_HVESSIntCoolantTemp].status
#define OUTLET_COOLANT_TEMP_VALUE    _vars[CAN_HVESSOutletCoolantTemp].value
#define OUTLET_COOLANT_TEMP_STATUS   _vars[CAN_HVESSOutletCoolantTemp].status

#define SET_TEMP_ARRAYS(val) {                                          \
                                   CoolantTempInlet_Array[0] = val;     \
                                   CoolantTempInlet_Array[1] = val;     \
                                   CoolantTempInlet_Array[2] = val;     \
                                   CoolantTempOutlet_Array[0] = val;    \
                                   CoolantTempOutlet_Array[1] = val;    \
                                   CoolantTempOutlet_Array[2] = val;    \
                             }

typedef uint16_t JD_VARMNGR_OBJ;
typedef int16_t Status_T;
typedef uint8_t UInt8_T;
typedef uint16_t UInt16_T;
typedef int16_t SInt16_T;
typedef uint32_t UInt32_T;

enum CAN_VARS_E
{
    CAN_HVESSIntCoolantTemp,
    CAN_HVESSOutletCoolantTemp,
    NUM_OF_CAN_VARS
};

struct SYSTEMVARIABLE_S
{
    JD_VARMNGR_OBJ value;
    Status_T status;
};
typedef struct SYSTEMVARIABLE_S SYSTEMVARIABLE_T;
                   


// Global Variables
struct SYSTEMVARIABLE_S _vars[NUM_OF_CAN_VARS];


// Static variables
static uint16_t CoolantTempInlet_Array[] = { INVALID_TEMP, INVALID_TEMP, INVALID_TEMP };
static uint16_t CoolantTempOutlet_Array[] = { INVALID_TEMP, INVALID_TEMP, INVALID_TEMP };

static void Compute_CoolantTemps(void);
static void JD_WriteVar(enum CAN_VARS_E can_var, SYSTEMVARIABLE_T * var);




int main(void) {

    // Let's unit test my coolant temp function!
    printf("\n\nSTARTING UNIT TEST OF Compute_CoolantTemps FUNCTION\n");
    printf("----------------------------------------------------\n\n");
    
    // First test invalid values...
    // First set will be INVALID_TEMP, which is what the arrays are initialized to already
    printf("\nChecking INVALID_TEMP input...");
    Compute_CoolantTemps();
    if ( INLET_COOLANT_TEMP_VALUE != INVALID_TEMP || OUTLET_COOLANT_TEMP_VALUE != INVALID_TEMP )
    {
        printf("\tFAIL at INVALID_TEMP input!\n");
    }
    else
    {
        printf("\tPASS :D\n");
    }

    // Now checking for input of 0
    printf("\nChecking 0 input...");
    SET_TEMP_ARRAYS(0);
    Compute_CoolantTemps();
    if ( INLET_COOLANT_TEMP_VALUE != INVALID_TEMP || OUTLET_COOLANT_TEMP_VALUE != INVALID_TEMP )
    {
        printf("\tFAIL at 0 input!\n");
    }
    else
    {
        printf("\tPASS :D\n");
    }

    // Now checking for correct averaging...
    // First, set all values the same way and see; we'll try three different values
    printf("\nChecking 23C input...");
    SET_TEMP_ARRAYS( RWV_TO_SI_TEMP_INPUT(23) );
    Compute_CoolantTemps();
    if ( INLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(23) || OUTLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(23) )
    {
        printf("\tFAIL at 23C input!\n");
    }
    else
    {
        printf("\tPASS :D\n");
    }
    printf("\nChecking -40C input...");
    SET_TEMP_ARRAYS( RWV_TO_SI_TEMP_INPUT(-40) );
    Compute_CoolantTemps();
    if ( INLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(-40) || OUTLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(-40) )
    {
        printf("\tFAIL at -40C input!\n");
    }
    else
    {
        printf("\tPASS :D\n");
    }
    printf("\nChecking 70C input...");
    SET_TEMP_ARRAYS( RWV_TO_SI_TEMP_INPUT(70) );
    Compute_CoolantTemps();
    if ( INLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(70) || OUTLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(70) )
    {
        printf("\tFAIL at 70C input!\n");
    }
    else
    {
        printf("\tPASS :D\n");
    }

    // Okay, now check for uneven input values...
    printf("\nChecking uneven input...");
    CoolantTempInlet_Array[0] = RWV_TO_SI_TEMP_INPUT(27);
    CoolantTempInlet_Array[1] = RWV_TO_SI_TEMP_INPUT(25);
    CoolantTempInlet_Array[2] = RWV_TO_SI_TEMP_INPUT(28);
    CoolantTempOutlet_Array[0] = RWV_TO_SI_TEMP_INPUT(20);
    CoolantTempOutlet_Array[1] = RWV_TO_SI_TEMP_INPUT(22);
    CoolantTempOutlet_Array[2] = RWV_TO_SI_TEMP_INPUT(19);
    Compute_CoolantTemps();
    if ( INLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(26) || OUTLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(20) )
    {
        printf("\tFAIL at uneven input!\n");
    }
    else
    {
        printf("\tPASS :D\n");
    }

    printf("\nChecking uneven input with one invalid value...");
    CoolantTempInlet_Array[0] = RWV_TO_SI_TEMP_INPUT(29);
    CoolantTempInlet_Array[1] = RWV_TO_SI_TEMP_INPUT(25);
    CoolantTempInlet_Array[2] = INVALID_TEMP;
    CoolantTempOutlet_Array[0] = RWV_TO_SI_TEMP_INPUT(20);
    CoolantTempOutlet_Array[1] = RWV_TO_SI_TEMP_INPUT(22);
    CoolantTempOutlet_Array[2] = INVALID_TEMP;
    Compute_CoolantTemps();
    if ( INLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(27) || OUTLET_COOLANT_TEMP_VALUE != RWV_TO_SI_TEMP_OUTPUT(21) )
    {
        printf("\tFAIL at uneven input with one invalid value!\n");
    }
    else
    {
        printf("\tPASS :D\n");
    }


    return 0;
}



static void JD_WriteVar(enum CAN_VARS_E can_var, SYSTEMVARIABLE_T * var)
{
    if ( can_var < NUM_OF_CAN_VARS )
    {
        _vars[can_var] = *var;
    }
}


static void Compute_CoolantTemps(void)
{
    SYSTEMVARIABLE_T inlet_temp = {INVALID_TEMP, DATA_NOTAVAILABLE}, outlet_temp = {INVALID_TEMP, DATA_NOTAVAILABLE};
    UInt16_T inlet1 = INVALID_TEMP, inlet2 = INVALID_TEMP, inlet3 = INVALID_TEMP;
    UInt16_T outlet1 = INVALID_TEMP, outlet2 = INVALID_TEMP, outlet3 = INVALID_TEMP;
    UInt8_T validity_count = 0u;
    UInt32_T cumulative_sum = 0u;

    // Coming in from Romeo batteries: Scale: 0.03125, Offset: -273
    // Going out over CAN: Scale: 1, Offset: -40
    // (same units --> Celsius)
    // To convert, SIcan = SIbat / 32 - 233
    // Also, we are going with the Average Coolant Temperature measurement
    // I will first convert all types to the output CAN type IF VALID then handle the averaging
    if ( VALID_TEMP(CoolantTempInlet_Array[0]) )
    {
        inlet1 = (UInt16_T) ( (SInt16_T)( CoolantTempInlet_Array[0] >> 5 ) - 233 );
    }
    if ( VALID_TEMP(CoolantTempInlet_Array[1]) )
    {
        inlet2 = (UInt16_T) ( (SInt16_T)( CoolantTempInlet_Array[1] >> 5 ) - 233 );
    }
    if ( VALID_TEMP(CoolantTempInlet_Array[2]) )
    {
        inlet3 = (UInt16_T) ( (SInt16_T)( CoolantTempInlet_Array[2] >> 5 ) - 233 );
    }
    if ( VALID_TEMP(CoolantTempOutlet_Array[0]) )
    {
        outlet1 = (UInt16_T) ( (SInt16_T)( CoolantTempOutlet_Array[0] >> 5 ) - 233 );
    }
    if ( VALID_TEMP(CoolantTempOutlet_Array[1]) )
    {
        outlet2 = (UInt16_T) ( (SInt16_T)( CoolantTempOutlet_Array[1] >> 5 ) - 233 );
    }
    if ( VALID_TEMP(CoolantTempOutlet_Array[2]) )
    {
        outlet3 = (UInt16_T) ( (SInt16_T)( CoolantTempOutlet_Array[2] >> 5 ) - 233 );
    }

    // Now take the average.
    // Only average over valid values.
    // NOTE! I'm not worried about overflow because 32 bits is more than enough to
    //       hold the sum of three 16 bit integers, and the division afterwards is
    //       guaranteed to bring the result to a 16-bit value.
    // We'll start with the inlet temperature.
    if ( inlet1 != INVALID_TEMP )
    {
        cumulative_sum += inlet1; validity_count++;
    }
    if ( inlet2 != INVALID_TEMP )
    {
        cumulative_sum += inlet2; validity_count++;
    }
    if ( inlet3 != INVALID_TEMP )
    {
        cumulative_sum += inlet3; validity_count++;
    }
    if ( validity_count > 0 )
    {
        inlet_temp.value = (UInt16_T) ( cumulative_sum / validity_count );
        inlet_temp.status = DATA_GOODDATA;
    }
    // Otherwise, inlet_temp stays at INVALID_TEMP value

    // Now the outlet temps
    cumulative_sum = 0; validity_count = 0u;    // Reset cumulative sum and validity counter
    if ( outlet1 != INVALID_TEMP )
    {
        cumulative_sum += outlet1; validity_count++;
    }
    if ( outlet2 != INVALID_TEMP )
    {
        cumulative_sum += outlet2; validity_count++;
    }
    if ( outlet3 != INVALID_TEMP )
    {
        cumulative_sum += outlet3; validity_count++;
    }
    if ( validity_count > 0 )
    {
        outlet_temp.value = (UInt16_T) ( cumulative_sum / validity_count );
        outlet_temp.status = DATA_GOODDATA;
    }

    // Write to CAN vars
    // TODO: Passing pointer to variables on the stack... Dangerous if not careful!
    JD_WriteVar(CAN_HVESSIntCoolantTemp, &inlet_temp);
    JD_WriteVar(CAN_HVESSOutletCoolantTemp, &outlet_temp);
}




// ************************************************************
//uint16_t assembly_current_limit1;
//uint16_t assembly_current_limit2;
//uint16_t power_limit;
//
//assembly_current_limit1 = (uint16_t) ( ( ( (int32_t) current_limit1 * num_of_packs ) + (32000L * (1L - ((int32_t)num_of_packs) )) ) );
//assembly_current_limit2 = (uint16_t) ( ( ( (int32_t) current_limit2 * num_of_packs ) + (32000L * (1L - ((int32_t)num_of_packs) )) ) );
//
//printf("Current Limit 1:\t\t%.2f\nCurrent Limit 2:\t\t%.2f\n\n", ((float)current_limit1 * 0.05 - 1600.0), ((float)current_limit2 * 0.05 - 1600.0));
//printf("Assembly Limit 1:\t\t%.2f\nAssembly Limit 2:\t\t%.2f\n\n", ((float)assembly_current_limit1 * 0.05 - 1600.0), ((float)assembly_current_limit2 * 0.05 - 1600.0));
//
//// Now let's try the power calc
//power_limit = (uint16_t) ( ((uint32_t)(dc_bus_voltage / 20)) * ((uint32_t)((((int32_t)current_limit3) / 20) - 1600) ) / 50);
//printf("DC Bus Voltage (V):\t\t%.2f\nCurrent Limit (A):\t\t%.2f\n", ((float)dc_bus_voltage * 0.05), ((float)current_limit3 * 0.05 - 1600.0));
//printf("Power Limit (kW):\t\t%.2f\n\n", ((float)power_limit * 0.05));
//
//// Debugging
//uint32_t val1 = ((uint32_t)(dc_bus_voltage / 20));
//uint32_t val2 = ((uint32_t)(((int32_t)current_limit3) / 20) - 1600);
//uint32_t val3 = val1 * val2;
//uint32_t val4 = val3 / 50;
//uint16_t val5 = (uint16_t) val4;

// ***********************************************************************

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
