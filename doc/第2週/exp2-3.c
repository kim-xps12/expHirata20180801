#include<stdio.h>
#include<math.h>

#define DIGI_ROUND 10

const int M = 512;		//[-]

	
FILE *fp;
	
	


double blkHrsWindow(int n){
	
	return (0.423 - 0.498*(cos( (2*M_PI*n/M) )) + 0.0792*(cos( (4*M_PI*n/M) )));
}



int main(void){

	int i = 0;
	int n = 0;
	int k = 0;		//フーリエ変換後横軸（周波数[Hz]）
	
	
	double ans = 0;
	double r = 0;
		
	double signANA[512] = {0};
	double valFilted[512]  = {0};
	
 	char *fname = "exp1-5.csv";
    double time = 0;
    double signTmp = 0;
	
	double valIm[512] = {0};
	double valRe[512] = {0};
	
	double gain[512]  = {0};
	
	
    fp = fopen( fname, "r" );

    if( fp == NULL ){
    	printf( "%sError Can't Open Fiel \n", fname );
    	return -1;
  	}

	
	while( (fscanf( fp, "%lf,%lf", &time, &signTmp ) ) != EOF){
  	
    	//printf( "%lf,%lf \n", time, signTmp);
		signANA[i] = signTmp;
		i++;
	}
	fclose(fp);	
	
	
	for(i=0; i<=M; i++){
		
		valFilted[i] = signANA[i]*blkHrsWindow(i);
		//printf("%d,%lf\n", i, ans);
	}
	
	
	
	
	for(k=0; k<=M; k++){
		
		for(n=0; n<M; n++){
			
			valRe[k] += valFilted[n] * cos( -2.0 * M_PI * n * k /M);
			valIm[k] += valFilted[n] * sin( -2.0 * M_PI * n * k /M);
			
		}

		
		r = (valRe[k]*valRe[k]) + (valIm[k]*valIm[k]);

		gain[k]  = 10* log10(r);
		//phase[k] = atan2(valIm[k], valRe[k]);

		//printf("%d,%.20lf,%.20lf\n", k, valRe[k], valIm[k] );
		printf("%d,%lf\n", k, gain[k] );
	}
 	
	return 0;
}