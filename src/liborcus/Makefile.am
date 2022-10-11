
AM_CPPFLAGS = -I$(top_srcdir)/include -I./include $(BOOST_CPPFLAGS)

EXTRA_PROGRAMS = \
	css-document-tree-test \
	json-document-tree-test \
	yaml-document-tree-test \
	xml-map-tree-test \
	common-test \
	format-detection-test \
	dom-tree-test \
	json-structure-tree-test \
	json-map-tree-test \
	xml-structure-tree-test \
	xpath-parser-test

TESTS =

if HAVE_STATIC_LIB
AM_CPPFLAGS += -D__ORCUS_STATIC_LIB=1
else
AM_CPPFLAGS += -D__ORCUS_BUILDING_DLL=1
endif

liborcus_@ORCUS_API_VERSION@_la_CXXFLAGS = \
	$(ZLIB_CFLAGS)

liborcus_@ORCUS_API_VERSION@_la_LDFLAGS = \
	-no-undefined $(BOOST_SYSTEM_LDFLAGS) $(BOOST_FILESYSTEM_LDFLAGS)

liborcus_@ORCUS_API_VERSION@_la_LIBADD = \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la \
	 $(BOOST_SYSTEM_LIBS) $(ZLIB_LIBS) $(BOOST_FILESYSTEM_LIBS)

AM_CPPFLAGS += -DSRCDIR=\""$(top_srcdir)"\"

lib_LTLIBRARIES = liborcus-@ORCUS_API_VERSION@.la
liborcus_@ORCUS_API_VERSION@_la_SOURCES = \
	config.cpp \
	css_document_tree.cpp \
	css_selector.cpp \
	detection_result.hpp \
	detection_result.cpp \
	dom_tree.cpp \
	format_detection.cpp \
	formula_result.hpp \
	formula_result.cpp \
	global.cpp \
	info.cpp \
	interface.cpp \
	json_document_tree.cpp \
	json_map_tree.hpp \
	json_map_tree.cpp \
	json_structure_mapper.hpp \
	json_structure_mapper.cpp \
	json_structure_tree.cpp \
	json_util.hpp \
	json_util.cpp \
	spreadsheet_interface.cpp \
	orcus_csv.cpp \
	orcus_json.cpp \
	orcus_xml.cpp \
	orcus_xml_impl.hpp \
	orcus_xml_impl.cpp \
	orcus_xml_map_def.cpp \
	measurement.cpp \
	xml_context_base.hpp \
	xml_context_base.cpp \
	xml_context_global.hpp \
	xml_context_global.cpp \
	xml_map_tree.hpp \
	xml_map_tree.cpp \
	xml_stream_handler.hpp \
	xml_stream_handler.cpp \
	xml_stream_parser.hpp \
	xml_stream_parser.cpp \
	xml_simple_stream_handler.hpp \
	xml_simple_stream_handler.cpp \
	xml_structure_mapper.hpp \
	xml_structure_mapper.cpp \
	xml_structure_tree.cpp \
	xpath_parser.cpp \
	yaml_document_tree.cpp \
	ooxml_namespace_types.cpp \
	ooxml_namespace_types.hpp \
	odf_namespace_types.hpp \
	odf_namespace_types_hpp.inl \
	odf_namespace_types.cpp \
	odf_namespace_types_cpp.inl \
	gnumeric_namespace_types.hpp \
	gnumeric_namespace_types.cpp \
	xls_xml_namespace_types.hpp \
	xls_xml_namespace_types.cpp \
	session_context.hpp \
	session_context.cpp \
	spreadsheet_impl_types.hpp \
	spreadsheet_impl_types.cpp \
	spreadsheet_types.cpp \
	spreadsheet_iface_util.hpp \
	spreadsheet_iface_util.cpp \
	string_helper.hpp \
	string_helper.cpp

if WITH_XLSX_FILTER

EXTRA_PROGRAMS += \
	xlsx-sheet-context-test

liborcus_@ORCUS_API_VERSION@_la_SOURCES += \
	ooxml_content_types.cpp \
	ooxml_content_types.hpp \
	ooxml_global.cpp \
	ooxml_global.hpp \
	ooxml_schemas.cpp \
	ooxml_schemas.hpp \
	ooxml_token_constants.hpp \
	ooxml_token_constants.inl \
	ooxml_tokens.cpp \
	ooxml_tokens.hpp \
	ooxml_tokens.inl \
	ooxml_types.hpp \
	ooxml_types.cpp \
	opc_context.cpp \
	opc_context.hpp \
	opc_reader.cpp \
	opc_reader.hpp \
	opc_reader.hpp \
	opc_token_constants.hpp \
	opc_token_constants.inl \
	opc_tokens.inl \
	orcus_xlsx.cpp \
	orcus_import_xlsx.cpp \
	xlsx_context.cpp \
	xlsx_context.hpp \
	xlsx_drawing_context.hpp \
	xlsx_drawing_context.cpp \
	xlsx_handler.cpp \
	xlsx_handler.hpp \
	xlsx_helper.cpp \
	xlsx_helper.hpp \
	xlsx_session_data.hpp \
	xlsx_session_data.cpp \
	xlsx_revision_context.cpp \
	xlsx_revision_context.hpp \
	xlsx_pivot_context.cpp \
	xlsx_pivot_context.hpp \
	xlsx_sheet_context.cpp \
	xlsx_sheet_context.hpp \
	xlsx_conditional_format_context.cpp \
	xlsx_conditional_format_context.hpp \
	xlsx_table_context.cpp \
	xlsx_table_context.hpp \
	xlsx_autofilter_context.cpp \
	xlsx_autofilter_context.hpp \
	xlsx_types.hpp \
	xlsx_types.cpp \
	xlsx_workbook_context.cpp \
	xlsx_workbook_context.hpp

