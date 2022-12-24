
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#include "nrf_uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UART_TX_BUFF_SIZE 128
#define UART_RX_BUFF_SIZE 128

#define UART_HWFC APP_UART_FLOW_CONTROL_DISABLED

void SENDSTRING__(char *str);

void uart_err_handle(app_uart_evt_type_t* p)
{

}

void myPrintf(const char s[]);

int main(void)
{
  uint32_t err_code;
  bsp_board_init(BSP_INIT_LEDS); //initialize leds

  const app_uart_comm_params_t com_params = 
  {
  
    26,
    27,
    -1,
    -1,
    UART_HWFC,
    false,
    NRF_UART_BAUDRATE_115200
  };
  APP_UART_FIFO_INIT(&com_params, UART_RX_BUFF_SIZE, UART_TX_BUFF_SIZE, uart_err_handle, APP_IRQ_PRIORITY_LOWEST, err_code);
  APP_ERROR_CHECK(err_code);

  myPrintf("Hello PC from nordic Device!!\r\n");
  while(true)
  {
    uint8_t cr;
    while(app_uart_get(&cr) != NRF_SUCCESS);//wait here until it receives a char from pc
    if(cr == 't')
    {
      bsp_board_leds_on();
      myPrintf("Leds Turned On!!\r\n");
    }else if(cr == 'k'){
      bsp_board_leds_off();
      myPrintf("Leds Turned off!!\r\n");
    }


  }
}

void myPrintf(const char s[])
{
  unsigned int i = 0;
  for(i = 0 ; i < strlen(s) ; i++)
  {
    while (app_uart_put(s[i]) != NRF_SUCCESS);
  }
}
void SENDSTRING__(char *str)
 {

while(*str != '\0')
{
  app_uart_put(*str);
  str++;
}
 }


