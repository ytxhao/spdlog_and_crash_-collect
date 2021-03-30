#include <jni.h>
#include <string>
#include <spdlog/ams_spdlog.h>
#include <android/log.h>
#include <openssl/modes.h>
#include <openssl/aes.h>
#include "openssl/src/AES.h"
//#include <spdlog/sinks/rotating_file_sink.h>
//#include <spdlog/sinks/android_sink.h>
//#include <spdlog/sinks/basic_file_sink.h>
//#include <spdlog/sinks/stdout_color_sinks.h>
#define TAG "MainActivityJNI"

void testAES(const std::string& data)
{
    std::string plainText = data;
    std::string encryptText;
    std::string decryptText;

    std::string key = std::string("8cc72b05705d5c46f412af8cbed55aad");

    // AES ecb模式加密验证
    ams::openssl::AES aes;
    aes.ecb_encrypt(plainText, encryptText, key, true);     // 加密
    aes.ecb_encrypt(encryptText, decryptText, key, false);  // 解密
    SPDLOGI(TAG,"AES ecb encrypt verify:%s",((decryptText == plainText) ? "succeeded" : "failed"));
    SPDLOGI(TAG,"AES ecb encrypt verify:%s",decryptText.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_test_spdlog_1and_1crash_1collect_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj /* this */,
        jstring filePath) {
    std::string hello = "Hello from C++";
    char *file_path = (char *) env->GetStringUTFChars(filePath, JNI_FALSE);
    std::string file(file_path);
    init_spdlog(file);

    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_test_spdlog_1and_1crash_1collect_MainActivity_nativeOnClick(
        JNIEnv* env,
        jobject obj) {
//    spdlog::info("{} nativeOnClick 123",TAG);
    SPDLOGI(TAG,"   12 nativeOnClick 34     ");
//    __android_log_print(ANDROID_LOG_INFO, TAG,"and %s", "nativeOnClick");
//    testAES("hello\n\tfda");
    return env->NewStringUTF("click");
}