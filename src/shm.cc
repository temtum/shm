#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "shm.h"

Napi::FunctionReference Shm::constructor;

Napi::Object Shm::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Shm", {
        InstanceMethod("open", &Shm::Open),
        InstanceMethod("close", &Shm::Close),
        InstanceMethod("size", &Shm::Size),
        InstanceMethod("keys", &Shm::Keys),
        InstanceMethod("get", &Shm::Get),
        InstanceMethod("del", &Shm::Del),
        InstanceMethod("put", &Shm::Put)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Shm", func);
    return exports;
}

Shm::Shm(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Shm>(info)  {}

void Shm::Open(const Napi::CallbackInfo& info) {

}

void Shm::Close(const Napi::CallbackInfo& info) {
}

Napi::Value Shm::Size(const Napi::CallbackInfo& info) {
    return info.Env().Undefined();
}

Napi::Value Shm::Keys(const Napi::CallbackInfo& info) {
    return info.Env().Undefined();
}

Napi::Value Shm::Get(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    char* shared_memory;
    char* val = nullptr;
    std::string key = info[0].As<Napi::String>();
    std::size_t key_hash = std::hash<std::string>{}(key);
    int segment_id = shmget(key_t(key_hash), (size_t)1024*1024*1024*1+1, IPC_CREAT);

    shared_memory = (char*) shmat(segment_id, (void*) 0, 0);
    val = strdup(shared_memory);
    shmdt(shared_memory);

    return Napi::String::New(env, val);
}

void Shm::Del(const Napi::CallbackInfo& info) {
    std::string key = info[0].As<Napi::String>();
}

void Shm::Put(const Napi::CallbackInfo& info) {
    char* shared_memory;
    std::string key = info[0].As<Napi::String>();
    std::string val = info[1].As<Napi::String>();
    std::size_t key_hash = std::hash<std::string>{}(key);
    int segment_id = shmget(
        (key_t)key_hash,
        (size_t)1024*1024*1024*1+1,
        IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP
    );

    shared_memory = (char*) shmat(segment_id, 0, 0);
    sprintf(shared_memory, "%s", val.c_str());
    shmdt(shared_memory);
}