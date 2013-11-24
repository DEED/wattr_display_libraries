/*
* Noritake VFD Library
* Written by D. Dichek
* 
* The purpose of this library is to simplify communication with the Noritake VFD
* It is configured to work with a Model GU128x32D-7003, and is based on
* specifications found in Specification No. DS-1144-0001-01
*
* Include this library to access functions such as vfd_refresh(), vfd_print() etc.
*
* Assumes that USART is configured in SPI mode and has been initialized
* If it hasn't been initialized, it will see that and initialize the ports. 
* See vfd_init(void) for that
*
* All functions ported from Noritake itron GU-7000 Code Library. See documentation
* provided by Noritake for additional explanations.
*/

#include "usart_spi.h"
#include "vfd_library.h"
#include <util/delay.h>
#include <string.h>


// not sure how to define these - they are used by the 
#define RESET	//PC28, pin 76
#define OUT		//PB1, pin 20
#define SCK		//PB13, pin 144
#define BUSY	//PA4/PGMN0, pin 77

#define USART_INSTANCE USART0	// The pins that are being used to communicate with the VFD suggest that we're using USART0

// Move the cursor back one position in the current font
void vfd_back(void){
	usart_spi_write_single(USART_INSTANCE, 0x08);
}

// Move the cursor forward one character in the current font
void vfd_forward(void){
	usart_spi_write_single(USART_INSTANCE, 0x09);
}

// Move the cursor down one line
void vfd_linefeed(void){
	usart_spi_write_single(USART_INSTANCE, 0x0a);
}

// Move the cursor to the home position (0,0)
void vfd_home(void){
	usart_spi_write_single(USART_INSTANCE, 0x0b);
}

// Moves the cursor to the beginning of the current line
void vfd_carriageReturn(void){
	usart_spi_write_single(USART_INSTANCE, 0x0d);
}

//NOT COMPLETE
// Sets the cursor to the given position
void vfd_setcursor(uint8_t x, uint8_t y){
	usart_spi_write_single(USART_INSTANCE, 0x1F);
	usart_spi_write_single(USART_INSTANCE, '$');
	vfd_command_xy(x,y);
}

void vfd_command_xy(unsigned x, unsigned y){
	usart_spi_write_single(USART_INSTANCE, x);
	usart_spi_write_single(USART_INSTANCE, x>>8);	// Not Entirely sure why this is here, but it was in the parent code
	y /= 8;
	usart_spi_write_single(USART_INSTANCE, y);
	usart_spi_write_single(USART_INSTANCE, y>>8);
}
// There is also a command_xy1, and it's missing the y /= 8;. Not sure what's going on there


// Clears the screen and moves cursor to home position
void vfd_clearscreen(void){
	usart_spi_write_single(USART_INSTANCE, 0x0C);
}

// Need to replicate functionality of command() function with three arguments
void vfd_cursonOn(void){
	//usart_spi_write_single
}

void vfd_cursorOff(void){
	//usart_spi_write_single
}

// Initializes the VFD module 
void vfd_init(void){
	
	//check if ports have already been initialized
	
	_delay_ms(NORITAKE_VFD_RESET_DELAY);
	initPort();
	
	usart_spi_write_single(USART_INSTANCE, 0x1B);
	usart_spi_write_single(USART_INSTANCE, '@');
}

void initPort(void){
	//port initPort(); function
	// it looks like this in the original code:
	/*
	void initPort() {
		RAISE(RESET);
		RAISE(OUT);
		RAISE(SCK);
		DIRECTION(OUT,1);
		DIRECTION(SCK,1);
		DIRECTION(RESET,1);
		DIRECTION(BUSY,0);
	}
	*/
	ioport_set_pin_level(RESET, true);
	ioport_set_pin_level(OUT, true);
	ioport_set_pin_level(SCK, true);
	ioport_set_pin_dir(OUT, 1);
	ioport_set_pin_dir(SCK, 1);
	ioport_set_pin_dir(RESET, 1);
	ioport_set_pin_dir(BUSY, 0);
}

void vfd_hardreset(void){
	// it looks like this in the original code:
	/*
	void hardReset() {
		initPort();
		LOWER(RESET);
		_delay_ms(2);
		RAISE(RESET);
		_delay_ms(120);
	}
	*/
	initPort();
	ioport_set_pin_level(RESET, false);
	_delay_ms(2);
	ioport_set_pin_level(RESET, true);
	_delay_ms(120);
}

// Prints one character
void vfd_print(char a){
	usart_spi_write_single(USART_INSTANCE, a);
}

// Prints one character, then moves down one line
void vfd_println(char a){
	usart_spi_write_single(USART_INSTANCE, a);
	vfd_crlf();
}

//moves the display cursor down one line and to the leftmost character of the display
void vfd_crlf(void){
	usart_spi_write_single(USART_INSTANCE, '\r');
	usart_spi_write_single(USART_INSTANCE, '\n');
}

// Prints a string.
void vfd_printword(char *word){
	while(*word)
	usart_spi_write_single(USART_INSTANCE, *word++);
}

// Prints a string and moves cursor to the next line
void vfd_printwordln(char *word){
	while(*word){
		usart_spi_write_single(USART_INSTANCE, *word++);
	}
	vfd_crlf();
}


