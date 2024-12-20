#ifndef IGUIMANAGER_HPP
#define IGUIMANAGER_HPP

#include <utility>
#include <vector>

#include "SettingsData.hpp"

class IGuiManager {
public:
    virtual ~IGuiManager() = default;
    virtual void startRender() = 0;
    virtual bool handleExit() = 0;
    virtual void updateSettings(SettingsData& settingsData) = 0;
    virtual void updateVisualizationArea(std::vector<std::pair<const char*, const std::vector<int>*> > sortedDAata) = 0;
    virtual void render() = 0;
};

#endif  // IGUIMANAGER_HPP