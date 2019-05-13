//
//  Poly.cpp
//  Polynomial
//
//  Created by 林仁鴻 on 2017/10/17.
//  Copyright © 2017年 林仁鴻. All rights reserved.
//

#include "Polynomial.h"
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

//預設建構子，將全部資料初始化
Polynomial::Polynomial( int count )
: length( count )
{
    s = "";
    terms = new Term[ length ];
    for( int i = 0; i < length; i++ )
    {
        terms[ i ].coef = 0;
        terms[ i ].exp = i;
    }
}


Polynomial::Polynomial( string input )
: s( input ), length( 1 )
{
    prepareTerm();//前置處理，解析字串
}


Polynomial Polynomial::operator + ( const Polynomial& A )
{
    int i, L, S;
    Polynomial big; //用來儲存最長的的length
    if(A.length < length) //判斷最長和最短
    {
        L = length;  //L為最長的長度
        S = A.length;//S為最短的長度
        big = *this; //把最長的長度儲存到Polynomial big
    }
    else
    {
        L = A.length;
        S = length;
        big = A;
    }
    
    Polynomial C (L);
    
    for(i=0; i < S; i++)//迴圈從0常數項開始一直到小於最短長度S
        C.terms[i].coef = A.terms[i].coef + terms[i].coef; //次方一樣的相加
    
    for(i=L - 1 ; i >= S; i--)//迴圈從最長度L開始到最短長度S
        C.terms[i].coef = big.terms[i].coef;//把剩下沒加的的補回去
    
    return C;
    
}


Polynomial Polynomial::operator - ( const Polynomial& A )
{
    int i, L, S;
    Polynomial big; //用來儲存最長的的length
    if(A.length < length) // 判斷最長和最短
    {
        L = length;  //L為最長的長度
        S = A.length;//S為最短的長度
        big = *this; //把最長的長度儲存到Polynomial big
    }
    else
    {
        L = A.length;
        S = length;
        big = A;
    }
    
    Polynomial C (L);
    
    for(i=0; i < S; i++) //迴圈從0常數項開始一直到小於最短長度S
        C.terms[i].coef = terms[i].coef - A.terms[i].coef;
    
    for(i=L - 1 ; i >= S; i--)//迴圈從最長度L開始到最短長度S
        if( A.length < length )
            C.terms[i].coef = big.terms[i].coef;//如果自身的項數比另一多項式要多，直接相減
        else
            C.terms[ i ].coef = -big.terms[ i ].coef;//如果自身的項數比另一多項式少，將剩下的加負號
    
    return C;
}


Polynomial Polynomial::operator * ( const Polynomial&  poly )
{
    int longestlength;
    //找出相乘後最大的項數
    longestlength=terms[length-1].exp+poly.terms[poly.length-1].exp + 1;
    
    //建立相乘後的多項式
    Polynomial b(longestlength);
    
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<poly.length;j++)
        {
            //係數相乘
            b.terms[i+j].coef+=terms[i].coef*poly.terms[j].coef;
            //指數相加
            b.terms[i+j].exp=terms[i].exp+poly.terms[j].exp;
        }
        
    }
    
    return b;
}


const Polynomial &Polynomial::operator = ( const Polynomial &right )
{
    //如果不是自己
    if( &right != this )
    {
        //如果項數不相等
        if( length != right.length )
        {
            delete [] terms;
            length = right.length;
            terms = new Term[ length ];
        }
        //將所有資料複製過去
        for( int i = 0; i < length; i++ )
        {
            terms[ i ].coef = right.terms[ i ].coef;
            terms[ i ].exp = right.terms[ i ].exp;
        }
        //將多項式的字串資料複製過去
        s = right.s;
    }
    //傳回自己本身的參照
    return *this;
}


double Polynomial::solution( const int &x )
{
    double total = 0;                                       //先定義參數為0
    
    for(int i = 0 ; i < length ;i++)                        //訂定出一個範圍 做迴圈
        total += terms[i].coef * pow( x , terms[i].exp);    //一直累加直到算出自己要的值
    
    return total;                                           //輸出算出來的值
    
    
    
}


void Polynomial::printPolynomial() const
{
    
    //如果多項式全部係數都為0
    if( isAllZero() )
        cout << 0 << endl;
    else
    {
        for( int i = length - 1; i >= 0; i-- )
        {
            //如果係數不為0
            if( terms[i].coef != 0 )
            {
                //如果係數不等於1和-1或不等於領導係數
                if( ( terms[i].coef != 1 && terms[ i ].coef != -1 ) || i == 0 )
                {
                    if(  terms[i].coef > 0 || ( i == length - 1 ) )
                        cout << terms[i].coef;
                    else
                        cout << -terms[i].coef;
                }
                
                //不等於常數項
                if( i != 0 )
                    cout << "x";
                //不等於常數項或第一項
                if( i != 1 && i !=0 )
                {
                    cout << "^";
                    cout << terms[i].exp;
                }
                
            }
            
            //判斷下一項是正還是負
            if( terms[i - 1].coef > 0 && i != 0 )
                cout << " + ";
            else if( terms[i - 1].coef < 0 && i != 0 )
                cout << " - ";
        }
    }
    
    cout << endl;
    cout << endl;
}


