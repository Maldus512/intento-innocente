#ifndef DIGOUT_H_INCLUDED
#define DIGOUT_H_INCLUDED

typedef enum {
    RELE_1 = 0,
    RELE_2,
    RELE_3,
    RELE_4,
    RELE_5,
    RELE_6,
    RELE_7,
    RELE_8,
    RELE_9,
    RELE_10,
    RELE_11,
    RELE_12,
    RELE_13,
    RELE_14,
    RELE_15,
    RELE_16,
    NUM_RELE,            
} rele_t;


void digout_init(void);
void digout_update_rele(rele_t rele, int val);


#endif