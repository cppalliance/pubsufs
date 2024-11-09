//
// Copyright (c) 2024 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/cppalliance/pubsufs
//

#include <boost/pubsufs/table.hpp>
#include <boost/punycode/idna.hpp>

#include "src/mulxp_hash.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace boost {
namespace pubsufs {

// avoid C locale
static
bool
is_space(char c) noexcept
{
    switch(c)
    {
    case ' ':
    case '\f':
    case '\n':
    case '\r':
    case '\t':
    case '\v':
        return true;
    default:
        break;
    }
    return false;
}

static
core::string_view
trim_space(
    core::string_view s) noexcept
{
    if(s.empty())
        return s;
    char const* p0 = s.data();
    char const* const end = p0 + s.size();
    while(is_space(*p0))
    {
        ++p0;
        if(p0 == end)
            return core::string_view(&s[0], 0);
    }
    auto p1 = end;
    for(;;)
    {
        if(! is_space(*--p1))
            break;
    }
    return core::string_view(p0, 1 + p1 - p0);
}

//------------------------------------------------

namespace {

struct domain_list
{
    std::size_t nsuffix = 0;
    std::size_t nexcept = 0;
    std::size_t nwild = 0;
    std::vector<std::string> v;
};

struct hash
{
    bool
    operator()(
        std::string const& s) const noexcept
    {
        return mulxp0_hash(reinterpret_cast<unsigned char const*>(s.data()), s.size(), 0);
    }
};

system::result<domain_list>
load_list_from_file(
    core::string_view path)
{
    enum
    {
        except_bit = 1,
        wild_bit = 2,
        icann_bit = 4,
        private_bit = 8,
        plain_bit = 16
    };

    std::ifstream f;
    f.open(static_cast<std::string>(path));
    if(f.fail())
        return std::error_code(errno, std::system_category());

    domain_list list;
    std::unordered_map<std::string, int, hash> m;

    {
        int sect = 0;
        std::string s;
        while(std::getline(f, s))
        {
            if(s.empty())
                continue;
            auto sv = trim_space(s);
            if(sv.empty())
                continue;
            if(
                sv[0] == '/' &&
                sv.size() > 1 &&
                sv[1] == '/')
            {
                if(sect == 0)
                {
                    if(sv.starts_with("// ===BEGIN ICANN DOMAINS==="))
                        sect = icann_bit;
                    else if(sv.starts_with("// ===BEGIN PRIVATE DOMAINS==="))
                        sect = private_bit;
                }
                else if(
                    sect == icann_bit && 
                    sv.starts_with("// ===END ICANN DOMAINS==="))
                {
                    sect = 0;
                }
                else if(
                    sect == private_bit &&
                    sv.starts_with("// ===END PRIVATE DOMAINS==="))
                {
                    sect = 0;
                }
                continue; // skip comments
            }

            int flags;
            if(sv[0] == '!')
            {
                ++list.nexcept;
                flags = except_bit | sect;
                sv.remove_prefix(1);
            }
            else if(sv[0] == '*')
            {
                if( sv.size() < 2 ||
                    sv[1] != '.')
                {
                    // ERROR unsupported
                    continue;
                }
                ++list.nwild;
                ++list.nsuffix;
                flags = wild_bit | plain_bit | sect;
                sv.remove_prefix(2);
            }
            else
            {
                ++list.nsuffix;
                flags = plain_bit | sect;
            }

            // encode to punycode
            std::string ps;
#if 1
            auto rv = punycode::utf8_to_idna(sv);
            if(rv.has_error())
            {
                // ERROR
                continue;
            }
#else
            {
                std::size_t n = 0;
                puny::encode(
                    puny::detail::ascii_count(n),
                    puny::detail::utf8_input(
                        sv.data(),
                        sv.data() + sv.size()),
                    puny::detail::utf8_input(
                        sv.data() + sv.size(),
                        sv.data() + sv.size()));
                ps.resize(n);
                puny::encode(
                    puny::detail::utf8_output(&ps[0]),
                    puny::detail::utf8_input(
                        sv.data(),
                        sv.data() + sv.size()),
                    puny::detail::utf8_input(
                        sv.data() + sv.size(),
                        sv.data() + sv.size()));
                if(ps != sv)
                {
                    ps.data();
                }

                std::u32string rs;
                rs.resize(1024);
                std::size_t len;
                puny::decode(
                    ps.data(),
                    ps.size(),
                    &rs[0],
                    &len);
                rs.resize(len);
                std::copy(rs.begin(), rs.end(),
                    puny::detail::utf8_count(len));
                std::string out;
                out.resize(len);
                std::copy(rs.begin(), rs.end(),
                    puny::detail::utf8_output(&out[0]));
                BOOST_ASSERT(out == sv);
            }
#endif

            if(m.find(*rv) != m.end())
            {
                // ERROR existing entry
                continue;
            }

            m.emplace(rv.value(), flags);
        }
    }

    list.v.reserve(m.size());
    for(auto const& e : m)
    {
        std::string s;
        s.reserve(e.first.size() + 1);
        s = e.first;
        s.push_back(
            '0' + static_cast<char>(e.second & 0x0f));
        list.v.emplace_back(std::move(s));
    }
    std::sort(list.v.begin(), list.v.end());

    for(auto const& s : list.v)
        std::cout << s << std::endl;

    return list;
}

} // (anon)

//------------------------------------------------

// public suffix list table format
// https://github.com/publicsuffix/list/wiki/Format

table::
table(
    std::shared_ptr<impl> sp) noexcept
    : sp_(std::move(sp))
{
}

struct table::impl
{
    void insert(core::string_view s)
    {
    }
};

//------------------------------------------------

system::result<table>
load_table_from_file(
    core::string_view path)
{
    auto rv = load_list_from_file(path);
    auto sp = std::make_shared<table::impl>();
    return table(std::move(sp));
}

} // pubsufs
} // boost
