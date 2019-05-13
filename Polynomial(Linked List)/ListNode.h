

#ifndef LISTNODE_H
#define LISTNODE_H



#include "Term.h"


class ListNode
{
    friend class PolynomialList;

public:
    ListNode( const Term & );
    Term getData() const;
private:
    Term data; //項
    ListNode *nextPtr; //下一項的指標
};



ListNode::ListNode( const Term &info )
    :data( info ), nextPtr( 0 )
{

}



Term ListNode::getData() const
{
    return data;
}

#endif
