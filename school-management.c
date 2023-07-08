#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>

void input();
void display();
void search();
void searchByRoll();
void searchByName();
void modify();
void del();
void sort();

struct student{
	char name[30];
	char class[10];
	int rollNo;
	char date[12];
	//char fatherName[30];
}s;

FILE *fp;

int main(){
	
	int ch;
	while(1){
		system("cls");
		printf("<==  School Management ==>\n");
		printf("1. Take Admission\n");
		printf("2. Student Info\n");
		printf("3. Search\n");
		printf("4. Modify\n");
		printf("5. Delete\n");
		printf("6. Sort by Roll Number\n");
		printf("0. Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d", &ch);
		
		switch(ch){
			case 0:
				exit(0);
				
			case 1:
				input();
				break;
				
			case 2:
				display();
				break;
				
			case 3:
				search();
				break;
				
			case 4:
				modify();
				break;
				
			case 5:
				del();
				break;
				
			case 6:
				sort();
				break;
				
			default:
				printf("Invalid Choice...");
				
		} 	
		printf("\n\nPress Any Key To Continue...");
		getch();
	}
	return 0;
}

void input(){
	
	char myDate[12];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	strcpy(s.date, myDate);
	
	fp = fopen("stud.txt", "ab");
	printf("Enter student name: ");
	fflush(stdin);
	gets(s.name);
	printf("Enter class: ");
	gets(s.class);
	printf("Enter roll no: ");
	scanf("%d", &s.rollNo);
	
	fwrite(&s, sizeof(s), 1, fp);
	printf("Record Saved Successfully...");
	fclose(fp);
}

void display(){
	
	system("cls");
	printf("<== Student Info ==>\n");
	printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
	fp = fopen("stud.txt", "rb");
	while(fread(&s, sizeof(s), 1, fp) == 1){
		printf("%-30s %-20s %-10d %s\n", s.name, s.class, s.rollNo, s.date);  
	}
	fclose(fp);
}

void search(){
		
	int ch;
	while(1){
		system("cls");
		printf("<== Search ==>\n");
		printf("1. Search by Roll No.\n");
		printf("2. Search by Name\n");
		printf("0. Back To Main Menu\n");
		printf("\n\nEnter your choice: ");
		scanf("%d", &ch);
		
		switch(ch){
			
			case 0:
				main();
				break;
			
			case 1:
				searchByRoll();
				break;
				
			case 2:
				searchByName();
				break;
				
			default:
				printf("Invalid Choice...");
		}
		getch();
	}
}

void searchByRoll(){
	int rl, f=0;
	printf("Enter Roll Number to search:");
	scanf("%d", &rl);
	
	printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
	fp = fopen("stud.txt", "rb");
	while(fread(&s, sizeof(s), 1, fp) == 1){
		if(rl == s.rollNo){
			f = 1;
			printf("%-30s %-20s %-10d %s\n", s.name, s.class, s.rollNo, s.date);  
			break;
		}
	}
	fclose(fp);
	if(f == 0){
		printf("Record not found");
	}else{
		printf("\n\nRecord found successfully");
	}
}

void searchByName(){
	char na[30];
	int f=0;
	printf("Enter Name to search:");
	fflush(stdin);
	gets(na);
	printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
	fp = fopen("stud.txt", "rb");
	while(fread(&s, sizeof(s), 1, fp) == 1){
		if(strcmpi(na, s.name) == 0){
			f = 1;
			printf("%-30s %-20s %-10d %s\n", s.name, s.class, s.rollNo, s.date);  
			break;
		}
	}
	fclose(fp);
	if(f == 0){
		printf("Record not found");
	}else{
		printf("\n\nRecord found successfully");
	}
}

void modify(){
	int rl, f=0;
	printf("Enter Roll Number to modify:");
	scanf("%d", &rl);
	 fp = fopen("stud.txt", "rb+");
	while(fread(&s, sizeof(s), 1, fp) == 1){
		if(rl == s.rollNo){
			f = 1;
			printf("Enter new name: ");
			fflush(stdin);
			gets(s.name);
			printf("Enter new class: ");
			fflush(stdin);
			gets(s.class);
			printf("Enter new roll: ");
			scanf("%d", &s.rollNo);
			fseek(fp, -(sizeof(s)), 1);
			fwrite(&s, sizeof(s), 1, fp);
			fclose(fp);
			break;
		}
	}
	if(f == 0){
		printf("Record not found");
	}else{
		printf("\n\nRecord Modified  successfully");
	}
}

void del(){
	int rl, f=0;
	printf("Enter Roll Number to delete:");
	scanf("%d", &rl);
	
	FILE *ft;
	
	fp = fopen("stud.txt", "rb");
	ft = fopen("temp.txt", "ab");
	while(fread(&s, sizeof(s), 1, fp) == 1){
		if(rl == s.rollNo){
			f = 1;
		}else{
			fwrite(&s, sizeof(s), 1, ft);
		}
	}
	fclose(fp);
	fclose(ft);
	remove("stud.txt");
	rename("temp.txt", "stud.txt");
	
	if(f == 0){
		printf("Record not found");
	}else{
		printf("\n\nRecord deleted successfully");
	}
}

void sort(){
	int c=0, i, j;
	struct student s1[50], t;
	system("cls");
	printf("<== Sort by Roll Number ==>\n\n");
	printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
	fp = fopen("stud.txt", "rb");
	while(fread(&s, sizeof(s), 1, fp) == 1){
		s1[c++] = s;
	}
	// Selection Sort
	for(i=0; i<c-1; i++){
		for(j=i+1; j<c; j++){
			if(s1[i].rollNo > s1[j].rollNo){
				t = s1[i];
				s1[i] = s1[j];
				s1[j] = t; 
			}
		}
	}
	
	for(i=0; i<c; i++){
		printf("%-30s %-20s %-10d %s\n", s1[i].name, s1[i].class, s1[i].rollNo, s1[i].date);
	}
	fclose(fp);
}

