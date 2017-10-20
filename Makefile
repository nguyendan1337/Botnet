OBJS = master candc zombie

all: $(OBJS)

master:
	gcc -D_GNU_SOURCE -o master master.c	

candc:
	gcc -D_GNU_SOURCE -o candc cc.c
	
zombie:
	gcc -o zombie zombie.c

clean:
	rm $(OBJS)
	rm bn.log
	
