#include "readStudentInfo.h"
#include "student.h"
#include "bTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readStudentInfo(const char* filename, BTree* bTree) {
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        exit(-1);
    }

    // 读取学生信息
    int id;
    int num = 0;
    while (fscanf(fp, "%d", &id) != EOF) {
        ++num;
        char name[NAME_STRING_LENGTH];
        int birth[3];
        double scores[3];
        fscanf(fp, "%s %d %d %d %lf %lf %lf", name, &birth[0], &birth[1], &birth[2], &scores[0], &scores[1], &scores[2]);
        Student student = createStudent(name, id, birth, scores);
        insert(bTree, student);
    }

    fclose(fp);
    return num;
}


