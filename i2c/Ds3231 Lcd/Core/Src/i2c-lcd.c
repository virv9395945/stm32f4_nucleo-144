
/** Put this in the src folder **/

#include "i2c-lcd.h"
#include "stdio.h"

extern I2C_HandleTypeDef I2C_LCD; 			 // change your handler here accordingly
//extern   char Linea_1[20];
//extern   char Linea_2[20];

extern     char 		display[2][16];

/**
  ******************************************************************************
  * @brief	Direccion I2C del dispositivo, se entrega valor desplazado y unico
  *			para lectura y escritura
  ******************************************************************************
  */
#define SLAVE_ADDRESS_LCD 0x27 << 1


/**
  ******************************************************************************
  * @brief	Declaración variables denerales
  ******************************************************************************
  */
 #define timeout 100 
  
/**
  ******************************************************************************
  * @brief	go
  * @param	
  * @retval	
  ******************************************************************************
  */
void lcd_send_cmd (char cmd)
{
   char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&I2C_LCD, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, timeout );
}
/**
  ******************************************************************************
  * @brief	
  * @param	
  * @retval	
  ******************************************************************************
  */
void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0    1101
	data_t[1] = data_u|0x09;  //en=0, rs=0    1001
	data_t[2] = data_l|0x0D;  //en=1, rs=0    1101
	data_t[3] = data_l|0x09;  //en=0, rs=0    1001
	HAL_I2C_Master_Transmit (&I2C_LCD, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, timeout );	
}
/**
  ******************************************************************************
  * @brief	
  * @param	
  * @retval	
  ******************************************************************************
  */
void lcd_init (void)
{
	lcd_send_cmd (0x01);
	HAL_Delay(4);
	lcd_send_cmd (0x02);
	HAL_Delay(4);
	lcd_send_cmd (0x28);
	HAL_Delay(4);
	
	lcd_send_cmd (0x0c);
	HAL_Delay(4);
	lcd_send_cmd (0x80);
	HAL_Delay(4);
}
/**
  ******************************************************************************
  * @brief	
  * @param	
  * @retval	
  ******************************************************************************
  */
void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}
/**
  ******************************************************************************
  * @brief	
  * @param	
  * @retval	
  ******************************************************************************
  */
void lcd_send_string_file (uint8_t File, char *str)
{
	if ( File == 0 )
		lcd_send_cmd (0x80);
	else
		lcd_send_cmd (0xc0);

	lcd_send_string (str);
}
/**
  ******************************************************************************
  * @brief	
  * @param	
  * @retval	
  ******************************************************************************
  */
void lcd_send_string_cr (char *str)
{
	sprintf(display[0],"%s", display[1]);
	sprintf(display[1],"%s", str);

	lcd_send_string_file (File_1, display[0]);
	lcd_send_string_file (File_2, display[1]);		
}

/*
 * @brief Print a string on the LCD
 * @param x: starting point on the x-axis (column)
 * @param y: starting point on the y-axis (line)
 */
void LCD_print(char *str, uint8_t x, uint8_t y){
	
	if ( y == 0 )
		lcd_send_cmd (0x80 );
	else
		lcd_send_cmd (0xc0 );
	
	lcd_send_string_file ( y , str);
	
}

