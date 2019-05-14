

#ifndef POLYNOMIALLIST_H
#define POLYNOMIALLIST_H

#include <iostream>
#include <cmath>
#include "ListNode.h"
#include "Polynomial.h"
using namespace std;


class PolynomialList
{
    friend ostream &operator<<( ostream &, const PolynomialList & );
public:
    PolynomialList(); //預設建構子
    PolynomialList( const Polynomial & ); //需要polynomial物件來建構的建構子
    PolynomialList( const PolynomialList & ); //複製建構子
    ~PolynomialList(); //解構子
    void addTerm( int ); //以指數來為多項式新增一項
    void addTerm( int, int ); //以指數及係數來為多項式新增一項
    void removeExistTerm( int ); //利用指數來刪除指定的項
    void parseToPoly(); //將polynomialList物件轉換成polynomial物件
    void insertAtFront( const Term & ); //新增一項到最前方
    void insertAtBack( const Term & ); //新增一項到最後方
    bool removeFromFront( Term & ); //刪除領導項
    bool removeFromBack( Term & ); //刪除最後一項
    bool isEmpty() const; //判斷鏈結陣列是否為空
    void print() const; //輸出結果
    
    PolynomialList operator + ( const PolynomialList& );//多項式相加
    
    PolynomialList operator - ( const PolynomialList& );//多項式相減
    
    PolynomialList operator * ( const PolynomialList& );//多項式相乘
    
    double solution( const int& );//代值計算
    
private:
    ListNode *firstPtr; //指向多項式領導項的指標
    ListNode *lastPtr; //指向多項式最後一項的指標
    Polynomial poly; //polynomial的物件，用於解析字串與輸出結果
    int length; //項數

    ListNode *getNewNode( const Term & ); //取得一個新的節點
};


PolynomialList::PolynomialList()
:firstPtr( 0 ), lastPtr( 0 )
{
    
}

PolynomialList::PolynomialList( const Polynomial &p )
:firstPtr( 0 ), lastPtr( 0 ), poly( p )
{
    
    length = poly.getLength(); //取得多項式的長度
    
    //開始建構Linked List
    for( int i = 0; i < length; i++ ) {
        if( poly.terms[i].coef != 0 )
            insertAtFront(poly.terms[i]);
    }
}


PolynomialList::PolynomialList( const PolynomialList &p )
{
    //如果該鏈結不為空，將該鏈結清空
    if( !isEmpty() )
    {
        ListNode *currentPtr = firstPtr;
        ListNode *tempPtr;
        
        while( currentPtr != 0 )
        {
            tempPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        }
    }
    //以欲複製的多項式的first指標來走訪
    ListNode *currentPtr = p.firstPtr;
    
    //如果還沒走訪完欲複製的鏈結
    while( currentPtr != 0 )
    {
        addTerm( currentPtr->data.exp, currentPtr->data.coef ); //將每一項複製給自己
        currentPtr = currentPtr->nextPtr;
    }
    poly = p.poly;
    length = poly.getLength();
}


PolynomialList::~PolynomialList()
{
    //如果該鏈結有資料，將指標所佔用的記憶體釋放
    if( !isEmpty() )
    {
        ListNode *currentPtr = firstPtr;
        ListNode *tempPtr;
        
        while( currentPtr != 0 )
        {
            tempPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            delete tempPtr;
        }
    }
    
}


void PolynomialList::addTerm( int i ) //i為欲新增項的指數
{
    int tCoef;
    cout << "Coef? : ";
    cin >> tCoef; //輸入想要加入該項的係數
    Term t( tCoef, i ); //創建項的物件
    ListNode *currentPtr = firstPtr;
    
    //如果鏈結為NULL或欲新增的指數 >= 領導項的指數
    if( currentPtr == 0 || i >= currentPtr->data.exp )
    {
        if( i == currentPtr->data.exp ) //如果欲新增項的指數等於領導項的指數
            currentPtr->data.coef += t.coef; //將兩者的係數相加
        else //代表該鏈結為空
            insertAtFront(t); //新增項
    }
    //代表欲新增的指數小於領導項
    else
    {
        //如果下一項不為NULL且欲新增項的指數小於下一項
        while( currentPtr->nextPtr != 0  && i < currentPtr->nextPtr->data.exp )
            currentPtr = currentPtr->nextPtr;
        
        ListNode *tempPtr = currentPtr->nextPtr; //將下一項暫存起來
        
        //如果預新增項為多項式最後一項
        if( currentPtr->nextPtr == 0 ){
            insertAtBack( t );
        }
        //代表欲新增項不為多項式的最後一項
        else
        {
            if( i == currentPtr->nextPtr->data.exp ) //如果欲新增項的指數等於下一項的指數
                tempPtr->data.coef += t.coef; //兩者相加
            else //代表欲新增項的指數 > 下一項的指數
            {
                ListNode *newPtr = getNewNode( t ); //將新增項創造成節點
                newPtr->nextPtr = tempPtr; //將下一項設為新增項的next指標
                currentPtr->nextPtr = newPtr; //將目前項的next指標設為新結點
            }
        }
    }
    
    parseToPoly(); //resize
}


