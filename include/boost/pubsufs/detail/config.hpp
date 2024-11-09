//
// Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/pubsufs
//

#ifndef BOOST_PUBSUFS_DETAIL_CONFIG_HPP
#define BOOST_PUBSUFS_DETAIL_CONFIG_HPP

#include <boost/config.hpp>

namespace boost {
namespace pubsufs {

//------------------------------------------------

#if defined(BOOST_PUBSUFS_DOCS)
# define BOOST_PUBSUFS_DECL
#else
# if (defined(BOOST_PUBSUFS_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_PUBSUFS_STATIC_LINK)
#  if defined(BOOST_PUBSUFS_SOURCE)
#   define BOOST_PUBSUFS_DECL        BOOST_SYMBOL_EXPORT
#   define BOOST_PUBSUFS_BUILD_DLL
#  else
#   define BOOST_PUBSUFS_DECL        BOOST_SYMBOL_IMPORT
#  endif
# endif // shared lib

# ifndef  BOOST_PUBSUFS_DECL
#  define BOOST_PUBSUFS_DECL
# endif

# if !defined(BOOST_PUBSUFS_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_PUBSUFS_NO_LIB)
#  define BOOST_LIB_NAME boost_pubsufs
#  if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_PUBSUFS_DYN_LINK)
#   define BOOST_DYN_LINK
#  endif
#  include <boost/config/auto_link.hpp>
# endif
#endif

//------------------------------------------------

// source location
#ifdef BOOST_PUBSUFS_NO_SOURCE_LOCATION
# define BOOST_PUBSUFS_POS ::boost::source_location()
#else
# define BOOST_PUBSUFS_POS (BOOST_CURRENT_LOCATION)
#endif

} // pubsufs
} // boost

#endif
