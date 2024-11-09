//
// Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/pubsufs
//

#ifndef BOOST_PUBSUFS_PUBSUFS_HPP
#define BOOST_PUBSUFS_PUBSUFS_HPP

#include <boost/pubsufs/detail/config.hpp>
#include <boost/pubsufs/where.hpp>
#include <boost/core/detail/string_view.hpp>

namespace boost {
namespace pubsufs {

/** Return true if s is a public suffix
*/
BOOST_PUBSUFS_DECL
bool
is_suffix(
    core::string_view s) noexcept;

/** Return true if s is a public suffix
*/
BOOST_PUBSUFS_DECL
bool
is_suffix(
    core::string_view s,
    where w) noexcept;

/** Return the longest public suffix of domain s
*/
BOOST_PUBSUFS_DECL
core::string_view
longest_public_suffix(
    core::string_view s) noexcept;

/** Return the shortest private suffix of domain s
*/
BOOST_PUBSUFS_DECL
core::string_view
shortest_private_suffix(
    core::string_view s) noexcept;

/** Return true if cookie domain is valid for the host
*/
BOOST_PUBSUFS_DECL
bool
is_valid_cookie_domain(
    core::string_view host,
    core::string_view domain);

} // pubsufs
} // boost

#endif
