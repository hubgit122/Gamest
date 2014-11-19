#ifndef __PointerArray_H__
#define __PointerArray_H__
#include "Array.h"

namespace CIG
{
    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    class PointerArray : public Array<T *, INI_DEPTH, DEPTH_INCRE>
    {
        public:
            inline PointerArray() {};
            inline PointerArray(const PointerArray &a) {};
            inline PointerArray(const MyJSONNode &json);
            inline  virtual  virtual ~PointerArray();

            inline virtual  void operator = (const Array<T, INI_DEPTH, DEPTH_INCRE> &a);
            inline virtual  void forceCopyFrom(const Array<T, INI_DEPTH, DEPTH_INCRE> &a);

            inline virtual  bool contains(const T &e)const;
            inline virtual  T *add(const T &element);
            inline virtual  void addAt(short index, const T e);
            inline virtual  void deleteAtNoReturn(short index);
            inline virtual  T deleteAtThenGet(short index);
            inline virtual  T &at(short index)const;
            inline virtual  T &operator[](short index)const;

            inline virtual  void increaseCapacity();
            inline virtual  void memAlloc();
            inline virtual  void memRealloc();
            inline virtual  void clearMem();
            inline virtual  void clear();
            inline virtual string toJSON()const;
    };

}
#endif /*__ARRAY_H_*/

// ���ݶ���ʱ, һ��Ҫ����һ��, ��string
// ����๹�캯�����ݲ�������ͨ����Ա��ʼ����, ��ʽ��:                �๹�캯����(�����б�):������(��������б��һ����), ��(ֵ),����
