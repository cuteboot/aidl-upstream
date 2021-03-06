# Copyright 2007 The Android Open Source Project
#
# Copies files into the directory structure described by a manifest

# This tool is prebuilt if we're doing an app-only build.
ifeq ($(TARGET_BUILD_APPS)$(filter true,$(TARGET_BUILD_PDK)),)

LOCAL_PATH:= $(call my-dir)

aidl_static_libraries := libbase libcutils

# Logic shared between aidl and its unittests
include $(CLEAR_VARS)
LOCAL_MODULE := libaidl-common
LOCAL_MODULE_HOST_OS := darwin linux windows

LOCAL_C_INCLUDES := external/gtest/include
LOCAL_CLANG_CFLAGS := -Wall -Werror
# Tragically, the code is riddled with unused parameters.
LOCAL_CLANG_CFLAGS += -Wno-unused-parameter
# yacc dumps a lot of code *just in case*.
LOCAL_CLANG_CFLAGS += -Wno-unused-function
LOCAL_CLANG_CFLAGS += -Wno-unneeded-internal-declaration
# yacc is a tool from a more civilized age.
LOCAL_CLANG_CFLAGS += -Wno-deprecated-register
# yacc also has a habit of using char* over const char*.
LOCAL_CLANG_CFLAGS += -Wno-writable-strings
LOCAL_STATIC_LIBRARIES := $(aidl_static_libraries)

LOCAL_SRC_FILES := \
    aidl.cpp \
    aidl_language.cpp \
    aidl_language_l.l \
    aidl_language_y.y \
    ast_cpp.cpp \
    ast_java.cpp \
    code_writer.cpp \
    generate_cpp.cpp \
    generate_java.cpp \
    generate_java_binder.cpp \
    import_resolver.cpp \
    io_delegate.cpp \
    options.cpp \
    type_cpp.cpp \
    type_java.cpp \
    type_namespace.cpp \

include $(BUILD_HOST_STATIC_LIBRARY)


# aidl executable
include $(CLEAR_VARS)
LOCAL_MODULE := aidl

LOCAL_MODULE_HOST_OS := darwin linux windows
LOCAL_CFLAGS := -Wall -Werror
LOCAL_C_INCLUDES := external/gtest/include
LOCAL_SRC_FILES := main_java.cpp
LOCAL_STATIC_LIBRARIES := libaidl-common $(aidl_static_libraries)
include $(BUILD_HOST_EXECUTABLE)

# aidl-cpp executable
include $(CLEAR_VARS)
LOCAL_MODULE := aidl-cpp

LOCAL_MODULE_HOST_OS := darwin linux windows
LOCAL_CFLAGS := -Wall -Werror
LOCAL_C_INCLUDES := external/gtest/include
LOCAL_SRC_FILES := main_cpp.cpp
LOCAL_STATIC_LIBRARIES := libaidl-common $(aidl_static_libraries)
include $(BUILD_HOST_EXECUTABLE)


# TODO(wiley) Compile these for mac as well after b/22771504
ifeq ($(HOST_OS),linux)
# Unit tests
include $(CLEAR_VARS)
LOCAL_MODULE := aidl_unittests

LOCAL_CFLAGS := -g -DUNIT_TEST -Wall -Werror
# Tragically, the code is riddled with unused parameters.
LOCAL_CLANG_CFLAGS := -Wno-unused-parameter
LOCAL_SRC_FILES := \
    ast_cpp_unittest.cpp \
    ast_java_unittest.cpp \
    generate_cpp_unittest.cpp \
    options_unittest.cpp \
    test_main.cpp \
    tests/end_to_end_tests.cpp \
    tests/example_interface_test_data.cpp \
    tests/fake_io_delegate.cpp \
    tests/test_util.cpp \
    type_cpp_unittest.cpp \
    type_java_unittest.cpp \

LOCAL_SHARED_LIBRARIES := \
    libchrome-host \

LOCAL_STATIC_LIBRARIES := \
    libaidl-common \
    $(aidl_static_libraries) \
    libgmock_host \
    libgtest_host \

LOCAL_LDLIBS_linux := -lrt

include $(BUILD_HOST_NATIVE_TEST)
endif # HOST_OS == linux

endif # No TARGET_BUILD_APPS or TARGET_BUILD_PDK
