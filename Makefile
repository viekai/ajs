all: clean ajs

ajs:	
	g++ -o ajs AJS.cpp AJS.h Lex.cpp Lex.h -g
clean:
	rm -rf ajs *.o
