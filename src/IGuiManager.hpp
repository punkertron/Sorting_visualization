#ifndef IGUIMANAGER_HPP
#define IGUIMANAGER_HPP

#include <unordered_map>
#include <vector>

#include "SettingsData.hpp"

class IGuiManager {
public:
    virtual ~IGuiManager() = default;
    virtual bool handleExit() = 0;
    virtual void updateSettings(SettingsData& settingsData) = 0;
    virtual void updateVisualizationArea(std::unordered_map<const char*, const std::vector<int>*> sortedDAata) = 0;
    virtual void render() = 0;
};

#endif  // IGUIMANAGER_HPP