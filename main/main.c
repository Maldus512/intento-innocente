#include <string.h>
#include "peripherals/system.h"
#include "peripherals/digout.h"
#include "peripherals/timer.h"
#include "peripherals/uart.h"
#include "gel/timer/timecheck.h"

#include "lightmodbus/lightmodbus.h"
#include "lightmodbus/slave.h"


int main(void) {
    system_init();
    digout_init();
    timer_init();
    uart_init();
    
    ModbusSlave slave={0};
    uint8_t coils[2] = {0};
    slave.coils = coils;
    slave.coilCount = 16;
    slave.address = 2;
    modbusSlaveInit(&slave);
    
    unsigned long ts = 0, tsrx = 0;
    int i = 0;
    char *string = "hello\n";
    
    for (;;) {
        
        if (is_expired(tsrx,get_millis(), 50))  {
           uint8_t buffer[300];
           int len = uart_read_rx_buffer(buffer); 
           slave.request.frame=buffer;
           slave.request.length=len;
           ModbusError err = modbusParseRequest(&slave);
           if (err==MODBUS_OK || err==MODBUS_ERROR_EXCEPTION) {
               uart_sync_write(slave.response.frame, slave.response.length);
               uart_clean_rx_buffer();
           }
           
           for (i = 0; i < NUM_RELE; i++) {
               digout_update_rele(i, (coils[i/8] & (1 << (i % 8))) > 0);
           }
           
           tsrx=get_millis();
        }
        
        if (is_expired(ts, get_millis(), 1000)) {
            uart_sync_write(string, strlen(string));
            ts = get_millis();
        }
    }
    
    return 0;
}