void PolynomialList::addTerm( int i, int tCoef ) //Overloading addterm function
{
    Term t( tCoef, i );
    ListNode *currentPtr = firstPtr;
    
    
    if( currentPtr == 0  || i >= currentPtr->data.exp ){
        if(  currentPtr != 0 && i == currentPtr->data.exp )
            currentPtr->data.coef += t.coef;
        else
            insertAtFront(t);
    }
    else
    {
        while(  currentPtr->nextPtr != 0  && i < currentPtr->nextPtr->data.exp )
            currentPtr = currentPtr->nextPtr;
        
        ListNode *tempPtr = currentPtr->nextPtr;
        
        if( currentPtr->nextPtr == 0 ){
            insertAtBack( t );
        }
        else
        {
            if( i == currentPtr->nextPtr->data.exp )
                tempPtr->data.coef += t.coef;
            else
            {
                ListNode *newPtr = getNewNode( t );
                newPtr->nextPtr = tempPtr;
                currentPtr->nextPtr = newPtr;
            }
        }
    }
    
    parseToPoly(); //將該多項式轉換成polynomial物件
}


void PolynomialList::removeExistTerm( int i )
{
    ListNode *currentPtr = firstPtr; //從領導項開始走訪
    
    //如果領導項為欲刪除的項
    if( currentPtr->data.exp == i )
    {
        ListNode *tempPtr = firstPtr; //將領導項的指標暫存起來
        firstPtr = firstPtr->nextPtr; //將first指標指向下一個
        delete tempPtr; //刪除領導項
    }
    //如果領導項不為欲刪除的項
    else
    {
        //如果下一項不為NULL並且不等於欲刪除的項
        while( currentPtr->nextPtr != 0 && currentPtr->nextPtr->data.exp != i )
            currentPtr = currentPtr->nextPtr;
        
        ListNode *tempPtr = currentPtr->nextPtr; //將下一項暫存
        
        if( currentPtr->nextPtr == 0 ) //走訪完畢且沒找到符合的項
            cout << "This elements is not exist!" << endl;
        else //找到欲刪除的項
        {
            currentPtr->nextPtr = tempPtr->nextPtr;
            delete tempPtr;
        }
    }
    
    //如果刪除後該多項式為空的，新增常數項，且常數項為0
    if( isEmpty() )
    {
        Term t( 0, 0 );
        ListNode *newPtr = getNewNode( t );
        firstPtr = lastPtr = newPtr;
    }
    
    parseToPoly(); //將該多項式轉換成polynomial物件
}


void PolynomialList::parseToPoly()
{
    length = firstPtr->data.exp + 1; //取得項數
    Polynomial temp( length ); //根據項數創建一個polynomial物件
    ListNode *currentPtr = firstPtr;
    
    //將在鏈結存在的項賦值給polynomial物件
    while( currentPtr != 0 )
    {
        temp.terms[ currentPtr->data.exp ].coef = currentPtr->data.coef;
        currentPtr = currentPtr->nextPtr;
    }
    poly = temp; //轉換完成
}


void PolynomialList::insertAtFront( const Term &value )
{
    ListNode *newPtr = getNewNode( value );
    
    if( isEmpty() )
        firstPtr = lastPtr = newPtr;
    else
    {
        newPtr->nextPtr = firstPtr;
        firstPtr = newPtr;
    }
}



void PolynomialList::insertAtBack( const Term &value )
{
    ListNode *newPtr = getNewNode( value );
    
    if( isEmpty() )
        firstPtr = lastPtr = newPtr;
    else
    {
        lastPtr->nextPtr = newPtr;
        lastPtr = newPtr;
    }
}



