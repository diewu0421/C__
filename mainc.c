//
// Created by zenglingwen on 2020/3/23.
//

#include "a.h"
//void test3() {}

void change1(int i) {
    i = 10;
}

void change2(int *i) {
    *i = 10;
}

void change3(int **i) {
//    i = 10;
    int j = 10;
    *i = &j;
}

#include <stdarg.h>

#pragma pack(2)
struct Student1 {

//    char name[10];
    short j;
    int i;
    short k;

} s1, s2;

#pragma pack()

void add(int num, ...) {

    va_list list;
    va_start(list, num);

    for (int i = 0; i < 5; ++i) {
        int j = va_arg(list, int);
        printf("\n可变参数 = %d\n", j);
    }
    char c = va_arg(list, char);
    printf("可变参数有%c\n", c);
}

/**
 * void (*p)(char*)
 * void 返回值
 * (*p) p变量用来表示这个函数
 * （char* ） 参数列表
 * @param p
 * @param param
 */
typedef void (*Func)(char *);

void say(Func func, char *param) {
    func(param);
}

void println(char *param) {
    printf(param);
}

#ifndef ZENGLW

#include <string.h>

#define  ZENGLW "100"

#endif

#define ADD(a, b) a * b

void test3() {
    printf("我是test3 在c中的实现");
}

void test(int a, int b) {
    printf("a = %d b = %d", a, b);
}

void test2(const char* string) {
    while (*string) {
        printf("加一之前%c", *string);
//        printf("%c", *string++);
        string++;
    }
}

/**
 * 共用体
 * 相同起始位置
 * 作用：
 * 只能有一个值
 * 大小和共用体中最长的字节是一样的
 * 举个例子: 比如有一个int和short 那么字节大小就和int保持一致
 *
 */
union MyUnion {
    short i;
    int j;
};
int main222() {
    if (1) {
        union MyUnion myUnion;
        myUnion.i = 10;
        printf("%d\n", myUnion.i);
        myUnion.j = 11;
        printf("%d\n", myUnion.j);
        printf("%d\n", myUnion.i);
        return 0;
    }

    if (1) {
        printf("sizeof is %lu", sizeof(struct Student1));
        return 0;
    }

    if (1) {
        char str[10] = "name";
        strcat(str, "11111");
//        printf("str = %s", str);
        say(println, str);
    }

    test2("\n-0----> Hello\n");

    char str[100];
    sprintf(str, "\n%d=%d\n", 100, 101);
    printf("str is %s", str);

    int c = ADD(1 + 10, 10 + 1);
    printf("a = %d", c);

    test(3, 5);

//    char* str = "11\n";
    int a[] = {11, 22, 33};

    int *arr = a;

//    printf("value = %d", *(a + 1));
//
//    for (int i = 0; i < 3; ++i) {
//        printf("value = %d\n", *arr++);
//    }
//    int array2[2][3] = {{11,22,33},{44,55,66}};
//    int (*arra2_p2)[3] = array2;
//    printf("二维 %d", array2[1][2]);
//
//    printf("11111111  %d", *(*++arra2_p2 + 1));


    int b = 3;
    int *p_array[3] = {&b, &b, &b};


//    printf("end");

    char tem[] = "hello";
    // 从右往左看，这里的p2是一个指针，
    // 是一个指向const char的指针，既然是const char 所以不能通过p2修改里面的内容，但是可以重新指向
    const char *p2 = tem;
    // 不可以
//    *p2 = 'z';
    p2 = "new hello";

    // 这里的const修饰的char，不能修饰*，所以这里和p2是一样的
    char const *p3 = tem;

    char *const p4 = tem;
    // no
    // p4 = NULL;
    // 可以修改
    p4[0] = 'a';

    // p5 和 p6一样，什么都不能修改
    const char *const p5 = tem;
    char const *const p6 = tem;

    // 多级指针
//    int i2 = 10;
//    int *p7 = &i2;
//    int **p8 = &p7;
//    printf("i2 = %d", **p8);
//
//    printf("%c", *p2);

    int i3 = 1;

    // 修改是内存地址的值
    change2(&i3);
    printf("change2 i3=%d\n", i3);
    int *p9 = &i3;
    // p9重新指向
    change3(&p9);
    printf("i3 = %d", *p9);

    add(5, 1, 2, 3, 4, 5, 'a');

    return 0;
}

