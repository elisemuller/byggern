
#define CAN_BR

#include "can_controller.h"
#include "sam.h"
#include "printf-stdarg.h"
#include "uart.h"


int main(void){
  configure_uart();
  can_init_def_tx_rx_mb(CAN_BR);
  
  //test can reception for joystick
}
