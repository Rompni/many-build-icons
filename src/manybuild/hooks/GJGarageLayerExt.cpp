#include "GJGarageLayerExt.hpp"
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/utils/NodeIDs.hpp>
#include <Geode/Geode.hpp>
#include "../ui/ProfilesPopup.hpp"

using namespace geode::prelude;

bool GJGarageLayerExt::init() {
    if (!GJGarageLayer::init()) return false;

    Loader::get()->queueInMainThread([this] {
        auto menu = static_cast<CCMenu*>(this->getChildByIDRecursive("shards-menu"));
        if (!menu) {
            log::warn("No se encontró el menú 'shards-menu'");
            return;
        }

        auto iconSpr = CCSprite::createWithSpriteFrameName("MBI_playerIcon.png"_spr);
        iconSpr->setScale(1.1f);

        // === SOMBRA ===
        auto shadow = CCSprite::createWithSpriteFrameName("MBI_playerIcon.png"_spr);
        shadow->setColor({ 0, 0, 0 });
        shadow->setOpacity(80);
        shadow->setPosition({ 17.f, 14.f });
        shadow->setZOrder(-1);
        iconSpr->addChild(shadow);

        auto btn = CCMenuItemSpriteExtra::create(
            iconSpr, this, menu_selector(GJGarageLayerExt::onMyButton)
        );
        btn->setPosition({ 20.f, 100.f });
        btn->setID("profile-button");

        menu->addChild(btn);
        });
    return true;
}

void GJGarageLayerExt::onMyButton(CCObject*) {
    //FLAlertLayer::create("¡Funciona!", "Has presionado el botón del perfil.", "OK")->show();
    auto popup = manybuild::ProfilesPopup::create();
    popup->show();
}

