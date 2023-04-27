#include "file_functions.h"

void add_students_from_file(Student_t *p_database, int *number_of_students, FILE *p_file) {
    char line[MAX_LINE_LEN];
    char *id_tok, *name_tok, *student_card_number_tok, *average_grade_tok, *login_tok, *hash_tok;
    while (fgets(line, MAX_LINE_LEN, p_file) != NULL) {
        char *name, *student_card_number, *login, *hash;

        id_tok = strtok(line, ":");
        name_tok = strtok(NULL, ":");
        student_card_number_tok = strtok(NULL, ":");
        average_grade_tok = strtok(NULL, ":");
        login_tok = strtok(NULL, ":");
        hash_tok = strtok(NULL, ":");

        name = (char *) malloc(strlen(name_tok) * sizeof(char));
        student_card_number = (char *) malloc(strlen(student_card_number_tok) * sizeof(char));
        login = (char *) malloc(strlen(login_tok) * sizeof(char));
        hash = malloc(strlen(hash_tok) * sizeof(char));

        strcpy(name, name_tok);
        strcpy(student_card_number, student_card_number_tok);
        strcpy(login, login_tok);
        strcpy(hash, hash_tok);

        int id = strtol(id_tok, NULL, 10);
        float average_grade = strtof(average_grade_tok, NULL);

        Student_t student = {id, name, student_card_number, average_grade, login, hash};
        add_student(p_database, number_of_students, student);
    }
}

// id:name:student_card_num:gpa:login:hash