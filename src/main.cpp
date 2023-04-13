#include <matdash.hpp>

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

// matdash::create_console
#include <matdash/console.hpp>

// gd.h includes cocos2d.h
#include <gd.h>

#include <dobby.h>

#include <cpr/cpr.h>
#include "utils/json.hpp"

using namespace cocos2d;

gd::FLAlertLayer* openAlert;
bool shareConfirmation;
CCNode* maybeShareLayer;

const char* get_node_name(CCNode* node) {
    return typeid(*node).name() + 6;
}

void EditLevelLayer_onShare(gd::EditLevelLayer* self, CCObject* sender) {
    matdash::orig<&EditLevelLayer_onShare>(self, nullptr);

    shareConfirmation = false;

    CCScene* parentScene = CCDirector::sharedDirector()->getRunningScene();

    std::cout << "Cocos scene nodes count" << parentScene->getChildrenCount() << std::endl;

    for (int i = 0; i < parentScene->getChildrenCount(); i++) {
        CCNode* buffer = (CCNode*)(parentScene->getChildren()->objectAtIndex(i));
        const char* nodename = get_node_name(buffer);

        std::cout << "And the " << i << " element is " << nodename << std::endl;

        if (*nodename == *(std::string("ShareLevelLayer").c_str())) {
            std::cout << "Setting... ShareLevelLayer " << std::endl;

            maybeShareLayer = (CCNode*)(parentScene->getChildren()->objectAtIndex(i));

            std::cout << "ShareLevelLayer set!" << std::endl;
        }
            
    }
    maybeShareLayer->setVisible(false);

    shareConfirmation = true;
   
    openAlert = gd::FLAlertLayer::create(self, "Choose", "Share", "Open Collab", "Do you wanna <cg>share level</c> or <cy>open collab?</c>");
    openAlert->show();
    
}


void onShowCollab(gd::EditLevelLayer* self) {
    gd::AchievementNotifier::sharedState()->notifyAchievement("Placeholder", "Collab is opening..", nullptr, false);
}


void EditLevelLayer_FLAlert_Clicked(gd::EditLevelLayer* self, gd::FLAlertLayer* alert, bool openCollabVariant) {

    if (shareConfirmation) {
        std::cout << "Open collab: " << openCollabVariant << std::endl;

        if (!openCollabVariant) {
            maybeShareLayer->setVisible(true);
        }
        else {
            maybeShareLayer->removeFromParent();
            onShowCollab(self);
        }

        shareConfirmation = false;
    }
    

    matdash::orig<&EditLevelLayer_FLAlert_Clicked>(self, alert, openCollabVariant);
}


namespace origs {
    inline bool(__thiscall* EditLevelLayer_init)(gd::EditLevelLayer*, gd::GJGameLevel*);
}


namespace hooks {
    inline bool __fastcall EditLevelLayer_init_H(gd::EditLevelLayer* self, void*, gd::GJGameLevel* level) {
        bool result = origs::EditLevelLayer_init(self, level);

        gd::AchievementNotifier::sharedState()->notifyAchievement("iow", "wioejfoiwef", nullptr, false);

        return result;
    }
}

void hook(uintptr_t local_address, void* hook, void** tramp) {
    DobbyHook((void*)(gd::base + local_address), hook, tramp);
}


void mod_main(HMODULE) {

    hook(0x6F5D0, hooks::EditLevelLayer_init_H, (void**)origs::EditLevelLayer_init);

    //matdash::add_hook<&EditLevelLayer_init>(gd::base + 0x6F5D0);
    matdash::add_hook<&EditLevelLayer_onShare>(gd::base + 0x71BE0);
    matdash::add_hook<&EditLevelLayer_FLAlert_Clicked>(gd::base + 0x71F80);
}