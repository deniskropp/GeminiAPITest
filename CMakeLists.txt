cmake_minimum_required(VERSION 3.16)

project(APITest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appAPITest
    src/main.cpp
    src/api/geminiapi.cpp
    src/api/geminiapi.h
    src/api/message.cpp
    src/api/message.h
    src/api/messagemodel.cpp
    src/api/messagemodel.h
    src/utils/Logger.cpp
    src/utils/Logger.h
)

qt_add_qml_module(appAPITest
    URI APITest
    VERSION 1.0
    QML_FILES resources/qml/Main.qml
    SOURCES src/api/geminiapi.h src/api/geminiapi.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAPITest PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAPITest
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAPITest
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appAPITest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
