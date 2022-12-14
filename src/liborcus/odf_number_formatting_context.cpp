/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "odf_number_formatting_context.hpp"
#include "odf_namespace_types.hpp"
#include "odf_token_constants.hpp"
#include "odf_helper.hpp"

#include <orcus/measurement.hpp>
#include <orcus/spreadsheet/import_interface.hpp>
#include <orcus/spreadsheet/styles.hpp>

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

namespace orcus {

namespace {

class number_style_attr_parser
{
    std::string_view m_country_code;
    std::string_view m_style_name;
    std::string_view m_language;
    bool m_volatile;

public:

    number_style_attr_parser():
        m_volatile(false)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_number)
        {
            switch(attr.name)
            {
                case XML_country:
                    m_country_code = attr.value;
                break;
                case XML_language:
                    m_language = attr.value;
                break;
                default:
                    ;
            }
        }
        else if (attr.ns == NS_odf_style)
        {
            switch (attr.name)
            {
                case XML_name:
                    m_style_name = attr.value;
                break;
                case XML_volatile:
                    m_volatile = attr.value == "true";
                break;
                default:
                    ;
            }
        }
    }

    std::string_view get_style_name() const { return m_style_name;}
    std::string_view get_country_code() const { return m_country_code;}
    bool is_volatile() const { return m_volatile;}
    std::string_view get_language() const { return m_language;}
};

class number_attr_parser
{
    size_t m_decimal_places;
    size_t m_min_int_digits;
    bool m_grouping;

public:

    number_attr_parser() :
        m_decimal_places(0),
        m_min_int_digits(0),
        m_grouping(false)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_number)
        {
            switch (attr.name)
            {
                case XML_decimal_places:
                {
                    m_decimal_places = to_long(attr.value);
                }
                break;
                case XML_grouping:
                    m_grouping = attr.value == "true";
                break;
                case XML_min_integer_digits:
                    m_min_int_digits = to_long(attr.value);
                break;
                default:
                    ;
            }
        }
    }

    size_t get_decimal_places() const { return m_decimal_places;}
    bool is_grouped() const { return m_grouping;}
    size_t get_min_int_digits() const { return m_min_int_digits;}
    bool has_decimal_places() const { return m_decimal_places > 0;}
};

class scientific_number_attr_parser
{
    size_t m_decimal_places;
    bool m_grouping;
    size_t m_min_exp_digits;
    size_t m_min_int_digits;

public:

    scientific_number_attr_parser() :
        m_decimal_places(0),
        m_grouping(false),
        m_min_exp_digits(0),
        m_min_int_digits(0)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_number)
        {
            switch(attr.name)
            {
                case XML_decimal_places:
                    m_decimal_places = to_long(attr.value);
                break;
                case XML_grouping:
                    m_grouping = attr.value == "true";
                break;
                case XML_min_exponent_digits:
                    m_min_exp_digits = to_long(attr.value);
                break;
                case XML_min_integer_digits:
                    m_min_int_digits = to_long(attr.value);
                break;
                default:
                    ;
            }
        }
    }

    size_t get_decimal_places() const { return m_decimal_places;}
    bool is_grouped() const { return m_grouping;}
    size_t get_min_exp_digits() const { return m_min_exp_digits;}
    size_t get_min_int_digits() const { return m_min_int_digits;}
};

class generic_style_attr_parser
{
    std::string_view m_style_name;
    bool m_volatile;
    bool m_long;

public:
    generic_style_attr_parser() :
        m_volatile(false),
        m_long(false)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_style)
        {
            switch (attr.name)
            {
                case XML_name:
                    m_style_name = attr.value;
                break;
                case XML_volatile:
                    m_volatile = attr.value == "true";
                break;
                default:
                    ;
            }
        }
        else if (attr.ns == NS_odf_number)
            if (attr.name == XML_style)
                m_long = attr.value == "long";
    }

    std::string_view get_style_name() const { return m_style_name;}
    bool is_volatile() const { return m_volatile;}
    bool has_long() const { return m_long;}
};

class month_attr_parser
{
    bool m_style_name;
    bool m_textual;

public:
    month_attr_parser():
        m_style_name(false),
        m_textual(false)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_number)
        {
            if (attr.name == XML_style)
                m_style_name = attr.value == "long";
            if (attr.name == XML_textual)
                m_textual = attr.value == "true";
        }
    }

    bool has_long() const { return m_style_name;}
    bool is_textual() const { return m_textual;}
};

