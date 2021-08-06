#ifndef DIPSWITCH_H_INCLUDED
#define DIPSWITCH_H_INCLUDED

#include <stdint.h>


void dipswitch_init(void);
uint8_t dipswitch_stable_read(void);


#endif