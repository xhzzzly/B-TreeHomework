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

// �����ӿ�
StudentList* createList(void);
void addFront(StudentList* list, Student* obj);
Student* front(StudentList* list);
Student* removeFront(StudentList* list);
void destroy(StudentList* obj);

// ��������
StudentListNode* createListNode(Student* obj, StudentListNode* next);

#endif