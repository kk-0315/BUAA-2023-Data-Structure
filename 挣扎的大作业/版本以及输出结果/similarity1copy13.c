#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 80
int han_dis[4][15000] = {0};
int id1 = 0;

typedef struct Node{
	char data;
	struct Node* next[26];
    int cnt;
}LNode,*LinkList;
LinkList CreateHead();
LinkList AddData(LinkList head,char* word);
int FindWord(LinkList head,char* word);

struct word_list
{
    char word[MAXWORD];
    int cnt;
} cnt_article[600000] = {{0}, 0};

int tree_of_article[600000][26] = {0};
int tree_of_vector[100000][26] = {0};
int flag_of_vector[100000] = {0};
int cnt_of_vector[100000] = {0};

int id3 = 0;
int id4 = 0;

LinkList head[100000]={NULL};

char tag_article[100000][12] = {0};
char tag_sample[12] = {0};

int fingers[10002] = {0};

int get_word(FILE *IN, char words[]);
void get_stop_words(char word[]);

int get_article_word(char word[]);


void get_vector_word1(char word[]);
void get_vector_word2(char word[]);
int cmp(const void *a, const void *b);

int han_ming(unsigned long long x1, unsigned long long x2, unsigned long long y1, unsigned long long y2);
char hash_value[100001][129] = {0};

