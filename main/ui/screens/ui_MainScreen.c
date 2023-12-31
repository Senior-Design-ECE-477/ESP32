/**
 * @file ui_MainScreen.c
 * Initialize all widgets, set their styles, and set their parent. Generates the screen that displays everything. Wifi bar getter and setter.
 */
#include <string.h>
#include "../ui.h"
static const char *TAG = "ui";

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

    ui_LockIcon = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_LockIcon, &ui_img_locked_png);
    lv_obj_set_width(ui_LockIcon, 64);  /// 1
    lv_obj_set_height(ui_LockIcon, 64); /// 1
    lv_obj_set_x(ui_LockIcon, 88);
    lv_obj_set_y(ui_LockIcon, 28);
    // lv_obj_align(ui_LockIcon, NULL, LV_ALIGN_CENTER, 0, -100);

    ui_UnlockIcon = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_UnlockIcon, &ui_img_unlocked_png);
    lv_obj_set_width(ui_UnlockIcon, 64);  /// 1
    lv_obj_set_height(ui_UnlockIcon, 64); /// 1
    lv_obj_set_hidden(ui_UnlockIcon, true);
    lv_obj_set_x(ui_UnlockIcon, 88);
    lv_obj_set_y(ui_UnlockIcon, 28);
    // lv_obj_align(ui_UnlockIcon, NULL, LV_ALIGN_CENTER, 0, -100);

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
    lv_obj_set_hidden(ui_WifiIcon2Bar, true);

    ui_WifiIconNoBar = lv_img_create(ui_ColorPanel, NULL);
    lv_img_set_src(ui_WifiIconNoBar, &ui_img_wifi_icon0_png);
    lv_obj_set_width(ui_WifiIconNoBar, 32);  /// 1
    lv_obj_set_height(ui_WifiIconNoBar, 32); /// 1
    lv_obj_align(ui_WifiIconNoBar, NULL, LV_ALIGN_CENTER, 94, -138);

    ui_WelcomeLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_WelcomeLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_WelcomeLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_WelcomeLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_WelcomeLabel, "Welcome\nback");
    lv_obj_add_style(ui_WelcomeLabel, LV_OBJ_PART_MAIN, &text30Style);
    lv_obj_align(ui_WelcomeLabel, NULL, LV_ALIGN_CENTER, 0, -30);
    lv_obj_set_auto_realign(ui_WelcomeLabel, true);

    ui_FirstNameLabel = lv_label_create(ui_ColorPanel, NULL);
    lv_obj_set_width(ui_FirstNameLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_FirstNameLabel, LV_SIZE_CONTENT); /// 1
    lv_label_set_align(ui_FirstNameLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(ui_FirstNameLabel, "Setul");
    lv_obj_add_style(ui_FirstNameLabel, LV_OBJ_PART_MAIN, &text40Style);
    lv_obj_align(ui_FirstNameLabel, NULL, LV_ALIGN_CENTER, 0, 50);
    lv_obj_set_auto_realign(ui_FirstNameLabel, true);

    // ui_LastNameLabel = lv_label_create(ui_ColorPanel, NULL);
    // lv_obj_set_width(ui_LastNameLabel, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height(ui_LastNameLabel, LV_SIZE_CONTENT); /// 1
    // lv_label_set_align(ui_LastNameLabel, LV_LABEL_ALIGN_CENTER);
    // lv_label_set_text(ui_LastNameLabel, "Parekh");
    // lv_obj_add_style(ui_LastNameLabel, LV_OBJ_PART_MAIN, &text40Style);
    // lv_obj_align(ui_LastNameLabel, NULL, LV_ALIGN_CENTER, 0, 60);
    // lv_obj_set_auto_realign(ui_LastNameLabel, true);

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

WifiBar ui_GetWifiBarNumber()
{
    if (!lv_obj_get_hidden(ui_WifiIcon1Bar))
    {
        return OneBar;
    }
    else if (!lv_obj_get_hidden(ui_WifiIcon2Bar))
    {
        return TwoBars;
    }
    else if (!lv_obj_get_hidden(ui_WifiIcon3Bar))
    {
        return ThreeBars;
    }
    else
    {
        return NoBars;
    }
}

void ui_SetWifiBarNumber(WifiBar bar)
{
    if (ui_GetWifiBarNumber() == bar)
    {
        return;
    }

    switch (bar)
    {
    case OneBar:
        ESP_LOGI(TAG, "OneBar");
        lv_obj_set_hidden(ui_WifiIcon1Bar, false);
        lv_obj_set_hidden(ui_WifiIcon2Bar, true);
        lv_obj_set_hidden(ui_WifiIcon3Bar, true);
        lv_obj_set_hidden(ui_WifiIconNoBar, true);
        break;
    case TwoBars:
        lv_obj_set_hidden(ui_WifiIcon1Bar, true);
        lv_obj_set_hidden(ui_WifiIcon2Bar, false);
        lv_obj_set_hidden(ui_WifiIcon3Bar, true);
        lv_obj_set_hidden(ui_WifiIconNoBar, true);
        ESP_LOGI(TAG, "TwoBars");
        break;
    case ThreeBars:
        lv_obj_set_hidden(ui_WifiIcon1Bar, true);
        lv_obj_set_hidden(ui_WifiIcon2Bar, true);
        lv_obj_set_hidden(ui_WifiIcon3Bar, false);
        lv_obj_set_hidden(ui_WifiIconNoBar, true);
        ESP_LOGI(TAG, "ThreeBars");
        break;
    default:
        lv_obj_set_hidden(ui_WifiIcon1Bar, true);
        lv_obj_set_hidden(ui_WifiIcon2Bar, true);
        lv_obj_set_hidden(ui_WifiIcon3Bar, true);
        lv_obj_set_hidden(ui_WifiIconNoBar, false);
        ESP_LOGI(TAG, "NoBars");
        break;
    }
}

void ui_UpdateDateTime(const struct tm time_info, bool twelve_hour)
{
    char time[6] = "12:59\0"; // 00:00
    char ampm[3] = "AM\0";
    // static const char *DAY_OF_WEEK[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    // static const char *MONTH[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Set first two character to hour value
    if (twelve_hour & (time_info.tm_hour > 12))
    {
        time[0] = (abs(time_info.tm_hour - 12) / 10) + '0'; // Tens hour
        time[1] = (abs(time_info.tm_hour - 12) % 10) + '0'; // Ones hour
    }
    else
    {
        time[0] = (time_info.tm_hour / 10) + '0'; // Tens hour
        time[1] = (time_info.tm_hour % 10) + '0'; // Ones hour
    }
    // Set last two character to minute value
    time[2] = ':';                           // :
    time[3] = (time_info.tm_min / 10) + '0'; // Tens min
    time[4] = (time_info.tm_min % 10) + '0'; // Ones min

    // Set hour to 12 if 00
    if ((time[0] == '0') & (time[1] == '0'))
    {
        time[0] = '1';
        time[1] = '2';
    }
    // Set set leading character to space if it is zero
    else if (time[0] == '0')
    {
        time[0] = '‎'; // 32 for space or zero-width: '[U+200E]'
    }

    // Edit time if time has changed
    if (strcmp(lv_label_get_text(ui_TimeLabel), time) != 0)
    {
        lv_label_set_text(ui_TimeLabel, time);
        lv_label_set_text(ui_TopTimeLabel, time);

        // Update AMPM Label
        if (time_info.tm_hour > 11)
        {
            ampm[0] = 'P';
        }
        else
        {
            ampm[0] = 'A';
        }
        if (strcmp(lv_label_get_text(ui_AMPMLabel), ampm) != 0)
        {
            lv_label_set_text(ui_AMPMLabel, ampm);
        }

        ESP_LOGI(TAG, "Time set to %s", time);
    }

    // free(time);
}

void ui_setName(char *name)
{
    lv_label_set_text(ui_FirstNameLabel, name);
}