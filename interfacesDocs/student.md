### `int compare(Student stu1, Student stu2)`

参数：`stu1`学生数据1，`stu2`学生数据2

返回值：若`stu1`的`id`大于`stu2`则返回正值，等于返回0，小于返回负值

简介：用于比较`Student`对象，比较的是`id`大小

### `Student createStudent(char* name, int id, int* birth, double* scores)`

参数：`name`姓名，`id`唯一的学号，`birth`长为度三的生日数组（年、月、日），`scores`长度为三的成绩数组（语、数、英）

返回值：返回生成的相应的`Student`对象

简介：用于生成`Student`对象