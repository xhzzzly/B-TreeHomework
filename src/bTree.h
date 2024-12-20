#ifndef B_TREE_H
#define B_TREE_H

#include "student.h"
#include "studentList.h"
#include <stdbool.h>

#define MAX_ORDER 5
#define MIN_ORDER ((MAX_ORDER) / 2)

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

// �����ӿ�
extern BTreeNode* createNode(bool isLeaf);
extern Student* search(BTree* tree, Student key);
extern void insert(BTree* tree, Student key);
extern void deleteStudent(BTree* tree, Student key);
extern BTree* createBTree(void);
extern StudentList* searchByName(BTree* tree, const char* name);
extern Student* searchById(BTree* tree, int id);

// ��������
extern StudentList* searchByNameInNode(BTreeNode* node, const char* name);
extern Student* searchInNode(BTreeNode* node, Student key);
extern void insertNonFull(BTreeNode* node, Student key);
extern void splitChild(BTreeNode* parent, int index);
extern BTreeNode* findPredecessor(BTreeNode* node, int index);
extern BTreeNode* findSuccessor(BTreeNode* node, int index);
extern void deleteKeyFromNode(BTreeNode* node, int index);
extern void deleteKey(BTreeNode* node, Student key);
extern void mergeChildren(BTreeNode* node, int index);
extern void fixChild(BTreeNode* parent, int index);

#endif