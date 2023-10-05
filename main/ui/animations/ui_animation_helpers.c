/**
 * @file ui_animations_helpers.c
 * Implementation of helpers for ui_animations. Contains callbacks for color and opacity changes for each style.
 */
#include "ui_animation_helpers.h"

// Lerp hex colors and get the value at a certain step
int32_t _ui_getColorLerpAtStep(int32_t initial_color, int32_t final_color, int curr_step)
{
    // Get initial color and set RGB
    int initialRed = (initial_color >> 16) & 0xFF;
    int initialGreen = (initial_color >> 8) & 0xFF;
    int initialBlue = initial_color & 0xFF;

    // Get RGB for final color
    int finalRed = (final_color >> 16) & 0xFF;
    int finalGreen = (final_color >> 8) & 0xFF;
    int finalBlue = final_color & 0xFF;

    // Generate new color
    // ((100 - 1 - v) * initialRed + v * finalRed) / (100 - 1)
    int newRed = ((ANIM_MAX_VALUE - 1 - curr_step) * initialRed + curr_step * finalRed) / (ANIM_MAX_VALUE - 1);
    int newGreen = ((ANIM_MAX_VALUE - 1 - curr_step) * initialGreen + curr_step * finalGreen) / (ANIM_MAX_VALUE - 1);
    int newBlue = ((ANIM_MAX_VALUE - 1 - curr_step) * initialBlue + curr_step * finalBlue) / (ANIM_MAX_VALUE - 1);
    int32_t newColor = (newRed << 16) | (newGreen << 8) | newBlue;

    return newColor;
}

void _ui_anim_callback_set_color_green(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_color_t initial = lv_obj_get_style_bg_color(obj, LV_OBJ_PART_MAIN);
    int32_t initialColorHex = lv_color_to32(initial);
    int32_t newColorHex = _ui_getColorLerpAtStep(initialColorHex, 0x66FF00, value);

    // Set new color
    lv_style_set_bg_color(&colorPanelStyle, LV_STATE_DEFAULT, lv_color_hex(newColorHex));
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &colorPanelStyle);
}

void _ui_anim_callback_set_color_red(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_color_t initial = lv_obj_get_style_bg_color(obj, LV_OBJ_PART_MAIN);
    int32_t initialColorHex = lv_color_to32(initial);
    int32_t newColorHex = _ui_getColorLerpAtStep(initialColorHex, 0xFF0000, value);

    // Set new color
    lv_style_set_bg_color(&colorPanelStyle, LV_STATE_DEFAULT, lv_color_hex(newColorHex));
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &colorPanelStyle);
}

void _ui_anim_callback_set_color_black(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_color_t initial = lv_obj_get_style_bg_color(obj, LV_OBJ_PART_MAIN);
    int32_t initialColorHex = lv_color_to32(initial);
    int32_t newColorHex = _ui_getColorLerpAtStep(initialColorHex, 0x000000, value);

    // Set new color
    lv_style_set_bg_color(&colorPanelStyle, LV_STATE_DEFAULT, lv_color_hex(newColorHex));
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &colorPanelStyle);
}

// text
void _ui_anim_callback_set_text48_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_text_opa(&text48Style, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &text48Style);
}

void _ui_anim_callback_set_text40_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_text_opa(&text40Style, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &text40Style);
}

void _ui_anim_callback_set_text30_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_text_opa(&text30Style, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &text30Style);
}

void _ui_anim_callback_set_text30KP_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_text_opa(&text30StyleKP, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &text30StyleKP);
}

void _ui_anim_callback_set_text18_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_text_opa(&text18Style, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &text18Style);
}

void _ui_anim_callback_set_text18top_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_text_opa(&text18TopStyle, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &text18TopStyle);
}

void _ui_anim_callback_set_text_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_text_opa(&textStyle, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &textStyle);
}

void _ui_anim_callback_set_keypad_opacity(lv_obj_t *obj, lv_anim_value_t value)
{
    lv_style_set_opa_scale(&keypadPanelStyle, LV_STATE_DEFAULT, value);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &keypadPanelStyle);
}