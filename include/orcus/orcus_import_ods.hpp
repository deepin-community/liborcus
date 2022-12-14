/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef ORCUS_ORCUS_IMPORT_ODS_HPP
#define ORCUS_ORCUS_IMPORT_ODS_HPP

#include "interface.hpp"

namespace orcus {

namespace spreadsheet { namespace iface {
    class import_styles;
}}

class ORCUS_DLLPUBLIC import_ods
{
public:
    import_ods() = delete;
    import_ods(const import_ods&) = delete;
    import_ods& operator=(const import_ods&) = delete;

    static void read_styles(std::string_view s, spreadsheet::iface::import_styles* data);
};

}

#endif
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
