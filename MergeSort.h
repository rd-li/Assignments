/*
 * Definition of class MergeSort
 *
 * author: Ruidan Li
 * date:   sep 8 2016
 */

#ifndef MERGESORT_H
#define MERGESORT_H

#include "ContactList.h"

using namespace std;

void MergeSort(ContactList &, int, int, int (*)(Contact&, Contact&));	// implementation of sort function
void Merge(ContactList&, int, int, int, int (*)(Contact&, Contact&)); //merge sort helper
#endif