#ifndef STUDENT_H
#define STUDENT_H

#define NAME_STRING_LENGTH 100

typedef struct {
    char name[NAME_STRING_LENGTH];
    int id;
    int birth[3]; // 下标0到2分别是年、月、日
} Student;

extern int compare(Student, Student);

#endif