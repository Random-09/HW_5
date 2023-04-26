#include "file_functions.h"

void add_students_from_file(Student_t *p_database, int *number_of_students, FILE *p_file) {
    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, p_file) != NULL) {
        char *id_str = strtok(line, ":");
        char *name = strtok(NULL, ":");
        char *student_card_number = strtok(NULL, ":");
        char *average_grade_str = strtok(NULL, ":");
        char *login = strtok(NULL, ":");
        char *hash = strtok(NULL, ":");
        int id = strtol(id_str, NULL, 10);
        float average_grade = strtof(average_grade_str, NULL);
        Student_t student = {id, name, student_card_number, average_grade, login, hash};
        add_student(p_database, number_of_students, student);
    }
}

// id:name:student_card_num:gpa:login:hash