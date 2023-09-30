/**
 * @file realtime.h
 * All realtime or multi-component project-specific functions header file
 */
#ifndef _REALTIME_H
#define _REALTIME_H

/**
 * @brief
 */
void entryEventISR();

/**
 * @brief
 */
void updateWifiState();

/**
 * @brief
 */
void checkAccess();

/**
 * @brief
 */
void systemSleep();

/**
 * @brief
 */
void systemWake();

/**
 * @brief
 */
void runWifiTask();

#endif /* _REALTIME_H */