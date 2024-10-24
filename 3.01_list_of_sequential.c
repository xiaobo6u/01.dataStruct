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

#define MAXSIZE 20
typedef struct
{
        int data[MAXSIZE]; // 数据存储
        uint32_t size;     // 当前有几个元素
        uint32_t capmax;   // 线性表容量
} seqList;

/**
 * ************************************************************************
 * 数据库的经典操作：增删改查
 *
 * seqlist，应该都有哪些方法可以使用呢？
 * 1. 初始化一个list，用于存放元素
 * 2. 获取list当前有多少个元素
 * 3. 向list中插入元素，
 *      index >= size || index = -1 时，插入尾部
 *      size > index >=0 移动元素腾位插入
 * 4. 更新指定坐标位的数据
 * 5. 从list中删除元素
 *      index >= size || index = -1 时，删除尾部最后一个元素
 *      size > index >=0 删除指定元素，把其后的元素逐个往前移一位
 * 6. 查询列表元素
 *      根据index 获取指定位上的数据
 *      根据数值 获取该数值的下标
 *              从头开始查找，返回第一个匹配的index
 *              从头开始查找，返回最后一个匹配的index
 *              从头开始查找，返回所有匹配到的下标集合
 * 7. 清空链表
 * 8. 判断链表是否为空
 * 9. 判断链表是否为满
 *
 * ************************************************************************
 */

void prList(seqList *list)
{
        if (!list || !list->size)
                return;

        printf("item of list %d:\n", list->size);
        for (int i = 0; i < list->size; i++)
        {
                printf("%d ", list->data[i]);
        }
        printf("\n");
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] seq  Comment
 *
 * @return
 * ************************************************************************
 */
static int seqlist_get_size(void *seq)
{
        seqList *list = seq;

        /*1. 判断链表指针是否不对*/
        if (!seq)
        {
                printf("seq list is null\n");
                return -1;
        }

        return list->size;
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] seq  Comment
 * @param[in] index  Comment
 * @param[in] data  Comment
 *
 * @return
 * ************************************************************************
 */
static int seqlist_insert(void *seq, int index, int data)
{
        int ret = 0, i = 0;
        seqList *list = seq;

        /*1. 判断链表指针是否不对*/
        if (!seq)
        {
                printf("seq list is null\n");
                return -1;
        }

        /*2. 判断链表是否满*/
        if (list->size >= list->capmax)
        {
                printf("seq list is full\n");
                return -1;
        }

        /*3. 如果index=-1，则插尾部*/
        i = list->size;
        if (index != -1)
        {
                /*4. 在指定位置插入元素*/
                do
                {
                        /**
                         * Note:
                         *
                         * 大多数运算符结合方向 是“自左至右”, 即: 先左后右, 例如 a - b + c , b 两侧有 - 和 + 两种运算符的优先级相同,
                         * 按先左后右结合方向, b 先与减号结合, 执行a - b 的运算, 再执行加 c 的运算。
                         *
                         * 除了自左至右的结合性外, C 语言有 三类运算符 参与运算的结合方向是从右至左。即: 单目运算符, 条件运算符, 赋值运算符。
                         * 比如，右结合（从右到左），那就是，把右边的运算用括号先括起来，再与左边的进行计算，这样自然是先执行右边的了。
                         *
                         * int a,b=1,c=2;
                         * a=b=c;
                         * 这里 =的结合性是 从右到左 。 故 a=b=c; 可变为 a=(b=c); 即 a 最终为 2。
                         */
                        list->data[i--] = list->data[i - 1];
                } while (i > 0 && i >= index);
        }
        list->data[i] = data;
        list->size++;
        // prList(list);
        return 0;
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] seq  Comment
 * @param[in] index  Comment
 * @param[in] data  Comment
 *
 * @return
 * ************************************************************************
 */
