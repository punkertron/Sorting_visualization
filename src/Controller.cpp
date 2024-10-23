#include "Controller.hpp"

#include <unordered_set>

#include "BubbleSort.hpp"
#include "ISortingAlgorithm.hpp"
#include "InsertionSort.hpp"

Controller::Controller(std::unique_ptr<IGuiManager> guiManager, std::unique_ptr<ISortingManager> sortingManager) :

    guiManager(std::move(guiManager)), sortingManager(std::move(sortingManager))
{
}

static std::unordered_set<std::unique_ptr<ISortingAlgorithm>> createAlgoClasses(const SettingsData& data)
{
    std::unordered_set<std::unique_ptr<ISortingAlgorithm>> res;

    if (data.isBubbleSortSelected) {
        res.insert(std::make_unique<BubbleSort>());
    }
    if (data.isInsertionSortSelected) {
        res.insert(std::make_unique<InsertionSort>());
    }
    return res;
}

void Controller::run()
{
    while (!isDone) {
        isDone = guiManager->handleExit();
        guiManager->updateSettings(data);
        if (!isStarted && data.isStarted) {
            isStarted = true;
            sortingManager->start(data.numberOfElements, createAlgoClasses(data));
        }
        if (isStarted) {
            guiManager->updateVisualizationArea(sortingManager->getDataFromAlgo(data.speed));
        }
        guiManager->render();
    }
}