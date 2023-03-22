/* 
* Morse.cpp
*
* Author: bobak
*/


#include "Morse.h"



// default constructor
Morse::Morse(Led* rgb,	Uart* uart,	Photo* photo){
	photo_ptr = photo;
	uart_ptr = uart;
	rgb_ptr = rgb;
	stopFunction = false;
	//this->MainFun = &this->ReceiveData;
	 
}

// default destructor
Morse::~Morse()
{
} //~Morse

void Morse::ReceiveData(void){
	int defVal = photo_ptr->get_value();
	while (defVal - DELTA < photo_ptr->get_value() )
	{
		delay_ms(ELEMENT_GAP);
		if (stopFunction)
		{
			return;
		}
	}
	const int offset = 4;
	int flash = 0;
	int pause = 0;
	uint8_t num = 0;
	int step = 0;
	while (1)
	{
		if (stopFunction)
		{
			return;
		}
		int val = photo_ptr->get_value();
				
		if (val < defVal - DELTA)
		{
			flash++;
			pause =0;
		} else
		{
			pause++;
		}
		
		if (pause > 0 && flash > 0)
		{
			uint8_t pom;
			if (flash < 3)
			{
				pom = 0b01;
			}
			else
			{
				pom = 0b11;
			}
			num |= pom << (6-( 2*step));
			step = (step + 1) % offset;
			flash = 0;
		} else if (pause > 2 && num > 0)
		{
			char c = convertIntToMorseChar(num);
			num = 0;
			printf("%c",c);
			step = 0;
		} else if (pause == 7)
		{
			printf(" ");
		} else if (pause > 7)
		{
			break;
		}
		delay_ms(ELEMENT_GAP);
	}
	printf("\n\r");
}

void Morse::TransmitData(void){
	char buffer[255];
	int i = 0;
	
	char c;
	do 
	{
		while (uart_ptr->charWasTaken())
		{
			delay_ms(10);
			if (stopFunction)
			{
				return;
			}
		}
		c = uart_ptr->getLastChar();
		if ((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z') || c == ' ')
		{
			buffer[i++] = c;
		}
		else if ((c == '\b' || c == 8) && i < 0)
		{
			printf("Backspace\n\r");
			buffer[i--] = 0;
		}
		uart_ptr->charWasTaken(true);
		_delay_ms(50);
	} while (i < 255 && c != '\n');
	delay_ms(ELEMENT_GAP);
	for (int j = 0; j < i; j++)
	{
		if (stopFunction)
		{
			return;
		}
		c = buffer[j];
		if (c == ' ')
		{
			delay_ms(WORD_GAP);
			continue;
		}
		uint8_t sign = convertCharToMorseInt(c);
		showSign(sign);
		delay_ms(CHAR_GAP);
	}
}

void Morse::showSign(uint8_t sign){
	for (int8_t i = 6; i >= 0; i-=2)
	{
		uint8_t pom = sign>>i;
		pom &= 0b00000011;
		if (pom == 0)
		{
			return;
		} else if (pom == DASH_MORSE)
		{
			this->delay_ms(ELEMENT_GAP);
			this->rgb_ptr->set(white);
			this->delay_ms(DASH_DURATION);
		} else
		{
			this->delay_ms(ELEMENT_GAP);
			this->rgb_ptr->set(white);
			this->delay_ms(DOT_DURATION);
		}
		this->rgb_ptr->set(black);
	}
}

void Morse::delay_ms(int ms)
{
	for(int i=0; i<ms; i++) _delay_ms(1);
}

void Morse::setStop(bool stop){
	stopFunction = stop;
}

bool Morse::getStop(void){
	return stopFunction;
}

char Morse::convertIntToMorseChar(uint8_t val){
	switch(val){
		case a_morse:
		return 'A';
		case b_morse:
		return 'B';
		case c_morse:
		return 'C';
		case d_morse:
		return 'D';
		case e_morse:
		return 'E';
		case f_morse:
		return 'F';
		case g_morse:
		return 'G';
		case h_morse:
		return 'H';
		case i_morse:
		return 'I';
		case j_morse:
		return 'J';
		case k_morse:
		return 'K';
		case l_morse:
		return 'L';
		case m_morse:
		return 'M';
		case n_morse:
		return 'N';
		case o_morse:
		return 'O';
		case p_morse:
		return 'P';
		case q_morse:
		return 'Q';
		case r_morse:
		return 'R';
		case s_morse:
		return 'S';
		case t_morse:
		return 'T';
		case u_morse:
		return 'U';
		case v_morse:
		return 'V';
		case w_morse:
		return 'W';
		case x_morse:
		return 'X';
		case y_morse:
		return 'Y';
		case z_morse:
		return 'Z';
		default:
		return 0;
	}
}

uint8_t Morse::convertCharToMorseInt(char val){
	switch (val)
	{
		case 'a':
		case 'A':
			return a_morse;
		case 'b':
		case 'B':
		return b_morse;
		case 'c':
		case 'C':
		return c_morse;
		case 'd':
		case 'D':
		return d_morse;
		case 'e':
		case 'E':
		return e_morse;
		case 'f':
		case 'F':
		return f_morse;
		case 'g':
		case 'G':
		return g_morse;
		case 'h':
		case 'H':
		return h_morse;
		case 'i':
		case 'I':
		return i_morse;
		case 'j':
		case 'J':
		return j_morse;
		case 'k':
		case 'K':
		return k_morse;
		case 'l':
		case 'L':
		return l_morse;
		case 'm':
		case 'M':
		return m_morse;
		case 'n':
		case 'N':
		return n_morse;
		case 'o':
		case 'O':
		return o_morse;
		case 'p':
		case 'P':
		return p_morse;
		case 'q':
		case 'Q':
		return q_morse;
		case 'r':
		case 'R':
		return r_morse;
		case 's':
		case 'S':
		return s_morse;
		case 't':
		case 'T':
		return t_morse;
		case 'u':
		case 'U':
		return u_morse;
		case 'v':
		case 'V':
		return v_morse;
		case 'w':
		case 'W':
		return w_morse;
		case 'x':
		case 'X':
		return x_morse;
		case 'y':
		case 'Y':
		return y_morse;
		case 'z':
		case 'Z':
		return z_morse;	
		default:
			return 0b000000;
	}
}