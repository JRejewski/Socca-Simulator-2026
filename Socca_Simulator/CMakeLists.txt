cmake_minimum_required(VERSION 3.19)
project(Socca_Simulator LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Socca_Simulator
    WIN32 MACOSX_BUNDLE
    main.cpp

    gui/mainwindow.cpp
    gui/mainwindow.h
    gui/mainwindow.ui

    src/zawodnicy/zawodnik.h src/zawodnicy/zawodnik.cpp
    src/zawodnicy/pilkarz.h src/zawodnicy/pilkarz.cpp
    src/zawodnicy/bramkarz.h src/zawodnicy/bramkarz.cpp


    src/druzyny/druzyna.h src/druzyny/druzyna.cpp
    src/mecze/mecz.h src/mecze/mecz.cpp

    src/rozgrywki/trybrozgrywki.h src/rozgrywki/trybrozgrywki.cpp
    src/rozgrywki/szybkimecz.h src/rozgrywki/szybkimecz.cpp
    src/rozgrywki/liga.h src/rozgrywki/liga.cpp
    src/rozgrywki/puchar.h src/rozgrywki/puchar.cpp

    src/turniej/drabinka.h src/turniej/drabinka.cpp

    src/gra/menedzergry.h src/gra/menedzergry.cpp

    src/dane/wczytywaczdruzyn.h src/dane/wczytywaczdruzyn.cpp
)

qt_add_resources(Socca_Simulator "daneGry"
    PREFIX "/"
    FILES
        data/druzyny.json
)

target_link_libraries(Socca_Simulator
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Socca_Simulator
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Socca_Simulator
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
