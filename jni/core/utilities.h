#ifndef __UTILITIES_H__
#define __UTILITIES_H__
/*************************************************************************
  包含文件
**************************************************************************/
#include <string.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <map>
#include <iosfwd>

#include "MyJSONNode.h"
#include "types.h"
#include "../libjson/libjson.h"
#include "C:\Program Files\Java\jdk1.8.0_11\include\jni.h"

using namespace std;
using namespace CIG;

/*************************************************************************
调试开关
**************************************************************************/
//#define VERBOS
//#define DEBUG_INTEGER
//#define DEBUG_ARRAY
//#define DEBUG_CHESSBOARD
//#define DEBUG_REF
//#define DEBUG_MESSAGE

/*****************************************************
 辅助宏定义
 *****************************************************/
#define JSON_KEYVALUE(j) JSON_KEY(j) << j
#define JSON_KEY(k) JSON_STRING(k) << ":"
#define JSON_INI(a) a(json.at(TO_STRING(a)))
#define JSON_GET(a,type) a = json.at(TO_STRING(a)).as_##type();
#define JSON_STRING(s) <<TO_STRING(s)
#define TO_STRING(s) "\""#s"\""
#define JSON_VALUE(v) <<v
#define JSON_COMMA <<","
#define JSON_ARRAY(a) "[" a <<"]"
#define JSON_OBJECT(a) "{" a <<"}"

/*************************************************************************
    辅助类和辅助函数
    **************************************************************************/

int roundInt(float f);
void parseBoolArray(const MyJSONNode &json, const string &s, vector<bool> &v);
void parseIntArray(const MyJSONNode &json, const string &s, vector<int> &v);

template<class T>
void QuickSort(T a[], unsigned n);
#endif // UTILITIES



/*************************************************************************
 学习笔记
**************************************************************************/
// 1. realloc失败的时候，返回NULL
//  2. realloc失败的时候，原来的内存不改变，不会释放也不会移动
//  3. 假如原来的内存后面还有足够多剩余内存的话，realloc的内存=原来的内存+剩余内存,realloc还是返回原来内存的地址; 假如原来的内存后面没有足够多剩余内存的话，realloc将申请新的内存，然后把原来的内存数据拷贝到新内存里，原来的内存将被free掉,realloc返回新内存的地址
//  4. 如果size为0，效果等同于free()。这里需要注意的是只对指针本身进行释放，例如对二维指针**a，对a调用realloc时只会释放一维，使用时谨防内存泄露。
//  5. 传递给realloc的指针必须是先前通过malloc(), calloc(), 或realloc()分配的
//  6.传递给realloc的指针可以为空，等同于malloc。
//
// static 成员的访问方式:   类型名::成员, 和java的 类型名.成员 不一样
// 不能用char*, const char*, string对象 作模板参数, C++的模板不如java支持的好. 虽然java不支持基本类型, 但是可以传包装类嘛.