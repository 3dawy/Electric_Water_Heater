#include "i2c.h"

#define EXT_EEPROM_ADD_WRITE        0xA0
#define EXT_EEPROM_ADD_READ         0xA1




void EXTEEPROM_Init (void)
{
    I2C_Init();
}
void EXTEEPROM_WriteByte (uint8_t Data, uint8_t ByteAdd)
{
    I2C_Start();
    I2C_Write(EXT_EEPROM_ADD_WRITE);
    I2C_Write(ByteAdd);
    I2C_Write(Data);
    I2C_Stop();
}
void EXTEEPROM_ReadByte (uint8_t* Data, uint8_t ByteAdd)
{
    I2C_Start();
    I2C_Write(EXT_EEPROM_ADD_WRITE);
    I2C_Write(ByteAdd);
    I2C_Restart();
    I2C_Write(EXT_EEPROM_ADD_READ);
    *Data = I2C_Read(1);
    I2C_Stop();
}
