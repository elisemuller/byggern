# byggern

NODE 1:
ADC: xmem
CAN: mcp, game
movement: adc, can
OLED: xmem
SPI: 
UART:
game: movement, menu
mcp: SPI
menu: oled, movement, can, game
xmem:

main: xmem, menu, can, game

NODE 2:
PWM: can_i
adc:
buzzer: PWM, game
can_c:
can_i: can_c, game, buzzer
game: PWM, motor, can_i, solenoid, adc, time, PID
motor: can_i, time
solenoid:
PID: motor
time: 

main: can_i, can_c, game, buzzer,
