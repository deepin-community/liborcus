/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef ORCUS_XLS_XML_HANDLER_HPP
#define ORCUS_XLS_XML_HANDLER_HPP

#include "xml_stream_handler.hpp"

namespace orcus {

namespace spreadsheet { namespace iface {

class import_factory;

}}

class tokens;
struct session_context;

class xls_xml_handler : public xml_stream_handler
{
public:
    xls_xml_handler(session_context& session_cxt, const tokens& t, spreadsheet::iface::import_factory* factory);
    virtual ~xls_xml_handler() override;
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
