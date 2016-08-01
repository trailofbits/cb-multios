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
#include <libcgc.h>
#include "libc.h"
#include "service.h"

void newReport(Report *report) {
	char character = 0;
	char* string = NULL;
	short pos = 0, prev_pos=0;
	short num_fields = 0;
	Field* new_field = NULL;

	while(END_CHAR != character) {
		if(SPLIT_CHAR == character) {
			new_field = malloc(sizeof(Field));
#ifdef PATCHED
			if(new_field == NULL)
				_terminate(ALLOCATE_ERROR);
#endif
			new_field->start = prev_pos-num_fields;
			new_field->size = pos-prev_pos-1;
#ifdef PATCHED
			if(new_field->size <= 0 || new_field->size > MAX_FIELD_SIZE)
				_terminate(FIELD_SIZE_ERROR);
#endif
			new_field->next = report->fields;
			report->fields = new_field;
			prev_pos = pos;
			num_fields++;
		}
		recv(STDIN, &character, sizeof(character));
		pos++;
#ifdef PATCHED
        if(pos < 0)
            _terminate(FIELD_SIZE_ERROR);
#endif
	}
	new_field = malloc(sizeof(Field));
#ifdef PATCHED
	if(new_field == NULL)
		_terminate(ALLOCATE_ERROR);
#endif
	new_field->start = prev_pos-num_fields;
	new_field->size = pos-prev_pos-1;
#ifdef PATCHED
			if(new_field->size <= 0 || new_field->size > MAX_FIELD_SIZE)
				_terminate(FIELD_SIZE_ERROR);
#endif
	new_field->next = report->fields;
	report->fields = new_field;
	num_fields++;

	report->record_size = pos-num_fields;

#ifdef PATCHED
	if(report->record_size <= 0 || report->record_size > MAX_REPORT_SIZE || report->record_size <= new_field->size+1)
		_terminate(REPORT_SIZE_ERROR);
#endif
}

void sendReport(Report *report) {
	Record* nextRecord = NULL;
	int ret=0;

	for(nextRecord=report->head; nextRecord != NULL; nextRecord = nextRecord->next) {
		if(transmit_all(STDOUT, nextRecord->data, report->record_size)) 
			_terminate(TRANSMIT_ERROR);
	}
}

void splitReport(Record *source, Record **front, Record **back) {
	Record *fast;
	Record *slow;

	if(!source || !source->next) {
		*front = source;
		*back = NULL;
	} else {
		slow = source;
		fast = source->next;

		while (fast != NULL) {
			fast = fast->next;
			if(fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		*front = source;
		*back = slow->next;
		slow->next = NULL;
	}

}

Record* mergeReport(Record* a, Record* b, Field* field) {
	Record* result = NULL;
	int compare;

	if(!a)
		return b;

	if(!b)
		return a;

	compare = strncmp(&a->data[field->start], &b->data[field->start], field->size);

	if(compare <= 0) {
		result = a;
		result->next = mergeReport(a->next, b, field);
	} else {
		result = b;
		result->next = mergeReport(a, b->next, field);
	}

	return result;
}

void sortReport(Record **headRef, Field* field) {
	Record *head = *headRef;
	Record *a=NULL, *b=NULL;

	if(!head || !head->next)
		return;

	splitReport(head, &a, &b);
	sortReport(&a, field);
	sortReport(&b, field);

	*headRef = mergeReport(a, b, field);

}

void filterReport(Report *report, Report* filteredReport, char* filterString) {
	Record* nextRecord = NULL;
	Field* nextField = NULL;
	int compare = 0;

	for(nextRecord = report->head; nextRecord != NULL; nextRecord = nextRecord->next) {
		for(nextField = report->fields; nextField->next != NULL; nextField = nextField->next) {
			compare = strncmp(&nextRecord->data[nextField->start], &filterString[nextField->start], nextField->size);
			if(!compare) {
				Record* record;
				record = malloc(sizeof(Record));
#ifdef PATCHED
				if(record == NULL)
					_terminate(ALLOCATE_ERROR);
#endif
				record->next = filteredReport->head;
				record->data = nextRecord->data;
				filteredReport->head = record;
				break;
			}
		}
	}

}


int newRecord(Report *report) {
	Record* record = NULL;
	short second_field_size = 0;
	char* receive_buf = NULL;
	Field* nextField = NULL;
	short field_index = 0;

	record = malloc(sizeof(Record));
#ifdef PATCHED
	if(record == NULL)
		_terminate(ALLOCATE_ERROR);
#endif
	record->next = NULL;
	record->data = malloc(report->record_size*2); 
#ifdef PATCHED
	if(record->data == NULL)
		_terminate(ALLOCATE_ERROR);
#endif
	receive_buf = malloc(report->record_size*2);
#ifdef PATCHED
	if(receive_buf == NULL)
		_terminate(ALLOCATE_ERROR);
#endif

	memset(record->data, 0, report->record_size);
    
    for(nextField = report->fields; nextField != NULL; nextField = nextField->next) {
    	memset(receive_buf, 0, report->record_size);
    	recv(STDIN, receive_buf, nextField->size);

    	strcpy(&record->data[field_index], receive_buf);
    	field_index += nextField->size;
    }

	free(receive_buf);

	if(startswith(record->data, "END")) {
		free(record->data);
		free(record);
		return 0;
	} else if(startswith(record->data, "REPORT")) {
		sendReport(report);
		free(record->data);
		free(record);
		return 1;
	} else if(startswith(record->data, "SORT")) {
		unsigned short field_index;
		Field* key;

		field_index = record->data[sizeof("SORT")-1];
		for(key = report->fields; key != NULL; key=key->next) {
			if(field_index == 0) {
				break;
			}
			field_index--;
		}

		if(key)
			sortReport(&report->head, key);

		free(record->data);
		free(record);

		return 1;
	} else if(startswith(record->data, "FREPORT")) {
		Report filteredReport = {NULL, 0, 0};
		filteredReport.record_size = report->record_size;
		filterReport(report, &filteredReport, record->data);
		sendReport(&filteredReport);
		free(record->data);
		free(record);

		return 1;
	} else {
		char* command;
		command = &record->data[report->fields->start];

		if(startswith(command, "ERROR")) {
#ifdef PATCHED
			free(record->data);
#else
			free(command);
#endif
			free(record);
			return 1;
		}
	}

	record->next = report->head;
	report->head = record;

	return 1;

}

int main(void) {
	Report report = {NULL, 0, 0};
	char* field = NULL;

	newReport(&report);
 	while(newRecord(&report));

	return 0;
}
