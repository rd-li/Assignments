#include "QuickSort.h"

void QuickSort(ContactList& data, int too_big, int too_small, int (*compar)(Contact&, Contact&))
{
    int pivot = too_big;    // pivot (take the middle one)
    int i = too_big + 1;                        // stores the data[i] > pivot
    int j = too_small;                      // stores the data[j] <= pivot

    while(i < j)    // while two indices haven't crossed yet
    {
        while(i <= too_small && compar(data.contacts[i], data.contacts[pivot]) <= 0)
            i ++;
        while(j > too_big && compar(data.contacts[j], data.contacts[pivot]) > 0)
            j --;
        if(i < j)   // swap the two based on their relative relation to pivot
            swap(data.contacts[i], data.contacts[j]);
    }
    swap(data.contacts[j], data.contacts[pivot]);   // j is the current too_small position
    pivot = j;      // update pivot
    if(too_big < (pivot - 1))       // make sure the pivot index is valid
        QuickSort(data, too_big, pivot - 1, compar);    // first half
    if((pivot + 1) < too_small)
        QuickSort(data, pivot + 1, too_small, compar);  // second half
}

