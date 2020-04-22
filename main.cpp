#include <iostream>

//#include "a.h"
#ifdef __cplusplus
extern "C" {

#include "b.h"
#endif

#ifdef __cplusplus
}
#endif
using namespace std;

int ii;

int main1() {

    ii = 11;
    int ii = 10;
    cout << ii << endl;
    cout << ::ii << endl;
    ::ii = 88;
    ii = 99;
    cout << ii << endl;
    cout << ::ii << endl;

    if (__cplusplus < 201103L) {
        printf("not support");
    } else {
        printf("support %ld\n", __cplusplus);
    }

    // 1. c 与 c++兼容
//    printf("Hello World!");

    // 字符串
    char str1[6] = {'h', 'e', 'l', '\0'};
    cout << str1 << endl;
    char *str2 = "hello";
    cout << str2 <<endl;
    cout << *(str2 +5) << endl;

    char str3[10];
//    strcpy(str3, str1);
    cout << "str3 = " << str3 << endl;
    string str4(str1);

//    str4 = "asdf11111111";
//    str4.empty();

    cout << "str4 = " << str4 << "  size = " << str4.size() << endl;


//    auto *str5 = new string;

    auto *str5 = new string;

//    strcat(reinterpret_cast<char *>(str5), "我是str5");
//
//    string str6 = str5 + str4;
//    cout << "str6 = " << str6 << endl;
//    str5

    str5->append("haha");


    cout << "str5 = " << *str5 << endl;

    delete str5;


//    string str6 =

//    test3();
    testb();
    return 0;
}
