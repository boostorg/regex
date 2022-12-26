/*
 *
 * Copyright (c) 2022
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

module;

#include <memory>

export module test_support;

export template <class T> struct pimpl
{
private:
   std::shared_ptr<T> data;
public:
   pimpl(const T& x) : data(new T(x)) {}
   pimpl() = default;
};

