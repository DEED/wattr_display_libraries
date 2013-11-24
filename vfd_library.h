/*
 * vfd_library.h
 *
 * Created: 11/11/2013 10:11:17 PM
 *  Author: DJD103
 */ 

#ifndef VFD_LIBRARY_H_
#define VFD_LIBRARY_H_

#define NORITAKE_VFD_RESET_DELAY 500

#include "usart_spi.h"

void vfd_back(void);
void vfd_forward(void);
void vfd_linefeed(void);
void vfd_home(void);
void vfd_carriageReturn(void);
void vfd_setcursor(uint8_t x, uint8_t y);
void vfd_clearscreen(void);
void vfd_cursonOn(void);
void vfd_cursorOff(void);
void vfd_init(void);
void vfd_hardreset(void);
void vfd_command_xy(unsigned x, unsigned y);
void vfd_print(char a);
void vfd_println(char a);
void vfd_crlf(void);
void vfd_printword(char *word);
void vfd_printwordln(char *word);

#endif /* VFD_LIBRARY_H_ */