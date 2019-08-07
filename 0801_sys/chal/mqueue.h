#include <sys/msg.h>

#define MSGSIZE 50
#define MSQKEY 34828

typedef struct {
	long mtype;
	char mtext[MSGSIZE];
}MSG;
