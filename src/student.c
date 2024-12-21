#include "student.h"
#include <string.h>

int compare(Student stu1, Student stu2) {
    return stu1.id - stu2.id;
}

Student createStudent(char* name, int id, int* birth, double* scores) {
    Student student;
    strcpy(student.name, name);
    student.id = id;
    for (int i = 0; i < 3; i++) {
        student.birth[i] = birth[i];
        student.scores[i] = scores[i];
    }
    return student;
}