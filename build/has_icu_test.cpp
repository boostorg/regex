/*
 *
 * Copyright (c) 2010
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <unicode/uversion.h>
#include <unicode/utypes.h>
#include <unicode/uchar.h>
#include <unicode/coll.h>
#include <boost/scoped_ptr.hpp>

#if defined(_MSC_VER) && !defined(_DLL)
#error "Mixing ICU with a static runtime doesn't work"
#endif

int main()
{
   UErrorCode err = U_ZERO_ERROR;
   UChar32 c = ::u_charFromName(U_UNICODE_CHAR_NAME, "GREEK SMALL LETTER ALPHA", &err);
   if(err) return err;
   U_NAMESPACE_QUALIFIER Locale l;
   boost::scoped_ptr<U_NAMESPACE_QUALIFIER Collator> p_col(U_NAMESPACE_QUALIFIER Collator::createInstance(l, err));
   return err;
}
