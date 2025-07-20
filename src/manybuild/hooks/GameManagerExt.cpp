#include <Geode/modify/ProfilePage.hpp>
#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

class $modify(GameManagerExt, GameManager) {
    static void onModify(auto& self) {
        log::info("GameManager hookeado correctamente");
    }

    void firstLoad(){
	    log::info("firstLoad");
        GameManager::firstLoad();

    }
};