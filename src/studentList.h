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

extern StudentList* createList(void);
extern void addFront(StudentList* list, Student* obj);
extern Student* front(StudentList* list);
extern Student* removeFront(StudentList* list);
extern void destroy(StudentList* obj);

#endif