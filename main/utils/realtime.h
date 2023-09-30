/**
 * @file realtime.h
 * All realtime or multi-component project-specific functions header file
 */
#ifndef REALTIME_H
#define REALTIME_H

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

#endif /* REALTIME_H */