#ifndef STUDENT_H
#define STUDENT_H

#define NAME_STRING_LENGTH 100

typedef struct {
    char name[NAME_STRING_LENGTH];
    int id; // 注意每位学生的id唯一
    int birth[3]; // 下标0到2分别是年、月、日
    double scores[3]; // 下标0到2分别是语文、数学、英语的成绩
} Student;

extern int compare(Student, Student);

#endif