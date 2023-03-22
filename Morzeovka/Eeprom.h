/* 
* Eeprom.h
*
* Author: bobak
*/


#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "Board.h"

class Eeprom
{
//variables
public:
protected:
private:

//functions
public:
	Eeprom();
	~Eeprom();
	static void write(uint16_t uiAddress, uint8_t ucData);
	static uint8_t read(uint16_t uiAddress);
protected:
private:


}; //Eeprom

#endif //__EEPROM_H__
