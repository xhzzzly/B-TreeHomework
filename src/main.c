#include "student.h"
#include "bTree.h"

#include <stdio.h>

int main(void) {
    BTree* tree = createBTree();

    Student stu1 = {"Jack", 1, {1, 2, 3}};
    insert(tree, stu1);

    printf("size: %d\n", tree->size);
    printf("Let's find id1\n");
    Student trg = {"Jack", 1, {1, 2, 3}};
    Student* obj = search(tree, trg);
    printf("%p\n", obj);

    printf("Let's find id3\n");
    trg.id = 3;
    obj = search(tree, trg);
    printf("%p\n", obj);

    printf("找一下Jack %p\n", searchByName(tree, "Jack"));

    return 0;
}