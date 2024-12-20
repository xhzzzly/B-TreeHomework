#ifndef B_TREE_H
#define B_TREE_H

#include "student.h"
#include "studentList.h"
#include <stdbool.h>

#define MAX_ORDER 5
#define MIN_ORDER (3)

typedef struct BTreeNode {
    Student keys[MAX_ORDER - 1];
    struct BTreeNode* children[MAX_ORDER];
    int numKeys;
    bool isLeaf;
} BTreeNode;

typedef struct {
    BTreeNode *root;
    int size;
} BTree;

extern BTreeNode* createNode(bool isLeaf);
extern Student* search(BTree* tree, Student key);
extern void insert(BTree* tree, Student key);
extern void deleteStudent(BTree* tree, Student key);
extern BTree* createBTree(void);
extern StudentList* searchByName(BTree* tree, const char* name);
extern Student* searchById(BTree* tree, int id);
extern void deleteById(BTree* tree, int id);

#endif