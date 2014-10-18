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

using namespace std;

#include "types.h"
#include "../libjson/libjson.h"
#include "C:\Program Files\Java\jdk1.8.0_11\include\jni.h"

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
struct PointOrVector_Float
{
    float x[2];

    PointOrVector_Float()
    {
        this->x[0] = 0;
        this->x[1] = 0;
    }

    PointOrVector_Float(float x, float y)
    {
        this->x[0] = x;
        this->x[1] = y;
    }

    float operator*(const PointOrVector_Float &p)
    {
        return x[0] * p.x[0] + x[1] * p.x[1];
    }

    void operator = (const PointOrVector_Float &p)
    {
        memcpy(x, p.x, sizeof(float) << 1);
    }

    friend PointOrVector_Float operator*(int lambda, const PointOrVector_Float &p)
    {
        return (float)lambda * p;
    }

    friend PointOrVector_Float operator*(float lambda, const PointOrVector_Float &p)
    {
        PointOrVector_Float temp = p;

        temp.x[0] *= lambda;
        temp.x[1] *= lambda;

        return temp;
    }

    PointOrVector_Float operator- (const PointOrVector_Float &p)
    {
        PointOrVector_Float temp = *this;

        temp.x[0] -= p.x[0];
        temp.x[1] -= p.x[1];

        return temp;
    }

    PointOrVector_Float operator+ (const PointOrVector_Float &p)
    {
        PointOrVector_Float temp = *this;

        temp.x[0] += p.x[0];
        temp.x[1] += p.x[1];

        return temp;
    }

    friend ostringstream &operator<<(ostringstream &oss, const PointOrVector_Float &p)                      ///�������÷���, �ͻ���ÿ������캯��, id��������߰���.
    {
        oss << "( " << p.x[0] << " , " << p.x[1] << " ) \n";
        return oss;
    }
};

struct PointOrVector
{
    short x[2];

    PointOrVector()
    {
        memset(x, -1, sizeof(unsigned short) << 1);             // TO-DO ע������ı�������ĵ�Ĭ��Ϊ0,0�ļ���, Ӧ�ò��������, ��������ʱ�����ע��һ��
    }

    PointOrVector(unsigned x, unsigned y)
    {
        this->x[0] = x;
        this->x[1] = y;
    }

    PointOrVector(unsigned xy)
    {
        *(unsigned *)(this->x) = xy;
    }

    short &operator[](bool index)
    {
        return x[index];
    }

    const short &operator[](bool index)const
    {
        return x[index];
    }

    bool operator==(const PointOrVector &p)const
    {
        return (*(unsigned *)this->x == *(unsigned *)(p.x));
    }

    bool operator!=(const PointOrVector &p)const
    {
        return !(*this == p);
    }

    friend PointOrVector operator*(int lambda, const PointOrVector &p)
    {
        PointOrVector temp = p;

        temp.x[0] *= lambda;
        temp.x[1] *= lambda;

        return temp;
    }
    PointOrVector operator- (const PointOrVector &p)const
    {
        PointOrVector temp = *this;

        //*(unsigned*)temp.x -= *(unsigned*)(p.x);              //�漰����λʱ��������ʧ��.
        temp.x[0] -= p.x[0];
        temp.x[1] -= p.x[1];
        return temp;
    }

    PointOrVector &operator+=(const PointOrVector &p)
    {
        this->x[0] += p[0];
        this->x[1] += p[1];
        return *this;
    }

    PointOrVector operator+ (const PointOrVector &p)const
    {
        PointOrVector temp = *this;

        temp.x[0] += p.x[0];
        temp.x[1] += p.x[1];

        //*(unsigned*)temp.x += *(unsigned*)(p.x);          //�ڵ�λ�и�����ʱ�����ּӷ�ʧ��.
        return temp;
    }

    friend ostringstream &operator<<(ostringstream &oss, const PointOrVector &p)                        ///�������÷���, �ͻ���ÿ������캯��, id��������߰���.
    {
        oss << "( " << p.x[0] << " , " << p.x[1] << " ) \n";
        return oss;
    }
};

struct Line
{
    PointOrVector p0, p1;
    Line(int x0, int y0, int x1, int y1): p0(x0, y0), p1(x1, y1)
    {
    }
};

int roundInt(float f);

void parseBoolArray(const JSONNode &json, const string &s, vector<bool>& v);
void parseIntArray(const JSONNode &json, const string &s, vector<int>& v);

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