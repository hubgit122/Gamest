
#ifndef __ARRAY_H__
#define __ARRAY_H__
#include "utilities.h"
#include "Object.h"

namespace CIG
{
    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    class Array: public Object
    {
        public:
            inline Array();
            inline Array(const Array &a);
            inline Array(const MyJSONNode &json);
            inline virtual ~Array();

            T *elements;
            unsigned short size;
            unsigned short capacity;

            inline void operator = (const Array<T, INI_DEPTH, DEPTH_INCRE> &a);
            inline void forceCopyFrom(const Array<T, INI_DEPTH, DEPTH_INCRE> &a);

            inline bool contains(const T &e)const;
            inline T *add(const T &element);
            inline void addAt(short index, const T e);
            inline void deleteAtNoReturn(short index);
            inline T deleteAtThenGet(short index);
            inline T &at(short index)const;
            inline T &operator[](short index)const;

            inline void increaseCapacity();
            inline void memAlloc();
            inline void memRealloc();
            inline void clearMem();
            inline void clear();
            inline virtual string toJSON()const;
    };

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::Array(const MyJSONNode &json) : size(0), capacity(INI_DEPTH)
    {
        try
        {
            JSONNode::const_iterator it = json.begin();

            while(it != json.end())
            {
                MyJSONNode k(*it);
                this->add(T(k));
                it++;
            }
        }
        catch(std::out_of_range *e)
        {
            return;
        }
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    string CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::toJSON()
    {
        ostringstream oss;
        oss << "[";

        for(int i = 0; i < this.size;)
        {
            oss << (typeid(T) == typeid(string) ? "\"" : "") << (*this)[i] << (typeid(T) == typeid(string) ? "\"" : "");
            ++i

            if(i < this.size)
            {
                oss << ",";
            }
            else
            {
                break;
            }
        }

        oss << "]";
        return oss.str();
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::forceCopyFrom(const Array<T, INI_DEPTH, DEPTH_INCRE> &a)
    {
        size = a.size;
        capacity = a.capacity;

        if(elements)
        {
            free(elements);
        }

        memAlloc();
        memcpy(elements, a.elements, size * sizeof(T));
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::deleteAtNoReturn(short index)
    {
        if((index >= this->size) || (index < -this->size))
        {
            this->informError(string("at : ��Χ����\n"));
        }

        if(index < 0)           //ָ�������һ��ѭ��, ����-1ָ�����һ��Ԫ��. ������Ҫ����.
        {
            index += this->size;
        }

        (elements + index)->~T();

        for(unsigned short i = index; i  < size - 1; ++i)
        {
            new(elements + i) T(elements[1 + i]);
            (elements + i + 1)->~T();
        }

        size--;
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::operator=(const Array<T, INI_DEPTH, DEPTH_INCRE> &a)
    {
        clearMem();
        size = a.size;
        capacity = a.capacity;
        memAlloc();

        for(int i = 0; i < size; ++i)
        {
            new(elements + i) T(a.elements[i]);
        }
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    bool CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::contains(const T &e) const
    {
        for(int i = size - 1; i >= 0; --i)
        {
            if(this->at[i] == e)
            {
                return true;
            }
        }

        return false;
    }

    //�����������.
    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::clearMem()
    {
        if(elements)
        {
            for(int i = 0; i < size; ++i)
            {
                (elements + i)->~T();
            }

            free(elements);
            elements = NULL;
        }
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::clear()
    {
        clearMem();
        size = 0;
        capacity = INI_DEPTH;
        memAlloc();
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::memRealloc()
    {
        T *temp;

        if((temp = (T *)malloc(sizeof(T) * (this->capacity))) == NULL)
        {
            this->informError(string("�ڴ治��, ����\n"));
        }

        if(elements)
        {
            for(int i = 0; i < size; ++i)
            {
                new(temp + i) T(elements[i]);
                elements[i].~T();
            }

            free(elements);                                         ///������仰, ����ʧ��.
        }

        elements = temp;
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::increaseCapacity()
    {
        if(this->size >= this->capacity)
        {
            if(DEPTH_INCRE < 0)
            {
                informError("�ﵽ�ڴ��������! \n");
            }
            else
            {
                this->capacity += ((DEPTH_INCRE == 0) ? this->capacity : DEPTH_INCRE);
                memRealloc();
            }
        }
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::memAlloc()
    {
        if((elements = (T *)malloc(sizeof(T) * (this->capacity))) == NULL)
        {
            this->informError(string("�ڴ治��, ����\n"));
        }
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    T &CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::operator [](short index) const
    {
        return this->at(index);
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    T &CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::at(short index) const
    {
        if((index >= this->size) || (index < -this->size))
        {
            this->informError(string("at : ��Χ����\n"));
        }

        if(index < 0)
        {
            index += this->size;
        }

        return this->elements[index];
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    T CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::deleteAtThenGet(short index)
    {
        if((index >= this->size) || (index < -this->size))
        {
            this->informError(string("at : ��Χ����\n"));
        }

        if(index < 0)           //ָ�������һ��ѭ��, ����-1ָ�����һ��Ԫ��. ������Ҫ����.
        {
            index += this->size;
        }

        T temp(this->elements[index]);
        (elements + index)->~T();

        for(unsigned short i = index; i + 1 < this->size; ++i)
        {
            new(elements + i) T(elements[1 + i]);
            (elements + i + 1)->~T();
        }

        this->size--;
        return temp;
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::addAt(short index, const T e)
    {
        if((index >= this->size) || (index < -this->size))
        {
            this->informError(string("at : ��Χ����\n"));
        }

        if(index < 0)
        {
            index += this->size;
        }

        this->increaseCapacity();

        for(unsigned short i = this->size - 1; i >= index; --i)
        {
            new(elements + i + 1) T(elements[i]);
            (elements + i)->~T();
        }

        new(elements + index) T(e);
        size++;
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    T *CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::add(const T &element)
    {
        this->increaseCapacity();
        new(elements + (size++)) T(element);
        return elements + size - 1;
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::~Array()
    {
        clearMem();
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::Array(const Array<T, INI_DEPTH, DEPTH_INCRE> &a)
        : size(a.size), capacity(max<unsigned short>(a.capacity, INI_DEPTH))
    {
        memAlloc();

        for(int i = 0; i < size; ++i)
        {
            new(elements + i) T(a.elements[i]);
        }
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    CIG::Array<T, INI_DEPTH, DEPTH_INCRE>::Array()
        : size(0), capacity(INI_DEPTH), elements(NULL)
    {
        memAlloc();
    }
}
#endif /*__ARRAY_H_*/

// ���ݶ���ʱ, һ��Ҫ����һ��, ��string
// ����๹�캯�����ݲ�������ͨ����Ա��ʼ����, ��ʽ��:                �๹�캯����(�����б�):������(��������б��һ����), ��(ֵ),����
