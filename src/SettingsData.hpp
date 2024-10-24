#ifndef SETTINGSDATA_HPP
#define SETTINGSDATA_HPP

struct SettingsData {
public:
    int numberOfElements = 100;
    int speed = 10;
    bool isStarted = false;
    bool isBubbleSortSelected = true;
    bool isInsertionSortSelected = true;
    bool isQuickSortSelected = true;
    bool isMergeSortSelected = true;
    bool isHeapSortSelected = true;
    bool isShellSortSelected = true;
};

#endif  // SETTINGSDATA_HPP