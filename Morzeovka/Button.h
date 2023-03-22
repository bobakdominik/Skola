/*
* Button.h
*
* Author: bobak
*/


#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Board.h"
#include "Morse.h"

class Button
{
	//variables
	public:
		static Button* button_ptr;
	protected:
	private:
		volatile bool is_pressed;
		volatile uint8_t counter;
		Morse* morse_ptr;
	//functions
	public:
	Button(Morse* morse);
	~Button();
	bool isPressed(void);
	void interruptHandler(void);
	void initInterrupt(externInt edge);
	uint8_t getCounter();
	bool getPressed(void);
	void setPressed(bool pressed);
	protected:
	private:


}; //Button

#endif //__BUTTON_H__
