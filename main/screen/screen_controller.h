/**
 * @file screen_controller.h
 * ScreenController header file
 */
#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

/**
 * @brief Start LVGL, init drivers, and init UI. Then start the loop for the screen.
 * @param controller: (ScreenController *) ScreenController for for thread/task
 */
void runScreenGUI(void *pvParameter);

#endif /* SCREEN_CONTROLLER_H */