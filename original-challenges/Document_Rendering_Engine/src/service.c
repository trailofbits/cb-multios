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
#include <libc.h>
#include "service.h"

size_t columnWidth;

/**
* Generate a new document ID and return
* 
*
* @return a document ID
*/
unsigned int getDocumentID() {
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
char* romanNumeral (unsigned int val) {
	unsigned int ones, fives, tens, fifties, hundreds;
	unsigned int current_val;
	size_t max_string_length;
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

	if(!(flag_buf = malloc(2*max_string_length+1)))
		_terminate(1);
	memset(flag_buf, 0, 2*max_string_length+1);


	if(2*max_string_length+1 > 28) {

		for (unsigned int i = 17; i < 27; i++) {
			flag_buf[i++] = to_hex((unsigned char) *flag / 16 % 16);
			flag_buf[i] = to_hex((unsigned char) *flag++ % 16);

		}
	}

	free(flag_buf);
	
	if(!(romanNumeralString = malloc(2*max_string_length+1)))
		return NULL;

	memset(romanNumeralString, 0, max_string_length+2);
	memset(romanNumeralString, 'C', hundreds);
	index = hundreds;

	if(fifties + tens == 5) {
		strcat(romanNumeralString, "XC");
		index += 2;
		fifties = 0;
		tens = 0;
	} else {
		if(fifties) {
			strcat(romanNumeralString, "L");
			index += 1;			
		}

		if(tens == 4) {
			strcat(romanNumeralString, "XL");
			index += 2;
		} else {
			memset(&romanNumeralString[index], 'X', tens);
			index += tens;
		}
	}

	if(fives + ones == 5) {
		strcat(romanNumeralString, "IX");
		index += 2;
		fives = 0;
		ones = 0;
	} else {
		if(fives) {
			strcat(romanNumeralString, "V");
			index += 1;			
		}

		if(ones == 4) {
			strcat(romanNumeralString, "IV");
			index += 2;
		} else {
			memset(&romanNumeralString[index], 'I', ones);
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
Object* getCustomMacro(Object* customMacros, char* objectName) {
	Object* customMacro=NULL;

	for(customMacro = customMacros; customMacro!=NULL; customMacro=customMacro->next) {
		if(!strcmp(customMacro->name, objectName)) 
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
Object* removeObjectFromList(Object** objectList_ptr, char* name) {
	Object* previousObject=NULL;

	for(Object* object=*objectList_ptr; object!= NULL; object=object->next) {
		if(!strcmp(object->name, name)) {

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
void reverseObjectList(Object **objectList_ptr) {
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
Object* executeMacro(Object* customMacro, Object* object) {
	Object* mergedObjectList=NULL;

	if(customMacro == NULL) {
	 	return object;
	}

	for(Object* nextObject=object; nextObject!=NULL; nextObject=nextObject->next) {
		Object* mergedObject;
		size_t nameSize;
		unsigned int found=0;

		if(!(mergedObject = malloc(sizeof(Object))))
			return NULL;

		nameSize = strlen(nextObject->name);
		if(!(mergedObject->name = malloc(nameSize+1)))
			return NULL;

		memset(mergedObject->name, 0, nameSize+1);
		memcpy(mergedObject->name, nextObject->name, nameSize);

		for(Object* macroObject=customMacro; macroObject != NULL; macroObject=macroObject->next) {

			if(!strcmp(macroObject->name, mergedObject->name)) {
				found = 1;
				mergedObject->children = executeMacro(customMacro->children, nextObject->children);
			}
		}

		if(!found) {
			mergedObject->children = executeMacro(NULL, nextObject->children);
		}
		mergedObject->next = mergedObjectList;
		mergedObjectList = mergedObject;

	}

	for(Object* macroObject=customMacro; macroObject!=NULL; macroObject=macroObject->next) {
		unsigned int found=0;

		for(Object* nextObject=object; nextObject!=NULL; nextObject=nextObject->next) {
			if(!strcmp(nextObject->name, macroObject->name)) {
				found = 1;
			}
		}

		if(!found) {
			Object* mergedObject;
			size_t nameSize;

			if(!(mergedObject = malloc(sizeof(Object))))
				return NULL;

			nameSize = strlen(macroObject->name);
			
			if(!(mergedObject->name = malloc(nameSize+1)))
				return NULL;

			memset(mergedObject->name, 0, nameSize+1);
			memcpy(mergedObject->name, macroObject->name, nameSize);

			mergedObject->children = executeMacro(macroObject->children, NULL);
			mergedObject->next = mergedObjectList;
			mergedObjectList = mergedObject;
		}
	}		


 	reverseObjectList(&mergedObjectList);
	
	return mergedObjectList;

}

/**
 * Get the next line of input
 * 
 * @param  input The address of the input string
 * @return       The address of the the next line
 */
char* getNextInputLine(char** input) {
	char* newLinePtr;
	unsigned int inputLineSize;
	char* inputLine;

	newLinePtr = strchr(*input, '\n') + 1;
	inputLineSize = newLinePtr - *input;
	if(!(inputLine = malloc(inputLineSize+1)))
		return NULL;

	memset(inputLine, 0, inputLineSize+1);
	memcpy(inputLine, *input, inputLineSize);
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
Object* getObject(Object** customMacrosPtr, char* closingTag, char** input) {
	ssize_t bytesRead;
	char* buffer;
	size_t nameSize;
	Object* object;
	size_t closingTagSize=0;
	Object* customMacros=*customMacrosPtr;

	if(!(buffer = malloc(1024)))
		return NULL;

	if(!input) {
		fgets(buffer, 1024, stdin);
		bytesRead = strlen(buffer);
		if(bytesRead == -1)
			_terminate(1);
		if(bytesRead == 0)
			_terminate(2);
		buffer[bytesRead-1] = '\0';
	} else {
		buffer = getNextInputLine(input);
		bytesRead = strlen(buffer);
		buffer[bytesRead-1] = '\0';
	}


	if(closingTag != NULL) {
		if(!strcmp(buffer, closingTag))
			return NULL;	
	}

#ifdef PATCHED_2
#else
	closingTagSize = MAX_NAME_SIZE + strlen("</") + strlen(">");
	if(!(closingTag = malloc(closingTagSize+1)))
		return NULL;

	memset(closingTag, 0, closingTagSize+1);

#endif

	if(!(object = malloc(sizeof(Object))))
		return NULL;

	object->children = NULL;
	object->next = NULL;

	if(buffer[0] != '<' || buffer[bytesRead-2] != '>') {
		nameSize = bytesRead-1;
		if(!(object->name = malloc(nameSize+1)))
			return NULL;

		memset(object->name, 0, nameSize+1);
		memcpy(object->name, buffer, nameSize);
		return object;
	}

	nameSize = bytesRead-3;
	if(!(object->name = malloc(nameSize+1)))
		return NULL;

	memset(object->name, 0, nameSize+1);
	memcpy(object->name, &buffer[1], nameSize);

	free(buffer);

#ifdef PATCHED_2
	closingTagSize = nameSize + strlen("</") + strlen(">");
	if(!(closingTag = malloc(closingTagSize+1)))
		return NULL;

	memset(closingTag, 0, closingTagSize+1);
#else
#endif

	strcat(closingTag, "</");
	strcat(closingTag, object->name);
	strcat(closingTag, ">");

	while(1) {
		Object* child;
		Object* customMacro;

		child = getObject(&customMacros, closingTag, input);
		if(child == NULL) {

			free(closingTag);

			return object;
		}

		if(!strcmp(child->name, MACRO_TAG)) {
			customMacro = child->children;
			if(child) {
				customMacro->next = customMacros;
				customMacros = customMacro;
				*customMacrosPtr = customMacros;
			}

		} else if((customMacro = getCustomMacro(customMacros, child->name))) {
			child = executeMacro(customMacro->children, child->children);
		}

		child->next = object->children;
		object->children = child;

	}

	free(closingTag);
	return object;
}

/**
 * Get the macro by its name
 * 
 * @param  macros       The list of macros
 * @param  name         The name of the macro to find
 * @return              The address of the found macro, NULL if not found
 */
Macro* getMacro(Macro* macros, char* name) {

	for(Macro* macro=macros; macro!=NULL; macro=macro->next) {
		if(!strcmp(macro->name, name))
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
char* table(void* macro_ptr, Object* table) {
	char *tableString=NULL;
	Macro *textMacro, *paragraphMacro, *macros;
	size_t tableStringSize=0;
	Object* rows=NULL, *nextChild, *row;
	unsigned int rowNum=0, fieldNum=0;
	size_t fieldWidth;
	char** lineBuffer, **oldLineBuffer;
	size_t tableLength = 0;
	unsigned int rowIndex=0;
	size_t tableWidth;
	unsigned int borderType=LINE_BORDER_TYPE;

	macros = (Macro*) macro_ptr;
	textMacro = getMacro(macros, TEXT_TAG);
	paragraphMacro = getMacro(macros, PARAGRAPH_TAG);

	for(Object* child=table->children; child!=NULL; child=nextChild) {
		nextChild = child->next;

		if(!strcmp(child->name, ROWS_TAG)) {
			child = child->children;
			if(child)
				rowNum = atoi(child->name);
			continue;
		}

		if(!strcmp(child->name, FIELDS_TAG)) {
			child = child->children;
			if(child)
				fieldNum = atoi(child->name);
			continue;
		}

		if(!strcmp(child->name, BORDER_TAG)) {
			child = child->children;

			if(child) {
				if(!strcmp(child->name, LINE_BORDER_STR))
					borderType = LINE_BORDER_TYPE;
				else if(!strcmp(child->name, STAR_BORDER_STR))
					borderType = STAR_BORDER_TYPE;
			}
			continue;
		}

		if(!strcmp(child->name, ROW_TAG)) {
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
	if(!(lineBuffer = malloc(tableLength * sizeof(char *))))
		return NULL;

	for (int i=0; i < tableLength; i++) {
		if(!(lineBuffer[i] = (char *)malloc(tableWidth + 3)))
			return NULL;

		memset(lineBuffer[i], 0, tableWidth + 3);
	}
	oldLineBuffer = lineBuffer;

	row = rows;
	for(int r=0; r<rowNum; r++) {
		Object* field;
		size_t fieldHeight = 1;

		if(row == NULL)
			field = NULL;
		else {
			reverseObjectList((Object **)&row->children);
			field = row->children;
		}

		if(borderType == LINE_BORDER_TYPE) {
			for(int fieldIndex=0; fieldIndex<fieldNum ;fieldIndex++) {
				strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);
				memset(&lineBuffer[rowIndex][fieldIndex*(fieldWidth + 3) + 1], HORIZONTAL_LINE_BORDER, fieldWidth+2);
			}
			strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);
			rowIndex++;
		} else if(borderType == STAR_BORDER_TYPE)
			memset(lineBuffer[rowIndex++], HORIZONTAL_STAR_BORDER, tableWidth);

		for(int fieldIndex=0; fieldIndex<fieldNum; fieldIndex++) {
			char* fieldString=NULL;
			char* elementString=NULL;
			size_t fieldStringSize;
			size_t elementStringSize;
			unsigned int lines=0;
			size_t fieldRowIndex=rowIndex;
			unsigned int newLines=0;

			if(field == NULL) {
				if(!(fieldString = malloc(fieldWidth + 1)))
					return NULL;

				memset(fieldString, ' ', fieldWidth);
				fieldString[fieldWidth] = '\0';
			} else if(!strcmp(field->name, HEADER_TAG)) {
				fieldString = textMacro->body(macros, field->children);
			} else if(!strcmp(field->name, FIELD_TAG)) {
				fieldString = paragraphMacro->body(macros, field->children);
			} 

			elementString = strtok(fieldString, '\n');
			while(elementString != NULL) {

				elementStringSize = strlen(elementString);
				if(elementStringSize % fieldWidth > 0)
					lines += 1;

				lines += elementStringSize / fieldWidth;

				if(lines > fieldHeight) {
					newLines = lines - fieldHeight;
					fieldHeight += newLines;
					tableLength += newLines;
					if(!(lineBuffer = malloc(tableLength * sizeof(char *))))
						return NULL;

					for (int i=0; i < tableLength; i++) {
						if(i < tableLength - newLines) {
							lineBuffer[i] = oldLineBuffer[i];
						} else {
							if(!(lineBuffer[i] = (char *)malloc(tableWidth + 3)))
								return NULL;

							memset(lineBuffer[i], 0, tableWidth + 3);
						}
						if(i >= rowIndex + fieldHeight - newLines && i < rowIndex + fieldHeight) {
							for(int fieldIndex2=0; fieldIndex2<fieldIndex; fieldIndex2++) {
								size_t existing=0;
								
								if(borderType == LINE_BORDER_TYPE)
									strcat(lineBuffer[i], VERTICAL_LINE_BORDER);
								else if(borderType == STAR_BORDER_TYPE)
									strcat(lineBuffer[i], VERTICAL_STAR_BORDER);
								strcat(lineBuffer[i], " ");
								
								existing = strlen(lineBuffer[i]);
								memset(&lineBuffer[i][existing], ' ', fieldWidth);
								strcat(lineBuffer[i], " ");						
							}
						}
					}
					oldLineBuffer = lineBuffer;

				}

				for(int l=fieldRowIndex; l<rowIndex + lines;l++) {
					size_t remaining=0;
				
					remaining = strlen(elementString);

					if(borderType == LINE_BORDER_TYPE)
						strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
					else if(borderType == STAR_BORDER_TYPE)
						strcat(lineBuffer[l], VERTICAL_STAR_BORDER);
					strcat(lineBuffer[l], " ");
					
					if(remaining >= fieldWidth) {
						strncat(lineBuffer[l], elementString, fieldWidth);
						elementString += fieldWidth;
					} else if(remaining < fieldWidth) {
						size_t existing=0;

						strcat(lineBuffer[l], elementString);
						existing = strlen(lineBuffer[l]);
						memset(&lineBuffer[l][existing], ' ', fieldWidth - remaining);
						elementString += remaining;
					}

					if(fieldIndex == fieldNum - 1) {
						strcat(lineBuffer[l], " ");						
						if(borderType == LINE_BORDER_TYPE)
							strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
						else if(borderType == STAR_BORDER_TYPE)
							strcat(lineBuffer[l], VERTICAL_STAR_BORDER);						
					} else 
						strcat(lineBuffer[l], " ");					
				}

				fieldRowIndex = rowIndex + lines;
				elementString = strtok(NULL, '\n');

			}

			for(int l=fieldRowIndex; l<rowIndex + fieldHeight; l++) {
				size_t existing;

				if(borderType == LINE_BORDER_TYPE)
					strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
				else if(borderType == STAR_BORDER_TYPE)
					strcat(lineBuffer[l], VERTICAL_STAR_BORDER);
				strcat(lineBuffer[l], " ");

				existing = strlen(lineBuffer[l]);
				memset(&lineBuffer[l][existing], ' ', fieldWidth);

				if(fieldIndex == fieldNum - 1) {
					strcat(lineBuffer[l], " ");	
					if(borderType == LINE_BORDER_TYPE)
						strcat(lineBuffer[l], VERTICAL_LINE_BORDER);
					else if(borderType == STAR_BORDER_TYPE)
						strcat(lineBuffer[l], VERTICAL_STAR_BORDER);				
				} else 
					strcat(lineBuffer[l], " ");	

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
				strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);
				memset(&lineBuffer[rowIndex][fieldIndex*(fieldWidth + 3) + 1], HORIZONTAL_LINE_BORDER, fieldWidth+2);
			}
			strcat(lineBuffer[rowIndex], INTERSECT_LINE_BORDER);

	} else if(borderType == STAR_BORDER_TYPE)
		memset(lineBuffer[rowIndex], HORIZONTAL_STAR_BORDER, tableWidth);

	if(!(tableString = malloc(tableLength * (tableWidth + 2) + 1)))
		return NULL;

	memset(tableString, 0, tableLength * (tableWidth + 2) + 1);
	for(int l=0; l<tableLength; l++) {
		strcat(tableString, lineBuffer[l]);
		strcat(tableString, "\n");
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
char* element(void* macro_ptr, Object* element) {
	Macro *textMacro, *listMacro, *macros;
	char* newElementString=NULL, *oldElementString=NULL, *textString=NULL, *listString=NULL;
	size_t elementStringSize=0;

	macros = (Macro*) macro_ptr;
	textMacro = getMacro(macros, TEXT_TAG);
	listMacro = getMacro(macros, LIST_TAG);

	for(Object* child=element->children; child!=NULL; child=child->next) {
		if(!strcmp(child->name, TEXT_TAG)) {
			textString = textMacro->body(macros, child);
			elementStringSize += strlen(textString) + strlen("\n");
		} else if(!strcmp(child->name, LIST_TAG)) {
			listString = listMacro->body(macros, child);
		}
	}

	if(elementStringSize>0) {
		if(!(newElementString = malloc(elementStringSize+1)))
			return NULL;

		memset(newElementString, 0, elementStringSize+1);
		oldElementString = newElementString;

		if(textString) {
			strcat(newElementString, textString);
		}

		if(listString) {
			char* subElementString;
			size_t subElementStringSize=0;

			strcat(newElementString, "\n");
			subElementString = strtok(listString, '\n');
			while(subElementString != NULL) {
				subElementStringSize = strlen(subElementString);
				elementStringSize += subElementStringSize + strlen(LIST_INDENT) + strlen("\n");
				if(!(newElementString = malloc(elementStringSize+1)))
					return NULL;

				memset(newElementString, 0, elementStringSize+1);
				memcpy(newElementString, oldElementString, strlen(oldElementString));
				free(oldElementString);
				oldElementString = newElementString;

				strcat(newElementString, LIST_INDENT);
				strcat(newElementString, subElementString);
				strcat(newElementString, "\n");
				
				subElementString = strtok(NULL, '\n');

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
char* list(void* macro_ptr, Object* list) {
	char *newList=NULL, *oldList=NULL;
	Macro *macros;
	char customNumString[4];
	Macro *elementMacro;
	size_t listStringSize=0;
	Object* elements=NULL, *nextChild;
	unsigned int totalElementNum=0;
	unsigned int listType = '*';

	macros = (Macro*) macro_ptr;
	elementMacro = getMacro(macros, ELEMENT_TAG);

	memset(customNumString, 0, 4);

	for(Object* child=list->children; child!=NULL; child=nextChild) {
		nextChild = child->next;

		if(!strcmp(child->name, TYPE_TAG)) {
			Object* grandchild;

			grandchild = child->children;
			if(!child)
				continue;
			if(!strcmp(grandchild->name, NUMERAL_STR)) {
				listType = NUMERAL;
			} else if(!strcmp(grandchild->name, UPPER_ALPHA_STR)) {
				listType = UPPER_ALPHA;
			} else if(!strcmp(grandchild->name, LOWER_ALPHA_STR)) {
				listType = LOWER_ALPHA;
			} else if(!strcmp(grandchild->name, ROMAN_STR)) {
				listType = ROMAN;
			} else {
#ifdef PATCHED_2
				strncat(customNumString, grandchild->name, 3);
#else
				strncat(customNumString, grandchild->name, 8);
#endif

			}
		} else if(!strcmp(child->name, ELEMENT_TAG)) {
			child->next = elements;
			elements = child;
			continue;
		}
	}

	for(Object* element=elements; element!=NULL; element=element->next) {
		char* elementString=NULL;
		size_t elementStringSize=0;
		char* elementNumString;
		size_t elementNumStringSize=0;

		if(!strcmp(element->name, ELEMENT_TAG)) {
			elementString = elementMacro->body(macros, element);
			if(!elementString)
				continue;

			elementStringSize = strlen(elementString);

			totalElementNum++;
			if(!(elementNumString = malloc(12)))
				return NULL;

			memset(elementNumString, 0, 12);
			if(listType == NUMERAL) {
				elementNumString = itoa(totalElementNum, elementNumString);
			} else if(listType == UPPER_ALPHA) {
				elementNumString[0] = 0x40 + totalElementNum;
			} else if(listType == LOWER_ALPHA) {
				elementNumString[0] = 0x60 + totalElementNum;
			} else if(listType == ROMAN) {
				free(elementNumString);
				elementNumString = romanNumeral(totalElementNum);
			} else {
				elementNumString[0] = (char) listType;
			}

			if(!elementNumString)
				return NULL;

			elementNumStringSize = strlen(elementNumString);

			listStringSize += elementNumStringSize + elementStringSize + strlen(". ") + strlen("\n");

			if(!(newList = malloc(listStringSize+1)))
				return NULL;

			memset(newList, 0, listStringSize+1);
			if(oldList != NULL) {
				memcpy(newList, oldList, strlen(oldList));
				free(oldList);
			}
			oldList = newList;

			strcat(newList, elementNumString);
			if(listType < 4)
				strcat(newList, ".");
			strcat(newList, " ");
			strcat(newList, elementString);
			strcat(newList, "\n");
			free(elementString);
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
char* text(void* macro_ptr, Object* text) {
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
char* paragraph(void* macro_ptr, Object* paragraph) {
	char *paragraphString=NULL, *childString=NULL;
	Macro *textMacro, *listMacro, *tableMacro, *macros;
	size_t paragraphSize=0;
	Object* child=NULL;

	macros = (Macro*) macro_ptr;
	textMacro = getMacro(macros, TEXT_TAG);
	listMacro = getMacro(macros, LIST_TAG);
	tableMacro = getMacro(macros, TABLE_TAG);

	child = paragraph->children;
	if(!child)
		return NULL;

	if(!strcmp(child->name, TEXT_TAG)) {
		childString = textMacro->body(macros, child);
		if(!childString)
			return NULL;

		paragraphSize = strlen(childString) + strlen(INDENT);
		if(!(paragraphString = malloc(paragraphSize+1)))
			return NULL;

		memset(paragraphString, 0, paragraphSize+1);
		strcat(paragraphString, INDENT);
		strcat(paragraphString, childString);
		free(childString);
	} else if(!strcmp(child->name, LIST_TAG)) {
		childString = listMacro->body(macros, child);
		if(!childString)
			return NULL;

		paragraphSize = strlen(childString);
		if(!(paragraphString = malloc(paragraphSize+1)))
			return NULL;

		memset(paragraphString, 0, paragraphSize+1);
		strcat(paragraphString, childString);
		free(childString);
	} else if(!strcmp(child->name, TABLE_TAG)) {
		childString = tableMacro->body(macros, child);
		if(!childString)
			return NULL;

		paragraphSize = strlen(childString);
		if(!(paragraphString = malloc(paragraphSize+1)))
			return NULL;

		memset(paragraphString, 0, paragraphSize+1);
		strcat(paragraphString, childString);
		free(childString);		
	}

	return paragraphString;
}

/**
 * Render a page string from the page object
 * @param  macro_ptr The address of the macro list
 * @param  page      The page object
 * @return           The string representation of the page
 */
char* page(void* macro_ptr, Object* page) {
	char *newPage=NULL, *oldPage=NULL;
	Macro *paragraphMacro, *macros;
	size_t pageSize=0;
	Object *children=NULL, *nextChild;

	macros = (Macro*) macro_ptr;
	paragraphMacro = getMacro(macros, PARAGRAPH_TAG);

	// Reverse order of children
	for(Object* child=page->children; child!=NULL; child=nextChild) {
		nextChild = child->next;
		child->next = children;
		children = child;
	}


	for(Object* child=children; child!=NULL; child=child->next) {
		char* childString;
		size_t childStringSize;

		if(!strcmp(child->name, PARAGRAPH_TAG)) {
			childString = paragraphMacro->body(macros, child);
			if(!childString)
				continue;
		} else {
			continue;
		}

		childStringSize = strlen(childString);
		pageSize += childStringSize + strlen("\n");
		if(!(newPage = malloc(pageSize+1)))
			return NULL;

		memset(newPage, 0, pageSize+1);
		if(oldPage != NULL) {
			strcat(newPage, oldPage);
			free(oldPage);			
		}
		strcat(newPage, childString);
		free(childString);
		strcat(newPage, "\n");
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
char* document(void* macro_ptr, Object* document) {
	char *newDocument=NULL, *oldDocument=NULL;
	Macro *pageMacro, *columnMacro, *macros;
	size_t documentSize=0;
	Object* pages=NULL;
	Object* nextChild;
	unsigned int totalPageNum=0;
	char** lineBuffer;
	size_t docLength=11, docWidth=20;
	unsigned int columnNum=1;

	macros = (Macro*) macro_ptr;
	pageMacro = getMacro(macros, PAGE_TAG);
	columnMacro = getMacro(macros, COLUMN_TAG);

	for(Object* child=document->children; child!=NULL; child=nextChild) {
		nextChild = child->next;

		if(!strcmp(child->name, PAGE_TAG) || !strcmp(child->name, COLUMN_TAG)) {
			child->next = pages;
			pages = child;
			continue;
		}

		if(!strcmp(child->name, LENGTH_TAG)) {
			child = child->children;
			if(child)
				docLength = atoi(child->name);
			continue;
		}

		if(!strcmp(child->name, WIDTH_TAG)) {
			child = child->children;
			if(child)	
				docWidth = atoi(child->name);
			continue;
		}
	}

	if(!(lineBuffer = malloc(docLength * sizeof(char *))))
		return NULL;

	for (int i=0; i < docLength; i++) {
		if(!(lineBuffer[i] = (char *)malloc(docWidth + 3)))
			return NULL;

		memset(lineBuffer[i], 0, docWidth + 3);

	}

	columnWidth = docWidth;

	for(Object* page=pages; page!=NULL; page=page->next) {
		char *pageString, *columnString;
		size_t pageSize, numLines;
		char* lineString;
		char* pageNumString;
		size_t lineStringLength;
		unsigned int columnIndex;

		if(!strcmp(page->name, COLUMN_TAG)) {
			columnString = columnMacro->body(macros, page);
			if(!columnString) {
				columnNum = 1;
				continue;
			}
			columnNum = atoi(columnString);
			if((docWidth / columnNum) - strlen(TAB) < 1)
				columnNum = 1;
			columnWidth = (docWidth / columnNum) - strlen(TAB);
			continue;
		}

		pageString = pageMacro->body(macros, page);
		if(!pageString) 
			continue;

		lineString = strtok(pageString, '\n');

		// Add new page
		totalPageNum++;
		documentSize += (docWidth + 1) * (docLength + 2);
		if(!(newDocument = malloc(documentSize+1)))
			return NULL;

		memset(newDocument, 0, documentSize+1);
		if(oldDocument != NULL) {
			size_t existing;
			
			existing = strlen(oldDocument);
			memcpy(newDocument, oldDocument, existing);
			free(oldDocument);
		}
		oldDocument = newDocument;

		columnIndex = 1;
		// Add Lines to page
		for(int lineIndex = 0; lineIndex < docLength; lineIndex++) {
			// Last line in page
			if(lineIndex == docLength - 1) {

				// Last column in page
				if(columnIndex == columnNum) {
					size_t existing;

					// Add page number
					if(!(pageNumString = malloc(docWidth)))
						return NULL;

					memset(pageNumString, 0, docWidth);
					pageNumString = itoa(totalPageNum, pageNumString);
					strcat(lineBuffer[lineIndex], " ");
					strncat(lineBuffer[lineIndex], pageNumString, docWidth-1);

					memset(newDocument, '=', docWidth);
					strcat(newDocument, "\n");
					// Append lineBuffers to document
					for(int index=0; index<docLength; index++) {
						strcat(newDocument, lineBuffer[index]);
						strcat(newDocument, "\n");

					}

					existing = strlen(newDocument);
					memset(&newDocument[existing], '=', docWidth);

					for (int i=0; i < docLength; i++) {
						memset(lineBuffer[i], 0, docWidth + 3);
					}

					// More lines in page?
					if(lineString != NULL) {
						// Add new page
						totalPageNum++;
						documentSize += (docWidth + 1) * (docLength + 2);
						if(!(newDocument = malloc(documentSize+1)))
							return NULL;

						memset(newDocument, 0, documentSize+1);
						if(oldDocument != NULL) {
							size_t existing;
							
							existing = strlen(oldDocument);
							memcpy(newDocument, oldDocument, existing);
							free(oldDocument);
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
				size_t remaining;

				remaining = strlen(lineBuffer[lineIndex]);
				memset(&lineBuffer[lineIndex][remaining], ' ', columnWidth);
				strcat(lineBuffer[lineIndex], TAB);
				continue;
			}

			lineStringLength = strlen(lineString);
			if(lineStringLength > columnWidth) {
				strncat(lineBuffer[lineIndex], lineString, columnWidth);
				if(columnNum > 1)
					strcat(lineBuffer[lineIndex], TAB);
				lineString += columnWidth;
			} else {
				size_t lineBufferLength;

				strcat(lineBuffer[lineIndex], lineString);
				for(int i=0; i<columnWidth - lineStringLength; i++)
					strcat(lineBuffer[lineIndex], " ");

				if(columnNum > 1)
					strcat(lineBuffer[lineIndex], TAB);
				lineString = strtok(NULL, '\n');
			}

		}

		transmit_all(STDOUT, newDocument, strlen(newDocument));
		transmit_all(STDOUT, "\x3", strlen("\x3"));
		free(newDocument);
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
Macro* newMacro(char* name, char* (*body)(void *macros, Object* object)) {
	Macro* macro;
	size_t nameSize;

	if(!(macro = malloc(sizeof(Macro))))
		return NULL;

	nameSize = strlen(name);
	if(!(macro->name = malloc(nameSize+1)))
		return NULL;

	memset(macro->name, 0, nameSize+1);
	memcpy(macro->name, name, nameSize);
	macro->body = body;

	return macro;
}

/**
 * Initialize the macros
 * 
 * @param macro_ptr The address of the macro list
 */
void initMacros(Macro** macro_ptr) {
	Macro* macro;

	macro = newMacro(ELEMENT_TAG, &element);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = newMacro(DOCUMENT_TAG, &document);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = newMacro(PAGE_TAG, &page);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = newMacro(PARAGRAPH_TAG, &paragraph);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = newMacro(TEXT_TAG, &text);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = newMacro(LIST_TAG, &list);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = newMacro(COLUMN_TAG, &text);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

	macro = newMacro(TABLE_TAG, &table);
	macro->next = *macro_ptr;
	*macro_ptr = macro;

}

/**
 * Initialize all custom macros
 * 
 * @param customMacrosPtr The address of the custom macro list
 */
void initCustomMacros(Object **customMacrosPtr) {
	getObject(customMacrosPtr, NULL, &FourByFourTable_Macro);
	getObject(customMacrosPtr, NULL, &FiveByFiveTable_Macro);
	getObject(customMacrosPtr, NULL, &AlphanumericOutline_Macro);
	getObject(customMacrosPtr, NULL, &BulletedOutline_Macro);

}

/**
 * Send the Document ID to the requester
 * 
 * @param documentID The value of the documentID
 */
void sendDocumentID(unsigned int documentID) {
	char* documentIDString;

	if(!(documentIDString = malloc(20)))
		return;

	documentIDString = itoa(documentID, documentIDString);
	transmit_all(STDOUT, DOC_ID_STRING, strlen(DOC_ID_STRING));
	transmit_all(STDOUT, documentIDString, strlen(documentIDString));
	transmit_all(STDOUT, "\n", strlen("\n"));
}


int main(void) {
	Object* documentObject;
	Macro* macros;
	char* documentString;
	Object* customMacros=NULL;
	char* titleObject;
	unsigned int documentID;
	char* documentIDString;

	documentID = getDocumentID();

	if(!(titleObject = malloc(sizeof(Macro))))
		return -1;

	initMacros(&macros);
	initCustomMacros(&customMacros);
	free(titleObject);
	documentObject = getObject(&customMacros, NULL, NULL);

	sendDocumentID(documentID);
	documentString = document(macros, documentObject);

	return 0;
}