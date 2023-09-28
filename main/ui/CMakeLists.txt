SET(SOURCES screens/ui_MainScreen.c
    ui.c
    components/ui_comp_hook.c
    animations/ui_animation_helpers.c
    animations/ui_animations.c
    images/ui_img_lcd_bg2_png.c
    images/ui_img_locked_png.c
    images/ui_img_unlocked_png.c
    images/ui_img_wifi_icon1_png.c
    images/ui_img_wifi_icon2_png.c
    images/ui_img_wifi_icon3_png.c
    images/ui_img_lcd_bg1_png.c)

add_library(ui ${SOURCES})
