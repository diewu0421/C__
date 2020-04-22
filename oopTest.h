//
// Created by zenglingwen on 2020/4/6.
//
#pragma once
#ifndef C___OOPTEST_H
#define C___OOPTEST_H

#include <iostream>

using namespace std;

class Student {
    int i;
    int j;

    // 友元函数
    friend void test(Student *);

    friend class StudentHelper;

public:
    Student(int i, int j);

    ~Student();

//    void setName();

    char *getName() {
        return name;
    }

private:

    char *name;
};


class StudentHelper {
public:
    void operateStudent(Student *student) {
        student->name = "asfdasdf";
    }
};

// c++单例

class Instance {
private:
    Instance();

    static Instance *instance;

public:
    static Instance *getInstance();

    static void destroyInstance();

    ~Instance() {
        printf("释放 Instance\n");
    }
};

class Test1 {

public:
    int i;

    Test1() {

        this->i = 0;
    }

    ~Test1() {
        cout << "Test 析构 " << endl;
    }

    Test1(const Test1 &test1) {

        this->i = test1.i;
        cout << "拷贝构造函数" << endl;
    }

    Test1 operator+(const Test1 &test1) {
        Test1 temp;
        temp.i = test1.i + this->i;
        return temp;
    }

};

class A {
public:
    A(char *name) {
        this->name = (char *) malloc(strlen(name) + 1);
        memcpy(this->name, "hell", strlen(name) + 1);
    }

    char *name;
};

class Parent {
public:
    virtual void test() {
        cout << "parent" << endl;
    }

    Parent() {

        cout << "parent con" << endl;
    }

    virtual ~Parent() {
        cout << "parent xigou "<< endl;
    }

protected:
    int i = 1234;

    int getI() {
        return i;
    }

};

class Parent2 {
protected:
    void test2() {
        cout << "test2 " << endl;
    }
};

class Child : public Parent, private Parent2 {

private:
//    void test() {
//        i = 10;
//        test2();
//    }

public:
    void test() override {
        cout << "child" << endl;
    }

public:

    Child() {
        cout << "child con" << endl;

    }

    ~Child() override {

        cout << "child 析构" << endl;
    }

    int getI() {
        return 10;
    }
};

template<typename T>
void testTTemplate(T t) {
    cout << "t = " << t << endl;
}



#endif //C___OOPTEST_H

