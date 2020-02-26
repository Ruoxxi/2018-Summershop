#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define LEN sizeof(struct word)

struct word *creat(struct word *head);//创建词库 
struct word *creatOther(struct word *head, char name[50]);//创建查询记录、生词本链表 
void search();//查找单词 
void regist();//注册 
void load();//登录 
void history(int num);//创建历史记录文档 
void difficulty(int num1);//创建生词本文档 
void output(char name[50]); //输出生词本、历史记录 
void menu();//菜单栏 
void add(char eng[20], char chi[50]);//添加入生词本 
void addWord(int b);//增加词单词 
void editWord(int b);//修改单词 
void delWord(int b);//删除单词 
void edit(int a);//编辑功能 
void study();//背单词
void addToStudy(char eng[20], char chi[50]);
void test();//小测试 

static char hist[50];//定义历史记录文件名 
static char diff[50];//定义生词本文件名 
static char stud[50];//定义背单词文件名 

struct word{
	char chi[50];
	char eng[20];
	struct word *next;
};

void menu(){
	Sleep(1000);
	printf("\n   ********************************************\n");
	printf("   *                                          *\n");
	printf("   *     【s】查询单词     【c】查询历史记录  *\n");
	printf("   *     【b】打开生词本   【p】编辑生词本    *\n");
	printf("   *     【l】背单词       【x】小测试        *\n");
	printf("   *     【e】编辑词库     【q】退出          *\n");
	printf("   *                                          *\n");
	printf("   ********************************************\n");
}

void edit(int a){
	printf("【1】添加单词   【2】修改单词   【3】删除单词\n");
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
			printf("请输入正确指令！\n"); 
			scanf("%c", &Edit);
			fflush(stdin);
		}	
	}		
} 

