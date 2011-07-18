#ifndef LOG_H
#define LOG_H

#include <android/log.h>

static bool logging = true;

#define LOG_TAG "baby-engine"
#define LOGD(...) if (logging) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static void setLogging(bool on) {
	logging = on;
}

#endif