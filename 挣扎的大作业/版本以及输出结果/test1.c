/*声明:
v0-1 初代数据结构: 三个字典树, 未使用topk算法仅qsort全部数据
v0-1:修改了浮点数比较, 确定了版本号
v0-2:(final) 修改: 1. simd为0的数据不进行输出, 这是题目隐含条件 2. 稍优化了各个数据域开辟内存大小
    [!消息] 小数据第一个点就是样例
---
大数据失败? 看了论坛大致是读入的处理问题, 可能是\r\n, 也可能是部分字符大于char型
v1-0:
    1. 修改了fgets读入大小为LINE_SIZE, 使其与宏定义/数组大小等适配.
    2. 检查dict和stopWord字典树对最后字符的读入, 确认没有隐患
    3. 修改了主函数的逻辑漏洞
v1-1:
    1. [Deleted/[!消息],关键词最大也就十来个] single_doc_key_freq截断后拼接, 防止数组过大无法开辟
    2. 将部分超大数组的游标类型从int改为long long
    3. 大修"读入文章"部分结构和读入方法:
        - [尚未完成] 优化buffer, ftell返回大小然后动态开辟, 节省空间和时间. 换掉fgets(目前在权衡fread和fgetc)
        - [尚未完成] 处理字符编码问题, 可能存在超出单字节的多字节字符(甚至有EOF)
    4. [Deleted/未检查出问题] 检查读入问题: \r\n, 字符超过char, 文档某处有多个(无意义)\f造成文档读多(一般是最后)
v1-2: 主版本, 使用fread读入整个文件, 入动态开辟数组中. 处理utf-8编码. -- 小数据成功/大数据仍失败
v1-2-1: 支线/实验版, 使用fgetc 
----
(支线变主线？？doge)
v2-1: v1-2-1版本修改了部分\f位置的特殊情况(可能在文章末或编号前， 不要跳读), 通过大数据 1.2s左右, 并更换为主线版本的堆排序
v2-1-1: v1-3版本修正\f和跳字符后通过大数据。时间为1.3s左右, 并入fgetc方法, 整个读入文件并不能带来速度明显提升。
----
未来计划:
1. 在topk堆排序中， 当比较次数多于两次时就进行拆半查找
2. 在v2版本(扩展性)中, 因为不必考虑时间因素, 将所有开辟的内存全部改换为动态内存
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
// #include<windows.h>
#include<math.h>
// #include<time.h>

//size部分
#define KEY_SIZE 100//关键词最多大概不超过十个, 但扩展性不保证
#define DOC_SIZE 300000
#define KEY_TRIE_SIZE 30000
#define DICT_TRIE_SIZE 3000000
#define STOP_TRIE_SIZE 100000
#define BUFFER_SIZE 500
#define WORD_SIZE 50//字典中单词长度
typedef int POS;
#define EPSILON 1e-6//比较浮点数
#define WORD_COUNTS_SIZE 10000
//info部分
int key_num;
long long doc_num;
struct KEY_WORD {
    //固有数据
    char word[WORD_SIZE];
    int key_appear_doc_num;
    double anti_key_freq;
    //浮动数据
    int single_doc_key_num;
    int single_state;//现在记录的是哪篇文章
}key[KEY_SIZE];//以key_num为游标, 从1开始
double single_doc_key_freq[DOC_SIZE][KEY_SIZE];//实在开辟不了太大, 就拆分开再重组

struct WEBSITE {
    int no_num;//编号
    char no_serial[30];//文档内编号
    double doc_sim;
}doc[DOC_SIZE];//从1开始
struct WORD_COUNT
{
    char s[30];
    int count;

} word_counts[WORD_COUNTS_SIZE];
//预处理部分: 构建词典 字典树
enum BOOL { F, T };
enum BOOL InDict( char * );
enum BOOL InStopDict( char * );
void CreateDictTrie( );
void CreateStopTrie( );
int dict_trie[DICT_TRIE_SIZE][30];
int stop_trie[KEY_TRIE_SIZE][30];
int flag_dict_trie[DICT_TRIE_SIZE];
int flag_stop_trie[STOP_TRIE_SIZE];
int total_dict_trie;
int total_stop_trie;


//字典树例程

void Insert( int( *trie )[30], int *flag, int *total, char *str );
int Find( int( *trie )[30], int *flag, int *total, char *str );
//处理文章例程
char *StrConstCpy( char *source, int len );
void ReadSerial( char *dest, FILE *fp );
/* topk例程 */
typedef struct WEBSITE WEB;
typedef WEB *WEB_;
WEB_ *CreateHeap( const int heapSize );
void UpdateStableHeap( WEB_ *heap, const int heapSize,
    WEB_ x, int ( *Cmp )( WEB_ fst, WEB_ sec ) );
int Cmp( WEB_ a, WEB_ b );


