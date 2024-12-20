#ifndef STUDENT_H
#define STUDENT_H

#define NAME_STRING_LENGTH 100

typedef struct {
    char name[NAME_STRING_LENGTH];
    int id; // ע��ÿλѧ����idΨһ
    int birth[3]; // �±�0��2�ֱ����ꡢ�¡���
    double scores[3]; // �±�0��2�ֱ������ġ���ѧ��Ӣ��ĳɼ�
} Student;

extern int compare(Student, Student);

#endif