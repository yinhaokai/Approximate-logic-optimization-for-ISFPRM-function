#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define Debug(fmt, a...) \
do{ \
	char cMsgBuf[128] = {0}; \
	sprintf(cMsgBuf, "[Dbg]:(%s:%d): ",  __FILE__, __LINE__); \
	sprintf(cMsgBuf + strlen(cMsgBuf), fmt, ##a); \
	printf("%s", cMsgBuf); \
}while(0)

