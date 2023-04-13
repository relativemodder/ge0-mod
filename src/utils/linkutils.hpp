#include <gd.h>

namespace linkutils {
    using namespace cocos2d;

    const char* get_node_name(CCNode* node) {
        return typeid(*node).name() + 6;
    }

    bool compareChars(const char* c1, const char* c2) {
        if (*c1 == *c2) return true;

        return false;
    }

    CCNode* find_shareLevelLayer(CCScene* parentScene) {
        CCNode* _maybeShareLayer;

        for (int i = 0; i < parentScene->getChildrenCount(); i++) {
            CCNode* buffer = (CCNode*)(parentScene->getChildren()->objectAtIndex(i));
            const char* nodename = get_node_name(buffer);

            std::cout << "And the " << i << " element is " << nodename << std::endl;



            if (compareChars(nodename, "ShareLevelLayer")) {
                std::cout << "Setting... ShareLevelLayer " << std::endl;

                _maybeShareLayer = (CCNode*)(parentScene->getChildren()->objectAtIndex(i));

                std::cout << "ShareLevelLayer set!" << std::endl;
            }

        }

        return _maybeShareLayer;
    }
}
