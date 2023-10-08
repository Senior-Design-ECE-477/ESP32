SET(SOURCES pwm_controller.c ntp_time.c wifi.c system.c motor.c)

add_library(utils ${SOURCES})
