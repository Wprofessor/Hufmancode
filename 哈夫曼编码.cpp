#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#define MAXSIZE 515
#define ASCLLNUM 256

int num[ASCLLNUM][ASCLLNUM];  
char **hastb = (char **)malloc(ASCLLNUM * sizeof(char*));
typedef struct node {
	int data;//���Ƶ��
	unsigned char c;//����ַ�
	struct node *lchild,*rchild;//�������������Һ���ָ��
	struct node *next;//���������Ľ��ͬʱ���ǵ�����Ľ�㣬nextΪ������Ľ��ָ��
} BSTree; //��������������������

typedef struct ascll{
	int count;//���Ÿ���
	unsigned  char sign;//����
}Ascll;
void show(){
	printf("                   ��������������                  \n\n");
	printf("���ܣ�\n");
	printf("     1.�ַ�Ƶ�ʵ��������\n");
	printf("     2.����������ǰ�����\n");
	printf("     3.�����������������\n");
	printf("     4.���������ĺ������\n");
	printf("     5.������������ı���\n");
	printf("     6.ѹ����ͷ�ļ���\n");
	printf("     7.��ѹ��\n");
	printf("     8.�˳�����\n");
	printf("ע�⣺ʹ�ñ�����ʹ����������·��\n\n");
	printf("��ѡ�������"); 
	 
	
} 
//����������ַ�������໥ת�� 
void Changing(int *i, char *c, int len)
{//iΪ�������飬cΪҪ����ַ��������飬lenΪ��������Ԫ�ظ���
    int k;
    char tmp[10];
    
    for(k=0;k<len;k++)
    {
    	itoa(i[k],tmp,10);
    	if(k==0){
    		strcpy(c,tmp);
		}else{
//			printf("����%s",tmp); 
        	strcat(c,tmp);
		}
         
    }
    
}
BSTree *CreateLinkList(Ascll ascll[],int val) { //����Ҷ�ӽ���Ȩֵ����һ����������
	BSTree *link,*p,*q,*s;
	int j;
	link=(BSTree*)malloc(sizeof(BSTree));//���ɵ������ͷ���
	s=(BSTree*)malloc(sizeof(BSTree));//���ɵ�����ĵ�һ�����ݽ�㣬ͬʱҲ�ǹ���������Ҷ���
	int ok;
	for(int i=0;i<ASCLLNUM;i++){
		if(ascll[i].count>0){
			s->data=ascll[i].count;
			s->c=ascll[i].sign;
			ok=i;
			break;
		}
	}
	//scanf("%d",&s->data);//����Ҷ�ӽ���Ȩֵ
	s->lchild=NULL;
	s->rchild=NULL;//�����Һ���ָ��Ϊ�յ�Ҷ����־
	s->next=NULL;//�õ�������β����־
	link->next=s;
	for(j=2; j<=  val; j++) { //���ɵ�����ʣ���val-1�����ݽ��
		s=(BSTree*)malloc(sizeof(BSTree));//����һ�����ݽ��
		for(int i=0;i<ASCLLNUM;i++){
			if(ascll[i].count>0&&i>ok){
				s->data=ascll[i].count;
				s->c=ascll[i].sign;
				ok=i;
				break;
			}
		}
		//scanf("%d",&s->data);//����Ҷ�ӽ���Ȩֵ
		s->lchild=NULL;
		s->rchild=NULL;//�����Һ���ָ��Ϊ�յ�Ҷ����־
		q=link;//�������ݽ�㰴������뵽��������
		p=q->next;
		while(p!=NULL)
			if(s->data>p->data) { //���Ҳ���λ��
				q=p;
				p=p->next;
			} else { //�ҵ�����λ�ú���в���
				q->next=s;
				s->next=p;
				break;
			}
		if(s->data>q->data) { //���뵽��β�Ĵ���
			q->next=s;
			s->next=p;
		}
	}
	return link;//�������������ͷָ����
}

void print(BSTree *h) { //���������
	BSTree *p;
	p=h->next;
	while(p!=NULL) {
		printf("%d,",p->data);
		p=p->next;
	}
	printf("\n");
}

