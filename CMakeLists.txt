cmake_minimum_required(VERSION 3.5)

project(cross_domain_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

SET(BOOST_ROOT "C:\\Boost")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Network Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Network Core Gui)
find_package(Boost  REQUIRED COMPONENTS filesystem property_tree)

set(TS_FILES cross_domain_client_zh_CN.ts)

file(GLOB WIDGET_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/widgets/*.h")
file(GLOB WIDGET_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/widgets/*.cpp")

file(GLOB HTTP_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/http/*.h")
# file(GLOB HTTP_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/http/*.cpp")

file(GLOB MODEL_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/model/*.h")
file(GLOB MODEL_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/model/*.cpp")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        clientconfig.h
        clientconfig.cpp
        ${TS_FILES}
        ${WIDGET_HEADER}
        ${WIDGET_RESOURCE}
        ${HTTP_HEADER}
        ${MODEL_HEADER}
        ${MODEL_RESOURCE}
        cross_domain_client.qrc
)

add_subdirectory(third_partys)
add_subdirectory(utils)
add_subdirectory(Encryption)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cross_wdomain_client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cross_domain_client APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(cross_domain_client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cross_domain_client
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(cross_domain_client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network components UTILS Encryption Boost::property_tree)

set_target_properties(cross_domain_client PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS cross_domain_client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cross_domain_client)
endif()
