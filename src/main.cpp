#include "pch.hpp"
#include "layers/EditLevelLayer.h"
#include <cpr/cpr.h>

using namespace cocos2d;


namespace modmain {

    void onShowCollab(gd::EditLevelLayer* self) {
        //gd::AchievementNotifier::sharedState()->notifyAchievement("Placeholder", "Collab is opening..", nullptr, false);
    }


    void onCreateEditLevelLayer(gd::EditLevelLayer* self, gd::GJGameLevel* level) {
        //gd::AchievementNotifier::sharedState()->notifyAchievement("EditLevelLayer", (std::string("Created with level: ") + std::string(level->m_sLevelName)).c_str(), nullptr, false);
    }
}


namespace modmainhooks {

    gd::FLAlertLayer* openAlert;
    bool shareConfirmation;
    CCNode* maybeShareLayer;


    void EditLevelLayer_onShare(gd::EditLevelLayer* self, CCObject* sender) {
        matdash::orig<&EditLevelLayer_onShare>(self, nullptr);

        shareConfirmation = false;
        CCScene* parentScene = CCDirector::sharedDirector()->getRunningScene();

        maybeShareLayer = linkutils::find_shareLevelLayer(parentScene);
        maybeShareLayer->setVisible(false);

        shareConfirmation = true;

        openAlert = gd::FLAlertLayer::create(self, "Choose", "Share", "Open Collab", "Do you wanna <cg>share level</c> or <cy>open collab?</c>");
        openAlert->show();
    }

    void EditLevelLayer_FLAlert_Clicked(gd::EditLevelLayer* self, gd::FLAlertLayer* alert, bool openCollabVariant) {

        if (shareConfirmation) {
            if (!openCollabVariant) {
                maybeShareLayer->setVisible(true);
            }
            else {
                maybeShareLayer->removeFromParent();
                modmain::onShowCollab(self);
            }

            shareConfirmation = false;
        }
        matdash::orig<&EditLevelLayer_FLAlert_Clicked>(self, alert, openCollabVariant);
    }

    gd::EditLevelLayer* EditLevelLayer_create(gd::GJGameLevel* level) {
        gd::EditLevelLayer* created_layer = matdash::orig<&EditLevelLayer_create>(level);
        modmain::onCreateEditLevelLayer(created_layer, level);
        return created_layer;
    }
}



void mod_main(HMODULE) {
    matdash::add_hook<&modmainhooks::EditLevelLayer_create>(gd::base + 0x6F530);
    matdash::add_hook<&modmainhooks::EditLevelLayer_onShare>(gd::base + 0x71BE0);
    matdash::add_hook<&modmainhooks::EditLevelLayer_FLAlert_Clicked>(gd::base + 0x71F80);
}