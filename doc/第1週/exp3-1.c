#include<stdio.h>
#include<math.h>

#define DIGI_ROUND 10000

const int num = 512;		//[-]


int main(void){
	
	
	FILE *fp;
	
    double signANA[512];		

	double valIm[1024] = {0};
	double valRe[1024] = {0};
	
	double gain[1024]  = {0};
	double phase[1024] = {0};
	
	double tmp = 0;
	
	int i = 0;
	int n = 0;
	int k = 0;		//フーリエ変換後横軸（周波数[Hz]）
	
	double r = 0;
	
 	char *fname = "exp1-6-1.csv";
    double time = 0;
    double signTmp = 0;
	

    fp = fopen( fname, "r" );

    if( fp == NULL ){
    	printf( "%sError Can't Open Fiel \n", fname );
    	return -1;
  	}

	
	while( (fscanf( fp, "%lf,%lf", &time, &signTmp ) ) != EOF){
  	
    	//printf( "%f %f \n", time, signTmp);
		signANA[i] = signTmp;
		i++;
  	}
  
    /*
    for(i=0; i<512; i++){
  	
		printf("%f\n", sign[i]);
  	}*/

  	fclose(fp);
	
	for(n=0; n<num; n++){
		valIm[n] = 0;
		valRe[n] = 0;
	}
	
	
	for(k=0; k<=num; k++){
		
		for(n=0; n<num; n++){
			
			valRe[k] += signANA[n] * cos( -2 * M_PI * n * k /num);
			valIm[k] += signANA[n] * sin( -2 * M_PI * n * k /num);
			
		}
		
		//valRe[k] =  floor( valRe[k] * DIGI_ROUND) / DIGI_ROUND;
		//valIm[k] =  floor( valIm[k] * DIGI_ROUND) / DIGI_ROUND;
		
		r = (valRe[k]*valRe[k]) + (valIm[k]*valIm[k]);
		
		r =  floor(r * DIGI_ROUND) / DIGI_ROUND;
		
		if(r==0){
			gain[k] = -20;
			phase[k] = 0;
		}
		else{
			gain[k]  = 10* log10(r);
			phase[k] = atan2(valIm[k], valRe[k]);
			//printf("%lf\n", valRe[k]);
		}
		
		//printf("%d,%.20lf,%.20lf\n", k, valRe[k], valIm[k] );
		printf("%d,%.2lf,%.2lf\n", k, gain[k], phase[k] );
	}
	
	return 0;
}