BSTree *HuffTree(BSTree *link) { //���ɹ�������
	BSTree *p,*q,*s;
	while(link->next!=NULL) { //������������ݽ��ǿ�ʱ
		p=link->next;//ȡ�����������еĵ�һ�����ݽ��
		q=p->next;//ȡ�����������еĵڶ������ݽ��
		link->next=q->next;//ʹͷ����ָ��ָ������ĵ��������ݽ��
		s=(BSTree*)malloc(sizeof(BSTree));//���ɹ�����������֦���
		s->data=p->data+q->data;//����֦����ȨֵΪȡ���Ķ������ݽ��Ȩֵ֮��
		s->lchild=p;//ȡ���ĵ�һ�����ݽ����Ϊ����֦��������
		s->rchild=q;//ȡ���ĵڶ������ݽ����Ϊ����֦�����Һ���
		q=link;//������֦��㰴������뵽��������
		p=q->next;
		while(p!=NULL)
			if(s->data>p->data) {
				q=p;
				p=p->next;
			} else {
				q->next=s;
				s->next=p;
				break;
			}
		if(q!=link&&s->data>q->data) { //���뵽��β�Ĵ������q����link������Ϊ�գ���ʱ*s��Ϊ�����
			q->next=s;
			s->next=p;
		}
	}
	return s;//��������Ϊ��ʱ��������ɵ���֦��㼴Ϊ���������ĸ��ڵ�
}
//�������ֵ 
void display(BSTree *elem){
	printf("%d ",elem->data);
}
//ǰ�����
void  Preordertraversal(BSTree *q){
	if(q){
	display(q);
	Preordertraversal(q->lchild);
	Preordertraversal(q->rchild);
	}
}
//�������
void Inordertraversal(BSTree *q){
	if(q){
	Inordertraversal(q->lchild);
	display(q);
	Inordertraversal(q->rchild);
	}
} 
//�������
void Postordertraversal(BSTree *q){
	if(q){
		Postordertraversal(q->lchild);
		Postordertraversal(q->rchild);
		display(q);
	}
} 
void HuffCode(BSTree *p,Ascll ascll[],bool panduan) { //��������������������������������
	BSTree *stack[MAXSIZE],*q;
	int b,i=-1,j=0,k;
	int code[MAXSIZE];
	int t = 0;
	for (i = 0; i < ASCLLNUM; i++)
	{
		hastb[i] = NULL;
	}
	do { //�������������
	int count = 0 ;
	//C:\Users\������\Desktop\test2.txt
		while(p!=NULL) { //��*p������֧�ϵ�������ջ
		
			if(p->lchild==NULL&&p->rchild==NULL) {
				hastb[(int)p->c] =(char *)malloc(10);
				if(panduan){
				printf("Ҷ�ӽ��%cƵ��=%d,����:",p->c,p->data);//���Ҷ�ӽ����Ϣ
				//�����Ҷ���Ĺ���������
				for(k=0;k<j;k++){
					printf("%d",code[k]);
				}
				cout<<endl;
				}
//				printf("\n");
				Changing(code,hastb[(int)p->c],j);
//				change[j]='\0';
//				hastb[(int)p->c]=change;
//				printf(" %s",hastb[(int)p->c]);
//				printf("\n");
				j--;
			}
			stack[++i]=p;//ָ��ǰ����ָ��p��ջ
			p=p->lchild;//pָ��*p������
			code[j++]=0;//��Ӧ�����֧�ñ���0
			
		}
	
		//ջ�������û�����ӻ����������ϵĽ�㶼�ѷ��ʹ�
		q=NULL;
		b=1;//���ѷ��ʹ��ı��
		while(i>=0&&b) { //ջstack�����ҵ�ǰջ�������������Ѿ�������
			p=stack[i];//ȡ����ǰջ���洢�Ľ��ָ��
			if(p->rchild==q) { //��ǰջ�����*p���Һ��ӻ�*p���Һ����ѷ��ʹ�
				i--;
				j--;
				q=p;//qָ��շ��ʹ��Ľ��*p
			} else { //��ǰջ�����*p��������
				p=p->rchild;//pָ��ǰջ�����*p���Һ��ӽ��
				code[j++]=1;//��Ӧ���ҷ�֧�ñ���1
				b=0;//���Һ��ӽ��δ�����������������
			}
		}
	} while(i>=0);//��ջstack�ǿ�ʱ��������
}

