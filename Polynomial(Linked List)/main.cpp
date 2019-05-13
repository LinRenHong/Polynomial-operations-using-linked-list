//
//  main.cpp
//  Polynomial(Linked List)
//
//  Created by 林仁鴻 on 2019/5/14.
//  Copyright © 2019 林仁鴻. All rights reserved.
//


#include <iostream>
#include "PolynomialList.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    string first, second;
    int expIndex, expIndex2, value;
    
    cout << "Please enter first polynomial ( ex : x^2 + 2x + 1 ) : " << endl;
    getline( cin, first );
    
    cout << "\nPlease enter second polynomial ( ex : x^2 + 2x + 1 ) : " << endl;
    getline( cin, second );
    
    Polynomial p(first);
    Polynomial p2(second);
    
    PolynomialList polylist(p);
    PolynomialList polylist2(p2);
    
    
    cout << "\nFirst polynomial is : " << endl;
    polylist.print();
    
    cout << "Second polynomial is : " << endl;
    polylist2.print();
    
    
    cout << "Add a term by exp in first polynomial : ";
    cin >> expIndex;
    polylist.addTerm(expIndex);
    
    cout << "\nAfter add a new term in first polynomial : " << endl;;
    polylist.print();
    
    cout << "Remove a term by exp in second polynomial: ";
    cin >> expIndex2;
    polylist2.removeExistTerm( expIndex2 );
    
    
    cout << "\nAfter remove a term in second polynomial : " << endl;
    polylist2.print();
    
    cout << "-------------------------------------\n" << endl;
    
    cout << "First polynomial is : " << endl;
    polylist.print();
    
    cout << "Second polhynomial is : " << endl;
    polylist2.print();
    
    cout << "-------------------------------------" << endl;
    
    cout << "\nPlease enter a value : ";
    cin >> value;
    
    cout << "\nFirst polynomial solution : " << polylist.solution( value ) << endl;
    cout << "\nSecond polynomial solution : " << polylist2.solution( value ) << endl << endl;
    
    cout << "-------------------------------------\n" << endl;
    
    cout << "First polynomial is : " << endl;
    cout << polylist;
    
    cout << "Second polhynomial is : " << endl;
    cout << polylist2;
    
    cout << "-------------------------------------" << endl;
    
    
    cout << "\nFirst polynomial + second polynomial = " << endl;
    ( polylist + polylist2 ).print();
    
    cout << "First polynomial - second polynomial = " << endl;
    ( polylist - polylist2 ).print();
    
    cout << "First polynomial * second polynomial = " << endl;
    ( polylist * polylist2 ).print();
    
    cout << "-------------------------------------" << endl;
}
