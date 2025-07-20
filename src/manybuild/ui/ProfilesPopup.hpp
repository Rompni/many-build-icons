// ProfilesPopup.hpp
#pragma once

#include <Geode/ui/Popup.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/binding/FLAlertLayerProtocol.hpp>
//#include "../managers/ProfileManager.hpp"

namespace manybuild {

    class ProfilesPopup : public geode::Popup<>, public FLAlertLayerProtocol {
    protected:
        geode::ScrollLayer* m_list;
        int m_deleteIndex = -1;

        bool setup() override;
        void createList();
        void reloadList();
        cocos2d::CCSize getPopupSize();
        void onAdd(CCObject*);
        void onUse(const std::string& id);
        void resetScene();
        void createNewProfileWithName(const std::string& name);
    public:
        static ProfilesPopup* create();
        void onDeleteProfile(CCObject* sender);

        
    };

} // namespace manybuild