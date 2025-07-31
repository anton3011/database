FLAGS=-mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
OPT = -O3
all: a.out

LIST1=a.o record.o list2.o command.o data_base.o
LIST1_D=$(subst .o,.d,$(LIST1))

%.o: %.cpp
	g++ -c $(FLAGS) $(OPT) -MMD $< 
%.out: %.o 
	g++ $(FLAGS) $^ -o $@ 

-include $(LIST1_D)
a.out: $(LIST1)

clean: 
	rm -f a.out $(LIST1) $(LIST1_D)