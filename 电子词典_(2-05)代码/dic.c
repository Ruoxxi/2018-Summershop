#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define LEN sizeof(struct word)

struct word *creat(struct word *head);//�����ʿ� 
struct word *creatOther(struct word *head, char name[50]);//������ѯ��¼�����ʱ����� 
void search();//���ҵ��� 
void regist();//ע�� 
void load();//��¼ 
void history(int num);//������ʷ��¼�ĵ� 
void difficulty(int num1);//�������ʱ��ĵ� 
void output(char name[50]); //������ʱ�����ʷ��¼ 
void menu();//�˵��� 
void add(char eng[20], char chi[50]);//��������ʱ� 
void addWord(int b);//���Ӵʵ��� 
void editWord(int b);//�޸ĵ��� 
void delWord(int b);//ɾ������ 
void edit(int a);//�༭���� 
void study();//������
void addToStudy(char eng[20], char chi[50]);
void test();//С���� 

static char hist[50];//������ʷ��¼�ļ��� 
static char diff[50];//�������ʱ��ļ��� 
static char stud[50];//���屳�����ļ��� 

struct word{
	char chi[50];
	char eng[20];
	struct word *next;
};

void menu(){
	Sleep(1000);
	printf("\n   ********************************************\n");
	printf("   *                                          *\n");
	printf("   *     ��s����ѯ����     ��c����ѯ��ʷ��¼  *\n");
	printf("   *     ��b�������ʱ�   ��p���༭���ʱ�    *\n");
	printf("   *     ��l��������       ��x��С����        *\n");
	printf("   *     ��e���༭�ʿ�     ��q���˳�          *\n");
	printf("   *                                          *\n");
	printf("   ********************************************\n");
}

void edit(int a){
	printf("��1����ӵ���   ��2���޸ĵ���   ��3��ɾ������\n");
	char Edit;
	scanf("%c", &Edit);
	fflush(stdin);
	
	while(1){
		if(Edit=='1'){
			addWord(a);
			break;
		}else if(Edit=='2'){
			editWord(a);
			break;
		}else if(Edit=='3'){
			delWord(a);
			break;
		}else{
			printf("��������ȷָ�\n"); 
			scanf("%c", &Edit);
			fflush(stdin);
		}	
	}		
} 

int main() {
	char input[50],regi;
	int temp=1;
	printf("��ӭʹ�õ��Ӵʵ䣡\n");
	while(temp==1){
		printf("��d����¼   ��z��ע��\n");
		scanf("%s", &regi);
		if(regi=='d'){
			load();
			temp=0;
		}else if(regi=='z'){
			regist();
			temp=0;
		}else{
			printf("��������ȷ��ָ�"); 
		}
	}
	menu();
	gets(input);
	while(strcmp(input, "q")!=0){
		if(strcmp(input, "s")==0){
			search();
			menu();
		}else if(strcmp(input, "c")==0){
			printf("����ʷ��¼��\n");
			output(hist);
			menu();
		}else if(strcmp(input, "b")==0){
			printf("�����ʱ���\n");
			output(diff);
			menu();
		}else if(strcmp(input, "e")==0){
			printf("���������Ա���룺");
			char secret[] = "fanruoxi";
			char inp[20];
			gets(inp);
			if(strcmp(secret,inp)==0){
				edit(1);
				menu();
			}else{
				printf("�������\n");
				menu();
			}
		}else if(strcmp(input, "p")==0){
			edit(2);
			menu();
		}else if(strcmp(input, "l")==0){
			study();
			menu();
		}else if(strcmp(input, "x")==0){
			test();
			menu();
		}else{
			printf("��������ȷ��ָ��\n"); 
		}
		gets(input);
	}
	if(strcmp(input, "q")==0){
		printf("лл����ʹ�ã�\n");
	}
	
	return 0;
}

