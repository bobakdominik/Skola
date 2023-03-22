/* 
* Uart.h
*
* Author: bobak
*/


#ifndef __UART_H__
#define __UART_H__

#include "Board.h"


class Uart
{
//variables
public:
	static Uart* uart_ptr;
protected:
private:
	FILE *file_ptr;
	bool takenChar;
	char lastChar;
//functions
public:
	Uart();
	~Uart();
	void interruptHandler(void);
	void initInterrupt(void);
	
	// HW implementation
	static int hwSendByte(char data, FILE *stream);
	static int hwReceiveByte(FILE *stream);
	
	// SW implementation
	static int swSendByte(char data, FILE *stream);
	static int swReceiveByte(FILE *stream);
	
	char getLastChar(void);
	bool charWasTaken(void);
	void charWasTaken(bool val);
	
protected:
private:


}; //Uart

#endif //__UART_H__
