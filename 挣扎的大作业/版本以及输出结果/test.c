#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define DOC_ARTICLE_SIZE 1005
#define DOC_SAMPLE_SIZE 15
#define WORD_SIZE 30
#define WORD_COUNTS_SIZE 10000

struct DOC_ARTICLE
{
    char doc_no[30];
    int finger[130];
    int weight[10000];

} doc_article[DOC_ARTICLE_SIZE];

struct DOC_SAMPLE
{
    char doc_no[30];
    int finger[130];
    int weight[130];
} doc_sample[DOC_SAMPLE_SIZE];

struct WORD_COUNT
{
    char s[30];
    int count;

} word_counts[WORD_COUNTS_SIZE];
char hash_table[10005][130];
int word_num;
char buffer[WORD_SIZE];
char stop_word[1000][30];
int len_stop_word;
char ch;
int doc_article_num = 1;
int doc_sample_num = 1;
int doc_article_num1 = 1;
int doc_sample_num1 = 1;
FILE *article, *result, *sample, *hash, *article_single,*sample_single;
void Create_stop_word();
int Instopword(char *w);
void Create_hash(FILE *fp);
void Read_article(int N, int M, FILE *article);
void Read_weight(FILE *fp, int M);
void Fingerprint(int N, int M);
void Read_sample(int N, int M, FILE *article);
void Read_weight1(FILE *fp, int N);
void Fingerprint1(int N, int M);
int cmp(const void *p1, const void *p2)
{
    if ((((struct WORD_COUNT *)p1)->count) == (((struct WORD_COUNT *)p2)->count))
        {
            if(strcmp((((struct WORD_COUNT *)p1)->s),(((struct WORD_COUNT *)p2)->s))>0)
            return 1;
            else
            return -1;
        }
    else if (((struct WORD_COUNT *)p1)->count < ((struct WORD_COUNT *)p2)->count)
        return 1;
    else
        return -1;
}

