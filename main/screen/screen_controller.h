/**
 * @file screen_controller.h
 * ScreenController header file
 */
#ifndef _SCREEN_CONTROLLER_H
#define _SCREEN_CONTROLLER_H

/**
 * @brief Start LVGL, init drivers, and init UI. Then start the loop for the screen.
 * @param pvParamter: task parameter
 */
void runScreenGUI(void *pvParameter);

#endif /* _SCREEN_CONTROLLER_H */