class seconds_attr_parser
{
    size_t m_decimal_places;
    bool m_style_name;

public:
    seconds_attr_parser():
        m_decimal_places(0),
        m_style_name(false)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_number)
        {
            if (attr.name == XML_style)
                m_style_name = attr.value == "long";
            if (attr.name == XML_decimal_places)
            {
                m_decimal_places = to_long(attr.value);
            }
        }
    }

    bool has_long() const { return m_style_name;}
    size_t get_decimal_places() const { return m_decimal_places;}
    bool has_decimal_places() const { return m_decimal_places > 0;}
};

class fraction_attr_parser
{
    size_t m_min_int_digits;
    size_t m_min_deno_digits;
    size_t m_min_num_digits;
    std::string_view m_deno_value;

    bool m_predefined_deno;

public:
    fraction_attr_parser():
        m_min_int_digits(0),
        m_min_deno_digits(0),
        m_min_num_digits(0),
        m_predefined_deno(false)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_number)
        {
            switch(attr.name)
            {
                case XML_min_integer_digits:
                    m_min_int_digits = to_long(attr.value);
                break;
                case XML_min_numerator_digits:
                    m_min_num_digits = to_long(attr.value);
                break;
                case XML_min_denominator_digits:
                    m_min_deno_digits = to_long(attr.value);
                break;
                case XML_denominator_value:
                {
                    m_deno_value = attr.value;
                    m_predefined_deno = true;
                }
                break;
                default:
                    ;
            }
        }
    }

    size_t get_min_int_digits() const { return m_min_int_digits;}
    size_t get_min_num_digits() const { return m_min_num_digits;}
    size_t get_min_deno_digits() const { return m_min_deno_digits;}
    std::string_view get_deno_value() const { return m_deno_value;}
    bool has_predefined_deno() const { return m_predefined_deno;}
};

class text_properties_attr_parser
{
    std::string_view m_color;
    bool color_absent;

public:
    text_properties_attr_parser():
        color_absent(true)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_fo)
        {
            switch (attr.name)
            {
                case XML_color:
                {
                    if (attr.value == "#000000")
                        m_color = "BLACK";
                    if (attr.value == "#ff0000")
                        m_color = "RED";
                    if (attr.value == "#00ff00")
                        m_color = "GREEN";
                    if (attr.value == "#0000ff")
                        m_color = "BLUE";
                    if (attr.value == "#ffff00")
                        m_color = "YELLOW";
                    if (attr.value == "#00ffff")
                        m_color = "CYAN";
                    if (attr.value == "#ff00ff")
                        m_color = "MAGENTA";
                    if (attr.value == "#ffffff")
                        m_color = "WHITE";
                    else
                        color_absent = false;
                }
            }
        }
    }

    std::string_view get_color() const { return m_color;}
    bool has_color() const { return !color_absent;}
};

class map_attr_parser
{
    string m_value;
    string m_sign;
    bool m_has_map;

public:
    map_attr_parser():
        m_has_map(false)
    {}

    void operator() (const xml_token_attr_t& attr)
    {
        if (attr.ns == NS_odf_style)
        {
            if (attr.name == XML_condition)
            {
                for (size_t i = 0; i < attr.value.size(); i++)
                {
                    if (attr.value[i] == '<' || attr.value[i] == '>' || attr.value[i] == '=')
                        m_sign = m_sign + attr.value[i];
                    if (isdigit(attr.value[i]))
                        m_value = m_value + attr.value[i];
                }
                m_has_map = true;
            }
        }
    }
    string get_value() const { return m_value;}
    string get_sign() const { return m_sign;}
    bool has_map() const { return m_has_map;}
};

}

number_formatting_context::number_formatting_context(
    session_context& session_cxt, const tokens& tk, odf_styles_map_type& styles,
    spreadsheet::iface::import_styles* iface_styles) :
    xml_context_base(session_cxt, tk),
    mp_styles(iface_styles),
    m_styles(styles)
{}

xml_context_base* number_formatting_context::create_child_context(xmlns_id_t /*ns*/, xml_token_t /*name*/)
{
    return nullptr;
}

void number_formatting_context::end_child_context(xmlns_id_t /*ns*/, xml_token_t /*name*/, xml_context_base* /*child*/)
{
}

