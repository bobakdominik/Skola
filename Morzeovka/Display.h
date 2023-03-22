/* 
* Display.h
*
* Author: bobak
*/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Board.h"

class Display
{
//variables
public:
protected:
private:

//functions
public:
	Display();
	~Display();
	void show(uint8_t character);
	void circle();
protected:
private:
	void display(uint8_t character);


}; //Display

#endif //__DISPLAY_H__
