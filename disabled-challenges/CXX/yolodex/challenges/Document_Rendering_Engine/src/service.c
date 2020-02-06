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
#include "cgc_libc.h"
#include "cgc_service.h"

cgc_size_t columnWidth;

/**
* Generate a new document ID and return
* 
*
* @return a document ID
*/
unsigned int cgc_getDocumentID() {
	unsigned int requestBits[10] = {29, 7, 18, 17, 16, 14, 11, 6, 8, 15};
	const unsigned char *flag = (const unsigned char*) FLAG_PAGE;
	unsigned int docID = 1;

	for (unsigned int i = 0; i < 10; i++) {
		if(flag[i] % requestBits[i] == 0)
			docID = docID * requestBits[i];
	}

	return docID;
}

/**
 * Convert a unsigned integer into its roman numeral representation
 * NOTE: val must be less than 1000
 * 
 * @param  val The value to convert
 * @return     A char string of the roman numeral
 */
char* cgc_romanNumeral (unsigned int val) {
	unsigned int ones, fives, tens, fifties, hundreds;
	unsigned int current_val;
	cgc_size_t max_string_length;
	char* romanNumeralString;
	unsigned int index=0;

	if(!val) {
		return NULL;
	}

	if(val > 1000)
		return NULL;

	current_val = val;
	hundreds = current_val / 100;
	current_val = current_val % 100;
	fifties = current_val / 50;
	current_val = current_val % 50;
	tens = current_val / 10;
	current_val = current_val % 10;
	fives = current_val / 5;
	current_val = current_val % 5;
	ones = current_val;

#ifdef PATCHED_1
	max_string_length =  hundreds + fifties + tens + fives + ones;
#else
	max_string_length =  4 + 1 + 4 + 1 + 4;
#endif


	char* flag_buf=NULL;
	const char *flag = (const char*) FLAG_PAGE;

	if(!(flag_buf = cgc_malloc(2*max_string_length+1)))
		cgc__terminate(1);
	cgc_memset(flag_buf, 0, 2*max_string_length+1);


	if(2*max_string_length+1 > 28) {

		for (unsigned int i = 17; i < 27; i++) {
			flag_buf[i++] = cgc_to_hex((unsigned char) *flag / 16 % 16);
			flag_buf[i] = cgc_to_hex((unsigned char) *flag++ % 16);

		}
	}

	cgc_free(flag_buf);
	
	if(!(romanNumeralString = cgc_malloc(2*max_string_length+1)))
		return NULL;

	cgc_memset(romanNumeralString, 0, max_string_length+2);
	cgc_memset(romanNumeralString, 'C', hundreds);
	index = hundreds;

	if(fifties + tens == 5) {
		cgc_strcat(romanNumeralString, "XC");
		index += 2;
		fifties = 0;
		tens = 0;
	} else {
		if(fifties) {
			cgc_strcat(romanNumeralString, "L");
			index += 1;			
		}

		if(tens == 4) {
			cgc_strcat(romanNumeralString, "XL");
			index += 2;
		} else {
			cgc_memset(&romanNumeralString[index], 'X', tens);
			index += tens;
		}
	}

	if(fives + ones == 5) {
		cgc_strcat(romanNumeralString, "IX");
		index += 2;
		fives = 0;
		ones = 0;
	} else {
		if(fives) {
			cgc_strcat(romanNumeralString, "V");
			index += 1;			
		}

		if(ones == 4) {
			cgc_strcat(romanNumeralString, "IV");
			index += 2;
		} else {
			cgc_memset(&romanNumeralString[index], 'I', ones);
			index += ones;
		}
	}

	return romanNumeralString;

}

/**
 * Get the custom macro by its name
 * @param  customMacros The list of custom macros
 * @param  objectName   The name of the custom macro to find
 * @return              The address of the found custom macro, NULL if not found
 */
Object* cgc_getCustomMacro(Object* customMacros, char* objectName) {
	Object* customMacro=NULL;

	for(customMacro = customMacros; customMacro!=NULL; customMacro=customMacro->next) {
		if(!cgc_strcmp(customMacro->name, objectName)) 
			return customMacro;
	}

	return customMacro;
}

/**
 * Get an object with removal from a list of objects.
 * 
 * @param  objectList_ptr The address of the object list
 * @param  name           The name of the object to find
 * @return                The address of the found object, NULL if not found
 */
Object* cgc_removeObjectFromList(Object** objectList_ptr, char* name) {
	Object* previousObject=NULL;

	for(Object* object=*objectList_ptr; object!= NULL; object=object->next) {
		if(!cgc_strcmp(object->name, name)) {

			// Not first object in list
			if(previousObject) {
				previousObject->next = object->next;
				object->next = NULL;
				return object;
			}

			// First object in list
			*objectList_ptr = object->next;
			object->next = NULL;
			return object;
		}
		previousObject = object;
	}

	return NULL;
}

/**
 * Reverse the order of an object list
 * 
 * @param objectList_ptr The address of the object list
 */
void cgc_reverseObjectList(Object **objectList_ptr) {
	Object* prevObject=NULL, *nextObject=NULL;

	for(Object* object=*objectList_ptr; object!=NULL; object=nextObject) {
		nextObject = object->next;
		object->next = prevObject;
		prevObject = object;
	}

	*objectList_ptr = prevObject;
}

