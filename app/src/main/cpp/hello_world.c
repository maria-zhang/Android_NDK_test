#include <jni.h>
#include <stdio.h>
#include <unistd.h>
#include <android/log.h>
#include <pthread.h>
#include <sys/time.h>

#define  LOG_TAG    "debug"
#define  LOG_printf(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

void *threadFork(void *vargp)
{
    LOG_printf("printing from thread \n");

    pid_t result = fork();
    if (result == 0) {
        LOG_printf("hi im in the child");
    }
    LOG_printf("Result from fork(): %d \n", result);

    LOG_printf("pid: %d \n", getpid());
    LOG_printf("Parent pid: %d \n", getppid());

    //sleep(10000000);

    return NULL;
}

JNIEXPORT jstring JNICALL
Java_com_example_ndktest_MainActivity_helloWorld(
        JNIEnv* env,
        jobject obj) {

    char text[] = "c string";
    FILE *pipe_fp;
    char buff[255];

    //size_t pagesize = getpagesize();
    //LOG_printf("System page size: %zu bytes \n", pagesize);

    //print stack address range for 2 processes
    for (int i = 0; i < 2; i++){
        if (( pipe_fp = popen("grep \"\\[stack\" /proc/self/maps", "r")) == NULL)
        {
            LOG_printf("error popen");
        } else {
            while (fgets(buff, 255, pipe_fp)) {
                LOG_printf("grep results: %s", buff);
            }
            fclose(pipe_fp);
        }
    }

    /*
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, threadFork, NULL);
    pthread_join(thread_id, NULL);
     */

    return (*env)->NewStringUTF(env, text);
}