// ProfilesPopup.cpp
#pragma once

#include "ProfilesPopup.hpp"
#include "manybuild/ui/list/ProfileCell.hpp"
#include "NameInputPopup.hpp"

#include <Geode/Geode.hpp>
#include <map>
#include <string>
#include <vector>
#include <Geode/utils/cocos.hpp>
#include <matjson.hpp>
using namespace geode::prelude;
using namespace manybuild;

bool ProfilesPopup::setup() {
    this->createList();

    auto spr = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
    spr->setScale(0.7f);

    auto addBtn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(ProfilesPopup::onAdd));
    addBtn->setAnchorPoint({ 0.5f, 0.1f });

    auto title = CCLabelBMFont::create("Profiles", "goldFont.fnt");
    title->setScale(1.4f);
    title->setAnchorPoint({ 0.5f, 0.5f });
    title->setPosition({ this->getPopupSize().width / 2, this->getPopupSize().height - 20.f}); // Ajusta la altura según el padding


    auto menu = CCMenu::create();
    menu->addChild(addBtn);
    menu->setZOrder(1);

    m_mainLayer->addChildAtPosition(menu, Anchor::BottomRight, { -30.f, 20.f });
    m_mainLayer->addChild(title);

    return true;
}


void ProfilesPopup::createNewProfileWithName(const std::string& name) {

    std::string finalName = name.empty() ? "New Profile" : name;

    auto gm = GameManager::sharedState();
    std::string uniqueId = std::to_string(std::time(nullptr));

    // Crear datos del perfil
    matjson::Value profile = matjson::makeObject({
        {"name", finalName},
        {"cube", gm->getPlayerFrame()},
        {"ship", gm->getPlayerShip()},
        {"ball", gm->getPlayerBall()},
        {"ufo", gm->getPlayerBird()},
        {"wave", gm->getPlayerDart()},
        {"robot", gm->getPlayerRobot()},
        {"spider", gm->getPlayerSpider()},
        {"swing", gm->getPlayerSwing()},
        {"shipFire", gm->getPlayerJetpack()},
        {"color1", gm->getPlayerColor()},
        {"color2", gm->getPlayerColor2()},
        {"glow", gm->getPlayerGlow()},
        {"glowColor", gm->getPlayerGlowColor()},
        {"death", gm->getPlayerDeathEffect()}
        });

    auto profiles = Mod::get()->getSavedValue<std::map<std::string, matjson::Value>>("icon_profiles");
    log::info(" {} ", profiles.size());

    profiles[uniqueId] = profile;

    Mod::get()->setSavedValue("icon_profiles", profiles);

    this->reloadList();
}

void ProfilesPopup::onAdd(CCObject*) {

    std::string newProfileName;

    NameInputPopup::create([this](std::string name) {
        this->createNewProfileWithName(name);
    });

}

void ProfilesPopup::onDeleteProfile(CCObject* sender) {
    auto btn = static_cast<CCMenuItemSpriteExtra*>(sender);
    std::string idBtn = btn->getID();
    auto item = btn->getParent()->getParent();

    std::string idToDelete = "mbi-profile-" + idBtn;
    std::string parentId = item->getID();

    geode::createQuickPopup(
        "Delete a Profile",
        "Are you sure?",  
        "Nah", "Yeah",
        [this, item, idBtn, idToDelete](auto, bool btn2) {
            if (!btn2) {
                return;
            }

            auto profiles = Mod::get()->getSavedValue<std::map<std::string, matjson::Value>>("icon_profiles");            

            if (profiles.erase(idBtn)) {
                Mod::get()->setSavedValue("icon_profiles", profiles);
                this->resetScene();
            }
            else {
                return;
            }
        }
    );
}

void ProfilesPopup::onUse(const std::string& id) {
    log::info("Usar perfil: {}", id);
    this->onClose(nullptr);
}

