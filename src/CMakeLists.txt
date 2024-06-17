set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Network NetworkAuth)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Network NetworkAuth )

set(TS_FILES tr/doppelganger_ru_RU.ts)

set(PROJECT_HEADERS
        mainwindow.h
        application.h
        yandexoauth.h
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        application.cpp
        yandexoauth.cpp
)

set(PROJECT_UICS
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(doppelganger
        MANUAL_FINALIZATION
        ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_UICS} ${TS_FILES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(doppelganger
        ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_UICS} ${TS_FILES}
    )

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(doppelganger PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::NetworkAuth)

set_target_properties(doppelganger PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS doppelganger
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(doppelganger)
endif()
