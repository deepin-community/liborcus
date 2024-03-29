/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_ORCUS_STRING_POOL_HPP
#define INCLUDED_ORCUS_STRING_POOL_HPP

#include "env.hpp"

#include <string>
#include <memory>
#include <vector>

namespace orcus {

/**
 * This class implements a shared string pool with the ability to merge with
 * other pools.
 *
 * @note This class is not copy-constructible, but is move-constructible.
 */
class ORCUS_PSR_DLLPUBLIC string_pool
{
public:
    string_pool(const string_pool&) = delete;
    string_pool& operator=(const string_pool&) = delete;

    string_pool();
    string_pool(string_pool&& other);
    ~string_pool();

    /**
     * Intern a string.
     *
     * @param str string to intern.
     *
     * @return pair whose first value is the interned string, and the second
     *         value specifies whether it is a newly created instance (true)
     *         or a reuse of an existing instance (false).
     */
    std::pair<std::string_view, bool> intern(std::string_view str);

    /**
     * Return all interned strings.
     *
     * @return sequence of all interned strings.  The sequence will be sorted.
     */
    std::vector<std::string_view> get_interned_strings() const;

    /**
     * Dump pool's content to stdout.
     *
     * @todo This needs to be reworked to make it more generally usable.
     */
    void dump() const;

    /**
     * Clear pool's content.
     */
    void clear();

    /**
     * Query the total number of strings stored in the pool.
     *
     * @return size_t total number of strings in the pool.
     */
    size_t size() const;

    /**
     * Swap the content with another string-pool instance.
     *
     *
     * @param other string-pool instance to swap contents with.
     */
    void swap(string_pool& other);

    /**
     * Merge another string pool instance in.  This will not invalidate any
     * string references to the other pool.
     *
     * The other string pool instance will become empty when this call
     * returns.
     *
     * @param other string pool instance to merge in.
     */
    void merge(string_pool& other);

private:
    struct impl;
    std::unique_ptr<impl> mp_impl;
};

}

#endif
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
