/*
 *
 * Copyright (c) 2004
 * Dr John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         static_mutex.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares static_mutex lock type.
  */

#include <boost/config.hpp>

#ifdef BOOST_HAS_THREADS

#include <boost/regex/static_mutex.hpp>

#if defined(BOOST_HAS_WINTHREADS)
#include <windows.h>
#endif


namespace boost{

#if defined(BOOST_HAS_PTHREADS) && defined(PTHREAD_MUTEX_INITIALIZER)

scoped_static_mutex_lock::scoped_static_mutex_lock(static_mutex& m, bool lk)
: m_mutex(m), m_have_lock(false)
{
   if(lk)
      lock();
}

scoped_static_mutex_lock::~scoped_static_mutex_lock()
{
   if(m_have_lock)
      unlock();
}

void scoped_static_mutex_lock::lock()
{
   if(0 == m_have_lock)
   {
      pthread_mutex_lock(&(m_mutex.m_mutex));
      m_have_lock = true;
   }
}

void scoped_static_mutex_lock::unlock()
{
   if(m_have_lock)
   {
      pthread_mutex_unlock(&(m_mutex.m_mutex));
      m_have_lock = false;
   }
}

#elif defined(BOOST_HAS_WINTHREADS)

scoped_static_mutex_lock::scoped_static_mutex_lock(static_mutex& m, bool lk)
: m_mutex(m), m_have_lock(false)
{
   if(lk)
      lock();
}

scoped_static_mutex_lock::~scoped_static_mutex_lock()
{
   if(m_have_lock)
      unlock();
}

void scoped_static_mutex_lock::lock()
{
   if(0 == m_have_lock)
   {
      while(0 != InterlockedCompareExchange((LONG*)&(m_mutex.m_mutex), 1, 0))
      {
         Sleep(0);
      }
      m_have_lock = true;
   }
}

void scoped_static_mutex_lock::unlock()
{
   if(m_have_lock)
   {
      InterlockedExchange((LONG*)&(m_mutex.m_mutex), 0);
      m_have_lock = false;
   }
}

#else
//
// Portable version of a static mutex based on Boost.Thread library:
//
#include <stdlib.h>
#include <assert.h>

boost::recursive_mutex* static_mutex::m_pmutex = 0;
boost::once_flag static_mutex::m_once = BOOST_ONCE_INIT;

extern "C" void free_static_mutex()
{
   delete static_mutex::m_pmutex;
   static_mutex::m_pmutex = 0;
}

void static_mutex::init()
{
   m_pmutex = new boost::recursive_mutex();
   int r = atexit(free_static_mutex);
   assert(0 == r);
}

scoped_static_mutex_lock::scoped_static_mutex_lock(static_mutex& , bool lk)
: m_plock(0), m_have_lock(false)
{
   if(lk)
      lock();
}

scoped_static_mutex_lock::~scoped_static_mutex_lock()
{
   if(m_have_lock)
      unlock();
   delete m_plock;
}

void scoped_static_mutex_lock::lock()
{
   if(0 == m_have_lock)
   {
      boost::call_once(&static_mutex::init, static_mutex::m_once);
      if(0 == m_plock)
         m_plock = new boost::recursive_mutex::scoped_lock(*static_mutex::m_pmutex, false);
      m_plock->lock();
      m_have_lock = true;
   }
}

void scoped_static_mutex_lock::unlock()
{
   if(m_have_lock)
   {
      m_plock->unlock();
      m_have_lock = false;
   }
}

#endif

}

#endif // BOOST_HAS_THREADS
