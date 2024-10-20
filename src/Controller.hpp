#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "IGuiManager.hpp"

#include <memory>

class Controller {
private:
    bool isDone = false;
    SettingsData data;
    std::unique_ptr<IGuiManager> guiManager;

public:
    Controller() = delete;
    ~Controller() = default;
    Controller(const Controller&) = delete;
    Controller(Controller&&) = delete;
    Controller& operator=(const Controller&) = delete;
    Controller& operator=(Controller&&) = delete;

    Controller(std::unique_ptr<IGuiManager> m);

    void run();
};

#endif // CONTROLLER_HPP