int main( int argc, char *argv[] ) {//in -> "100","edu","news","article"
    int ch;
    long long i, j, tail, word_num = 0, result_num;
    FILE *fp_in_article, *fp_out;
    char buffer[BUFFER_SIZE];
    WEB_ *indexL;//topk索引表
    /*测时结构*/
    /* lock_t start, end;
    start = clock( ); */
    CreateDictTrie( );
    CreateStopTrie( );
    fp_out = fopen( "results.txt", "w" );
    //read in whole file
    // fp_in_article = fopen( "F:\\notes\\assign\\bonus\\reference\\article.txt", "r" );
    fp_in_article = fopen( "article.txt", "r" );

    

    //读入
    doc_num = 1;
    ReadSerial( doc[doc_num].no_serial, fp_in_article );   
    while ( ( ch = fgetc( fp_in_article ) ) != EOF )
    {
        if ( isalpha( ch ) ) {
            //向后读单个单词
            i = 0;
            do {
                buffer[i++] = tolower( ch );
                ch = fgetc( fp_in_article );
            }
            while ( isalpha( ch ) );
            ungetc( ch, fp_in_article );
            buffer[i] = 0;
            
            
        }

        else if ( ch == '\f' ) {
            //last article
            doc[doc_num].no_num = doc_num;
            for ( i = 1; i <= key_num; i++ )
                if ( key[i].single_state == doc_num )
                    single_doc_key_freq[doc_num][i]
                        = 100 * ( double )key[i].single_doc_key_num / word_num;
            //new article turn
            doc_num++;
            fgetc( fp_in_article );//读入\n
            ReadSerial( doc[doc_num].no_serial, fp_in_article );//向下读入下一文章序号
            word_num = 0;//重置词数
        }
    }
    
   
}

//返回该单词最终位置
void Insert( int( *trie )[30], int *flag, int *total, char *str ) {
    int len = strlen( str );
    int i, id;
    int parent = 0;
    //!未检查是否溢出
    for ( i = 0; i < len; i++ ) {
        id = str[i] - 'a' + 1;
        if ( !trie[parent][id] )
            trie[parent][id] = ++*total;
        parent = trie[parent][id];//ptr down
    }
    flag[parent] = 1;
    
}

int Find( int( *trie )[30], int *flag, int *total, char *str ) {
    int len = strlen( str );
    int parent = 0, i, id;
    for ( i = 0; i < len; i++ ) {
        id = str[i] - 'a' + 1;
        if ( !trie[parent][id] )
            return 0;//0空间没有用, 代表空
        parent = trie[parent][id];//游标下沉
    }
    if ( flag[parent] )//是词尾
        return parent;
    else
        return 0;
}
void getword()
{
    for(int i=1;i<=total_dict_trie;i++)
    {
        
    }
}


void CreateDictTrie( ) {
    FILE *fp_in_dict;
    char word[WORD_SIZE];
    // fp_in_dict = fopen( "F:\\notes\\assign\\bonus\\reference\\dictionary.txt", "r" );
    fp_in_dict = fopen( "article.txt", "r" );
    char ch;
    char buffer[WORD_SIZE];
    while ( ( ch = fgetc( fp_in_dict ) ) != EOF )
    {
        if ( isalpha( ch ) ) {
            //向后读单个单词
            int i = 0;
            do {
                buffer[i++] = tolower( ch );
                ch = fgetc( fp_in_dict );
            }
            while ( isalpha( ch ) );
            ungetc( ch, fp_in_dict );
            buffer[i] = 0;

            //入树
            if ( !InStopDict( buffer )  ) {
                if(InDict(buffer))
                {
                    flag_dict_trie[Find(dict_trie,flag_dict_trie,total_dict_trie,buffer)]++;
                }
                else
                {
                    Insert(dict_trie,flag_dict_trie,total_dict_trie,buffer);
                }
            }
            
        }
       
    }
    while ( fscanf( fp_in_dict, "%s", word ) != EOF )
        Insert( dict_trie, flag_dict_trie, &total_dict_trie, word );
    fclose( fp_in_dict );
    return;
}

void CreateStopTrie( ) {
    FILE *fp_in_stop;
    char word[WORD_SIZE];
    // fp_in_stop = fopen( "F:\\notes\\assign\\bonus\\reference\\stopwords.txt", "r" );
    fp_in_stop = fopen( "stopwords.txt", "r" );
    while ( fscanf( fp_in_stop, "%s", word ) != EOF )
        Insert( stop_trie, flag_stop_trie, &total_stop_trie, word );
    fclose( fp_in_stop );
}

enum BOOL InDict( char *word ) {
    int in = Find( dict_trie, flag_dict_trie, &total_dict_trie, word );
    if ( in )
        return T;
    else
        return F;
}
enum BOOL InStopDict( char *word ) {
    int in = Find( stop_trie, flag_stop_trie, &total_stop_trie, word );
    if ( in )
        return T;
    else
        return F;
}





