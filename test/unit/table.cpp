//
// Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/pubsufs
//

#include <boost/pubsufs/table.hpp>

#include "test_suite.hpp"

namespace boost {
namespace pubsufs {

struct table_test
{
    void
    run()
    {
        auto rv = load_table_from_file(
            "C:\\Users\\vinnie\\src\\boost\\libs\\pubsufs\\src\\public_suffix_list.dat");
        if(! BOOST_TEST(! rv.has_error()))
            test_suite::log << rv.error().what() << std::endl;
    }
};

TEST_SUITE(
    table_test,
    "boost.pubsufs.table");

} // pubsufs
} // boost
