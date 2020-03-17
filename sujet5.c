
#include <stdio.h>
#include <stdlib.h>
#include "rdtsc.h"
#include "common.h"


void initVect(float** t);
void initMat(float*** m, unsigned long n);
void baseline (unsigned n , float ** m, float * x , float * y);
void l1 (unsigned n, float** m, float * x, float * y);
void l2 (unsigned n, float** m, float * x, float * y);
void l3 (unsigned n, float** m, float * x, float * y);
void ram (unsigned n, float** m, float * x, float * y);

//pour voir caracteristique de votre ordinateur, tapez sur le terminal "lscpu"

int main(int nbarg, char *argv[])
{
	//Listing.1 – Code de réduction d’un tableau
		int r,t;
		f64 cycles[MAX_SAMPLES];
		u64 samples_count = 0,cb,ca;
	  unsigned long n = atol(argv[1]);
		unsigned long repw = 100;
		unsigned long repm = 100;

		for ( t= 0; t < 31; t++) {

		  float * x=(float*)malloc(n*sizeof(float));
		  float * y=NULL;
		  float ** m=NULL;

		  //printf("%ld\n",sizeof(float)); //sizeof(float) = 4
		  //Initialisation des tableaux
		  initVect(&y);
		  initMat(&m, n);

			for (r  = 0;  r<repw; r ++) {
				baseline(n, m, x, y);
			}

		  // Premier relevé de temps
		  cb = rdtsc();
		  //appel baseline
	  	for (r = 0; r < repm; r++) {
	  		baseline(n, m, x, y);
	  	}
		  //Deuxième relevé de temps
		  ca = rdtsc();


			free(x);
			free(y);
			for (r= 0; r < n; r++) {
				free(m[r]);
			}


			f64 elapsed = (float)(ca - cb)/(n*n*16 *repm);
			cycles[samples_count++] = elapsed;


		}

		sort(cycles, samples_count);

	  //
	  f64 min, max, avg, mea, dev, bpc;

	  //
	  mea = mean(cycles, samples_count);

	  //
	  dev = stddev(cycles, samples_count);

	  //
	  min = cycles[0];
	  max = cycles[samples_count - 1];
	  avg = (min + max) / 2.0;



	  //
	  printf("\n %15.3f; %15.3f; %15.3f; %15.3f; %15.3f %%; %15.3f %%;\n",
		  min,
		  max,
		  avg,
		  mea,
			(avg-min)/min,
	  	(dev * 100.0 / mea));

		return 0;
}

// Initialisation du tableau
void initVect(float** t)
{
  unsigned long i;

  //Allocation du vecteur
  (*t) = (float *) malloc ( sizeof(float) * 16);

  //Affectation
  for (i = 0; i < 16; i++)
  {
    (*t)[i] = 1;
  }

  return;
}

void initMat(float*** m, unsigned long n)
{
  unsigned i, j;

  //Allocation de la matrice
  (*m) = (float **) malloc( sizeof(float *) * n );
  for (i = 0; i < n; i++)
    (*m)[i] = (float *) malloc (sizeof(float) * n);

  //Affectation
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      (*m)[i][j] = 1;
    }
  }

  return;
}



//Fonction à coder
void baseline (unsigned n, float** m, float * x, float * y)
{
  unsigned i , j , k ;
  for ( i = 0; i < n ; i ++)
    x [i] = 0;

  for ( k = 0; k < 16; k ++)
    for ( j = 0; j < n ; j ++)
      for ( i = 0; i < n ; i ++)
        x [i] += m [i][j] * y [k];
}

void l1 (unsigned n, float** m, float * x, float * y)
{
  unsigned i , j , k ;
  for ( i = 0; i < n ; i ++)
    x [i] = 0;

  for ( k = 0; k < 16; k ++)
    for ( j = 0; j < n ; j ++)
      for ( i = 0; i < n ; i ++)
        x [i] += m [i][j] * y [k];
}

void l2 (unsigned n, float** m, float * x, float * y)
{
  unsigned i , j , k ;
  for ( i = 0; i < n ; i ++)
    x [i] = 0;

  for ( k = 0; k < 16; k ++)
    for ( j = 0; j < n ; j ++)
      for ( i = 0; i < n ; i ++)
        x [i] += m [i][j] * y [k];
}

void l3 (unsigned n, float** m, float * x, float * y)
{
  unsigned i , j , k ;
  for ( i = 0; i < n ; i ++)
    x [i] = 0;

  for ( k = 0; k < 16; k ++)
    for ( j = 0; j < n ; j ++)
      for ( i = 0; i < n ; i ++)
        x [i] += m [i][j] * y [k];
}

void ram (unsigned n, float** m, float * x, float * y)
{
  unsigned i , j , k ;
  for ( i = 0; i < n ; i ++)
    x [i] = 0;

  for ( k = 0; k < 16; k ++)
    for ( j = 0; j < n ; j ++)
      for ( i = 0; i < n ; i ++)
        x [i] += m [i][j] * y [k];
}