void load(){
	int num;
	char cipher[20];
	fflush(stdin);
	char str[20];
	FILE *fp;
	int temp=0;
	int numtrue;//��ȷ�˺� 
	char ciphertrue[20];//��ȷ���� 
	while(temp==0){
		printf("�˺ţ�");
		scanf("%d", &num);
		fflush(stdin);
		printf("���룺");
		gets(cipher);
		itoa(num, str, 10);
		char str1[] = " ";
		strcat(str1, str);
		strcat(str1, ".dat");
		if((fp = fopen(str1,"r"))==NULL){/*���ڼ�¼�û���ѯ��¼����ͬ�û����ڲ�ͬ�ĵ�*/ 
			printf("���˺Ų����ڣ���ע�ᣡ\n");
			temp=1;
			regist();	
		}else{
			fp = fopen(str1,"r");
			fscanf(fp, "%d %s", &numtrue, &ciphertrue);
			fclose(fp);
			if(num==numtrue&&strcmp(cipher,ciphertrue)==0){
				temp=1;
				printf("��¼�ɹ���\n");
				char hit[10];//��¼history�ļ��� 
				itoa(num, hit, 10);
				strcat(hit," history.dat");
				char str2[] = " ";
				strcat(str2,hit);
				strcpy(hist,str2);
  				
				char dif[10];//��¼difficulty�ļ��� 
				itoa(num, dif, 10);			
				strcat(dif," difficulty.dat");				
				char str3[] = " ";		
				strcat(str3,dif);	
				strcpy(diff,str3);
				
				char stu[10];//��¼study�ļ��� 
				itoa(num, stu, 10);			
				strcat(stu," study.dat");				
				char str4[] = " ";	
				strcat(str4,stu);	
				strcpy(stud,str4);
			}else{
				printf("�����������������\n");
			}
		}
	}		
}

void history(int num){/*������ѯ��¼�ĵ�*/ 
	FILE *fp;
	char hit[10];
	itoa(num, hit, 10);
	strcat(hit," history.dat");
	char str2[] = " ";
	strcat(str2,hit);
	strcpy(hist,str2);
	if((fp = fopen(str2,"w+"))==NULL){/*���ڼ�¼�û���ѯ��¼����ͬ�û����ڲ�ͬ�ĵ�*/ 
		printf("Creat history fail!");
	}
	

}

void difficulty(int num1){/*�������ʱ��ĵ�*/ 
	FILE *dp;
	char dif[10];
	itoa(num1, dif, 10);
	strcat(dif," difficulty.dat");
	char str3[] = " ";	
	strcat(str3,dif);
	strcpy(diff,str3);
	if((dp = fopen(str3,"w+"))==NULL){/*���ڼ�¼�û���ѯ��¼����ͬ�û����ڲ�ͬ�ĵ�*/ 
		printf("Creat difficulty fail!");
	}
	fclose(dp);
}

void output(char name[50]){/*����ĵ��е�����*/ 
	struct word *head;
	head = creatOther(head, name);
	struct word *p;
	int temp = 0;
	p = head->next;
	while(p->next!=NULL){
		printf("%s %s\n", p->eng, p->chi);		
		p = p->next;
	}
}

void regist(){
	char cipher[20];
	fflush(stdin);
	int num;
	char name[20];
	printf("�����������˺ţ�10λ���֣���");
	scanf("%d", &num);
	itoa(num, name, 10);
	strcat(name, ".dat");
	char strr[] = " ";
	strcat(strr,name);
	FILE *p;
	while((p = fopen(strr,"r"))!=NULL){
		printf("���˺��Ѵ��ڣ����������룺");
		scanf("%d", &num);
		itoa(num, name, 10);
		strcat(name, ".dat");
		char strr[]=" ";
		strcat(strr,name);
		
	}
	fclose(p);
	fflush(stdin);
	printf("\n�������������루6λ������������֡���ĸ����"); 
	gets(cipher);

	FILE *fp;//�½��ı��ĵ� 
	char str[30];
	itoa(num, str, 10);
	strcat(str, ".dat");
	char str1[]=" ";
	strcat(str1,str);
	if((fp = fopen(str1,"w+"))==NULL){/*���ڼ�¼�û��˺�����*/ 
		printf("Creat file fail!");
	}
	fp = fopen(str1,"w+");
	fprintf(fp,"%d %s", num, cipher);//д���˺����룬��֤֮��ĵ�¼ 
	fclose(fp);
	
	history(num);
	difficulty(num);
	
	char stu[10];
	itoa(num, stu, 10);
	strcat(stu," study.dat");
	char str3[]=" ";	
	strcat(str3,stu);
	strcpy(stud,str3);
}	

