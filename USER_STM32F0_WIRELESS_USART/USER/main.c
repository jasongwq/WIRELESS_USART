/***************************************************************/
//2013.10.26  Copyright@ rhyme呆瓜云
/***************************************************************/
#include "stm32f0xx.h"
#include "usart.h"
#include "delay.h"
#include "gpio.h"
#include "stdio.h"
/***************************************************************/
#include "sys_os.h"
#include "sys_usart.h"
/***************************************************************/
/***************************************************************/
#include "user.h"
/***************************************************************/
enum NRF_ID_TYPE NRF_ID;
u8 cha;//串口已接收 但未转发完成的数据量
u8 nrf_test[32];

/**
 * 运行指示灯
 * @method PB1
 * @return null
 */
int task_led(void)
{
    _SS
    PB1_OUT Clr_B1
    while (1)
    {
        WaitX(50);
        static int systick;
        if (systick++)
        {
            systick = 0;
            Set_B1
        }
        else
        {
            Clr_B1
        }
    }
    _EE
}


int main(void)
{
    SYS_INIT();
    while (1)
    {
        if (NRF_ID == NRF905 || NRF_ID == NRF_NOLL)
        {
            RunTaskA(task_nrf905, 1);
        }
        if (NRF_ID == NRF24L01 || NRF_ID == NRF_NOLL)
        {
#if TX_RX_MODE
            RunTaskA(task_nrf24l01_t, 2);
#else
            RunTaskA(task_nrf24l01_r, 2);
#endif
            RunTaskA(task_led, 0);
        }
    }
}
void SYS_INIT(void)
{
    SysTick_Config(48000000 / 8 / OS_TICKS_PER_SEC);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    USART_Configuration(115200);
    printf("Usart Printf ok! \r\n");
		NRF_ID = NRF24L01;
}
/***************************************************************/

