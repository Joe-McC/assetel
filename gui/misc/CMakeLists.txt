add_library(misc STATIC
    utilities.cpp
    xmlwriter.cpp
)
target_link_libraries(misc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::QuickControls2 Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(misc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