struct word *creat(struct word *head){/*�����ʿ��е�����*/ 
	FILE *fp;
	if((fp = fopen("CET4.dat","r"))==NULL){ 
		printf("Cannot open CET4.dat file!\n");
	}

	struct word *p, *q;
	head = (struct word *)malloc(LEN);
	head->next = NULL;
	q = head;
	while(fgetc(fp)!=EOF){
		p = (struct word *)malloc(LEN);
		fscanf(fp,"%s", p->eng);
		fscanf(fp, "%s", p->chi);
		q->next = p;
		q = q->next;		
	}
	fclose(fp);
	p->next = NULL;
	return head;
}

struct word *creatOther(struct word *head, char name[50]){//���������ʿ��е����� 
	
	FILE *fp;
	if((fp = fopen(name,"r"))==NULL){ 
		printf("Cannot open other!\n");
	}
	struct word *p, *q;
	head = (struct word *)malloc(LEN);
	q = head;
	while(!feof(fp)){
		p = (struct word *)malloc(LEN);
		fscanf(fp,"%s %s", p->eng, p->chi);
		q->next = p;
		q = p;	
	}
	fclose(fp);
	p->next = NULL;
	return head;
	free(p);
	free(head);	
} 

void search(){
	
	struct word *head, *p;
	head = creat(head);
	p = head->next;
	
	FILE *fp;
	if((fp = fopen(hist,"a+"))==NULL){/*���ڼ�¼�û���ѯ��¼����ͬ�û����ڲ�ͬ�ĵ�*/ 
		printf("Open history fail!");
	}
	fp = fopen(hist,"a+");
	char scan[20];
	printf("��������Ҫ��ѯ�Ĵʣ�\n");
	gets(scan);
	int temp = 0;//�жϴʿ����Ƿ��������� 
	
	if((scan[0]>='a'&&scan[0]<='z')||(scan[0]>='A'&&scan[0]<='Z')){//�ж��û�����������Ļ���Ӣ�� 
		int len = strlen(scan);
		int i;
		for(i = 0;i<len;i++){
			if(scan[i]>='A'&&scan[i]<='Z') {
				scan[i] = scan[i]+32;
			}
		}	
		while(p!=NULL){
			if(strcmp(p->eng, scan)==0){
				printf("\n��ѯ�������%s %s��\n\n", p->eng, p->chi);
				temp=1;
				char a[70];
				int tem = 0;
				while(fgets(a,70,fp)){
					if(strstr(a,scan)!=NULL){
						tem = 1;
						break;
					}
				}
				strcpy(scan,p->eng);
				strcat(scan, " ");
				strcat(scan, p->chi);
				if(tem==0){
					fprintf(fp, "%s\n", scan);	
				}
			
				printf("�Ƿ񽫸ôʷ������ʱ���('y'/'n')\n");
				char in[10];
				gets(in);	
				if(strcmp(in, "y")==0){
					add(p->eng, p->chi);
				}
				break;		
			}else{
				p = p->next;
			}
		}
	}else{
		while(p!=NULL){
			if(strstr(p->chi, scan)!=NULL){
				printf("\n��ѯ�������%s %s��\n\n", p->eng, p->chi);
				temp=1;
				char a[70];
				int tem = 0;
				char eng[70];
				while(fgets(a,70,fp)){
					if(strstr(a,scan)!=NULL){
						tem = 1;
						break;
					}
				}
				strcpy(eng,p->eng);
				strcat(eng, " ");
				strcat(eng, p->chi);
				if(tem==0){
					fprintf(fp, "%s\n", eng);	
				} 
				printf("�Ƿ񽫸ôʷ������ʱ���('y'/'n')");
				char in[10];
				gets(in);
				if(strcmp(in, "y")==0){
					add(p->eng, p->chi);
				}
				break;			
			}else{
				p = p->next;
			}
		}
	}
	fclose(fp);
	
	if(temp==0){
		printf("�ʿ���û������ʣ�\n"); 
	}

}