# xlsx-sheet-context-test

xlsx_sheet_context_test_SOURCES = \
	formula_result.cpp \
	global.cpp \
	mock_spreadsheet.hpp \
	mock_spreadsheet.cpp \
	ooxml_global.cpp \
	ooxml_namespace_types.cpp \
	ooxml_schemas.cpp \
	ooxml_tokens.cpp \
	ooxml_types.cpp \
	session_context.cpp \
	spreadsheet_interface.cpp \
	xlsx_autofilter_context.cpp \
	xlsx_conditional_format_context.cpp \
	xlsx_helper.cpp \
	xlsx_session_data.cpp \
	xlsx_sheet_context.cpp \
	xlsx_sheet_context_test.cpp \
	xlsx_types.cpp \
	xml_context_base.cpp \
	xml_context_global.cpp

xlsx_sheet_context_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

xlsx_sheet_context_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

TESTS += \
	 xlsx-sheet-context-test

endif # WITH_XLSX_FILTER

if WITH_XLS_XML_FILTER

liborcus_@ORCUS_API_VERSION@_la_SOURCES += \
	xls_xml_tokens.hpp \
	xls_xml_tokens.inl \
	xls_xml_tokens.cpp \
	xls_xml_token_constants.hpp \
	xls_xml_token_constants.inl \
	orcus_xls_xml.cpp \
	xls_xml_detection_handler.hpp \
	xls_xml_detection_handler.cpp \
	xls_xml_handler.hpp \
	xls_xml_handler.cpp \
	xls_xml_context.hpp \
	xls_xml_context.cpp

endif # WITH_XLS_XML_FILTER

if WITH_ODS_FILTER

liborcus_@ORCUS_API_VERSION@_la_SOURCES += \
	odf_para_context.hpp \
	odf_para_context.cpp \
	odf_styles.hpp \
	odf_styles.cpp \
	odf_styles_context.hpp \
	odf_styles_context.cpp \
	odf_number_formatting_context.hpp \
	odf_number_formatting_context.cpp \
	odf_token_constants.hpp \
	odf_token_constants.inl \
	odf_tokens.hpp \
	odf_tokens.inl \
	odf_tokens.cpp \
	ods_content_xml_context.hpp \
	ods_content_xml_context.cpp \
	ods_content_xml_handler.hpp \
	ods_content_xml_handler.cpp \
	ods_dde_links_context.hpp \
	ods_dde_links_context.cpp \
	ods_session_data.hpp \
	ods_session_data.cpp \
	odf_helper.hpp \
	odf_helper.cpp \
	orcus_ods.cpp \
	orcus_import_ods.cpp

# odf-helper-test

EXTRA_PROGRAMS += \
	odf-helper-test

odf_helper_test_SOURCES = \
	odf_helper.cpp \
	string_helper.cpp \
	odf_helper_test.cpp

odf_helper_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

odf_helper_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

TESTS += \
	 odf-helper-test

endif # WITH_ODS_FILTER

if WITH_GNUMERIC_FILTER

liborcus_@ORCUS_API_VERSION@_la_SOURCES += \
	gnumeric_cell_context.hpp \
	gnumeric_context.hpp \
	gnumeric_detection_handler.hpp \
	gnumeric_detection_handler.cpp \
	gnumeric_handler.hpp \
	gnumeric_helper.hpp \
	gnumeric_sheet_context.hpp \
	gnumeric_token_constants.hpp \
	gnumeric_token_constants.inl \
	gnumeric_tokens.hpp \
	gnumeric_cell_context.cpp \
	gnumeric_context.cpp \
	gnumeric_handler.cpp \
	gnumeric_helper.cpp \
	gnumeric_sheet_context.cpp \
	gnumeric_tokens.cpp \
	gnumeric_tokens.inl \
	orcus_gnumeric.cpp

liborcus_@ORCUS_API_VERSION@_la_LDFLAGS += \
	$(BOOST_IOSTREAMS_LDFLAGS)

liborcus_@ORCUS_API_VERSION@_la_LIBADD += \
	$(BOOST_IOSTREAMS_LIBS)

