#include "project.h"

void uart_irq_handler()
{    
    float value;
        
    Cy_SCB_UART_GetArray(UART_HW, &value, 4);
    Cy_SCB_UART_PutArray(UART_HW, &value, 4);
    
    Cy_SCB_UART_ClearRxFifoStatus(UART_HW,CY_SCB_UART_RX_TRIGGER);
}

int main(void)
{
    __enable_irq();
    
    Cy_SysInt_Init(&UART_INTERRUPT_cfg,&uart_irq_handler);
    NVIC_ClearPendingIRQ(UART_INTERRUPT_cfg.intrSrc);
	NVIC_EnableIRQ(UART_INTERRUPT_cfg.intrSrc);
    
    UART_Start();
    
    for(;;)
    {
        CyDelay(1000);
        Cy_GPIO_Write(RED_PORT,RED_NUM,0);
        CyDelay(1000);
        Cy_GPIO_Write(RED_PORT,RED_NUM,1);
    }
}