void add(char inputeng[20], char inputchi[50]){//�������ʱ� 
	
	FILE *h;
	if((h = fopen(diff, "a+"))==NULL){
		printf("Open difficulty fail!");
	}
	char a[70];
	int tem = 0;
	char eng[20], chi[50];
	fscanf(h, "%s %s", eng,chi);
	while(!feof(h)){
		if(strcmp(eng, inputeng)==0){
			tem = 1;
		}
		fscanf(h, "%s %s", eng,chi);
	}	

	if(tem==0){
		fprintf(h, "%s %s\n", inputeng, inputchi);
		printf("��%s %s���Ѽ������ʱ���\n", inputeng, inputchi);
	}else{
		printf("���ʱ����Ѵ��ڡ�%s %s��\n", inputeng, inputchi);
	}
	fclose(h);
}

void addWord(int b){
	printf("��������Ҫ��ӵĵ��ʡ��������������壺\n");
	
	char ineng[20], inchi[50];
	scanf("%s %s", ineng, inchi);
	int len = strlen(ineng);
	int i;
	for(i = 0;i<len;i++){
		if(ineng[i]>='A'&&ineng[i]<='Z') {
			ineng[i] = ineng[i]+32;
		}
	}
	fflush(stdin);
	FILE *e;
	int temp = 0;//�жϵ����Ƿ��Ѵ��� 
	char eng[20], chi[50];
	if(b==1){
		e = fopen("CET4.dat","a+");
	}else{
		e = fopen(diff, "a+");
	}
	while(!feof(e)){	
		fscanf(e, "%s %s", eng,chi);
		if(strcmp(eng, ineng)==0){
			printf("�õ����Ѿ����ڣ�\n");
			temp = 1;
			break;
		}
	}	
	if(temp==0){
		fprintf(e,"%s %s\n",ineng, inchi);
		printf("�ɹ����%s %s��\n", ineng, inchi);
	}
	fclose(e);
} 

void editWord(int b){
	printf("��������Ҫ�޸ĵ�Ӣ�ĵ��ʣ�\n");
	
	char inputEng[20];
	gets(inputEng);
	int len = strlen(inputEng);
	int i;
	for(i = 0;i<len;i++){
		if(inputEng[i]>='A'&&inputEng[i]<='Z') {
			inputEng[i] = inputEng[i]+32;
		}
	}	
	int temp = 1;
	char eng[20], chi[50];
	char a[500];
	FILE *e, *w;
	if(b==1){
		e = fopen("CET4.dat","a+");//������ʱ�ĵ� 
		w = fopen("TEMP.dat","w+");
	}else{
		e = fopen(diff,"a+");
		w = fopen("TEMP.dat","w+");//��������ʱ�ĵ� 
	}
	fscanf(e, "%s %s", eng,chi);
	while(!feof(e)){
		if(strcmp(eng, inputEng)!=0){
			fprintf(w, "%s %s\n", eng, chi);
		}else{
			printf("�������޸ĺ�ĵ��ʼ��������壺\n");
			char after1[20], after2[50];
			scanf("%s %s", after1, after2);
			fflush(stdin);
			fprintf(w,"%s %s\n",after1, after2);
			temp = 0;
			temp=0; 
		}
		fscanf(e, "%s %s", eng,chi);
	}	
	
	fclose(e);
	fclose(w);
	if(temp==1){
		printf("û��%s�����!\n", inputEng);
		remove("TEMP.dat");
	}else{
		
		if(b==1){
			remove("CET4.dat");
			rename("TEMP.dat", "CET4.dat");		
		}else{
			remove(diff);
			rename("TEMP.dat", diff);
		}
		printf("�޸ĳɹ���\n");
	}		
}

void delWord (int b){
	printf("��������Ҫɾ����Ӣ�ĵ��ʣ�\n");
	char inputEng[20];
	scanf("%s", inputEng);
	fflush(stdin);
	
	int len = strlen(inputEng);
	int i;
	for(i = 0;i<len;i++){//����дת��ΪСд 
		if(inputEng[i]>='A'&&inputEng[i]<='Z') {
			inputEng[i] = inputEng[i]+32;
		}
	}	
	
	int temp = 1;	
	char a[500];
	FILE *e, *w;
	w = fopen("TEMP.dat","w+");
	
	if(b==1){
		e = fopen("CET4.dat","a+");
	}else{
		e = fopen(diff,"a+");
	}
	char eng[20], chi[50];
	fscanf(e, "%s %s", eng,chi);
	while(!feof(e)){
		if(strcmp(eng, inputEng)!=0){
			fprintf(w, "%s %s\n", eng, chi);
		}else{
			temp=0; 
		}
		fscanf(e, "%s %s", eng,chi);
	}		
	fclose(e);
	fclose(w);
	if(temp==1){
		printf("�ʿ���û��%s!\n", inputEng);
		remove("TEMP.dat");
	}else{
		if(b==1){
			remove("CET4.dat");
			rename("TEMP.dat", "CET4.dat");
		}else{
			remove(diff);
			rename("TEMP.dat", diff);
		}
		printf("ɾ���ɹ���\n");
	}	
}

