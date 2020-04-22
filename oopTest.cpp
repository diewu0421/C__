//
// Created by zenglingwen on 2020/4/6.
//

#include <vector>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include "oopTest.h"
#include <iostream>
#include <fstream>

using namespace std;
#ifndef ZENGLW

#define  ZENGLW

#endif
#ifdef ZENGLW

#define PI 3.14

#endif


void test(Student *student);

Instance *Instance::instance = nullptr;

Instance::Instance() {

    cout << " Instance constructor" << endl;
}

Instance *Instance::getInstance() {
    // C++11 编译器 保证内部静态变量的线程安全
    if (!instance) {
        instance = new Instance();
    }
    return instance;
}

void Instance::destroyInstance() {
    delete instance;
}

vector<int> globalVec;

class Type {
public:
    Type(int i) : i(i) {}

    int i;
};

struct TypeLess {
    bool operator()(const Type &__x, const Type &__y) const { return __x.i > __y.i; }
};


void testException() {
    throw Parent();
}

void testFile() {

    cout << "PI = " << PI << endl;

    char path[50] = "/Users/apple/Desktop/test.txt";
    FILE *f = fopen(path, "w");
    fprintf(f, "I go to %d 技师", 88);
    fclose(f);


    f = fopen("/Users/apple/Desktop/test.txt", "r");
    char buffer[1025];

//    while (!feof(f)) {
//        fscanf(f, "%s",buffer);
//
//        cout << "读取文件n: " << buffer << endl;
//    }

    fgets(buffer, 1024, f);

    cout << "读取文件n: " << buffer << endl;

    fclose(f);
    cout << "--------------------------------" << endl;

    ofstream oFile;
    oFile.open(path);

    char data[50];

    cin >> data;
    oFile << data << endl;

    oFile.close();

    ifstream inFile;

    inFile.open(path);
    inFile >> data;
    cout << "读取的文件为 " << data << endl;

    cout << "--------------------------------" << endl;


}

void vectorTest() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(3);

    auto it = vec.begin();

    while (it != vec.end()) {

        cout << *it++ << endl;
    }

    it = vec.begin();
}

#include <pthread.h>
#include <thread>

void *threadRunnable(void *param) {
    int *p = static_cast<int *>(param);
    cout << "thread RUnnable param = " << *p << endl;
}


void testThread() {
    pthread_t pid;
    int i = 100;

    pthread_attr_t attr;

    pthread_attr_init(&attr);
    // 分离线程
    // 默认为非分离线程
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//    pthread_attr_setschedparam(&attr, )

    pthread_create(&pid, &attr, threadRunnable, &i);
    pthread_join(pid, nullptr);

    pthread_attr_destroy(&attr);
    cout << "线程执行完毕" << endl;
}


pthread_mutex_t mutex1;

queue<int> q;

void *takeQueue(void *param) {
    pthread_mutex_lock(&mutex1);
    if (!q.empty()) {
        cout << "取出数据: " << q.front() << endl;
        q.pop();
    } else {
        cout << "数据为空" << endl;
    }
    pthread_mutex_unlock(&mutex1);
    return nullptr;
}

void testMutex() {
    pthread_mutex_init(&mutex1, nullptr);

    for (size_t i = 0; i < 5; ++i) {
        q.push(i);
    }

    pthread_t pids[10];

    for (pthread_t &pid : pids) {
//        pthread_attr_t attr;
//
//        pthread_attr_init(&attr);

//        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&pid, 0, takeQueue, nullptr);
//        pthread_join(pid, nullptr);
//        pthread_attr_destroy(&attr);
    }

    pthread_mutex_destroy(&mutex1);
}

template<typename T>
class SafeQueue {

public:
    SafeQueue() {
        pthread_mutex_init(&mutex, 0);
        pthread_cond_init(&cond, 0);
    }


    ~SafeQueue() {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }

    // 生产数据
    void push(T t) {
        pthread_mutex_lock(&mutex);
        q.push(t);
//        pthread_cond_signal(&cond);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    // 取数据
    void pop(T &t) {

        pthread_mutex_lock(&mutex);
//        if (q.empty()) {
//            t = q.front();
//            q.pop();
//        }

        while (q.empty()) {
            pthread_cond_wait(&cond, &mutex);
        }
        t = q.front();
        q.pop();
        pthread_mutex_unlock(&mutex);
    }

private:
    queue<T> q;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

};

SafeQueue<int> safeQueue;

void *product(void *param) {
    while (1) {
        int i;

//        try {

cout << "输入i的值: " ;
            cin >> i;
//            cout << "i = " << i << endl;

//            safeQueue.push(i);
//        } catch (exception) {
//
//            cout << "有意查呢" << endl;
//        }
//        cout << "i的值为 " << i << endl;
//        if (!isnumber(i)) {
//            cout << "输入有误，不是数字" << endl;
//        } else {
        safeQueue.push(i);
//        }
    }
}

void *consumer(void *param) {

    while (1) {
        int i;
        safeQueue.pop(i);
        cout << "取出的数据位: " << i << endl;
    }
}


void testSafeQueue() {

//    auto safeQueue = SafeQueue<int>();
//    safeQueue.push(1);

cout << "start " << endl;
    pthread_t pid1, pid2;
    pthread_create(&pid1, 0, product, 0);
    pthread_create(&pid2, 0, consumer, 0);
    pthread_join(pid1, 0);
//    pthread_join(pid2, 0);

}

class SmartPointer {

public:
    ~SmartPointer() {

        cout << " 析构 " << endl;
    }
};


class BB;
class AA {
public:
    ~AA() {
        cout << "释放AA " << endl;
    }

    weak_ptr<BB> b;
};

class BB {
public:
    ~BB() {
        cout << "释放BB " << endl;
    }

    // 不会引起引入技术加1
    weak_ptr<AA> a;
};
void smartPointer() {

//    SmartPointer *pointer = new SmartPointer;
//
////    shared_ptr<SmartPointer> sharedPtr(&pointer);
//
////    delete pointer;
//
//    shared_ptr<SmartPointer> sharedPtr(pointer);
//    shared_ptr<SmartPointer> sharedPtr2(pointer);

    shared_ptr<AA> a(new AA);
    shared_ptr<BB> b(new BB);

    cout << "AA 引入技术为 " << a.use_count()<< endl;
    a->b = b;
    b->a = a;
    cout << "AA 引入技术为 " << a.use_count()<< endl;
    auto i = 5;
// [&] 表示外部变量都以引用的形式在lambda中使用，函数内部修改i的值会影响外部
// 这里的 -> auto 自动推导在c++11不支持，c++14中对auto进行了扩展

}

void testLambda(void  (* param)()) {

    param();
}

class AAA {
public:
    ~AAA() {
        cout << "释放AAA " << endl;
    }
};

template <typename  T>
class Ptr {
public:
    Ptr(){

        count = new int(1);
        this->t = nullptr;
    }

    Ptr(T* t) {
        count = new int(1);
        this->t = t;
    }
    ~Ptr() {

        --(*count);
        if (*count == 0) {
            if (t) {
                delete t;
                t = nullptr;
            }
            delete count;
            count = nullptr;
        }
    }