void number_formatting_context::start_element(xmlns_id_t ns, xml_token_t name, const std::vector<xml_token_attr_t>& attrs)
{
    m_current_style.character_stream = std::string_view{};

    if (ns == NS_odf_number)
    {
        switch(name)
        {
            case XML_number_style:
            {
                number_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.name = func.get_style_name();
                m_current_style.is_volatile = func.is_volatile();
            }
            break;
            case XML_number:
            {
                number_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                if (func.is_grouped())
                {
                    if (func.get_min_int_digits() < 4)
                    {
                        m_current_style.number_formatting_code += "#,";
                        for (size_t i = 0; i < 3 - func.get_min_int_digits(); i++)
                        {
                            m_current_style.number_formatting_code += "#";
                        }
                        for (size_t i = 0; i < func.get_min_int_digits(); i++)
                        {
                            m_current_style.number_formatting_code += "0";
                        }
                    }
                    else
                    {
                        std::string temporary_code;
                        for(size_t i = 0; i < func.get_min_int_digits(); i++)
                        {
                            if (i % 3 == 0 && i != 0)
                                temporary_code += ",";
                            temporary_code += "0";
                        }
                        std::reverse(temporary_code.begin(), temporary_code.end());
                        m_current_style.number_formatting_code += temporary_code;
                    }
                }
                else
                {
                    if (func.get_min_int_digits() == 0)
                        m_current_style.number_formatting_code += "#";

                    for (size_t i = 0; i < func.get_min_int_digits(); i++)
                    {
                        m_current_style.number_formatting_code += "0";
                    }
                }
                if (func.has_decimal_places())
                {
                    m_current_style.number_formatting_code += ".";
                    for(size_t i = 0; i < func.get_decimal_places() ; i++)
                        m_current_style.number_formatting_code += "0";
                }
            }
            break;
            case XML_currency_style:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.name = func.get_style_name();
                m_current_style.is_volatile = func.is_volatile();
            }
            break;
            case XML_percentage_style:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.name = func.get_style_name();
                m_current_style.is_volatile = func.is_volatile();
            }
            break;
            case XML_scientific_number:
            {
                scientific_number_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);

                if (func.is_grouped())
                {
                    if (func.get_min_int_digits() < 4)
                    {
                        m_current_style.number_formatting_code += "#,";
                        for (size_t i = 0; i < 3 - func.get_min_int_digits(); i++)
                        {
                            m_current_style.number_formatting_code += "#";
                        }
                        for (size_t i = 0; i < func.get_min_int_digits(); i++)
                        {
                            m_current_style.number_formatting_code += "0";
                        }
                    }
                    else
                    {
                        std:: string temporary_code;
                        for(size_t i = 0; i < func.get_min_int_digits(); i++)
                        {
                            if (i % 3 == 0 && i != 0)
                                temporary_code += ",";
                            temporary_code += "0";
                        }
                        std::reverse(temporary_code.begin(), temporary_code.end());
                        m_current_style.number_formatting_code += temporary_code;
                    }
                }
                else
                {
                    if (func.get_min_int_digits() == 0)
                        m_current_style.number_formatting_code += "#";

                    for (size_t i = 0; i < func.get_min_int_digits(); i++)
                    {
                        m_current_style.number_formatting_code += "0";
                    }
                }

                m_current_style.number_formatting_code += ".";
                for(size_t i = 0; i < func.get_decimal_places() ; i++)
                    m_current_style.number_formatting_code += "0";

                m_current_style.number_formatting_code += "E+";
                for(size_t i = 0; i < func.get_min_exp_digits() ; i++)
                    m_current_style.number_formatting_code += "0";
            }
            break;
            case XML_boolean_style:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.name = func.get_style_name();
                m_current_style.is_volatile = func.is_volatile();
            }
            break;
            case XML_boolean:
            {
                m_current_style.number_formatting_code += "BOOLEAN";
            }
            break;
            case XML_fraction:
            {
                fraction_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);

                for (size_t i = 0; i < func.get_min_int_digits(); i++)
                    m_current_style.number_formatting_code += "#";

                if (func.get_min_int_digits() != 0)
                    m_current_style.number_formatting_code += " ";

                for (size_t i = 0; i < func.get_min_num_digits(); i++)
                    m_current_style.number_formatting_code += "?";

                m_current_style.number_formatting_code += "/";
                if (func.has_predefined_deno())
                    m_current_style.number_formatting_code += func.get_deno_value();
                else
                    for(size_t i = 0; i < func.get_min_deno_digits(); i++)
                        m_current_style.number_formatting_code += "?";
            }
            break;
            case XML_date_style:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.name = func.get_style_name();
                m_current_style.is_volatile = func.is_volatile();
            }
            break;
            case XML_day:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.number_formatting_code += "D";
                if (func.has_long())
                    m_current_style.number_formatting_code += "D";
            }
            break;
            case XML_month:
            {
                month_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.number_formatting_code += "M";
                if (func.has_long())
                    m_current_style.number_formatting_code += "M";
                if (func.is_textual())
                    m_current_style.number_formatting_code += "M";
                if (func.has_long() && func.is_textual())
                    m_current_style.number_formatting_code += "M";
            }
            break;
            case XML_year:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.number_formatting_code += "YY";
                if (func.has_long())
                    m_current_style.number_formatting_code += "YY";
            }
            break;
            case XML_time_style:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.name = func.get_style_name();
                m_current_style.is_volatile = func.is_volatile();
            }
            break;
            case XML_hours:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.number_formatting_code += "H";
                if (func.has_long())
                    m_current_style.number_formatting_code += "H";
            }
            break;
            case XML_minutes:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.number_formatting_code += "M";
                if (func.has_long())
                    m_current_style.number_formatting_code += "M";
            }
            break;
            case XML_seconds:
            {
                seconds_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.number_formatting_code += "S";
                if (func.has_long())
                    m_current_style.number_formatting_code += "S";
                if (func.has_decimal_places())
                    for (size_t i = 0; i < func.get_decimal_places(); i++)
                        m_current_style.number_formatting_code += "S";
            }
            break;
            case XML_am_pm:
            {
                m_current_style.number_formatting_code += " AM/PM";
            }
            break;
            case XML_text_style:
            {
                generic_style_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                m_current_style.name = func.get_style_name();
                m_current_style.is_volatile = func.is_volatile();
            }
            break;
            case XML_text_content:
            {
                m_current_style.number_formatting_code += "@";
            }
            break;
            default:
                ;
        }
    }
    if (ns == NS_odf_style)
    {
        switch (name)
        {
            case XML_text_properties:
            {
                text_properties_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                if (func.has_color())
                {
                    std::ostringstream os;
                    os << m_current_style.number_formatting_code << '[' << func.get_color() << ']';
                    m_current_style.number_formatting_code = os.str();
                }
            }
            break;
            case XML_map:
            {
                map_attr_parser func;
                func = std::for_each(attrs.begin(), attrs.end(), func);
                if (func.has_map())
                {
                    std::ostringstream os;
                    os << '[' << func.get_sign() << func.get_value() << ']' << m_current_style.number_formatting_code;
                    m_current_style.number_formatting_code = os.str();
                }
            }
            break;
            default:
                ;
        }
    }
}

