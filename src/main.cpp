#include <matdash.hpp>

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

// matdash::create_console
#include <matdash/console.hpp>

// gd.h includes cocos2d.h
#include <gd.h>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

bool MenuLayer_init(gd::MenuLayer* self) {
    if (!matdash::orig<&MenuLayer_init>(self)) return false;

    return true;
}

void mod_main(HMODULE) {
    matdash::create_console();
    matdash::add_hook<&MenuLayer_init>(gd::base + 0x1907B0);
}