/*
 * Definition of class ContactList
 *
 * author: S Thomas
 * date:   2016
 */

#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Contact.h"

using namespace std;

class ContactList {
private:
    string dataFile;              // name of Contact data file used to populate this ContactList
    
public:
    ContactList( string, int );   // constructor
    ContactList(const ContactList&, const int, const int);   // copy constructor

    vector<Contact> contacts;     // data to be sorted
    void print( int, int );       // print ContactList elements [start...end]
    int length() { return (int) contacts.size(); };

};

#endif
