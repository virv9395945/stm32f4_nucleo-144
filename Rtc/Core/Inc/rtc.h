/*******************************************************************************
  rtc.h


 **** Agregar en main.c ****

 Private includes ----------------------------------------------------------
 	USER CODE BEGIN Includes
 	#include "rtc.h"
 	#include "stdio.h"


 USER CODE BEGIN PV
RTC_HandleTypeDef   HRTC;

char 	time[10]		;
char 	date[10]		;

uint8_t t_hours 	  = 12 ;
uint8_t t_minutes   = 02 ;
uint8_t t_seconds   = 00 ;
uint8_t d_weekday   =  5 ;
uint8_t d_month 	  =  4 ;
uint8_t d_date	  = 22 ;
uint8_t d_year	  = 21 ;

uint8_t a_hours   = 12 ;
uint8_t a_minutes =  5 ;
uint8_t a_seconds =  0 ;
uint8_t a_weekday =  5 ;

uint8_t alarm     =  0 ;

 USER CODE BEGIN PFP
void to_do_on_alarm( void );

 USER CODE BEGIN 2
  rtc_init(  );

NOTA: borrar completo de main.c la funcion MX_RTC_Init(void)

USER CODE BEGIN 4

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
	alarm = 1;
}

void to_do_on_alarm( void )
{
  *** RUTINA ALARNA ***
}

*******************************************************************************/

#include "device.h"

#ifndef INC_RTC_H_
#define INC_RTC_H_

void rtc_init( );
void set_time_date 	( uint8_t hours  , uint8_t minutes, uint8_t seconds, uint8_t weekday, uint8_t month, uint8_t date, uint8_t year );
void set_time 		( uint8_t hours  , uint8_t minutes, uint8_t seconds );
void set_date 		( uint8_t weekday, uint8_t month  , uint8_t date   , uint8_t year );
void set_alarma 	( uint8_t hours  , uint8_t minutes, uint8_t seconds , uint8_t weekday );

/*******************************************************************************/
 void get_time(void);


#endif /* INC_RTC_H_ */
