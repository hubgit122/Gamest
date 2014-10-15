
#ifndef __STACK_H__
#define __STACK_H__

#include "Array.h"
#include "ChessGameConfig.h"

namespace CIG
{
    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    class Stack: public Array< T, INI_DEPTH, DEPTH_INCRE>
    {
        public:
            inline Stack();
            inline Stack(const Stack &s);
            virtual ~Stack();

            inline void operator<<(Stack<T, INI_DEPTH, DEPTH_INCRE> &a);

            inline T *push(const T &E);
            inline T popThenGet();
            inline void popNoReturn();
            inline T &top()const;
    };

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    CIG::Stack<T, INI_DEPTH, DEPTH_INCRE>::~Stack()
    {
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    T &CIG::Stack<T, INI_DEPTH, DEPTH_INCRE>::top() const
    {
        return this->at(this->size - 1);                    //size-1 ���������������.
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    T CIG::Stack<T, INI_DEPTH, DEPTH_INCRE>::popThenGet()
    {
        return Array<T, INI_DEPTH, DEPTH_INCRE>::deleteAtThenGet(this->size - 1);
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    void CIG::Stack<T, INI_DEPTH, DEPTH_INCRE>::popNoReturn()
    {
        Array<T, INI_DEPTH, DEPTH_INCRE>::deleteAtNoReturn(this->size - 1);
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    T *CIG::Stack<T, INI_DEPTH, DEPTH_INCRE>::push(const T &E)
    {
        return Array<T, INI_DEPTH, DEPTH_INCRE>::add(E);
    }

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    Stack<T, INI_DEPTH, DEPTH_INCRE>::Stack() {}

    template <class T, unsigned short INI_DEPTH, unsigned short DEPTH_INCRE>
    CIG::Stack<T, INI_DEPTH, DEPTH_INCRE>::Stack(const Stack &s): Array(s) {}

    class Motion;
    typedef Stack<Motion, INT_BOARD_HISTORY_STACK_SIZE, 0> Move;
    typedef  Stack<OPERATIONS, INT_BOARD_HISTORY_STACK_SIZE, 0> OperationStack;
    typedef Stack<Move, INT_BOARD_HISTORY_STACK_SIZE, 0> MoveStack;
}

#endif /*__STACK_H_*/