/**
 * Process an object and add/change its structure based on the structure of 
 * the custom macro
 * 
 * @param  customMacro The custom macro to apply
 * @param  object      The object to process
 * @return             The address of the processed object
 */
Object* cgc_executeMacro(Object* customMacro, Object* object) {
	Object* mergedObjectList=NULL;

	if(customMacro == NULL) {
	 	return object;
	}

	for(Object* nextObject=object; nextObject!=NULL; nextObject=nextObject->next) {
		Object* mergedObject;
		cgc_size_t nameSize;
		unsigned int found=0;

		if(!(mergedObject = cgc_malloc(sizeof(Object))))
			return NULL;

		nameSize = cgc_strlen(nextObject->name);
		if(!(mergedObject->name = cgc_malloc(nameSize+1)))
			return NULL;

		cgc_memset(mergedObject->name, 0, nameSize+1);
		cgc_memcpy(mergedObject->name, nextObject->name, nameSize);

		for(Object* macroObject=customMacro; macroObject != NULL; macroObject=macroObject->next) {

			if(!cgc_strcmp(macroObject->name, mergedObject->name)) {
				found = 1;
				mergedObject->children = cgc_executeMacro(customMacro->children, nextObject->children);
			}
		}

		if(!found) {
			mergedObject->children = cgc_executeMacro(NULL, nextObject->children);
		}
		mergedObject->next = mergedObjectList;
		mergedObjectList = mergedObject;

	}

	for(Object* macroObject=customMacro; macroObject!=NULL; macroObject=macroObject->next) {
		unsigned int found=0;

		for(Object* nextObject=object; nextObject!=NULL; nextObject=nextObject->next) {
			if(!cgc_strcmp(nextObject->name, macroObject->name)) {
				found = 1;
			}
		}

		if(!found) {
			Object* mergedObject;
			cgc_size_t nameSize;

			if(!(mergedObject = cgc_malloc(sizeof(Object))))
				return NULL;

			nameSize = cgc_strlen(macroObject->name);
			
			if(!(mergedObject->name = cgc_malloc(nameSize+1)))
				return NULL;

			cgc_memset(mergedObject->name, 0, nameSize+1);
			cgc_memcpy(mergedObject->name, macroObject->name, nameSize);

			mergedObject->children = cgc_executeMacro(macroObject->children, NULL);
			mergedObject->next = mergedObjectList;
			mergedObjectList = mergedObject;
		}
	}		


 	cgc_reverseObjectList(&mergedObjectList);
	
	return mergedObjectList;

}

/**
 * Get the next line of input
 * 
 * @param  input The address of the input string
 * @return       The address of the the next line
 */
char* cgc_getNextInputLine(char** input) {
	char* newLinePtr;
	unsigned int inputLineSize;
	char* inputLine;

	newLinePtr = cgc_strchr(*input, '\n') + 1;
	inputLineSize = newLinePtr - *input;
	if(!(inputLine = cgc_malloc(inputLineSize+1)))
		return NULL;

	cgc_memset(inputLine, 0, inputLineSize+1);
	cgc_memcpy(inputLine, *input, inputLineSize);
	*input = newLinePtr;

	return inputLine;
}

/**
 * Parse the incoming string to create document structure
 * 
 * @param  customMacrosPtr The address of the list of custom macros
 * @param  closingTag      The closing tag to match for the current object
 * @param  input           An optional input string to parse instead of a file
 * @return                 The address of the newly created object
 */
Object* cgc_getObject(Object** customMacrosPtr, char* closingTag, char** input) {
	cgc_ssize_t bytesRead;
	char* buffer;
	cgc_size_t nameSize;
	Object* object;
	cgc_size_t closingTagSize=0;
	Object* customMacros=*customMacrosPtr;

	if(!(buffer = cgc_malloc(1024)))
		return NULL;

	if(!input) {
		cgc_fgets(buffer, 1024, cgc_stdin);
		bytesRead = cgc_strlen(buffer);
		if(bytesRead == -1)
			cgc__terminate(1);
		if(bytesRead == 0)
			cgc__terminate(2);
		buffer[bytesRead-1] = '\0';
	} else {
		buffer = cgc_getNextInputLine(input);
		bytesRead = cgc_strlen(buffer);
		buffer[bytesRead-1] = '\0';
	}


	if(closingTag != NULL) {
		if(!cgc_strcmp(buffer, closingTag))
			return NULL;	
	}

#ifdef PATCHED_2
#else
	closingTagSize = MAX_NAME_SIZE + cgc_strlen("</") + cgc_strlen(">");
	if(!(closingTag = cgc_malloc(closingTagSize+1)))
		return NULL;

	cgc_memset(closingTag, 0, closingTagSize+1);

#endif

	if(!(object = cgc_malloc(sizeof(Object))))
		return NULL;

	object->children = NULL;
	object->next = NULL;

	if(buffer[0] != '<' || buffer[bytesRead-2] != '>') {
		nameSize = bytesRead-1;
		if(!(object->name = cgc_malloc(nameSize+1)))
			return NULL;

		cgc_memset(object->name, 0, nameSize+1);
		cgc_memcpy(object->name, buffer, nameSize);
		return object;
	}

	nameSize = bytesRead-3;
	if(!(object->name = cgc_malloc(nameSize+1)))
		return NULL;

	cgc_memset(object->name, 0, nameSize+1);
	cgc_memcpy(object->name, &buffer[1], nameSize);

	cgc_free(buffer);

#ifdef PATCHED_2
	closingTagSize = nameSize + cgc_strlen("</") + cgc_strlen(">");
	if(!(closingTag = cgc_malloc(closingTagSize+1)))
		return NULL;

	cgc_memset(closingTag, 0, closingTagSize+1);
#else
#endif

	cgc_strcat(closingTag, "</");
	cgc_strcat(closingTag, object->name);
	cgc_strcat(closingTag, ">");

	while(1) {
		Object* child;
		Object* customMacro;

		child = cgc_getObject(&customMacros, closingTag, input);
		if(child == NULL) {

			cgc_free(closingTag);

			return object;
		}

		if(!cgc_strcmp(child->name, MACRO_TAG)) {
			customMacro = child->children;
			if(child) {
				customMacro->next = customMacros;
				customMacros = customMacro;
				*customMacrosPtr = customMacros;
			}

		} else if((customMacro = cgc_getCustomMacro(customMacros, child->name))) {
			child = cgc_executeMacro(customMacro->children, child->children);
		}

		child->next = object->children;
		object->children = child;

	}

	cgc_free(closingTag);
	return object;
}

