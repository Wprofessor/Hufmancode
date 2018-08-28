#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 515
#define ASCLLNUM 256
char *hastb[ASCLLNUM] ;
typedef struct node {
	int data;//结点频率
	unsigned char c;//结点字符
	struct node *lchild,*rchild;//哈夫曼树的左右孩子指针
	struct node *next;//哈夫曼树的结点同时又是单链表的结点，next为单链表的结点指针
} BSTree; //二叉树及单链表结点类型

typedef struct ascll{
	int count;//符号个数
	unsigned  char sign;//符号
}Ascll;
//整形数组和字符数组的相互转换 
void Changing(int *i, char *c, int len)
{//i为整形数组，c为要存放字符串的数组，len为整形数组元素个数
    int k;
    char tmp[10];
    for(k=0;k<len;k++)
    {
        itoa(i[k],tmp,10);
        strcat(c,tmp);
    }
}
BSTree *CreateLinkList(Ascll ascll[],int val) { //根据叶子结点的权值生成一个升序单链表
	BSTree *link,*p,*q,*s;
	int j;
	link=(BSTree*)malloc(sizeof(BSTree));//生成单链表的头结点
	s=(BSTree*)malloc(sizeof(BSTree));//生成单链表的第一个数据结点，同时也是哈夫曼树的叶结点
	int ok;
	for(int i=0;i<ASCLLNUM;i++){
		if(ascll[i].count>0){
			s->data=ascll[i].count;
			s->c=ascll[i].sign;
			ok=i;
			break;
		}
	}
	//scanf("%d",&s->data);//输入叶子结点的权值
	s->lchild=NULL;
	s->rchild=NULL;//置左、右孩子指针为空的叶结点标志
	s->next=NULL;//置单链表链尾结点标志
	link->next=s;
	for(j=2; j<=val; j++) { //生成单链表剩余的total-1个数据结点
		s=(BSTree*)malloc(sizeof(BSTree));//生成一个数据结点
		for(int i=0;i<ASCLLNUM;i++){
			if(ascll[i].count>0&&i>ok){
				s->data=ascll[i].count;
				s->c=ascll[i].sign;
				ok=i;
				break;
			}
		}
		//scanf("%d",&s->data);//输入叶子结点的权值
		s->lchild=NULL;
		s->rchild=NULL;//置左右孩子指针为空的叶结点标志
		q=link;//将该数据结点按升序插入到单链表中
		p=q->next;
		while(p!=NULL)
			if(s->data>p->data) { //查找插入位置
				q=p;
				p=p->next;
			} else { //找到插入位置后进行插入
				q->next=s;
				s->next=p;
				break;
			}
		if(s->data>q->data) { //插入到链尾的处理
			q->next=s;
			s->next=p;
		}
	}
	return link;//返回升序单链表的头指针结点
}

void print(BSTree *h) { //输出单链表
	BSTree *p;
	p=h->next;
	while(p!=NULL) {
		printf("%d,",p->data);
		p=p->next;
	}
	printf("\n");
}

BSTree *HuffTree(BSTree *link) { //生成哈夫曼树
	BSTree *p,*q,*s;
	while(link->next!=NULL) { //当单链表的数据结点非空时
		p=link->next;//取出升序链表中的第一个数据结点
		q=p->next;//取出升序链表中的第二个数据结点
		link->next=q->next;//使头结点的指针指向单链表的第三个数据结点
		s=(BSTree*)malloc(sizeof(BSTree));//生成哈夫曼树的树枝结点
		s->data=p->data+q->data;//该树枝结点的权值为取出的二个数据结点权值之和
		s->lchild=p;//取出的第一个数据结点作为该树枝结点的左孩子
		s->rchild=q;//取出的第二个数据结点作为该树枝结点的右孩子
		q=link;//将该树枝结点按升序插入到单链表中
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
		if(q!=link&&s->data>q->data) { //插入到链尾的处理，如果q等于link则链表为空，此时*s即为根结点
			q->next=s;
			s->next=p;
		}
	}
	return s;//当单链表为空时，最后生成的树枝结点即为哈夫曼树的根节点
}

