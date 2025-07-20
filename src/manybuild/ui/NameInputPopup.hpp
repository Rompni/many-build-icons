#pragma once

#include <Geode/ui/Popup.hpp>
#include <Geode/ui/TextInput.hpp>
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/loader/Mod.hpp>
#include <cocos2d.h>

using namespace geode::prelude;

class NameInputPopup : public geode::Popup<> {
protected:

    geode::TextInput* m_input;
    std::function<void(std::string)> m_onConfirm;

    bool setup() override {
        auto size = this->getPopupSize();

        this->setTitle("Create a Profile");
        this->m_title->setAnchorPoint({ 0.5f, 0.8f });

        auto input = geode::TextInput::create(180.f, "Profile name...");
        input->setAnchorPoint({ 0.5f, 0.5f });
        m_mainLayer->addChildAtPosition(input, Anchor::Center);
        m_input = input;

        auto confirmBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Save", "goldFont.fnt", "GJ_button_01.png", 0.8f),
            this, menu_selector(NameInputPopup::onConfirm)
        );

        auto cancelBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("Cancel", "goldFont.fnt", "GJ_button_01.png", 0.8f),
            this, menu_selector(NameInputPopup::onCancel)
        );

        auto menu = CCMenu::create();
        menu->addChild(cancelBtn);
        menu->addChild(confirmBtn);
        menu->alignItemsHorizontallyWithPadding(20.f);
        menu->setPosition({ size.width / 2, 40.f });
        this->m_mainLayer->addChild(menu);

        return true;
    }

    void onConfirm(CCObject*) {
        auto text = m_input->getString();
        if (!text.empty()) {
            log::info("{}", text);
            if (m_onConfirm) {
                m_onConfirm(text);
                }
            }
        this->onClose(nullptr);
    }

    void onCancel(CCObject*) {
        this->onClose(nullptr);
    }

    CCSize getPopupSize() {
        return { 200.f, 160.f };
    }

public:
    static NameInputPopup* create(std::function<void(std::string)> const& onConfirm) {
        auto ret = new NameInputPopup();
        if (ret->initAnchored(200.f, 160.f)) {
            ret->m_onConfirm = onConfirm;
            ret->autorelease();
            ret->show();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};