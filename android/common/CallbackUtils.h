/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <jni.h>

#include "common/CallbackUtils.h"
#include "common/NioUtils.h"

#include <filament/Engine.h>

struct CallbackJni {
#ifdef ANDROID
    jclass handlerClass = nullptr;
    jmethodID post = nullptr;
#endif
    jclass executorClass = nullptr;
    jmethodID execute = nullptr;
};

void acquireCallbackJni(JNIEnv* env, CallbackJni& callbackUtils);
void releaseCallbackJni(JNIEnv* env, CallbackJni callbackUtils, jobject handler, jobject callback);

struct JniBufferCallback {
    static JniBufferCallback* make(filament::Engine* engine,
            JNIEnv* env, jobject handler, jobject callback, AutoBuffer&& buffer);

    static void invoke(void* buffer, size_t n, void* user);

private:
    JniBufferCallback(JNIEnv* env, jobject handler, jobject callback, AutoBuffer&& buffer);
    JniBufferCallback(JniBufferCallback const &) = delete;
    JniBufferCallback(JniBufferCallback&&) = delete;
    ~JniBufferCallback();

    JNIEnv* mEnv;
    jobject mHandler;
    jobject mCallback;
    AutoBuffer mBuffer;
    CallbackJni mCallbackUtils;
};

struct JniImageCallback {
    static JniImageCallback* make(filament::Engine* engine, JNIEnv* env, jobject handler,
            jobject runnable, long image);

    static void invoke(void* image, void* user);

private:
    JniImageCallback(JNIEnv* env, jobject handler, jobject runnable, long image);
    JniImageCallback(JniImageCallback const &) = delete;
    JniImageCallback(JniImageCallback&&) = delete;
    ~JniImageCallback();

    JNIEnv* mEnv;
    jobject mHandler;
    jobject mCallback;
    long mImage;
    CallbackJni mCallbackUtils;
};

struct JniCallback {
    static JniCallback* make(JNIEnv* env, jobject handler, jobject runnable);

    static void invoke(void* user);

    jobject getCallbackObject() { return mCallback; }
    JNIEnv* getJniEnv() { return mEnv; }

private:
    JniCallback(JNIEnv* env, jobject handler, jobject runnable);
    JniCallback(JniCallback const &) = delete;
    JniCallback(JniCallback&&) = delete;
    ~JniCallback();

    JNIEnv* mEnv;
    jobject mHandler;
    jobject mCallback;
    CallbackJni mCallbackUtils;
};