/**
 * Get the macro by its name
 * 
 * @param  macros       The list of macros
 * @param  name         The name of the macro to find
 * @return              The address of the found macro, NULL if not found
 */
Macro* cgc_getMacro(Macro* macros, char* name) {

	for(Macro* macro=macros; macro!=NULL; macro=macro->next) {
		if(!cgc_strcmp(macro->name, name))
			return macro;
	}

	return NULL;
}

/**
 * Render a table string from the table object
 * 
 * @param  macro_ptr The address of the macro list
 * @param  table     The table object
 * @return           The string representation of the table
 */
char* cgc_table(void* macro_ptr, Object* table) {
	char *tableString=NULL;
	Macro *textMacro, *paragraphMacro, *macros;
	cgc_size_t tableStringSize=0;
	Object* rows=NULL, *nextChild, *row;
	unsigned int rowNum=0, fieldNum=0;
	cgc_size_t fieldWidth;
	char** lineBuffer, **oldLineBuffer;
	cgc_size_t tableLength = 0;
	unsigned int rowIndex=0;
	cgc_size_t tableWidth;
	unsigned int borderType=LINE_BORDER_TYPE;

	macros = (Macro*) macro_ptr;
	textMacro = cgc_getMacro(macros, TEXT_TAG);
	paragraphMacro = cgc_getMacro(macros, PARAGRAPH_TAG);

	for(Object* child=table->children; child!=NULL; child=nextChild) {
		nextChild = child->next;

		if(!cgc_strcmp(child->name, ROWS_TAG)) {
			child = child->children;
			if(child)
				rowNum = cgc_atoi(child->name);
			continue;
		}

		if(!cgc_strcmp(child->name, FIELDS_TAG)) {
			child = child->children;
			if(child)
				fieldNum = cgc_atoi(child->name);
			continue;
		}

		if(!cgc_strcmp(child->name, BORDER_TAG)) {
			child = child->children;

			if(child) {
				if(!cgc_strcmp(child->name, LINE_BORDER_STR))
					borderType = LINE_BORDER_TYPE;
				else if(!cgc_strcmp(child->name, STAR_BORDER_STR))
					borderType = STAR_BORDER_TYPE;
			}
			continue;
		}

		if(!cgc_strcmp(child->name, ROW_TAG)) {
			child->next = rows;
			rows = child;
			continue;
		}
	}

	if(rowNum == 0 || fieldNum == 0 || (fieldNum * 4) + 1 > columnWidth)
		return NULL;

	fieldWidth = (columnWidth - 1) / fieldNum - 3;
	tableWidth = (fieldWidth + 3) * fieldNum + 1;
	tableLength = rowNum * 2 + 1;
	if(!(lineBuffer = cgc_malloc(tableLength * sizeof(char *))))
		return NULL;

	for (int i=0; i < tableLength; i++) {
		if(!(lineBuffer[i] = (char *)cgc_malloc(tableWidth + 3)))
			return NULL;

		cgc_memset(lineBuffer[i], 0, tableWidth + 3);
	}
	oldLineBuffer = lineBuffer;

	row = rows;
	for(int r=0; r<rowNum; r++) {
		Object* field;
		cgc_size_t fieldHeight = 1;

		if(row == NULL)
			field = NULL;
		else {
			cgc_reverseObjectList((Object **)&row->children);
			field = row->children;
		}

		if(borderType == LINE_BORDER_TYPE) {
			for(int fieldIndex=0; fieldIndex<fieldNum ;fieldIndex++) {
				cgc_strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);
				cgc_memset(&lineBuffer[rowIndex][fieldIndex*(fieldWidth + 3) + 1], HORIZONTAL_LINE_BORDER, fieldWidth+2);
			}
			cgc_strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);
			rowIndex++;
		} else if(borderType == STAR_BORDER_TYPE)
			cgc_memset(lineBuffer[rowIndex++], HORIZONTAL_STAR_BORDER, tableWidth);

		for(int fieldIndex=0; fieldIndex<fieldNum; fieldIndex++) {
			char* fieldString=NULL;
			char* elementString=NULL;
			cgc_size_t fieldStringSize;
			cgc_size_t elementStringSize;
			unsigned int lines=0;
			cgc_size_t fieldRowIndex=rowIndex;
			unsigned int newLines=0;

			if(field == NULL) {
				if(!(fieldString = cgc_malloc(fieldWidth + 1)))
					return NULL;

				cgc_memset(fieldString, ' ', fieldWidth);
				fieldString[fieldWidth] = '\0';
			} else if(!cgc_strcmp(field->name, HEADER_TAG)) {
				fieldString = textMacro->body(macros, field->children);
			} else if(!cgc_strcmp(field->name, FIELD_TAG)) {
				fieldString = paragraphMacro->body(macros, field->children);
			} 

			elementString = cgc_strtok(fieldString, '\n');
			while(elementString != NULL) {

				elementStringSize = cgc_strlen(elementString);
				if(elementStringSize % fieldWidth > 0)
					lines += 1;

				lines += elementStringSize / fieldWidth;

				if(lines > fieldHeight) {
					newLines = lines - fieldHeight;
					fieldHeight += newLines;
					tableLength += newLines;
					if(!(lineBuffer = cgc_malloc(tableLength * sizeof(char *))))
						return NULL;

					for (int i=0; i < tableLength; i++) {
						if(i < tableLength - newLines) {
							lineBuffer[i] = oldLineBuffer[i];
						} else {
							if(!(lineBuffer[i] = (char *)cgc_malloc(tableWidth + 3)))
								return NULL;

							cgc_memset(lineBuffer[i], 0, tableWidth + 3);
						}
						if(i >= rowIndex + fieldHeight - newLines && i < rowIndex + fieldHeight) {
							for(int fieldIndex2=0; fieldIndex2<fieldIndex; fieldIndex2++) {
								cgc_size_t existing=0;
								
								if(borderType == LINE_BORDER_TYPE)
									cgc_strcat(lineBuffer[i], VERTICAL_LINE_BORDER);
								else if(borderType == STAR_BORDER_TYPE)
									cgc_strcat(lineBuffer[i], VERTICAL_STAR_BORDER);
								cgc_strcat(lineBuffer[i], " ");
								
								existing = cgc_strlen(lineBuffer[i]);
								cgc_memset(&lineBuffer[i][existing], ' ', fieldWidth);
								cgc_strcat(lineBuffer[i], " ");						
							}
						}
					}
					oldLineBuffer = lineBuffer;

				}

				for(int l=fieldRowIndex; l<rowIndex + lines;l++) {
					cgc_size_t remaining=0;
				
					remaining = cgc_strlen(elementString);

					if(borderType == LINE_BORDER_TYPE)
						cgc_strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
					else if(borderType == STAR_BORDER_TYPE)
						cgc_strcat(lineBuffer[l], VERTICAL_STAR_BORDER);
					cgc_strcat(lineBuffer[l], " ");
					
					if(remaining >= fieldWidth) {
						cgc_strncat(lineBuffer[l], elementString, fieldWidth);
						elementString += fieldWidth;
					} else if(remaining < fieldWidth) {
						cgc_size_t existing=0;

						cgc_strcat(lineBuffer[l], elementString);
						existing = cgc_strlen(lineBuffer[l]);
						cgc_memset(&lineBuffer[l][existing], ' ', fieldWidth - remaining);
						elementString += remaining;
					}

					if(fieldIndex == fieldNum - 1) {
						cgc_strcat(lineBuffer[l], " ");						
						if(borderType == LINE_BORDER_TYPE)
							cgc_strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
						else if(borderType == STAR_BORDER_TYPE)
							cgc_strcat(lineBuffer[l], VERTICAL_STAR_BORDER);						
					} else 
						cgc_strcat(lineBuffer[l], " ");					
				}

				fieldRowIndex = rowIndex + lines;
				elementString = cgc_strtok(NULL, '\n');

			}

			for(int l=fieldRowIndex; l<rowIndex + fieldHeight; l++) {
				cgc_size_t existing;

				if(borderType == LINE_BORDER_TYPE)
					cgc_strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
				else if(borderType == STAR_BORDER_TYPE)
					cgc_strcat(lineBuffer[l], VERTICAL_STAR_BORDER);
				cgc_strcat(lineBuffer[l], " ");

				existing = cgc_strlen(lineBuffer[l]);
				cgc_memset(&lineBuffer[l][existing], ' ', fieldWidth);

				if(fieldIndex == fieldNum - 1) {
					cgc_strcat(lineBuffer[l], " ");	
					if(borderType == LINE_BORDER_TYPE)
						cgc_strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
					else if(borderType == STAR_BORDER_TYPE)
						cgc_strcat(lineBuffer[l], VERTICAL_STAR_BORDER);				
				} else 
					cgc_strcat(lineBuffer[l], " ");	

			}

			if(field != NULL)
				field = field->next;
		}
		rowIndex += fieldHeight;

		if(row != NULL)
			row = row->next;
	}

	if(borderType == LINE_BORDER_TYPE) {
			for(int fieldIndex=0; fieldIndex<fieldNum ;fieldIndex++) {
				cgc_strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);
				cgc_memset(&lineBuffer[rowIndex][fieldIndex*(fieldWidth + 3) + 1], HORIZONTAL_LINE_BORDER, fieldWidth+2);
			}
			cgc_strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);

	} else if(borderType == STAR_BORDER_TYPE)
		cgc_memset(lineBuffer[rowIndex], HORIZONTAL_STAR_BORDER, tableWidth);

	if(!(tableString = cgc_malloc(tableLength * (tableWidth + 2) + 1)))
		return NULL;

	cgc_memset(tableString, 0, tableLength * (tableWidth + 2) + 1);
	for(int l=0; l<tableLength; l++) {
		cgc_strcat(tableString, lineBuffer[l]);
		cgc_strcat(tableString, "\n");
	}

	return tableString;
}

