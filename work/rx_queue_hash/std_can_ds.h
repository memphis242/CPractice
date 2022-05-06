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

#ifndef STDCANDS_H_
#define STDCANDS_H_


/** Include Files **/
#include <stdint.h>


/** Local Definitions **/
typedef uint8_t UInt8_T;
typedef uint16_t UInt16_T;

#define MOARH_IDE_BIT           0x2000U
#define MOARH_IDE_BIT_STD       0x0U
#define MOARH_IDE_BIT_EXT       0x2000U

#define IS_STD_MESSAGE(MSG_OBJ_PTR)             ((MSG_OBJ_PTR->MOARH & MOARH_IDE_BIT) == MOARH_IDE_BIT_STD)
#define EXTRACT_STD_ID(MSG_OBJ_PTR)             ( (MSG_OBJ_PTR->MOARH & 0x1FFFU) >> 2u )
#define MOCTRL_CLEAR_NEWDAT_BIT(MSG_OBJ_PTR)    ( MSG_OBJ_PTR->MOCTRL = MO_CTRL_NEWDAT )    // Bit is cleared by setting the corresponding bit in the CTRL register
#define WAS_MESSAGE_LOST_PRIOR(MSG_OBJ_PTR)     ( MSG_OBJ_PTR->MOSTATL & MO_CTRL_MSG_LST )
#define MOCTRL_CLEAR_MSGLST_BIT(MSG_OBJ_PTR)    ( MSG_OBJ_PTR->MOCTRL = MO_CTRL_MSG_LST )   // Bit is cleared by setting the corresponding bit in the CTRL register


#define MAX_NUM_OF_PACKS_ROMEO              (3)
#define NUM_OF_RELEVANT_MSGS_RX             (8 * MAX_NUM_OF_PACKS_ROMEO)    // For the external master model --> later on, need to abstract away this from Romeo-specific 11-bit comms
#define NUM_OF_RELEVANT_PARAMETERS_RX       (15 * MAX_NUM_OF_PACKS_ROMEO)   // For the external master model --> later on, need to abstract away this from Romeo-specific 11-bit comms
#define MAX_NUM_OF_MSGS_PER_SEC             (12)  // The data rate of all messages, except isolation status, is 100ms, so I'll just allow in for a couple more for an extra buffer
#define STD_QUEUE_SIZE                      NUM_OF_RELEVANT_MSGS_RX *  MAX_NUM_OF_MSGS_PER_SEC // I want to be able to hold 1s worth of RELEVANT data, so my estimate would be: ~288

#define STD_QUEUE_HASH_NUM                  57      // To get this number, I wrote a script that basically tries out a bunch of numbers for use with the modulo hash function against
// the set of IDs I care about, and picked the smallest number that resulted in 0 collisions against this set. NOTE, there are
// still potentially collisions with other IDs that make up the universe of possible standard IDs, but I handle these collisions
// by having the relevancy hash table consist of the relevancy value, the ID that was supposed to map to that table entry, and
// then a callback function pointer. Neat solution if you ask me!

struct Std_CAN_Queue_Item_S {
    UInt16_T identifier;
    UInt8_T data[8];
    void (* cb)(struct Std_CAN_Queue_Item_S * item);    // Callback function for the particular item with void return type that accepts a queue item object
};

struct Std_CAN_Queue_S {
    struct Std_CAN_Queue_Item_S * buff;
    UInt16_T head;
    UInt16_T tail;
    UInt16_T max_size;
    UInt16_T counter;
    UInt8_T initialized;    // member to say whether or not the standard CAN queue has been initialized yet or not --> 0 = NOT_INITIALIZED, 1 = INITIALIZED
};

struct Relevancy_Table_Item {
    UInt8_T relevancy_val;  // either a 0 or a 1, with 1 being relevant
    UInt16_T intended_id;   // this is how I deal with collisions --> I check against the intended ID at this location
    void (* cb)(struct Std_CAN_Queue_Item_S * item);    // the callback function to be used with this intended_id
};

#ifndef RELEVANCY_HASH_TABLE_
extern const struct Relevancy_Table_Item RELEVANCY_HASH_TABLE[STD_QUEUE_HASH_NUM];
#endif  /* RELEVANCY_HASH_TABLE_ */


/** Public Functions **/

void std_queue_init(void);

void std_queue_reset(void);

void std_queue_put(struct Std_CAN_Queue_Item_S * item);

UInt8_T std_queue_put_safe(struct Std_CAN_Queue_Item_S * item);

UInt8_T std_queue_get(struct Std_CAN_Queue_Item_S * item);

UInt8_T std_queue_empty(void);

UInt8_T std_queue_full(void);

UInt8_T std_queue_initialzied(void);

UInt8_T std_queue_id_relevant(UInt16_T id);

void print_queue(void);

void print_relevant_ids(void);

/** Public Data **/


/** External Functions **/


/** External Data **/


/**************** Module Level Information *************************/


/** Private Function Prototypes **/



/** Private Data **/


/** Module Level Code **/



#endif // STDCANDS_H_

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