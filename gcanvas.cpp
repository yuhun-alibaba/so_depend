#include <jni.h>
#include <android/log.h>
#include <stdarg.h>
#include <dlfcn.h>

#include "elf_sym_reader.h"

#define TAG "fakeJni"

#define LOGE(fmt, args...) \
{ \
__android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args); \
}



typedef    void  (*Fake_callBack)(void*);


void call_back_function() {
	LOGE("enter call_back_function");
}


void dlopen_fakejni_so_under_android_7() {

	
	void *sohandler = dlopen("libfakejni.so", RTLD_LAZY);
	LOGE("dlopen libfakejni.so in libgcanvas.so sohandler is %p",sohandler);

	Fake_callBack cb = (Fake_callBack)dlsym(RTLD_DEFAULT,"callBack");
	(*cb)((void*)call_back_function);

	dlclose(sohandler);

}



void dlopen_fakejni_so_above_android_7() {

	uint32_t result = 0; 

	const char *sopath = "/data/app/com.example.hello-1/lib/arm/libfakejni.so";

	result = ali::getSymbolAddr((char *)"callBack",(char *)sopath,(char*)"libfakejni.so");
	LOGE("result is %x",result);

	Fake_callBack cb = (Fake_callBack)result;
	(*cb)((void*)call_back_function);
}



typedef const char* (*FunType)(const char*, int, const char*);

void dlopen_weex_so_under_android_7() {

	void *sohandler = dlopen("libweexjsc.so", RTLD_LAZY);
	LOGE("dlopen libweexjsc.so in libgcanvas.so sohandler is %p",sohandler);

	FunType cb = (FunType)dlsym(RTLD_DEFAULT,"Inject_GCanvasFunc");
	(*cb)(NULL,0,NULL);

	dlclose(sohandler);

}


void dlopen_weex_so_above_android_7() {


	uint32_t result = 0; 

	const char *sopath = "/data/app/com.example.hello-1/lib/arm/libweexjsc.so";

	result = ali::getSymbolAddr((char *)"Inject_GCanvasFunc",(char *)sopath,(char *)"libweexjsc.so");
	LOGE("result is 0x%x",result);

	FunType cb = (FunType)result;
	(*cb)(NULL,0,NULL);

}




JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env;


	if (vm->GetEnv( (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		return -1;
	}

	dlopen_weex_so_above_android_7();


	return JNI_VERSION_1_4;
}
