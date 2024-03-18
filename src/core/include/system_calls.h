#ifndef _SYSTEM_CALLS_H
#define _SYSTEM_CALLS_H

#define PCB_PTR_MASK 0xFFFFE000 
#define LARGENUMBER 100000
#define LOAD_ADDRESS 0x8048000
#define IN_USE 0x0001
#define NOT_IN_USE 0x0000
#define FILE_START 0x0000

#define RTC_TYPE	0 
#define DIR_TYPE	1
#define	FILE_TYPE	2

#define MIN_FD		2
#define MAX_FD		7   

#define MAX_FILES 8
#define MAX_PROCESSES 6

#define FILE_NAME_SIZE 32
#define MAX_COMMAND_SIZE 10
#define MAX_BUFFER_SIZE 100
#define READ_BUFFER_SIZE 4
#define ENTRY_POINT_START 24


#endif // _SYSTEM_CALLS_H