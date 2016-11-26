/*
 * Implementation of class ContactList
 *
 * author: S Thomas
 * date:   2016
 */

#include "ContactList.h"

// Constructor 
//   Parameters:  file name, number of lines to read
// ------------------------------------------------------------------------
ContactList::ContactList(string filename, int howmany) {

    // open file for reading
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error opening file " << filename << endl;
    }

    // Read text data from filename, one line at a time
    string line;
    cout << "Reading data from file...\n";
    for( int i=0; i<howmany; i++ ){
        getline(infile, line);
        stringstream ssline( line );
        vector<string> elements;     // elements of an individual line of data file
        string stemp;
        // split line at '|' character into 6 parts
        while( getline(ssline, stemp, '|') )
            elements.push_back( stemp );        
        string name    = elements[0];
        string address = elements[1];
        string state   = elements[2];
        int    zip     = stoi( elements[3] );
        string phone   = elements[4];
        string SSN     = elements[5];
        // create a Contact and push onto list2sort
        Contact tempContact = Contact( name, address, state, zip, phone, SSN );
        contacts.push_back( tempContact );
    }
    cout << "\nRead " << contacts.size() << " lines\n";
    infile.close();
}

// print(int start, int end):
//   print sorted vector positions [start ... end] to the screen.
// ------------------------------------------------------------------------
void ContactList::print(int start, int end) {
    cout << endl;
    for (int i = start; i <= end; i++) {
        contacts[i].print();
    }
}

/* copy constructor */
ContactList::ContactList(const ContactList& data, const int start, const int end)
{
    for(int i = start; i < end; i++)
    {
        Contact tempContact = Contact(data.contacts[i]);
        contacts.push_back( tempContact );
    }
}