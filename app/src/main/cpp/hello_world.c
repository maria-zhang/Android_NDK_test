#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <android/log.h>
#include <pthread.h>

#define  LOG_TAG    "debug"
#define  LOG_printf(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void *threadFork(void *vargp)
{
    LOG_printf("printing from thread \n");

    pid_t result = fork();
    if (result == 0) {
        LOG_printf("hi im in the child");
    }
    LOG_printf("result :%d \n", result);

    LOG_printf("pid: %d \n", getpid());
    LOG_printf(" Parent pid: %d \n", getppid());

    //sleep(10000000);

    return NULL;
}

JNIEXPORT jstring JNICALL
Java_com_example_ndktest_MainActivity_helloWorld(
        JNIEnv* env,
        jobject obj) {

    char text[] = "c string";

    size_t pagesize = getpagesize();
    LOG_printf("System page size: %zu bytes \n", pagesize);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, threadFork, NULL);
    pthread_join(thread_id, NULL);

    return (*env)->NewStringUTF(env, text);
}