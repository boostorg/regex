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
  *   FILE         unicode_iterator.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Iterator adapters for converting between different Unicode encodings.
  */

#ifndef BOOST_REGEX_UNICODE_ITERATOR_HPP
#define BOOST_REGEX_UNICODE_ITERATOR_HPP
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/static_assert.hpp>
#include <stdexcept>
#ifndef BOOST_NO_STD_LOCALE
#include <sstream>
#endif

namespace boost{

namespace detail{

static const ::boost::uint16_t high_surrogate_base = 0xD7C0u;
static const ::boost::uint16_t low_surrogate_base = 0xDC00u;
static const ::boost::uint32_t ten_bit_mask = 0x3FFu;

inline bool is_high_surrogate(::boost::uint16_t v)
{
   return (v & 0xFC00u) == 0xd800u;
}
inline bool is_low_surrogate(::boost::uint16_t v)
{
   return (v & 0xFC00u) == 0xdc00u;
}
template <class T>
inline bool is_surrogate(T v)
{
   return (v & 0xF800u) == 0xd800;
}

}

template <class BaseIterator, class U16Type = ::boost::uint16_t>
class u32_to_u16_iterator
   : public boost::iterator_facade<u32_to_u16_iterator<BaseIterator, U16Type>, U16Type, std::bidirectional_iterator_tag, const U16Type>
{
   typedef boost::iterator_facade<u32_to_u16_iterator<BaseIterator>, U16Type, std::bidirectional_iterator_tag, const U16Type> base_type;
   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 32);
   BOOST_STATIC_ASSERT(sizeof(U16Type)*CHAR_BIT == 16);
public:
   typename base_type::reference
      dereference()const
   {
      if(m_current == 2)
         const_cast<u32_to_u16_iterator*>(this)->extract_current();
      return m_values[m_current];
   }
   bool equal(const u32_to_u16_iterator& that)const
   {
      if(m_position == that.m_position)
      {
         if((m_current >= 2) && (that.m_current < 2))
            const_cast<u32_to_u16_iterator*>(this)->extract_current();
         else if((m_current < 2) && (that.m_current >= 2))
            const_cast<u32_to_u16_iterator&>(that).extract_current();
         if(m_current == that.m_current)
            return true;
      }
      return false;
   }
   void increment()
   {
      // if we have a pending read then read now, so that we know whether
      // to skip a position, or move to a low-surrogate:
      if(m_current == 2)
      {
         // pending read:
         extract_current();
      }
      // move to the next surrogate position:
      ++m_current;
      // if we've reached the end skip a position:
      if(m_values[m_current] == 0)
      {
         m_current = 2;
         ++m_position;
      }
   }
   void decrement()
   {
      if(m_current != 1)
      {
         // decrementing an iterator always leads to a valid position:
         --m_position;
         extract_current();
         m_current = m_values[1] ? 1 : 0;
      }
      else
      {
         m_current = 0;
      }
   }
   BaseIterator base()const
   {
      return m_position;
   }
   // construct:
   u32_to_u16_iterator() : m_position(), m_current(0)
   {
      m_values[2] = 0;
   }
   u32_to_u16_iterator(BaseIterator b) : m_position(b), m_current(2)
   {
      m_values[2] = 0;
   }
private:
   void invalid_code_point(::boost::uint32_t val)
   {
#ifndef BOOST_NO_STD_LOCALE
      std::stringstream ss;
      ss << "Invalid UTF-32 code point U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-16 sequence";
      std::out_of_range e(ss.str());
#else
      std::out_of_range e("Invalid UTF-32 code point encountered while trying to encode UTF-16 sequence");
#endif
      boost::throw_exception(e);
   }

