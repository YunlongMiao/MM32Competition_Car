#include "zf_common_headfile.h"

#include "motor_control.h"
#include "sensing_control.h"


#define GET_pit_handler                         (TIM7_PIT )
#define PIT_Motor                   						 TIM8_PIT






int main(){

	int data ; 
	uint32 len;
	uint8 Cont_Da[64]; 
	Control_Data_TypeDef Control_Data;
	
	clock_init(SYSTEM_CLOCK_120M);        // 初始化芯片时钟 工作频率为 120MHz
  debug_init();
	
	Sensing_Control_Init();
	Motor_Control_Init();
	
//	
	pit_ms_init(PIT_Motor,10);	//电机
//	pit_ms_init(GET_pit_handler,5);	//读取发送指令
	gpio_init(H2, GPO, GPIO_LOW, GPO_PUSH_PULL);
	while(1){
		
//		len = debug_read_ring_buffer(&data);
//		if(data == 101 | data == 102 | data == 103 | data == 104 | data == 201 | data == 202 | data == 203 | data == 301)
//		{
//							gpio_set_level(E9, GPIO_HIGH);                                            // BEEP 响
//							system_delay_ms(100);
//							gpio_set_level(E9, GPIO_LOW); 
//							Get_All_Sensing(&Control_Data);
//							Cont_Da[0] = Control_Data.power;
//							Cont_Da[1] = Control_Data.pm2_5;
//							Cont_Da[2] = Control_Data.Tem;
//							Cont_Da[3] = Control_Data.ShiDu;
//							Cont_Da[4] = Control_Data.fire;
//							uart_write_buffer(UART_6,Cont_Da,5);
//			
//		}
//							gpio_toggle_level(H2);
//							delay_ms(1000);
//							len = 0;
		
	}
}


void Motor_pit_handler (void)
{
		Gray_Control();
}

void GET_pit_Control()
{
	int i =0;

}