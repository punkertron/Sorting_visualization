#include "Controller.hpp"

#include <vector>

#include "sortingAlgorithms/BubbleSort.hpp"
#include "sortingAlgorithms/HeapSort.hpp"
#include "sortingAlgorithms/ISortingAlgorithm.hpp"
#include "sortingAlgorithms/InsertionSort.hpp"
#include "sortingAlgorithms/MergeSort.hpp"
#include "sortingAlgorithms/QuickSort.hpp"
#include "sortingAlgorithms/ShellSort.hpp"

Controller::Controller(std::unique_ptr<IGuiManager> guiManager, std::unique_ptr<ISortingManager> sortingManager) :

    guiManager(std::move(guiManager)), sortingManager(std::move(sortingManager))
{
}

static std::vector<std::unique_ptr<ISortingAlgorithm>> createAlgoClasses(const SettingsData& data)
{
    std::vector<std::unique_ptr<ISortingAlgorithm>> res;

    if (data.isShellSortSelected) {
        res.push_back(std::make_unique<ShellSort>());
    }
    if (data.isHeapSortSelected) {
        res.push_back(std::make_unique<HeapSort>());
    }
    if (data.isMergeSortSelected) {
        res.push_back(std::make_unique<MergeSort>());
    }
    if (data.isInsertionSortSelected) {
        res.push_back(std::make_unique<InsertionSort>());
    }
    if (data.isQuickSortSelected) {
        res.push_back(std::make_unique<QuickSort>());
    }
    if (data.isBubbleSortSelected) {
        res.push_back(std::make_unique<BubbleSort>());
    }

    return res;
}

void Controller::run()
{
    while (!isDone) {
        guiManager->startRender();
        isDone = guiManager->handleExit();

        guiManager->updateSettings(data);
        if (!isStarted && data.isStarted) {
            isEverStarted = true;
            isStarted = true;
            sortingManager->start(data.numberOfElements, createAlgoClasses(data));
        }
        if (isStarted && !data.isPaused) {
            guiManager->updateVisualizationArea(sortingManager->getDataFromAlgo(data.speed));
        }
        if (isEverStarted && (!isStarted || data.isPaused)) {
            // if user stops the animation (or it's done), we need to resize the Visualization Area
            guiManager->updateVisualizationArea(sortingManager->getCurrentData());
        }
        guiManager->render();

        if (isStarted && sortingManager->isNoMoreDataLeft()) {
            isStarted = false;
            data.isStarted = false;
            data.isPaused = false;
        }
    }
}