#include <stdio.h>
#include <stdlib.h>

char FILENAME[100] = "./notes.txt";

/*add a note to text file*/
void writeFile(char *s){
	FILE * fp;
	fp = fopen("./notes.txt","a");  	
	fprintf(fp, "%s", s);
	fclose(fp);
}

void addNote(){
	char in[256];
	printf("Enter the note: ");
	fgets(in, 256, stdin);
	printf("%s",in);
	writeFile(&in[0]);
}
/*remove note from text file*/
void removeNote(){
	int rInt;
	char tInt[20];
	printf("Enter the note number to delete (0 for all): ");
	fgets(tInt, 20, stdin);
	rInt = strtol(tInt, NULL, 0);
	/* open curr file */
	FILE * currF;
	currF = fopen("./notes.txt","r");  	
	if(rInt == 0){
		fclose(currF);
		FILE * ccf;
		fopen(FILENAME, "w");
		return;
	}	
	/* open temp file */
	FILE *tf;
	tf = fopen("./temp_notes.txt", "w");
	char ab[256];
	int k = 0;
	/* copy lines over except deleted*/
	while(fgets(ab, sizeof(ab), currF)){
		k += 1;
		if(k != rInt){
			fprintf(tf, "%s", &ab[0]);			
		}
	}
	fclose(tf);
	/* delete curr file*/
	remove("./notes.txt");
	/* rename temp to notes.txt*/
	rename("./temp_notes.txt", FILENAME);
	fclose(currF);
}

/*print note list */
void printList(){
	FILE * fp1;
	int k = 0;
	fp1 = fopen("./notes.txt", "r");
	char c[256];
	while(fgets(c, sizeof(c), fp1)){
		k += 1;
		printf("[%d] %s",k, c);
	
	}
	fclose(fp1); 
}


void printMenu(){
	printf("Welcome to sol's note taker app.\n");
	printf("Options:\n");
	printf("[1] Add a note\n");
	printf("[2] Delete a note\n");
	printf("[3] View Notes\n");
	printf("[4] Exit\n");
}
int main(){
	int a;
	char p[20];
	while(1){
		printMenu();
		fgets (p, 20, stdin);
		a = strtol(p, NULL, 0);
		switch(a){
			case 1:
				addNote();
				break;
			case 2:
				removeNote();
				break;
			case 3:
				printList();
				break;
			case 4:
				exit(0);
			default:
				printf("DONE");
		}
	}
	return 0;
}
