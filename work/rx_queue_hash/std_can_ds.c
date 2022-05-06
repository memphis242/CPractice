//
// Created by abdullah on 05/05/22.
//

//-HEADER
/*******************************************************************
 *
 * DESCRIPTION: This module contains the header information used
 * lay out the data structures used for operating on the 11-bit CAN bus.
 *
 * NOTES:
 *
 *******************************************************************/
//~HEADER
//-COPYRIGHT
/** Start of File Copyright ****************************************
 *
 * Copyright (c) Deere & Company as an unpublished work
 * THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
 * DEERE & COMPANY.  ALL USE, DISCLOSURE, AND/OR
 * REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
 * DEERE & COMPANY IS PROHIBITED.
 *
 *******************************************************************/
//~COPYRIGHT

/** Include Files **/
#define RELEVANCY_HASH_TABLE_
#include "std_can_ds.h"
#include "callbacks.h"
#include <stdio.h>


/** Local Definitions **/
// Declare and initialize the standard CAN receive queue you will be using along with its underlying buffer
static struct Std_CAN_Queue_Item_S StdQueueRxBuffer[STD_QUEUE_SIZE];
static struct Std_CAN_Queue_S StdQueue;
// This table holds the list of relevant standard identifiers
// The idea will be to use this as a filter and to only allow a message to be placed
// on the standard CAN queue if the message id is one of those listed in this table
const static UInt16_T RELEVANT_ID_TABLE[NUM_OF_RELEVANT_MSGS_RX] =
        {
                128U, 129U, 130U,
                160U, 161U, 162U,
                288U, 289U, 290U,
                352U, 353U, 354U,
                448U, 449U, 450U,
                608U, 609U, 610U,
                704U, 705U, 706U,
                896U, 897U, 898U
        };
#define RELEVANT_ID_TABLE_MID_INDEX     (NUM_OF_RELEVANT_MSGS_RX / 2)
#define RELEVANT_ID_TABLE_MAX_INDEX     (NUM_OF_RELEVANT_MSGS_RX - 1)

// Dedefine relevancy (hash) table! In order to be accessed in other files, just include the CAN_StandardCAN_DS.h file
/* Recall Relevancy_Table_Item struct has:
 *      - UInt8_T relevancy_val
 *      - UInt16_T intended_id
 *      - void (* cb)(struct Std_CAN_Queue_Item_S * item)
 */
const struct Relevancy_Table_Item RELEVANCY_HASH_TABLE[STD_QUEUE_HASH_NUM] =
        {
                { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL },
                { 1U, 288U, CellVoltage_Callback }, { 1U, 289U, CellVoltage_Callback }, { 1U, 290U, CellVoltage_Callback }, // min/max cell voltages
                { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL },
                { 1U, 352U, DynamicMaxCurrentLimit_Callback }, { 1U, 353U, DynamicMaxCurrentLimit_Callback }, { 1U, 354U, DynamicMaxCurrentLimit_Callback }, // dynamic current limits
                { 0U, 0U, NULL },
                { 1U, 128U, PackVoltageCurrent_Callback }, { 1U, 129U, PackVoltageCurrent_Callback }, { 1U, 130U, PackVoltageCurrent_Callback }, // pack voltage and currents
                { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL },
                { 1U, 704U, StressEstimator_Callback }, { 1U, 705U, StressEstimator_Callback }, { 1U, 706U, StressEstimator_Callback }, // charge/discharge stress estimators
                { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL },
                { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL },
                { 1U, 608U, CellTemp_Callback }, { 1U, 609U, CellTemp_Callback }, { 1U, 610U, CellTemp_Callback }, // min/max cell temps
                { 1U, 896U, SOC_Callback }, { 1U, 897U, SOC_Callback }, { 1U, 898U, SOC_Callback }, // true soc
                { 0U, 0U, NULL }, { 0U, 0U, NULL },
                { 1U, 160U, BMSContactorState_Callback }, { 1U, 161U, BMSContactorState_Callback }, { 1U, 162U, BMSContactorState_Callback }, // bms state and contactor status
                { 1U, 448U, IsolationStatus_Callback }, { 1U, 449U, IsolationStatus_Callback }, { 1U, 450U, IsolationStatus_Callback }, // isolation status
                { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }, { 0U, 0U, NULL }
        };


