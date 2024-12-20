#include "student.h"
#include "bTree.h"

#include <stdio.h>

int main(void) {
    BTree* tree = createBTree();

    Student stu1 = {"Jack", 1, {1, 2, 3}, {1, 2, 3}};
    Student stu2 = {"Jack", 2, {1, 2, 3}, {1, 2, 3}};
    Student stu3 = {"Mike", 33, {1, 2, 3}, {1, 2, 3}};
    Student stu4 = {"Mike", 444, {1, 2, 3}, {1, 2, 3}};
    Student stu5 = {"Mike", 55, {1, 2, 3}, {1, 2, 3}};
    insert(tree, stu1);
    insert(tree, stu2);
    insert(tree, stu3);
    insert(tree, stu4);
    insert(tree, stu5);
    StudentList* tmp = searchByName(tree, "Jack");
    printf("%d\n", tmp->size);
    tmp = searchByName(tree, "Mike");
    printf("%d\n", tmp->size);
    printf("%d\n", tree->size);
    printf("%s\n", searchById(tree, 3)->name);
    printf("%s\n", searchById(tree, 4)->name);
    printf("%s\n", searchById(tree, 5)->name);

    return 0;
}