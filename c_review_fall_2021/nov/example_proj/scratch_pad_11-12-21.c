////
//// Created by abdullah on 11/12/21.
////
//
//#include <stdio.h>
//#include <stdint.h>
//
//typedef struct {
//    uint16_t sid;   // bits 10:0 --> 0x000 to 0x7FF
//    uint8_t exide;    // 0 = standard, 1 = extended
//    uint32_t eid;   // bits 17:0 --> 0x00000 to 0x3FFFF
//    uint8_t rtr;    // 0 = data frame, 1 = remote frame (for J1939, rtr always = 0)
//} can_msg_arb_field;
//
//typedef struct {
//    uint8_t dlc;    // 4-bit to represent # of messages --> above 8 and this will need more logic...
//} can_msg_ctrl_field;
//
//typedef struct {
//    uint8_t data0;
//    uint8_t data1;
//    uint8_t data2;
//    uint8_t data3;
//    uint8_t data4;
//    uint8_t data5;
//    uint8_t data6;
//    uint8_t data7;
//} can_msg_data_field;   // Can also just use a uint8_t array of length 8
//
//typedef struct {
//    can_msg_arb_field arb_field;
//    can_msg_ctrl_field ctrl_field;
//    can_msg_data_field data_field;
//} can_msg;
//
//
//void main(void){
//
//    // Testing out my can_compose_msg_ext and can_parse_msg functions (they should be inverses of each other)
//    // Example CAN message
//    can_msg test_msg;
//    test_msg.arb_field.sid = 0x3E1u;
//    test_msg.arb_field.exide = 1u;
//    test_msg.arb_field.eid = 0x00ABCu;
//    test_msg.arb_field.rtr = 0u;
//    test_msg.ctrl_field.dlc = 0x08u;
//    test_msg.data_field.data0 = 0xAA;
//    test_msg.data_field.data1 = 0xBB;
//    test_msg.data_field.data2 = 0xCC;
//    test_msg.data_field.data3 = 0xDD;
//    test_msg.data_field.data4 = 0xEE;
//    test_msg.data_field.data5 = 0xFF;
//    test_msg.data_field.data6 = 0x00;
//    test_msg.data_field.data7 = 0x11;
//
//    // Original Message
//    printf("THE ORIGINAL MESSAGE:\n");
//    printf("Arbitration Field\n");
//    printf("SID: %03x\n", test_msg.arb_field.sid);
//    printf("EXIDE: %01x\n", test_msg.arb_field.exide);
//    printf("EID: %05x\n", test_msg.arb_field.eid);
//    printf("RTR: %01x\n", test_msg.arb_field.rtr);
//    printf("\nControl Field\n");
//    printf("DLC: %02x\n", test_msg.ctrl_field.dlc);
//    printf("\nData Fields\n");
//    printf("%02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x", test_msg.data_field.data0,
//           test_msg.data_field.data1, test_msg.data_field.data2, test_msg.data_field.data3, test_msg.data_field.data4,
//           test_msg.data_field.data5, test_msg.data_field.data6, test_msg.data_field.data7);
//
//    // struct --> buff...
//    can_msg * msg = &test_msg;
//    uint8_t mcp2515_tx_buf[13] = {0u};
//    mcp2515_tx_buf[0] = (msg->arb_field.sid & 0x07F8u) >> 3u;      // SID10:SID3
//    mcp2515_tx_buf[1] = ((msg->arb_field.sid & 0x0007u) << 5u) |   // SID2:SID0
//                        ((msg->arb_field.exide) << 3u)         |   // EXIDE
//                        ((msg->arb_field.eid & 0x30000) >> 16u);   // EID17:EID16
//    mcp2515_tx_buf[2] = (msg->arb_field.eid & 0x0FF00) >> 8u;      // EID15:EID8
//    mcp2515_tx_buf[3] = msg->arb_field.eid & 0x000FF;              // EID7:EID0
//    mcp2515_tx_buf[4] = (msg->arb_field.rtr << 6u)    |           // RTR
//                        (msg->ctrl_field.dlc);                     // DLC
//    mcp2515_tx_buf[5] = msg->data_field.data0;
//    mcp2515_tx_buf[6] = msg->data_field.data1;
//    mcp2515_tx_buf[7] = msg->data_field.data2;
//    mcp2515_tx_buf[8] = msg->data_field.data3;
//    mcp2515_tx_buf[9] = msg->data_field.data4;
//    mcp2515_tx_buf[10] = msg->data_field.data5;
//    mcp2515_tx_buf[11] = msg->data_field.data6;
//    mcp2515_tx_buf[12] = msg->data_field.data7;
//
//    // Print out and hope for the best
//    printf("\n\n\nSTRUCT --> BUFFER\n");
//    printf("The results:\t");
//    for(uint8_t i=0; i<13; i++){
//        printf("%02x  ", mcp2515_tx_buf[i]);
//    }
//
//    // Now going in reverse!
//    can_msg msg_inverted;
//    can_msg * inv_msg = &msg_inverted;
//    inv_msg->arb_field.sid = (((uint16_t) mcp2515_tx_buf[0]) << 3u) | (((uint16_t) mcp2515_tx_buf[1] & 0x00E0) >> 5u);
//    inv_msg->arb_field.exide = (mcp2515_tx_buf[1] & 0x08) >> 3u;
//    inv_msg->arb_field.eid = (((uint16_t) mcp2515_tx_buf[1] & 0x0003) << 16u)    |
//                         (((uint16_t) mcp2515_tx_buf[2]) << 8u)     |
//                         ((uint16_t) mcp2515_tx_buf[3]);
//    inv_msg->arb_field.rtr = (mcp2515_tx_buf[4] & 0x40) >> 6u;
//    inv_msg->ctrl_field.dlc = mcp2515_tx_buf[4] & 0x0F;
//    inv_msg->data_field.data0 = mcp2515_tx_buf[5];
//    inv_msg->data_field.data1 = mcp2515_tx_buf[6];
//    inv_msg->data_field.data2 = mcp2515_tx_buf[7];
//    inv_msg->data_field.data3 = mcp2515_tx_buf[8];
//    inv_msg->data_field.data4 = mcp2515_tx_buf[9];
//    inv_msg->data_field.data5 = mcp2515_tx_buf[10];
//    inv_msg->data_field.data6 = mcp2515_tx_buf[11];
//    inv_msg->data_field.data7 = mcp2515_tx_buf[12];
//
//    // Now print it out!
//    printf("\n\n\nBUFFER BACK TO STRUCT:\n");
//    printf("Arbitration Field\n");
//    printf("SID: %03x\n", inv_msg->arb_field.sid);
//    printf("EXIDE: %01x\n", inv_msg->arb_field.exide);
//    printf("EID: %05x\n", inv_msg->arb_field.eid);
//    printf("RTR: %01x\n", inv_msg->arb_field.rtr);
//    printf("\nControl Field\n");
//    printf("DLC: %02x\n", inv_msg->ctrl_field.dlc);
//    printf("\nData Fields\n");
//    printf("%02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x", inv_msg->data_field.data0,
//           inv_msg->data_field.data1, inv_msg->data_field.data2, inv_msg->data_field.data3, inv_msg->data_field.data4,
//           inv_msg->data_field.data5, inv_msg->data_field.data6, inv_msg->data_field.data7);
//
//
//
//
//}