all: main.c kk.c sol.c rr.c hc.c sa.c
	gcc -o all main.c kk.c sol.c rr.c hc.c sa.c


clean:
	rm -f *.o main kk sol rr hc sa