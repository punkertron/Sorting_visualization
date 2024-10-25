#include "Controller.hpp"

#include <algorithm>
#include <utility>
#include <vector>

#include "sortingAlgorithms/BubbleSort.hpp"
#include "sortingAlgorithms/HeapSort.hpp"
#include "sortingAlgorithms/ISortingAlgorithm.hpp"
#include "sortingAlgorithms/InsertionSort.hpp"
#include "sortingAlgorithms/MergeSort.hpp"
#include "sortingAlgorithms/QuickSort.hpp"
#include "sortingAlgorithms/ShellSort.hpp"

Controller::Controller(std::unique_ptr<IGuiManager> guiManager, std::unique_ptr<ISortingManager> sortingManager) :

    guiManager_(std::move(guiManager)), sortingManager_(std::move(sortingManager))
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
    while (!isDone_) {
        guiManager_->startRender();
        isDone_ = guiManager_->handleExit();

        guiManager_->updateSettings(settingsData_);
        if (!isStarted_ && settingsData_.isStarted) {
            isEverStarted_ = true;
            isStarted_ = true;
            sortingManager_->start(settingsData_.numberOfElements, createAlgoClasses(settingsData_));
        }
        if (isStarted_ && !settingsData_.isPaused) {
            guiManager_->updateVisualizationArea(sortingManager_->getDataFromAlgo(settingsData_.speed));
        }
        if (isEverStarted_ && (!isStarted_ || settingsData_.isPaused)) {
            // if user stops the animation (or it's done), we need to resize the Visualization Area
            guiManager_->updateVisualizationArea(sortingManager_->getCurrentData());
        }
        guiManager_->render();

        if (isStarted_ && sortingManager_->isNoMoreDataLeft()) {
            isStarted_ = false;
            settingsData_.isStarted = false;
            settingsData_.isPaused = false;
        }
    }
}