void compress(char x){
	FILE *infile,
		*outfile;
	//��ʼ��
//	for(int i=0;i<ASCLLNUM;i++){
//		hastb[i]=new char[MAXSIZE];
//	}
	char intfName[MAXSIZE],outfName[MAXSIZE];
	printf("�������ļ�·����\n");
	cin>>intfName;
	infile=fopen(intfName,"rb");
	while(infile==NULL){
		printf("��������ļ�����򲻴���\n");
		printf("��������Ҫ��ȡ���ļ���1  �������˵���2\n");
		char ob;
		cin>>ob;
		while(ob!='1'&&ob!='2'){
			cout<<"����������������������"<<endl;
			cout<<"��������Ҫ��ȡ���ļ���1  �������˵���2"<<endl;
			cin>>ob;
		}
		if(ob=='2'){
			return;
		}
		else{
		cout<<"�������ļ�·��:"<<endl;
	    cin>>intfName;
		infile=fopen(intfName,"rb");
		}
	}
	strcpy(outfName,intfName);
	strcat(outfName,".txt");
	outfile=fopen(outfName,"wb");
	Ascll ascll[ASCLLNUM];
	unsigned char c;
	int total=0; //�ַ��ܳ���
	int val=0; //�ַ�������
	for(int i=0;i<ASCLLNUM;i++){
		ascll[i].count=0;
	}
	while(!feof(infile)){//��ȡ�ļ��е������Ϣ
		c=fgetc(infile);
		ascll[c].sign=c;
		ascll[c].count++;
		total++;
	}
	total--;
	for(int i=0;i<ASCLLNUM;i++){
		if(ascll[i].count>0){
			val++;
		}
	}
	BSTree *q;
	q=CreateLinkList(ascll,val);
	
	if(x=='1'){
		print(q);
		
	}
	q=HuffTree(q);
	if(x=='2'){
		Preordertraversal(q);
		cout<<endl;
	}
	if(x=='3'){
		Inordertraversal(q);
		cout<<endl;
	}
	if(x=='4'){
		Postordertraversal(q);
		cout<<endl;
	}
	if(x=='5'){
		HuffCode(q,ascll,true);
	}
	if(x=='6'){
		//ѹ��ͷ�ļ�
	outfile=fopen(outfName,"wb");
	fprintf(outfile,"%d",total);
	for(int i=0;i<ASCLLNUM;i++){
		fprintf(outfile,"%d",ascll[i].count);
	}
	}
	if(x=='7'){
		printf("��ȴ��´θ��£�лл\n");
	}
	if(x=='8'){
		printf("ллʹ�ã���Ҫ���Ƕ���Ŷ��\n");
		return;
	}
	
	
//	printf("%s\n\n",hastb['h']);
	
//	for(int i=0;i<ASCLLNUM;i++) {
//		if(ascll[i].count > 0)
//			printf("%s\n",hastb[i]);
//	}
//	fclose(infile);
//	fclose(outfile);
	
	//ѹ�����ļ�
	fseek(infile,0,0);//��ͷ��ʼ��
	while(!feof(infile)){
		c=fgetc(infile);
	} 
	fclose(infile);
	fclose(outfile);
}
int main() {
	int value=0;
	while(1){
	value++;
	if(value==1){
    show(); 
	}
	else{
		cout<<"��ѡ�����"<<endl;
	}
    char obtion;
    cin>>obtion;
    while(obtion!='1'&&obtion!='2'&&obtion!='3'&&obtion!='4'&&obtion!='5'&&obtion!='6'&&obtion!='7'&&obtion!='8'){
    	printf("��Ч������please��������:\n");
    	cin>>obtion;
	}
	switch(obtion){
		case '1':
			compress('1');
			break;
		case '2':
			compress('2');
			break;	
		case '3':
			compress('3');
			break;	
		case '4':
			compress('4');
			break;	
		case '5':
			compress('5');
			break;
		case '6':
			compress('6');
			break;	
		case '7':
			compress('7');
			break;	
		case '8':
			compress('8');
			return 0;	
	}
	
	
}
}

//C:\Users\������\Desktop\test2.txt
