#ifndef DIGIN_H_INCLUDED
#define DIGIN_H_INCLUDED


typedef enum {
    DIGIN_IN1 = 0,
    DIGIN_IN2,
    DIGIN_IN3,
    DIGIN_IN4,
    DIGIN_IN5,
    DIGIN_IN6,
    DIGIN_IN7,
    DIGIN_IN8,
    DIGIN_IN9,
    DIGIN_IN10,
    DIGIN_IN11,
    DIGIN_IN12,
} digin_t;



void digin_init(void);
int digin_take_reading(void);
int digin_get(digin_t digin);
unsigned int digin_get_inputs(void);


#endif