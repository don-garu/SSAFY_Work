#include <stdio.h>


#include "../header/function.h"
#include "../header/m_socket.h"

int main(){
	pid_t pid = 0;
	char *buf_rcv, *buf_snd, **buf_parsed, cur[BUFSIZE] = HOME_DIR, *buf_ret;
	int argc, i = 0;
	struct stat sbuf;

	init_server();
	for (i = 0; i<5; i++){
		if (fork() == 0)
			break;
	}
	init_server_thread();

	buf_snd = (char*)calloc(sizeof(char), BUFSIZE);

	while (1){
		strcat(buf_snd, "\n");
		strcat(buf_snd, cur);
		serv_write(buf_snd);

		memset(buf_snd, 0, BUFSIZE);

		printf("CUR : %s\n", cur);
		buf_rcv = serv_read();
		if (strncmp(buf_rcv, "exit", 4) == 0)
			break;
		buf_parsed = parsing(buf_rcv);
		argc = 0;
		for (i = 0; i < BUFDEG; i++){
			if (buf_parsed[i] == NULL || strlen(buf_parsed[i]) == 0)
				break;
			argc++;
		}
		switch(command_chk(buf_parsed[0])){
		case CMD_LS:
			printf("<LS>\n");
			buf_ret = command_ls(cur, argc, buf_parsed);
			strcpy(buf_snd, buf_ret);
			break;
		case CMD_CD:
			printf("<CD>\n");
			buf_ret = command_cd(cur, buf_parsed[1]);
			if (access(buf_ret, F_OK) == -1)
				break;
			stat(buf_ret, &sbuf);
			if (!S_ISDIR(sbuf.st_mode))
				break;
			strcpy(cur, buf_ret);
			break;
		case CMD_CP:
			printf("<CP>\n");
			if (argc != 3){
				strcpy(buf_snd, "Usage : cp <ORIGIN> <COPY>");
				break;
			}
			command_cp(cur, buf_parsed[1], buf_parsed[2]);
			break;
		case CMD_MKDIR:
			printf("<MKDIR>\n");
			if (argc != 2){
				strcpy(buf_snd, "Usage : mkdir <DIRNAME>");
				break;
			}
			command_mkdir(cur, buf_parsed[1]);
			break;
		case CMD_RM:
			printf("<RM>\n");
			if (argc != 2){
				strcpy(buf_snd, "Usage : rm <filename>");
				break;
			}
			command_rm(cur, buf_parsed[1]);
			break;
		default:
			printf("Unknown Command. %s\n", buf_parsed[0]);
			break;
		}
	}
	
	exit_server();
}
