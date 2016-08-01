#ifndef TIME_H_
#define TIME_H_

extern unsigned long long current_time; /* in milliseconds since epoch */

int handle_msg_time(void *data, unsigned int n);

#endif
