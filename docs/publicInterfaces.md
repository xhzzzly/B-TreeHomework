# 项目接口设计

其中，前面带`#`的是待实现接口

## int compare(Student stu1, Student stu2)

参数：

stu1：学生数据1

stu2：学生数据2

返回值：

若`stu1`的`id`大于`stu2`则返回正值，等于返回0，小于返回负值

简介：

用于比较`Student`对象，比较的是`id`大小

声明与实现位置：

`student.h`、`student.c`