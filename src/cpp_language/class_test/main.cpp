//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

class TestFieldNameClass {
  public:
      TestFieldNameClass(){
    printf("init test class %p\n",this);
  }
  int value;
  int i_value{};
  void print() const{
        printf("value %d  i_value  %d\n",value,i_value);

  }
};
TestFieldNameClass g_val; // 全局默认初始化, 在main函数前初始化, 即使没有声明要初始化的变量value也会被置为默认值
TestFieldNameClass g_i_val{}; // 全局默认初始化
// static 全局变量只能在本文件中访问 , 初始化上没区别 , 只是为了格式统一
static TestFieldNameClass g_s_val; // 全局默认初始化
static TestFieldNameClass g_s_i_val{}; // 全局默认初始化

void testFunc(){
  printf("==== start func \n");

  int a;    // 局部基础变量不会初始化
  int i_a{};  // 局部变量调用默认初始化函数初始化
  TestFieldNameClass l_val;  // 类变量总是初始化, i_value 会被初始化, 但是 value 不会, 应为不再构造函数初始化表中
  TestFieldNameClass l_i_val{}; // 类变量初始化
  static TestFieldNameClass
      l_s_val; // 局部静态变量在第一次调用函数时初始化 i_value 和 value 都会初始化,和全局变量的初始化规则类似, 只是时机晚一些
  static TestFieldNameClass
      l_s_i_val{}; // 局部静态变量在第一次调用函数时初始化

#define PRINT_C(name)\
  printf("now check [%s]  [%p] ",#name,&name);\
  name.print();

  printf("test int [a : %d]  [i_a : %d]\n",a,i_a);

  PRINT_C(g_val)
  PRINT_C(g_i_val)
  PRINT_C(g_s_val)
  PRINT_C(g_s_i_val)
  PRINT_C(l_val)
  PRINT_C(l_i_val)
  PRINT_C(l_s_val)
  PRINT_C(l_s_i_val)
#undef PRINT_C
}
int main(int argc, char **argv) {
  testFunc();
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}