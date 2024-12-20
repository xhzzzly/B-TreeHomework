# 项目接口设计

其中，前面带`#`的是待实现接口

## `student.h`

### `int compare(Student stu1, Student stu2)`

参数：`stu1`学生数据1，`stu2`学生数据2

返回值：

若`stu1`的`id`大于`stu2`则返回正值，等于返回0，小于返回负值

简介：

用于比较`Student`对象，比较的是`id`大小

## `studentList.h`

### `StudentList* createList(void)`

返回值：空的`StudentList`的指针

简介：创建新的空的`StudentList`

### `void addFront(StudentList* list, Student* obj)`

参数：`list`操作的列表，`obj`待加入表的对象的指针

简介：把`obj`插入到表`list`的第一个位置，注意两个参数都是指针类型

### `Student* front(StudentList* list)`

参数：`list`操作的列表

返回值：最前面的`Student`元素的指针

简介：返回列表最前面元素的指针，请注意是指针

### `Student* removeFront(StudentList* list)`

参数：`list`操作的列表

返回值：最前面的`Student`元素的指针

简介：在列表中删除第一个元素，返回它的指针，请注意是`Student`指针，而不是列表元素的指针。列表元素本身对外不设公共修改或获取操作

### `void destroy(StudentList* list)`

参数：`list`操作的列表

简介：将列表内的每一个结点对象释放，最后释放`list`所指的列表对象。最好在执行完此操作后，将原列表指针置为`NULL`，避免内存问题，如：

```c
StudentList* list = createList();
...
destroy(list);
list = NULL;
```

## `bTree.h`

### `BTree* createBTree(void)`

返回值：新建的`BTree`对象的指针

简介：在内存中新建一个空`BTree`对象，并返回它的指针。B-树的构建基于`compare()`接口的实现，换言之树上的元素按`compare()`定义的比大小规则有序，也仅在该大小规则下进行查询是最快的

### `void insert(BTree* tree, Student key)`

参数：`tree`操作的B-树，`key`待插入对象

简介：把`key`插入树中

### `Student* search(BTree* tree, Student key)`

参数：`tree`操作的B-树，`key`待被查询的`Student`对象

返回值：查找到匹配的`Student`对象的指针，若没查到返回`NULL`

简介：在树中查找匹的对象，此处的『匹配』取决于`compare()`接口的定义，`compare()`返回0时为『匹配』。当前状态下，该函数只比较`key`中的`id`，即只要某些`key`的`id`相同，该函数的行为就是相同的

### `StudentList* searchByName(BTree* tree, const char* name)`

参数：`tree`操作的B-树，`name`字符串字面值

返回值：保存着所有同名学生的`StudentList`数据结构

简介：查找所有同名学生，返回`StudentList`。当前状态下，由于只有`id`有序，因此该函数会遍历每一个结点以寻找同名学生，效率不如`id`查找

### `Student* searchById(BTree* tree, int id)`

参数：`tree`操作的B-树，`id`目标学生的`id`

返回值：查找到`id`匹配的`Student`对象的指针，若没查到返回`NULL`

简介：当前状态下，用`id`查找效率最高

### `void deleteStudent(BTree* tree, Student key)`

参数：`tree`操作的B-树，`key`待被删除的`Student`对象

返回值：删除树中匹配的`Student`对象，是否匹配等价于`compare()==0`表达式的结果

简介：当前状态下，删除`id`与所给的`key.id`相同的对象

### `void deleteById(BTree* tree, int id)`

参数：`tree`操作的B-树，`id`目标学生的`id`

返回值：删除树中`id`匹配的`Student`对象

简介：用于通过`id`删除树上的对象

