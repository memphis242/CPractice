#include <stdio.h>
#include <stdint.h>

// Testing method of verifying array parameter size...
struct Data_S
{
    uint8_t data[8];
};

static size_t LengthOfData( const struct Data_S * data_ptr );

int main(void)
{
    uint8_t data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    struct Data_S data_struct;

    for ( uint8_t i=0; i<8; i++ )
    {
        data_struct.data[i] = data[i];
    }

    printf( "Length of my data array: %d\n", LengthOfData(&data_struct) );

    return 0;
}


static size_t LengthOfData( const struct Data_S * data_ptr )
{
    return sizeof( *data_ptr );
}