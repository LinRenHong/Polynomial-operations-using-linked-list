//
//  Header.h
//  Polynomial
//
//  Created by 林仁鴻 on 2017/10/17.
//  Copyright © 2017年 林仁鴻. All rights reserved.
//

#ifndef TERM_H
#define TERM_H

class ListNode;

class Term//放係數與指數
{
    
    friend class Polynomial;
    friend class PolynomialList;
    friend class ListNode;
public:
    
    Term( const double & tCoef = 0, const int & tExp = 0 )
    : coef( tCoef ), exp( tExp ) {
        
    }

    
private :
    double coef;//係數
    int exp;//指數
};

#endif /* TERM_H */