/** Public Functions **/
void std_queue_init(void) {

    StdQueue.buff= StdQueueRxBuffer;
    StdQueue.head = 0u;
    StdQueue.tail = 0u;
    StdQueue.max_size = STD_QUEUE_SIZE;
    StdQueue.counter = 0u;
    StdQueue.initialized = 1u;

    return;
}

void std_queue_put(struct Std_CAN_Queue_Item_S * item) {

    // Place item in queue at head and increment head index, account for wrap-around
    StdQueue.buff[StdQueue.head++] = *item;
    StdQueue.head %= STD_QUEUE_SIZE;

    // Increment counter to keep track of how much is in the queue --> if the queue is full, stop incrementing counter
    if ( !std_queue_full() ) StdQueue.counter++;

    return;
}

//SInt8_T std_queue_put_safe(struct Std_CAN_Queue_S * queue_handle, struct Std_CAN_Queue_Item_S * item);

UInt8_T std_queue_get(struct Std_CAN_Queue_Item_S * item) {

    UInt8_T r = 0u;
    if ( !std_queue_empty() ) {
        *item = StdQueue.buff[StdQueue.tail++];
        StdQueue.tail %= STD_QUEUE_SIZE;
        StdQueue.counter--;
        r = 1u;
    }

    return r;
}

UInt8_T std_queue_empty(void) {

    return StdQueue.counter == 0u;
}

UInt8_T std_queue_full(void) {

    return StdQueue.counter == STD_QUEUE_SIZE;
}

UInt8_T std_queue_initialzied(void) {

    return StdQueue.initialized;
}

// Instead of the hash table approach, this can be used to just check
// if a given ID is relevant to us or not --> note that hash table approach
// is faster and I might actually just replace this function with a hash table one...
UInt8_T std_queue_id_relevant_binsearch(UInt16_T id) {

    UInt8_T relevancy_val = 0u;

    // Perform the hash function on the id
    // FOR NOW, DON'T HAVE A GOOD HASH FUNCTION SO WILL USE TABLE INSTEAD
    // Return the relevancy value the corresponded to this id

    // Utilizing the RELEVANT_ID_TABLE... perform a binary search
    // Go into search if value is within range of table, assuming table is sorted least to greatest
    if ( id >= RELEVANT_ID_TABLE[0u] && id <= RELEVANT_ID_TABLE[RELEVANT_ID_TABLE_MAX_INDEX] ) {

        UInt8_T check_range_left = 0u;
        UInt8_T check_range_right = RELEVANT_ID_TABLE_MAX_INDEX;
        UInt8_T check_index = (check_range_right + check_range_left) >> 1u;

        // As long as the check range has a width greater than 1, keep searching
        while( (check_range_right - check_range_left) > 0u ) {

            // If we get an ID match...
            if ( id == RELEVANT_ID_TABLE[check_index] ) {
                relevancy_val = 1u;
                break;

                // Otherwise, update the check range and index
            } else if ( id > RELEVANT_ID_TABLE[check_index] ) {
                // To cover the corner case of the ID passed being in between the right-most index and the one before it...
                if ( check_range_left == (check_range_right - 1u) ) {
                    relevancy_val = (id == RELEVANT_ID_TABLE[check_range_right]);   // we will now check definitively index
                    break;
                } else {
                    check_range_left = check_index;
                }

            } else {
                check_range_right = check_index;
            }

            check_index = (check_range_right + check_range_left) >> 1u;

        }

    }

    return relevancy_val;
}


void print_queue(void) {

    printf("\n");
    for ( uint8_t i=0u; i<StdQueue.counter; i++ ) {
        printf("%d   ", StdQueue.buff[i].identifier);
    }
    printf("\n");

    return;
}

void print_relevant_ids(void)
{
    printf("\n");
    for ( uint8_t i=0; i<NUM_OF_RELEVANT_MSGS_RX; i++ )
    {
        printf("%d   ", RELEVANT_ID_TABLE[i]);
    }
    printf("\n");

    return;
}



/** Public Data **/


/** External Functions **/


/** External Data **/


/**************** Module Level Information *************************/


/** Private Function Prototypes **/



/** Private Data **/


/** Module Level Code **/


//-COPYRIGHT
/** End of File Copyright ******************************************
 *
 * Copyright (c) Deere & Company as an unpublished work
 * THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
 * DEERE & COMPANY.  ALL USE, DISCLOSURE, AND/OR
 * REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
 * DEERE & COMPANY IS PROHIBITED.
 *
 *******************************************************************/
//~COPYRIGHT