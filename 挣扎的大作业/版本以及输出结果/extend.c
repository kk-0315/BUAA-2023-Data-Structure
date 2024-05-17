#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 77
int total1 = 0, total2 = 0;
typedef struct Node
{
    struct Node *next[50];
    int cnt;
} tree, *TREE;
TREE CreateHead();
TREE Insert(TREE head, char *word);
struct word_list
{
    char word[MAXWORD];
    int cnt;
};
struct word_list cnt_article[400000] ;
int tree_of_article[400000][50];
TREE head[160000] = {NULL};
TREE head1[160000]= {NULL};
int weight[160000] ;
int han_dis[160000];
int finger[160000][1300] ;
int finger1[1300];
char title_article[16000][30] ;
char title_sample[30] ;
int get_word(FILE *IN, char words[]);
void set_stop_words_tree(char word[]);
int find(TREE head, char *word);
int set_article_words_tree(char word[]);
int cmp(const void *a, const void *b);
char hash_value[16000][130];
char word[MAXWORD];
int state = 1;
int readstate = 1;
int num_article = 0;
int num_sample;
int N = 0, M = 0;

int main(int argc, char *argv[])
{
    for (int i = 0; argv[1][i] != 0; i++)
    {
        N = argv[1][i] - '0' + 10 * N;
    }
    for (int i = 0; argv[2][i] != 0; i++)
    {
        M = argv[2][i] - '0' + 10 * M;
    }
    
    
    FILE *stop_words, *file_article, *hash, *file_sample, *file_result;
    
    hash = fopen("hashvalue.txt", "r");
    for (int j = 0; j < N; j++)
        fread(hash_value[j], sizeof(char), sizeof(hash_value[j]), hash);

    fclose(hash);
    // 读取停用词表并建立stopword树
    stop_words = fopen("stopwords.txt", "r");

    int pos = 0, max = 0;
    while (fscanf(stop_words, "%s", word) != EOF)
    {
        set_stop_words_tree(word);
    }
    fclose(stop_words);
    memset(word, 0, 77);
    // 读取article并建立article树

    file_article = fopen("article.txt", "r");
    while (fscanf(file_article, "%s", title_article[num_article]) != EOF)
    {

        head[num_article] = CreateHead();
        while ((state = get_word(file_article, word)) == 0) // 成功读入一个单词
        {
            if ((pos = set_article_words_tree(word)) > 0) // 把单词读入字典树
            {
                Insert(head[num_article], word);
                if (pos > max)
                    max = pos;
            }
            memset(word, 0, 77);
        }

        num_article++;
        if (state == -2) // 到末尾
            break;
    }
    // 对cnt排序,得到排序好的词频
    qsort(cnt_article, max+1, sizeof(struct word_list), cmp);
    file_result = fopen("result.txt", "w");
    /*for(int i=0;i<100;i++)
    printf("%d %s %d\n",i,cnt_article[i].word,cnt_article[i].cnt);*/
    
    for (int i = 0; i < num_article; i++)
    {
        for (int j = 0; j < N; j++)
        {
            weight[j] = find(head[i], cnt_article[j].word); 
        }
        for (int j = 0; j < M; j++)
            for (int k = 0; k < N; k++)
            {
                if (hash_value[k][j] == '1')
                    finger[i][j] += weight[k];
                else
                    finger[i][j] -= weight[k];
            }
        for (int j = 0; j < M; j++)
        {
            if (finger[i][j] > 0)
                finger[i][j] = 1;
            else
                finger[i][j] = 0;
        } 
    }
    /*
    for(int i=0;i<num_article;i++)
    {
        for(int j=0;j<M;j++)
        fprintf(file_result,"%d ",finger[i][j]);
        fprintf(file_result,"\n");
    }*/
    file_sample = fopen("sample.txt", "r");
    int count = 0;
    while (fscanf(file_sample, "%s", title_sample) != EOF)
    {
        for(int i=0;i<N;i++)
        weight[i]=0;
        for(int i=0;i<M;i++)
        finger1[i]=0;
        /*memset(weight, 0, 16000);
        memset(finger1, 0, 130);
        memset(han_dis, 0, 16000);*/
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
            memset(word,0,77);
        }
        
        /*for(int j=0;j<N;j++)
        fprintf(file_result,"%d ",weight[j]);
        fprintf(file_result,"\n");*/
  
        // 计算指纹
        for (int j = 0; j < M; j++)
            for (int k = 0; k < N; k++)
            {
                if (hash_value[k][j] == '1')
                    finger1[j] += weight[k];
                else
                    finger1[j] -= weight[k];
                /*if(flag1==2&&j==33)
                printf("%d->",finger1[j]);*/
            }
        /*for(int j=0;j<M;j++)
        fprintf(file_result1,"%d ",finger1[j]);
        
        fprintf(file_result1,"\n");*/
        for (int j = 0; j < M; j++)
        {
            if (finger1[j] > 0)
                finger1[j] = 1;
            else
                finger1[j] = 0;
        }   
        /*for(int j=0;j<M;j++)
        fprintf(file_result,"%d ",finger1[j]);
        fprintf(file_result,"\n");*/
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
        fprintf(file_result, "%s\n", title_sample);
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
                    fprintf(file_result, "%s ", title_article[j]);
                }
            }
            if (flag == 1)
                fprintf(file_result, "\n");
        }
        if (count == 0)
        {
            count=1;
            printf("%s\n",title_sample);
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
                        printf("%s ",title_article[j]);
                    }
                }
                if (flag == 1)
                    printf("\n");
            }
        }
        
    }
    fclose(file_article);
    fclose(file_result);
    fclose(file_sample);
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
void set_stop_words_tree(char word[])
{
    int p = 0, n = 0; // 建立stopwords字典树
    for (int i = 0; word[i]; i++)
    {
        n = word[i] - 'a';
        if (tree_of_article[p][n] == 0)
            tree_of_article[p][n] = ++total1;
        p = tree_of_article[p][n];
    }
    cnt_article[p].cnt = -1; // 表示这个词是停用词
}
int set_article_words_tree(char word[])
{
    int p = 0, n = 0;
    for (int i = 0; word[i]; i++) // 建立字典树
    {
        n = word[i] - 'a';
        if (tree_of_article[p][n] == 0)
            tree_of_article[p][n] = ++total1;
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
TREE CreateHead()
{
    TREE head = (TREE)malloc(sizeof(tree));
    for (int i = 0; i < 50; i++)
        head->next[i] = NULL;
    head->cnt = 0;
    return head;
}
TREE Insert(TREE head, char *word)
{
    TREE newnode, p = head;
    int i = 0;
    while (word[i] != '\0')
    {
        int index = word[i] - 'a';
        if (p->next[index] == NULL)
        { 
            newnode = CreateHead();       
            p->next[index] =newnode;
            p = newnode;
        }
        else
        {
            p = p->next[index];
        }
        i++;
    }
    p->cnt++;
    return head;
}
int find(TREE head, char *word)
{
    int i = 0;
    int index;
    while (word[i] != '\0')
    {
        index = word[i] - 'a';
        if (head->next[index] == NULL)
            return 0;
        else
        {
            head = head->next[index];
            i++;
        }
    }
    return head->cnt;
}