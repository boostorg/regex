# Copyright 2018-2019 Mike Dev
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.Regex is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required( VERSION 3.5 )
project( BoostRegex LANGUAGES CXX )

option( BOOST_REGEX_INCLUDE_EXAMPLES "Also build (some) boost regex examples" OFF )

file( GLOB BOOST_REGEX_SRC ./src/*.cpp )

add_library( boost_regex ${BOOST_REGEX_SRC} )
add_library( Boost::regex ALIAS boost_regex )

target_include_directories( boost_regex PUBLIC include )

target_link_libraries( boost_regex
    PUBLIC
        Boost::assert
        Boost::concept_check
        Boost::config
        Boost::container_hash
        Boost::core
        Boost::integer
        Boost::iterator
        Boost::mpl
        Boost::predef
        Boost::smart_ptr
        Boost::static_assert
        Boost::throw_exception
        Boost::type_traits
)

if( BOOST_REGEX_INCLUDE_EXAMPLES )
    add_subdirectory( example/snippets )
endif()

