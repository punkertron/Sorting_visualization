# Sorting Visualization

---

![sorting](assets/sorting.gif)

---

## Contents

1. [Project idea](#project-idea)
2. [How To Build](#how-to-build)
3. [Details](#details)
4. [Code style](#code-style)
5. [Libraries Used](#libraries-used)
6. [TODO](#todo)

---

### Project idea
This project visualizes sorting algorithms using Dear ImGui, SDL2, and OpenGL2, with each algorithm running in its own thread. It was created to practice GUI development and class architecture.

---

### How To Build
Developed on Debian 12. Not tested on other platforms.<br/>
You need to make sure that you have `SDL2, OpenGL2, cmake, make` installed.<br/><br/>
The actual steps:
``` bash
git clone --recurse-submodules https://github.com/punkertron/Sorting_visualization
cd Sorting_visualization
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build ./build
```
The program **SortingVisualization** will appear in the `build/` directory.

---

### Details

#### How It Works?

The program is organized around a central class, [Controller](src/Controller.hpp), which coordinates the interactions between the [SortingManager](src/SortingManager.cpp) and [GuiManager](src/ImGuiSDL2OpenGL2Manager.hpp).

The [SortingManager](src/SortingManager.cpp) uses a custom [ConcurrentQueue](src/ConcurrentQueue.hpp) to store [SwappedPositions](src/SwappedPositions.hpp) data, capturing every `std::swap` operation from the sorting algorithms. This allows the [SortingManager](src/SortingManager.cpp) to track and manage swaps in real-time.

The [Controller](src/Controller.hpp) requests data from the [SortingManager](src/SortingManager.cpp) for visualization. The [SortingManager](src/SortingManager.cpp) processes the swaps and provides the relevant data to the [GuiManager](src/ImGuiSDL2OpenGL2Manager.hpp), which handles the rendering of the sorting process.

Though tracking only swaps and creating multiple copies of the data for sorting isn't the most efficient approach, it works well enough for this demo project. The sorting process involves two `std::swap` calls — one during the actual algorithm and another during data transmission to the [GuiManager](src/ImGuiSDL2OpenGL2Manager.hpp).

Additionally, all components are designed using interfaces ([IGuiManager](src/IGuiManager.hpp), [ISortingManager](src/ISortingManager.hpp), [ISortingAlgorithm](src/sortingAlgorithms/ISortingAlgorithm.hpp)), making it easy to extend functionality or swap out implementations.

---

### Code Style

This project includes its own [clang-format](.clang-format) configuration and a script to format the code automatically:
```bash
bash code_style.sh
```

---

### Libraries Used
- [Dear ImGui](https://github.com/ocornut/imgui)
- SDL2 + OpenGL2

---

### TODO
- **Expand Test Coverage**: Add tests to ensure the reliability and accuracy of the sorting algorithms and other components.
- **Review Sorting Logic**: Reevaluate the logic behind sorting, including how sorting data is tracked and transferred to the `GuiManager`, to optimize performance and reduce redundancy.
- **Improve Documentation**: Write comprehensive documentation and add meaningful comments to enhance code readability and maintainability.