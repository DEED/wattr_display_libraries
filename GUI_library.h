
// This header file goes with GUI_library.c

#ifndef GUI_LIBRARY_H
#define GUI_LIBRARY_H

enum measurements{
	VOLTAGE,
	CURRENT,
	KWH,
	COST,
	WATTS,
	VOLTAMPS,
	VARS,
	FREQ,
	DEGREES,
	PFACTOR
};

void draw_selection_screen(void);
void initial_screen(void);
void draw_device_info(void);
void draw_measurements_screen(int cursor_row);
void measurement_todraw(int measurement_number);
void draw_settings_screen(void);
void draw_set_clock_screen(void);
void draw_set_cost_screen(void);
void draw_set_energy_cycles_screen(void);
void draw_set_spike_level_screen(void);
void draw_set_sag_cycles_screen(void);
void set_sag_level_screen(void);

#endif