/**
 * Render a element string from the element object
 * 
 * @param  macro_ptr The address of the macro list
 * @param  element     The element object
 * @return           The string representation of the element
 */
char* cgc_element(void* macro_ptr, Object* element) {
	Macro *textMacro, *listMacro, *macros;
	char* newElementString=NULL, *oldElementString=NULL, *textString=NULL, *listString=NULL;
	cgc_size_t elementStringSize=0;

	macros = (Macro*) macro_ptr;
	textMacro = cgc_getMacro(macros, TEXT_TAG);
	listMacro = cgc_getMacro(macros, LIST_TAG);

	for(Object* child=element->children; child!=NULL; child=child->next) {
		if(!cgc_strcmp(child->name, TEXT_TAG)) {
			textString = textMacro->body(macros, child);
			elementStringSize += cgc_strlen(textString) + cgc_strlen("\n");
		} else if(!cgc_strcmp(child->name, LIST_TAG)) {
			listString = listMacro->body(macros, child);
		}
	}

	if(elementStringSize>0) {
		if(!(newElementString = cgc_malloc(elementStringSize+1)))
			return NULL;

		cgc_memset(newElementString, 0, elementStringSize+1);
		oldElementString = newElementString;

		if(textString) {
			cgc_strcat(newElementString, textString);
		}

		if(listString) {
			char* subElementString;
			cgc_size_t subElementStringSize=0;

			cgc_strcat(newElementString, "\n");
			subElementString = cgc_strtok(listString, '\n');
			while(subElementString != NULL) {
				subElementStringSize = cgc_strlen(subElementString);
				elementStringSize += subElementStringSize + cgc_strlen(LIST_INDENT) + cgc_strlen("\n");
				if(!(newElementString = cgc_malloc(elementStringSize+1)))
					return NULL;

				cgc_memset(newElementString, 0, elementStringSize+1);
				cgc_memcpy(newElementString, oldElementString, cgc_strlen(oldElementString));
				cgc_free(oldElementString);
				oldElementString = newElementString;

				cgc_strcat(newElementString, LIST_INDENT);
				cgc_strcat(newElementString, subElementString);
				cgc_strcat(newElementString, "\n");
				
				subElementString = cgc_strtok(NULL, '\n');

			}

		}

	}

	return newElementString;
}

