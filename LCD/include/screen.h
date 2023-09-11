/**
 * @file screen.h
 * ScreenController header file
 */
#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#ifdef __cplusplus
extern "C"
{
#endif /* C++ */

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#include "lv_port_disp.h"
#else
#include "lvgl/lvgl.h"
#endif

// Singleton class
class ScreenController
{
public:
    ScreenController();
    /**
     * @brief Start the screen refresh loop
    */
    static void start(void *pvParameter);
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

private:
    static void lv_tick_task(void *arg);

};

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* SCREEN_CONTROLLER_H */