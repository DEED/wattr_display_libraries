
// This header file goes with GUI_library.c

#ifndef GUI_LIBRARY_H
#define GUI_LIBRARY_H


void draw_selection_screen(void);
void initial_screen(void);
void draw_device_info(void);
void draw_measurements_screen(int cursor_row);
void measurement_todraw(int measurement_number);
void draw_settings_screen(void);

#endif