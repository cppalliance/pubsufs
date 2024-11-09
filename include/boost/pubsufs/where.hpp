//
// Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/pubsufs
//

#ifndef BOOST_PUBSUFS_WHERE_HPP
#define BOOST_PUBSUFS_WHERE_HPP

#include <boost/pubsufs/detail/config.hpp>

namespace boost {
namespace pubsufs {

/** Areas which may be searched
*/
enum where
{
    private_,
    icann,
    no_star,
    any
};

} // pubsufs
} // boost

#endif
