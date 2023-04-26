#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "database.h"
#include "merge_sort.h"

int main() {
    int running = true;
    Student_t *database;
    database = (Student_t *) malloc(DB_CAPACITY * (sizeof(Student_t)));
    char input;
    int choice;
    int number_of_students = 0;
    while (running) {
        printf("Total number of students: %d\n", number_of_students);
        printf("1. Add student\n2. Delete student\n3. Student info\n4. Print average grades\n5. Exit\n");
        scanf("%s", &input);
        choice = strtol(&input, NULL, 10);
        switch (choice) {
            case ADD_STUDENT:
                add_student(database, &number_of_students);
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
            case EXIT:
                running = false;
                break;
            default:
                puts("Incorrect input!");
                break;
        }
    }
    free(database);
}

//0:Andrew:1337:4.15:andy:a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3
//1:Nikita:228:3.71:nikos:b2bbddeabbceef232628ada1603ba4dda1d29c73d360cfa0a608baa5a70a7152