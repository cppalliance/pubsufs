//
// Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/pubsufs
//

#include <boost/pubsufs/pubsufs.hpp>

namespace boost {
namespace pubsufs {

bool
is_suffix(
    core::string_view s) noexcept;

bool
is_suffix(
    core::string_view s,
    where w) noexcept
{
    return false;
}

core::string_view
longest_public_suffix(
    core::string_view s) noexcept
{
    return "";
}

core::string_view
shortest_private_suffix(
    core::string_view s) noexcept
{
    return "";
}

bool
is_valid_cookie_domain(
    core::string_view host,
    core::string_view domain)
{
    return false;
}

} // pubsufs
} // boost
