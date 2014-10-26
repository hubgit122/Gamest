#ifndef __UTILITIES_H__
#define __UTILITIES_H__
/*************************************************************************
  �����ļ�
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
���Կ���
**************************************************************************/
//#define VERBOS
//#define DEBUG_INTEGER
//#define DEBUG_ARRAY
//#define DEBUG_CHESSBOARD
//#define DEBUG_REF
//#define DEBUG_MESSAGE

/*****************************************************
 �����궨��
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
    ������͸�������
    **************************************************************************/

int roundInt(float f);
void parseBoolArray(const MyJSONNode &json, const string &s, vector<bool> &v);
void parseIntArray(const MyJSONNode &json, const string &s, vector<int> &v);

template<class T>
void QuickSort(T a[], unsigned n);
#endif // UTILITIES



/*************************************************************************
 ѧϰ�ʼ�
**************************************************************************/
// 1. reallocʧ�ܵ�ʱ�򣬷���NULL
//  2. reallocʧ�ܵ�ʱ��ԭ�����ڴ治�ı䣬�����ͷ�Ҳ�����ƶ�
//  3. ����ԭ�����ڴ���滹���㹻��ʣ���ڴ�Ļ���realloc���ڴ�=ԭ�����ڴ�+ʣ���ڴ�,realloc���Ƿ���ԭ���ڴ�ĵ�ַ; ����ԭ�����ڴ����û���㹻��ʣ���ڴ�Ļ���realloc�������µ��ڴ棬Ȼ���ԭ�����ڴ����ݿ��������ڴ��ԭ�����ڴ潫��free��,realloc�������ڴ�ĵ�ַ
//  4. ���sizeΪ0��Ч����ͬ��free()��������Ҫע�����ֻ��ָ�뱾������ͷţ�����Զ�άָ��**a����a����reallocʱֻ���ͷ�һά��ʹ��ʱ�����ڴ�й¶��
//  5. ���ݸ�realloc��ָ���������ǰͨ��malloc(), calloc(), ��realloc()�����
//  6.���ݸ�realloc��ָ�����Ϊ�գ���ͬ��malloc��
//
// static ��Ա�ķ��ʷ�ʽ:   ������::��Ա, ��java�� ������.��Ա ��һ��
// ������char*, const char*, string���� ��ģ�����, C++��ģ�岻��java֧�ֵĺ�. ��Ȼjava��֧�ֻ�������, ���ǿ��Դ���װ����.