void ProfilesPopup::createList() {
    auto size = this->m_mainLayer->getContentSize();

    constexpr static float s_horizontalMargin = 50.f;  // margen a los lados
    constexpr static float s_verticalMargin = 52.f;    // margen arriba/abajo
    constexpr static float s_cellSpacing = 6.f;

    if (m_list) {
        m_list->removeFromParent();
    }

    m_list = ScrollLayer::create(
        { size.width - s_horizontalMargin * 2,
        size.height - s_verticalMargin * 2 - 4.f
        },
        s_cellSpacing
        );

    m_list->setPosition({ s_horizontalMargin, s_verticalMargin + 2.f });


    auto profiles = Mod::get()->getSavedValue<std::map<std::string, matjson::Value>>("icon_profiles");
    int currentId = Mod::get()->getSavedValue<int>("current_icon_profile");

    int counter = 0;
    for (const auto& [id, value] : profiles) {

        auto name = value.get<std::string>("name").unwrapOr("Sin nombre");

        bool isCurrent = id == std::to_string(currentId);

        auto profileId = stoi(id);

        auto cell = ProfileCell::create(
            id, // ID
            name,              // Nombre visible
            [this, profileId, value]() {

                auto gm = GameManager::sharedState();

                int cube = value.get<int>("cube").unwrap();
                int ship = value.get<int>("ship").unwrap();
                int ball = value.get<int>("ball").unwrap();
                int ufo = value.get<int>("ufo").unwrap();
                int wave = value.get<int>("wave").unwrap();
                int robot = value.get<int>("robot").unwrap();
                int spider = value.get<int>("spider").unwrap();
                int swing = value.get<int>("swing").unwrap();
                int shipFire = value.get<int>("shipFire").unwrap();
                int color1 = value.get<int>("color1").unwrap();
                int color2 = value.get<int>("color2").unwrap();
                bool glow = value.get<bool>("glow").unwrap();
                int glowColor = value.get<int>("glowColor").unwrap();
                int death = value.get<int>("death").unwrap();

                gm->setPlayerFrame(cube);
                gm->setPlayerShip(ship);
                gm->setPlayerBall(ball);
                gm->setPlayerBird(ufo);
                gm->setPlayerDart(wave);
                gm->setPlayerRobot(robot);
                gm->setPlayerSpider(spider);
                gm->setPlayerSwing(swing);
                gm->setPlayerJetpack(shipFire);
                gm->setPlayerColor(color1);
                gm->setPlayerColor2(color2);
                gm->setPlayerColor3(glowColor);
                gm->setPlayerGlow(glow);
                gm->setPlayerDeathEffect(death);

                
                Mod::get()->setSavedValue<int>("current_icon_profile", profileId);

                this->resetScene();

                // Cierre suave
                this->onClose(this);
            },
            CCSize{ this->getPopupSize().width - s_horizontalMargin * 2, 45.f },
            isCurrent
        );

        cell->setAnchorPoint({ 0.f, 0.f });
        cell->setPosition({ 10.f, m_list->m_contentLayer->getContentSize().height - (counter + 1) * 60.f });
        cell->setVisible(true); // Por si acaso
        m_list->m_contentLayer->addChild(cell);
        counter++;
    }

    m_list->m_contentLayer->setLayout(
        SimpleColumnLayout::create()
        ->setMainAxisDirection(AxisDirection::TopToBottom)
        ->setMainAxisAlignment(MainAxisAlignment::Start)
        ->setMainAxisScaling(AxisScaling::Grow)
        ->setGap(4.f));

    m_list->scrollToTop();

    this->m_mainLayer->addChild(m_list);
    handleTouchPriority(this);
}

void ProfilesPopup::reloadList() {
    this->createList();
}

CCSize ProfilesPopup::getPopupSize() {
    return { 420.f, 270.f };
}

ProfilesPopup* ProfilesPopup::create() {
    auto ret = new ProfilesPopup();
    if (ret && ret->initAnchored(ret->getPopupSize().width, ret->getPopupSize().height)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void ProfilesPopup::resetScene() {
    auto gl = static_cast<GJGarageLayer*>(CCDirector::sharedDirector()->getRunningScene()->getChildByID("GJGarageLayer"));
    if (gl) {
        CCDirector::sharedDirector()->replaceScene(
            CCTransitionFade::create(0.5f, GJGarageLayer::scene())
        );
    }
}



