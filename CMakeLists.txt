cmake_minimum_required(VERSION 3.16)
project(system76_power_kde
        DESCRIPTION "A plasmoid to control system76 power profile."
        HOMEPAGE_URL "https://github.com/yuri6037/KDE-System76-Power"
        VERSION 1.0.0)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(KDEInstallDirs)
include(KDECMakeSettings)

find_package(Qt5
             CONFIG REQUIRED
             Core
             DBus
             Quick)

find_package(KF5 ${KF5_REQUIRED_VERSION}
        REQUIRED COMPONENTS
        Plasma)

add_subdirectory(plugin)
add_subdirectory(plasmoid)
