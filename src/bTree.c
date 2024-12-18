#include "bTree.h"

#include <stddef.h>
#include <malloc.h>
#include <string.h>

BTree* createBTree(void) {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = createNode(true);
    tree->size = 0;
    return tree;
}

BTreeNode* createNode(bool isLeaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < MAX_ORDER; ++i) {
        node->children[i] = NULL;
    }
    return node;
}

Student* search(BTree* tree, Student key) {
    return searchInNode(tree->root, key);
}

Student* searchInNode(BTreeNode* node, Student key) {
    int i = 0;
    while (i < node->numKeys && compare(key, node->keys[i]) > 0) {
        i++;
    }
    if (i < node->numKeys && compare(key, node->keys[i]) == 0) {
        return &node->keys[i];
    }
    if (node->isLeaf) {
        return NULL;
    }
    return searchInNode(node->children[i], key);
}

extern Student* searchById(BTree* tree, int id) {
    Student trg;
    trg.id = id;
    return search(tree, trg);
}

Student* searchByNameInNode(BTreeNode* node, const char* name) {
    if (node == NULL) return NULL;

    for (int i = 0; i < node->numKeys; i++) {
        if (strcmp(node->keys[i].name, name) == 0) {
            return &node->keys[i];
        }
    }

    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            Student* result = searchByNameInNode(node->children[i], name);
            if (result != NULL) return result;
        }
    }

    return NULL;
}

Student* searchByName(BTree* tree, const char* name) {
    return searchByNameInNode(tree->root, name);
}

void insertNonFull(BTreeNode* node, Student key) {
    int i = node->numKeys - 1;
    if (node->isLeaf) {
        while (i >= 0 && compare(key, node->keys[i]) < 0) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && compare(key, node->keys[i]) < 0) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == MAX_ORDER - 1) {
            splitChild(node, i);
            if (compare(key, node->keys[i]) > 0) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void splitChild(BTreeNode* parent, int index) {
    BTreeNode* fullChild = parent->children[index];
    BTreeNode* newChild = createNode(fullChild->isLeaf);
    parent->children[index + 1] = newChild;

    for (int i = 0; i < MIN_ORDER - 1; i++) {
        newChild->keys[i] = fullChild->keys[i + MIN_ORDER];
    }
    if (!fullChild->isLeaf) {
        for (int i = 0; i < MIN_ORDER; i++) {
            newChild->children[i] = fullChild->children[i + MIN_ORDER];
        }
    }
    fullChild->numKeys = MIN_ORDER - 1;

    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newChild;

    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = fullChild->keys[MIN_ORDER - 1];
    parent->numKeys++;
}

void insert(BTree* tree, Student key) {
    ++tree->size;
    if (tree->root->numKeys == MAX_ORDER - 1) {
        BTreeNode* newRoot = createNode(0);
        newRoot->children[0] = tree->root;
        splitChild(newRoot, 0);
        tree->root = newRoot;
    }
    insertNonFull(tree->root, key);
}

BTreeNode* findPredecessor(BTreeNode* node, int index) {
    BTreeNode* current = node->children[index];
    while (!current->isLeaf) {
        current = current->children[current->numKeys];
    }
    return current;
}

BTreeNode* findSuccessor(BTreeNode* node, int index) {
    BTreeNode* current = node->children[index + 1];
    while (!current->isLeaf) {
        current = current->children[0];
    }
    return current;
}

void deleteKeyFromNode(BTreeNode* node, int index) {
    for (int i = index; i < node->numKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    node->numKeys--;
}

void deleteKey(BTreeNode* node, Student key) {
    int i = 0;
    while (i < node->numKeys && compare(key, node->keys[i]) > 0) {
        i++;
    }

    if (i < node->numKeys && compare(key, node->keys[i]) == 0) {
        if (node->isLeaf) {
            deleteKeyFromNode(node, i);
        } else {
            BTreeNode* predecessor = findPredecessor(node, i);
            if (predecessor->numKeys >= MIN_ORDER) {
                node->keys[i] = predecessor->keys[predecessor->numKeys - 1];
                deleteKey(predecessor, predecessor->keys[predecessor->numKeys - 1]);
            } else {
                BTreeNode* successor = findSuccessor(node, i);
                if (successor->numKeys >= MIN_ORDER) {
                    node->keys[i] = successor->keys[0];
                    deleteKey(successor, successor->keys[0]);
                } else {
                    mergeChildren(node, i);
                    deleteKey(node->children[i], key);
                }
            }
        }
    } else if (!node->isLeaf) {
        BTreeNode* child = node->children[i];
        if (child->numKeys == MIN_ORDER - 1) {
            fixChild(node, i);
        }
        deleteKey(node->children[i], key);
    }
}

void mergeChildren(BTreeNode* node, int index) {
    BTreeNode* leftChild = node->children[index];
    BTreeNode* rightChild = node->children[index + 1];

    leftChild->keys[MIN_ORDER - 1] = node->keys[index];
    for (int i = 0; i < rightChild->numKeys; i++) {
        leftChild->keys[MIN_ORDER + i] = rightChild->keys[i];
    }
    if (!leftChild->isLeaf) {
        for (int i = 0; i <= rightChild->numKeys; i++) {
            leftChild->children[MIN_ORDER + i] = rightChild->children[i];
        }
    }

    leftChild->numKeys += rightChild->numKeys + 1;

    deleteKeyFromNode(node, index);
    free(rightChild);
}

void fixChild(BTreeNode* parent, int index) {
    BTreeNode* child = parent->children[index];
    BTreeNode* leftSibling = (index > 0) ? parent->children[index - 1] : NULL;
    BTreeNode* rightSibling = (index < parent->numKeys) ? parent->children[index + 1] : NULL;

    if (leftSibling && leftSibling->numKeys >= MIN_ORDER) {
        for (int i = child->numKeys - 1; i >= 0; i--) {
            child->keys[i + 1] = child->keys[i];
        }
        if (!child->isLeaf) {
            for (int i = child->numKeys; i >= 0; i--) {
                child->children[i + 1] = child->children[i];
            }
        }
        child->keys[0] = parent->keys[index - 1];
        if (!child->isLeaf) {
            child->children[0] = leftSibling->children[leftSibling->numKeys];
        }
        parent->keys[index - 1] = leftSibling->keys[leftSibling->numKeys - 1];
        leftSibling->numKeys--;
        child->numKeys++;
    } else if (rightSibling && rightSibling->numKeys >= MIN_ORDER) {
        child->keys[child->numKeys] = parent->keys[index];
        if (!child->isLeaf) {
            child->children[child->numKeys + 1] = rightSibling->children[0];
        }
        parent->keys[index] = rightSibling->keys[0];
        for (int i = 1; i < rightSibling->numKeys; i++) {
            rightSibling->keys[i - 1] = rightSibling->keys[i];
        }
        if (!rightSibling->isLeaf) {
            for (int i = 1; i <= rightSibling->numKeys; i++) {
                rightSibling->children[i - 1] = rightSibling->children[i];
            }
        }
        rightSibling->numKeys--;
        child->numKeys++;
    } else {
        if (leftSibling) {
            mergeChildren(parent, index - 1);
        } else {
            mergeChildren(parent, index);
        }
    }
}

void deleteStudent(BTree* tree, Student key) {
    --tree->size;
    deleteKey(tree->root, key);
    if (tree->root->numKeys == 0) {
        BTreeNode* temp = tree->root;
        if (tree->root->isLeaf) {
            tree->root = NULL;
        } else {
            tree->root = tree->root->children[0];
        }
        free(temp);
    }
}