cmake_minimum_required(VERSION 3.16)

project(NeobankClientWidgets VERSION 0.1 LANGUAGES CXX)

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
  readme.md

  network/socketwrapper.h
  network/socketwrapper.cpp

  services/accountsservice.h
  services/accountsservice.cpp
  services/authservice.h
  services/authservice.cpp
  services/transactionsservice.h
  services/transactionsservice.cpp

  pages/accountspage.ui
  pages/accountspage.h
  pages/accountspage.cpp

  pages/connectpage.ui
  pages/connectpage.h
  pages/connectpage.cpp

  pages/dashboardpage.ui
  pages/dashboardpage.h
  pages/dashboardpage.cpp

  pages/loginpage.ui
  pages/loginpage.h
  pages/loginpage.cpp

  pages/registrationpage.ui
  pages/registrationpage.h
  pages/registrationpage.cpp

  pages/transactionspage.ui
  pages/transactionspage.h
  pages/transactionspage.cpp

  #нет ui
  pages/transferdialog.h
  pages/transferdialog.cpp
    res.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(NeobankClientWidgets
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    constants.h
    models/account.h
    models/transaction.h
    models/user.h
)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NeobankClientWidgets APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(NeobankClientWidgets SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NeobankClientWidgets
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(NeobankClientWidgets PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(NeobankClientWidgets PRIVATE Qt6::Widgets)
target_link_libraries(NeobankClientWidgets PRIVATE Qt6::Core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.NeobankClientWidgets)
endif()
set_target_properties(NeobankClientWidgets PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS NeobankClientWidgets
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(NeobankClientWidgets)
endif()
