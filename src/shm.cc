#include <iostream>
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
    std::string name = info[0].As<Napi::String>();  
    int blockSize = info[1].As<Napi::Number>();
    int blocks = info[2].As<Napi::Number>();
    
    this->db = new simdb(name.c_str(), blockSize, blocks);
}

void Shm::Close(const Napi::CallbackInfo& info) {
    if (this->db != nullptr) {
        this->db->close();
    }
}

Napi::Value Shm::Size(const Napi::CallbackInfo& info) {
    return info.Env().Undefined();
}

Napi::Value Shm::Keys(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::vector<simdb::VerStr> keys = this->db->getKeyStrs();

    return info.Env().Undefined();
}

Napi::Value Shm::Get(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string key = info[0].As<Napi::String>();
    std::string val = this->db->get(key);

    return Napi::String::New(env, val);
}

void Shm::Del(const Napi::CallbackInfo& info) {
    std::string key = info[0].As<Napi::String>();

    this->db->del(key);
}

void Shm::Put(const Napi::CallbackInfo& info) {
    std::string key = info[0].As<Napi::String>();
    std::string val = info[1].As<Napi::String>();

    this->db->put(key, val);
}