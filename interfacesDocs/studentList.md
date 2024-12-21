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
