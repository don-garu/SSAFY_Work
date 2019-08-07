#include <stdio.h>

#include "../header/m_socket.h"

int main(int argc, char** argv){
	if (argc != 2){
		printf("Usage : %s <IP> \n", argv[0]);
		exit(1);
	}
	char *buf_rcv, *buf_snd;
	buf_snd = (char*)calloc(sizeof(char), BUFSIZE);

	init_client(argv[1]);

	while (1){
		buf_rcv = clnt_read();
		printf("%s$ ", buf_rcv);
		fgets(buf_snd, BUFSIZE, stdin);
		buf_snd[strlen(buf_snd) - 1] = '\0';
		clnt_write(buf_snd);
		if (strcmp(buf_snd, "exit") == 0){
			break;
		}
	}

	exit_client();
}