void Polynomial::prepareTerm()
{
    int start = 0;;
    string times = "";
    stringstream tss;
    
    //判斷此多項式有幾項
    for( int i = 0; i < s.length(); i++ )
    {
        //尋找指數
        if( s[i - 1] == '^'  )
        {
            times += s[i];
            start = i;
            while( s[start] >='0' && s[start] <= '9' )
            {
                times += s[++start];
            }
            tss << times;
            tss >> length;
            length += 1;
            break;
        }
        //如果多項式只有2項
        if( ( s[i] == 'x' || s[i] == 'X' ) && s[ i + 1 ] != '^' )
        {
            length = 2;
            break;
        }
        //如果多項式只有常數項
        if( i == s.length() - 1 )
            length = 1;
        
    }
    
    //將每項進行初始化
    terms = new Term[ length ];
    for( int i = 0; i < length; i++ )
        terms[ i ].exp = i;
    stringstream ss, ss2;
    //temp存係數的字串，temp2存指數的字串
    string temp = "", temp2 = "";
    int tCoef = 0, tExp = 0;
    bool isPositive = true;
    
    //解析字串
    for( int i = 0; i < s.length(); i++ )
    {
        //判斷下一項是正還是負
        if( s[i] == '+' )
            isPositive = true;
        else if( s[i] == '-' )
            isPositive = false;
        
        //如果是數字
        if( ( s[i] >= '0' && s[i] <= '9' ) && s[i-1] != '^' )
        {
            //如果是係數
            if( temp2.empty() )
                temp += s[i];
            //如果是指數
            else
            {
                temp2 += s[i];
                
                //如果到結尾
                if( i == s.length() - 1 )
                {
                    ss2 << temp2;
                    ss2 >> tExp;
                    
                    if( !isPositive )
                        tCoef = -tCoef;
                    //將解析出來的係數，指數丟到每一項中
                    terms[ tExp ].coef = tCoef;
                    //清空
                    temp = "";
                    temp2 = "";
                    tCoef = 0;
                    tExp = 0;
                    ss.str("");
                    ss2.str("");
                    ss.clear();
                    ss2.clear();
                }
            }
            
            //如果是常數項
            if( i == s.length() - 1 )
            {
                //字串轉數字
                ss << temp;
                ss >> tCoef;
                
                if( !isPositive )
                    tCoef = -tCoef;
                
                terms[ 0 ].coef = tCoef;
                //清空
                temp = "";
                tCoef = 0;
                ss.str("");
                ss.clear();
            }
            
        }
        //如果不是數字
        else
        {
            //遇到x代表係數已經能確定了
            if( ( s[i] == 'X' || s[i] == 'x' ) )
            {
                
                
                //如果係數為1
                if( temp == "" )
                    tCoef = 1;
                //如果係數不為1
                else
                {
                    ss << temp;
                    ss >> tCoef;
                }
                
                //如果是x項
                if( s[i + 1] != '^' )
                {
                    if( !isPositive )
                        tCoef = -tCoef;
                    
                    terms[ 1 ].coef = tCoef;
                    temp = "";
                    tCoef = 0;
                    ss.str("");
                    ss.clear();
                }
                
                
            }
            //當遇到指數時
            else if( s[i] == '^' ) {
                temp2 += s[i + 1];
            }
            //當遇到空白或者是到結尾時
            else if( s[i] == ' ' || ( i == s.length() - 1 ) )
            {
                ss2 << temp2;
                ss2 >> tExp;
                
                if( !isPositive )
                    tCoef = -tCoef;
                //將解析出來的係數，指數丟到每一項中
                terms[ tExp ].coef = tCoef;
                //清空
                temp = "";
                temp2 = "";
                tCoef = 0;
                tExp = 0;
                ss.str("");
                ss2.str("");
                ss.clear();
                ss2.clear();
            }
        }
    }
}

bool Polynomial::isAllZero() const
{
    bool isZero = true;
    for( int i = 0; i < length && isZero; i++ )
    {
        //如果有哪個係數不為0，停止迴圈
        if( terms[ i ].coef != 0 )
            isZero = false;
    }
    return isZero;
}

