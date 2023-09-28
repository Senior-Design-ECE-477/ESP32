/**
 * @file screen_controller.h
 * ScreenController header file
 */
#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

// #ifdef LV_LVGL_H_INCLUDE_SIMPLE
// #include "lvgl.h"
// #else
// #include "lvgl/lvgl.h"
// #endif

/**
 * @brief Enum for the types of data.
 */
typedef enum _DataType
{
    one,
    two,
    three
} DataType;

/**
 * @brief ScreenController is a struct that controls the screen. This struct is used in the screen loop and depending on the values will update the screen.
 * @param lock: (bool) If true, data cannot be changed
 * @param type: (DataType) The tag for the data, what is it that is being controlled
 * @param data: (void *) Pointer to any data type
 */
typedef struct _ScreenController
{
    bool lock;
    DataType type;
    void *data;
} ScreenController;

/**
 * @brief Start LVGL, init drivers, and init UI. Then start the loop for the screen.
 * @param controller: (ScreenController *) ScreenController for for thread/task
 */
void runScreenGUI(void *pvParameter);

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void stop();
/**
 * @brief Display the access granted aka accept aka success page
 */
void accepted(int ms);
/**
 * @brief Display the access denied aka error page
 */
void denied(int ms);
/**
 * @brief Display the home page with the lock icon
 */
void home();

#endif /* SCREEN_CONTROLLER_H */