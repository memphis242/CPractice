#include "circular_queue.h"

#define RESET_VALUE   0u

// User provides struct
void queue_init(queue_handle_t me, uint8_t * buffer, size_t size) {
	
	me->buffer = buffer;
	me->max = size;
	queue_reset(me);
	
	return;
}

void queue_reset(queue_handle_t me) {
	
	me->head = 0u;
	me->tail = 0u;
	me->counter = 0u;
	
	return;
}

bool queue_full(queue_handle_t me) {
	
	return (me->counter == me->max);
}

bool queue_empty(queue_handle_t me){
	
	return (me->counter == 0u);
}

size_t queue_capacity(queue_handle_t me){
	
	return me->max;
}

size_t queue_num_of_elements(queue_handle_t me){
	
	return me->counter;
}

// Allows overwriting of previous data
void queue_put(queue_handle_t me, uint8_t data) {
	
	me->buffer[me->tail++] = data;
	me->tail %= me->max;
	if(!queue_full(me)) me->counter++;
	
	return;
}

int8_t queue_get(queue_handle_t me, uint8_t * data){
	
	int8_t r = -1;
	if(!queue_empty(me)) {
		*data = me->buffer[me->head];
        me->buffer[me->head++] = RESET_VALUE;
		me->head %= me->max;
		me->counter--;
		r = 0;
	}
	
	return r;
}

void print_queue(queue_handle_t me){

    printf("\nQueue: ");
    for(size_t i=0; i<me->max; i++) {
        if (i==me->head) printf("   |HEAD->|");
        else if(i==me->tail) printf("|<-TAIL|   ");
        printf("%d ", me->buffer[i]);
    }
    printf("\nNumber of Items in Queue:\t%i\n", me->counter);
    printf("Queue Head:\t%d\nQueue Tail:\t%d\nQueue Full?\t%d\nQueue Empty?\t%d\n", me->head, me->tail, queue_full(me),
           queue_empty(me));

    return;
}


