/**
 * @file ui.h
 * Everything UI related header file
 */
#ifndef _LCD_UI_H
#define _LCD_UI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <time.h>
#include "esp_log.h"

/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#define LV_SIZE_CONTENT 1

    /**
     * @brief Enum to determine the amount of bars. The four different wifi bar types: OneBar, TwoBars, ThreeBars, and NoBars
     */
    typedef enum _WifiBar
    {
        OneBar,
        TwoBars,
        ThreeBars,
        NoBars
    } WifiBar;
    /**
     * @brief Animation to fade color from current to green
     * @param TargetObject LVGL object to animate the color of
     * @param delay Delay before animation starts
     */
    void ui_FadeGreen_Animation(lv_obj_t *TargetObject, int delay);
    /**
     * @brief Runs 500ms animation to fade away time text, fade in the time at the top
     * and move while scaling the lock icon to the top left.
     * @param delay Delay before animation starts
     * @param reverse_delay Delay before animation starts playing backward, -1 for no playback
     */
    void ui_TimeAndIconsToTop_Animation(int delay, int reverse_delay);
    /**
     * @brief Runs 4500ms animation that fades to a welcome screen and then
     * back to the home screen.
     * @param delay Delay before animation starts
     */
    void ui_Welcome_Animation(int delay);
    /**
     * @brief Runs 500ms animation to fade in the keypad screen.
     * @param delay Delay before animation starts
     */
    void ui_ShowKeypad_Animation(int delay);
    /**
     * @brief Runs 100ms animation that shakes the keypad repeatedly.
     * @param delay Delay before animation starts
     */
    void ui_ShakeKeypad_Animation(int delay);
    /**
     * @brief Hides lock icon and shows unlock icon
     */
    void ui_Unlock();
    /**
     * @brief Hides unlock icon and shows lock icon
     */
    void ui_Lock();
    /**
     * @brief Get the current number of bars showing on the wifi indicator
     */
    WifiBar ui_GetWifiBarNumber();
    /**
     * @brief Set the current number of bars showing on the wifi indicator
     * @param bars Number of bars to show. WifiBar types: OneBar, TwoBars, ThreeBars, or NoBars
     */
    void ui_SetWifiBarNumber(WifiBar bars);
    /**
     * @brief Runs 100ms animation that shakes the lock repeatedly.
     * @param delay Delay before animation starts
     */
    void ui_ShakeLock_Animation(int delay);
    /**
     * @brief Set the text that displays time on the screen.
     * @param time_info A struct of type tm that contains the current time info, must have
     * @param twelve_hour True if time should be set using a 12-hour format, false for 24-hour format
     * day, month, year, hour, and minute
     */
    void ui_UpdateDateTime(const struct tm time_info, bool twelve_hour);

    /* START INTERNAL ONLY ----------------------------------------------------------------------------------------------------- */

    // SCREEN: ui_MainScreen
    void ui_MainScreen_screen_init(void);
    extern lv_style_t colorPanelStyle;
    extern lv_style_t keypadPanelStyle;
    extern lv_style_t text48Style;
    extern lv_style_t text40Style;
    extern lv_style_t text30Style;
    extern lv_style_t text30StyleKP;
    extern lv_style_t text18Style;
    extern lv_style_t text18TopStyle;
    extern lv_style_t textStyle;
    extern lv_obj_t *ui_MainScreen;
    extern lv_obj_t *ui_BackgroundImage;
    extern lv_obj_t *ui_ColorPanel;
    extern lv_obj_t *ui_LockIcon;
    extern lv_obj_t *ui_UnlockIcon;
    extern lv_obj_t *ui_TimeLabel;
    extern lv_obj_t *ui_TopTimeLabel;
    extern lv_obj_t *ui_TitleLabel;
    extern lv_obj_t *ui_AMPMLabel;
    extern lv_obj_t *ui_WifiIcon1Bar;
    extern lv_obj_t *ui_WifiIcon2Bar;
    extern lv_obj_t *ui_WifiIcon3Bar;
    extern lv_obj_t *ui_WifiIconNoBar;
    extern lv_obj_t *ui_WelcomeLabel;
    extern lv_obj_t *ui_FirstNameLabel;
    extern lv_obj_t *ui_LastNameLabel;
    extern lv_obj_t *ui_KeypadPanel;
    extern lv_obj_t *ui_PasscodeLabel;
    // Other
    extern lv_obj_t *ui____initial_actions0;

    // Images
    LV_IMG_DECLARE(ui_img_lcd_bg2_png);    // assets\lcd_bg2.png
    LV_IMG_DECLARE(ui_img_locked_png);     // assets\locked.png
    LV_IMG_DECLARE(ui_img_unlocked_png);   // assets\unlocked.png
    LV_IMG_DECLARE(ui_img_wifi_icon1_png); // assets\wifi_icon1.png
    LV_IMG_DECLARE(ui_img_wifi_icon2_png); // assets\wifi_icon2.png
    LV_IMG_DECLARE(ui_img_wifi_icon3_png); // assets\wifi_icon3.png
    LV_IMG_DECLARE(ui_img_wifi_icon0_png); // assets\wifi_icon0.png
    LV_IMG_DECLARE(ui_img_lcd_bg1_png);    // assets\lcd_bg1.png

    /* END INTERNAL ONLY ----------------------------------------------------------------------------------------------------- */

    /**
     * @brief Called by the edited sc_runScreenGUI function. Initialized the GUI
     * by creating the widget we defined in code. Also sets styles for the widgets.
     */
    void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _LCD_UI_H */