# gnumeric-cell-context-test

EXTRA_PROGRAMS += \
	gnumeric-cell-context-test \
	gnumeric-sheet-context-test \
	gnumeric-helper-test

gnumeric_cell_context_test_SOURCES = \
	session_context.cpp \
	gnumeric_cell_context_test.cpp \
	gnumeric_cell_context.cpp \
	xml_context_base.cpp \
	gnumeric_namespace_types.cpp \
	gnumeric_tokens.cpp \
	odf_namespace_types.cpp \
	spreadsheet_interface.cpp \
	mock_spreadsheet.hpp \
	mock_spreadsheet.cpp

gnumeric_cell_context_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

orcus_gnumeric_cell_context_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

TESTS += gnumeric-cell-context-test

# gnumeric-sheet-context-test

gnumeric_sheet_context_test_SOURCES = \
	session_context.cpp \
	gnumeric_sheet_context_test.cpp \
	gnumeric_sheet_context.cpp \
	gnumeric_cell_context.cpp \
	gnumeric_helper.cpp \
	xml_context_base.cpp \
	gnumeric_namespace_types.cpp \
	gnumeric_tokens.cpp \
	odf_namespace_types.cpp \
	spreadsheet_interface.cpp \
	mock_spreadsheet.hpp \
	mock_spreadsheet.cpp \
	string_helper.cpp

gnumeric_sheet_context_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

gnumeric_sheet_context_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

TESTS += gnumeric-sheet-context-test

# gnumeric-helper-test

gnumeric_helper_test_SOURCES = \
	gnumeric_helper_test.cpp \
	string_helper.hpp \
	string_helper.cpp

gnumeric_helper_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

gnumeric_helper_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

TESTS += gnumeric-helper-test

endif # WITH_GNUMERIC_FILTER

# css-document-tree-test

css_document_tree_test_SOURCES = \
	css_document_tree.cpp \
	css_document_tree_test.cpp

css_document_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la \
	$(BOOST_FILESYSTEM_LIBS) $(BOOST_SYSTEM_LIBS)

# json-document-tree-test

json_document_tree_test_SOURCES = \
	json_document_tree.cpp \
	json_util.cpp \
	json_document_tree_test.cpp

json_document_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la \
	$(BOOST_FILESYSTEM_LIBS) $(BOOST_SYSTEM_LIBS)

json_document_tree_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

# yaml-document-tree-test

yaml_document_tree_test_SOURCES = \
	yaml_document_tree.cpp \
	json_util.cpp \
	yaml_document_tree_test.cpp

yaml_document_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la \
	$(BOOST_FILESYSTEM_LIBS) $(BOOST_SYSTEM_LIBS)

yaml_document_tree_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

# xml-map-tree-test

xml_map_tree_test_SOURCES = \
	xml_map_tree.cpp \
	xml_map_tree.hpp \
	xpath_parser.hpp \
	xpath_parser.cpp \
	spreadsheet_impl_types.hpp \
	spreadsheet_impl_types.cpp \
	xml_map_tree_test.cpp

xml_map_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

# xml-structure-tree-test

xml_structure_tree_test_SOURCES = \
	string_helper.cpp \
	xml_structure_tree.cpp \
	xml_structure_mapper.cpp \
	xml_structure_tree_test.cpp

xml_structure_tree_test_CPPFLAGS = -I$(top_builddir)/lib/liborcus/liborcus.la $(AM_CPPFLAGS)

xml_structure_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la \
	$(BOOST_FILESYSTEM_LIBS) $(BOOST_SYSTEM_LIBS)

# common-test

common_test_SOURCES = \
	global.cpp \
	common_test.cpp

common_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

# format-detection-test

format_detection_test_SOURCES = \
	format_detection_test.cpp

format_detection_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

# dom-tree-test

dom_tree_test_SOURCES = dom_tree_test.cpp
dom_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

# json-structure-tree-test

json_structure_tree_test_SOURCES = json_structure_tree_test.cpp
json_structure_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la \
	$(BOOST_SYSTEM_LIBS) $(BOOST_FILESYSTEM_LIBS)

# json-map-tree-test

json_map_tree_test_SOURCES = json_map_tree_test.cpp \
	json_map_tree.cpp \
	spreadsheet_impl_types.cpp
json_map_tree_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

# xpath-parser-test

xpath_parser_test_SOURCES = \
	xpath_parser_test.cpp \
	xpath_parser.cpp
xpath_parser_test_LDADD = \
	liborcus-@ORCUS_API_VERSION@.la \
	../parser/liborcus-parser-@ORCUS_API_VERSION@.la

TESTS += \
	css-document-tree-test \
	json-document-tree-test \
	yaml-document-tree-test \
	xml-map-tree-test \
	common-test \
	format-detection-test \
	dom-tree-test \
	json-structure-tree-test \
	json-map-tree-test \
	xml-structure-tree-test \
	xpath-parser-test

distclean-local:
	rm -rf $(TESTS)
