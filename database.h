#ifndef TASK3_DATABASE_H
#define TASK3_DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sha-2/sha-256.h"

#define DB_CAPACITY 50
#define NAME_SIZE 15
#define STUDENT_CARD_SIZE 7
#define LOGIN_SIZE 10
#define PASSWORD_SIZE 15
#define HASH_SIZE 64
#define BUFFER 30
#define MAX_INT 9
#define MAX_FLOAT 7

typedef struct { // id:name:student_card_num:gpa:login:hash
    int id;
    char *name;
    char *student_card_number;
    float average_grade;
    char *login;
    uint8_t *hash;
} Student_t;

enum choice {
    ADD_STUDENT = 1,
    DELETE_STUDENT,
    STUDENT_INFO,
    PRINT_AVERAGE_GRADES,
    AUTHENTICATION,
    EXIT
};

int id_uniqueness_check(int id, Student_t *p_database, int number_of_students);

int id_index(int id, Student_t *p_database);

int login_index(const char *login, Student_t *p_database);

int id_input();

void str_input(char *input, int data_size);

float grade_input();

int int_check(char data[sizeof(int)]);

int float_check(char data[sizeof(float)]);

void add_student_from_terminal(Student_t *p_database, int *number_of_students);

void add_student(Student_t *p_database, int *number_of_students, Student_t student);

void delete_student(Student_t *p_database, int *number_of_students);

void student_info(Student_t *p_database);

void print_average_grades(Student_t *p_database, int number_of_students);

void authentication(Student_t *p_database);

#endif