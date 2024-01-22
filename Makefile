PROJECTNAME=calc
BIN=build/$(PROJECTNAME)
CC=gcc

EXT=c
INCDIRS=include

# make mode=release
ifeq ($(mode), release)
	OPT=-O3
else
	OPT=-Og -g
endif
DEPFLAGS=-MP -MD
MACROS=
FLAGS=-Wall -Wextra $(foreach F,$(INCDIRS),-I$(F)) $(OPT) $(DEPFLAGS) $(foreach M,$(MACROS),-D$(M))

SRC=$(shell find . -name "*.$(EXT)" -path "./src/*")
OBJ=$(subst ./src/,./build/,$(SRC:.$(EXT)=.o))

$(shell mkdir -p build)


all : $(BIN)

$(BIN) : $(OBJ) $(LIBO)
	$(CC) $(FLAGS) -o $@ $^

-include $(OBJ:.o=.d) $(LIBO:.o=.d)

build/%.o : src/%.$(EXT)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<
build/%.o : lib/%.$(EXT)
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -o $@ -c $<

# make run input="program input"
run : $(BIN)
	./$< $(input)

clean :
	rm -rf build/*

check :
	cppcheck --enable=all --suppress=missingIncludeSystem $(foreach I,$(INCDIRS),-I$(I)) .
	flawfinder .

debug : $(BIN)
	gdb $< $(input)

# unzip : tar -xvf exemple.tgz
dist : clean
	$(info /!\ project folder has to be named $(PROJECTNAME) /!\ )
	cd .. && tar zcvf $(PROJECTNAME)/build/$(PROJECTNAME).tgz $(PROJECTNAME) >/dev/null

push :
	git push bbsrv
	git push gh

install : dist
	cp Makefile ../script
	mv build/$(PROJECTNAME).tgz ../opt/archive
	cd .. && rm -rf $(PROJECTNAME)

# alias

r : run

t : test

c : check

p : push

d : debug

.PHONY : all run r clean check c debug d dist push p install info
