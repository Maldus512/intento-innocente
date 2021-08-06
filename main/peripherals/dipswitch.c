#include <stdlib.h>
#include "system.h"
#include "hardwareprofile.h"
#include "dipswitch.h"
#include "gel/debounce/debounce.h"


void dipswitch_init(void) {
    DIPSWITCH1_TRIS = TRIS_INPUT;
    DIPSWITCH2_TRIS = TRIS_INPUT;
}


uint8_t dipswitch_stable_read(void) {
    debounce_filter_t filter = {0};
    size_t attempts = 0;
    int changed = 0;
    
    debounce_filter_init(&filter);
    
    do {
        unsigned int input = DIPSWITCH2_PORT | (DIPSWITCH1_PORT << 1);
        changed = debounce_filter(&filter, input, 5);
        attempts++;
        __delay_ms(5);
    } while ((attempts < 20 || changed) && attempts < 100);
    
    if (changed) {
        return 0;
    } else {
        return (uint8_t)debounce_value(&filter);
    }
}


