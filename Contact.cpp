/*
 * Implementation of class Contact
 *
 * author: S Thomas
 * date:   2016
 */

#include "Contact.h"

// Constructor 
// ------------------------------------------------------------------------
Contact::Contact(string namearg, string addressarg, string statearg, int ziparg, string phonearg, string SSNarg) {
    name    = namearg;
    address = addressarg;
    state   = statearg;
    zip     = ziparg;
    phone   = phonearg;
    SSN     = SSNarg;
}

// Copy constructor
// ------------------------------------------------------------------------
Contact::Contact(const Contact& cont)
{
    name    = cont.name;
    address = cont.address;
    state   = cont.state;
    zip     = cont.zip;
    phone   = cont.phone;
    SSN     = cont.SSN;
}

// compareName( other ): return -1 if thisone value is less than other.name
//                      return  0 if thisone value is equal to other.name
//                      return +1 if thisone value is greater than other.name
// ------------------------------------------------------------------------
int Contact::compareName( Contact& thisone, Contact& other ) {
     return thisone.name.compare( other.name );
}

// compareZip( other ): return -1 if thisone value is less than other.zip
//                      return  0 if thisone value is equal to other.zip
//                      return +1 if thisone value is greater than other.zip
// ------------------------------------------------------------------------
int Contact::compareZip( Contact& thisone, Contact& other ) {
    int temp = thisone.zip - other.zip;
    return ( 0 < temp ) - ( temp < 0 );
}

// compareSSN( other ): return -1 if thisone value is less than other.SSN
//                      return 0 if thisone value is equal to other.SSN
//                      return +1 if thisone value is greater than other.SSN
// ------------------------------------------------------------------------
int Contact::compareSSN( Contact& thisone, Contact& other ) {
    return thisone.SSN.compare( other.SSN );
}

// compareState( other ): return -1 if thisone state is less than other.state
//                        return 0 if thisone value is equal to other.state
//                        return +1 if thisone value is greater than other.state
// ------------------------------------------------------------------------
int Contact::compareState( Contact& thisone, Contact& other ) {
    return thisone.state.compare( other.state );
}

// print():  print a representation of a Contact object
// ------------------------------------------------------------------------
void Contact::print( ) {
    cout << name << " | "
              << address << ", " << state << " | "
              << setfill('0') << setw(5) << zip << " | " << phone << " | " << SSN << endl;
}

