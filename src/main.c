#include "student.h"
#include "bTree.h"
#include "readStudentInfo.h"
#include "studentList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MENU_WIDTH 50

void clearScreen() {
    system("cls");
}

void printCentered(const char* text) {
    int padding = (MENU_WIDTH - strlen(text)) / 2;
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s\n", text);
}

void printWelcomeMessage() {
    clearScreen();
    printCentered("欢迎使用学生管理系统");
    printCentered("=======================");
}

void printMainMenu(BTree* tree) {
    clearScreen();
    printf("\n");
    printCentered("======== 主菜单 ========");
    char buffer[MENU_WIDTH];
    snprintf(buffer, MENU_WIDTH, "当前学生数量: %d", tree->size);
    printCentered(buffer);
    printCentered("1. 插入学生");
    printCentered("2. 查找学生");
    printCentered("3. 删除学生");
    printCentered("4. 显示所有学生信息");
    printCentered("5. 保存所有学生信息到文件");
    printCentered("6. 退出");
    printCentered("========================");
    printCentered("请选择操作: \n");
}

void printSubMenu(const char* title, const char* options[], int optionCount) {
    printf("\n");
    printCentered(title);
    for (int i = 0; i < optionCount; i++) {
        char buffer[MENU_WIDTH];
        snprintf(buffer, MENU_WIDTH, "%d. %s", i + 1, options[i]);
        printCentered(buffer);
    }
    printCentered("0. 返回上级菜单");
    printCentered("========================");
    printCentered("请选择操作: \n");
}

int getValidatedChoice(int min, int max) {
    int choice;
    while (true) {
        printf("请输入有效的选项 (%d-%d): ", min, max);
        if (scanf("%d", &choice) == 1 && choice >= min && choice <= max) {
            while (getchar() != '\n'); // 清理输入缓冲区
            return choice;
        } else {
            printf("输入无效，请重试！\n");
            while (getchar() != '\n'); // 清理输入缓冲区
        }
    }
}

