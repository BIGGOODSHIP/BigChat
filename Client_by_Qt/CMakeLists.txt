cmake_minimum_required(VERSION 3.16)

project(Client_by_Qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Client_by_Qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        config.h
        logindialog.h logindialog.cpp logindialog.ui
        rc.qrc
        registerdialog.h registerdialog.cpp registerdialog.ui
        global.h
        global.cpp
        singleton.h
        httpmgr.h httpmgr.cpp
        config.ini
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Client_by_Qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Client_by_Qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Client_by_Qt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Client_by_Qt PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Client_by_Qt)
endif()
set_target_properties(Client_by_Qt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Client_by_Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Client_by_Qt)
endif()

if(WIN32)
    # 只在Release构建时执行，和原来 CONFIG(release, debug|release) 保持一致
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set(SRC_CONFIG "${CMAKE_SOURCE_DIR}/config.ini")
        set(DST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

        # POST_BUILD：编译链接完成后执行，等价QMAKE_POST_LINK
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND copy /Y "${SRC_CONFIG}" "${DST_DIR}\\"
            COMMENT "Copy config.ini to output directory"
            VERBATIM
        )
    endif()
endif()
