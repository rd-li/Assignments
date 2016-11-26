/*
 * Definition of class Contact
 * A Contact is represented by a 6-tuple (name, address, state,  zip, phone, SSN)
 *
 * author: S Thomas
 * date:   2016
 */

#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Contact {
private:
    string name;
    string address;
    string state;
    int zip;       // 5-digit zip
    string phone;
    string SSN;    // includes hyphens
    
public:
    Contact( string, string, string, int, string, string ); // constructor
    Contact(const Contact&); // copy constructor
    void print();                                   // print a Contact instance
    string getState(){ return state; };             // inline accessor
    static int compareName( Contact&, Contact& );   // returns -1/0/1
    static int compareZip( Contact&, Contact& );    // returns -1/0/1
    static int compareSSN( Contact&, Contact& );    // returns -1/0/1
    static int compareState( Contact&, Contact& );  // returns -1/0/1
};

#endif
