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
  *   FILE         basic_regex_creator.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares template class basic_regex_creator which fills in
  *                the data members of a regex_data object.
  */

#ifndef BOOST_REGEX_V4_BASIC_REGEX_CREATOR_HPP
#define BOOST_REGEX_V4_BASIC_REGEX_CREATOR_HPP

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost{

namespace re_detail{

template <class charT, class traits>
class basic_regex_creator
{
public:
   basic_regex_creator(regex_data<charT, traits>* data);
   std::ptrdiff_t getoffset(void* addr)
   {
      return getoffset(addr, m_pdata->m_data.data());
   }
   std::ptrdiff_t getoffset(void* addr, void* base)
   {
      return static_cast<const char*>(addr) - static_cast<const char*>(base);
   }
   re_syntax_base* getaddress(std::ptrdiff_t off)
   {
      return getaddress(off, m_pdata->m_data.data());
   }
   re_syntax_base* getaddress(std::ptrdiff_t off, void* base)
   {
      return static_cast<re_syntax_base*>(static_cast<void*>(static_cast<char*>(base) + off));
   }
   void init(unsigned flags)
   {
      m_pdata->m_flags = flags;
      m_icase = flags & regex_constants::icase;
   }
   re_syntax_base* append_state(syntax_element_type t, std::size_t s = sizeof(re_syntax_base));
   re_syntax_base* insert_state(std::ptrdiff_t pos, syntax_element_type t, std::size_t s = sizeof(re_syntax_base));
   re_literal* append_literal(charT c);
   void finalize(const charT* p1, const charT* p2);
protected:
   regex_data<charT, traits>*    m_pdata;     // pointer to the basic_regex_data struct we are filling in
   const traits&                 m_traits;    // convenience reference to traits class
   re_syntax_base*               m_last_state;// the last state we added
   bool                          m_icase;     // true for case insensitive matches
   typename traits::char_class_type m_word_mask; // mask used to determine if a character is a word character
   typename traits::char_class_type m_mask_space; // mask used to determine if a character is a word character
private:
   basic_regex_creator& operator=(const basic_regex_creator&);
   basic_regex_creator(const basic_regex_creator&);

   void fixup_pointers(re_syntax_base* state);
   void create_startmaps(re_syntax_base* state);
   void create_startmap(re_syntax_base* state, unsigned char* map, unsigned int* pnull, unsigned char mask, re_syntax_base* terminal);
   unsigned get_restart_type(re_syntax_base* state);
};

template <class charT, class traits>
basic_regex_creator<charT, traits>::basic_regex_creator(regex_data<charT, traits>* data)
   : m_pdata(data), m_traits(data->m_traits), m_last_state(0)
{
   m_pdata->m_data.clear();
   static const charT w = 'w';
   static const charT s = 's';
   m_word_mask = m_traits.lookup_classname(&w, &w +1);
   m_mask_space = m_traits.lookup_classname(&s, &s +1);
   BOOST_ASSERT(m_word_mask); 
   BOOST_ASSERT(m_mask_space); 
}

template <class charT, class traits>
re_syntax_base* basic_regex_creator<charT, traits>::append_state(syntax_element_type t, std::size_t s)
{
   // append a new state, start by aligning our last one:
   m_pdata->m_data.align();
   // set the offset to the next state in our last one:
   if(m_last_state)
      m_last_state->next.i = m_pdata->m_data.size() - getoffset(m_last_state);
   // now actually extent our data:
   m_last_state = static_cast<re_syntax_base*>(m_pdata->m_data.extend(s));
   // fill in boilerplate options in the new state:
   m_last_state->next.i = 0;
   m_last_state->type = t;
   return m_last_state;
}

template <class charT, class traits>
re_syntax_base* basic_regex_creator<charT, traits>::insert_state(std::ptrdiff_t pos, syntax_element_type t, std::size_t s)
{
   // append a new state, start by aligning our last one:
   m_pdata->m_data.align();
   // set the offset to the next state in our last one:
   if(m_last_state)
      m_last_state->next.i = m_pdata->m_data.size() - getoffset(m_last_state);
   // remember the last state position:
   std::ptrdiff_t off = getoffset(m_last_state) + s;
   // now actually insert our data:
   re_syntax_base* new_state = static_cast<re_syntax_base*>(m_pdata->m_data.insert(pos, s));
   // fill in boilerplate options in the new state:
   new_state->next.i = s;
   new_state->type = t;
   m_last_state = getaddress(off);
   return new_state;
}

template <class charT, class traits>
re_literal* basic_regex_creator<charT, traits>::append_literal(charT c)
{
   re_literal* result;
   // start by seeing if we have an existing re_literal we can extend:
   if((0 == m_last_state) || (m_last_state->type != syntax_element_literal))
   {
      // no existing re_literal, create a new one:
      result = static_cast<re_literal*>(append_state(syntax_element_literal, sizeof(re_literal) + sizeof(charT)));
      result->length = 1;
      *static_cast<charT*>(static_cast<void*>(result+1)) = m_traits.translate(c, m_icase);
   }
   else
   {
      // we have an existing re_literal, extend it:
      std::ptrdiff_t off = getoffset(m_last_state);
      m_pdata->m_data.extend(sizeof(charT));
      m_last_state = result = static_cast<re_literal*>(getaddress(off));
      charT* characters = static_cast<charT*>(static_cast<void*>(result+1));
      characters[result->length] = m_traits.translate(c, m_icase);
      ++(result->length);
   }
   return result;
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::finalize(const charT* p1, const charT* p2)
{
   // we've added all the states we need, now finish things off.
   // start by adding a terminating state:
   append_state(syntax_element_match);
   // extend storage to store original expression:
   std::ptrdiff_t len = p2 - p1;
   m_pdata->m_expression_len = len;
   charT* ps = static_cast<charT*>(m_pdata->m_data.extend(sizeof(charT) * (1 + (p2 - p1))));
   m_pdata->m_expression = ps;
   std::copy(p1, p2, ps);
   ps[p2 - p1] = 0;
   // fill in our other data...
   // successful parsing implies a zero status:
   m_pdata->m_status = 0;
   // get the first state of the machine:
   m_pdata->m_first_state = static_cast<re_syntax_base*>(m_pdata->m_data.data());
   // fixup pointers in the machine:
   fixup_pointers(m_pdata->m_first_state);
   // create nested startmaps:
   create_startmaps(m_pdata->m_first_state);
   // create main startmap:
   std::memset(m_pdata->m_startmap, 0, sizeof(m_pdata->m_startmap));
   m_pdata->m_can_be_null = 0;

   create_startmap(m_pdata->m_first_state, m_pdata->m_startmap, &(m_pdata->m_can_be_null), mask_all, 0);
   // get the restart type:
   m_pdata->m_restart_type = get_restart_type(m_pdata->m_first_state);
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::fixup_pointers(re_syntax_base* state)
{
   while(state)
   {
      switch(state->type)
      {
      case syntax_element_alt:
      case syntax_element_rep:
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_long_set_rep:
         std::memset(static_cast<re_alt*>(state)->_map, 0, sizeof(static_cast<re_alt*>(state)->_map));
         static_cast<re_alt*>(state)->can_be_null = 0;
         // fall through:
      case syntax_element_jump:
         static_cast<re_jump*>(state)->alt.p = getaddress(static_cast<re_jump*>(state)->alt.i, state);
         // fall through again:
      default:
         if(state->next.i)
            state->next.p = getaddress(state->next.i, state);
         else
            state->next.p = 0;
      }
      state = state->next.p;
   }
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::create_startmaps(re_syntax_base* state)
{
   // recursive implementation:
   // create the last map in the machine first, so that earlier maps
   // can make use of the result...
   while(state)
   {
      switch(state->type)
      {
      case syntax_element_alt:
      case syntax_element_rep:
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_long_set_rep:
         // create other startmaps *first*, since we can use the
         // results from these when creating out own:
         create_startmaps(state->next.p);
         create_startmap(state->next.p, static_cast<re_alt*>(state)->_map, &static_cast<re_alt*>(state)->can_be_null, mask_take, state);
         create_startmap(static_cast<re_alt*>(state)->alt.p, static_cast<re_alt*>(state)->_map, &static_cast<re_alt*>(state)->can_be_null, mask_skip, state);
         return;
      default:
         state = state->next.p;
      }
   }
}

template <class charT, class traits>
void basic_regex_creator<charT, traits>::create_startmap(re_syntax_base* state, unsigned char* map, unsigned int* pnull, unsigned char mask, re_syntax_base* terminal)
{
   while(state && (state != terminal))
   {
      switch(state->type)
      {
      case syntax_element_literal:
      {
         // don't set anything in *pnull, set each element in map
         // that could match the first character in the literal:
         if(map)
         {
            map[0] |= mask_init;
            charT first_char = *static_cast<charT*>(static_cast<void*>(static_cast<re_literal*>(state) + 1));
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               if(m_traits.translate(static_cast<charT>(i), m_icase) == first_char)
                  map[i] |= mask;
            }
         }
         return;
      }
      case syntax_element_end_line:
      {
         // next character must be a line separator (if there is one):
         if(map)
         {
            map[0] |= mask_init;
            map['\n'] |= mask;
            map['\r'] |= mask;
         }
         // now figure out if we can match a NULL string at this point:
         if(pnull)
            create_startmap(state->next.p, 0, pnull, mask, terminal);
         return;
      }
      case syntax_element_backref:
      case syntax_element_wild:
      {
         // can't be null, any character can match:
         if(map)
         {
            map[0] |= mask_init;
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               map[i] |= mask;
            }
         }
         return;
      }
      case syntax_element_match:
      {
         // must be null, any character can match:
         if(map)
         {
            map[0] |= mask_init;
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               map[i] |= mask;
            }
         }
         if(pnull)
            *pnull |= mask;
         return;
      }
      case syntax_element_word_start:
      {
         // recurse, then AND with all the word characters:
         create_startmap(state->next.p, map, pnull, mask, terminal);
         if(map)
         {
            map[0] |= mask_init;
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               if(!m_traits.is_class(static_cast<charT>(i), m_word_mask))
                  map[i] &= static_cast<unsigned char>(~mask);
            }
         }
         return;
      }
      case syntax_element_word_end:
      {
         // recurse, then AND with all the word characters:
         create_startmap(state->next.p, map, pnull, mask, terminal);
         if(map)
         {
            map[0] |= mask_init;
            for(unsigned int i = 0; i < (1u << CHAR_BIT); ++i)
            {
               if(m_traits.is_class(static_cast<charT>(i), m_word_mask))
                  map[i] &= static_cast<unsigned char>(~mask);
            }
         }
         return;
      }
      case syntax_element_buffer_end:
      {
         // we *must be null* :
         if(pnull)
            *pnull |= mask;
         return;
      }
      case syntax_element_long_set:
         assert(0);
      case syntax_element_set:
         assert(0);
      case syntax_element_jump:
         // take the jump:
         state = static_cast<re_alt*>(state)->alt.p;
         break;;
      case syntax_element_alt:
         assert(0);
      case syntax_element_rep:
      case syntax_element_dot_rep:
      case syntax_element_char_rep:
      case syntax_element_short_set_rep:
      case syntax_element_long_set_rep:
         {
            re_alt* rep = static_cast<re_repeat*>(state);
            if(rep->_map[0] & mask_init)
            {
               if(map)
               {
                  // copy previous results:
                  for(unsigned int i = 0; i <= UCHAR_MAX; ++i)
                  {
                     if(rep->_map[i] & mask_any)
                        map[i] |= mask;
                  }
               }
               if(pnull)
               {
                  if(rep->can_be_null & mask_any)
                     *pnull |= mask;
               }
            }
            else
            {
               // we haven't created a startmap for this alternative yet
               // so take the union of the two options:
               create_startmap(state->next.p, map, pnull, mask, state);
               create_startmap(rep->alt.p, map, pnull, mask, state);
            }
         }
         return;
      case syntax_element_soft_buffer_end:
         // match newline or null:
         if(map)
         {
            map[0] |= mask_init;
            map['\n'] |= mask;
            map['\r'] |= mask;
         }
         if(pnull)
            *pnull |= mask;
         return;
      default:
         state = state->next.p;
      }
   }
}

template <class charT, class traits>
unsigned basic_regex_creator<charT, traits>::get_restart_type(re_syntax_base* state)
{
   //
   // find out how the machine starts, so we can optimise the search:
   //
   while(state)
   {
      switch(state->type)
      {
      case syntax_element_startmark:
      case syntax_element_endmark:
         state = state->next.p;
         continue;
      case syntax_element_start_line:
         return regbase::restart_line;
      case syntax_element_word_boundary:
      case syntax_element_word_start:
         return regbase::restart_line;
      case syntax_element_buffer_start:
         return regbase::restart_continue;
      default:
         state = 0;
         continue;
      }
   }
   return regbase::restart_any;
}

} // namespace re_detail

} // namespace boost

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif
