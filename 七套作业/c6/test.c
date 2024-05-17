#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE   10007   /* Hash数组大小 */
#define MAX_WORD_LEN    256 /* 单词最大长度 */

typedef struct word_item {
    char* word;     /* 单词字符串 */
    int count;      /* 单词出现次数 */
    struct word_item* next; /* Hash冲突时的链表指针 */
} word_item;

unsigned int hash(char* str) {
    /* 求出字符串对应的Hash值 */
    unsigned int h = 0;
    while (*str) {
        h = *str + (h << 6) + (h << 16) - h;
        str++;
    }
    return h % HASH_SIZE;
}

word_item* find_word(word_item** table, char* word) {
    /* 在Hash表中查找单词 */
    unsigned int h = hash(word);
    word_item* node = table[h];
    while (node != NULL) {
        if (strcmp(node->word, word) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void insert_word(word_item** table, char* word) {
    /* 向Hash表中插入单词 */
    unsigned int h = hash(word);
    word_item* node = table[h];
    while (node != NULL) {
        if (strcmp(node->word, word) == 0) {
            node->count++;
            return;
        }
        node = node->next;
    }
    /* 如果单词不存在，则新增一个节点 */
    node = (word_item*)malloc(sizeof(word_item));
    node->word = (char*)malloc(strlen(word) + 1);
    strcpy(node->word, word);
    node->count = 1;
    node->next = table[h];
    table[h] = node;
}

void destroy_word_table(word_item** table) {
    /* 销毁Hash表 */
    int i;
    word_item* p, *q;
    for (i = 0; i < HASH_SIZE; i++) {
        p = table[i];
        while (p != NULL) {
            q = p;
            p = p->next;
            free(q->word);
            free(q);
        }
        table[i] = NULL;
    }
}

void print_topn_words(word_item** table, int n) {
    /* 输出出现频率最高的前N个单词 */
    word_item** topn = (word_item**)malloc(n * sizeof(word_item*));
    memset(topn, 0, n * sizeof(word_item*));
    int i, j;
    word_item* node;
    for (i = 0; i < HASH_SIZE; i++) {
        node = table[i];
        while (node != NULL) {
            for (j = 0; j < n; j++) {
                if (topn[j] == NULL || node->count > topn[j]->count) {
                    /* 如果该单词的出现频率高于前N个单词中的某个单词，则替换之 */
                    memmove(&topn[j + 1], &topn[j], (n - j - 1) * sizeof(word_item*));
                    topn[j] = node;
                    break;
                }
            }
            node = node->next;
        }
    }
    /* 输出前N个单词及其出现次数 */
    for (i = 0; i < n; i++) {
        if (topn[i] == NULL) {
            break;
        }
        printf("%s: %d\n", topn[i]->word, topn[i]->count);
    }
    free(topn);
}

int main() {
    char text[1024], word[MAX_WORD_LEN];
    int i, len;
    word_item* table[HASH_SIZE] = { NULL };
    /* 读取输入文本，处理单词，并插入到Hash表中 */
    while (fgets(text, 1024, stdin)) {
        len = strlen(text);
        for (i = 0; i < len; i++) {
            if (isalpha(text[i])) {
                /* 将字母转化为小写，并记录到word数组中 */
                word[0] = tolower(text[i]);
                for (len = 1; i + 1 < len && isalpha(text[i + 1]); i++, len++) {
                    word[len] = tolower(text[i + 1]);
                }
                word[len] = '\0';
                insert_word(table, word);
            }
        }
    }
    /* 输出出现频率最高的前N个单词 */
    print_topn_words(table, 10);
    /* 销毁Hash表 */
    destroy_word_table(table);
    return 0;
}