#include "hardwareprofile.h"
#include "digout.h"


void digout_init(void) {
    RELE1_TRIS = TRIS_OUTPUT;
    RELE2_TRIS = TRIS_OUTPUT;
    RELE3_TRIS = TRIS_OUTPUT;
    RELE4_TRIS = TRIS_OUTPUT;
    RELE5_TRIS = TRIS_OUTPUT;
    RELE6_TRIS = TRIS_OUTPUT;
    RELE8_TRIS = TRIS_OUTPUT;
    RELE9_TRIS = TRIS_OUTPUT;
    RELE10_TRIS = TRIS_OUTPUT;
    RELE11_TRIS = TRIS_OUTPUT;
    RELE12_TRIS = TRIS_OUTPUT;
    RELE13_TRIS = TRIS_OUTPUT;
    RELE14_TRIS = TRIS_OUTPUT;
    RELE15_TRIS = TRIS_OUTPUT;
    RELE16_TRIS = TRIS_OUTPUT;
}


void digout_update_rele(rele_t rele, int val) {
    val = val > 0;
    switch(rele) {
        case RELE_1 :
            RELE1_LAT=val;
            break;
        case RELE_2 :
            RELE2_LAT=val;
            break;
        case RELE_3 :
            RELE3_LAT=val;
            break;
        case RELE_4 :
            RELE4_LAT=val;
            break;
        case RELE_5 :
            RELE5_LAT=val;
            break;
        case RELE_6 :
            RELE6_LAT=val;
            break;
        case RELE_7 :
            RELE7_LAT=val;
            break;
        case RELE_8 :
            RELE8_LAT=val;
            break;
        case RELE_9 :
            RELE9_LAT=val;
            break;
        case RELE_10 :
            RELE10_LAT=val;
            break;
        case RELE_11 :
            RELE11_LAT=val;
            break;
        case RELE_12 :
            RELE12_LAT=val;
            break;
        case RELE_13 :
            RELE13_LAT=val;
            break;
        case RELE_14 :
            RELE14_LAT=val;
            break;
        case RELE_15 :
            RELE15_LAT=val;
            break;
        case RELE_16 :
            RELE16_LAT=val;
            break;
        default:
            break;
    }
}