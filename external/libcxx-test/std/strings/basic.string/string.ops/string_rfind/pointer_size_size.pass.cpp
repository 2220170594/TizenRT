/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <string>

// size_type rfind(const charT* s, size_type pos, size_type n) const;

#include <string>
#include <cassert>
#include "test_macros.h"
#include "libcxx_tc_common.h"


template <class S>
static int
test(const S& s, const typename S::value_type* str, typename S::size_type pos,
      typename S::size_type n, typename S::size_type x)
{
    TC_ASSERT_EXPR(s.rfind(str, pos, n) == x);
    if (x != S::npos)
        TC_ASSERT_EXPR(x <= pos && x + n <= s.size());
    return 0;
}

template <class S>
static int test0()
{
    TC_ASSERT_FUNC((test(S(""), "", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 0, 1, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 0, 2, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 0, 4, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 0, 5, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 0, 1, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 0, 5, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 0, 9, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 0, 10, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 0, 1, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 0, 10, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 0, 19, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 0, 20, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "", 1, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 1, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 1, 1, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 1, 2, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 1, 4, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcde", 1, 5, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 1, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 1, 1, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 1, 5, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 1, 9, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcde", 1, 10, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 1, 0, 0)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 1, 1, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 1, 10, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 1, 19, S::npos)));
    TC_ASSERT_FUNC((test(S(""), "abcdeabcdeabcdeabcde", 1, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 0, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 0, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 0, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 0, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 0, 9, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 0, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 0, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 0, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 0, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 1, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 1, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 1, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 1, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 1, 9, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 1, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 1, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 1, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 1, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "", 2, 0, 2)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 2, 0, 2)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 2, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 2, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 2, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 2, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 2, 0, 2)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 2, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 2, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 2, 9, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 2, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 2, 0, 2)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 2, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 2, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 2, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 2, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "", 4, 0, 4)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 4, 0, 4)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 4, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 4, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 4, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 4, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 4, 0, 4)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 4, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 4, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 4, 9, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 4, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 4, 0, 4)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 4, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 4, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 4, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 4, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 5, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 5, 2, 0)));
    return 0;
}

template <class S>
static int test1()
{
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 5, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 5, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 5, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 5, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 5, 9, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 5, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 5, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 5, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 5, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 5, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "", 6, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 6, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 6, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 6, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 6, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcde", 6, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 6, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 6, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 6, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 6, 9, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcde", 6, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 6, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 6, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 6, 10, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 6, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcde"), "abcdeabcdeabcdeabcde", 6, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 0, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 0, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 0, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 0, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 0, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 0, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 0, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 0, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 0, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 1, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 1, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 1, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 1, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 1, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 1, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 1, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 1, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 1, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 5, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 5, 2, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 5, 4, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 5, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 5, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 5, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 5, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 5, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 5, 0, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 5, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 5, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 5, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 5, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "", 9, 0, 9)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 9, 0, 9)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 9, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 9, 2, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 9, 4, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 9, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 9, 0, 9)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 9, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 9, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 9, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 9, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 9, 0, 9)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 9, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 9, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 9, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 9, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 10, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 10, 2, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 10, 4, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 10, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 10, 1, 5)));
    return 0;
}

template <class S>
static int test2()
{
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 10, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 10, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 10, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 10, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 10, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 10, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 10, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "", 11, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 11, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 11, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 11, 2, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 11, 4, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcde", 11, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 11, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 11, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 11, 5, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 11, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcde", 11, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 11, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 11, 1, 5)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 11, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 11, 19, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcde"), "abcdeabcdeabcdeabcde", 11, 20, S::npos)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 0, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 0, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 0, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 0, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 0, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 0, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 0, 0, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 0, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 0, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 0, 19, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 0, 20, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 1, 2, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 1, 4, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 1, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 1, 5, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 1, 9, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 1, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 1, 0, 1)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 1, 1, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 1, 10, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 1, 19, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 1, 20, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 10, 1, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 10, 2, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 10, 4, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 10, 5, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 10, 1, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 10, 5, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 10, 9, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 10, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 10, 0, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 10, 1, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 10, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 10, 19, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 10, 20, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "", 19, 0, 19)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 19, 0, 19)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 19, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 19, 2, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 19, 4, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 19, 5, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 19, 0, 19)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 19, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 19, 5, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 19, 9, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 19, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 19, 0, 19)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 19, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 19, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 19, 19, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 19, 20, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "", 20, 0, 20)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 20, 0, 20)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 20, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 20, 2, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 20, 4, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 20, 5, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 20, 0, 20)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 20, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 20, 5, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 20, 9, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 20, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 20, 0, 20)));
    return 0;
}

template <class S>
static int test3()
{
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 20, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 20, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 20, 19, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 20, 20, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "", 21, 0, 20)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 21, 0, 20)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 21, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 21, 2, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 21, 4, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcde", 21, 5, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 21, 0, 20)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 21, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 21, 5, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 21, 9, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcde", 21, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 21, 0, 20)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 21, 1, 15)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 21, 10, 10)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 21, 19, 0)));
    TC_ASSERT_FUNC((test(S("abcdeabcdeabcdeabcde"), "abcdeabcdeabcdeabcde", 21, 20, 0)));
    return 0;
}

int tc_libcxx_strings_string_rfind_pointer_size_size(void)
{
    {
    typedef std::string S;
    TC_ASSERT_FUNC((test0<S>()));
    TC_ASSERT_FUNC((test1<S>()));
    TC_ASSERT_FUNC((test2<S>()));
    TC_ASSERT_FUNC((test3<S>()));
    }
    TC_SUCCESS_RESULT();
    return 0;
}
