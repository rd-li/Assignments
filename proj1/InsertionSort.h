/*
 * Definition of class InsertionSort
 *
 * author: S Thomas
 * date:   2016
 */

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "ContactList.h"

using namespace std;

void InsertionSort(ContactList &, int (*)(Contact&, Contact&));	// implementation of sort function

#endif
