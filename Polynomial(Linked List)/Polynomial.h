//
//  Polynomial.h
//  Polynomial
//
//  Created by 林仁鴻 on 2017/10/17.
//  Copyright © 2017年 林仁鴻. All rights reserved.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Term.h"
#include <string>

class ListNode;

using std::string;

class Polynomial
{
    friend class PolynomialList;
    friend class ListNode;
    public :
    
    Polynomial( int = 3 );//此建構子會根據傳進來的數字來決定為多少項的多項式
    
    Polynomial( string );//此建構子會根據傳進來的字串來建構出多項式
    
    //不需解構，因linked list已解構
    
    Polynomial operator + ( const Polynomial& );//多項式相加
    
    Polynomial operator - ( const Polynomial& );//多項式相減
    
    Polynomial operator * ( const Polynomial& );//多項式相乘
    
    const Polynomial &operator = ( const Polynomial & );//因為有指標，所以要Overloading賦值運算子
    
    double solution( const int& );//代值計算
    
    void printPolynomial() const;//印出多項式
    
    bool isAllZero() const;
    
    
    //取得長度
    int getLength() const {
        return length;
    }
    
    private :
    void prepareTerm(); //前置作業，解析字串
    Term * terms; //項
    Polynomial *nextPtr;
    string s; //傳入的多項式
    int length; //項數
};
#endif /* Poly_h */

