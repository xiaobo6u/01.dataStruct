/**
 * ************************************************************************
 * @copyright Copyright (c) 2024
 * For study and research only, no reprinting
 *
 * @par        changelist:
 * Date          Author      Version   Description
 * 2024-10-23    tianzong    1.0       first edition
 * ************************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

/**
 * int rand(void); 返回一个 0~RAND_MAX 之间的整数，RAND_MAX一般是32767
 */
#define MAXSIZE 20
typedef struct
{
        int data[MAXSIZE]; // 数据存储
        uint32_t size;     // 当前有几个元素
} seqList;

void prList(seqList *list)
{
        if (!list || !list->size)
                return;

        printf("item of list:\n");
        for (int i = 0; i < list->size; i++)
        {
                printf("%d ", list->data[i]);
        }
        printf("\n");
}

int main(int argc, char const *argv[])
{
        seqList list = {.size = 0}; // size一定要初始化
        int i = 0, cnt = 100;

        /* 1 初始化线性表*/
        for (i = 0; i < cnt && i < MAXSIZE; i++)
        {
                list.data[i] = rand() % 100;
                list.size++;
        }
        prList(&list);
        /* code */
        return 0;
}
