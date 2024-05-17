#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode
{
    char c;
    int weight;
    struct tnode *left, *right;
};
int Ccount[128] = {0};
struct tnode *Root = NULL;
char HCode[128][MAXSIZE] = {{0}};
int Step = 0;
FILE *Src, *Obj;

void statCount();
void createHTree();
void makeHCode();
void atoHZIP();

void print1();                // �������1�Ľ��
void print2(struct tnode *p); // �������2�Ľ��
void print3();                // �������3�Ľ��
void print4();                // �������4�Ľ��

int main()
{
    if ((Src = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if ((Obj = fopen("output.txt", "w")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step); // ���뵱ǰʵ�鲽��

    statCount();                           // ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
    (Step == 1) ? print1() : 1;            // ���ʵ�鲽��1���
    createHTree();                         // ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
    (Step == 2) ? print2(Root) : 2;        // ���ʵ�鲽��2���
    makeHCode();                           // ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
    (Step == 3) ? print3() : 3;            // ���ʵ�鲽��3���
    (Step >= 4) ? atoHZIP(), print4() : 4; // ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���

    fclose(Src);
    fclose(Obj);

    return 0;
}

// ��ʵ�鲽��1����ʼ

void statCount()
{

    Ccount[0] = 1;

    char ch;
    while ((ch = fgetc(Src)) != EOF)
    {
        if (ch != '\n')
            Ccount[(int)ch]++;
    }
}

// ��ʵ�鲽��1������

// ��ʵ�鲽��2����ʼ

void createHTree()
{
    struct tnode *F[150];
    for (int i = 0; i < 150; i++)
    {
        F[i] = NULL;
    }
    struct tnode *p;
    int k = 0;
    for (int i = 0; i < 128; i++)

        if (Ccount[i] > 0)
        {

            p = (struct tnode *)malloc(sizeof(struct tnode));

            p->c = i;
            p->weight = Ccount[i];

            p->left = p->right = NULL;

            F[k++] = p;
        }
    int i1, j1;
    struct tnode *hold;
    for (i1 = 1; i1 < k; i1++)
        for (j1 = 0; j1 < k - i1; j1++)
        {
            if ((F[j1]->weight > F[j1 + 1]->weight) || ((F[j1]->weight == F[j1 + 1]->weight) && ((F[j1]->c) > (F[j1 + 1]->c))))
            {
                hold = F[j1];
                F[j1] = F[j1 + 1];
                F[j1 + 1] = hold;
            }
        }
    while (k > 1)
    {
        struct tnode *T;
        // T=add(F[0],F[1]);
        T = (struct tnode *)malloc(sizeof(struct tnode));
        T->weight = F[0]->weight + F[1]->weight;
        T->left = F[0];
        T->right = F[1];

        // Delete(F[0],F[1]);

        for (int i = 0; i < k; i++)
        {
            F[i] = F[i + 2];
        }
        k -= 2;

        // ADD(T);
        if (k == 0)
        {
            F[0] = T;
        }
        else
        {
            for (int i = 0; i < k; i++)
            {

                if (i == k - 1)
                {
                    F[i + 1] = T;
                    break;
                }
                else if ((T->weight >= F[i]->weight) && (T->weight < F[i + 1]->weight))
                {
                    for (int j = k; j >= i + 1; j--)
                    {
                        F[j + 1] = F[j];
                    }
                    F[i + 1] = T;
                    break;
                }
            }
            k++;
        }
    }
    Root = F[0];
}

// ��ʵ�鲽��2������

// ��ʵ�鲽��3����ʼ
void preorder(struct tnode *T, char s[], int k) // 前序输出
{
    struct tnode *p = T;

    if (p->left == NULL && p->right == NULL)
    {
        s[k--] = 0;
        strcpy(HCode[(int)p->c], s);

        return;
    }

    s[k++] = '0';
    preorder(p->left, s, k);

    k--;
    s[k++] = '1';
    preorder(p->right, s, k);

    s[k--] = 0;
}
void makeHCode()
{
    char s[150];

    memset(s, 0, 150);
    int k = 0;
    preorder(Root, s, k);
}

// ��ʵ�鲽��3������

// ��ʵ�鲽��4����ʼ

void atoHZIP()
{
    char s[50000];
    memset(s,0,50000);
    fseek(Src,0,SEEK_SET);
    char c=1;
    do{
        c=fgetc(Src);
        if(c==EOF)
        c=0;
        strcat(s,HCode[(int)c]);
    }while(c!=0);
    unsigned char hc;
    int len=strlen(s);
    int num=8-len%8;
    if(num!=8)
    for(int i=0;i<num;i++)
    {
        s[len++]='0';
    }
    for (int i = 0; s[i] != 0; i++)
    {

        
        hc = (hc << 1) | (s[i] - '0');

        if ((i + 1) % 8 == 0)
        {

            fputc(hc, Obj); // 输出到目标（压缩）文件中

            printf("%x", hc); // 按十六进制输出到屏幕上
            hc=0;
        }
    }
}

// ��ʵ�鲽��4������

void print1()
{
    int i;
    printf("NUL:1\n");
    for (i = 1; i < 128; i++)
        if (Ccount[i] > 0)
            printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
    if (p != NULL)
    {
        if ((p->left == NULL) && (p->right == NULL))
            switch (p->c)
            {
            case 0:
                printf("NUL ");
                break;
            case ' ':
                printf("SP ");
                break;
            case '\t':
                printf("TAB ");
                break;
            case '\n':
                printf("CR ");
                break;
            default:
                printf("%c ", p->c);
                break;
            }
        print2(p->left);
        print2(p->right);
    }
}

void print3()
{
    int i;

    for (i = 0; i < 128; i++)
    {
        if (HCode[i][0] != 0)
        {
            switch (i)
            {
            case 0:
                printf("NUL:");
                break;
            case ' ':
                printf("SP:");
                break;
            case '\t':
                printf("TAB:");
                break;
            case '\n':
                printf("CR:");
                break;
            default:
                printf("%c:", i);
                break;
            }
            printf("%s\n", HCode[i]);
        }
    }
}

void print4()
{
    long int in_size, out_size;

    fseek(Src, 0, SEEK_END);
    fseek(Obj, 0, SEEK_END);
    in_size = ftell(Src);
    out_size = ftell(Obj);

    printf("\nԭ�ļ���С��%ldB\n", in_size);
    printf("ѹ�����ļ���С��%ldB\n", out_size);
    printf("ѹ���ʣ�%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}