/**
 * Render a list string from the list object
 * 
 * @param  macro_ptr The address of the macro list
 * @param  list      The list object
 * @return           The string representation of the list
 */
char* cgc_list(void* macro_ptr, Object* list) {
	char *newList=NULL, *oldList=NULL;
	Macro *macros;
	char customNumString[4];
	Macro *elementMacro;
	cgc_size_t listStringSize=0;
	Object* elements=NULL, *nextChild;
	unsigned int totalElementNum=0;
	unsigned int listType = '*';

	macros = (Macro*) macro_ptr;
	elementMacro = cgc_getMacro(macros, ELEMENT_TAG);

	cgc_memset(customNumString, 0, 4);

	for(Object* child=list->children; child!=NULL; child=nextChild) {
		nextChild = child->next;

		if(!cgc_strcmp(child->name, TYPE_TAG)) {
			Object* grandchild;

			grandchild = child->children;
			if(!child)
				continue;
			if(!cgc_strcmp(grandchild->name, NUMERAL_STR)) {
				listType = NUMERAL;
			} else if(!cgc_strcmp(grandchild->name, UPPER_ALPHA_STR)) {
				listType = UPPER_ALPHA;
			} else if(!cgc_strcmp(grandchild->name, LOWER_ALPHA_STR)) {
				listType = LOWER_ALPHA;
			} else if(!cgc_strcmp(grandchild->name, ROMAN_STR)) {
				listType = ROMAN;
			} else {
#ifdef PATCHED_2
				cgc_strncat(customNumString, grandchild->name, 3);
#else
				cgc_strncat(customNumString, grandchild->name, 8);
#endif

			}
		} else if(!cgc_strcmp(child->name, ELEMENT_TAG)) {
			child->next = elements;
			elements = child;
			continue;
		}
	}

	for(Object* element=elements; element!=NULL; element=element->next) {
		char* elementString=NULL;
		cgc_size_t elementStringSize=0;
		char* elementNumString;
		cgc_size_t elementNumStringSize=0;

		if(!cgc_strcmp(element->name, ELEMENT_TAG)) {
			elementString = elementMacro->body(macros, element);
			if(!elementString)
				continue;

			elementStringSize = cgc_strlen(elementString);

			totalElementNum++;
			if(!(elementNumString = cgc_malloc(12)))
				return NULL;

			cgc_memset(elementNumString, 0, 12);
			if(listType == NUMERAL) {
				elementNumString = cgc_itoa(totalElementNum, elementNumString);
			} else if(listType == UPPER_ALPHA) {
				elementNumString[0] = 0x40 + totalElementNum;
			} else if(listType == LOWER_ALPHA) {
				elementNumString[0] = 0x60 + totalElementNum;
			} else if(listType == ROMAN) {
				cgc_free(elementNumString);
				elementNumString = cgc_romanNumeral(totalElementNum);
			} else {
				elementNumString[0] = (char) listType;
			}

			if(!elementNumString)
				return NULL;

			elementNumStringSize = cgc_strlen(elementNumString);

			listStringSize += elementNumStringSize + elementStringSize + cgc_strlen(". ") + cgc_strlen("\n");

			if(!(newList = cgc_malloc(listStringSize+1)))
				return NULL;

			cgc_memset(newList, 0, listStringSize+1);
			if(oldList != NULL) {
				cgc_memcpy(newList, oldList, cgc_strlen(oldList));
				cgc_free(oldList);
			}
			oldList = newList;

			cgc_strcat(newList, elementNumString);
			if(listType < 4)
				cgc_strcat(newList, ".");
			cgc_strcat(newList, " ");
			cgc_strcat(newList, elementString);
			cgc_strcat(newList, "\n");
			cgc_free(elementString);
		} 
	}

	return newList;
}

