#include <napi.h>
#include "shm.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Shm::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)