   void extract_current()
   {
      // begin by checking for a code point out of range:
      if(static_cast< ::boost::uint32_t>(*m_position) >= 0x10000u)
      {
         if(static_cast< ::boost::uint32_t>(*m_position) > 0x10FFFFu)
            invalid_code_point(*m_position);
         // split into two surrogates:
         base_value_type v = *m_position;
         m_values[0] = static_cast<U16Type>(v >> 10) + detail::high_surrogate_base;
         m_values[1] = static_cast<U16Type>(v & detail::ten_bit_mask) + detail::low_surrogate_base;
         m_current = 0;
         BOOST_ASSERT(detail::is_high_surrogate(m_values[0]));
         BOOST_ASSERT(detail::is_low_surrogate(m_values[1]));
      }
      else
      {
         // 16-bit code point:
         m_values[0] = static_cast<U16Type>(*m_position);
         m_values[1] = 0;
         m_current = 0;
         // value must not be a surrogate:
         if(detail::is_surrogate(m_values[0]))
            invalid_code_point(*m_position);
      }
   }
   BaseIterator m_position;
   U16Type m_values[3];
   unsigned m_current;
};

template <class BaseIterator, class U32Type = ::boost::uint32_t>
class u16_to_u32_iterator
   : public boost::iterator_facade<u16_to_u32_iterator<BaseIterator, U32Type>, U32Type, std::bidirectional_iterator_tag, const U32Type>
{
   typedef boost::iterator_facade<u16_to_u32_iterator<BaseIterator>, U32Type, std::bidirectional_iterator_tag, const U32Type> base_type;
   // special values for pending iterator reads:
   BOOST_STATIC_CONSTANT(::boost::uint32_t, pending_read = 0xffffffffu);

   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 16);
   BOOST_STATIC_ASSERT(sizeof(U32Type)*CHAR_BIT == 32);

public:
   typename base_type::reference
      dereference()const
   {
      if(m_value == pending_read)
         const_cast<u16_to_u32_iterator*>(this)->extract_current();
      return m_value;
   }
   bool equal(const u16_to_u32_iterator& that)const
   {
      return m_position == that.m_position;
   }
   void increment()
   {
      // skip high surrogate first if there is one:
      if(detail::is_high_surrogate(*m_position)) ++m_position;
      ++m_position;
      m_value = pending_read;
   }
   void decrement()
   {
      --m_position;
      // if we have a low surrogate then go back one more:
      if(detail::is_low_surrogate(*m_position)) 
         --m_position;
      m_value = pending_read;
   }
   BaseIterator base()const
   {
      return m_position;
   }
   // construct:
   u16_to_u32_iterator() : m_position()
   {
   }
   u16_to_u32_iterator(BaseIterator b) : m_position(b)
   {
      m_value = pending_read;
   }
private:
   void invalid_code_point(::boost::uint16_t val)
   {
#ifndef BOOST_NO_STD_LOCALE
      std::stringstream ss;
      ss << "Misplaced UTF-16 surrogate U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-32 sequence";
      std::out_of_range e(ss.str());
#else
      std::out_of_range e("Misplaced UTF-16 surrogate encountered while trying to encode UTF-32 sequence");
#endif
      boost::throw_exception(e);
   }
   void extract_current()
   {
      m_value = static_cast<U32Type>(static_cast< ::boost::uint16_t>(*m_position));
      // if the last value is a high surrogate then adjust m_position and m_value as needed:
      if(detail::is_high_surrogate(*m_position))
      {
         // precondition; next value must have be a low-surrogate:
         ::boost::uint16_t t = *++m_position;
         if((*m_position & 0xFC00u) != 0xDC00u)
            invalid_code_point(t);
         m_value = (m_value - detail::high_surrogate_base) << 10;
         m_value |= (static_cast<U32Type>(static_cast< ::boost::uint16_t>(t)) & detail::ten_bit_mask);
         --m_position;
      }
      // postcondition; result must not be a surrogate:
      if(detail::is_surrogate(m_value))
         invalid_code_point(static_cast< ::boost::uint16_t>(m_value));
   }
   BaseIterator m_position;
   U32Type m_value;
};

}

#endif // BOOST_REGEX_UNICODE_ITERATOR_HPP