    Ptr<T> &operator=(const Ptr<T> &ptr) {
        cout << "Operator" << endl;
        (*ptr.count)++;

        if (--(*count) == 0) {
            if (t) {
                delete t;
                t = nullptr;
            }
        }

        this->count = ptr.count;
        this->t = ptr.t;
        return *this;

    }


private:
    int* count;
    T *t;
};

int main() {


    AAA* a1 = new AAA;
    AAA* a2 = new AAA;

    Ptr<AAA> ptr(a1);

    Ptr<AAA> ptr1(a2);
    ptr1 = ptr;

    return 0;
    smartPointer();
//    testSafeQueue();
    return 0;
    testMutex();
//    cout  << "end" << endl;

    for (int i = 0; i < 10000000; ++i) {
//        cout << endl;
    }
    return 0;
    testThread();
    return 0;
//    vectorTest();
//    testFile();
//    try {
//        testException();
//    } catch (Parent &parent1) {
//        cout << "exception";
//    }

    cout << "herer" << endl;
//    Student student(10, 20);

//    student.setName();
//    cout << student.name << endl;


//    auto *student = new Student(1, 2);
//    Student student(1, 2);
//    Student *p = &student;
//    test(p);
//    cout << " name = " << student.getName() << endl;
//
//    StudentHelper helper;
//    helper.operateStudent(p);
//
//    cout << " name = " << student.getName() << endl;
//
//    Instance* instance = Instance::getInstance();
//
//    cout << instance << endl;
//    cout << Instance::getInstance() << endl;
//
//    Instance::destroyInstance();
//
//    cout << "________________________" <<endl;
//    Test1 test1;
//    test1.i = 100;
//    Test1 test2;
//
//    test2.i = 200;
//    Test1 test3 = test1 + test2;
//    cout << "test3 i " << test3.i << endl;
//
//    cout << "____________________" << endl;
//    char *name = (char *) malloc(sizeof(100));
////    name = "niaf";
//    A a(name);
//    cout << "a.nname = " << a.name << endl;
//
//    free(name);
//
//    Parent *pp = new Child;
//    pp->test();
//    delete pp;
//
//
////    cout << child.getI() << endl;
//
//
//    testTTemplate("aaaaaa");

    vector<int> vec;

    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(2);
//    cout << vec[0] << endl;
//
//    cout << vec.at(1) << endl;
//
//    cout << vec.front() << endl;
//    cout << vec.back() << endl;
//
////    vec.clear()
//    cout << "capcity " << vec.capacity() << endl;
//    vec.erase(vec.begin(), vec.end());
//
////    vec.swap()
//    vector<int>().swap(vec);
//    cout << "capcity " << vec.capacity() << endl;
//    cout << vec.size() << endl;
//


//    queue<int> q;
//    q.push(1);
//    q.push(3);
//    q.push(2);
//
//    cout << q.back() << endl;


    priority_queue<Type, vector<Type>, TypeLess> pq;
//    pq.push(2);
//    pq.push(1);
//    pq.push(3);

//    cout << pq.top() << endl;
//    pq.push(3);
//    pq.push(1);
//    pq.push(2);
    pq.push(Type(1));
    pq.push(Type(3));
    pq.push(Type(2));
    cout << pq.top().i << endl;

    // 关联式容器
    // 通过一个关键字， 保存和访问元素的
//    pq.push(Type(2));
//    pq.push(Type(4234324));

    set<int> set1 = {1, 2, 3, 4};

    pair<set<int>::iterator, bool> pair = set1.insert(4);
    cout << pair.second << endl;

    cout << set1.size() << endl;

    set<int>::iterator set1It = set1.begin();
//    for (; set1It != set1.end(); ++set1It) {
//        cout << "value = " << *set1It << endl;
//    }

    while (set1It != set1.end()) {

        cout << "value = " << *set1It++ << endl;
    }
    set1It = set1.begin();


//    set<int>::iterator _it = vec.begin();
    vector<int>::iterator _it = vec.begin();

    for (; _it < vec.end();) {

        if (*_it == 3) {
            _it = vec.erase(_it);

        } else {
//            _it.operator++();
            _it++;
        }
    }

    _it = vec.begin();

    for (; _it < vec.end();) {

        cout << "删除后的为 " << *_it++ << endl;
    }

    cout << "--------------------------------" << endl;
    map<int, string> map1;

    map<string, string> map2 = {{"name", "zenglw"}};

    cout << map2["name"] << endl;

    const char *name = "niasdf";
    char *new_name = const_cast<char *> (name);

    cout << "--------------------------------" << endl;

//    Child* child = new Child;
//    child->test();
//
//    Parent* parent = static_cast<Parent *>(child);
//    if (parent) {
//
//        parent->test();
//    } else {
//
//        cout << "invalid" << endl;
//    }
    Parent *parent = new Parent;
//    child->test();

    Child *child = static_cast<Child *>(parent);
    if (child) {

        child->test();
    } else {

        cout << "invalid" << endl;
    }
//    cout << child->getI() << endl;


    return 0;
}

Student::~Student() {

//    cout << "释放内存" << endl;
}

Student::Student(int i, int j) : i(i), j(j) {
    cout << "i = " << i << "  j = " << j << endl;
}

void test(Student *student) {
    student->name = "是是名";
}

//void Student::setName() {
//
//    this->name = "name111111";
//}

