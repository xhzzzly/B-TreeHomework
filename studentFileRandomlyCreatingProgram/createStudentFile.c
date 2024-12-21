#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_FAMILY_NAMES 10
#define NUM_GIVEN_NAMES 80
#define NUM_STUDENTS 10000  // 学生数量

const char* family_names[NUM_FAMILY_NAMES] = {
    "张", "王", "李", "刘", "陈", "杨", "赵", "黄", "周", "吴"
};

const char* given_names[NUM_GIVEN_NAMES] = {
    "明", "刚", "杰", "静", "芳", "梅", "娜", "丽", "婷", "建",
    "鑫", "华", "国", "艳", "林", "琴", "云", "颖", "强", "军",
    "亮", "冰", "敏", "娟", "丽", "玉", "娅", "欢", "阳", "伟",
    "超", "波", "鹏", "萍", "丽", "蕾", "琳", "辰", "东", "义",
    "广", "宏", "志", "莉", "东", "桂", "蓉", "晨", "希", "晨",
    "娜", "建", "娜", "磊", "琴", "欣", "馨", "文", "伟", "睿",
    "彬", "翔", "浩", "峰", "忠", "颖", "慧", "凡", "舟", "炜",
    "冰", "倩", "涵", "淇", "彤", "文", "煜", "泽", "铎", "薇"
};

void generate_name(char *name) {
	int a = rand()%3; 
    if(a == 0) //三个字的名字 
    {
    	int family_index = rand() % NUM_FAMILY_NAMES;
    	const char* family_name = family_names[family_index];

    	int given_name_index1 = rand() % NUM_GIVEN_NAMES;
    	int given_name_index2 = rand() % NUM_GIVEN_NAMES;
    	const char* given_name1 = given_names[given_name_index1];
    	const char* given_name2 = given_names[given_name_index2];

    	sprintf(name, "%s%s%s", family_name, given_name1, given_name2);
	}
	else//两个字的名字 
	{
		int family_index = rand() % NUM_FAMILY_NAMES;
    	const char* family_name = family_names[family_index];

    	int given_name_index1 = rand() % NUM_GIVEN_NAMES;
    	const char* given_name1 = given_names[given_name_index1];

    	sprintf(name, "%s%s", family_name, given_name1);
	}
}

// 随机生成出生日期
void generate_birthday(char *birthday) {
    int year = 2000 + rand() % 11;  // 2000 到 2010 年之间
    int month = 1 + rand() % 12;    // 1 到 12 月
    int day = 1 + rand() % 28;      // 1 到 28 日（简化处理，确保日期合法）

    sprintf(birthday, "%04d %02d %02d", year, month, day);
}

// 随机生成成绩
void generate_grades(int *chinese, int *math, int *english) {
    *chinese = rand() % 101;  // 语文成绩 0 - 100
    *math = rand() % 101;     // 数学成绩 0 - 100
    *english = rand() % 101;  // 英语成绩 0 - 100
}

// 将学生信息写入文件
void write_student_data(FILE *file, int id, char *name, char *birthday, int chinese, int math, int english) {
    fprintf(file, "%09d %s %s", id, name, birthday);
    if(rand()%2)
    fprintf(file," %d",chinese);
    else
    fprintf(file," %d.5",chinese);
    if(rand()%2)
    fprintf(file," %d",math);
    else
    fprintf(file," %d.5",math);
    if(rand()%2)
    fprintf(file," %d\n",english);
    else
    fprintf(file," %d.5\n",english);
}

void createFile() {
    srand(time(NULL));
    FILE *file = fopen("students_data.txt", "w");
    for (int i = 1; i <= NUM_STUDENTS; i++) {
        char name[50];
        char birthday[11];
        int chinese, math, english;

        // 生成学生数据
        generate_name(name);
        generate_birthday(birthday);
        generate_grades(&chinese, &math, &english);

        // 将学生数据写入文件
        write_student_data(file, i, name, birthday, chinese, math, english);
    }

    // 关闭文件
    fclose(file);
}
int main()
{
	createFile();
	return 0;
}

