#ifndef TASK3_FILE_FUNCTIONS_H
#define TASK3_FILE_FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"

#define MAX_LINE_LEN 128

void add_students_from_file(Student_t *p_database, int *number_of_students, FILE *p_file);


#endif
