#ifndef UI_ANIMATION_HELPERS_H
#define UI_ANIMATION_HELPERS_H

#include "../ui.h"

#define ANIM_DURATION_1000MS 1000
#define ANIM_DURATION_500MS 500
#define ANIM_DURATION_250MS 250

#define ANIM_MAX_VALUE 500

int32_t _ui_getColorLerpAtStep(int32_t initial_color, int32_t final_color, int curr_step);
void _ui_anim_callback_set_color_green(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_color_red(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_color_black(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_text48_opacity(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_text40_opacity(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_text30_opacity(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_text30KP_opacity(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_text18_opacity(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_text18top_opacity(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_text_opacity(lv_obj_t *obj, lv_anim_value_t value);
void _ui_anim_callback_set_keypad_opacity(lv_obj_t *obj, lv_anim_value_t value);

#endif