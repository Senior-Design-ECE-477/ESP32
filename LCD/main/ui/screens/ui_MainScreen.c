
#include <string.h>
#include "../ui.h"

void ui_MainScreen_screen_init(void)
{
    ui_MainScreen = lv_obj_create(NULL, NULL);
    static lv_style_t backgroundStyle;
    lv_style_init(&backgroundStyle);
    lv_style_set_bg_color(&backgroundStyle, LV_STATE_DEFAULT, lv_color_hex(0x000000));
    lv_obj_add_style(ui_MainScreen, LV_OBJ_PART_MAIN, &backgroundStyle);

    // Text Styles
    lv_style_init(&text48Style);
    lv_style_set_text_color(&text48Style, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_style_set_text_font(&text48Style, LV_STATE_DEFAULT, &lv_font_montserrat_48);

    lv_style_init(&text40Style);
    lv_style_set_text_color(&text40Style, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_style_set_text_font(&text40Style, LV_STATE_DEFAULT, &lv_font_montserrat_40);
    lv_style_set_text_opa(&text40Style, LV_STATE_DEFAULT, 0);

    lv_style_init(&text30Style);
    lv_style_set_text_color(&text30Style, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_style_set_text_font(&text30Style, LV_STATE_DEFAULT, &lv_font_montserrat_30);
    lv_style_set_text_opa(&text30Style, LV_STATE_DEFAULT, 0);

    lv_style_init(&text30StyleKP);
    lv_style_set_text_color(&text30StyleKP, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_style_set_text_font(&text30StyleKP, LV_STATE_DEFAULT, &lv_font_montserrat_30);
    lv_style_set_text_opa(&text30StyleKP, LV_STATE_DEFAULT, 0);

    lv_style_init(&text18Style);
    lv_style_set_text_color(&text18Style, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_style_set_text_font(&text18Style, LV_STATE_DEFAULT, &lv_font_montserrat_18);

    lv_style_init(&text18TopStyle);
    lv_style_set_text_color(&text18TopStyle, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_style_set_text_font(&text18TopStyle, LV_STATE_DEFAULT, &lv_font_montserrat_18);
    lv_style_set_text_opa(&text18TopStyle, LV_STATE_DEFAULT, 0);

    lv_style_init(&textStyle);
    lv_style_set_text_color(&textStyle, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));

    ui_BackgroundImage = lv_img_create(ui_MainScreen, NULL);
    lv_img_set_src(ui_BackgroundImage, &ui_img_lcd_bg2_png);
    lv_obj_set_width(ui_BackgroundImage, 240);  /// 1
    lv_obj_set_height(ui_BackgroundImage, 320); /// 1
    lv_obj_align(ui_BackgroundImage, NULL, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_add_flag(ui_BackgroundImage, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    // lv_obj_clear_flag(ui_BackgroundImage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    // lv_obj_set_style_bg_img_src(ui_BackgroundImage, &TemporaryImage, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ColorPanel = lv_obj_create(ui_BackgroundImage, NULL);
    lv_obj_set_width(ui_ColorPanel, 240);
    lv_obj_set_height(ui_ColorPanel, 320);
    lv_obj_align(ui_ColorPanel, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_style_init(&colorPanelStyle);
    lv_style_set_bg_color(&colorPanelStyle, LV_STATE_DEFAULT, lv_color_hex(0x000000));
    lv_style_set_bg_opa(&colorPanelStyle, LV_STATE_DEFAULT, 125);
    lv_style_set_border_width(&colorPanelStyle, LV_STATE_DEFAULT, 0);
    lv_style_set_radius(&colorPanelStyle, LV_STATE_DEFAULT, 16);
    lv_obj_add_style(ui_ColorPanel, LV_OBJ_PART_MAIN, &colorPanelStyle);
    // lv_obj_clear_flag(ui_ColorPanel, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
    // lv_obj_set_style_local_bg_color(ui_ColorPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_ColorPanel, 125, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LockIcon = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_LockIcon, &ui_img_locked_png);
    lv_obj_set_width(ui_LockIcon, 64);  /// 1
    lv_obj_set_height(ui_LockIcon, 64); /// 1
    lv_obj_align(ui_LockIcon, NULL, LV_ALIGN_CENTER, 0, -100);

    ui_UnlockIcon = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_UnlockIcon, &ui_img_unlocked_png);
    lv_obj_set_width(ui_UnlockIcon, 64);  /// 1
    lv_obj_set_height(ui_UnlockIcon, 64); /// 1
    lv_obj_set_hidden(ui_UnlockIcon, true);
    lv_obj_align(ui_UnlockIcon, NULL, LV_ALIGN_CENTER, 0, -100);
    // lv_obj_add_flag(ui_UnlockIcon, LV_OBJ_FLAG_HIDDEN);                                                                                                                                                                                                         /// Flags
    // lv_obj_clear_flag(ui_UnlockIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags

    ui_TimeLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_TimeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_TimeLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_TimeLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_TimeLabel, "12:59");
    lv_obj_add_style(ui_TimeLabel, LV_OBJ_PART_MAIN, &text48Style);
    lv_obj_align(ui_TimeLabel, NULL, LV_ALIGN_CENTER, 0, -15);
    lv_obj_set_auto_realign(ui_TimeLabel, true);

    ui_TopTimeLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_TopTimeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_TopTimeLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_TopTimeLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_TopTimeLabel, "12:59");
    lv_obj_add_style(ui_TopTimeLabel, LV_OBJ_PART_MAIN, &text18TopStyle);
    lv_obj_align(ui_TopTimeLabel, NULL, LV_ALIGN_OUT_TOP_MID, 0, 34);
    lv_obj_set_auto_realign(ui_TopTimeLabel, true);

    ui_TitleLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_TitleLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_TitleLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_TitleLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_TitleLabel, "TITLE");
    lv_obj_add_style(ui_TitleLabel, LV_OBJ_PART_MAIN, &text18Style);
    lv_obj_align(ui_TitleLabel, NULL, LV_ALIGN_CENTER, 0, 85);
    lv_obj_set_auto_realign(ui_TitleLabel, true);

    ui_AMPMLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_AMPMLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_AMPMLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_AMPMLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_AMPMLabel, "PM");
    lv_obj_add_style(ui_AMPMLabel, LV_OBJ_PART_MAIN, &textStyle);
    lv_obj_align(ui_AMPMLabel, NULL, LV_ALIGN_CENTER, 80, -27);
    lv_obj_set_auto_realign(ui_AMPMLabel, true);

    ui_WifiIcon1Bar = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_WifiIcon1Bar, &ui_img_wifi_icon1_png);
    lv_obj_set_width(ui_WifiIcon1Bar, 32);  /// 1
    lv_obj_set_height(ui_WifiIcon1Bar, 32); /// 1
    lv_obj_align(ui_WifiIcon1Bar, NULL, LV_ALIGN_CENTER, 94, -138);
    lv_obj_set_hidden(ui_WifiIcon1Bar, true);

    ui_WifiIcon2Bar = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_WifiIcon2Bar, &ui_img_wifi_icon2_png);
    lv_obj_set_width(ui_WifiIcon2Bar, 32);  /// 1
    lv_obj_set_height(ui_WifiIcon2Bar, 32); /// 1
    lv_obj_align(ui_WifiIcon2Bar, NULL, LV_ALIGN_CENTER, 94, -138);
    lv_obj_set_hidden(ui_WifiIcon2Bar, true);

    ui_WifiIcon3Bar = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_WifiIcon3Bar, &ui_img_wifi_icon3_png);
    lv_obj_set_width(ui_WifiIcon3Bar, 32);  /// 1
    lv_obj_set_height(ui_WifiIcon3Bar, 32); /// 1
    lv_obj_align(ui_WifiIcon3Bar, NULL, LV_ALIGN_CENTER, 94, -138);

    ui_WelcomeLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_WelcomeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_WelcomeLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_WelcomeLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_WelcomeLabel, "Welcome");
    lv_obj_add_style(ui_WelcomeLabel, LV_OBJ_PART_MAIN, &text30Style);
    lv_obj_align(ui_WelcomeLabel, NULL, LV_ALIGN_CENTER, 0, -75);
    lv_obj_set_auto_realign(ui_WelcomeLabel, true);

    ui_FirstNameLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_FirstNameLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_FirstNameLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_FirstNameLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_FirstNameLabel, "Setul");
    lv_obj_add_style(ui_FirstNameLabel, LV_OBJ_PART_MAIN, &text40Style);
    lv_obj_align(ui_FirstNameLabel, NULL, LV_ALIGN_CENTER, 0, 20);
    lv_obj_set_auto_realign(ui_FirstNameLabel, true);

    ui_LastNameLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_LastNameLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LastNameLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_LastNameLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_LastNameLabel, "Parekh");
    lv_obj_add_style(ui_LastNameLabel, LV_OBJ_PART_MAIN, &text40Style);
    lv_obj_align(ui_LastNameLabel, NULL, LV_ALIGN_CENTER, 0, 60);
    lv_obj_set_auto_realign(ui_LastNameLabel, true);

    ui_KeypadPanel = lv_obj_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_KeypadPanel, 200);
    lv_obj_set_height(ui_KeypadPanel, 60);
    lv_obj_align(ui_KeypadPanel, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_style_init(&keypadPanelStyle);
    lv_style_set_bg_color(&keypadPanelStyle, LV_STATE_DEFAULT, lv_color_hex(0x000000));
    lv_style_set_bg_opa(&keypadPanelStyle, LV_STATE_DEFAULT, 125);
    lv_style_set_border_color(&keypadPanelStyle, LV_STATE_DEFAULT, lv_color_hex(0xFFFFFF));
    lv_style_set_border_opa(&keypadPanelStyle, LV_STATE_DEFAULT, 175);
    lv_style_set_border_width(&keypadPanelStyle, LV_STATE_DEFAULT, 2);
    lv_style_set_radius(&keypadPanelStyle, LV_STATE_DEFAULT, 30);
    lv_style_set_opa_scale(&keypadPanelStyle, LV_STATE_DEFAULT, 0);
    lv_obj_add_style(ui_KeypadPanel, LV_OBJ_PART_MAIN, &keypadPanelStyle);

    ui_PasscodeLabel = lv_label_create(ui_KeypadPanel, NULL);
    lv_obj_set_width(ui_PasscodeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_PasscodeLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_PasscodeLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_PasscodeLabel, "*");
    lv_obj_add_style(ui_PasscodeLabel, LV_OBJ_PART_MAIN, &text30StyleKP);
    lv_obj_align(ui_PasscodeLabel, NULL, LV_ALIGN_CENTER, 0, -1);
    lv_obj_set_auto_realign(ui_PasscodeLabel, true);
}

/*

Animations:
- Fade green
- Fade red
- Fade AMPM and Title labels
- Fade Hello and Name labels
- Move time and both lock images
- Scale keypad box and text




animation on unlock (1 second):

step 1 (0.5s):
background faded to green
rock lock icon to the right by 45 degrees while also changing image to unlocked icon
background faded to normal
on the rock back to normal, move lock to top left and scale down to 1/2

step 2 (0.5s):
time label and ampm label scaled to 1/8 and moved to top middle

step 2.1:
title fades away
hello label and first/last name labels fade in


animation on fail (0.5 seconds):

step 1 (0.5s):
vibrate lock icon
change background to red, then back to normal


*/