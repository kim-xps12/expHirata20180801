#include<stdio.h>

int main(void)
{
  FILE *fp;
  char *fname = "exp1-1.csv";
  float time, signTmp;
  
  float sign[512];
  
  int i = 0;

  fp = fopen( fname, "r" );
  
  if( fp == NULL ){
    printf( "%sError Can't Open Fiel \n", fname );
    return -1;
  }

  while( (fscanf( fp, "%f,%f", &time, &signTmp ) ) != EOF){
  	
    //printf( "%f %f \n", time, signTmp);
	sign[i] = signTmp;
	i++;
  }
  
  for(i=0; i<512; i++){
  	
	printf("%f\n", sign[i]);
  }

  fclose( fp );
  return 0;
}
