/*
*
* Wattr GUI library 
* Written by D. Dichek
*
* The purpose of this library is to build a GUI for the Noritake VFD
* This library relies heavily on the VFD library written for the Noritake GU128X32D-7003
* See vfd_library.c and vfd_library.h for details on that. 
*
* Include this library to access functions such as draw_select_screen() and draw_device_info() etc.
*
* A map of the screens generated by this code is available in a blog post by Daniel. Email him, and he'll be happy to send it to you
*/

#include <util/delay.h>
#include "vfd_library.h"

//Call this function when the device first turns on. This draws the device info screen for a set amount of time, and then the measurements screen
void initial_screen(){
	vfd_init();			 // Just to make sure the VFD has been configured. vfd_init() checks to see if the screen has already been initialized.
	draw_device_info();	 // Draw the device info screen
	_delay_ms(4000);			 // Wait 4 seconds
	draw_measurements_screen(); // Draws the measurements screen	
}

// Draws the selection screen and contains the logic for navigating to subsequent screens 
void draw_selection_screen(){
	/*
	draw:
	> Measurements
	  Settings
	  Device Info
	  
	the > is the cursor. When the cursor is next to a screen name, the screen can be selected:
	  
	if(button_center || button_right)
		draw the screen that is currently being selected
	
	if(encoder_CCW || button_down)
		move the cursor down by one element
	if(encoder_CW || button_up)
		move the cursor up by one element
	*/
	
	
}

void draw_device_info(){
	/*
	This is a static screen. It only changes when the device is re-cal'd or the firmware is changed
	
	draw:
	AC Power Analyzer
	V 1.0 - 11/3/2013	//(firmware rev date)
	Cal: 11/10/2013		//(cal date)
	TL.AH.DD.BM.MV'13
	*/
	
	vfd_printwordln("AC Power Analyzer");
	vfd_printwordln("V1.0 - 11/21/2013");
	vfd_printwordln("Cal: 11/24/2013");
	vfd_printwordln("TL.AH.DD.BM.MV'13");
	
	/*
	if(button_back || button_left)
		draw_selection_screen();
	*/
}

// This function describes how the entire measurements screen is navigated/drawn
// It will likely be broken up into many different functions
void draw_measurements_screen(int cursor_row){
	/*
	draw (number of element to left, element to right. number of element not drawn, for reference only):
	0: (rms V) V
	1: (rms A) A
	2: (kWh)   kWh      
	3: (cost)  $
	4: (re pwr) W
	5: (im pwr) VA
	6: (ap pwr) VAR
	7: (freq)   Hz
	8: (ph ang) deg
	9: PF: (pwr fact) 
	
	Only 4 lines can be drawn at once. Position of the "cursor" must be sensed. 
	
	How to draw the measurement sceen given a cursor position:
	for(int i = cursor_row; i < cursor_row + 3; i++){
		draw_measurement(i);
	}
	
	struct measurement_todraw{
		double voltage;
		double current;
		double kwh;
		double cost;
		double watts;
		double voltamps;
		double vars;
		double freq;
		double degrees;
		double pfactor
	}
	
	int cursor_row = 0; // sets y position of cursor at top of screen
	if(encoder_CCW || button_down && cursor_row != 6)	//
		cursor_row++;
	if(encoder_CW || button_up && cursor_row != 0)
		cursor_row--;
	if(button_back || button_left)
		draw_selection_screen();
	*/
	
}

// This function takes in the number of the measurement to draw, and should probably take in *where* to draw it. 
void measurement_todraw(int measurement_number){
	switch(measurement_number){
		case 0 :
			//get the voltage measurement, convert to to string, print with vfd_printwordln. do this for all cases.
		case 1 :
			//draw measurement.current
		case 2 :
			// draw measurement.kwh
		case 3: 
			// draw measurement.cost
		case 4: 
			// draw measurement.watts
		case 5:
			// draw measurement.voltamps
		case 6: 
			// draw measurement.vars
		case 7:
			// draw measurement.freq
		case 8: 
			// draw measurement.degrees
		case 9:
			// draw measurement.pfactor
	}
}

void draw_settings_screen(void){
	/*
	draw:
	>Set Clock
	 Set Cost per kWh
	 Reset kWh
	 Toggle +enegy only
	 Set eneg cycles
	 Set spike level
	 Set sag level
	 Set sag cycles
	*/
}

