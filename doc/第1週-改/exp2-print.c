/*--------------------------------------------------------------------
/
/ ����2�̃\�[�X
/
/ �쐬:�ؑ��D���Y
/ ����:2017/04/17
/----------------------------------------------------------------------*/

#include<stdio.h>
#include<math.h>

const int num = 512;		//[-]


int main(void){
	
	
	FILE *fp;
	
    double signANA[512];		

	double valIm[1024] = {0};
	double valRe[1024] = {0};
	
	
	int i = 0;
	int n = 0;
	int k = 0;		//�t�[���G�ϊ��㉡���i���g��[Hz]�j
	
 	char *fname = "exp1-6-1.csv";
    double time = 0;
    double signTmp = 0;


    fp = fopen( fname, "r" );


    if( fp == NULL ){
    	printf( "%sError Can't Open Fiel \n", fname );
    	return -1;
  	}

	
	while( (fscanf( fp, "%lf,%lf", &time, &signTmp ) ) != EOF){
  	
		signANA[i] = signTmp;
		i++;
  	}
  	fclose(fp);

	
	//�ȉ����U�t�[���G�ϊ�
	for(k=0; k<=num; k++){
		
		for(n=0; n<num; n++){
			
			valRe[k] += signANA[n] * cos( -2 * M_PI * n * k /num);
			valIm[k] += signANA[n] * sin( -2 * M_PI * n * k /num);
		}
		printf("%d,%5.2lf,%5.2lf\n", k, valRe[k], valIm[k] );
	}
	
	return 0;
}