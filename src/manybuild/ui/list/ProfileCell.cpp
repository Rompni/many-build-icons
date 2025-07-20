#include "ProfileCell.hpp"
#include "../ProfilesPopup.hpp"
#include <Geode/Geode.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/binding/ButtonSprite.hpp>
#include <cocos2d.h>

using namespace geode::prelude;

namespace manybuild {

    bool ProfileCell::init(
        const std::string& id,
        const std::string& name,
        std::function<void()> onUseCallback,
        cocos2d::CCSize size,
        bool isSelected
    ) {
        if (!CCNode::init())
            return false;

        this->setID("mbi-profile-" + id);

        this->setContentSize(size);
        m_onUse = onUseCallback;

        // Fondo de celda
        auto bg = CCScale9Sprite::create("GJ_button_01.png");
        bg->setContentSize(size);
        bg->setColor({ 109, 58, 31 }); // Marrón
        bg->setAnchorPoint({ 0.f, 0.f });
        bg->setPosition({ 0.f, 0.f });
        this->addChild(bg);

        // 🗑️ Botón de eliminar
        auto deleteSpr = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
        deleteSpr->setScale(0.7f);

        auto deleteBtn = CCMenuItemSpriteExtra::create(
            deleteSpr,
            this, 
            menu_selector(ProfilesPopup::onDeleteProfile)
        );
        //int tag = std::stoi(id);
        //deleteBtn->setTag(tag);
        deleteBtn->setID(id);
        deleteBtn->setPosition({ 25.f, size.height / 2 });

        auto menu = CCMenu::create();
        menu->setID("mbi-delete-menu-"+id);
        menu->setPosition(CCPointZero);
        menu->addChild(deleteBtn);
        this->addChild(menu);

        // Etiqueta del nombre del perfil
        auto label = CCLabelBMFont::create(name.c_str(), "goldFont.fnt");
        label->setAnchorPoint({ 0.f, 0.5f });
        label->setPosition({ 50.f, size.height / 2 });
        label->setScale(1.1f);
        this->addChild(label);

        if (isSelected) {
            auto check = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
            check->setPosition({ size.width - 30.f, size.height / 2 });
            check->setScale(0.8f);
            this->addChild(check);;
        }
        else {
            auto icon = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
            icon->setScale(0.8f);
            auto btn = CCMenuItemSpriteExtra::create(icon, this, menu_selector(ProfileCell::onUseButton));
            btn->setPosition({ size.width - 30.f, size.height / 2 });

            auto menu = CCMenu::createWithItem(btn);
            menu->setPosition(CCPointZero);
            menu->setID("mbi-check-menu-" + id);
            this->addChild(menu);
        }

        return true;
        }

    void ProfileCell::onUseButton(CCObject*) {
        if (m_onUse) {
            log::info("Clicked!");
            Mod::get()->setSavedValue<bool>("need_icon_profile", true);
            m_onUse();
        }
    }

    ProfileCell* ProfileCell::create(const std::string& id, const std::string& name, std::function<void()> onUseCallback, cocos2d::CCSize size, bool isSelected) {
        auto ret = new ProfileCell();

        if (ret && ret->init(id, name, onUseCallback, size, isSelected)) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }

}
