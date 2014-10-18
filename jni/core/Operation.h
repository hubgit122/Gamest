#ifndef __OPERATION_H__
#define __OPERATION_H__
class Operation : public Object
{
public:
    string name;
    unsigned short id;

    Operation(string s, unsigned short i): name(s), id(i)
    {
    }

private:
    Operation(){}
};
#endif//__OPERATION_H__