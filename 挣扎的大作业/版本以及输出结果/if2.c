#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 80
int id1 = 0, id2 = 0;
typedef struct Node
{
    char data;
    struct Node *next[26];
    int cnt;
} LNode, *LinkList;
LinkList CreateHead();
LinkList AddData(LinkList head, char *word);
struct word_list
{
    char word[MAXWORD];
    int cnt;
};
struct word_list cnt_article[600000] ;

int tree_of_article[600000][26];


LinkList head[100000] = {NULL};
LinkList head1[100000]= {NULL};
int weight[100000] ;
int han_dis[100000];
long long finger[100000][130] ;
long long finger1[130];
char tag_article[100000][12] ;
char tag_sample[12] ;
int get_word(FILE *IN, char words[]);
void get_stop_words(char word[]);
int find(LinkList head, char *word);
int set_article_word(char word[]);
int cmp(const void *a, const void *b);
int get_sample_word(char word[]);
char hash_value[100001][129];
char word[MAXWORD];
int read_activate = 1;
int readstate = 1;
int num_article = 0;
int num_sample;
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
    N=1100;
    M=36;
    
    FILE *stop_words, *file_article, *hash, *file_sample, *file_result;
    
    hash = fopen("hashvalue.txt", "r");
    for (int j = 0; j < N; j++)
        fread(hash_value[j], sizeof(char), sizeof(hash_value[j]), hash);

    fclose(hash);
    // 读取停用词表并建立树1
    stop_words = fopen("stopwords.txt", "rb");

    int pos = 0, pos_max = 0;
    while (fscanf(stop_words, "%s", word) != EOF)
    {
        get_stop_words(word);
    }
    fclose(stop_words);
    memset(word, 0, 80);
    // 读取article并建立树2

    file_article = fopen("article.txt", "r");
    while (fscanf(file_article, "%s", tag_article[num_article]) != EOF)
    {

        head[num_article] = CreateHead();

        while ((read_activate = get_word(file_article, word)) == 0) // 成功读入一个单词
        {
            if ((pos = set_article_word(word)) > 0) // 把单词读入
            {
                AddData(head[num_article], word);
                if (pos > pos_max)
                    pos_max = pos;
            }
            memset(word, 0, 80);
        }

        num_article++;
        
    }
    // 对cnt排序,得到特征向量
    qsort(cnt_article, pos_max+1, sizeof(struct word_list), cmp);
    file_result = fopen("result.txt", "w");
    /*for(int i=0;i<600000;i++)
    {
        fprintf(file_result,"%s %d\n",cnt_article[i].word,cnt_article[i].cnt);
    }*/
    
    for (int i = 0; i < num_article; i++)
    {
        memset(weight, 0, 100000);
        for (int j = 0; j < N; j++)
        {
            weight[j] = find(head[i], cnt_article[j].word);
            
        }
        
        for (int j = 0; j < M; j++)
            for (int k = 0; k < N; k++)
            {
                if (hash_value[k][j] == '1')
                    finger[i][j] += (long long)weight[k];
                else
                    finger[i][j] -= (long long)weight[k];
            }
        for (int j = 0; j < M; j++)
        {
            if (finger[i][j] > 0)
                finger[i][j] = 1;
            else
                finger[i][j] = 0;
        }
    }

    /*for(int i=0;i<num_article;i++)
    {
        for(int j=0;j<M;j++)
        printf("%d ",finger[i][j]);

        printf("\n");
    }*/

    file_sample = fopen("sample.txt", "r");
    file_result = fopen("result.txt", "w");
    int count = 0;
    while (fscanf(file_sample, "%s", tag_sample) != EOF)
    {
        memset(weight, 0, 100000);
        memset(finger1, 0, 130);
        memset(han_dis, 0, 100000);
        while ((readstate = get_word(file_sample, word)) == 0)
        {
            for (int i = 0; i < N; i++)
            {
                if (strcmp(word, cnt_article[i].word) == 0)
                {
                    weight[i]++;
                    break;
                }
            }
            memset(word,0,80);

        }
        
        // 计算指纹
        for (int j = 0; j < M; j++)
            for (int k = 0; k < N; k++)
            {
                if (hash_value[k][j] == '1')
                    finger1[j] += (long long)weight[k];
                else
                    finger1[j] -= (long long)weight[k];
            }
        for (int j = 0; j < M; j++)
        {
            if (finger1[j] > 0)
                finger1[j] = 1;
            else
                finger1[j] = 0;
        }

        // 计算汉明
        int hanming = 0;
        for (int i = 0; i < num_article; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (finger[i][j] != finger1[j])
                    hanming++;
            }
            han_dis[i] = hanming;
            hanming = 0;
        }
        fprintf(file_result, "%s\n", tag_sample);
        for (int i = 0; i <= 3; i++)
        {
            int flag = 0;
            for (int j = 0; j < num_article; j++)
            {
                if (han_dis[j] == i)
                {
                    if (flag == 0)
                    {
                        fprintf(file_result, "%d:", i);
                        flag = 1;
                    }
                    fprintf(file_result, "%s ", tag_article[j]);
                }
            }
            if (flag == 1)
                fprintf(file_result, "\n");
        }
        if (count == 0)
        {
            count=1;
            printf("%s\n",tag_sample);
            for (int i = 0; i <= 3; i++)
            {
                int flag = 0;
                for (int j = 0; j < num_article; j++)
                {
                    if (han_dis[j] == i)
                    {
                        if (flag == 0)
                        {
                            printf("%d:",i);
                            flag = 1;
                        }
                        printf("%s ",tag_article[j]);
                    }
                }
                if (flag == 1)
                    printf("\n");
            }
        }
    }
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
    int p = 0, n = 0; // 建立stop_words字典树
    for (int i = 0; word[i]; i++)
    {
        n = word[i] - 'a';
        if (tree_of_article[p][n] == 0)
            tree_of_article[p][n] = ++id1;
        p = tree_of_article[p][n];
    }
    cnt_article[p].cnt = -1; // 表示这个词是停用词
}
int set_article_word(char word[])
{
    int p = 0, n = 0;
    for (int i = 0; word[i]; i++) // 建立字典树
    {
        n = word[i] - 'a';
        if (tree_of_article[p][n] == 0)
            tree_of_article[p][n] = ++id1;
        p = tree_of_article[p][n];
    }
    if (cnt_article[p].cnt == -1) // 表示读到的词是停用词
        return -1;
    if (cnt_article[p].cnt == 0) // 不是停用词
        strcpy(cnt_article[p].word, word);
    // 不是停用词而且词频不是0
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
LinkList CreateHead()
{
    LinkList head = (LinkList)malloc(sizeof(LNode));
    for (int i = 0; i < 26; i++)
        head->next[i] = NULL;
    head->cnt = 0;
    return head;
}
LinkList AddData(LinkList head, char *word)
{
    LinkList newnode, p = head;
    int i = 0;
    while (word[i] != '\0')
    {
        int hashnum = word[i] - 'a';
        if (p->next[hashnum] == NULL)
        {
            newnode = CreateHead();
            newnode->data = word[i];
            p->next[hashnum] = newnode;
            p = newnode;
        }
        else
        {
            p = p->next[hashnum];
        }
        i++;
    }
    p->cnt++;
    return head;
}
int find(LinkList head, char *word)
{
    int i = 0;
    int hashnum;
    while (word[i] != '\0')
    {
        hashnum = word[i] - 'a';
        if (head->next[hashnum] == NULL)
            return 0;
        else
        {
            head = head->next[hashnum];
            i++;
        }
    }
    return head->cnt;
}