#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	struct stat buf;

	stat("test.txt", &buf);
	printf("Before Link Count = %d\n", (int)buf.st_nlink);

	link("test.txt", "unix.ln");

	stat("test.txt", &buf);
	printf("After Link Count = %d\n", (int)buf.st_nlink);

	// Symbolic link

	symlink("test.txt", "test.sln");

	return 0;
}
