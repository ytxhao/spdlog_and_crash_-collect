#include <jni.h>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/android_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#define TAG "MainActivityJNI"

extern "C" JNIEXPORT jstring JNICALL
Java_com_test_spdlog_1and_1crash_1collect_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj /* this */,
        jstring filePath) {
    std::string hello = "Hello from C++";
    char *file_path = (char *) env->GetStringUTFChars(filePath, JNI_FALSE);
    std::string file(file_path);
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    // spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %t %L: %v"); // change log pattern
    spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %P-%t %L: %v"); // change log pattern
//    LOGD(TAG,"initSpdlog SetLogPath new path:%s",file.c_str());
    std::string tag = "spdlog-android";
//    auto android_logger = spdlog::android_logger_mt("android", tag);
//    auto file_logger = spdlog::rotating_logger_mt("ams_file_logger", file, 1024 * 1024 * 5, 3);

    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file,1024 * 1024 * 5,3);
    file_sink->set_pattern("%Y-%m-%d %H:%M:%S.%e %P-%t %L: %v");
    file_sink->set_level(spdlog::level::debug);

    auto android_sink = std::make_shared<spdlog::sinks::android_sink_mt>(tag, true);
    android_sink->set_pattern("%v");
    android_sink->set_level(spdlog::level::debug);

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(file_sink);
    sinks.push_back(android_sink);
    auto combined_logger = std::make_shared<spdlog::logger>( "multi_sink", begin( sinks ), end( sinks ));
//    spdlog::register_logger( combined_logger );
    spdlog::set_default_logger(combined_logger);
    std::chrono::seconds s(3);
    spdlog::flush_every(s);


    spdlog::info("{} stringFromJNI path: {}",TAG,hello.c_str());

    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_test_spdlog_1and_1crash_1collect_MainActivity_nativeOnClick(
        JNIEnv* env,
        jobject obj) {
    spdlog::info("{} nativeOnClick 123",TAG);
    return env->NewStringUTF("click");
}