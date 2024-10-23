#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <memory>

#include "IGuiManager.hpp"
#include "ISortingManager.hpp"

class Controller {
private:
    bool isDone = false;
    bool isStarted = false;
    SettingsData data;
    std::unique_ptr<IGuiManager> guiManager;
    std::unique_ptr<ISortingManager> sortingManager;

public:
    Controller() = delete;
    ~Controller() = default;
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;

    Controller(std::unique_ptr<IGuiManager> guiManager, std::unique_ptr<ISortingManager> sortingManager);

    void run();
};

#endif  // CONTROLLER_HPP