#ifndef 	__EEPROM_H
#define		__EEPROM_H
#include "softwarei2c.h"
#include "uart.h"


#define EEPROM_DEV_ADDR			0xA0		/* 24xx02的设备地址 */
#define EEPROM_PAGE_SIZE		  8			  /* 24xx02的页面大小 */
#define EEPROM_SIZE				  256			  /* 24xx02总容量 */
																					
//void EEPROM_Init(void);	
//void I2C_EE_WaitEepromStandbyState(void);
//uint32_t I2C_EE_ByteWrite(u8* pBuffer,u8 WriteAddr);			
//void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite);

uint8_t ee_CheckOk(void);
uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
void ee_Erase(void);
uint8_t ee_Test(void);
#endif 		/*__EEPROM_H*/