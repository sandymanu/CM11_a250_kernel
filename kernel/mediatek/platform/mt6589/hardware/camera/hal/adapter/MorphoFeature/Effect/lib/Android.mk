LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := libmorpho_effect_engine.a
include $(BUILD_MULTI_PREBUILT)

