#include <dobby.h>

void hook(uintptr_t local_address, void* hook, void** tramp) {
    DobbyHook((void*)(gd::base + local_address), hook, tramp);
}