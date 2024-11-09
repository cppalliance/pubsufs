//
// Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/pubsufs
//

#ifndef BOOST_PUBSUFS_TABLE_HPP
#define BOOST_PUBSUFS_TABLE_HPP

#include <boost/pubsufs/detail/config.hpp>
#include <boost/pubsufs/where.hpp>
#include <boost/core/detail/string_view.hpp>
#include <boost/system/result.hpp>
#include <memory>

namespace boost {
namespace pubsufs {

struct entry
{
    core::string_view name;
    bool is_puny;
};

class table
{
    struct impl;

    std::shared_ptr<impl> sp_;

public:

private:
    explicit table(std::shared_ptr<impl> sp) noexcept;

    friend
    BOOST_PUBSUFS_DECL
    system::result<table>
    load_table_from_file(
        core::string_view path);
};

/** Return a table constructed from a file
*/
BOOST_PUBSUFS_DECL
system::result<table>
load_table_from_file(
    core::string_view path);

} // pubsufs
} // boost

#endif
