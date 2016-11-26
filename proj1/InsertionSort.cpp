#include "InsertionSort.h"

void InsertionSort(ContactList& data, int (*compar)(Contact&, Contact&)) {

    int size = data.length();
    int j;  // j iterates through the already sorted items
	
    // simple insertion sort
    for (int i = 1; i < size; i++) {
        j = i;
        while (j > 0 && compar(data.contacts[j-1], data.contacts[j]) > 0 ) {
            swap( data.contacts[j-1], data.contacts[j] );
            j--;
        } //end of while loop
    } //end of for loop
}

