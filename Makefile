CC=gcc
II=icc

CFLAGS=-g3

OFLAGS=-march=native

baseline:
	$(CC) -DBASELINE=1 $(CFLAGS) $(OFLAGS) -$(O) sujet5.c common.c -o sujet5 -lm
	$(II) -DBASELINE=1 $(CFLAGS) $(OFLAGS) -$(O) sujet5.c common.c -o sujet5_icc -lm

baseline_xHost:
	$(CC) -DBASELINE=1 $(CFLAGS) $(OFLAGS) -O3 -march=native sujet5.c common.c -o sujet5 -lm
	$(II) -DBASELINE=1 $(CFLAGS) $(OFLAGS) -O3 -xHost sujet5.c common.c -o sujet5_icc -lm


clean:
	rm -Rf *~ sujet5 sujet5_icc
