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
  *   FILE         basic_regex_parser.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares template class basic_regex_parser.
  */

#ifndef BOOST_REGEX_V4_BASIC_REGEX_PARSER_HPP
#define BOOST_REGEX_V4_BASIC_REGEX_PARSER_HPP

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost{
namespace re_detail{

template <class charT, class traits>
class basic_regex_parser : public basic_regex_creator<charT, traits>
{
public:
   basic_regex_parser(regex_data<charT, traits>* data);
   void parse(const charT* p1, const charT* p2, unsigned flags);
   void fail(regex_constants::error_type error_code, std::ptrdiff_t position);

   bool parse_all();
   bool parse_basic();
   bool parse_extended();
   bool parse_literal();
   bool parse_open_paren();
   bool parse_basic_escape();
   bool parse_extended_escape();
   bool parse_match_any();
   bool parse_repeat(std::size_t low = 0, std::size_t high = (std::numeric_limits<std::size_t>::max)());
   bool parse_repeat_range(bool isbasic);

private:
   typedef bool (basic_regex_parser::*parser_proc_type)();
   parser_proc_type           m_parser_proc;    // the main parser to use
   const charT*               m_base;           // the start of the string being parsed
   const charT*               m_end;            // the end of the string being parsed
   const charT*               m_position;       // our current parser position
   unsigned                   m_mark_count;     // how many sub-expressions we have
   std::ptrdiff_t             m_paren_start;    // where the last seen ')' began (where repeats are inserted).
   unsigned                   m_repeater_id;    // the id of the next repeater

   basic_regex_parser& operator=(const basic_regex_parser&);
   basic_regex_parser(const basic_regex_parser&);
};

template <class charT, class traits>
basic_regex_parser<charT, traits>::basic_regex_parser(regex_data<charT, traits>* data)
   : basic_regex_creator<charT, traits>(data), m_mark_count(0), m_paren_start(0), m_repeater_id(0)
{
}

template <class charT, class traits>
void basic_regex_parser<charT, traits>::parse(const charT* p1, const charT* p2, unsigned flags)
{
   // empty strings are errors:
   if(p1 == p2)
      fail(REG_EMPTY, 0);
   // pass flags on to base class:
   this->init(flags);
   // set up pointers:
   m_position = m_base = p1;
   m_end = p2;
   // select which parser to use:
   switch(flags & regbase::main_option_type)
   {
   case regbase::perl_syntax_group:
      m_parser_proc = &basic_regex_parser<charT, traits>::parse_extended;
      break;
   case regbase::basic_syntax_group:
      m_parser_proc = &basic_regex_parser<charT, traits>::parse_basic;
      break;
   case regbase::literal:
      m_parser_proc = &basic_regex_parser<charT, traits>::parse_literal;
      break;
   }

   // parse all our characters:
   bool result = parse_all();
   // if we haven't gobbled up all the characters then we must
   // have had an unexpected ')' :
   if(!result)
      fail(regex_constants::error_paren, std::distance(m_base, m_position));
   // fill in our sub-expression count:
   this->m_pdata->m_mark_count = 1 + m_mark_count;
   this->finalize(p1, p2);
}

template <class charT, class traits>
void basic_regex_parser<charT, traits>::fail(regex_constants::error_type error_code, std::ptrdiff_t position)
{
   std::string message = this->m_pdata->m_traits.error_string(error_code);
   boost::bad_expression e(message, error_code, position);
   boost::throw_exception(e);
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_all()
{
   bool result = true;
   while(result && (m_position != m_end))
   {
      result = (this->*m_parser_proc)();
   }
   return result;
}

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4702)
#endif
template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_basic()
{
   switch(this->m_traits.syntax_type(*m_position))
   {
   case regex_constants::syntax_escape:
      return parse_basic_escape();
   case regex_constants::syntax_dot:
      return parse_match_any();
   case regex_constants::syntax_caret:
      ++m_position;
      this->append_state(syntax_element_start_line);
      break;
   case regex_constants::syntax_dollar:
      ++m_position;
      this->append_state(syntax_element_end_line);
      break;
   case regex_constants::syntax_star:
      if(!(this->m_last_state) || (this->m_last_state->type == syntax_element_start_line))
         return parse_literal();
      else
      {
         ++m_position;
         return parse_repeat();
      }
   default:
      return parse_literal();
   }
   return true;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_extended()
{
   bool result;
   switch(this->m_traits.syntax_type(*m_position))
   {
   case regex_constants::syntax_open_mark:
      return parse_open_paren();
   case regex_constants::syntax_close_mark:
      return false;
   case regex_constants::syntax_escape:
      return parse_extended_escape();
   case regex_constants::syntax_dot:
      return parse_match_any();
   case regex_constants::syntax_caret:
      ++m_position;
      this->append_state(syntax_element_start_line);
      break;
   case regex_constants::syntax_dollar:
      ++m_position;
      this->append_state(syntax_element_end_line);
      break;
   case regex_constants::syntax_star:
      if(m_position == this->m_base)
         fail(REG_BADRPT, 0);
      ++m_position;
      return parse_repeat();
   case regex_constants::syntax_question:
      if(m_position == this->m_base)
         fail(REG_BADRPT, 0);
      ++m_position;
      return parse_repeat(0,1);
   case regex_constants::syntax_plus:
      if(m_position == this->m_base)
         fail(REG_BADRPT, 0);
      ++m_position;
      return parse_repeat(1);
   case regex_constants::syntax_open_brace:
      ++m_position;
      return parse_repeat_range(false);
   case regex_constants::syntax_close_brace:
      fail(REG_EBRACE, this->m_position - this->m_end);
      // we don't ever get here, because we will have thrown:
      BOOST_ASSERT(0);
      result = false;
      break;
   default:
      result = parse_literal();
      break;
   }
   return result;
}
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_literal()
{
   this->append_literal(*m_position);
   ++m_position;
   return true;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_open_paren()
{
   //
   // update our mark count, and append the required state:
   //
   unsigned markid = ++m_mark_count;
   re_brace* pb = static_cast<re_brace*>(this->append_state(syntax_element_startmark, sizeof(re_brace)));
   pb->index = markid;
   ++m_position;
   std::ptrdiff_t last_paren_start = this->getoffset(pb);
   //
   // now recursively add more states, this will terminate when we get to a
   // matching ')' :
   //
   parse_all();
   //
   // we either have a ')' or we have run out of characters prematurely:
   //
   if(m_position == m_end)
      this->fail(REG_EPAREN, std::distance(m_base, m_end));
   BOOST_ASSERT(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_close_mark);
   ++m_position;
   //
   // append closing parenthesis state:
   //
   pb = static_cast<re_brace*>(this->append_state(syntax_element_endmark, sizeof(re_brace)));
   pb->index = markid;
   this->m_paren_start = last_paren_start;

   return true;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_basic_escape()
{
   ++m_position;
   bool result;
   switch(this->m_traits.escape_syntax_type(*m_position))
   {
   case regex_constants::syntax_open_mark:
      return parse_open_paren();
   case regex_constants::syntax_close_mark:
      return false;
   case regex_constants::syntax_plus:
      if(this->m_pdata->m_flags & regex_constants::bk_plus_qm)
      {
         ++m_position;
         return parse_repeat(1);
      }
      else
         return parse_literal();
   case regex_constants::syntax_question:
      if(this->m_pdata->m_flags & regex_constants::bk_plus_qm)
      {
         ++m_position;
         return parse_repeat(0, 1);
      }
      else
         return parse_literal();
   case regex_constants::syntax_open_brace:
      ++m_position;
      return parse_repeat_range(true);
   case regex_constants::syntax_close_brace:
      fail(REG_EBRACE, this->m_position - this->m_base);
      result = false;
      break;
   default:
      result = parse_literal();
      break;
   }
   return result;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_extended_escape()
{
   ++m_position;
   switch(this->m_traits.escape_syntax_type(*m_position))
   {
   case regex_constants::escape_type_left_word:
      ++m_position;
      this->append_state(syntax_element_word_start);
      break;
   case regex_constants::escape_type_right_word:
      ++m_position;
      this->append_state(syntax_element_word_end);
      break;
   default:
      return parse_literal();
   }
   return true;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_match_any()
{
   //
   // we have a '.' that can match any character:
   //
   ++m_position;
   this->append_state(syntax_element_wild);
   return true;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_repeat(std::size_t low, std::size_t high)
{
   bool greedy = true;
   std::size_t insert_point;
   // 
   // when we get to here we may have a non-greedy ? mark still to come:
   //
   if((m_position != m_end) 
      && (0 == (this->m_pdata->m_flags & (regbase::main_option_type | regbase::no_perl_ex))))
   {
      // OK we have a perl regex, check for a '?':
      if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_question)
      {
         greedy = false;
         ++m_position;
      }
   }
   if(0 == this->m_last_state)
   {
      fail(REG_BADRPT, std::distance(m_base, m_position));
   }
   if(this->m_last_state->type == syntax_element_endmark)
   {
      // insert a repeat before the '(' matching the last ')':
      insert_point = this->m_paren_start;
   }
   else if((this->m_last_state->type == syntax_element_literal) && (static_cast<re_literal*>(this->m_last_state)->length > 1))
   {
      // the last state was a literal with more than one character, split it in two:
      re_literal* lit = static_cast<re_literal*>(this->m_last_state);
      charT c = (static_cast<charT*>(static_cast<void*>(lit+1)))[lit->length - 1];
      --(lit->length);
      // now append new state:
      lit = static_cast<re_literal*>(this->append_state(syntax_element_literal, sizeof(re_literal) + sizeof(charT)));
      lit->length = 1;
      (static_cast<charT*>(static_cast<void*>(lit+1)))[0] = c;
      insert_point = this->getoffset(this->m_last_state);
   }
   else
   {
      // repeat the last state whatever it was, need to add some error checking here:
      switch(this->m_last_state->type)
      {
      case syntax_element_start_line:
      case syntax_element_end_line:
      case syntax_element_word_boundary:
      case syntax_element_within_word:
      case syntax_element_word_start:
      case syntax_element_word_end:
      case syntax_element_buffer_start:
      case syntax_element_buffer_end:
      case syntax_element_alt:
      case syntax_element_soft_buffer_end:
      case syntax_element_restart_continue:
         // can't legally repeat any of the above:
         fail(REG_BADRPT, m_position - m_base);
      default:
         // do nothing...
         break;
      }
      insert_point = this->getoffset(this->m_last_state);
   }
   //
   // OK we now know what to repeat, so insert the repeat around it:
   //
   re_repeat* rep = static_cast<re_repeat*>(this->insert_state(insert_point, syntax_element_rep, re_repeater_size));
   rep->min = low;
   rep->max = high;
   rep->greedy = greedy;
   rep->leading = false;
   rep->id = m_repeater_id++;
   // store our repeater position for later:
   std::ptrdiff_t rep_off = this->getoffset(rep);
   // and append a back jump to the repeat:
   re_jump* jmp = static_cast<re_jump*>(this->append_state(syntax_element_jump, sizeof(re_jump)));
   jmp->alt.i = rep_off - this->getoffset(jmp);
   this->m_pdata->m_data.align();
   // now fill in the alt jump for the repeat:
   rep = static_cast<re_repeat*>(this->getaddress(rep_off));
   rep->alt.i = this->m_pdata->m_data.size() - rep_off;
   return true;
}

template <class charT, class traits>
bool basic_regex_parser<charT, traits>::parse_repeat_range(bool isbasic)
{
   //
   // parse a repeat-range:
   //
   std::size_t min, max;
   int v;
   // skip whitespace:
   while((m_position != m_end) && this->m_traits.is_class(*m_position, this->m_mask_space))
      ++m_position;
   // fail if at end:
   if(this->m_position == this->m_end)
      fail(REG_EBRACE, this->m_position - this->m_base);
   // get min:
   v = this->m_traits.toi(m_position, m_end, 10);
   // skip whitespace:
   while((m_position != m_end) && this->m_traits.is_class(*m_position, this->m_mask_space))
      ++m_position;
   if(v < 0)
      fail(REG_BADBR, this->m_position - this->m_base);
   else if(this->m_position == this->m_end)
      fail(REG_EBRACE, this->m_position - this->m_base);
   min = v;
   // see if we have a comma:
   if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_comma)
   {
      // move on and error check:
      ++m_position;
      // skip whitespace:
      while((m_position != m_end) && this->m_traits.is_class(*m_position, this->m_mask_space))
         ++m_position;
      if(this->m_position == this->m_end)
         fail(REG_EBRACE, this->m_position - this->m_base);
      // get the value if any:
      v = this->m_traits.toi(m_position, m_end, 10);
      max = (v >= 0) ? v : (std::numeric_limits<std::size_t>::max)();
   }
   else
   {
      // no comma, max = min:
      max = min;
   }
   // skip whitespace:
   while((m_position != m_end) && this->m_traits.is_class(*m_position, this->m_mask_space))
      ++m_position;
   // OK now check trailing }:
   if(this->m_position == this->m_end)
      fail(REG_EBRACE, this->m_position - this->m_base);
   if(isbasic)
   {
      if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_escape)
      {
         ++m_position;
         if(this->m_position == this->m_end)
            fail(REG_EBRACE, this->m_position - this->m_base);
      }
      else
      {
         fail(REG_BADBR, this->m_position - this->m_base);
      }
   }
   if(this->m_traits.syntax_type(*m_position) == regex_constants::syntax_close_brace)
      ++m_position;
   else
      fail(REG_BADBR, this->m_position - this->m_base);
   //
   // finally go and add the repeat, unless error:
   //
   if(min > max)
      fail(REG_ERANGE, this->m_position - this->m_base);
   return parse_repeat(min, max);
}

} // namespace re_detail
} // namespace boost

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif
