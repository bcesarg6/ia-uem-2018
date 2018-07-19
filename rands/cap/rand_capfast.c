/* Testando o método rand do Fast do CAP
 * Copyright(C) 2014 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define RANDNUM_W 521288629;
#define RANDNUM_Z 362436069;

static unsigned randum_w = RANDNUM_W;
static unsigned randum_z = RANDNUM_Z;

void srandnum(int seed){
	unsigned w, z;

	w = (seed * 104623) & 0xffffffff;
	randum_w = (w) ? w : RANDNUM_W;
	z = (seed * 48947) & 0xffffffff;
	randum_z = (z) ? z : RANDNUM_Z;
}

unsigned randnum(void){
	unsigned u;

	/* 0 <= u < 2^32 */
	randum_z = 36969 * (randum_z & 65535) + (randum_z >> 16);
	randum_w = 18000 * (randum_w & 65535) + (randum_w >> 16);
	u = (randum_z << 16) + randum_w;

	return (u);
}

int main(){

  int i;
  int n = 10;
  time_t t;
  unsigned max = RAND_MAX*2;
  srandnum(time(&t));

  for (i = 0; i < n; i++) {
    printf("%lf\n", (double)randnum() / max);
  }

}
