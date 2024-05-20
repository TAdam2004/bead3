cmake_minimum_required(VERSION 3.28)
project(Beadando_2)

find_package( SDL2 REQUIRED )

link_directories(/opt/homebrew/lib)
link_directories(/Users/tadam/Documents/BevProg2/ITK_graphicslib-master)

set(CMAKE_CXX_STANDARD 17)

link_libraries (
        SDL2
        SDL2_ttf
)

add_executable(alma main.cpp
        widgets.hpp
        widgets.cpp
        AmobaGame.hpp
        AmobaGame.cpp
        GameBoardWidget.hpp
        GameBoardWidget.cpp
        WidgetContainer.cpp
        WidgetContainer.hpp
)
target_link_libraries(alma graphics)