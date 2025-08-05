include(GoogleTest)


add_executable(testGoogleArtifact testArtifact.cc ${PROJECT_SOURCES})

add_executable(testGoogleBattle testBattle/testBattle.cc ${PROJECT_SOURCES})
add_executable(testGoogleBattlefield testBattle/testBattlefield.cc ${PROJECT_SOURCES})

add_executable(testGoogleCharacter testCharacter/testCharacter.cc ${PROJECT_SOURCES})
add_executable(testGoogleSecondarySkill testCharacter/testSecondarySkill.cc ${PROJECT_SOURCES})

add_executable(testGoogleKeyHandler testGame/testKeyHandler.cc ${PROJECT_SOURCES})

add_executable(testGoogleCoords testMiscellaneous/testCoords.cc ${PROJECT_SOURCES})

add_executable(testGoogleUnit testUnits/testUnit.cc ${PROJECT_SOURCES})

add_executable(testGoogleGridTile testWorldMap/testGridTile.cc ${PROJECT_SOURCES})
add_executable(testGoogleWorldMap testWorldMap/testWorldMap.cc ${PROJECT_SOURCES})


set(MODULES
    testGoogleArtifact
    testGoogleBattle
    testGoogleBattlefield
    testGoogleCharacter
    testGoogleSecondarySkill
    testGoogleKeyHandler
    testGoogleCoords
    testGoogleUnit
    testGoogleGridTile
    testGoogleWorldMap
)


foreach(module ${MODULES})
    target_link_libraries(${module} PUBLIC
        GTest::gtest_main
        pthread
        sfml-system
        sfml-window
        SFML::Window
        Battle Units Miscellaneous Game)

    target_include_directories(${module} PUBLIC
        SFML::Graphic
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}

        ${CMAKE_SOURCE_DIR}/include/
        ${CMAKE_SOURCE_DIR}/include/Artifact/
        ${CMAKE_SOURCE_DIR}/include/Battle/
        ${CMAKE_SOURCE_DIR}/include/Character/
        ${CMAKE_SOURCE_DIR}/include/Game
        ${CMAKE_SOURCE_DIR}/include/Miscellaneous/
        ${CMAKE_SOURCE_DIR}/include/WorldMap
    )

    gtest_discover_tests(${module})
endforeach()