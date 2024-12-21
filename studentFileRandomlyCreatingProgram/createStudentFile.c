#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int num_students = 10000;
#define FILE_NAME_LENGTH 100
char filename[FILE_NAME_LENGTH];

#define NUM_FAMILY_NAMES 100
#define NUM_GIVEN_NAMES 390

const char* family_names[NUM_FAMILY_NAMES] = {
    "张", "王", "李", "刘", "陈", "杨", "赵", "黄", "周", "吴",
    "徐", "孙", "朱", "马", "胡", "郭", "何", "林", "高", "罗",
    "郑", "梁", "谢", "宋", "唐", "许", "韩", "冯", "邓", "曹",
    "彭", "曾", "萧", "田", "董", "潘", "袁", "蔡", "蒋", "余",
    "杜", "叶", "程", "魏", "苏", "吕", "丁", "任", "沈", "姚",
    "卢", "姜", "崔", "钟", "谭", "陆", "汪", "范", "金", "石",
    "廖", "贾", "夏", "韦", "付", "方", "白", "邹", "孟", "熊",
    "秦", "邱", "侯", "江", "尹", "薛", "闫", "段", "雷", "黎",
    "史", "龙", "陶", "贺", "顾", "毛", "郝", "龚", "邵", "万",
    "钱", "覃", "武", "戴", "莫", "孔", "向", "汤", "曹", "祝"
};

const char* given_names[NUM_GIVEN_NAMES] = {
    "明", "刚", "杰", "静", "芳", "梅", "娜", "丽", "婷", "建",
    "鑫", "华", "国", "艳", "林", "琴", "云", "颖", "强", "军",
    "亮", "冰", "敏", "娟", "玉", "娅", "欢", "阳", "伟", "超",
    "波", "鹏", "萍", "蕾", "琳", "辰", "东", "义", "广", "宏",
    "志", "莉", "桂", "蓉", "晨", "希", "娜", "磊", "欣", "文",
    "睿", "彬", "翔", "浩", "峰", "忠", "慧", "凡", "舟", "炜",
    "倩", "涵", "淇", "彤", "煜", "泽", "铎", "薇", "轩", "楠",
    "佳", "宇", "睿", "翔", "凯", "俊", "乐", "航", "辉", "哲",
    "晨", "辰", "东", "翔", "睿", "铭", "昊", "杰", "豪", "韬",
    "洁", "婉", "然", "影", "瑶", "丽", "琼", "瑜", "岚", "珊",
    "琳", "芳", "宁", "芊", "菁", "萌", "芮", "莹", "婕", "蓓",
    "雨", "雪", "雯", "馨", "冰", "莹", "霜", "霖", "琪", "滢",
    "灵", "梦", "依", "欢", "伊", "娴", "娟", "嫣", "娆", "婉",
    "丽", "洁", "媛", "婷", "瑞", "芬", "青", "子", "燕", "君",
    "清", "羽", "菲", "伊", "乔", "茜", "兰", "榕", "蕊", "荟",
    "蓉", "茵", "欣", "滢", "萍", "璇", "瑾", "露", "凝", "悠",
    "霏", "瑾", "菡", "菲", "晨", "依", "卿", "晴", "露", "洁",
    "岚", "妍", "晶", "乐", "漫", "莎", "琪", "琦", "凌", "逸",
    "涵", "滢", "然", "娇", "岚", "瑶", "雯", "滢", "婧", "涵",
    "悦", "希", "文", "嫣", "梦", "诗", "怡", "璐", "韵", "颖",
    "欣", "淑", "雯", "倩", "曦", "依", "雪", "倩", "娴", "瑾",
    "婷", "娅", "倩", "悠", "依", "瑶", "琼", "蓉", "梦", "菲",
    "媛", "菡", "清", "娜", "婉", "婷", "慧", "婕", "冰", "莹",
    "怡", "晴", "婵", "丽", "睿", "晶", "霖", "婉", "芳", "茜",
    "瑜", "馨", "嫣", "露", "凝", "绮", "璇", "玮", "蓉", "丹",
    "玲", "华", "莺", "曼", "馨", "君", "惠", "倩", "芬", "莎",
    "静", "欣", "语", "佳", "欢", "妍", "悠", "颖", "萍", "瑶",
    "婕", "婷", "媛", "琳", "芬", "琦", "璐", "芸", "舒", "静",
    "瑾", "敏", "晓", "婷", "欣", "妍", "欢", "妍", "娅", "希",
    "蓓", "梦", "妍", "珊", "娟", "悠", "霏", "媛", "瑜", "琼",
    "梓", "子", "宇", "辰", "一", "宸", "泽", "嘉", "欣", "佳",
    "玥", "睿", "妍", "熙", "煜", "昕", "玥", "泽", "晨", "雨",
    "诗", "瑶", "桐", "萱", "奕", "依", "诺", "怡", "涵", "语",
    "桐", "欣", "妍", "可", "汐", "雨", "桐", "梦", "瑶", "梓",
    "宸", "睿", "妍", "熙", "煜", "昕", "玥", "泽", "晨", "雨",
    "诗", "瑶", "桐", "萱", "奕", "依", "诺", "怡", "涵", "语",
    "桐", "欣", "妍", "可", "汐", "雨", "桐", "梦", "瑶", "梓",
    "宸", "睿", "妍", "熙", "煜", "昕", "玥", "泽", "晨", "雨",
    "诗", "瑶", "桐", "萱", "奕", "依", "诺", "怡", "涵", "语",
};

void generate_name(char *name) {
	int a = rand()%3; 
    if(a != 0) //三个字的名字 
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
    fprintf(file, "%d %s %s", id, name, birthday);
    if(chinese == 100 || rand()%2)
        fprintf(file," %d",chinese);
    else
        fprintf(file," %d.5",chinese);
    if(math == 100 || rand()%2)
        fprintf(file," %d",math);
    else
        fprintf(file," %d.5",math);
    if(english == 100 || rand()%2)
        fprintf(file," %d\n",english);
    else
        fprintf(file," %d.5\n",english);
}

void createFile() {
    srand(time(NULL));
    FILE *file = fopen(filename, "w");
    for (int i = 1; i <= num_students; i++) {
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
    printf("请输入学生数量：");
    scanf("%d",&num_students);
    printf("请输入文件名（末尾最好带.txt后缀）：");
    scanf("%s",filename);
	createFile();
    printf("文件已生成\n");
    system("pause");
	return 0;
}

