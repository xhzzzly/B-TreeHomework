#ifndef STUDENT_H
#define STUDENT_H

#define NAME_STRING_LENGTH 100

typedef struct {
    char name[NAME_STRING_LENGTH];
    int id; // 唯一id
    int birth[3]; // 生日，对应年、月、日
    double scores[3]; // 语、数、英
} Student;

extern int compare(Student, Student);
extern Student createStudent(char* name, int id, int* birth, double* scores);

#endif