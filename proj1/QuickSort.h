/*
 * Definition of class QuickSort
 *
 * author: Ruidan Li
 * date:   sep 8 2016
 */

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "ContactList.h"

using namespace std;

void QuickSort(ContactList &, int, int, int (*)(Contact&, Contact&));	// implementation of sort function

#endif