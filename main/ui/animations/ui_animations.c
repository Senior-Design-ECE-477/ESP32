
#include "../ui.h"
#include "ui_animation_helpers.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/*
///////////////////////////////
////// ANIMATION TEMPLATE /////
///////////////////////////////

////// INITIALIZE AN ANIMATION //////

lv_anim_t a;
lv_anim_init(&a);

////// MANDATORY SETTINGS //////

// Set the "animator" function
lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_color_green);
// Set the "animator" function
lv_anim_set_var(&a, TargetObject);
// Length of the animation [ms]
lv_anim_set_time(&a, ANIM_DURATION_MS);
// Set start and end values. E.g. 0, 150
lv_anim_set_values(&a, 0, ANIM_MAX_VALUE);

////// OPTIONAL SETTINGS //////

// Time to wait before starting the animation [ms]
lv_anim_set_delay(&a, delay);
// Set path (curve). Default is linear
lv_anim_set_path(&a, &path);
// Set a callback to call when animation is ready.
lv_anim_set_ready_cb(&a, ready_cb);
// Set a callback to call when animation is started (after delay).
lv_anim_set_start_cb(&a, start_cb);
// Play the animation backward too with this duration. Default is 0 (disabled) [ms]
lv_anim_set_playback_time(&a, ANIM_DURATION_MS);
// Delay before playback. Default is 0 (disabled) [ms]
lv_anim_set_playback_delay(&a, ANIM_DURATION_MS / 10);
// Number of repetitions. Default is 1.  LV_ANIM_REPEAT_INFINIT for infinite repetition
lv_anim_set_repeat_count(&a, wait_time);
// Delay before repeat. Default is 0 (disabled) [ms]
lv_anim_set_repeat_delay(&a, wait_time);
// true (default): apply the start vale immediately, false: apply start vale after delay when then anim. really starts.
lv_anim_set_early_apply(&a, true / false);
// START THE ANIMATION
lv_anim_start(&a); // Start the animation

*/

void ui_FadeGreen_Animation(lv_obj_t *obj, int delay)
{
    // Init
    lv_anim_t a;
    lv_anim_init(&a);

    // Mandatory
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_color_green);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, ANIM_DURATION_500MS);
    lv_anim_set_values(&a, 0, ANIM_MAX_VALUE);

    // Optional
    lv_anim_set_delay(&a, delay);

    // Start
    lv_anim_start(&a);

    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_color_black);
    lv_anim_set_delay(&a, delay + ANIM_DURATION_500MS);
    lv_anim_start(&a);
}

void ui_TimeAndIconsToTop_Animation(int delay, int reverse_delay)
{
    // Init
    lv_anim_t a;
    lv_anim_init(&a);

    // TIME ANIM
    // Fade out big middle time
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text48_opacity);
    lv_anim_set_var(&a, ui_TimeLabel);
    lv_anim_set_time(&a, ANIM_DURATION_250MS);
    lv_anim_set_values(&a, 255, 0);
    lv_anim_set_delay(&a, delay);
    if (reverse_delay >= 0)
    {
        lv_anim_set_playback_time(&a, ANIM_DURATION_250MS);
        lv_anim_set_playback_delay(&a, reverse_delay);
    }
    lv_anim_start(&a);

    // Fade in small top time
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text18top_opacity);
    lv_anim_set_var(&a, ui_TopTimeLabel);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_start(&a);

    // Fade out AMPM
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text_opacity);
    lv_anim_set_var(&a, ui_AMPMLabel);
    lv_anim_set_values(&a, 255, 0);
    lv_anim_start(&a);

    // LOCK ICON ANIM
    // Move y
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_var(&a, ui_LockIcon);
    lv_anim_set_time(&a, ANIM_DURATION_500MS);
    lv_anim_set_values(&a, lv_obj_get_y(ui_LockIcon), -8);
    if (reverse_delay >= 0)
    {
        lv_anim_set_playback_time(&a, ANIM_DURATION_500MS);
        lv_anim_set_playback_delay(&a, reverse_delay);
    }
    lv_anim_start(&a);

    // Move x
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_values(&a, lv_obj_get_x(ui_LockIcon), -8);
    lv_anim_start(&a);

    // Scale by 1/2
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_zoom);
    lv_anim_set_values(&a, 256, 128);
    lv_anim_start(&a);

    // UNLOCK ICON ANIM
    // Move y
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_var(&a, ui_UnlockIcon);
    lv_anim_set_values(&a, lv_obj_get_y(ui_UnlockIcon), -8);
    lv_anim_start(&a);

    // Move x
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_values(&a, lv_obj_get_x(ui_UnlockIcon), -8);
    lv_anim_start(&a);

    // Scale by 1/2
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_zoom);
    lv_anim_set_values(&a, 256, 128);
    lv_anim_start(&a);
}

