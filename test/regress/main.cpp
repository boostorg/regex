
#include "test.hpp"
#include <stdarg.h>

int error_count = 0;

int cpp_main(int argc, char * argv[])
{
   basic_tests();
   test_alt();
   test_sets();
   test_anchors();
   test_backrefs();
   test_character_escapes();
   test_assertion_escapes();
   test_tricky_cases();
   test_tricky_cases2();
   test_grep();
   test_replace();
   test_non_greedy_repeats();
   test_non_marking_paren();
   test_partial_match();
   test_forward_lookahead_asserts();
   test_fast_repeats();
   return error_count;
}

const int* make_array(int first, ...)
{
   //
   // this function takes a variable number of arguments
   // and packs them into an array that we can pass through
   // our testing macros (ideally we would use an array literal
   // but these can't apparently be used as macro arguments).
   //
   static int data[200];
   va_list ap;
   va_start(ap, first);
   //
   // keep packing args, until we get two successive -2 values:
   //
   int terminator_count;
   int next_position = 1;
   data[0] = first;
   if(first == -2)
      terminator_count = 1;
   else
      terminator_count = 0;
   while(terminator_count < 2)
   {
      data[next_position] = va_arg(ap, int);
      if(data[next_position] == -2)
         ++terminator_count;
      else
         terminator_count = 0;
      ++next_position;
   }
   va_end(ap);
   return data;
}

