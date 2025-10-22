//
// Created by yk on 2025/10/22.
//
#include <iostream>
#include <wait.h>
int main(){
    const char* str1 = "yk yyds";
    // {
    //     char *str2 = (char*)str1;
    // }
    // printf("%s",str2);

    // char *str2 = (char*)str1;
    // str2[0]='H';//未定义行为，强制类型转换只是编译期类型视角的改变，实际上本质还是一个常量！
    // printf("%s",str2);
    return 0;
}