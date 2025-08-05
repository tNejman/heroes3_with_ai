add_executable(${APP_NAME} Main.cc)

# add_executable(${APP_NAME} Main_a.cc)
target_link_libraries(${APP_NAME} PRIVATE
    ${MODULES}
    SFML::Graphics
)