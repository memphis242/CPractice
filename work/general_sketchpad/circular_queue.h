#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// The definition of our circular buffer structure
struct queue_t {
    uint8_t * buffer;	// user provided buffer holding the actual array
    size_t head;	// this holds the index of the oldest element
    size_t tail;	// this holds the index of the most recent element
    size_t max;	// of the buffer
    size_t counter;	// number of items in the queue
};

// Opaque circular buffer structure
typedef struct queue_t queue_t;
// Handle type, the way users interact with the API, so that they don't directly work with a pointer to a circular_buf_t structure
typedef queue_t * queue_handle_t;

// Initializes the queue --> involves having the user already statically allocate a queue structure
void queue_init(queue_handle_t me, uint8_t * buffer, size_t size);

// Reset the circular buffer to empty, head == tail
void queue_reset(queue_handle_t me);

// put version1 continues to add data to the queue even if the buffer is full
// Old data is overwritten
void queue_put(queue_handle_t me, uint8_t data);

// put version2 rejects new data if the buffer is full
// returns 0 on success, -1 if the buffer is full
int8_t queue_put_safe(queue_handle_t me, uint8_t data);

// Retrieve a value from the queue; user will pass in pointer to the data
// Returns 0 on success, -1 if the buffer is empty
int8_t queue_get(queue_handle_t me, uint8_t * data);

// Returns true if the buffer is empty
bool queue_empty(queue_handle_t me);

// Returns true if the buffer is full
bool queue_full(queue_handle_t me);

// Returns the maximum capacity of the queue
size_t queue_capacity(queue_handle_t me);

// Returns the current number of elements in the queue
size_t queue_num_of_elements(queue_handle_t me);

// For debugging
void print_queue(queue_handle_t me);