void HuffCode(BSTree *p,char* hastb[ASCLLNUM]) { //后序遍历哈夫曼树并输出哈夫曼树编码
	BSTree *stack[MAXSIZE],*q;
	int b,i=-1,j=0,k;
	int code[MAXSIZE];
	do { //后序遍历二叉树
		while(p!=NULL) { //将*p结点左分支上的左孩子入栈
			if(p->lchild==NULL&&p->rchild==NULL) {
				printf("叶子结点%c频率=%d,编码:",p->c,p->data);//输出叶子结点信息
				//输出该叶结点的哈夫曼编码
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
			stack[++i]=p;//指向当前结点的指针p入栈
			p=p->lchild;//p指向*p的左孩子
			code[j++]=0;//对应的左分支置编码0
		}
		//栈顶结点已没有左孩子或其左子树上的结点都已访问过
		q=NULL;
		b=1;//置已访问过的标记
		while(i>=0&&b) { //栈stack不空且当前栈顶结点的左子树已经遍历过
			p=stack[i];//取出当前栈顶存储的结点指针
			if(p->rchild==q) { //当前栈顶结点*p无右孩子或*p的右孩子已访问过
				i--;
				j--;
				q=p;//q指向刚访问过的结点*p
			} else { //当前栈顶结点*p有右子树
				p=p->rchild;//p指向当前栈顶结点*p的右孩子结点
				code[j++]=1;//对应的右分支置编码1
				b=0;//置右孩子结点未遍历过其右子树标记
			}
		}
	} while(i>=0);//当栈stack非空时继续遍历
}

void compress(){
	FILE *infile,
		*outfile;
	//初始化
	for(int i=0;i<ASCLLNUM;i++){
		hastb[i]=new char[MAXSIZE];
	}
	char intfName[MAXSIZE],outfName[MAXSIZE];
	printf("请输入文件路径：\n");
	scanf("%s",intfName);
	infile=fopen(intfName,"rb");
	strcpy(outfName,intfName);
	strcat(outfName,".txt");
	outfile=fopen(outfName,"wb");
	Ascll ascll[ASCLLNUM];
	unsigned char c;
	int total=0; //字符总长度
	int val=0; //字符种类数
	for(int i=0;i<ASCLLNUM;i++){
		ascll[i].count=0;
	}
	while(!feof(infile)){//读取文件中的相关信息
		c=fgetc(infile);
		ascll[c].sign=c;
		ascll[c].count++;
		total++;
	}
	total--;
	for(int i=0;i<ASCLLNUM;i++){
		if(ascll[i].count>0){
			val++;
			printf("符号：%c 频数：%d\n",ascll[i].sign,ascll[i].count);
		}
	}
	BSTree *q;
	q=CreateLinkList(ascll,val);
	print(q);
	q=HuffTree(q);
	HuffCode(q,hastb);
	fclose(infile);
	fclose(outfile);
	//压缩头文件
	outfile=fopen(outfName,"wb");
	fprintf(outfile,"%d",total);
	for(int i=0;i<ASCLLNUM;i++){
		fprintf(outfile,"%d",ascll[i].count);
	}
	//压缩主文件
	fseek(infile,0,0);//从头开始读
	while(!feof(infile)){
		c=fgetc(infile);
	} 
}
int main() {
	/*BSTree *root;
	int n;

	while(printf("输入叶子结点的个数\n")&&scanf("%d",&n)!=EOF){  //连续输入
	printf("输入n个叶子结点的权值:\n");
	root=CreateLinkList(n);//生成一个升序单链表
	printf("输出所生成的升序单链表:\n");
	print(root);
	root=HuffTree(root);//生成哈夫曼树
	printf("后序遍历哈夫曼树构造并输出哈夫曼编码:\n");
	HuffCode(root);
	}*/
	compress();
	return 0;
}
