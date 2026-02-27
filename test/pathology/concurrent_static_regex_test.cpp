/*
 *
 * Copyright (c) 2026
 * Amaan Qureshi
 *
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

/*
 *   LOCATION:    see http://www.boost.org for most recent version.
 *   FILE:        concurrent_static_regex_test.cpp
 *   VERSION:     see <boost/version.hpp>
 *   DESCRIPTION: Test for concurrent use of static regex objects.
 *                See https://github.com/boostorg/regex/issues/198
 */

#include "../test_macros.hpp"
#include <atomic>
#include <boost/detail/lightweight_main.hpp>
#include <boost/regex.hpp>
#include <string>
#include <thread>
#include <vector>

namespace {

std::atomic<unsigned> match_count{0};
std::atomic<unsigned> search_count{0};
std::atomic<unsigned> replace_count{0};

static const boost::regex digits_regex(R"(^\d+$)");
static const boost::regex
    map_regex(R"(^\s*\S+\s+\S+\s+\S+\s+\S+\s+\S+\s+(/\S+)\s*$)");
static const boost::regex special_regex(R"([.^$\\*+?()\[\]{}|])");

void thread_regex_match(unsigned iterations) {
  const char *samples[] = {"12345", "hello", "99999", "0", "abc123", "42"};
  const unsigned n_samples = sizeof(samples) / sizeof(samples[0]);

  for (unsigned i = 0; i < iterations; ++i) {
    const char *s = samples[i % n_samples];
    if (boost::regex_match(s, digits_regex))
      match_count.fetch_add(1, std::memory_order_relaxed);
  }
}

void thread_regex_search(unsigned iterations) {
  const std::string lines[] = {
      "08:00-17:00 r--p 00000000 08:01 12345  /usr/lib/libc.so.6",
      "7f8a1000-7f8a2000 rw-p 00001000 08:01 67890  /usr/lib/ld-linux.so.2",
      "this line does not match the pattern at all",
      "00400000-00401000 r-xp 00000000 08:02 54321  /usr/bin/test",
  };
  const unsigned n_lines = sizeof(lines) / sizeof(lines[0]);

  boost::smatch what;
  for (unsigned i = 0; i < iterations; ++i) {
    const std::string &line = lines[i % n_lines];
    if (boost::regex_search(line, what, map_regex))
      search_count.fetch_add(1, std::memory_order_relaxed);
  }
}

void thread_regex_replace(unsigned iterations) {
  const std::string inputs[] = {
      "/nix/store/abc123",
      "path.with"
      "[brackets]",
      "no+specials*here?",
      "plain",
  };
  const unsigned n_inputs = sizeof(inputs) / sizeof(inputs[0]);

  for (unsigned i = 0; i < iterations; ++i) {
    const std::string &input = inputs[i % n_inputs];
    std::string result = boost::regex_replace(input, special_regex, R"(\\$&)");
    if (result != input)
      replace_count.fetch_add(1, std::memory_order_relaxed);
  }
}

} // anonymous namespace

int cpp_main(int, char *[]) {
  const unsigned n_threads = 8;
  const unsigned iterations = 50000;

  for (unsigned round = 0; round < 3; ++round) {
    match_count = 0;
    search_count = 0;
    replace_count = 0;

    std::vector<std::thread> threads;
    threads.reserve(n_threads * 3);

    for (unsigned t = 0; t < n_threads; ++t) {
      threads.emplace_back(thread_regex_match, iterations);
      threads.emplace_back(thread_regex_search, iterations);
      threads.emplace_back(thread_regex_replace, iterations);
    }

    for (auto &th : threads)
      th.join();

    BOOST_CHECK(match_count > 0);
    BOOST_CHECK(search_count > 0);
    BOOST_CHECK(replace_count > 0);
  }

  return 0;
}
