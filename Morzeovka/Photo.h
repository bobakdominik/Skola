/* 
* Photo.h
*
* Author: bobak
*/


#ifndef __PHOTO_H__
#define __PHOTO_H__

#include "Board.h"
#include "Adc.h"

class Photo:Adc
{
//variables
public:
protected:
private:

//functions
public:
	Photo();
	~Photo();
	int get_value(void);
protected:
private:
	Photo( const Photo &c );
	Photo& operator=( const Photo &c );

}; //Photo

#endif //__PHOTO_H__
