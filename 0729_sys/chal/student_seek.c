#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 20

typedef struct {
	char name[MAX_NAME_LEN + 1];
	int age, num;
}Student;

void store_students();
void search_student();

Student stu_list[5];

int main(int argc, char *argv[]){
	int n;
	if (argc != 2){
		printf("Usage : %s [mode]\n", argv[0]);
		exit(1);
	}
	if (strcmp(argv[1], "save") == 0)
		store_students();
	else if (strcmp(argv[1], "find") == 0)
		search_student();
	else{
		printf("Enabled argv is (save / find)\n");
		exit(1);
	}
}

void search_student(){
	FILE *fp;
	Student tmp;
	int idx;
	if ((fp = fopen("students.dat", "rb")) == NULL){
		perror("Open error");
		exit(1);
	}

	printf("Input Num (1 ~ 4) : ");
	scanf("%d", &idx);

	fseek(fp, sizeof(Student) * (idx - 1), SEEK_SET);
	fread(&tmp, sizeof(Student), 1, fp);

	printf("Name : %s Num : %d Age : %d\n", tmp.name, tmp.num, tmp.age);
	fclose(fp);
}

void store_students(){
	FILE *fp;
	int i;
	if ((fp = fopen("students.dat", "wb")) == NULL){
		perror("Open error");
		exit(1);
	}

	strcpy(stu_list[0].name, "Hong Guil-dong");
	strcpy(stu_list[1].name, "Gang Gam-chan");
	strcpy(stu_list[2].name, "Kim Yu-sin");
	strcpy(stu_list[3].name, "Lee Soon-sin");

	stu_list[0].age = 20, stu_list[0].num = 3;
	stu_list[1].age = 30, stu_list[1].num = 4;
	stu_list[2].age = 70, stu_list[2].num = 1;
	stu_list[3].age = 35, stu_list[3].num = 2;

	i = fwrite(stu_list, sizeof(Student), 4, fp);
	if (i == -1){
		perror("Write error");
		exit(1);
	}

	fclose(fp);
}
