/*
 * bluetooth.c
 *
 * Created: 02.05.2014 20:06:27
 *  Author: Richard
 */ 
#define F_CPU 19660800UL

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <include/btm222.h>
#include <avr/eeprom.h>
#include <include/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#define btm222_uart_putc(c) uart_putc(c)
#define btm222_uart_puts(s) uart_puts(s)
#define btm222_uart_getc() uart_getc()
#define btm222_uart_init(baud) uart_init(baud)

uint8_t eebtm222state EEMEM = 0;


uint8_t btm222_init()
{
    uint8_t btm222state = 0;
    btm222state = eeprom_read_byte (&eebtm222state);
    _delay_ms(1);
    if (btm222state == 0) {
        btm222_uart_init(UART_BAUD_SELECT(115200,F_CPU));
        btm222_uart_puts(BTM_DEFAULT_CMD);
        _delay_ms(100);
        btm222_uart_puts(BTM_STRING(BTM_ECHO_CMD, BTM_NONE_ECHO));
        _delay_ms(20);
        btm222_uart_puts(BTM_STRING(BTM_FLOW_CTRL_CMD, BTM_FLOW_CTRL_DIS));
        _delay_ms(20);
        btm222_uart_puts(BTM_STRING(BTM_BAUD_CMD, BTM_BAUD_19200));
        _delay_ms(20);
        btm222_uart_init(UART_BAUD_SELECT(19200,F_CPU));
        _delay_ms(20);
        btm222_uart_puts(BTM_STRING(BTM_BT_NAME_CMD, BTM_BT_NAME));
        _delay_ms(20);
        btm222_uart_puts(BTM_STRING(BTM_PASSWORD_CMD, BTM_BT_PASSWORD));
        _delay_ms(20);
        btm222state = 1;
        eeprom_update_byte(&eebtm222state, btm222state);
    }
    else {
        btm222_uart_init(UART_BAUD_SELECT(19200,F_CPU));
    }
    return BTM_ERRNO_INIT_DONE;
}

void btm222_conneciton(uint8_t c)
{
    static char btm222_income[31];
    static uint8_t btm222_count = 0;
    
    if (btm222_count >= 31) {
        btm222_count = 0;
    }
    
    if (c != '\n') {
        btm222_income[btm222_count++] = c;
        btm222_income[btm222_count] = 0;
        if (btm222_count >= 7) {
            if((!strncmp("CONNECT", btm222_income, 7))) {
                _delay_ms(200);
                btm222_uart_puts("Welcome!\r\n");
                btm222_count = 0;
            }
            if((!strncmp("DISCONNECT", btm222_income, 9))) {
                btm222_count = 0;
            }
        }
    }
    else {
        btm222_count = 0;
    }
    
}