/**
 * Render a text string from the text object
 * 
 * @param  macro_ptr The address of the macro list
 * @param  text      The text object
 * @return           The string representation of the text
 */
char* cgc_text(void* macro_ptr, Object* text) {
	Object* child;

	child = text->children;

	if(child)
		return child->name;
	
	return NULL;
}

/**
 * Render a paragraph string from the paragraph object
 * 
 * @param  macro_ptr The address of the macro list
 * @param  paragraph The paragraph object
 * @return           The string representation of the paragraph
 */
char* cgc_paragraph(void* macro_ptr, Object* paragraph) {
	char *paragraphString=NULL, *childString=NULL;
	Macro *textMacro, *listMacro, *tableMacro, *macros;
	cgc_size_t paragraphSize=0;
	Object* child=NULL;

	macros = (Macro*) macro_ptr;
	textMacro = cgc_getMacro(macros, TEXT_TAG);
	listMacro = cgc_getMacro(macros, LIST_TAG);
	tableMacro = cgc_getMacro(macros, TABLE_TAG);

	child = paragraph->children;
	if(!child)
		return NULL;

	if(!cgc_strcmp(child->name, TEXT_TAG)) {
		childString = textMacro->body(macros, child);
		if(!childString)
			return NULL;

		paragraphSize = cgc_strlen(childString) + cgc_strlen(INDENT);
		if(!(paragraphString = cgc_malloc(paragraphSize+1)))
			return NULL;

		cgc_memset(paragraphString, 0, paragraphSize+1);
		cgc_strcat(paragraphString, INDENT);
		cgc_strcat(paragraphString, childString);
		cgc_free(childString);
	} else if(!cgc_strcmp(child->name, LIST_TAG)) {
		childString = listMacro->body(macros, child);
		if(!childString)
			return NULL;

		paragraphSize = cgc_strlen(childString);
		if(!(paragraphString = cgc_malloc(paragraphSize+1)))
			return NULL;

		cgc_memset(paragraphString, 0, paragraphSize+1);
		cgc_strcat(paragraphString, childString);
		cgc_free(childString);
	} else if(!cgc_strcmp(child->name, TABLE_TAG)) {
		childString = tableMacro->body(macros, child);
		if(!childString)
			return NULL;

		paragraphSize = cgc_strlen(childString);
		if(!(paragraphString = cgc_malloc(paragraphSize+1)))
			return NULL;

		cgc_memset(paragraphString, 0, paragraphSize+1);
		cgc_strcat(paragraphString, childString);
		cgc_free(childString);		
	}

	return paragraphString;
}

/**
 * Render a page string from the page object
 * @param  macro_ptr The address of the macro list
 * @param  page      The page object
 * @return           The string representation of the page
 */
char* cgc_page(void* macro_ptr, Object* page) {
	char *newPage=NULL, *oldPage=NULL;
	Macro *paragraphMacro, *macros;
	cgc_size_t pageSize=0;
	Object *children=NULL, *nextChild;

	macros = (Macro*) macro_ptr;
	paragraphMacro = cgc_getMacro(macros, PARAGRAPH_TAG);

	// Reverse order of children
	for(Object* child=page->children; child!=NULL; child=nextChild) {
		nextChild = child->next;
		child->next = children;
		children = child;
	}


	for(Object* child=children; child!=NULL; child=child->next) {
		char* childString;
		cgc_size_t childStringSize;

		if(!cgc_strcmp(child->name, PARAGRAPH_TAG)) {
			childString = paragraphMacro->body(macros, child);
			if(!childString)
				continue;
		} else {
			continue;
		}

		childStringSize = cgc_strlen(childString);
		pageSize += childStringSize + cgc_strlen("\n");
		if(!(newPage = cgc_malloc(pageSize+1)))
			return NULL;

		cgc_memset(newPage, 0, pageSize+1);
		if(oldPage != NULL) {
			cgc_strcat(newPage, oldPage);
			cgc_free(oldPage);			
		}
		cgc_strcat(newPage, childString);
		cgc_free(childString);
		cgc_strcat(newPage, "\n");
		oldPage = newPage;
	}

	return newPage;
}

