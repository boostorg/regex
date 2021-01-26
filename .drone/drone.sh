#!/bin/bash

# Copyright 2020 Rene Rivera, Sam Darwin
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

set -e
set -x
export TRAVIS_BUILD_DIR=$(pwd)
export DRONE_BUILD_DIR=$(pwd)
export TRAVIS_BRANCH=$DRONE_BRANCH
export VCS_COMMIT_ID=$DRONE_COMMIT
export GIT_COMMIT=$DRONE_COMMIT
export REPO_NAME=$DRONE_REPO
export PATH=~/.local/bin:/usr/local/bin:$PATH

if [ "$DRONE_JOB_BUILDTYPE" == "boost" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop && [ "$TRAVIS_BRANCH" == "master" ] && BOOST_BRANCH=master || true
cd ..
git clone -b $BOOST_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update --init tools/boostdep
cp -r $TRAVIS_BUILD_DIR/* libs/regex
python tools/boostdep/depinst/depinst.py -I example -g "--jobs 3" regex
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

echo "using $TOOLSET : : $COMPILER ;" > ~/user-config.jam
IFS=','
for CXXLOCAL in $CXXSTD; do  (cd libs/config/test && ../../../b2 config_info_travis_install toolset=$TOOLSET cxxstd=$CXXLOCAL $CXXSTD_DIALECT && echo With Standard Version $CXXLOCAL && ./config_info_travis && rm ./config_info_travis)  done
unset IFS
./b2 -j3 libs/regex/test toolset=$TOOLSET cxxstd=$CXXSTD $CXXSTD_DIALECT

elif [ "$DRONE_JOB_BUILDTYPE" == "e0a32953fd-8c01c2152f" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop && [ "$TRAVIS_BRANCH" == "master" ] && BOOST_BRANCH=master || true
cd ..
git clone -b $BOOST_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update --init tools/boostdep
cp -r $TRAVIS_BUILD_DIR/* libs/regex
python tools/boostdep/depinst/depinst.py -I example -g "--jobs 3" regex
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

mkdir __build__ && cd __build__
cmake .. -DBOOST_ENABLE_CMAKE=ON -DBOOST_INCLUDE_LIBRARIES=regex -DBOOST_REGEX_INCLUDE_EXAMPLES=ON
cmake --build .

elif [ "$DRONE_JOB_BUILDTYPE" == "e0a32953fd-a5127a4a07" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop && [ "$TRAVIS_BRANCH" == "master" ] && BOOST_BRANCH=master || true
cd ..
git clone -b $BOOST_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update --init tools/boostdep
cp -r $TRAVIS_BUILD_DIR/* libs/regex
python tools/boostdep/depinst/depinst.py -I example -g "--jobs 3" regex
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

mkdir __build__ && cd __build__
cmake .. -DBUILD_SHARED_LIBS=ON -DBOOST_ENABLE_CMAKE=ON -DBOOST_INCLUDE_LIBRARIES=regex -DBOOST_REGEX_INCLUDE_EXAMPLES=ON
cmake --build .

elif [ "$DRONE_JOB_BUILDTYPE" == "9ff6a79955-b49008754c" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop && [ "$TRAVIS_BRANCH" == "master" ] && BOOST_BRANCH=master || true
cd ..
git clone -b $BOOST_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update --init tools/boostdep
cp -r $TRAVIS_BUILD_DIR/* libs/regex
python tools/boostdep/depinst/depinst.py -I example regex
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

echo "using $TOOLSET : : $COMPILER ;" > ~/user-config.jam
IFS=','
for CXXLOCAL in $CXXSTD; do  (cd libs/config/test && ../../../b2 config_info_travis_install toolset=$TOOLSET cxxstd=$CXXLOCAL $CXXSTD_DIALECT && echo With Standard Version $CXXLOCAL && ./config_info_travis && rm ./config_info_travis)  done
unset IFS
./b2 -j3 libs/regex/test toolset=$TOOLSET cxxstd=$CXXSTD $CXXSTD_DIALECT

fi
