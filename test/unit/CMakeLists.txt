#
# Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/cppalliance/pubsufs
#

set(EXTRAFILES
    ../../../url/extra/test_main.cpp
    ../../../url/extra/test_suite.hpp
    )

file(GLOB_RECURSE PFILES CONFIGURE_DEPENDS *.cpp *.hpp)
list(APPEND PFILES
    CMakeLists.txt
    #Jamfile
    )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "" FILES ${PFILES})
source_group("_extra" FILES ${EXTRAFILES})
add_executable(boost_pubsufs_tests ${PFILES} ${EXTRAFILES})
target_include_directories(boost_pubsufs_tests PUBLIC . ../../../url/extra)
target_link_libraries(
    boost_pubsufs_tests
    PRIVATE
        Boost::pubsufs
        Boost::assert
        Boost::config
        Boost::core # for string_view
        Boost::punycode
        Boost::system # for result, error_code
        Boost::utility # for current_function in test_suite.hpp
    )
add_test(NAME boost_pubsufs_tests COMMAND boost_pubsufs_tests)
