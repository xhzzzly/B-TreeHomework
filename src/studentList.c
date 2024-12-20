#include "studentList.h"
#include <stdlib.h>

StudentListNode* createListNode(Student* obj, StudentListNode* next) {
    StudentListNode* node = (StudentListNode*)malloc(sizeof(StudentListNode));
    node->student = obj;
    node->next = next;
    return node;
}

StudentList* createList(void) {
    StudentList* list = (StudentList*)malloc(sizeof(StudentList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void addFront(StudentList* list, Student* obj) {
    ++list->size;
    list->head = createListNode(obj, list->head);
}

Student* front(StudentList* list) { return list->head == NULL ? NULL : list->head->student; }

Student* removeFront(StudentList* list) {
    Student* obj = front(list);
    StudentListNode* tmp = list->head;
    if (list->head != NULL) {
        --list->size;
        list->head = list->head->next;
        free(tmp);
    }
    return obj;
}

void destroy(StudentList* obj) {
    while (obj->size > 0) removeFront(obj);
    free(obj);
}