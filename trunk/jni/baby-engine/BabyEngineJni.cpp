#include <jni.h>
#include "Log.h"

#include "AndcopterRenderer.h"

static Renderer* renderer = 0;

JNIEXPORT
void onSurfaceCreate(JNIEnv* env, jobject thiz) {
	LOGD("onSurfaceCreate()");	
	if (!renderer) {
		renderer = new AndcopterRenderer();
	}
	renderer->onCreate();
}

JNIEXPORT
void onSurfaceChange(JNIEnv* env, jobject thiz, jint width, jint height) {
	LOGD("onSurfaceChange(w=%d, h=%d)", width, height);
	if (renderer) {
		renderer->onSurfaceChange(width, height);
	}
}

JNIEXPORT
void onDraw(JNIEnv* env, jobject thiz) {
	if (renderer) {
		renderer->onDraw();
	}
}

JNIEXPORT
void release(JNIEnv* env, jobject thiz) {
	LOGD("release()");
	if (renderer) {
		delete renderer;
		renderer = 0;
	}
}

JNIEXPORT
void setLoggingJni(JNIEnv* env, jobject thiz, jboolean on) {
	setLogging(on);
}

int methodsCount = 4;
JNINativeMethod methods[] = {
	{"nativeOnSurfaceCreate", "()V", (void*)onSurfaceCreate },
	{"nativeOnSurfaceChange", "(II)V",	(void*)onSurfaceChange },
	{"nativeOnDraw", "()V",	(void*)onDraw },
	{"nativeRelease", "()V", (void*)release },
	{"nativeSetLogging", "(Z)V", (void*)setLoggingJni }
};
const char *classPathName = "com/shaubert/andcopter/jni/BabyEngineJNI";

int jniRegisterNativeMethods(JNIEnv* env, const char* className,
	const JNINativeMethod* gMethods, int numMethods)
{
	jclass clazz;

	LOGD("Registering %s natives", className);
	clazz = env->FindClass(className);
	if (clazz == 0) {
		LOGD("Native registration unable to find class '%s'", className);
		return -1;
	}
	if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
		LOGD("RegisterNatives failed for '%s'", className);
		return -1;
	}
	return 0;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = 0;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
		LOGD("ERROR: GetEnv failed");
		return -1;
	}
	if (jniRegisterNativeMethods(env, classPathName, methods, methodsCount) < 0) {
		LOGE("native registration failed");
		return -1;
	}
	return JNI_VERSION_1_4;
}