/**
 * Render a document string from the document object
 * @param  macro_ptr The address of the macro list
 * @param  document  The document object
 * @return           The string representation of the document
 */
char* cgc_document(void* macro_ptr, Object* document) {
	char *newDocument=NULL, *oldDocument=NULL;
	Macro *pageMacro, *columnMacro, *macros;
	cgc_size_t documentSize=0;
	Object* pages=NULL;
	Object* nextChild;
	unsigned int totalPageNum=0;
	char** lineBuffer;
	cgc_size_t docLength=11, docWidth=20;
	unsigned int columnNum=1;

	macros = (Macro*) macro_ptr;
	pageMacro = cgc_getMacro(macros, PAGE_TAG);
	columnMacro = cgc_getMacro(macros, COLUMN_TAG);

	for(Object* child=document->children; child!=NULL; child=nextChild) {
		nextChild = child->next;

		if(!cgc_strcmp(child->name, PAGE_TAG) || !cgc_strcmp(child->name, COLUMN_TAG)) {
			child->next = pages;
			pages = child;
			continue;
		}

		if(!cgc_strcmp(child->name, LENGTH_TAG)) {
			child = child->children;
			if(child)
				docLength = cgc_atoi(child->name);
			continue;
		}

		if(!cgc_strcmp(child->name, WIDTH_TAG)) {
			child = child->children;
			if(child)	
				docWidth = cgc_atoi(child->name);
			continue;
		}
	}

	if(!(lineBuffer = cgc_malloc(docLength * sizeof(char *))))
		return NULL;

	for (int i=0; i < docLength; i++) {
		if(!(lineBuffer[i] = (char *)cgc_malloc(docWidth + 3)))
			return NULL;

		cgc_memset(lineBuffer[i], 0, docWidth + 3);

	}

	columnWidth = docWidth;

	for(Object* page=pages; page!=NULL; page=page->next) {
		char *pageString, *columnString;
		cgc_size_t pageSize, numLines;
		char* lineString;
		char* pageNumString;
		cgc_size_t lineStringLength;
		unsigned int columnIndex;

		if(!cgc_strcmp(page->name, COLUMN_TAG)) {
			columnString = columnMacro->body(macros, page);
			if(!columnString) {
				columnNum = 1;
				continue;
			}
			columnNum = cgc_atoi(columnString);
			if((docWidth / columnNum) - cgc_strlen(TAB) < 1)
				columnNum = 1;
			columnWidth = (docWidth / columnNum) - cgc_strlen(TAB);
			continue;
		}

		pageString = pageMacro->body(macros, page);
		if(!pageString) 
			continue;

		lineString = cgc_strtok(pageString, '\n');

		// Add new page
		totalPageNum++;
		documentSize += (docWidth + 1) * (docLength + 2);
		if(!(newDocument = cgc_malloc(documentSize+1)))
			return NULL;

		cgc_memset(newDocument, 0, documentSize+1);
		if(oldDocument != NULL) {
			cgc_size_t existing;
			
			existing = cgc_strlen(oldDocument);
			cgc_memcpy(newDocument, oldDocument, existing);
			cgc_free(oldDocument);
		}
		oldDocument = newDocument;

		columnIndex = 1;
		// Add Lines to page
		for(int lineIndex = 0; lineIndex < docLength; lineIndex++) {
			// Last line in page
			if(lineIndex == docLength - 1) {

				// Last column in page
				if(columnIndex == columnNum) {
					cgc_size_t existing;

					// Add page number
					if(!(pageNumString = cgc_malloc(docWidth)))
						return NULL;

					cgc_memset(pageNumString, 0, docWidth);
					pageNumString = cgc_itoa(totalPageNum, pageNumString);
					cgc_strcat(lineBuffer[lineIndex], " ");
					cgc_strncat(lineBuffer[lineIndex], pageNumString, docWidth-1);

					cgc_memset(newDocument, '=', docWidth);
					cgc_strcat(newDocument, "\n");
					// Append lineBuffers to document
					for(int index=0; index<docLength; index++) {
						cgc_strcat(newDocument, lineBuffer[index]);
						cgc_strcat(newDocument, "\n");

					}

					existing = cgc_strlen(newDocument);
					cgc_memset(&newDocument[existing], '=', docWidth);

					for (int i=0; i < docLength; i++) {
						cgc_memset(lineBuffer[i], 0, docWidth + 3);
					}

					// More lines in page?
					if(lineString != NULL) {
						// Add new page
						totalPageNum++;
						documentSize += (docWidth + 1) * (docLength + 2);
						if(!(newDocument = cgc_malloc(documentSize+1)))
							return NULL;

						cgc_memset(newDocument, 0, documentSize+1);
						if(oldDocument != NULL) {
							cgc_size_t existing;
							
							existing = cgc_strlen(oldDocument);
							cgc_memcpy(newDocument, oldDocument, existing);
							cgc_free(oldDocument);
						}
						oldDocument = newDocument;
						// Reset index
						lineIndex = -1;
						columnIndex = 1;		
					}
				} else {
					columnIndex++;
					lineIndex = -1;
				}

				continue;
			}

			// No more lines
			if(lineString == NULL) {
				cgc_size_t remaining;

				remaining = cgc_strlen(lineBuffer[lineIndex]);
				cgc_memset(&lineBuffer[lineIndex][remaining], ' ', columnWidth);
				cgc_strcat(lineBuffer[lineIndex], TAB);
				continue;
			}

			lineStringLength = cgc_strlen(lineString);
			if(lineStringLength > columnWidth) {
				cgc_strncat(lineBuffer[lineIndex], lineString, columnWidth);
				if(columnNum > 1)
					cgc_strcat(lineBuffer[lineIndex], TAB);
				lineString += columnWidth;
			} else {
				cgc_size_t lineBufferLength;

				cgc_strcat(lineBuffer[lineIndex], lineString);
				for(int i=0; i<columnWidth - lineStringLength; i++)
					cgc_strcat(lineBuffer[lineIndex], " ");

				if(columnNum > 1)
					cgc_strcat(lineBuffer[lineIndex], TAB);
				lineString = cgc_strtok(NULL, '\n');
			}

		}

		cgc_transmit_all(STDOUT, newDocument, cgc_strlen(newDocument));
		cgc_transmit_all(STDOUT, "\x3", cgc_strlen("\x3"));
		cgc_free(newDocument);
		oldDocument=NULL;
		newDocument=NULL;

	}

	return newDocument;
}

