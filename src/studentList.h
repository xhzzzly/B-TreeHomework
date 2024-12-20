#ifndef STUDENT_LIST_H
#define STUDENT_LIST_H

#include "student.h"

typedef struct StudentListNode {
    Student* student;
    struct StudentListNode* next;
} StudentListNode;

typedef struct {
    StudentListNode* head;
    int size;
} StudentList;

// 公共接口
StudentList* createList(void);
void addFront(StudentList* list, Student* obj);
Student* front(StudentList* list);
Student* removeFront(StudentList* list);
void destroy(StudentList* obj);

// 其他函数
StudentListNode* createListNode(Student* obj, StudentListNode* next);

#endif