set(PLUGIN_SRCS
        src/Init.cpp
        src/Connection.cpp src/Connection.hpp)

add_library(system76_power_kde_plugin SHARED ${PLUGIN_SRCS})

target_link_libraries(system76_power_kde_plugin Qt5::Quick)

install(TARGETS system76_power_kde_plugin
        DESTINATION ${KDE_INSTALL_QMLDIR}/system76_power_kde)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/system76_power_kde)
