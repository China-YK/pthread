//
// Created by yk on 2025/10/22.
//
#include <iostream>
#include <pthread.h>
#include <wait.h>

void* threadEntry(void *arg){
    const char* msg = "thread is comming!";
    fprintf(stdout,"arg is:%s\n",(char*)arg);
    return (void*)msg;
}
void CreateThread(){
    pthread_t tid;
    //之前进程号的类型为pid_t
    //这里线程号的类型为pthread_t
    const char* pInfo = "hello thread!";
    int ret = pthread_create(&tid,nullptr,threadEntry,(void*)pInfo);
    //讲一下pthread_create
    //第一个参数，输出参数，创建成功后会把新线程的ID写入tid里面
    //第二个参数，表示线程属性，可以用来控制线程栈的大小，调度策略等，填nullptr表示默认属性
    //第三个参数，本质上是一个函数指针，用来回调线程的入口函数，要求入口函数返回值类型为void*，一个形参同时类型为void*
    //第四个参数，线程入口函数的参数
    //总结：创建一个线程，并通过tid获取线程id，创建成功立即开始执行线程的入口函数，返回的值为0
    //如果创建失败，返回值为非零(错误码)，比如11->系统资源不足，12->线程分配栈空间失败。而tid就不会赋值，保持原值
    if (ret == 0){
        void *result = nullptr;
        pthread_join(tid,&result);
        //pthread_join就是阻塞当前的主线程，等待tid这个子线程的入口函数执行完毕，并把返回值放到result里面去

        //这里我们学了这么多，也可以考虑到一种极端情况，如果子线程的入口函数执行的特别快，我主线程都还没执行到pthread_join(tid,&result);
        //子线程的入口函数就执行完毕了，并且返回了(void*)msg，那我们这里用result去接收这个返回值能接收到吗？会报错吗？
        //答案是：能接收到，也不会报错！
        //原因是：内核为结束线程保留状态
        //当线程结束时(return或者pthread_exit)，它的资源不会立刻被操作系统销毁，而是进入一种"可连接状态"
        //在这种状态下：线程已经结束运行，但操作系统仍然保留它的线程控制块(TCB)、返回值、退出码等
        //直到有另一个线程(比如这里的主线程)对线程号为tid的线程调用pthread_join()才真正释放这些资源

        fprintf(stdout,"threadEntry return is:%s\n",(char*)result);
    }
}
int main(){
    CreateThread();
    return 0;
}