#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXN 10000
#define MAXM 130
#define SIGNS 130
int flag=0;
/*特征向量长度、指纹长度*/
int N, M;

/*文本指纹数据结构*/
typedef struct fingerprint{
    char hash[130];    //指纹哈希值（01串）
    int id;              //指纹所属文本编号
}fingerprint;

fingerprint fingerprints[MAXM]; //指纹列表
int fcnt;                       //指纹总数

/*停用词数据结构*/
char stopwords[MAXN][25];   //停用词表
int snum;                   //停用词总数

/*哈希值数据结构*/
char hashvalues[MAXN][130];    //哈希值表
int hnum;                       //哈希值总数

/*特征向量数据结构*/
char features[MAXM][MAXN][25];  //特征向量数组
int freq[MAXM][MAXN];           //特征向量权值
int fnum[MAXM];                 //特征向量长度
int totalfreq[MAXM];            //特征向量总权值和

/*读入停用词*/
void read_stopwords()
{
    FILE *fp = fopen("stopwords.txt", "r");
    char word[25];
    while(fscanf(fp, "%s", word) != EOF)
    {
        strcpy(stopwords[snum++], word);
    }
    fclose(fp);
}

/*读入哈希值*/
void read_hashvalues()
{
    FILE *fp = fopen("hashvalue.txt", "r");
    char hash[SIGNS];
    while(fscanf(fp, "%s", hash) != EOF)
    {
        int i;
        for(i = 0; i < SIGNS; i++)
        {
            hashvalues[hnum][i] = hash[i];
        }
        hnum++;
    }
    fclose(fp);
}

/*判断单词是否为停用词*/
int is_stopword(char *word)
{
    int i;
    for(i = 0; i < snum; i++)
    {
        if(!strcmp(word, stopwords[i]))
            return 1;
    }
    return 0;
}

/*读入一个网页的文本数据*/
void read_doc_content(int idx, char *docname)
{
    FILE *fp = fopen(docname, "r");
    char word[25];
    while(fscanf(fp, "%s", word) != '\f')
    {
        int i;
        for(i = 0; i < strlen(word); i++)
        {
            word[i] = tolower(word[i]);  //转换为小写字母
        }
        if(!is_stopword(word))           //判断是否为停用词
        {
            int j, flag = 0;
            for(j = 0; j < fnum[idx]; j++)
            {
                if(!strcmp(word, features[idx][j])) //判断单词是否在特征向量中出现过
                {
                    flag = 1;
                    freq[idx][j]++;                 //特征向量权值加1
                    break;
                }
            }
            if(!flag && fnum[idx] < N)             //单词未出现在特征向量中且未达到特征向量维度上限N
            {
                strcpy(features[idx][fnum[idx]], word);
                freq[idx][fnum[idx]]++;
                fnum[idx]++;
            }
        }
    }
    fclose(fp);

    /*计算特征向量总权值和*/
    int j;
    for(j = 0; j < fnum[idx]; j++)
    {
        totalfreq[idx] += freq[idx][j];
    }
}

/*计算指纹哈希值*/
void calc_fingerprint()
{
    int i, j, k;
    for(i = 0; i < fcnt; i++)
    {
        char signweights[SIGNS];
        memset(signweights, 0, sizeof(signweights)); //初始化为0
        for(j = 0; j < fnum[i]; j++)
        {
            for(k = 0; k < hnum; k++)
            {
                if(!strcmp(features[i][j], hashvalues[k])) //单词的哈希值与哈希值表中某项相同时，对符号权重进行取值
                {
                    int sign = freq[i][j] > totalfreq[i] / 2 ? 1 : 0;  //计算符号
                    int l;
                    for(l = 0; l < SIGNS; l++)
                    {
                        signweights[l] += (hashvalues[k][l] == '1' ? (sign ? 1 : -1) : 0); //累加符号化权重值
                    }
                }
            }
        }
        /*根据符号化权重值计算文本指纹*/
        for(j = 0; j < SIGNS; j++)
        {
            fingerprints[fcnt].hash[j] = signweights[j] > 0 ? '1' : '0';
        }
        fingerprints[fcnt].id = i;  //指纹所属文本编号
        fcnt++;                    //指纹总数+1
    }
}

/*计算海明距离*/
int hamming_distance(char *str1, char *str2)
{
    int i, dist = 0;
    for(i = 0; i < M; i++)
    {
        if(str1[i] != str2[i])
        {
            dist++;
        }
    }
    return dist;
}

/*检测文本指纹是否在指纹列表中出现过*/
int find_fingerprint(char *hash)
{
    int i;
    for(i = 0; i < fcnt; i++)
    {
        if(!strcmp(hash, fingerprints[i].hash))
            return i;
    }
    return -1;
}

/*比较两个文本的相似度,返回汉明距离*/
int compare_docs(int idx1, int idx2)
{
    char hash[SIGNS];
    memset(hash, 0, sizeof(hash));  //初始化为0
    int i, j;
    for(i = 0; i < fnum[idx1]; i++)
    {
        for(j = 0; j < hnum; j++)
        {
            if(!strcmp(features[idx1][i], hashvalues[j]))
            {
                int sign = freq[idx1][i] > totalfreq[idx1] / 2 ? 1 : 0;
                int k;
                for(k = 0; k < SIGNS; k++)
                {
                    hash[k] += (hashvalues[j][k] == '1' ? (sign ? 1 : -1) : 0);
                }
            }
        }
    }
    /*根据符号化权重值计算第一个文本的指纹*/
    char fhash1[SIGNS];
    for(i = 0; i < SIGNS; i++)
    {
        fhash1[i] = hash[i] > 0 ? '1' : '0';
    }

    memset(hash, 0, sizeof(hash));
    for(i = 0; i < fnum[idx2]; i++)
    {
        for(j = 0; j < hnum; j++)
        {
            if(!strcmp(features[idx2][i], hashvalues[j]))
            {
                int sign = freq[idx2][i] > totalfreq[idx2] / 2 ? 1 : 0;
                int k;
                for(k = 0; k < SIGNS; k++)
                {
                    hash[k] += (hashvalues[j][k] == '1' ? (sign ? 1 : -1) : 0);
                }
            }
        }
    }
    /*根据符号化权重值计算第二个文本的指纹*/
    char fhash2[SIGNS];
    for(i = 0; i < SIGNS; i++)
    {
        fhash2[i] = hash[i] > 0 ? '1' : '0';
    }

    /*计算海明距离*/
    int dist = hamming_distance(fhash1, fhash2);
    return dist;
}

/*读入已有网页数据*/
void read_articles()
{
    FILE *fp = fopen("article1.txt", "r");
    while(1)
    {
        char docname[25];
        if(fscanf(fp, "%s", docname) == EOF)
            break;
        read_doc_content(fcnt, docname); //读入一个网页
        fcnt++;
    }
    fclose(fp);
}

/*读入待查重的网页数据*/
void read_sample_docs()
{
    FILE *fp = fopen("sample1.txt", "r");
    
    while(1)
    {
        char docname[25];
        if(fscanf(fp, "%s", docname) == EOF)
            break;
        if(flag==0)
        {
            flag=fcnt;
        }
        read_doc_content(fcnt, docname); //读入一个网页
        fcnt++;
    }
    fclose(fp);
}

int main()
{
    scanf("%d%d",&N,&M);
    
    read_stopwords();
    read_hashvalues();
    read_articles();
    read_sample_docs();

    calc_fingerprint();

    printf("%d",compare_docs(0,flag));


}