
main: clean compile execm execs

clean:
	@rm -f *.o 

compile: Monitor.o
	@gcc -g -c *.c	
	@gcc -g -o Simulator util*.o Simulator.o -lpthread
	@gcc -g -o Monitor util*.o Monitor.o -lpthread

execm:
	@x-terminal-emulator --geometry "5x5" -e "bash -c './Monitor';bash" > /dev/null;

execs:
	@x-terminal-emulator --geometry "5x5" -e "bash -c './Simulator';bash" > /dev/null;
