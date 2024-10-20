#ifndef IGUIMANAGER_HPP
#define IGUIMANAGER_HPP

#include "SettingsData.hpp"

class IGuiManager {
public:
    virtual ~IGuiManager() = default;
    virtual bool handleExit() = 0;
    virtual void updateData(SettingsData& settingsData) = 0;
    virtual void render() = 0;
};

#endif // IGUIMANAGER_HPP