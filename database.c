#include "database.h"

int id_uniqueness_check(int id, Student_t *p_database, int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        if (p_database[i].id == id)
            return 0;
    }
    return 1;
}

int id_index(int id, Student_t *p_database) {
    for (int i = 0; i < 50; i++) {
        if (p_database[i].id == id)
            return i;
    }
    return -1;
}

int id_input() {
    char id_str[BUFFER];
    int i = 0;
    puts("Enter student's ID.");
    do {
        if (i > 0)
            printf("This value is not a number or longer than %d. Try again.\n", MAX_INT);
        scanf("%s", id_str);
        i++;
    } while (!int_check(id_str) || strlen(id_str) > MAX_INT);
    return strtol(id_str, NULL, 10);
}

float grade_input() {
    char average_grade_str[BUFFER];
    int i = 0;
    puts("Enter average grade.");
    do {
        if (i > 0)
            printf("This value is not a float number or longer than %d. Try again.\n", MAX_FLOAT);
        scanf("%s", average_grade_str);
        i++;
    } while (!float_check(average_grade_str) || strlen(average_grade_str) > MAX_FLOAT);
    return strtof(average_grade_str, NULL);
}

void str_input(char *input, int data_size) {
    int i = 0;
    do {
        if (i > 0)
            printf("Length must be equal or less than %d. Try again.\n", data_size);
        scanf("%s", input);
        i++;
    } while (strlen(input) > data_size);
}

void password_input(char *hash) {
    char password[PASSWORD_SIZE];
    str_input(password, PASSWORD_SIZE);
    printf("%s", password);
}

int int_check(char data[MAX_INT]) {
    for (int i = 0; i < strlen(data); i++) {
        if (!isdigit(data[i]))
            return 0;
    }
    return 1;
}

int float_check(char data[MAX_FLOAT]) {
    for (int i = 0; i < strlen(data); i++) {
        if (isdigit(data[i]) || data[i] == '.')
            continue;
        else
            return 0;
    }
    return 1;
}

void add_student_from_terminal(Student_t *p_database, int *number_of_students) {
    int id = id_input();
    if (!id_uniqueness_check(id, p_database, *number_of_students)) {
        puts("ID is not unique!\n");
        exit(EXIT_FAILURE);
    }
    char *name;
    char *student_card_number;
    char *login;
    char *hash;
    name = (char *) malloc(10 * sizeof(char));
    student_card_number = (char *) malloc(10 * sizeof(char));
    login = (char *) malloc(10 * sizeof(char));
    hash = (char *) malloc(10 * sizeof(char));
    puts("Enter name of the student.");
    str_input(name, NAME_SIZE);
    puts("Enter student's card number.");
    str_input(student_card_number, STUDENT_CARD_SIZE);
    float average_grade = grade_input();
    puts("Enter student login.");
    str_input(login, LOGIN_SIZE);
    puts("Enter password of the student.");
    password_input(hash);
    Student_t student = {id, name, student_card_number, average_grade, login, hash};
    add_student(p_database, number_of_students, student);
}

void add_student(Student_t *p_database, int *number_of_students, Student_t student) {
    p_database[*number_of_students] = student;
    (*number_of_students)++;
}

void delete_student(Student_t *p_database, int *number_of_students) {
    if (*number_of_students == 0)
        puts("Database is empty!");
    else {
        int id = id_input();
        int index = id_index(id, p_database);
        if (index != -1) {
            free(p_database[index].name);
            free(p_database[index].student_card_number);
            for (int i = index; i < DB_CAPACITY - 1; i++)
                p_database[i] = p_database[i + 1];
            (*number_of_students)--;
        } else
            puts("ID not found in this database!");
    }
}

void student_info(Student_t *p_database) {
    int id = id_input();
    int index = id_index(id, p_database);
    if (index != -1) {
        char *name = p_database[index].name;
        char *student_card_number = p_database[index].student_card_number;
        float average_grade = p_database[index].average_grade;
        printf("Student with id: %d\nName: %s\nStudent card number: %s\nAverage grade: %.2f\n\n",
               id, name, student_card_number, average_grade);
    } else {
        puts("ID not found in this database!\n");
    }
}

void print_average_grades(Student_t *p_database, int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        char *name = p_database[i].name;
        float average_grade = p_database[i].average_grade;
        printf("%s: %.2f\n", name, average_grade);
    }
    puts("");
}