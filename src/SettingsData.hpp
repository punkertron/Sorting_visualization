#ifndef SETTINGSDATA_HPP
#define SETTINGSDATA_HPP

struct SettingsData {
public:
    int numberOfElements = 0;
    int speed = 1;
    bool isStarted = false;
    bool isBubbleSortSelected = false;
    bool isInsertionSortSelected = false;
    bool isQuickSortSelected = false;
    bool isMergeSortSelected = false;
    bool isHeapSortSelected = false;
    bool isShellSortSelected = false;
};

#endif  // SETTINGSDATA_HPP