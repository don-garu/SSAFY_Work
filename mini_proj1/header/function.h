#pragma once

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 1024
#define BUFDEG 10

#define HOME_DIR "home"

#define CMD_BASE 1000
#define CMD_LS CMD_BASE + 1
#define CMD_CD CMD_BASE + 2
#define CMD_CP CMD_BASE + 3
#define CMD_MKDIR CMD_BASE + 4
#define CMD_RM CMD_BASE + 5

/*
char** parsing(char* msg);
void command_rm(char* cur, char* file);
void command_cp(char* cur, char* origin, char* copy);
void command_mkdir(char* cur, char* dirname);
char* command_cd(char* cur, char* next);
int command_chk(char* msg);
char* command_ls(char* cur, int argc, char** argv);
*/

char** parsing(char* msg){
	char **ret, *tmp;
	int i;
	ret = (char**)calloc(sizeof(char*), BUFDEG);
	for (i = 0; i < BUFDEG; i++){
		ret[i] = (char*)calloc(sizeof(char), BUFSIZE);
	}

	tmp = strtok(msg, " ");
	for (i = 0; i < BUFDEG; i++){
		printf("%d : %s\n", i, tmp);
		strcpy(ret[i], tmp);
		tmp = strtok(NULL, " ");
		if (tmp == NULL)
			break;
	}
	return ret;
}

void command_rm(char* cur, char* file){
	char path[BUFSIZE];
	if (cur[strlen(cur) - 1] == '/')
		sprintf(path, "%s%s", cur, file);
	else
		sprintf(path, "%s/%s", cur, file);

	if (remove(path) == -1){
		perror("remove");
		return;
	}
	return;
}

void command_cp(char* cur, char* origin, char* copy){
	char path_orig[BUFSIZE], path_copy[BUFSIZE], buf[BUFSIZE];
	FILE* fp1, *fp2;
	struct stat sbuf;
	if (cur[strlen(cur) - 1] == '/'){
		sprintf(path_orig, "%s%s", cur, origin);
		sprintf(path_copy, "%s%s", cur, copy);
	}
	else{
		sprintf(path_orig, "%s/%s", cur, origin);
		sprintf(path_copy, "%s/%s", cur, copy);
	}
	
	if (access(path_orig, F_OK) == -1){
		printf("No File or Directory\n");
		return;
	}
	if (stat(path_orig, &sbuf) == -1){
		perror("stat error ");
		return;
	}
	if (S_ISDIR(sbuf.st_mode)){
		printf("Can't copy directory\n");
		return;
	}
	fp1 = fopen(path_orig, "r");
	fp2 = fopen(path_copy, "w");
	
	while (fgets(buf, BUFSIZE, fp1)){
		fprintf(fp2, "%s", buf);	
	}

	fclose(fp1);
	fclose(fp2);
	return;
}

void command_mkdir(char* cur, char* dirname){
	char path[BUFSIZE];
	if (cur[strlen(cur) - 1] == '/')
		sprintf(path, "%s%s", cur, dirname);
	else
		sprintf(path, "%s/%s", cur, dirname);

	if (mkdir(path, 0766) == -1){
		perror("mkdir error ");
		return;
	}
}

char* command_cd(char* cur, char* next){
	char path[BUFSIZE], *ret;
	int i;
	ret = (char*)calloc(sizeof(char), BUFSIZE);

	if (strlen(next) == 0 || next == NULL){
		strcpy(ret, HOME_DIR);
	}
	else if (strlen(next) == 1 && strcmp(next, ".") == 0){
		strcpy(ret, cur);
	}
	else if (strlen(next) == 2 && strcmp(next, "..") == 0){
		for (i = strlen(cur) - 2; i >= 0; i--){
			if (cur[i] == '/'){
				cur[i] = '\0';
				break;
			}
		}
		strcpy(ret, cur);
	}
	else {
		if (cur[strlen(cur) - 1] == '/')
			sprintf(path, "%s%s", cur, next);
		else
			sprintf(path, "%s/%s", cur, next);
		strcpy(ret, path);
	}
	return ret;
}

char* command_ls(char* cur, int argc, char** argv){
	DIR* dp;
	struct dirent *dent;
	char path[BUFSIZE], *ret;
	if (argv[1] != NULL && strlen(argv[1]))
		sprintf(path, "home/%s", argv[1]);
	else
		strcpy(path, cur);

	if ((dp = opendir(path)) == NULL){
		perror("opendir error ");
		return NULL;
	}
	ret = (char*)calloc(sizeof(char), BUFSIZE);

	printf("DIR <%s> : ", path);
	strcpy(ret, "DIR : ");
	while (dent = readdir(dp)){
		if (dent->d_name[0] == '.')
			continue;
		printf("%s ", dent->d_name);
		strcat(ret, dent->d_name);
		strcat(ret, " ");
		// OPTION
	}
	printf("\n");
	strcat(ret, "\n");

	closedir(dp);
	return ret;
}

int command_chk(char* msg){
	if (strncmp(msg, "ls", 2) == 0){
		return CMD_LS;
	}
	if (strncmp(msg, "cd", 2) == 0){
		return CMD_CD;
	}
	if (strncmp(msg, "cp", 2) == 0){
		return CMD_CP;
	}
	if (strncmp(msg, "mkdir", 5) == 0){
		return CMD_MKDIR;
	}
	if (strncmp(msg, "rm", 2) == 0){
		return CMD_RM;
	}
	return -1;
}