void test(){

	struct word *head = NULL;
	head = creat(head);
	struct word *p;

	p = head->next;
	
	char english[20];
	int i = 0, temp = 0, num =0;
	int get;
	srand((int)time(NULL));
	int time;
	printf("������һ�������ĵ���������");
	scanf("%d", &time);
	fflush(stdin);
	for(;temp<time;temp++){		
		p = head->next;
		get = rand()%1000;
		for(; ;){
			if(i==get){
				i = 0;
				printf("\n%s\n", p->chi);
				printf("������ô����Ӧ��Ӣ�ģ�");
				gets(english);

				if(strcmp(english, p->eng)!=0){
					printf("����\n");
					printf("��ȷ��Ϊ����%s��\n", p->eng);
					num++;
					add(p->eng, p->chi);
				}else{
					printf("��ȷ��\n");
				}	
				break;
			}else{
				i++;
				p = p->next;
			}
		}
	}
	printf("\n��%d���⣬����%d��!,�������ͣ�\n", time, num);
}

void study(){
	FILE *fs;
	fs = fopen(stud, "w+");
	fclose(fs);
	
	int temp = 0, get, i = 0; 
	char in[10];
	
	struct word *head, *p;
	head = creat(head);
	srand((int)time(NULL));
	
	int time; 
	printf("������һ�鵥�ʵ�������");
	scanf("%d", &time);
	fflush(stdin);
	
	for(;temp<time;temp++){		
		p = head->next;
		get = rand()%1000;
		for(; ;){
			if(i==get){
				i = 0;
				printf("\n%s ��'y'��ʶ  'n'����ʶ��", p->eng);
				gets(in);
				while(1){	
					if(strcmp(in, "n")==0){
						addToStudy(p->eng, p->chi);//����ʶ��ת��һ���µ��ĵ� 
						break; 
					}else if(strcmp(in, "y")==0){
						break;
					}else{
						printf("��������ȷָ�\n");
						gets(in);
					}
				} 
				printf("��%s %s��\n", p->eng, p->chi);
				break;
			}else{
				i++;
				p = p->next;
			}
		}
	}
	
	struct word *q, *t;
	
	FILE *w, *fw;
	fw = fopen(stud, "a+");
	
	while(fgetc(fw)!=EOF){//ѭ�����������ʶ���ĵ���ֱ��ȫ����ʶ 
		fclose(fw);
		fw = fopen(stud, "a+");	
		q = creatOther(q, stud);
		t = q->next;
		while(t->next!=NULL){
			printf("\n%s ��'y'��ʶ  'n'����ʶ��", t->eng);
			gets(in);
			if(strcmp(in, "y")==0){
				printf("��%s %s��\n", t->eng, t->chi);	
				char a[500];
				w = fopen("TEMP.dat","w+");			
				while(fgets(a,500,fw)){
					if(strstr(a,t->eng)==NULL){
						fputs(a,w);
					}
				}	
				fclose(fw);
				fclose(w);
				remove(stud);
				rename("TEMP.dat", stud);	
			}else{
				fclose(fw);
				printf("��%s %s��\n", t->eng, t->chi);	
			}
			t = t->next;
		}
		fw = fopen(stud, "a+");	
	}
}

void addToStudy(char eng[20], char chi[50]){//���롮�����ʡ��ĵ� 
	FILE *h;
	if((h = fopen(stud, "a+"))==NULL){
		printf("Open study fail!");
	}
	fprintf(h, "%s %s\n", eng, chi);
	fclose(h);
}

