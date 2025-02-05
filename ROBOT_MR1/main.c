// #include "cmsis_os.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "FreeRTOS.h"
#include "task.h"

#include "utils.h"
#include "config.h"
#include "doc_tay_game.h"
#include "4OmniControler.h"

#include "Ban_Tay.h"
#include "Canh_Tay.h"
#include "Motor_Hut.h"
#include "Mam_Xoay.h"

vs32 HMI_LOOP;

void HMI_TRAN(vs32 _so_dong)
{
	char *camera = "11111111111111111111110111111111";
	vs32 _i, _chua_cac_bit = 0;
	char _ghep_bit[40];
	char _chu_cac_bit[40];
	_ghep_bit[0] = 0;
	_chu_cac_bit[0] = 0;
	switch (_so_dong)
	{
	case 0:
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_15, 0);
			HMI_DMI("ROBOT 2 DANG CHAY SAN XANH:   ", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15), 0);
		}
		else
		{
			GPIO_WriteBit(GPIOC, GPIO_Pin_15, 1);
			HMI_DMI("ROBOT 2 DANG CHAY SAN DO:   ", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_15), 0);
		}

		break;
	case 1:
		HMI_DMI("IMU:", _robotIMUAngle, 1);
		break;
	case 2:
		HMI_DMI("LAZER TRUOC:", lazerTruocValue, 2);
		break;
	case 3:
		HMI_DMI("LAZER TRAI:", lazerTraiValue, 3);
		break;
	case 4:
		HMI_DMI("LAZER PHAI:", lazerPhaiValue, 4);
		break;

	case 5:
		HMI_DMI("EN B TRAI:", get_Encoder_Banh_Trai(), 5);
		break;
	case 6:
		HMI_DMI("EN B PHAI:", get_Encoder_Banh_Phai(), 6);
		break;
	case 7:
		HMI_DMI("EN TONG:", get_Encoder_Tong(), 7);

	case 8:
		HMI_DMI("EN CT X:", ENCODER_CANH_TAY_X, 8);
		break;
	case 9:
		HMI_DMI("EN CT Y:", ENCODER_CANH_TAY_Y, 9);
		break;
	case 10:
		HMI_DMI("BT MAM XOAY:", BIEN_TRO_MAM_XOAY, 10);
		break;
	case 11:
		HMI_DMI("BT BAN TAY:", BIEN_TRO_BAN_TAY, 11);
		break;
	case 12:
		HMI_DMI("T BT MAM XOAY:", Target_Bien_Tro_Mam_Xoay, 12);
		break;
	case 13:
		HMI_DMI("T BT BAN TAY:", Target_Bien_Tro_Ban_Tay, 13);
		break;
	case 14:
		HMI_DMI("CBT Y Duoi:", CAM_BIEN_TU_Y_DUOI, 14);
		break;
	case 15:
		//	hien thi phan ngo vao
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)); //
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)); // CB bong
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		//										sprintf(_ghep_bit,"%d",cb_dung_chan_da);
		//										strcat(_chu_cac_bit,_ghep_bit);

		HMI_PUTS("I:", _chu_cac_bit, 16);
		break;
	case 16:
		// hien thi phan ngo ra
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_10));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_14));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_11));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12));
		strcat(_chu_cac_bit, _ghep_bit);
		sprintf(_ghep_bit, "%d", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_6));
		strcat(_chu_cac_bit, _ghep_bit);
		HMI_PUTS("OUT:", _chu_cac_bit, 17);
		break;
	}
}
void HMI_RUN_LOOP(vs32 _cause)
{
	if (HMI_LOOP > _cause)
		HMI_LOOP = 0;
	else
		HMI_LOOP++;
	HMI_TRAN(HMI_LOOP);
}
static void taskLCD(void *pvParameters)
{
	while (1)
	{
		HMI_RUN_LOOP(16);
		vTaskDelay(15);
	}
}
static void taskDieuKhienCoCau(void *pvParameters)
{
	while (1)
	{
		ADCValue_Control();
		//		Giu_Tay_Nang_Bong();
		//		Giu_Truc_Y();
		//		Giu_Truc_X();
		//		Giu_Mam_Xoay();
		vTaskDelay(5);
	}
}
static void taskRobotAnalytics(void *pvParameters)
{
	while (1)
	{
		robotAnalytics();
		vTaskDelay(5);
	}
}
void Config_Robot(void)
{
	Config_Out_Mode();
	Config_In_Mode();

	Config_encoder_timer2_timer3();
	Config_encoder_timer1();

	Config_ADC1_DMA();

	Config_int_time7();

	UART1_DMA_RX(115200);
	UART2_DMA_TX(115200);
	UART3_DMA_RX(115200);
	UART4_DMA_RX(115200);
	UART5_DMA_TX(921600);

	Config_encoder_timer5();
	// Config_encoder_timer4();

	vTaskDelay(5);
}

static void taskMain(void *pvParameters)
{

	// xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	// xTaskCreate(taskDieuKhienCoCau, (signed char *)"taskDieuKhienCoCau", 256, NULL, 0, NULL);
	Config_Robot();
	// task_Reset_Canh_Tay_X();
	task_Reset_Canh_Tay_Y();
	while (1)
	{
		// while (gp_get_mode_uart() == GP_MODE_ANALOGUE_RED_LED)
		// {

		// }
		vTaskDelay(5);
	}
}

int main(void)
{

	xTaskCreate(taskMain, (signed char *)"taskMain", 256, NULL, 0, NULL);
	xTaskCreate(taskLCD, (signed char *)"taskLCD", 256, NULL, 0, NULL);

	vTaskStartScheduler();
}
