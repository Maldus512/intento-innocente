#include "digin.h"
#include "hardwareprofile.h"
#include "gel/debounce/debounce.h"


static debounce_filter_t filter;


void digin_init(void)
{
    INPUT1_TRIS=TRIS_INPUT;
    INPUT2_TRIS=TRIS_INPUT;
    INPUT3_TRIS=TRIS_INPUT;
    INPUT4_TRIS=TRIS_INPUT;
    INPUT5_TRIS=TRIS_INPUT;
    INPUT6_TRIS=TRIS_INPUT;
    INPUT7_TRIS=TRIS_INPUT;
    INPUT8_TRIS=TRIS_INPUT;
    INPUT9_TRIS=TRIS_INPUT;
    INPUT10_TRIS=TRIS_INPUT;
    INPUT11_TRIS=TRIS_INPUT;
    INPUT12_TRIS=TRIS_INPUT;
    
    debounce_filter_init(&filter);
}


int digin_get(digin_t digin)
{
   return debounce_read(&filter, digin);
}


int digin_take_reading(void)
{
    unsigned int input=0;
    
    input|=!INPUT1_PORT;
    input|=(!INPUT2_PORT)<<1;
    input|=(!INPUT3_PORT)<<2;
    input|=(!INPUT4_PORT)<<3;
    input|=(!INPUT5_PORT)<<4;
    input|=(!INPUT6_PORT)<<5;
    input|=(!INPUT7_PORT)<<6;
    input|=(!INPUT8_PORT)<<7;
    input|=(!INPUT9_PORT)<<8;
    input|=(!INPUT10_PORT)<<9;
    input|=(!INPUT11_PORT)<<10;
    input|=(!INPUT12_PORT)<<11;
    
    return debounce_filter(&filter, input, 1);
}



int digin_reading(void)
{
    unsigned int input=0;
    
    input|=!INPUT1_PORT;
    input|=(!INPUT2_PORT)<<1;
    input|=(!INPUT3_PORT)<<2;
    input|=(!INPUT4_PORT)<<3;
    input|=(!INPUT5_PORT)<<4;
    input|=(!INPUT6_PORT)<<5;
    input|=(!INPUT7_PORT)<<6;
    input|=(!INPUT8_PORT)<<7;
    input|=(!INPUT9_PORT)<<8;
    input|=(!INPUT10_PORT)<<9;
    input|=(!INPUT11_PORT)<<10;
    input|=(!INPUT12_PORT)<<11;
    
    //return debounce_filter(&filter, input, 1);
    
    return input;
}



unsigned int digin_get_inputs(void)
{
    return debounce_value(&filter);
}
