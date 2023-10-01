/**
 * @file ui.c
 * Everything UI related definition and ui_init implementation file
 */
#include "ui.h"

///////////////////// VARIABLES ////////////////////
void ui_FadeGreen_Animation(lv_obj_t *TargetObject, int delay);
void ui_TimeAndIconsToTop_Animation(int delay, int reverse_delay);
void ui_Welcome_Animation(int delay);
void ui_ShowKeypad_Animation(int delay);
void ui_ShakeKeypad_Animation(int delay);
void ui_Unlock();
void ui_Lock();
WifiBar ui_GetWifiBarNumber();
void ui_SetWifiBarNumber(WifiBar bars);
void ui_ShakeLock_Animation(int delay);
// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
lv_style_t colorPanelStyle;
lv_style_t keypadPanelStyle;
lv_style_t text48Style;
lv_style_t text40Style;
lv_style_t text30Style;
lv_style_t text30StyleKP;
lv_style_t text18Style;
lv_style_t text18TopStyle;
lv_style_t textStyle;
lv_obj_t *ui_MainScreen;
lv_obj_t *ui_BackgroundImage;
lv_obj_t *ui_ColorPanel;
lv_obj_t *ui_LockIcon;
lv_obj_t *ui_UnlockIcon;
lv_obj_t *ui_TimeLabel;
lv_obj_t *ui_TopTimeLabel;
lv_obj_t *ui_TitleLabel;
lv_obj_t *ui_AMPMLabel;
lv_obj_t *ui_WifiIcon1Bar;
lv_obj_t *ui_WifiIcon2Bar;
lv_obj_t *ui_WifiIcon3Bar;
lv_obj_t *ui_WifiIconNoBar;
lv_obj_t *ui_WelcomeLabel;
lv_obj_t *ui_FirstNameLabel;
lv_obj_t *ui_LastNameLabel;
lv_obj_t *ui_KeypadPanel;
lv_obj_t *ui_PasscodeLabel;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

void ui_init(void)
{
    ui_MainScreen_screen_init();
    // ui____initial_actions0 = lv_obj_create(NULL, NULL);
    lv_scr_load(ui_MainScreen);
}
