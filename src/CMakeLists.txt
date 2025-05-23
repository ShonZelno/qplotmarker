# Подключаем необходимые модули Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Charts)

if(QT_VERSION_MAJOR EQUAL 5)
    find_package(Qt5 REQUIRED COMPONENTS Svg)
elseif(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS SvgWidgets)
endif()


# Заменяем qt_add_library на стандартный add_library
add_library(qplotmarker
    SHARED
    qplotmarker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/QPlotMarker/qplotmarker.hpp
    entity/movable_button.hpp entity/movable_button.cpp
    entity/graphics_coord_item.hpp entity/graphics_coord_item.cpp
    effects/fast_colorize_effect.hpp effects/fast_colorize_effect.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/QPlotMarker/qplot_marker_group.hpp
    qplot_marker_group.cpp
)

# Остальные настройки остаются без изменений
target_include_directories(qplotmarker
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Указываем публичные заголовочные файлы
set_target_properties(qplotmarker PROPERTIES
    PUBLIC_HEADER
        "${CMAKE_CURRENT_SOURCE_DIR}/../include/QPlotMarker/qplotmarker.hpp;
         ${CMAKE_CURRENT_SOURCE_DIR}/../include/QPlotMarker/qplotmarker_global.hpp;
         ${CMAKE_CURRENT_SOURCE_DIR}/../include/QPlotMarker/qplotmarkergroup.hpp"
)


if(QT_VERSION_MAJOR EQUAL 5)
    target_link_libraries(qplotmarker
        PUBLIC
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Charts
            Qt${QT_VERSION_MAJOR}::Svg
    )
elseif(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(qplotmarker
        PUBLIC
            Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Charts
            Qt${QT_VERSION_MAJOR}::SvgWidgets
    )
endif()

set_target_properties(qplotmarker PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    DEFINE_SYMBOL QPLOTMARKER_LIBRARY
)

install(TARGETS qplotmarker
    EXPORT QPlotMarkerTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QPlotMarker
)
