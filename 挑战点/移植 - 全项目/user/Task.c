//Task.cнд╪Ч
#include "Task.h"
#include "usart.h"
#include <os.h>
void TASK1(void *p_arg){
while(1){
USART2_SendChar('a');
OSTimeDly(1000);
}
}
void TASK2(void *p_arg){
while(1){
USART2_SendChar('b');
OSTimeDly(1500);
}
}
