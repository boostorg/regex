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
  *   FILE         cpp_regex_traits.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares regular expression traits class cpp_regex_traits.
  */

#ifndef BOOST_CPP_REGEX_TRAITS_HPP_INCLUDED
#define BOOST_CPP_REGEX_TRAITS_HPP_INCLUDED

#ifndef BOOST_REGEX_TRAITS_DEFAULTS_HPP_INCLUDED
#include <boost/regex/v4/regex_traits_defaults.hpp>
#endif
#ifdef BOOST_HAS_THREADS
#include <boost/regex/static_mutex.hpp>
#endif

namespace boost{ 

//
// forward declaration is needed by some compilers:
//
template <class charT>
class cpp_regex_traits;
   
namespace re_detail{

//
// class cpp_regex_traits_base:
// acts as a container for locale and the facets we are using.
//
template <class charT>
struct cpp_regex_traits_base
{
   cpp_regex_traits_base(const std::locale& l)
   { imbue(l); }
   std::locale imbue(const std::locale& l);

   std::locale m_locale;
   std::ctype<charT> const* m_pctype;
   std::messages<charT> const* m_pmessages;
   std::collate<charT> const* m_pcollate;
};

template <class charT>
std::locale cpp_regex_traits_base<charT>::imbue(const std::locale& l)
{
   std::locale result(m_locale);
   m_locale = l;
   m_pctype = &BOOST_USE_FACET(std::ctype<charT>, l);
   m_pmessages = &BOOST_USE_FACET(std::messages<charT>, l);
   m_pcollate = &BOOST_USE_FACET(std::collate<charT>, l);
   return result;
}

//
// class cpp_regex_traits_char_layer:
// implements methods that require specialisation for narrow characters:
//
template <class charT>
class cpp_regex_traits_char_layer : public cpp_regex_traits_base<charT>
{
   typedef std::basic_string<charT> string_type;
   typedef std::map<charT, regex_constants::syntax_type> map_type;
   typedef typename map_type::const_iterator map_iterator_type;
public:
   cpp_regex_traits_char_layer(const std::locale& l);

   regex_constants::syntax_type syntax_type(charT c)const
   {
      map_iterator_type i = m_char_map.find(c);
      return ((i == m_char_map.end()) ? 0 : i->second);
   }
   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      map_iterator_type i = m_char_map.find(c);
      if(i == m_char_map.end())
      {
         if(this->m_pctype->is(std::ctype_base::lower, c)) return regex_constants::escape_type_class;
         if(this->m_pctype->is(std::ctype_base::upper, c)) return regex_constants::escape_type_not_class;
         return 0;
      }
      return i->second;
   }

private:
   string_type get_default_message(regex_constants::syntax_type);
   // TODO: use a hash table when available!
   map_type m_char_map;
};

template <class charT>
cpp_regex_traits_char_layer<charT>::cpp_regex_traits_char_layer(const std::locale& l) 
   : cpp_regex_traits_base<charT>(l)
{
   // we need to start by initialising our syntax map so we know which
   // character is used for which purpose:
#ifndef __IBMCPP__
   typename std::messages<charT>::catalog cat = static_cast<std::messages<char>::catalog>(-1);
#else
   typename std::messages<charT>::catalog cat = reinterpret_cast<std::messages<char>::catalog>(-1);
#endif
   std::string cat_name(cpp_regex_traits<charT>::get_catalog_name());
   if(cat_name.size())
   {
      cat = this->m_pmessages->open(
         cat_name, 
         this->m_locale);
      if((int)cat < 0)
      {
         std::string m("Unable to open message catalog: ");
         std::runtime_error err(m + cat_name);
         boost::throw_exception(err);
      }
   }
   //
   // if we have a valid catalog then load our messages:
   //
   if((int)cat >= 0)
   {
      try{
         for(regex_constants::syntax_type i = 1; i < regex_constants::syntax_max; ++i)
         {
            string_type mss = this->m_pmessages->get(cat, 0, i, get_default_message(i));
            for(typename string_type::size_type j = 0; j < mss.size(); ++j)
            {
               m_char_map[mss[j]] = i;
            }
         }
         this->m_pmessages->close(cat);
      }
      catch(...)
      {
         this->m_pmessages->close(cat);
         throw;
      }
   }
   else
   {
      for(regex_constants::syntax_type i = 1; i < regex_constants::syntax_max; ++i)
      {
         const char* ptr = get_default_syntax(i);
         while(ptr && *ptr)
         {
            m_char_map[this->m_pctype->widen(*ptr)] = i;
            ++ptr;
         }
      }
   }
}

template <class charT>
typename cpp_regex_traits_char_layer<charT>::string_type 
   cpp_regex_traits_char_layer<charT>::get_default_message(regex_constants::syntax_type i)
{
   const char* ptr = get_default_syntax(i);
   string_type result;
   while(ptr && *ptr)
   {
      result.append(1, this->m_pctype->widen(*ptr));
      ++ptr;
   }
   return result;
}

//
// specialised version for narrow characters:
//
template <>
class cpp_regex_traits_char_layer<char> : public cpp_regex_traits_base<char>
{
   typedef std::string string_type;
public:
   cpp_regex_traits_char_layer(const std::locale& l)
   : cpp_regex_traits_base<char>(l)
   {
      init();
   }

