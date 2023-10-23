#include <stdio.h>
#include <stdint.h>

// Testing method of verifying array parameter size...
struct Data_S
{
    uint8_t data[8];
};

static uint8_t AccessMyArray_UsingPointerToPrimitive( const uint8_t * data_ptr );
static uint8_t AccessMyArray_UsingPointerToStruct( const struct Data_S * data_ptr );

static const uint8_t Example[] = {0, 1, 2};
static const uint8_t Example2[2] = {0, 1, 2};

int main(void)
{
    uint8_t data[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    struct Data_S data_struct;

    for ( uint8_t i=0; i<12; i++ )
    {
        data_struct.data[i] = data[i];
    }

    data[10] = 0;
    data_struct.data[10] = 0;

    printf("%d", AccessMyArray_UsingPointerToStruct( &data_struct ) );
    printf("%d", AccessMyArray_UsingPointerToPrimitive( data ) );

    return 0;
}


static uint8_t AccessMyArray_UsingPointerToPrimitive( const uint8_t * data_ptr )
{
    return data_ptr[20];    // Intentionally obvious out-of-bounds array access
}

static uint8_t AccessMyArray_UsingPointerToStruct( const struct Data_S * data_ptr )
{
    return data_ptr->data[20];    // Intentionally obvious out-of-bounds array access
}