int fingerprint_ori[128] = {0};
unsigned long long article_fingerprint[100001][2] = {0};
unsigned long long sample_fingerprint[2] = {0};
int read_activate = 1;
int num_article = 0;
int num_similar[4] = {0};
int N = 0, M = 0;
int main(/*int argc, char *argv[]*/)
{

    /*for (int i = 0; argv[1][i] != 0; i++)
    {
        N = argv[1][i] - '0' + 10 * N;
    }
    for (int i = 0; argv[2][i] != 0; i++)
    {
        M = argv[2][i] - '0' + 10 * M;
    }*/
    N=1280;
    M=23;
    FILE *stop_words, *file_article, *hash, *file_sample, *file_result;
    //file_words=fopen("words.txt","w");
    // 读取hash表，读N*128个
    hash = fopen("hashvalue.txt", "r");
    for (int j = 0; j < N; j++)
        fread(hash_value[j],sizeof(char),sizeof(hash_value[j]),hash);

    fclose(hash);
    // 读取停用词表并建立树1
    stop_words = fopen("stopwords.txt", "rb");
    char word[MAXWORD];
    int pos = 0, pos_max = 0, han_tmp = 0;
    while (fscanf(stop_words, "%s", word) != EOF)
    {
        get_stop_words(word);
    }
    fclose(stop_words);
    // 读取article并建立树2
    file_article = fopen("article.txt", "r");
    while (fscanf(file_article, "%s", tag_article[num_article]) != EOF)
    {

        head[num_article]=CreateHead();

        while ((read_activate = get_word(file_article, word)) == 0)
        {
            if ((pos = get_article_word(word))>0)
            {
                AddData(head[num_article],word);
                if (pos > pos_max)
                pos_max = pos;
            }
        }
        id3 = 0;
        num_article++;
        if (read_activate == -2)
            break;
    }
    // 对cnt排序,得到向量
    qsort(cnt_article, pos_max, sizeof(struct word_list), cmp);
    /*
    for(int i=0;i<600000;i++)
    {
        fprintf(file_result,"%s %d\n",cnt_article[i].word,cnt_article[i].cnt);
    }*/
    file_result = fopen("outing6.txt", "w");
    for (int z = 0; z < num_article; z++) // 遍历文章
    {
        for (int i = 0; i < N; i++) // 计算权重
        {
            fingers[i]=FindWord(head[z],cnt_article[i].word);
        }
        
        
            
        

        for (int i = 0; i < N; i++) // 计算指纹
        {
            for (int j = 0; j < M; j++)
            {
                if (hash_value[i][j] == '1')
                    fingerprint_ori[j] += fingers[i];
                else
                    fingerprint_ori[j] -= fingers[i];
            }
        } // 填写指纹到unsigned long long

        for(int i=0;i<M;i++){
            if(fingerprint_ori[i]>0)
            fingerprint_ori[i]=1;
            else
            fingerprint_ori[i]=0;
            fprintf(file_result,"%d ",fingerprint_ori[i]);}
            fprintf(file_result,"\n");
            
        
        for (int i = 0; i < 64 && i < M; i++)
        {
            if (fingerprint_ori[i] > 0)
                article_fingerprint[z][0] |= (1ULL << i);
        }
        for (int i = 64; i < M; i++)
        {
            if (fingerprint_ori[i] > 0)
                article_fingerprint[z][1] |= (1ULL << (i - 64));
        }
        // 重置计算指纹时用到的中间变量
        memset(fingerprint_ori, 0, sizeof(fingerprint_ori));
        memset(fingers, 0, sizeof(fingers));
    }
    
    fclose(file_article);
    // 建立向量树
    int check_flag=0;
    for (int i = 0; i < N; i++)
    {
        get_vector_word1(cnt_article[i].word);
    }
    
    file_sample = fopen("sample.txt", "r");
    
    int flag1=0;
    while (fscanf(file_sample, "%s", tag_sample) != EOF)
    {
        flag1++;
        while ((read_activate = get_word(file_sample, word)) == 0)
        {
            get_vector_word2(word);
        }
        for (int i = 0; i < N; i++) // 计算权重
        {
            int p = 0, j = 0, n = 0;
            for (; cnt_article[i].word[j] != 0; j++)
            {
                n = cnt_article[i].word[j] - 'a';
                p = tree_of_vector[p][n];
            }
                fingers[i] = cnt_of_vector[p];
        }
        
        /*for(int j=0;j<N;j++)
        fprintf(file_result,"%d ",fingers[j]);

        fprintf(file_result,"\n");*/

        for (int i = 0; i < N; i++) // 计算指纹
        {
            for (int j = 0; j < M; j++)
            {
                if (hash_value[i][j] == '1')
                    fingerprint_ori[j] += fingers[i];
                else
                    fingerprint_ori[j] -= fingers[i];
                /*if(flag1==2&&j==33)
                printf("%d->",fingerprint_ori[j]);*/
            }
        }
            /*
            for(int i=0;i<M;i++){
            if(fingerprint_ori[i]>0)
            fingerprint_ori[i]=1;
            else
            fingerprint_ori[i]=0;
            fprintf(file_result,"%d ",fingerprint_ori[i]);}
            fprintf(file_result,"\n");*/
        /*
        for (int i = 0; i < 64 && i < M; i++) // 填入unsigned long long
        {
            if (fingerprint_ori[i] > 0)
                sample_fingerprint[0] |= (1ULL << i);
        }
        for (int i = 64; i < M; i++)
        {
            if (fingerprint_ori[i] > 0)
                sample_fingerprint[1] |= (1ULL << (i - 64));
        }
        for (int i = 0; i < num_article; i++) // 计算汉明距离并按照距离将编号填入han——dis【0】，【1】，【2】，【3】，
        {
            han_tmp = han_ming(article_fingerprint[i][0], article_fingerprint[i][1], sample_fingerprint[0], sample_fingerprint[1]);
            if (han_tmp <= 3)
            {
                han_dis[han_tmp][num_similar[han_tmp]] = i;
                num_similar[han_tmp]++; // 对应数量++
            }
        }

        fprintf(file_result, "%s\n", tag_sample);

        for (int i = 0; i <= 3; i++)
        {
            if (num_similar[i] > 0)
            {
                fprintf(file_result, "%d:", i);

                for (int j = 0; j < num_similar[i]; j++)
                    fprintf(file_result, "%s ", tag_article[han_dis[i][j]]);
                fprintf(file_result, "\n");
            }
        }
        /*
        if(check_flag==0)
        {
            check_flag=1;
            printf("%s\n", tag_sample);

        for (int i = 0; i <= 3; i++)
        {
            if (num_similar[i] > 0)
            {
                printf("%d:", i);

                for (int j = 0; j < num_similar[i]; j++)
                    printf("%s ", tag_article[han_dis[i][j]]);
                printf("\n");
            }
        }

        }*/
        if (read_activate == -2)
            break;
        memset(fingerprint_ori, 0, sizeof(fingerprint_ori));
        memset(han_dis, 0, sizeof(han_dis));
        memset(num_similar, 0, sizeof(num_similar));
        memset(fingers, 0, sizeof(fingers));
        memset(cnt_of_vector, 0, sizeof(cnt_of_vector));
        sample_fingerprint[0] = 0;
        sample_fingerprint[1] = 0;
    }
    fclose(file_sample);
    fclose(file_result);
}

