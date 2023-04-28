#include "database.h"

int id_uniqueness_check(int id, Student_t *p_database, int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        if (*p_database[i].id == id)
            return 0;
    }
    return 1;
}

int login_uniqueness_check(char *login, Student_t *p_database, int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        if (!strcmp(p_database[i].login, login))
            return 0;
    }
    return 1;
}

int id_index(int id, Student_t *p_database) {
    for (int i = 0; i < 50; i++) {
        if (*p_database[i].id == id)
            return i;
    }
    return -1;
}

int login_index(const char *login, Student_t *p_database) {
    for (int i = 0; i < 50; i++) {
        if (!strcmp(login, p_database[i].login))
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

void password_input(uint8_t hash[SIZE_OF_SHA_256_HASH]) {
    char password[PASSWORD_SIZE];
    str_input(password, PASSWORD_SIZE);
    calc_sha_256(hash, password, strlen(password));
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

void add_student_to_file_and_db(Student_t *p_database, int *number_of_students, char *file_path) {
    int id_temp = id_input();
    if (!id_uniqueness_check(id_temp, p_database, *number_of_students)) {
        puts("ID is not unique!\n");
        return;
    }
    int *id;
    char *name;
    char *student_card_number;
    float *average_grade;
    char *login;
    char login_input[LOGIN_SIZE];
    char *hash_str;
    uint8_t hash[SIZE_OF_SHA_256_HASH];

    id = (int *) malloc(sizeof(int));
    *id = id_temp;
    name = (char *) malloc(NAME_SIZE * sizeof(char));
    student_card_number = (char *) malloc(STUDENT_CARD_SIZE * sizeof(char));
    average_grade = (float *) malloc(sizeof(float));
    hash_str = (char *) malloc(HASH_STR_SIZE * sizeof(char));

    puts("Enter name of the student.");
    str_input(name, NAME_SIZE);

    puts("Enter student's card number.");
    str_input(student_card_number, STUDENT_CARD_SIZE);

    float average_grade_temp = grade_input();
    *average_grade = average_grade_temp;

    puts("Enter student's login.");
    str_input(login_input, LOGIN_SIZE);
    if (!login_uniqueness_check(login_input, p_database, *number_of_students)) {
        puts("Login is not unique!");
        return;
    }
    login = (char *) malloc(LOGIN_SIZE * sizeof(char));
    strcpy(login, login_input);
    puts("Enter student's password.");
    password_input(hash);
    uint_to_str(hash, hash_str);
    FILE *p_file = fopen(file_path, "a");
    if (*number_of_students != 0)
        fputs("\n", p_file);
    fprintf(p_file, "%d:%s:%s:%.2f:%s:%s", *id, name, student_card_number, *average_grade, login, hash_str);
    fclose(p_file);
    Student_t student = {id, name, student_card_number, average_grade, login, hash_str};
    add_student(p_database, number_of_students, student);
}

void add_student(Student_t *p_database, int *number_of_students, Student_t student) {
    p_database[*number_of_students] = student;
    (*number_of_students)++;
}

void delete_student(Student_t *p_database, int *number_of_students, char *file_path) {
    if (*number_of_students == 0) {
        puts("Database is empty!");
        return;
    }
    int id = id_input();
    int index = id_index(id, p_database);
    if (index == -1) {
        puts("ID not found in this database!");
        return;
    }
    free(p_database[index].id);
    free(p_database[index].name);
    free(p_database[index].student_card_number);
    free(p_database[index].average_grade);
    free(p_database[index].login);
    free(p_database[index].hash);
    (*number_of_students)--;
    FILE *p_file = fopen(file_path, "w");
    for (int i = 0; i < *number_of_students; i++) {
        Student_t student = p_database[i];
        fprintf(p_file, "%d:%s:%s:%.2f:%s:%s", *student.id, student.name, student.student_card_number,
                *student.average_grade, student.login, student.hash);
    }
    fclose(p_file);
}

void student_info(Student_t *p_database) {
    int id = id_input();
    int index = id_index(id, p_database);
    if (index == -1) {
        puts("ID not found in this database!\n");
        return;
    }
    char *name = p_database[index].name;
    char *student_card_number = p_database[index].student_card_number;
    float *average_grade = p_database[index].average_grade;
    printf("Student with id: %d\nName: %s\nStudent card number: %s\nAverage grade: %.2f\n\n",
           id, name, student_card_number, *average_grade);
}

void print_average_grades(Student_t *p_database, int number_of_students) {
    for (int i = 0; i < number_of_students; i++) {
        char *name = p_database[i].name;
        float *average_grade = p_database[i].average_grade;
        printf("%s: %.2f\n", name, *average_grade);
    }
    puts("");
}

void authentication(Student_t *p_database) {
    char login[LOGIN_SIZE];
    uint8_t hash[SIZE_OF_SHA_256_HASH];
    char hash_str[HASH_STR_SIZE];
    puts("Enter student's login.");
    str_input(login, LOGIN_SIZE);
    int index = login_index(login, p_database);
    printf("Index: %d\n", index);
    puts("Enter student's password.");
    password_input(hash);
    uint_to_str(hash, hash_str);
    printf("%s %s\n", p_database[index].hash, hash_str);
    if (!strcmp(p_database[index].hash, hash_str)) {
        puts("Authentication successful\n");
    } else
        puts("Wrong password\n");
}

void uint_to_str(uint8_t hash[], char hash_str[]) {
    for (int i = 0; i < 32; i++) {
        hash_str += sprintf(hash_str, "%02x", hash[i]);
    }
}