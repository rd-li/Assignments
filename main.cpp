/*
 *   main.cpp driver for sort comparison exercise
 *
 * author: S Thomas
 * date:   2016
 */

#include "main.h"

// Global constants
const int STEPSIZE = 1000;
// increment size for increasing length of list to be sorted
const int NUMSORTS = 30000/STEPSIZE;   // number of sorts that will be performed on increasing length lists

// get_timestamp(): returns current time in seconds
// ------------------------------------------------------------------------
timestamp_t get_timestamp () {
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

// save( filename, timings ): save timing results to filename
// file format is:
//       problemSize  time
//       problemSize  time
//       ...
// ------------------------------------------------------------------------
void save(string filename, double timings[]) {
    ofstream outfile;
    outfile.open(filename);
    if ( !outfile.is_open() ) {
        cout << "Error opening file " << filename << endl;
    }

    cout << "\nWriting results to file " << filename << endl;
    for (int i = 0; i < NUMSORTS; i++) {
        outfile << STEPSIZE * (i+1) << ", " << timings[i] << endl;
    }
    outfile.close();
}

int main() {
 
    double timings[NUMSORTS];	// array of timing results
    string timingFileName;
    
    // run the sort(s) multiple times with increasing list sizes
    // STEPSIZE is the delta for increasing the length of the list 
    for( int run=0; run<NUMSORTS; run++ ){

        // increase the number of values to sort by increments of STEPSIZE
        int sortsize  = (run + 1) * STEPSIZE;

        // create a ContactList of length "sortsize" by reading data from a file
        ContactList contactList("data/contacts", sortsize);

        // sanity check
        cout << "\nFirst 10 records before sorting\n";
        contactList.print(0,9);   // prints from contacts

        // Time the sorting algorithm
        timestamp_t startTime = get_timestamp();	  // start the timer

        /*timingFileName = "InsertionSortTimings";
	    InsertionSort( contactList, Contact::compareName  );
	    InsertionSort( contactList, Contact::compareState );*/

        /*timingFileName = "MergeSortTimings";
        MergeSort( contactList, 0, sortsize-1, Contact::compareName  );
        MergeSort( contactList, 0, sortsize-1, Contact::compareState );*/

        timingFileName = "QuickSortTimings";
        QuickSort( contactList, 0, sortsize-1, Contact::compareName  );
        QuickSort( contactList, 0, sortsize-1, Contact::compareState );

        timestamp_t endTime = get_timestamp();	  // stop the timer

        timings[run] = (endTime - startTime) / 1000000.0L;  // record the elapsed time

        // verify results by printing first 10 contacts
        cout << "\nFirst 10 Contacts after sorting\n";
        contactList.print(0,9);   // prints from contacts

        // and the last 10 contacts
        cout << "\nLast 10 Contacts after sorting\n";
        contactList.print(sortsize-10,sortsize-1);   // prints data in contacts

        cout << "Sorted " << sortsize << " records" << endl;
    }
    // save all sort times to a file
    save( "data/" + timingFileName, timings );
}