int get_word(FILE *IN, char words[])
{
    char ch = 0;
    int i = 0;
    while (!isalpha(ch = fgetc(IN)))
    {
        if (ch == EOF)
            return -2;
        else if (ch == '\f')
            return -1;
    }
    do
    {
        words[i] = tolower(ch);
        i++;
    } while (isalpha(ch = fgetc(IN)));
    words[i] = '\0';
    return 0;
}

void get_stop_words(char word[])
{
    int p = 0, n = 0;
    for (int i = 0; word[i]; i++)
    {
        n = word[i] - 'a';
        if (tree_of_article[p][n] == 0)
            tree_of_article[p][n] = ++id1;
        p = tree_of_article[p][n];
    }
    cnt_article[p].cnt = -1;
}
void get_vector_word1(char word[])
{
    int p = 0, n = 0;
    for (int i = 0; word[i]; i++)
    {
        n = word[i] - 'a';
        if (tree_of_vector[p][n] == 0)
            tree_of_vector[p][n] = ++id4;
        p = tree_of_vector[p][n];
    }
    flag_of_vector[p] = 1;
}
void get_vector_word2(char word[])
{
    int p = 0, n = 0;
    for (int i = 0; word[i]; i++)
    {
        n = word[i] - 'a';
        if (tree_of_vector[p][n] == 0)
            return;
        p = tree_of_vector[p][n];
    }
    if (flag_of_vector[p] == 1)
        cnt_of_vector[p]++;
}


int get_article_word(char word[])
{
    int p = 0, n = 0;
    for (int i = 0; word[i]; i++)
    {
        n = word[i] - 'a';
        if (tree_of_article[p][n] == 0)
            tree_of_article[p][n] = ++id1;
        p = tree_of_article[p][n];
    }
    if(cnt_article[p].cnt==-1)
    return -1;
    if (cnt_article[p].cnt == 0)
        strcpy(cnt_article[p].word, word);

    cnt_article[p].cnt++;
    return p;
}

int cmp(const void *a, const void *b)
{
    int cnt1 = (*(struct word_list *)b).cnt;
    int cnt2 = (*(struct word_list *)a).cnt;
    if (cnt1 != cnt2)
        return cnt1 - cnt2;
    else if (strcmp((*(struct word_list *)a).word, (*(struct word_list *)b).word) > 0)
        return 1;
    else
        return -1;
}

int han_ming(unsigned long long x1, unsigned long long x2, unsigned long long y1, unsigned long long y2)
{
    unsigned long long s = x1 ^ y1;
    int ret = 0;
    while (s != 0)
    {
        s &= s - 1;
        ret++;
    }
    if (M > 64)
    {
        unsigned long long t = x2 ^ y2;
        while (t != 0)
        {
            t &= t - 1;
            ret++;
        }
    }
    return ret;
}
LinkList CreateHead(){
	LinkList head = (LinkList)malloc(sizeof(LNode));
	for(int i = 0;i<26;i++) head->next[i] = NULL;
    head->cnt=0;
	return head;
}
LinkList AddData(LinkList head,char* word){
	LinkList newnode,p = head;
	int i = 0;
	while(word[i]!='\0'){
		int hashnum = word[i] - 'a';
		if(p->next[hashnum] == NULL){
			newnode = CreateHead();
			newnode->data = word[i];
			p->next[hashnum] = newnode;
			p = newnode;
		}else{
			p = p->next[hashnum];
		}
		i++;
	}
    p->cnt++;
	return head;
}
int FindWord(LinkList head,char*word){
	int i = 0;
	int hashnum;
	while(word[i]!='\0'){
		hashnum = word[i]-'a';
		if(head->next[hashnum] == NULL) return 0;
		else{
			head = head->next[hashnum];
			i++;
		}
	}
	return head->cnt;
}
