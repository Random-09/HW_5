#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "database.h"
#include "merge_sort.h"
#include "file_functions.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        puts("Wrong number of arguments");
        exit(EXIT_FAILURE);
    }
    FILE *p_file = fopen(argv[1], "r");
    if (p_file == NULL) {
        puts("Error opening file");
        exit(EXIT_FAILURE);
    }
    Student_t *database;
    database = (Student_t *) malloc(DB_CAPACITY * (sizeof(Student_t)));
    int running = true;
    char input;
    int choice;
    int number_of_students = 0;
    add_students_from_file(database, &number_of_students, p_file);
    while (running) {
        printf("Total number of students: %d\n", number_of_students);
        printf("1. Add student\n2. Delete student\n3. Student info\n4. Print average grades\n"
               "5. Authentication\n6. Exit\n");
        scanf("%s", &input);
        choice = strtol(&input, NULL, 10);
        switch (choice) {
            case ADD_STUDENT:
                add_student_from_terminal(database, &number_of_students);
                break;
            case DELETE_STUDENT:
                delete_student(database, &number_of_students);
                break;
            case STUDENT_INFO:
                student_info(database);
                break;
            case PRINT_AVERAGE_GRADES:
                merge_sort(database, 0, number_of_students - 1);
                print_average_grades(database, number_of_students);
                break;
            case AUTHENTICATION:
                authentication(database);
                break;
            case EXIT:
                running = false;
                break;
            default:
                puts("Incorrect input!");
                break;
        }
    }
    fclose(p_file);
    free(database);
}

// TODO

// 1) Функция перевода хэша из uin8_t в string

// 2) allocate memory for each data type in Student_t (int and float)