# Copyright 2019 Sam Day
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.regex is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required(VERSION 3.5)
project(BoostRegex LANGUAGES CXX)

add_library(boost_regex
        src/c_regex_traits.cpp
        src/cpp_regex_traits.cpp
        src/cregex.cpp
        src/fileiter.cpp
        src/icu.cpp
        src/instances.cpp
        src/posix_api.cpp
        src/regex.cpp
        src/regex_debug.cpp
        src/regex_raw_buffer.cpp
        src/regex_traits_defaults.cpp
        src/static_mutex.cpp
        src/usinstances.cpp
        src/w32_regex_traits.cpp
        src/wc_regex_traits.cpp
        src/wide_posix_api.cpp
        src/winstances.cpp
        )
add_library(Boost::regex ALIAS boost_regex)

target_include_directories(boost_regex PUBLIC include)

target_link_libraries(boost_regex
        PUBLIC
        Boost::assert
        Boost::concept_check
        Boost::config
        Boost::core
        Boost::detail
        Boost::functional
        Boost::integer
        Boost::iterator
        Boost::mpl
        Boost::predef
        Boost::smart_ptr
        Boost::static_assert
        Boost::throw_exception
        Boost::type_traits
        Boost::utility
        )
