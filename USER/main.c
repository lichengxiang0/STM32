/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "process.h"

uint64_t mycnt = 0;

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
   delay_init();	    	 //延时函数初始化	
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
   uart1_init(115200);	 //串口初始化为115200
   uart2_init(115200); 
 
  /* Infinite loop */
  while (1)
  {
      if(flag_uart2)
      {
        flag_uart2 = 0;
        printf("latitude=%f&longitude=%f&height=%f&roll=%f&pitch=%f&yaw=%f\n",platitude,plongitude,phigh,prow,ppitch,pdirct);
      }

  }
}



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
