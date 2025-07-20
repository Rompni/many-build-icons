#pragma once

#include <string>
#include <functional>
#include <cocos2d.h>
#include <Geode/Geode.hpp>

namespace manybuild {

    class ProfileCell : public cocos2d::CCNode {
    protected:
        std::string m_id;
        std::string m_name;
        std::function<void()> m_onUse;

        bool init(
            const std::string& id,
            const std::string& name,
            std::function<void()> onUse,
            cocos2d::CCSize size,
            bool isSelected
        );

        void onUseButton(cocos2d::CCObject*);

    public:
        static ProfileCell* create(
            const std::string& id,
            const std::string& name,
            std::function<void()> onUse,
            cocos2d::CCSize size,
            bool isSelected
        );
    };

}