bool number_formatting_context::end_element(xmlns_id_t ns, xml_token_t name)
{
    std::string_view character_content = m_current_style.character_stream;

    if (ns == NS_odf_number)
    {
        if (name == XML_number_style || name == XML_currency_style || name == XML_percentage_style
                || name == XML_text_style || name == XML_boolean_style || name == XML_date_style
                || name == XML_time_style)
        {
            if (m_current_style.is_volatile)
            {
                m_current_style.number_formatting_code += ";";
            }
            else
            {
                size_t id_number_format = 0;

                if (!m_current_style.number_formatting_code.empty())
                {
                    mp_styles->set_number_format_code(m_current_style.number_formatting_code);
                    id_number_format = mp_styles->commit_number_format();
                }

                mp_styles->set_xf_number_format(id_number_format);

                mp_styles->set_cell_style_name(m_current_style.name);
                mp_styles->set_cell_style_xf(mp_styles->commit_cell_style_xf());
                mp_styles->commit_cell_style();
                return true;
            }
        }
        else if (name == XML_currency_symbol)
        {
            std::ostringstream os;
            os << m_current_style.number_formatting_code << "[$" << character_content << ']';
            m_current_style.number_formatting_code = os.str();
        }
        else if (name == XML_text)
        {
            m_current_style.number_formatting_code += character_content;
        }
    }
    return false;
}


void number_formatting_context::characters(std::string_view str, bool transient)
{
    if (str != "\n")
    {
        if (transient)
            m_current_style.character_stream = m_pool.intern(str).first;
        else
            m_current_style.character_stream = str;
    }
}

void number_formatting_context::reset()
{
    m_current_style = number_formatting_style{};
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