bool PolynomialList::removeFromFront( Term &value )
{
    if( isEmpty() )
        return false;
    else
    {
        ListNode *tempPtr = firstPtr;
        
        if( firstPtr == lastPtr )
            firstPtr = lastPtr = 0;
        else
            firstPtr = firstPtr->nextPtr;
        
        value = tempPtr->data;
        delete tempPtr;
        return true;
    }
}



bool PolynomialList::removeFromBack( Term &value )
{
    if( isEmpty() )
        return false;
    else
    {
        ListNode *tempPtr = lastPtr;
        
        if( firstPtr == lastPtr )
            firstPtr = lastPtr = 0;
        else
        {
            ListNode *currentPtr = firstPtr;
            
            
            while( currentPtr->nextPtr != lastPtr )
                currentPtr = currentPtr->nextPtr;
            
            lastPtr = currentPtr;
            currentPtr->nextPtr = 0;
        }
        
        value = tempPtr->data;
        delete tempPtr;
        return true;
    }
}



bool PolynomialList::isEmpty() const
{
    return firstPtr == 0;
}



ListNode *PolynomialList::getNewNode( const Term &value )
{
    return new ListNode( value );
}



void PolynomialList::print() const
{
    //如果多項式為空
    if( isEmpty() )
    {
        cout << 0 << endl;
        return;
    }
    
    //將多項式輸出
    poly.printPolynomial();
    
    /*
     
     ListNode *currentPtr = firstPtr;
     cout << "The list is: \n";
     
     while( currentPtr != 0 )
     {
     cout << "Coef : " << currentPtr->data.coef << ' ';
     cout << "Exp : " << currentPtr->data.exp << '\n';
     currentPtr = currentPtr->nextPtr;
     }
     
     cout << "\n\n";
     */
}

PolynomialList PolynomialList::operator + ( const PolynomialList& p )
{
    
    ListNode *currentPtr = p.firstPtr; //走訪欲相加的多項式
    PolynomialList temp = *this; //複製一個自己的PolynomialList物件
    
    
    while( currentPtr != 0 )
    {
        temp.addTerm( currentPtr->data.exp, currentPtr->data.coef ); //將兩多項式相加
        currentPtr = currentPtr->nextPtr;
    }
    
    return temp;
    
    /*
     PolynomialList temp( poly + p.poly );
     return temp;
     */
}


PolynomialList PolynomialList::operator - ( const PolynomialList& p )
{
    ListNode *currentPtr = p.firstPtr; //走訪欲相減的多項式
    PolynomialList temp = *this; //複製一個自己的PolynomialList物件
    
    while( currentPtr != 0 )
    {
        temp.addTerm( currentPtr->data.exp, -( currentPtr->data.coef ) ); //將兩多項式相減
        currentPtr = currentPtr->nextPtr;
    }
    
    return temp;
    
    /*
     PolynomialList temp( poly - p.poly );
     return temp;
     */
}


PolynomialList PolynomialList::operator * ( const PolynomialList& p )
{
    PolynomialList temp; //暫存的Linked List物件
    ListNode *currentPtrFirst = firstPtr; //走訪自己
    
    while( currentPtrFirst != 0 )
    {
        ListNode *currentPtrSecond = p.firstPtr; //走訪欲相乘的多項式
        while( currentPtrSecond != 0 )
        {
            temp.addTerm( currentPtrFirst->data.exp + currentPtrSecond->data.exp,
                         currentPtrFirst->data.coef * currentPtrSecond->data.coef ); //指數相加，係數相乘，並將產生的項新增到temp
            currentPtrSecond = currentPtrSecond->nextPtr;
        }
        currentPtrFirst = currentPtrFirst->nextPtr;
    }
    
    return temp;
    /*
     PolynomialList temp( poly * p.poly );
     return temp;
     */
}


ostream &operator<<( ostream &output, const PolynomialList &right )
{
    //如果多項式為空
    if( right.isEmpty() ) {
        cout << 0 << endl;
    }else {
        //將多項式輸出
        right.print();
    }
    return output;
}


double PolynomialList::solution( const int& number )
{
    double total = 0;
    ListNode *currentPtr = firstPtr;
    
    //走訪自己
    while( currentPtr != 0 )
    {
        total += currentPtr->data.coef * pow( number, currentPtr->data.exp ); //將值逐項帶入，並由total累加
        currentPtr = currentPtr->nextPtr;
    }
    
    return total;
    //return poly.solution( number );
}


#endif
