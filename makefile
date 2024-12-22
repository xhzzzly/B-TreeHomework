.PHONY: all clean

CFLAGS = -Wall

all: bin/aTestProgram.exe bin/createStudentFile.exe
	@echo "All Done"

bin/createStudentFile.exe: studentFileRandomlyGeneratingProgram/createStudentFile.c
	gcc $(CFLAGS) $< -o $@

bin/createStudentFile.exe: obj/main.o obj/bTree.o obj/readStudentInfo.o obj/student.o obj/studentList.o
	gcc $(CFLAGS) $^ -o $@

obj/%.o: src/%.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	del obj/*.o