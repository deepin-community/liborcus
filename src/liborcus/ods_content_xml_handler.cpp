/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "ods_content_xml_handler.hpp"
#include "ods_content_xml_context.hpp"

namespace orcus {

ods_content_xml_handler::ods_content_xml_handler(session_context& session_cxt, const tokens& t, spreadsheet::iface::import_factory* factory) :
    xml_stream_handler(session_cxt, t, std::make_unique<ods_content_xml_context>(session_cxt, t, factory))
{
}

ods_content_xml_handler::~ods_content_xml_handler()
{
}

void ods_content_xml_handler::start_document()
{
}

void ods_content_xml_handler::end_document()
{
}

}
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
