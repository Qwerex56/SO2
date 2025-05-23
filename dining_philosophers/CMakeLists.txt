cmake_minimum_required(VERSION 3.30)
project(dining_philosophers)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(dining_philosophers src/main.cpp
        src/chopstick.cpp
        include/chopstick.h
        src/philosopher.cpp
        include/philosopher.h
        include/PhilosopherStatus.h
        src/DiningPhilosophers.cpp
        include/DiningPhilosophers.h
        include/DiningPhilosophersVisualizer.h
        src/DiningPhilosophersVisualizer.cpp
)
target_compile_features(dining_philosophers PRIVATE cxx_std_17)
target_link_libraries(dining_philosophers PRIVATE SFML::Graphics)