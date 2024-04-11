# Fetchcontent from CMake 3.11
cmake_minimum_required(VERSION 3.16)
project(pybind11_template)

#-------#
# fetch #
#-------#

include(FetchContent)

find_package(glog 0.6.0)
if(NOT glog_FOUND)
    FetchContent_Declare(
        glog
        GIT_REPOSITORY https://github.com/google/glog.git
        GIT_TAG        v0.6.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    # for minimum install
    set(BUILD_TESTING OFF)
    FetchContent_GetProperties(glog)

    if(NOT glog_POPULATED)
        FetchContent_Populate(glog)
        add_subdirectory(${glog_SOURCE_DIR} ${glog_BINARY_DIR})
    endif()
endif()

# v3.3.90 and higher supports slicing
# https://eigen.tuxfamily.org/dox-devel/group__TutorialSlicingIndexing.html
find_package(Eigen3 3.4.0)
if(NOT Eigen3_FOUND)
    FetchContent_Declare(
        Eigen
        GIT_REPOSITORY    https://gitlab.com/libeigen/eigen.git
        GIT_TAG           3.4.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    # for minimum install
    set(BUILD_TESTING OFF)
    set(EIGEN_BUILD_TESTING OFF)
    set(EIGEN_MPL2_ONLY ON)
    set(EIGEN_BUILD_PKGCONFIG OFF)
    set(EIGEN_BUILD_DOC OFF)
    FetchContent_MakeAvailable(Eigen)
endif()

find_package(pybind11 2.12.0 CONFIG)
if(NOT pybind11_FOUND)
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG        v2.12.0
    )
    FetchContent_GetProperties(pybind11)
    if(NOT pybind11_POPULATED)
        FetchContent_Populate(pybind11)
        add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
    endif()
endif()

#------#
# bind #
#------#

# モジュール名を定義
set(bind_name bind)
# モジュール定義
pybind11_add_module(${bind_name} "./src/bind/bind.cpp")
# set_target_properties(${bind_name} PROPERTIES OUTPUT_NAME mypackage/${bind_name})

target_link_libraries(${bind_name} PUBLIC
        glog::glog
        Eigen3::Eigen)

target_compile_features(${bind_name} PUBLIC cxx_std_11)
target_compile_options(${bind_name} PUBLIC
        # 各種警告
        # -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wno-char-subscripts
        # 数値関連エラー：オーバーフロー・未定義動作を検出
        # -ftrapv -fno-sanitize-recover
        # デバッグ情報付与
        $<$<CONFIG:Debug>: -g>
        # 最適化
        $<$<CONFIG:Release>: -mtune=native -march=native -mfpmath=both -O2>)