int main()
{
    int N, M;
    article = fopen("article1.txt", "r");
    result = fopen("result.txt", "w");
    sample = fopen("sample.txt", "r");
    hash = fopen("hashvalue.txt", "r");
    Create_hash(hash);
    Create_stop_word();

    scanf("%d%d", &N, &M);
    for(int i=0;i<WORD_COUNTS_SIZE;i++)
    {
        word_counts[i].count=0;
        for(int j=0;j<30;j++)
        word_counts[i].s[j]=0;
    }
    for(int i=0;i<DOC_SAMPLE_SIZE;i++)
    {
        for(int j=0;j<10000;j++)
        doc_article[i].weight[j]=0;
    }
    
    Read_article(N, M, article);
    
    
    /*for(int i=0;i<N;i++)
    printf("%s %d",word_counts[i].s,word_counts[i].count);*/
    
    article_single = fopen("article1.txt", "r");
    Read_weight(article_single, N);
    
    
    for(int i=1;i<2;i++)
    {
        for(int j=0;j<N;j++)
        printf("%d ",doc_article[i].weight[j]);
    }
    /*
    Fingerprint(N, M);

    
    Read_sample(N, M, sample);
    sample_single = fopen("sample.txt", "r");
    Read_weight1(sample_single, N);
    Fingerprint1(N, M);
    
    /*for (int i = 1; i < doc_sample_num; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%d ", doc_sample[i].finger[j]);
        printf("\n");

    }*/
    /*for (int i = 1; i < doc_article_num1; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%d ", doc_article[i].finger[j]);
        printf("\n");

    }*/
}
void Create_stop_word()
{
    FILE *stop;
    char word[1000];
    stop = fopen("stopwords.txt", "r");
    while (fscanf(stop, "%s", word) != EOF)
    {
        strcpy(stop_word[len_stop_word++], word);
    }
}
int Instopword(char *w)
{
    for (int i = 0; i < len_stop_word; i++)
    {
        if (strcmp(w, stop_word[i]) == 0)
            return 1;
    }
    return 0;
}
void Create_hash(FILE *fp)
{

    for (int i = 0; i < 10000; i++)
    {
        fscanf(fp, "%s", hash_table[i]);
    }
}
void Read_article(int N, int M, FILE *article)
{
    fscanf(article, "%s", doc_article[doc_article_num].doc_no);

    while ((ch = (fgetc(article))) != EOF)
    {
        memset(buffer, 0, WORD_SIZE);
        if (isalpha(ch))
        {
            int i = 0;
            do
            {
                buffer[i++] = tolower(ch);
                ch = fgetc(article);
            } while (isalpha(ch));
            ungetc(ch, article);
            buffer[i] = 0;

            if (Instopword(buffer) == 0)
            {
                int flag = 0;
                for (int i = 0; i < word_num; i++)
                {
                    if (strcmp(buffer, word_counts[i].s) == 0)
                    {
                        word_counts[i].count++;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    strcpy(word_counts[word_num].s, buffer);
                    word_counts[word_num++].count = 1;
                }
            }
        }
        else if (ch == '\f')
        {

            // new article turn
            doc_article_num++;

            fscanf(article, "%s", doc_article[doc_article_num].doc_no); // 向下读入下一文章序号
        }
    }
    qsort(word_counts, word_num, sizeof(struct WORD_COUNT), cmp);
}
void Read_sample(int N, int M, FILE *article)
{
    memset(word_counts,0,WORD_COUNTS_SIZE);

    word_num=0;
    fscanf(article, "%s", doc_sample[doc_sample_num].doc_no);

    while ((ch = (fgetc(article))) != EOF)
    {
        memset(buffer, 0, WORD_SIZE);
        if (isalpha(ch))
        {
            int i = 0;
            do
            {
                buffer[i++] = tolower(ch);
                ch = fgetc(article);
            } while (isalpha(ch));
            ungetc(ch, article);
            buffer[i] = 0;

            if (Instopword(buffer) == 0)
            {
                int flag = 0;
                for (int i = 0; i < word_num; i++)
                {
                    if (strcmp(buffer, word_counts[i].s) == 0)
                    {
                        word_counts[i].count++;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    strcpy(word_counts[word_num].s, buffer);
                    word_counts[word_num++].count = 1;
                }
            }
        }
        else if (ch == '\f')
        {

            // new article turn
            doc_sample_num++;

            fscanf(article, "%s", doc_sample[doc_sample_num].doc_no); // 向下读入下一文章序号
        }
    }
    qsort(word_counts, word_num, sizeof(struct WORD_COUNT), cmp);
}
void Read_weight(FILE *fp, int N)
{
    while ((ch = (fgetc(fp))) != EOF)
    {
        
        memset(buffer, 0, WORD_SIZE);
        if (isalpha(ch))
        {
            int i = 0;
            do
            {
                buffer[i++] = tolower(ch);
                ch = fgetc(fp);
            } while (isalpha(ch));
            ungetc(ch, fp);
            buffer[i] = 0;
            
           
            

            for (int i = 0; i < N; i++)
            {
                if (strcmp(buffer, word_counts[i].s) == 0)
                {
                    doc_article[doc_article_num1].weight[i]++;
                    break;
                }
            }
        }
        else if (ch == '\f')
        {
            // new article turn
            doc_article_num1++;
        }
    }
}
void Fingerprint(int N, int M)
{
    for (int k = 1; k < doc_article_num; k++)
    {

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if ((hash_table[j][i]-'0') > 0)
                {
                    doc_article[k].finger[i] += doc_article[k].weight[j];
                }
                else
                {
                    doc_article[k].finger[i] -= doc_article[k].weight[j];
                }
            }
            if(doc_article[k].finger[i]>0)
            doc_article[k].finger[i]=1;
            else
            doc_article[k].finger[i]=0;
        }

    }
}
void Fingerprint1(int N, int M)
{
    for (int k = 1; k < doc_sample_num; k++)
    {

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if ((hash_table[j][i]-'0') > 0)
                {
                    doc_sample[k].finger[i] += doc_sample[k].weight[j];
                }
                else
                {
                    doc_sample[k].finger[i] -= doc_sample[k].weight[j];
                }
            }
            if(doc_sample[k].finger[i]>0)
            doc_sample[k].finger[i]=1;
            else
            doc_sample[k].finger[i]=0;
        }

    }
}
void Read_weight1(FILE *fp, int N)
{
    while ((ch = (fgetc(fp))) != EOF)
    {
        
        memset(buffer, 0, WORD_SIZE);
        if (isalpha(ch))
        {
            int i = 0;
            do
            {
                buffer[i++] = tolower(ch);
                ch = fgetc(fp);
            } while (isalpha(ch));
            ungetc(ch, fp);
            buffer[i] = 0;

            for (int i = 0; i < N; i++)
            {
                if (strcmp(buffer, word_counts[i].s) == 0)
                {
                    doc_sample[doc_sample_num1].weight[i]++;
                }
            }
        }
        else if (ch == '\f')
        {
            // new article turn
            doc_sample_num1++;
        }
    }
}