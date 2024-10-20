#include "Controller.hpp"

Controller::Controller(std::unique_ptr<IGuiManager> m): guiManager(std::move(m))
{
}

void Controller::run()
{
    while(!isDone) {
        isDone = guiManager->handleExit();
        guiManager->updateData(data);
        // --------------------------------------
        // here call model and sorting algorithms
        // ...
        // --------------------------------------
        guiManager->render();
    }
}