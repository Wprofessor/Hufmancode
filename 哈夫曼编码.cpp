#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 515
#define ASCLLNUM 256
char *hastb[ASCLLNUM] ;
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
//����������ַ�������໥ת�� 
void Changing(int *i, char *c, int len)
{//iΪ�������飬cΪҪ����ַ��������飬lenΪ��������Ԫ�ظ���
    int k;
    char tmp[10];
    for(k=0;k<len;k++)
    {
        itoa(i[k],tmp,10);
        strcat(c,tmp);
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
	for(j=2; j<=val; j++) { //���ɵ�����ʣ���total-1�����ݽ��
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

void HuffCode(BSTree *p,char* hastb[ASCLLNUM]) { //��������������������������������
	BSTree *stack[MAXSIZE],*q;
	int b,i=-1,j=0,k;
	int code[MAXSIZE];
	do { //�������������
		while(p!=NULL) { //��*p������֧�ϵ�������ջ
			if(p->lchild==NULL&&p->rchild==NULL) {
				printf("Ҷ�ӽ��%cƵ��=%d,����:",p->c,p->data);//���Ҷ�ӽ����Ϣ
				//�����Ҷ���Ĺ���������
				char change[MAXSIZE]="";
				
				for(k=0;k<j;k++){
					printf("%d",code[k]);
				}
				Changing(code,change,j);
				change[j]='\0';
				hastb[p->c]=change;
				printf(" %s",hastb[p->c]);
				printf("\n");
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

void compress(){
	FILE *infile,
		*outfile;
	//��ʼ��
	for(int i=0;i<ASCLLNUM;i++){
		hastb[i]=new char[MAXSIZE];
	}
	char intfName[MAXSIZE],outfName[MAXSIZE];
	printf("�������ļ�·����\n");
	scanf("%s",intfName);
	infile=fopen(intfName,"rb");
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
			printf("���ţ�%c Ƶ����%d\n",ascll[i].sign,ascll[i].count);
		}
	}
	BSTree *q;
	q=CreateLinkList(ascll,val);
	print(q);
	q=HuffTree(q);
	HuffCode(q,hastb);
	fclose(infile);
	fclose(outfile);
	//ѹ��ͷ�ļ�
	outfile=fopen(outfName,"wb");
	fprintf(outfile,"%d",total);
	for(int i=0;i<ASCLLNUM;i++){
		fprintf(outfile,"%d",ascll[i].count);
	}
	//ѹ�����ļ�
	fseek(infile,0,0);//��ͷ��ʼ��
	while(!feof(infile)){
		c=fgetc(infile);
	} 
}
int main() {
	/*BSTree *root;
	int n;

	while(printf("����Ҷ�ӽ��ĸ���\n")&&scanf("%d",&n)!=EOF){  //��������
	printf("����n��Ҷ�ӽ���Ȩֵ:\n");
	root=CreateLinkList(n);//����һ����������
	printf("��������ɵ���������:\n");
	print(root);
	root=HuffTree(root);//���ɹ�������
	printf("������������������첢�������������:\n");
	HuffCode(root);
	}*/
	compress();
	return 0;
}
