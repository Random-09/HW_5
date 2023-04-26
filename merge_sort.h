#ifndef TASK3_MERGE_SORT_H
#define TASK3_MERGE_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include "database.h"

void merge(Student_t *array, int left, int middle, int right);

void merge_sort(Student_t *array, int left, int right);

#endif