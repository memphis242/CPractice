////
////
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <string.h>
//
//
//typedef struct Battery {
//    float charge;
//} Battery;
//
//typedef struct Descriptor
//{
//    int id;
//    int name_length;
//    char *name;
//} Descriptor;
//
//void square(int * num);
//void charge(Battery * battery, float charge);
//int copy_bit(int src, int dst, int pos);
//void tile_edges(int * tiles, int width, int height);
//char * allocate_string(int length);
//int * init_range(int length);
//Descriptor * allocate_and_initialize_descriptor(int id, const char *name);
//void deallocate_descriptor(Descriptor *descriptor);
//
//void main(void){
//
////    // QUESTION 1
////    int i = 2;
////    int j = 3;
////
////    square(&i);
////    square(&j);
////
////    printf("%d\t%d\n", i, j);
//
////    // QUESTION 2
////    Battery battery = {0};
////    charge(&battery, 1.0f);
////    printf("%f", battery.charge);
//
////    // QUESTION 3
////    printf("Source: %d\nDestination: %d\nResult of copy_bit(7,12,0): %d\n", 7, 12, copy_bit(7,12,3));
//
////    // QUESTION 4
////    int width = 3, height = 3;
////    int * tiles = calloc(width * height, sizeof(int));
////    tile_edges(tiles, width, height);
////
////    printf("%d %d %d \n%d %d %d \n%d %d %d",
////           tiles[0], tiles[1], tiles[2],
////           tiles[3], tiles[4], tiles[5],
////           tiles[6], tiles[7], tiles[8]);
//
////    // QUESTION 5
////    // What are the correct implementations of the following function to allocate memory for a string of specified length?
////    allocate_string(5);
//
////    // QUESTION 6
////    int *range = init_range(6);
////    for (int i = 0; i < 6; i++) {
////        printf("%d ", range[i]);
////    }
//
////    // QUESTION 7
////    Descriptor *descriptor = allocate_and_initialize_descriptor(2, "File");
////    printf("Id: %d, name length: %d, name: %s", descriptor->id, descriptor->name_length, descriptor->name);
////    deallocate_descriptor(descriptor);
//
//    // QUESTION 8
//    /*
//     * We had numbers 318832606 (decimal), ... (some more numbers), 270859996 (decimal) stored in temporary memory.
//     * Depending on the type of computer system, what is the first byte of memory stored? (use hex representation)
//     *      LITTLE ENDIAN:
//     *      BIG ENDIAN:
//     *
//     * MY ANSWER
//     * So they gave four numbers, but since we're only talking about the first byte, we only really care about the
//     * first number (no matter what system type, objects will be stored in order of first --> last; what differs is
//     * how the individual bytes of a given object are stored). So that means 318832606. In hex, that is 0x13 00 FF DE.
//     * This is also a positive number, so we don't have to worry about a sign bit. So, for this first number, its
//     * MOST SIGNIFICANT BYTE is 13, and the LEAST SIGNIFICANT BYTE is DE. After that, it's easy. Little endian systems
//     * store least-significant-first, whereas big endian systems store most-significant-first. So, for little endian,
//     * the first byte stored is DE; for big endian, the first byte stored is 13.
//     */
//
//}
//
//void square(int * num){
//    *num *= *num;
//}
//
//void charge(Battery * battery, float charge){
//    battery->charge += charge;
//}
//
//int copy_bit(int src, int dst, int pos){
//    unsigned int bit_pos_mask = 0x01 << pos;
//    unsigned int src_bit = src & bit_pos_mask;
////    dst &= ~bit_pos_mask;
////    return (dst | src_bit);
//
//    int result = src_bit ? (dst | bit_pos_mask) : (dst & ~bit_pos_mask);
//    return result;
//}
//
//void tile_edges(int * tiles, int width, int height){
//    for(int i=0; i<height; i++){
//        for(int j=0; j<width; j++){
//
//            if(i==0 || i==(height-1) || j==0 || j==(width-1)){  // We are at top or bottom border or left border or right border
//                *(tiles + i*width + j) = 1;
//            } else {
//                *(tiles + i*width + j) = 0;
//            }
//
//        }
//    }
//}
//
//char * allocate_string(int length){
//    return malloc((length+1) * sizeof(char));
////    return calloc((length+1), sizeof(char));
////    return malloc()
//}
//
//int * init_range(int length) {
//    int * arr = (int *) malloc(length * sizeof(int));
//    // Ensure memory allocation was successfull...
//    if(arr == NULL){
//        printf("Unsuccessfull memory allocation!");
//        return NULL;
//    }
//
//    for(int i=0; i<length; i++){
//        arr[i] = i;
//    }
//    return arr;
//}
//
//Descriptor *allocate_and_initialize_descriptor(int id, const char *name)
//{
//    // Allocate memory for Descriptor struct using malloc()...
//    Descriptor * new_des_struct = (Descriptor *) malloc(sizeof(Descriptor));
//    int len_of_name = strlen(name);
//
//    // Assign component values of struct
//    new_des_struct->id = id;
//    new_des_struct->name_length = len_of_name;
//    new_des_struct->name = (char *) malloc((len_of_name + 1) * sizeof(char));
//    strcpy(new_des_struct->name, name);
//
//    return new_des_struct;
//}
//
//void deallocate_descriptor(Descriptor *descriptor)
//{
//    free(descriptor->name);
//    free(descriptor);
//}