/******************************************************************************/
/*                                                                            */
/*      H   H      SSSS     W   W                                             */
/*      H   H     S         W   W                                             */
/*      HHHHH      SSS      W   W                                             */
/*      H   H         S     W W W                                             */
/*      H   H  *  SSSS   *   W W   *  snc                                     */
/*                                                                            */
/*      *********************************                                     */
/*                                                                            */
/*  HSW snc - Casalecchio di Reno (BO) ITALY                                  */
/*  ----------------------------------------                                  */
/*                                                                            */
/*  programma:  Scheda Espansione 16 OUT+12 IN + 2 DipSW + 1 TX/RX RS485      */
/*                                                                            */
/*  cliente:    H.S.W. snc x GA Service & Rotondi Group                       */
/*                                                                            */
/*  ver. 00:    02/08/2021  Come prima GA                                     */
/*                                                                            */
/*  ver. att.:  02/08/2022  00.3                                              */
/*                                                                            */
/*  BY:         Maldus (Mattia MALDINI) & Massimo ZANNA                       */
/*                                                                            */
/*  NNB:        SENSO DEGLI INGRESSI: DRITTO !!!!                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  micro:      MicroChip PIC PIC24FJ256GA705 - XXXMHz  ????????              */
/*              256 Flash - x4K Auxiliary Flash - xx.xxxb Ram                 */
/*              xxx.xxx b ?  xx.xxx b ?            xx.xxx b                   */
/*                                                                            */
/*============================================================================*/

// STRINGA "VERSIONE PROGRAMMA"              12345678901234567890123456
const unsigned char str_versione_prog[32] = "I.I. # V.00.3 D.02/08/2022"; // 26 CHR

/******************************************************************************/
/*                                                                            */
/*  rev.:   00.0 del 02/81/2021                                               */
/*                                                                            */
/*      - versione di partenza dalla versione GA-I/O Remote Control 02/08/2021*/
/*                                                                            */
/******************************************************************************/



#include <string.h>
#include "peripherals/system.h"
#include "peripherals/digout.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "gel/timer/timecheck.h"
#include "peripherals/dipswitch.h"
#include "lightmodbus/lightmodbus.h"
#include "lightmodbus/slave.h"
#include "peripherals/digin.h"
#include "gel/serializer/serializer.h"

#include "peripherals/hardwareprofile.h"





int main(void)
{
    unsigned long timestamp = 0;
    
    system_init();
    digin_init();
    digout_init();
    timer_init();
    uart_init();
    dipswitch_init();
    
    uint8_t config = dipswitch_stable_read();
    
    ModbusSlave minion={0};
    uint8_t coils[2] = {0};
    uint8_t discrete[2] = {0};
    minion.coils = coils;
    minion.coilCount = 16;
    minion.discreteInputs = discrete;
    minion.discreteInputCount = 12;
    minion.address = 2 + config;
    modbusSlaveInit(&minion);
    
    int i = 0;
    
    for (;;)
    {
       int len = uart_read_rx_buffer(minion.request.frame); 
       minion.request.length=len;

        if (len > 0)
        {
            ModbusError err = modbusParseRequest(&minion);
            if (err==MODBUS_OK || err==MODBUS_ERROR_EXCEPTION)
            {
                uart_clean_rx_buffer();
                uart_sync_write(minion.response.frame, minion.response.length);

                for (i = 0; i < NUM_RELE; i++)
                {
                    digout_update_rele(i, (coils[i/8] & (1 << (i % 8))) > 0); // LETTURA "NORMALE" INPUT
                }
            }
        }
        
        if (is_expired(timestamp, get_millis(), 10))
        {
            if (digin_take_reading() > 0)
            {
                serialize_uint16_le(discrete, (uint16_t)digin_get_inputs());
            }
            
            
            
//            size_t i = 0;
//            for (i = 0; i < 12; i++)
//            {
//               //digout_update_rele(i, digin_get(i)); // LETTURA "FORZATA" IN SU OUT
//            }
            
            
            
            timestamp = get_millis();
        }
       
       
       
//        input_buf = digin_reading();
//        
//        if (input_buf |= 0)
//        {
//            Nop();
//            Nop();
//            Nop();
//            Nop();
//        }
//        
//        
//        Nop();
//        Nop();
//        Nop();
//        Nop();
//        
//        mem_in[0] = !INPUT1_PORT;
//        mem_in[1] = !INPUT2_PORT;
//        mem_in[2] = !INPUT3_PORT;
//        mem_in[3] = !INPUT4_PORT;
//        
//        mem_in[4] = !INPUT5_PORT;
//        mem_in[5] = !INPUT6_PORT;
//        mem_in[6] = !INPUT7_PORT;
//        mem_in[7] = !INPUT8_PORT;
//        
//        mem_in[8] = !INPUT9_PORT;
//        mem_in[9] = !INPUT10_PORT;
//        mem_in[10] = !INPUT11_PORT;
//        mem_in[11] = !INPUT12_PORT;
        
       
       
       
        Idle(); // This also resets the watchdog timer
    }
    
    return 0;
}
