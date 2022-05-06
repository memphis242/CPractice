#include <stdio.h>
#include "std_can_ds.h"


struct Std_CAN_Queue_Item_S example_msgs[10U] =
        {
                { 128U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 130U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 185U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 107U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 896U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 704U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 705U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 761U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 953U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
                { 1000U, { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }, NULL },
        };

void next_item(struct Std_CAN_Queue_Item_S example_item) {

    if (std_queue_initialzied()) {
        // Place message information into queue only if it is one of the relevant messages...
        UInt16_T message_id = example_item.identifier;
        UInt8_T hash_val = message_id % STD_QUEUE_HASH_NUM;
        if (RELEVANCY_HASH_TABLE[hash_val].relevancy_val == 1U &&
            RELEVANCY_HASH_TABLE[hash_val].intended_id == message_id) {
            // Construct Std_CAN_Queue_Item_S object to be placed into queue
            // Recall members are UInt16_T id and UInt8_T data[8]
            struct Std_CAN_Queue_Item_S new_item;
            new_item.identifier = message_id;    // Message id
            // Message data
            new_item.data[0] = example_item.data[0];
            new_item.data[1] = example_item.data[1];
            new_item.data[2] = example_item.data[2];
            new_item.data[3] = example_item.data[3];
            new_item.data[4] = example_item.data[4];
            new_item.data[5] = example_item.data[5];
            new_item.data[6] = example_item.data[6];
            new_item.data[7] = example_item.data[7];
            // Message callback function
            new_item.cb = RELEVANCY_HASH_TABLE[hash_val].cb;

            // Place into std_queue
            std_queue_put(&new_item);

        }

    }

}

int main() {

    std_queue_init();

//    next_item(example_msgs[0]);
//    next_item(example_msgs[1]);
//    next_item(example_msgs[2]);
//    next_item(example_msgs[3]);
//    next_item(example_msgs[4]);

    for ( uint16_t i=0; i<65000U; i++ ) {
        struct Std_CAN_Queue_Item_S item;
        item.identifier = i;
        next_item(item);
    }

    print_queue();

    print_relevant_ids();


    return 0;
}
