/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDED_ORCUS_XLSX_CONTEXT_HPP
#define INCLUDED_ORCUS_XLSX_CONTEXT_HPP

#include "orcus/spreadsheet/types.hpp"
#include "orcus/string_pool.hpp"
#include "orcus/cell_buffer.hpp"

#include "xml_context_base.hpp"
#include "xlsx_types.hpp"

namespace orcus {

namespace spreadsheet { namespace iface {
    class import_sheet;
    class import_shared_strings;
    class import_styles;
}}

/**
 * Context for xl/sharedStrings.xml part.
 */
class xlsx_shared_strings_context : public xml_context_base
{
public:
    xlsx_shared_strings_context(session_context& session_cxt, const tokens& tokens, spreadsheet::iface::import_shared_strings* strings);
    virtual ~xlsx_shared_strings_context();

    virtual xml_context_base* create_child_context(xmlns_id_t ns, xml_token_t name);
    virtual void end_child_context(xmlns_id_t ns, xml_token_t name, xml_context_base* child);

    virtual void start_element(xmlns_id_t ns, xml_token_t name, const xml_attrs_t& attrs);
    virtual bool end_element(xmlns_id_t ns, xml_token_t name);
    virtual void characters(std::string_view str, bool transient);

private:
    spreadsheet::iface::import_shared_strings* mp_strings;
    string_pool m_pool;
    cell_buffer m_cell_buffer;
    pstring m_cur_str;
    bool m_in_segments;
};

/**
 * Context for xl/styles.xml part.  This part contains various styles used
 * in the sheets.
 */
class xlsx_styles_context : public xml_context_base
{
public:
    xlsx_styles_context(session_context& session_cxt, const tokens& tokens, spreadsheet::iface::import_styles* import_styles);
    virtual ~xlsx_styles_context();

    virtual xml_context_base* create_child_context(xmlns_id_t ns, xml_token_t name);
    virtual void end_child_context(xmlns_id_t ns, xml_token_t name, xml_context_base* child);

    virtual void start_element(xmlns_id_t ns, xml_token_t name, const xml_attrs_t& attrs);
    virtual bool end_element(xmlns_id_t ns, xml_token_t name);
    virtual void characters(std::string_view str, bool transient);

private:
    void start_element_number_format(const xml_token_pair_t& parent, const xml_attrs_t& attrs);

    void start_element_border(const xml_token_pair_t& parent, const xml_attrs_t& attrs);
    void start_element_diagonal(const xml_token_pair_t& parent, const xml_attrs_t& attrs);
    void start_border_color(const xml_attrs_t& attrs);
    void start_font_color(const xml_attrs_t& attrs);

    void end_element_number_format();

private:
    spreadsheet::iface::import_styles* mp_styles;
    string_pool m_pool;
    bool m_diagonal_up;
    bool m_diagonal_down;
    spreadsheet::border_direction_t m_cur_border_dir;
    bool m_cell_style_xf;
};

}

#endif
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
