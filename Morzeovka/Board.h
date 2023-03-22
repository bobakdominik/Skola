/*
 * Board.h
 *
 *  Author: bobak
 */ 


#ifndef BOARD_H_
#define BOARD_H_



#define BOARD_TYPE 2018	 // 2017

#ifndef F_CPU
#define F_CPU 12000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

/************************** MACROS ****************************/
#define sbi(x,y) x |= _BV(y)		// set bit (1<<y) [log. 1]
#define cbi(x,y) x &= ~(_BV(y))		// clear bit - using bitwise AND operator [log. 0]
#define tbi(x,y) x ^= _BV(y)		// toggle bit - using bitwise XOR operator
/**************************************************************/

/************************** RGB ****************************/
#define R_LED PORTD6
#define G_LED PORTD3
#if BOARD_TYPE == 2018
#define B_LED PORTD5
#else
#define B_LED PORTB1
#endif

enum Colour {						// enumerable type - default: 0, 1, 2, 3...
	red, green, blue, yellow, purple, cyan, white, black, count
};
/***********************************************************/

/************************** BUTTON ****************************/
#define BTN PORTD2
/**************************************************************/

/************************** DISPLAY ****************************/
#define SER PORTC5
#define OE PORTC4
#define RCLK PORTD7
#define SRCLK PORTB1

/* numbers definitions */
//              MSB           LSB
//              H G F E D C B A
#define zero	0b00111111
#define one		0b00000110
#define two		0b01011011
#define three	0b01001111
#define four	0b01100110
#define five	0b01101101
#define six		0b01111101
#define seven	0b00000111
#define eight	0b01111111
#define nine	0b01101111
#define ahex	0b01110111
#define bhex	0b01111100
#define chex	0b01011000
#define dhex	0b01011110
#define ehex	0b01111001
#define fhex	0b01110001
#define dot		0b10000000
#define err		0b01001001
#define non		0b00000000
/***************************************************************/

/************************** UART ****************************/
#define HTX PORTD1
#define HRX PORTD0

#define STX PORTC2
#define SRX PORTC3

#define BAUDERATE 115200   // 115200
#define UBRR_VALUE ((F_CPU / (BAUDERATE * 8L)) -1)  //   8....51  ,  16.....25  12.....12
/***************************************************************/

enum externInt{		// EICRA
	low,			// 00
	change,			// 01
	fall,			// 10
	rising			// 11
};


/************************** MORSE ****************************/

#define DELTA 200

#define ELEMENT_GAP 200
#define DOT_DURATION ELEMENT_GAP
#define DASH_DURATION 3*ELEMENT_GAP
#define CHAR_GAP 3*ELEMENT_GAP
#define WORD_GAP 7*ELEMENT_GAP

#define DOT_MORSE 0b01
#define DASH_MORSE 0b11

#define a_morse	0b01110000
#define b_morse	0b11010101
#define c_morse	0b11011101
#define d_morse	0b11010100
#define e_morse	0b01000000
#define f_morse	0b01011101
#define g_morse	0b11110100
#define h_morse	0b01010101
#define i_morse	0b01010000
#define j_morse	0b01111111
#define k_morse	0b11011100
#define l_morse	0b01110101
#define m_morse	0b11110000
#define n_morse	0b11010000
#define o_morse	0b11111100
#define p_morse	0b01111101
#define q_morse	0b11110111
#define r_morse	0b01110100
#define s_morse	0b01010100
#define t_morse	0b11000000
#define u_morse	0b01011100
#define v_morse	0b01010111
#define w_morse	0b01111100
#define x_morse	0b11010111
#define y_morse	0b11011111
#define z_morse	0b11110101
/*
#define zero_morse	0b
#define one_morse	0b
#define two_morse	0b
#define three_morse	0b
#define four_morse	0b
#define five_morse	0b
#define six_morse	0b
#define seven_morse	0b
#define eight_morse	0b
#define nine_morse	0b
*/

/*************************************************************/

#endif /* BOARD_H_ */