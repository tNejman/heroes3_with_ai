add_library(Game
    KeyHandler.cc
    Game.cc
)

target_include_directories(Game PUBLIC
    SFML::Graphic
    SFML::Window
    SFML::System
    ${CMAKE_SOURCE_DIR}/include/Algorithms
    ${CMAKE_SOURCE_DIR}/include/Game
    ${CMAKE_SOURCE_DIR}/include/
)

target_link_libraries(Game PRIVATE 
        Algorithms
    PUBLIC
        SFML::Window
        SFML::System)