void insertStudent(BTree* tree) {
    char name[NAME_STRING_LENGTH];
    int id;
    int birth[3];
    double scores[3];

    printf("请输入学生的姓名: ");
    scanf("%s", name);
    while (getchar() != '\n'); // 清理输入缓冲区

    printf("请输入学生的学号: ");
    while (scanf("%d", &id) != 1 || id <= 0) {
        printf("学号无效，请重新输入: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    while (searchById(tree, id) != NULL) {
        printf("学号已存在，请重新输入: ");
        while (scanf("%d", &id) != 1 || id <= 0) {
            printf("学号无效，请重新输入: ");
            while (getchar() != '\n');
        }
    }

    printf("请输入学生的生日（年 月 日）: ");
    while (scanf("%d %d %d", &birth[0], &birth[1], &birth[2]) != 3 ||
           birth[0] < 1900 || birth[1] < 1 || birth[1] > 12 || birth[2] < 1 || birth[2] > 31) {
        printf("生日无效，请重新输入: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    printf("请输入学生的成绩（语文 数学 英语）: ");
    while (scanf("%lf %lf %lf", &scores[0], &scores[1], &scores[2]) != 3 ||
           scores[0] < 0 || scores[1] < 0 || scores[2] < 0) {
        printf("成绩无效，请重新输入: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');

    Student student = createStudent(name, id, birth, scores);
    insert(tree, student);
    printf("学生数据已成功插入\n");
    system("pause");
}

void searchStudent(BTree* tree) {
    const char* options[] = {"按学号查找", "按姓名查找"};
    int choice;
    while (true) {
        clearScreen();
        printSubMenu("查找学生", options, 2);
        choice = getValidatedChoice(0, 2);
        if (choice == 0) return;

        if (choice == 1) {
            int id;
            printf("请输入学号: ");
            while (scanf("%d", &id) != 1 || id <= 0) {
                printf("学号无效，请重新输入: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            Student* student = searchById(tree, id);
            if (student) {
                printf("找到学生: \n");
                printf("姓名: %s\t学号: %d\t生日: %d-%d-%d\t语文: %.2lf\t数学: %.2lf\t英语: %.2lf\n",
                       student->name, student->id, student->birth[0], student->birth[1], student->birth[2],
                       student->scores[0], student->scores[1], student->scores[2]);
            } else {
                printf("未找到该学生\n");
            }
            system("pause");
        } else if (choice == 2) {
            char name[NAME_STRING_LENGTH];
            printf("请输入姓名: ");
            scanf("%s", name);
            while (getchar() != '\n');

            StudentList* list = searchByName(tree, name);
            if (list && list->size > 0) {
                StudentListNode* node = list->head;
                printf("找到以下学生:\n");
                printf("姓名\t学号\t生日\t\t语文\t数学\t英语\n");
                while (node) {
                    printf("%s\t%d\t%d-%d-%d\t%.2lf\t%.2lf\t%.2lf\n",
                           node->student->name, node->student->id, node->student->birth[0], node->student->birth[1],
                           node->student->birth[2], node->student->scores[0], node->student->scores[1], node->student->scores[2]);
                    node = node->next;
                }
            } else {
                printf("未找到该姓名的学生\n");
            }
            system("pause");
        }
    }
}

void removeStudent(BTree* tree) {
    const char* options[] = {"按学号删除", "按姓名删除"};
    int choice;
    while (true) {
        clearScreen();
        printSubMenu("删除学生", options, 2);
        choice = getValidatedChoice(0, 2);
        if (choice == 0) return;

        if (choice == 1) {
            int id;
            printf("请输入学号: ");
            while (scanf("%d", &id) != 1 || id <= 0) {
                printf("学号无效，请重新输入: ");
                while (getchar() != '\n');
            }
            while (getchar() != '\n');

            deleteById(tree, id);
            printf("学生已删除\n");
        } else if (choice == 2) {
            char name[NAME_STRING_LENGTH];
            printf("请输入姓名: ");
            scanf("%s", name);
            while (getchar() != '\n');

            StudentList* list = searchByName(tree, name);
            if (list && list->size > 0) {
                StudentListNode* node = list->head;
                while (node) {
                    printf("姓名: %s, 学号: %d\n", node->student->name, node->student->id);
                    node = node->next;
                }
                printf("请输入要删除的学号: ");
                int id;
                while (scanf("%d", &id) != 1 || id <= 0) {
                    printf("学号无效，请重新输入: ");
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                deleteById(tree, id);
                printf("学生已删除\n");
            } else {
                printf("未找到该姓名的学生\n");
            }
        }
        system("pause");
    }
}

void displayAllStudentsInNode(BTreeNode* node) {
    if (node == NULL) return;

    for (int i = 0; i < node->numKeys; i++) {
        printf("%s\t%d\t%d-%d-%d\t%.2lf\t%.2lf\t%.2lf\n",
               node->keys[i].name, node->keys[i].id, node->keys[i].birth[0], node->keys[i].birth[1], node->keys[i].birth[2],
               node->keys[i].scores[0], node->keys[i].scores[1], node->keys[i].scores[2]);
    }

    for (int i = 0; i <= node->numKeys; i++) {
        displayAllStudentsInNode(node->children[i]);
    }
}

void displayAllStudents(BTree* tree) {
    clearScreen();
    if (tree->root == NULL || tree->size == 0) {
        printf("没有学生信息可显示\n");
        system("pause");
        return;
    }

    printf("所有学生信息如下:\n");
    printf("姓名\t学号\t生日\t\t语文\t数学\t英语\n");
    displayAllStudentsInNode(tree->root);
    system("pause");
}

void saveAllStudentsInNodeToFile(BTreeNode* node, FILE* file) {
    if (node == NULL) return;

    for (int i = 0; i < node->numKeys; i++) {
        fprintf(file, "%d %s %d %d %d %.2lf %.2lf %.2lf\n", node->keys[i].id, node->keys[i].name, node->keys[i].birth[0], node->keys[i].birth[1], node->keys[i].birth[2],
                 node->keys[i].scores[0], node->keys[i].scores[1], node->keys[i].scores[2]);
    }

    for (int i = 0; i <= node->numKeys; i++) {
        saveAllStudentsInNodeToFile(node->children[i], file);
    }
}

void saveAllStudentsToFile(BTree* tree) {
    clearScreen();
    char filename[FILENAME_MAX];
    printf("请输入要保存的文件名（带后缀）: ");
    scanf("%s", filename);
    while (getchar() != '\n'); // 清理输入缓冲区

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    if (tree->root == NULL || tree->size == 0) {
        printf("没有学生信息可保存\n");
    } else {
        saveAllStudentsInNodeToFile(tree->root, file);
    }

    fclose(file);
    printf("学生信息已保存到文件 %s\n", filename);
    system("pause");
}

int main() {
    BTree* bTree = createBTree();
    char filename[FILENAME_MAX];
    printf("请输入初始学生信息文件名（带后缀）: ");
    scanf("%s", filename);
    while (getchar() != '\n');

    readStudentInfo(filename, bTree);

    int choice;

    printWelcomeMessage();
    system("pause");

    while (true) {
        printMainMenu(bTree);
        choice = getValidatedChoice(1, 6);
        clearScreen();

        switch (choice) {
            case 1:
                insertStudent(bTree);
                break;
            case 2:
                searchStudent(bTree);
                break;
            case 3:
                removeStudent(bTree);
                break;
            case 4:
                displayAllStudents(bTree);
                break;
            case 5:
                saveAllStudentsToFile(bTree);
                break;
            case 6:
                printf("感谢使用学生管理系统，再见！\n");
                system("pause");
                return 0;
            default:
                printf("无效选项，请重新选择\n");
        }
    }
}
