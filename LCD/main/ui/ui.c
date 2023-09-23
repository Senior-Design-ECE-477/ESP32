// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.2.0
// Project name: lcd1

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////

// SCREEN: ui_MainScreen
void ui_MainScreen_screen_init(void);
lv_obj_t *ui_MainScreen;
lv_obj_t *ui_BackgroundImage;
lv_obj_t *ui_ColorPanel;
lv_obj_t *ui_LockIcon;
lv_obj_t *ui_UnlockIcon;
lv_obj_t *ui_TimeLabel;
lv_obj_t *ui_TitleLabel;
lv_obj_t *ui_AMPMLabel;
lv_obj_t *ui_WifiIcon1Bar;
lv_obj_t *ui_WifiIcon2Bar;
lv_obj_t *ui_WifiIcon3Bar;
lv_obj_t *ui_HelloLabel;
lv_obj_t *ui_FirstNameLabel;
lv_obj_t *ui_LastNameLabel;
lv_obj_t *ui____initial_actions0;
const lv_img_dsc_t *ui_imgset_lcd_bg[2] = {&ui_img_lcd_bg1_png, &ui_img_lcd_bg2_png};
const lv_img_dsc_t *ui_imgset_wifi_icon[3] = {&ui_img_wifi_icon1_png, &ui_img_wifi_icon2_png, &ui_img_wifi_icon3_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    // lv_disp_t *dispp = lv_disp_get_default();
    // lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    // lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    // ui____initial_actions0 = lv_obj_create(NULL, NULL);
    lv_scr_load(ui_MainScreen);
    // lv_disp_load_scr(ui_MainScreen);
}
