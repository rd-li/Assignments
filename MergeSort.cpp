#include "MergeSort.h"

void MergeSort(ContactList& data, int p, int r, int (*compar)(Contact&, Contact&))
{

    int q = 0;
    if(p < r)       // check if the indices given are valid
    {
        q = (int)((p + r) / 2.0);           // position to split the list
        MergeSort(data, p, q, compar);      // first half
        MergeSort(data, q + 1, r, compar);  // second half
        Merge(data, p, q, r, compar);       // merge
    }
}

void Merge(ContactList& data, int p, int q, int r, int (*compar)(Contact&, Contact&))
{
    int n1 = q - p + 1;     // first half (left)
    int n2 = r - q;         // second half (right)
    ContactList LeftContactList(data, p, p + n1);
    ContactList RightContactList(data, q + 1, q + 1 + n2);
    int i = 0;      // set to the start of the left sub-list
    int j = 0;      // set to the start of the right sub-list
    int k = p;      // set to the start of the merged list
    // Merge
    while (i < n1 && j < n2)
    {   // place the smaller one into the merged list
        if (compar(LeftContactList.contacts[i], RightContactList.contacts[j]) <= 0)
        {
            data.contacts[k] = Contact(LeftContactList.contacts[i]);
            i++;
        }
        else
        {
            data.contacts[k] = Contact(RightContactList.contacts[j]);
            j++;
        }
        k++;    // increment merged list
    }
    // check for anything left in both sub-lists
    while (i < n1)
    {
        data.contacts[k] = Contact(LeftContactList.contacts[i]);
        i++;
        k++;
    }
    while (j < n2)
    {
        data.contacts[k] = Contact(RightContactList.contacts[j]);
        j++;
        k++;
    }
}