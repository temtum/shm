#ifndef SHM_H
#define SHM_H

#include <napi.h>
#include <uv.h>

class Shm : public Napi::ObjectWrap<Shm> {

    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        Shm(const Napi::CallbackInfo& info);

    private:
        static Napi::FunctionReference constructor;

        void Del(const Napi::CallbackInfo& info);
        void Put(const Napi::CallbackInfo& info);
        Napi::Value Get(const Napi::CallbackInfo& info);  
};

#endif
