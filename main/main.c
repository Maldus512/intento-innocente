#include <string.h>
#include "peripherals/system.h"
#include "peripherals/digout.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "gel/timer/timecheck.h"
#include "peripherals/dipswitch.h"
#include "lightmodbus/lightmodbus.h"
#include "lightmodbus/slave.h"


int main(void) {
    system_init();
    digout_init();
    timer_init();
    uart_init();
    dipswitch_init();
    
    uint8_t config = dipswitch_stable_read();
    
    ModbusSlave minion={0};
    uint8_t coils[2] = {0};
    minion.coils = coils;
    minion.coilCount = 16;
    minion.address = 2 + config;
    modbusSlaveInit(&minion);
    
    unsigned long tsrx = 0;
    int i = 0;
    
    for (;;) {
        if (is_expired(tsrx,get_millis(), 10))  {
           int len = uart_read_rx_buffer(minion.request.frame); 
           minion.request.length=len;
           
           if (len > 0) {
                ModbusError err = modbusParseRequest(&minion);
                if (err==MODBUS_OK || err==MODBUS_ERROR_EXCEPTION) {
                    uart_clean_rx_buffer();
                    uart_sync_write(minion.response.frame, minion.response.length);
                }

                for (i = 0; i < NUM_RELE; i++) {
                    digout_update_rele(i, (coils[i/8] & (1 << (i % 8))) > 0);
                }
           }
           
           tsrx=get_millis();
        }
        
        Idle(); // This also resets the watchdog timer
    }
    
    return 0;
}