/**
 * Create a new macro
 * 
 * @param  name 	The name of the new macro
 * @param  body 	The address of the macro function
 * @return          The address of the newly create macro
 */
Macro* cgc_newMacro(char* name, char* (*body)(void *macros, Object* object)) {
	Macro* macro;
	cgc_size_t nameSize;

	if(!(macro = cgc_malloc(sizeof(Macro))))
		return NULL;

	nameSize = cgc_strlen(name);
	if(!(macro->name = cgc_malloc(nameSize+1)))
		return NULL;

	cgc_memset(macro->name, 0, nameSize+1);
	cgc_memcpy(macro->name, name, nameSize);
	macro->body = body;

	return macro;
}

/**
 * Initialize the macros
 * 
 * @param macro_ptr The address of the macro list
 */
void cgc_initMacros(Macro** macro_ptr) {
	Macro* macro;

	macro = cgc_newMacro(ELEMENT_TAG, &cgc_element);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = cgc_newMacro(DOCUMENT_TAG, &cgc_document);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = cgc_newMacro(PAGE_TAG, &cgc_page);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = cgc_newMacro(PARAGRAPH_TAG, &cgc_paragraph);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = cgc_newMacro(TEXT_TAG, &cgc_text);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = cgc_newMacro(LIST_TAG, &cgc_list);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = cgc_newMacro(COLUMN_TAG, &cgc_text);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = cgc_newMacro(TABLE_TAG, &cgc_table);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

}

/**
 * Initialize all custom macros
 * 
 * @param customMacrosPtr The address of the custom macro list
 */
void cgc_initCustomMacros(Object **customMacrosPtr) {
	cgc_getObject(customMacrosPtr, NULL, &FourByFourTable_Macro);
	cgc_getObject(customMacrosPtr, NULL, &FiveByFiveTable_Macro);
	cgc_getObject(customMacrosPtr, NULL, &AlphanumericOutline_Macro);
	cgc_getObject(customMacrosPtr, NULL, &BulletedOutline_Macro);

}

/**
 * Send the Document ID to the requester
 * 
 * @param documentID The value of the documentID
 */
void cgc_sendDocumentID(unsigned int documentID) {
	char* documentIDString;

	if(!(documentIDString = cgc_malloc(20)))
		return;

	documentIDString = cgc_itoa(documentID, documentIDString);
	cgc_transmit_all(STDOUT, DOC_ID_STRING, cgc_strlen(DOC_ID_STRING));
	cgc_transmit_all(STDOUT, documentIDString, cgc_strlen(documentIDString));
	cgc_transmit_all(STDOUT, "\n", cgc_strlen("\n"));
}


int main(int cgc_argc, char *cgc_argv[]) {
	Object* documentObject;
	Macro* macros;
	char* documentString;
	Object* customMacros=NULL;
	char* titleObject;
	unsigned int documentID;
	char* documentIDString;

	documentID = cgc_getDocumentID();

	if(!(titleObject = cgc_malloc(sizeof(Macro))))
		return -1;

	cgc_initMacros(&macros);
	cgc_initCustomMacros(&customMacros);
	cgc_free(titleObject);
	documentObject = cgc_getObject(&customMacros, NULL, NULL);

	cgc_sendDocumentID(documentID);
	documentString = cgc_document(macros, documentObject);

	return 0;
}