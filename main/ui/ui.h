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

    // #include "lvgl.h"
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
     * @brief
     */
    void ui_FadeGreen_Animation(lv_obj_t *TargetObject, int delay);
    /**
     * @brief
     */
    void ui_TimeAndIconsToTop_Animation(int delay, int reverse_delay);
    /**
     * @brief
     */
    void ui_Welcome_Animation(int delay);
    /**
     * @brief
     */
    void ui_ShowKeypad_Animation(int delay);
    /**
     * @brief
     */
    void ui_ShakeKeypad_Animation(int delay);
    /**
     * @brief
     */
    void ui_Unlock();
    /**
     * @brief
     */
    void ui_Lock();
    /**
     * @brief
     */
    WifiBar ui_GetWifiBarNumber();
    /**
     * @brief
     */
    void ui_SetWifiBarNumber(WifiBar bars);
    /**
     * @brief
     */
    void ui_ShakeLock_Animation(int delay);

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
    LV_IMG_DECLARE(ui_img_lcd_bg1_png);    // assets\lcd_bg1.png

    /* END INTERNAL ONLY ----------------------------------------------------------------------------------------------------- */

    /**
     * @brief
     */
    void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _LCD_UI_H */