static int seqlist_update(void *seq, int index, int data)
{
        seqList *list = seq;

        /*1. 判断链表指针是否不对*/
        if (!seq)
        {
                printf("seq list is null\n");
                return -1;
        }

        /*如果index >= size，则在尾部插入新元素*/
        if (index >= 0 && index < list->size)
        {
                list->data[index] = data;
        }
        /*如果index=-1，则更新最后一个元素数值*/
        else if (index == -1)
        {
                list->data[list->size - 1] = data;
        }
        else
        {
                if (list->size >= list->capmax)
                {
                        printf("seq list is full, but the index outof range\n");
                        return -1;
                }
                list->data[list->size++] = data;
        }
        return 0;
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] seq  Comment
 * @param[in] index  Comment
 *
 * @return
 * ************************************************************************
 */
static int seqlist_remove_by_index(void *seq, int index)
{
        int i = 0;
        seqList *list = seq;

        /*1. 判断链表指针是否不对*/
        if (!seq)
        {
                printf("seq list is null\n");
                return -1;
        }

        if (index >= list->size)
        {
                printf("index outof range of seqlist, remove fail\n");
                return -1;
        }

        if (index == -1)
        {
                list->size--;
                return 0;
        }

        i = index;
        do
        {
                list->data[i++] = list->data[i + 1];
        } while (i < list->size - 1);
        list->size--;
        return 0;
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] seq  Comment
 * @param[in] data  Comment
 *
 * @return
 * ************************************************************************
 */
static int seqlist_remove_by_data(void *seq, int data)
{
        int i = 0, start = 0;
        seqList *list = seq;

        /*1. 判断链表指针是否不对*/
        if (!seq)
        {
                printf("seq list is null\n");
                return -1;
        }

        /*获取data 所在的index*/
        do
        {
                if (data == list->data[i])
                {
                        start = i;
                        break;
                }
        } while ((++i) < list->size);

        if (i >= list->size && !start)
        {
                return -1;
        }

        /*删除目标元素*/
        do
        {
                list->data[start++] = list->data[start + 1];
        } while (start < list->size - 1);
        list->size--;
        return 0;
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] seq  Comment
 * @param[in] data  Comment
 *
 * @return
 * ************************************************************************
 */
static int seqlist_remove_all_data(void *seq, int data)
{
        int ret = 0;
        /*1. 判断链表指针是否不对*/
        if (!seq)
        {
                printf("seq list is null\n");
                return -1;
        }

        do
        {
                ret = seqlist_remove_by_data(seq, data);
        } while (!ret);

        return 0;
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] seq  Comment
 * @param[in] index  Comment
 *
 * @return
 * ************************************************************************
 */
static int seqlist_query_by_index(void *seq, int index)
{
        seqList *list = seq;

        /*1. 判断链表指针是否不对*/
        if (!seq)
        {
                printf("seq list is null\n");
                return -1;
        }

        if (index < 0 || index >= list->size)
        {
                printf("index outof range, query fail\n");
                return -1;
        }

        return list->data[index];
}

/**
 * ************************************************************************
 * @brief
 *
 * @param[in] argc  Comment
 * @param[in] argv  Comment
 *
 * @return
 * ************************************************************************
 */
int main(int argc, char const *argv[])
{
        seqList list = {.size = 0, .capmax = MAXSIZE}; // size一定要初始化
        int i = 0, cnt = 10;

        /* 1 初始化线性表*/
        for (i = 0; i < cnt && i < MAXSIZE; i++)
        {
                /*int rand(void); 返回一个 0~RAND_MAX 之间的整数，RAND_MAX一般是32767*/
                list.data[i] = rand() % 100;
                list.size++;
        }
        prList(&list);

        /*插入测试*/
        seqlist_insert(&list, 0, 11);

        /*获取当前元素个数*/
        printf("seq list has %d item\n", seqlist_get_size(&list));

        /*更新元素*/
        prList(&list);
        seqlist_update(&list, 0, 10);
        prList(&list);

        seqlist_remove_by_index(&list, 0);
        prList(&list);

        seqlist_remove_by_data(&list, 11);
        prList(&list);

        seqlist_remove_all_data(&list, 10);
        prList(&list);

        seqlist_query_by_index(&list, 0);
        return 0;
}
