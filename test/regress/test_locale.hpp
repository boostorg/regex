

#ifndef BOOST_REGEX_REGRESS_TEST_LOCALE_HPP
#define BOOST_REGEX_REGRESS_TEST_LOCALE_HPP
//
// defines class test_locale that handles the locale used for testing:
//
class test_locale
{
public:
   enum{
      no_test,
      test_no_locale,
      test_with_locale
   };

   test_locale(const char* c_name, boost::uint32_t lcid);
   ~test_locale();

   static int c_locale_state()
   {
      return s_c_locale;
   }
   static int cpp_locale_state()
   {
      return s_cpp_locale;
   }
   static int win_locale_state()
   {
      return s_win_locale;
   }

   static std::locale cpp_locale()
   {
      return s_cpp_locale_inst;
   }
   static boost::uint32_t win_locale()
   {
      return s_win_locale_inst;
   }

private:
   // the actions to take for each locale type:
   static int s_c_locale;
   static int s_cpp_locale;
   static int s_win_locale;
   // current locales:
   static std::locale s_cpp_locale_inst;
   static boost::uint32_t s_win_locale_inst;

   // backed up versions of the previous locales and their action state:
   std::string     m_old_c_locale;
   int             m_old_c_state;
   std::locale     m_old_cpp_locale;
   int             m_old_cpp_state;
   boost::uint32_t m_old_win_locale;
   int             m_old_win_state;

};

#endif

