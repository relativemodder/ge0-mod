#include <gd.h>

namespace origs {
    inline bool(__thiscall* EditLevelLayer_init)(gd::EditLevelLayer*, gd::GJGameLevel*);
}

namespace hooks {
    bool __fastcall EditLevelLayer_init_H(gd::EditLevelLayer* self, void*, gd::GJGameLevel* level) {
        bool result = origs::EditLevelLayer_init(self, level);

        gd::AchievementNotifier::sharedState()->notifyAchievement("iow", "wioejfoiwef", nullptr, false);

        return result;
    }
}