void ui_ShakeLock_Animation(int delay)
{
    // Init
    lv_anim_t a;
    lv_anim_init(&a);

    // COLOR ANIM
    // SHAKE ANIM
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&a, ui_LockIcon);
    lv_anim_set_time(&a, 30);
    lv_anim_set_values(&a, 88, 96);
    lv_anim_set_playback_time(&a, 30);
    lv_anim_set_repeat_count(&a, 15);
    lv_anim_set_delay(&a, delay);
    lv_anim_start(&a);
}

void ui_Welcome_Animation(int delay)
{
    ui_TimeAndIconsToTop_Animation(delay, 2500 + 750);

    // Init
    lv_anim_t a;
    lv_anim_init(&a);

    // TEXT ANIM
    // Fade out title
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text18_opacity);
    lv_anim_set_var(&a, ui_TitleLabel);
    lv_anim_set_time(&a, ANIM_DURATION_250MS);
    lv_anim_set_values(&a, 255, 0);
    lv_anim_set_delay(&a, delay + 250);
    lv_anim_set_playback_time(&a, ANIM_DURATION_500MS);
    lv_anim_set_playback_delay(&a, 2500 + 250);
    lv_anim_start(&a);

    // Fade in welcome
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text30_opacity);
    lv_anim_set_var(&a, ui_WelcomeLabel);
    lv_anim_set_time(&a, ANIM_DURATION_500MS);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_set_playback_time(&a, ANIM_DURATION_250MS);
    lv_anim_set_playback_delay(&a, 2500);
    lv_anim_start(&a);

    // Fade in first name
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text40_opacity);
    lv_anim_set_var(&a, ui_FirstNameLabel);
    lv_anim_start(&a);

    // Fade in last name
    lv_anim_set_var(&a, ui_LastNameLabel);
    lv_anim_start(&a);
}

void ui_ShowKeypad_Animation(int delay)
{
    ui_TimeAndIconsToTop_Animation(delay, -1);

    // Init
    lv_anim_t a;
    lv_anim_init(&a);

    // TEXT ANIM
    // Fade out title
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text18_opacity);
    lv_anim_set_var(&a, ui_TitleLabel);
    lv_anim_set_time(&a, ANIM_DURATION_250MS);
    lv_anim_set_values(&a, 255, 0);
    lv_anim_set_delay(&a, delay);
    lv_anim_start(&a);

    // Fade in keypad
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_keypad_opacity);
    lv_anim_set_var(&a, ui_KeypadPanel);
    lv_anim_set_time(&a, ANIM_DURATION_500MS);
    lv_anim_set_values(&a, 0, 255);
    lv_anim_set_delay(&a, delay + 250);
    lv_anim_start(&a);

    // Fade in passcode label
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)_ui_anim_callback_set_text30KP_opacity);
    lv_anim_set_var(&a, ui_PasscodeLabel);
    lv_anim_start(&a);
}

void ui_ShakeKeypad_Animation(int delay)
{
    // Init
    lv_anim_t a;
    lv_anim_init(&a);
    lv_coord_t initialX = lv_obj_get_x(ui_KeypadPanel);

    // SHAKE ANIM
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&a, ui_KeypadPanel);
    lv_anim_set_time(&a, 30);
    lv_anim_set_values(&a, initialX, initialX + 8);
    lv_anim_set_playback_time(&a, 30);
    lv_anim_set_repeat_count(&a, 15);
    lv_anim_set_delay(&a, delay);
    lv_anim_start(&a);
}

void ui_Unlock()
{
    // Hide locked
    lv_obj_set_hidden(ui_LockIcon, true);
    // Show unlocked
    lv_obj_set_hidden(ui_UnlockIcon, false);
}

void ui_Lock()
{
    // Show locked
    lv_obj_set_hidden(ui_LockIcon, false);
    // Hide unlocked
    lv_obj_set_hidden(ui_UnlockIcon, true);
}