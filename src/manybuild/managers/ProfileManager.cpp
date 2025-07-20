#include <manybuild/managers/ProfileManager.hpp>
#include <Geode/Geode.hpp>
#include <string>
#include <unordered_map>
#include <optional>

using namespace manybuild;

bool ProfileManager::init() {
    if (m_initialized) return true;
    m_initialized = true;
    return true;
}

geode::Result<> ProfileManager::loadProfiles() {
    if (geode::Mod::get()->hasSavedValue("icon_profiles")) {
        m_profiles = geode::Mod::get()->getSavedValue<std::vector<IconProfile>>("icon_profiles");
    }
    return geode::Ok();
}

geode::Result<> ProfileManager::saveProfiles() {
    geode::Mod::get()->setSavedValue("icon_profiles", m_profiles);
    return geode::Ok();
}

geode::Result<> ProfileManager::addProfile(int id, std::string name, std::map<std::string, int> icons) {
    IconProfile data{ id, name, icons };
    m_profiles.push_back(data);
    return this->saveProfiles();
}

std::vector<IconProfile>& ProfileManager::getProfiles() {
    return m_profiles;
}