   regex_constants::syntax_type syntax_type(char c)const
   {
      return m_char_map[static_cast<unsigned char>(c)];
   }
   regex_constants::escape_syntax_type escape_syntax_type(char c) const
   {
      return m_char_map[static_cast<unsigned char>(c)];
   }

private:
   regex_constants::syntax_type m_char_map[1u << CHAR_BIT];
   void init();
};

//
// class cpp_regex_traits_implementation:
// provides pimpl implementation for cpp_regex_traits.
//
template <class charT>
class cpp_regex_traits_implementation : public cpp_regex_traits_char_layer<charT>
{
public:
   cpp_regex_traits_implementation();
   cpp_regex_traits_implementation(const std::locale& l) : cpp_regex_traits_char_layer<charT>(l){}
   std::string error_string(regex_constants::error_type n) const
   {
      if(!m_error_strings.empty())
      {
         std::map<int, std::string>::const_iterator p = m_error_strings.find(n);
         return (p == m_error_strings.end()) ? std::string(get_default_error_string(n)) : p->second;
      }
      return get_default_error_string(n);
   }
private:
   std::map<int, std::string> m_error_strings;
};

template <class charT>
cpp_regex_traits_implementation<charT>::cpp_regex_traits_implementation()
{
#ifndef __IBMCPP__
   typename std::messages<charT>::catalog cat = static_cast<std::messages<char>::catalog>(-1);
#else
   typename std::messages<charT>::catalog cat = reinterpret_cast<std::messages<char>::catalog>(-1);
#endif
   std::string cat_name(cpp_regex_traits<charT>::get_catalog_name());
   if(cat_name.size())
   {
      cat = this->m_pmessages->open(
         cat_name, 
         this->m_locale);
      if((int)cat < 0)
      {
         std::string m("Unable to open message catalog: ");
         std::runtime_error err(m + cat_name);
         boost::throw_exception(err);
      }
   }
   //
   // if we have a valid catalog then load our messages:
   //
   if((int)cat >= 0)
   {
      for(int i = 0; i <= boost::regex_constants::error_unknown; ++i)
      {
         std::string s = this->m_pmessages->get(cat, 0, i+200, get_default_error_string(i));
         m_error_strings[i] = s;
      }
   }
}

template <class charT>
boost::shared_ptr<cpp_regex_traits_implementation<charT> > create_cpp_regex_traits(const std::locale& l)
{
   // TODO: create a cache for previously constructed objects.
   return boost::shared_ptr<cpp_regex_traits_implementation<charT> >(new cpp_regex_traits_implementation<charT>(l));
}

} // re_detail

template <class charT>
class cpp_regex_traits
{
private:
   typedef std::ctype<charT>            ctype_type;
public:
   typedef charT                        char_type;
   typedef std::size_t                  size_type;
   typedef std::basic_string<char_type> string_type;
   typedef std::locale                  locale_type;
   typedef typename ctype_type::mask    char_class_type;

   cpp_regex_traits()
      : m_pimpl(re_detail::create_cpp_regex_traits<charT>(std::locale()))
   { }
   static size_type length(const char_type* p)
   {
      return std::char_traits<charT>::length(p);
   }
   regex_constants::syntax_type syntax_type(charT c)const
   {
      return m_pimpl->syntax_type(c);
   }
   regex_constants::escape_syntax_type escape_syntax_type(charT c) const
   {
      return m_pimpl->escape_syntax_type(c);
   }
   charT translate(charT c, bool icase) const
   {
      return icase ? m_pimpl->m_pctype->tolower(c) : c;
   }
   string_type transform(const charT* p1, const charT* p2) const
   {
      return m_pimpl->m_pcollate->transform(p1, p2);
   }
   string_type transform_primary(const charT* , const charT* ) const
   {
      return string_type();
   }
   char_class_type lookup_classname(const charT* p1, const charT* p2) const
   {
      return 0;
   }
   string_type lookup_collatename(const charT* p1, const charT* p2) const
   {
      return string_type();
   }
   bool is_class(charT c, char_class_type f) const
   {
      return false;
   }
   int value(charT) const
   {
      return -1;
   }
   locale_type imbue(locale_type l)
   {
      std::locale result(getloc());
      m_pimpl = re_detail::create_cpp_regex_traits<charT>(l);
      return result;
   }
   locale_type getloc()const
   {
      return m_pimpl->m_locale;
   }
   std::string error_string(regex_constants::error_type n) const
   {
      return m_pimpl->error_string(n);
   }

   //
   // extension:
   // set the name of the message catalog in use (defaults to "boost_regex").
   //
   static std::string catalog_name(const std::string& name);
   static std::string get_catalog_name();

private:
   boost::shared_ptr<re_detail::cpp_regex_traits_implementation<charT> > m_pimpl;
   //
   // catalog name handler:
   //
   static std::string& get_catalog_name_inst();
#ifdef BOOST_HAS_THREADS
   static static_mutex& get_mutex_inst();
#endif
};

template <class charT>
std::string cpp_regex_traits<charT>::catalog_name(const std::string& name)
{
#ifdef BOOST_HAS_THREADS
   static_mutex::scoped_lock lk(get_mutex_inst());
#endif
   std::string result(get_catalog_name_inst());
   get_catalog_name_inst() = name;
   return result;
}

template <class charT>
std::string& cpp_regex_traits<charT>::get_catalog_name_inst()
{
   static std::string s_name;
   return s_name;
}

template <class charT>
std::string cpp_regex_traits<charT>::get_catalog_name()
{
#ifdef BOOST_HAS_THREADS
   static_mutex::scoped_lock lk(get_mutex_inst());
#endif
   std::string result(get_catalog_name_inst());
   return result;
}

#ifdef BOOST_HAS_THREADS
template <class charT>
static_mutex& cpp_regex_traits<charT>::get_mutex_inst()
{
   static static_mutex s_mutex = BOOST_STATIC_MUTEX_INIT;
   return s_mutex;
}
#endif


} // boost

#endif
