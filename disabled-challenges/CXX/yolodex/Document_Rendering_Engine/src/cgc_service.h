/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define NUMERAL 0
#define UPPER_ALPHA 1
#define LOWER_ALPHA 2
#define ROMAN 3

#define NUMERAL_STR "numeral"
#define UPPER_ALPHA_STR "ALPHA"
#define LOWER_ALPHA_STR "alpha"
#define ROMAN_STR "roman"

#define LINE_BORDER_TYPE 0
#define STAR_BORDER_TYPE 1

#define LINE_BORDER_STR "line"
#define STAR_BORDER_STR "star"

#define VERTICAL_LINE_BORDER "|"
#define HORIZONTAL_LINE_BORDER '-'
#define INTERSECT_LINE_BORDER "+"
#define VERTICAL_STAR_BORDER "*"
#define HORIZONTAL_STAR_BORDER '*'

#define TEXT_TAG "text"
#define LIST_TAG "list"
#define PARAGRAPH_TAG "pgraph"
#define PAGE_TAG "page"
#define DOCUMENT_TAG "document"
#define LENGTH_TAG "length"
#define WIDTH_TAG "width"
#define ELEMENT_TAG "element"
#define TYPE_TAG "type"
#define COLUMN_TAG "column"
#define ROWS_TAG "rows"
#define FIELDS_TAG "fields"
#define HEADER_TAG "header"
#define FIELD_TAG "field"
#define TABLE_TAG "table"
#define ROW_TAG "row"
#define MACRO_TAG "macro"
#define BORDER_TAG "border"

#define INDENT "     "
#define TAB "    "
#define LIST_INDENT "  "

#define MAX_NAME_SIZE 8

#define FLAG_PAGE 0x4347C000

#define DOC_ID_STRING "Document ID: "

typedef struct {
	char* name;
	void* children;
	void* next;
} Object;

typedef struct {
	char* (*body)(void *macros, Object* object);
	void* next;
	char* name;
} Macro;

char* FourByFourTable_Macro = "<document>\n"
							  "<macro>\n"
							  "<4x4Table>\n"
							  "<table>\n"
							  "<rows>\n"
							  "4\n"
							  "</rows>\n"
							  "<fields>\n"
							  "4\n"
   							  "</fields>\n"
							  "</table>\n"
							  "</4x4Table>\n"
							  "</macro>\n"
							  "</document>\n";

char* FiveByFiveTable_Macro = "<document>\n"
							  "<macro>\n"
							  "<5x5Table>\n"
							  "<table>\n"
							  "<rows>\n"
							  "5\n"
							  "</rows>\n"
							  "<fields>\n"
							  "5\n"
   							  "</fields>\n"
							  "</table>\n"
							  "</5x5Table>\n"
							  "</macro>\n"
							  "</document>\n";

char* AlphanumericOutline_Macro = "<document>\n"
							      "<macro>\n"
							      "<Outline>\n"
							      "<list>\n"
							      "<type>\n"
							      "roman\n"
							      "</type>\n"
							      "<element>\n"
							      "<list>\n"
							      "<type>\n"
							      "ALPHA\n"
							      "</type>\n"
							      "<element>\n"
							      "<list>\n"
							      "<type>\n"
							      "numeral\n"
							      "</type>\n"
							      "<element>\n"
							      "<list>\n"
							      "<type>\n"
							      "alpha\n"
							      "</type>\n"
							      "</list>\n"
							      "</element>\n"
							      "</list>\n"
							      "</element>\n"					
							      "</list>\n"
							      "</element>\n"
							      "</list>\n"
							      "</Outline>\n"
							      "</macro>\n"
							      "</document>\n";

char* BulletedOutline_Macro = "<document>\n"
							      "<macro>\n"
							      "<Bulleted>\n"
							      "<list>\n"
							      "<element>\n"
							      "<list>\n"
							      "<type>\n"
							      "-\n"
							      "</type>\n"
							      "<element>\n"
							      "<list>\n"
							      "<type>\n"
							      ">\n"
							      "</type>\n"
							      "<element>\n"
							      "<list>\n"
							      "<type>\n"
							      "+\n"
							      "</type>\n"
							      "</list>\n"
							      "</element>\n"
							      "</list>\n"
							      "</element>\n"					
							      "</list>\n"
							      "</element>\n"
							      "</list>\n"
							      "</Bulleted>\n"
							      "</macro>\n"
							      "</document>\n";