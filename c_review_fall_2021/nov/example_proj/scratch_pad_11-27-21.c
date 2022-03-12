//
// Created by abdullah on 11/27/21.
//


#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint16_t sid;   // bits 10:0 --> 0x000 to 0x7FF
    uint8_t exide;    // 0 = standard, 1 = extended
    uint32_t eid;   // bits 17:0 --> 0x00000 to 0x3FFFF
    uint8_t rtr;    // 0 = data frame, 1 = remote frame (for J1939, rtr always = 0)
} can_msg_arb_field;

typedef struct {
    uint8_t dlc;    // 4-bit to represent # of messages --> above 8 and this will need more logic...
} can_msg_ctrl_field;

typedef struct {
    uint8_t data0;
    uint8_t data1;
    uint8_t data2;
    uint8_t data3;
    uint8_t data4;
    uint8_t data5;
    uint8_t data6;
    uint8_t data7;
} can_msg_data_field;   // Can also just use a uint8_t array of length 8

typedef struct {
    can_msg_arb_field arb_field;
    can_msg_ctrl_field ctrl_field;
    can_msg_data_field data_field;
} can_msg;


const can_msg ack_msg = {
        .arb_field = { .sid = 0xFEAEu, .exide = 1u, .eid = 0x3111Fu, .rtr = 0u },
        .ctrl_field = { .dlc = 8u },
        .data_field = { .data0 = 0xFAu }
};



void main(void){


    // Print out ack_msg to check I initialized it correctly
    printf("\nACK_MSG STRUCT:\n\n");
    printf("Arbitration Field\n");
    printf("SID: %03x\n", ack_msg.arb_field.sid);
    printf("EXIDE: %01x\n", ack_msg.arb_field.exide);
    printf("EID: %05x\n", ack_msg.arb_field.eid);
    printf("RTR: %01x\n", ack_msg.arb_field.rtr);
    printf("\nControl Field\n");
    printf("DLC: %02x\n", ack_msg.ctrl_field.dlc);
    printf("\nData Fields\n");
    printf("%02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x", ack_msg.data_field.data0,
           ack_msg.data_field.data1, ack_msg.data_field.data2, ack_msg.data_field.data3, ack_msg.data_field.data4,
           ack_msg.data_field.data5, ack_msg.data_field.data6, ack_msg.data_field.data7);

}