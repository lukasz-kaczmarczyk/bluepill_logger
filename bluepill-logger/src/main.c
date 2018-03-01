/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "ff.h"
#include "utils.h"
#include "ds18b20.h"

/* Global variables ----------------------------------------------------------*/
FRESULT fr;
FATFS fs;
FIL fil;
FILINFO fileInfo;
char buff[32];
char buff2[32];
UINT nRead, nWritten;
uint16_t i;
uint fileNr;

simple_float temperature;
int entry = 0;
bool doLog = false;
bool sdPlugged = false;
uint8_t button;
char logName[64] = "test.txt";
char timestamp[32];

ADC_InitTypeDef adc;
float voltage;

/* Private function prototypes -----------------------------------------------*/
void blink_led(uint16_t blink_delay_ms);
void init_pins();
void wait_for_sd();
FRESULT check_sd();
FRESULT open_append(FIL* fp, const char* path);
void init_rtc();
void print_header();

void blink_led(uint16_t blink_delay_ms) {
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);
	delay_ms(TIM2, blink_delay_ms);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);
	delay_ms(TIM2, blink_delay_ms);
}

FRESULT open_append(FIL* fp, /* [OUT] File object to create */
const char* path /* [IN]  File name to be opened */
) {

	/* Opens an existing file. If not exist, creates a new file. */
	fr = f_open(fp, path, FA_WRITE | FA_OPEN_ALWAYS);
	if (fr == 0) {
		/* Seek to end of the file to append data */
		fr = f_lseek(fp, f_size(fp));
		if (fr != 0)
			f_close(fp);
	}
	return fr;
}

void init_pins() {
	GPIO_InitTypeDef gpioInitStruct;
	GPIO_StructInit(&gpioInitStruct);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInitStruct.GPIO_Pin = GPIO_Pin_13;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpioInitStruct);
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpioInitStruct.GPIO_Pin = GPIO_Pin_11;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &gpioInitStruct);

	 gpioInitStruct.GPIO_Pin = GPIO_Pin_0;
	 gpioInitStruct.GPIO_Mode = GPIO_Mode_AIN;
	 GPIO_Init(GPIOA, &gpioInitStruct);
}

FRESULT check_sd() {
	fr = f_mount(&fs, "", 0);
	if (fr != FR_OK) {
		return fr;
	}
	bool hasFile = true;
	fr = f_open(&fil, "test.txt", FA_OPEN_EXISTING);
	if (fr == FR_NO_FILE) {
		hasFile = false;
	}
	uint8_t flags = FA_WRITE;
	if (!hasFile) {
		flags |= FA_CREATE_ALWAYS;
	}
	fr = f_open(&fil, "test.txt", flags);
	if (fr == FR_OK) {
		f_close(&fil);
	} else {
		return fr;
	}
	if (!hasFile) {
		f_unlink("test.txt");
	}
	return FR_OK;
}

void wait_for_sd() {
	FRESULT cardOk = 1;
	while (cardOk != FR_OK) {
		cardOk = check_sd();
		if (cardOk != FR_OK) {
			blink_led(500);
		}
	}
	sdPlugged = true;
}


void print_header() {
	f_mount(&fs, "", 0);
	/* Open or create a log file and ready to append */
	fr = open_append(&fil, logName);
	if (fr == FR_OK) {
		/* Append a line */
		f_puts("voltage logger", logName);
		f_close(&fil);
	}
}

void init_rtc() {
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd (ENABLE);
	/* Reset Backup Domain */
	BKP_DeInit();
	/* Enable LSE */
	RCC_LSEConfig (RCC_LSE_ON);
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) {
	}
	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig (RCC_RTCCLKSource_LSE);
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
	RTC_WaitForLastTask();
}

void init_adc() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	 ADC_StructInit(&adc);
	 adc.ADC_ContinuousConvMode = ENABLE;
	 adc.ADC_NbrOfChannel = 1;
	 adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	 ADC_Init(ADC1, &adc);

	 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_71Cycles5);
	 ADC_Cmd(ADC1, ENABLE);

	 ADC_ResetCalibration(ADC1);
	 while (ADC_GetResetCalibrationStatus(ADC1));

	 ADC_StartCalibration(ADC1);
	 while (ADC_GetCalibrationStatus(ADC1));

	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}



int main(void) {
	setup_delay_timer (TIM2);
	init_pins();
	init_rtc();
	init_adc();
	wait_for_sd();
	//get_log_name();
	//check if file exist:
	sprintf(buff, "%s%d%s","log_", fileNr, ".csv");
	while (FR_OK == (fr = f_stat(buff, &fileInfo))){
		sprintf(buff,"%s%d%s","log_", fileNr, ".csv");
		++fileNr;
	}

	//f_unlink(logName); //delete old file

	while (1) {

		// LED's on while taking measurement and writing it to SD

		voltage = (float)ADC_GetConversionValue(ADC1) * 3.3f / 4096.0f;
		sprintf(buff,"%f\n", voltage);
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);
		f_mount(&fs, "", 0);
		fr = open_append(&fil, logName);
		if (fr == FR_OK) {
			/* Append a line */
			//f_puts(buff, &fil);
			f_puts("44\n", &fil);
			f_close(&fil);
		} else {
			wait_for_sd();
		}
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);
		delay_ms(TIM2,100);
		++i;
		if(10 < i) {
			i=0;
			++fileNr;
			sprintf(buff,"%s%d%s","log_", fileNr, ".csv");
			f_unlink(logName); //delete old file
		}
	}
}