int main() {
	char input[50],regi;
	int temp=1;
	printf("欢迎使用电子词典！\n");
	while(temp==1){
		printf("【d】登录   【z】注册\n");
		scanf("%s", &regi);
		if(regi=='d'){
			load();
			temp=0;
		}else if(regi=='z'){
			regist();
			temp=0;
		}else{
			printf("请输入正确的指令！"); 
		}
	}
	menu();
	gets(input);
	while(strcmp(input, "q")!=0){
		if(strcmp(input, "s")==0){
			search();
			menu();
		}else if(strcmp(input, "c")==0){
			printf("【历史记录】\n");
			output(hist);
			menu();
		}else if(strcmp(input, "b")==0){
			printf("【生词本】\n");
			output(diff);
			menu();
		}else if(strcmp(input, "e")==0){
			printf("请输入管理员密码：");
			char secret[] = "fanruoxi";
			char inp[20];
			gets(inp);
			if(strcmp(secret,inp)==0){
				edit(1);
				menu();
			}else{
				printf("密码错误！\n");
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
			printf("请输入正确的指令\n"); 
		}
		gets(input);
	}
	if(strcmp(input, "q")==0){
		printf("谢谢您的使用！\n");
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
	int numtrue;//正确账号 
	char ciphertrue[20];//正确密码 
	while(temp==0){
		printf("账号：");
		scanf("%d", &num);
		fflush(stdin);
		printf("密码：");
		gets(cipher);
		itoa(num, str, 10);
		char str1[] = " ";
		strcat(str1, str);
		strcat(str1, ".dat");
		if((fp = fopen(str1,"r"))==NULL){/*用于记录用户查询记录，不同用户存于不同文档*/ 
			printf("该账号不存在，请注册！\n");
			temp=1;
			regist();	
		}else{
			fp = fopen(str1,"r");
			fscanf(fp, "%d %s", &numtrue, &ciphertrue);
			fclose(fp);
			if(num==numtrue&&strcmp(cipher,ciphertrue)==0){
				temp=1;
				printf("登录成功！\n");
				char hit[10];//记录history文件名 
				itoa(num, hit, 10);
				strcat(hit," history.dat");
				char str2[] = " ";
				strcat(str2,hit);
				strcpy(hist,str2);
  				
				char dif[10];//记录difficulty文件名 
				itoa(num, dif, 10);			
				strcat(dif," difficulty.dat");				
				char str3[] = " ";		
				strcat(str3,dif);	
				strcpy(diff,str3);
				
				char stu[10];//记录study文件名 
				itoa(num, stu, 10);			
				strcat(stu," study.dat");				
				char str4[] = " ";	
				strcat(str4,stu);	
				strcpy(stud,str4);
			}else{
				printf("密码错误！请重新输入\n");
			}
		}
	}		
}

void history(int num){/*创建查询记录文档*/ 
	FILE *fp;
	char hit[10];
	itoa(num, hit, 10);
	strcat(hit," history.dat");
	char str2[] = " ";
	strcat(str2,hit);
	strcpy(hist,str2);
	if((fp = fopen(str2,"w+"))==NULL){/*用于记录用户查询记录，不同用户存于不同文档*/ 
		printf("Creat history fail!");
	}
	

}

void difficulty(int num1){/*创建生词本文档*/ 
	FILE *dp;
	char dif[10];
	itoa(num1, dif, 10);
	strcat(dif," difficulty.dat");
	char str3[] = " ";	
	strcat(str3,dif);
	strcpy(diff,str3);
	if((dp = fopen(str3,"w+"))==NULL){/*用于记录用户查询记录，不同用户存于不同文档*/ 
		printf("Creat difficulty fail!");
	}
	fclose(dp);
}

void output(char name[50]){/*输出文档中的内容*/ 
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
	printf("请设置您的账号（10位数字）：");
	scanf("%d", &num);
	itoa(num, name, 10);
	strcat(name, ".dat");
	char strr[] = " ";
	strcat(strr,name);
	FILE *p;
	while((p = fopen(strr,"r"))!=NULL){
		printf("该账号已存在，请重新输入：");
		scanf("%d", &num);
		itoa(num, name, 10);
		strcat(name, ".dat");
		char strr[]=" ";
		strcat(strr,name);
		
	}
	fclose(p);
	fflush(stdin);
	printf("\n请设置您的密码（6位以上需包含数字、字母）："); 
	gets(cipher);

	FILE *fp;//新建文本文档 
	char str[30];
	itoa(num, str, 10);
	strcat(str, ".dat");
	char str1[]=" ";
	strcat(str1,str);
	if((fp = fopen(str1,"w+"))==NULL){/*用于记录用户账号密码*/ 
		printf("Creat file fail!");
	}
	fp = fopen(str1,"w+");
	fprintf(fp,"%d %s", num, cipher);//写入账号密码，验证之后的登录 
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

struct word *creat(struct word *head){/*创建词库中的链表*/ 
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

struct word *creatOther(struct word *head, char name[50]){//创建其他词库中的链表 
	
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
	if((fp = fopen(hist,"a+"))==NULL){/*用于记录用户查询记录，不同用户存于不同文档*/ 
		printf("Open history fail!");
	}
	fp = fopen(hist,"a+");
	char scan[20];
	printf("请输入您要查询的词：\n");
	gets(scan);
	int temp = 0;//判断词库中是否存在这个词 
	
	if((scan[0]>='a'&&scan[0]<='z')||(scan[0]>='A'&&scan[0]<='Z')){//判断用户输入的是中文还是英文 
		int len = strlen(scan);
		int i;
		for(i = 0;i<len;i++){
			if(scan[i]>='A'&&scan[i]<='Z') {
				scan[i] = scan[i]+32;
			}
		}	
		while(p!=NULL){
			if(strcmp(p->eng, scan)==0){
				printf("\n查询结果：【%s %s】\n\n", p->eng, p->chi);
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
			
				printf("是否将该词放入生词本？('y'/'n')\n");
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
				printf("\n查询结果：【%s %s】\n\n", p->eng, p->chi);
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
				printf("是否将该词放入生词本？('y'/'n')");
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
		printf("词库中没有这个词！\n"); 
	}

}

void add(char inputeng[20], char inputchi[50]){//加入生词本 
	
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
		printf("【%s %s】已加入生词本！\n", inputeng, inputchi);
	}else{
		printf("生词本中已存在【%s %s】\n", inputeng, inputchi);
	}
	fclose(h);
}

void addWord(int b){
	printf("请输入您要添加的单词、词性与中文释义：\n");
	
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
	int temp = 0;//判断单词是否已存在 
	char eng[20], chi[50];
	if(b==1){
		e = fopen("CET4.dat","a+");
	}else{
		e = fopen(diff, "a+");
	}
	while(!feof(e)){	
		fscanf(e, "%s %s", eng,chi);
		if(strcmp(eng, ineng)==0){
			printf("该单词已经存在！\n");
			temp = 1;
			break;
		}
	}	
	if(temp==0){
		fprintf(e,"%s %s\n",ineng, inchi);
		printf("成功添加%s %s！\n", ineng, inchi);
	}
	fclose(e);
} 

void editWord(int b){
	printf("请输入您要修改的英文单词：\n");
	
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
		e = fopen("CET4.dat","a+");//创建临时文档 
		w = fopen("TEMP.dat","w+");
	}else{
		e = fopen(diff,"a+");
		w = fopen("TEMP.dat","w+");//重命名临时文档 
	}
	fscanf(e, "%s %s", eng,chi);
	while(!feof(e)){
		if(strcmp(eng, inputEng)!=0){
			fprintf(w, "%s %s\n", eng, chi);
		}else{
			printf("请输入修改后的单词及中文释义：\n");
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
		printf("没有%s这个词!\n", inputEng);
		remove("TEMP.dat");
	}else{
		
		if(b==1){
			remove("CET4.dat");
			rename("TEMP.dat", "CET4.dat");		
		}else{
			remove(diff);
			rename("TEMP.dat", diff);
		}
		printf("修改成功！\n");
	}		
}

void delWord (int b){
	printf("请输入您要删除的英文单词：\n");
	char inputEng[20];
	scanf("%s", inputEng);
	fflush(stdin);
	
	int len = strlen(inputEng);
	int i;
	for(i = 0;i<len;i++){//将大写转换为小写 
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
		printf("词库中没有%s!\n", inputEng);
		remove("TEMP.dat");
	}else{
		if(b==1){
			remove("CET4.dat");
			rename("TEMP.dat", "CET4.dat");
		}else{
			remove(diff);
			rename("TEMP.dat", diff);
		}
		printf("删除成功！\n");
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
	printf("请输入一组测试题的单词数量：");
	scanf("%d", &time);
	fflush(stdin);
	for(;temp<time;temp++){		
		p = head->next;
		get = rand()%1000;
		for(; ;){
			if(i==get){
				i = 0;
				printf("\n%s\n", p->chi);
				printf("请输入该词语对应的英文：");
				gets(english);

				if(strcmp(english, p->eng)!=0){
					printf("错误！\n");
					printf("正确答案为：【%s】\n", p->eng);
					num++;
					add(p->eng, p->chi);
				}else{
					printf("正确！\n");
				}	
				break;
			}else{
				i++;
				p = p->next;
			}
		}
	}
	printf("\n共%d道题，错误%d题!,继续加油！\n", time, num);
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
	printf("请输入一组单词的数量：");
	scanf("%d", &time);
	fflush(stdin);
	
	for(;temp<time;temp++){		
		p = head->next;
		get = rand()%1000;
		for(; ;){
			if(i==get){
				i = 0;
				printf("\n%s （'y'认识  'n'不认识）", p->eng);
				gets(in);
				while(1){	
					if(strcmp(in, "n")==0){
						addToStudy(p->eng, p->chi);//不认识的转到一个新的文档 
						break; 
					}else if(strcmp(in, "y")==0){
						break;
					}else{
						printf("请输入正确指令：\n");
						gets(in);
					}
				} 
				printf("【%s %s】\n", p->eng, p->chi);
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
	
	while(fgetc(fw)!=EOF){//循环输出“不认识”的单词直到全部认识 
		fclose(fw);
		fw = fopen(stud, "a+");	
		q = creatOther(q, stud);
		t = q->next;
		while(t->next!=NULL){
			printf("\n%s （'y'认识  'n'不认识）", t->eng);
			gets(in);
			if(strcmp(in, "y")==0){
				printf("【%s %s】\n", t->eng, t->chi);	
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
				printf("【%s %s】\n", t->eng, t->chi);	
			}
			t = t->next;
		}
		fw = fopen(stud, "a+");	
	}
}

void addToStudy(char eng[20], char chi[50]){//加入‘背单词’文档 
	FILE *h;
	if((h = fopen(stud, "a+"))==NULL){
		printf("Open study fail!");
	}
	fprintf(h, "%s %s\n", eng, chi);
	fclose(h);
}

