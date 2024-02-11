PROJECTNAME=calc
BIN=build/$(PROJECTNAME)
CC=clang

#OPT=-O3
OPT=-Og -g -ggdb
DEPFLAGS=-MP -MD
FLAGS=-Wall -Wextra -I. $(OPT) $(DEPFLAGS) $(EXTRAFLAGS)

SRC=$(shell ls *.c)
OBJ=$(foreach S, $(SRC:.c=.o), build/$(S))

$(shell mkdir -p build)


all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

-include $(OBJ:.o=.d) $(LIBO:.o=.d)

build/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

run : $(BIN)
	./$< $(input)

clean :
	rm -rf build/*

check :
	cppcheck --enable=all --suppress=missingIncludeSystem -I. .
	gcc -fanalyzer $(FLAGS) $(SRC) -o $(BIN)
	for file in $(SRC); do echo "clang analyze $$file :"; clang --analyze $$file -o ./build/clang.analyze; done
	#flawfinder .

debug : $(BIN)
	gdb $< $(input)

# unzip : tar -xvf exemple.tgz
dist : clean
	$(info /!\ project folder has to be named $(PROJECTNAME) /!\ )
	cd .. && tar zcvf $(PROJECTNAME)/build/$(PROJECTNAME).tgz $(PROJECTNAME) >/dev/null

push :
	git push bbsrv
	git push gh

# alias

r : run

t : test

c : check

p : push

d : debug

.PHONY : all run r clean check c debug d dist push p info
