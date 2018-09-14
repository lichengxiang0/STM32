#include "process.h"
#include "string.h"

char pos_shuzu[100]={0};


unsigned char data_pos_cnt=0;
char pos_jilu_flag=0;

const unsigned char START_BYTE=0xAA;
const unsigned char END_BYTE=0xFC;
#define RX_START  0
#define RX_DATA  1	
#define RX_MAX   100
unsigned char start_cnt=0;
unsigned char end_cnt=0;
unsigned char RX_STATUS=RX_START;

char longitude[8];
double plongitude=0;
char latitude[8];
double platitude=0;
char high[4];
float phigh=0;
char pitch[4];
float ppitch=0;
char row[4];
float prow=0;
char dirct[4];
float pdirct=0;

u8 test_cnt = 0;

unsigned char com_data =0;
unsigned char i=0;

u8 flag_uart2 = 0;

#if 1
void USART2_IRQHandler(void)
{
    test_cnt++;

	//接收中断 (接收寄存器非空)----------------------------------------
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{
			com_data= USART2->DR;
	     
   switch (RX_STATUS)
     {
   case RX_START:
        if (com_data == START_BYTE)//0xAA 大写字符U
        {
               start_cnt++;
            if (start_cnt == 3)
            {
                RX_STATUS = RX_DATA;
				start_cnt=0;
              //  RX_head_check_cnt_0 = 0;
              //  RX_rear_check_cnt_0 = 0;
            }
        }
        else
        {start_cnt = 0;}
        break;

    case RX_DATA:
      pos_shuzu[data_pos_cnt] = com_data;
            data_pos_cnt ++;
		    if(data_pos_cnt==8)
				{
					for(i=0;i<8;i++)
					{
					longitude[i]=pos_shuzu[i];
					}
            memcpy(&plongitude,longitude,sizeof(longitude));
//          plongitude=*(double*)&longitude;
				}
				else if(data_pos_cnt==16)
				{
				   for(i=0;i<8;i++)
					{
					latitude[i]=pos_shuzu[i+8];
					}
//          platitude=*(double*)&latitude;
                    memcpy(&platitude,latitude,sizeof(latitude));
				}
				else if(data_pos_cnt==20)
				{
				  for(i=0;i<4;i++)
					{
					high[i]=pos_shuzu[i+16];
					}
//          phigh=*(float*)&high;
                    memcpy(&phigh,high,sizeof(high));
				
				}
				else if(data_pos_cnt==24)
				{
				  for(i=0;i<4;i++)
					{
					pitch[i]=pos_shuzu[i+20];
					}
//          ppitch=*(float*)&pitch;
                    memcpy(&ppitch,pitch,sizeof(pitch));
				
				}
			  else if(data_pos_cnt==28)
				{
				  for(i=0;i<4;i++)
					{
					row[i]=pos_shuzu[i+24];
					}
//          prow=*(float*)&row;
                    memcpy(&prow,row,sizeof(row));
				
				}
				 else if(data_pos_cnt==32)
				{
				  for(i=0;i<4;i++)
					{
					dirct[i]=pos_shuzu[i+28];
					}
//           pdirct=*(float*)&dirct;
               memcpy(&pdirct,dirct,sizeof(dirct));      
				
				}
		   if(data_pos_cnt>RX_MAX)
			 {
			    data_pos_cnt=0;
			    RX_STATUS=RX_START;
			 }

        if (com_data == END_BYTE)//0xFC
        {
              end_cnt++;
            if (end_cnt == 3)
            {
							 end_cnt=0;
					
               RX_STATUS=RX_START;
               data_pos_cnt=0;
                flag_uart2 = 1;	
          
            }
        }
        else
        end_cnt = 0;

        break;
    }
   }


}
#endif
