#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <Geode/Geode.hpp>

namespace manybuild {

    struct IconProfile {
        std::string name;
        int id;
        std::map<std::string, int> icons;
    };

    class ProfileManager {
    protected:
        bool m_initialized = false;
        std::vector<IconProfile> m_profiles;

        ProfileManager() = default;

    public:
        static ProfileManager& get() {
            static ProfileManager instance;
            return instance;
        }

        bool init();
        geode::Result<> loadProfiles();
        geode::Result<> saveProfiles();
        geode::Result<> addProfile(std::string name, std::map<std::string, int> values);

        std::vector<ProfileData>& getProfiles();
    };

} // namespace manybuild