/* 
* Morse.h
*
* Author: bobak
*/


#ifndef __MORSE_H__
#define __MORSE_H__
#include "LED.h"
#include "Photo.h"
#include "Uart.h"
#include "Board.h"

class Morse
{
//variables
public:
	typedef void (Morse::*MainFun)(void); 
protected:
private:
Led* rgb_ptr;					
Uart* uart_ptr;					
Photo* photo_ptr;
bool stopFunction;

//functions
public:
	Morse(Led* rgb,	Uart* uart,	Photo* photo);
	~Morse();
	void ReceiveData(void);
	void TransmitData(void);
	void setStop(bool stop);
	bool getStop(void);
protected:
private:
	Morse( const Morse &c );
	Morse& operator=( const Morse &c );
	
	void showSign(uint8_t sign);
	void delay_ms(int ms);
	
	char convertIntToMorseChar(uint8_t val);
	uint8_t convertCharToMorseInt(char val);
}; //Morse

char convertIntToMorseChar(uint8_t val);
uint8_t convertCharMorseInt(char val);

#endif //__MORSE_H__
