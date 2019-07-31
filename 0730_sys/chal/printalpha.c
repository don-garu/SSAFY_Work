#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main(){
	char buf[BUFSIZE];
	int cnt[26], len;
	FILE* fp;

	memset(cnt, 0, sizeof(cnt));
	memset(buf, 0, sizeof(buf));

	if ((fp = fopen("report/dirlist.lst", "r")) == NULL){
		perror("open");
		exit(1);
	}

	while(fgets(buf, BUFSIZE, fp) != NULL){
		len = strlen(buf);
		for (int i = 0; i<len; i++){
			if (buf[i] == ' ')
				break;
			if (buf[i] >= 'A' && buf[i] <= 'Z')
				cnt[buf[i] - 'A']++;
			if (buf[i] >= 'a' && buf[i] <= 'z')
				cnt[buf[i] - 'a']++;
		}
	}
	for (int i = 0; i<26; i++){
		printf("%c: %d\n", (char)(i + 'A'), cnt[i]);
	}
}
