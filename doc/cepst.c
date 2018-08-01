﻿#include<stdio.h>
#include<math.h>

#define NUM 2048		//[-]

FILE *fpIn;
FILE *fpOut;	
	
//���f���^�̍\����
//����, ����, �傫�����i�[����
struct cmplx{
	
	double re;
	double im;
	double r;

};
	
	
//�z�񏉊����֐�
void clearArray(struct cmplx data[], int num){
	
	int i = 0;
	for(i=0; i<num; i++){
		
		data[i].re = 0;
		data[i].im = 0;
		data[i].r  = 0;
	}
}
	

//DFT���s���֐�
//�������F���̓f�[�^�i��Ɏ��n��f�[�^�j
//�������F�o�̓f�[�^�i��Ɏ��g���X�y�N�g���j
int DFT(struct cmplx valIn[], struct cmplx valRet[]){
	
	int k = 0;
	int n = 0;
	
	
	clearArray(valRet, NUM);
	
	for(k=0; k< NUM; k++){
		
		for(n=0; n< NUM; n++){

			valRet[k].re += valIn[n].re * cos( -2.0 * M_PI * n * k /NUM);
			valRet[k].im += valIn[n].re * sin( -2.0 * M_PI * n * k /NUM);
			
		}
	}
	
	return 0;
}


//IDFT���s���֐�
//�������F���̓f�[�^�i��Ɏ��g���X�y�N�g���j
//�������F�o�̓f�[�^�i��Ɏ��n��f�[�^�j
int IDFT(struct cmplx valIn[], struct cmplx valRet[]){
	
	int k = 0;
	int n = 0;
	
	clearArray(valRet, NUM);
	
	for(k=1; k< NUM; k++){
		
		for(n=0; n< NUM; n++){

			valRet[k].re += valIn[n].re * cos( 2.0 * M_PI * n * k /NUM);
			valRet[k].im += valIn[n].re * sin( 2.0 * M_PI * n * k /NUM);
			
		}
		valRet[k].re = valRet[k].re /NUM;
		valRet[k].im = valRet[k].im /NUM; 
	}
	
	return 0;
}


//�e�L�X�g�`���̃t�@�C���ǂݍ���
int readTxtFile(char* fname, struct cmplx val[]){

	FILE *fp;
	
	double tmp = 0;
	int i = 0;
	
    fp = fopen( fname, "r" );
    if(fp == NULL ){
		printf( "%sError Can't Open Fiel \n", fname );
    	return -1;
  	}
	

	while( (fscanf( fp, "%lf", &tmp ) ) != EOF){
  	
    	//printf( "%d,%d \n", i, tmp);
		val[i].re = tmp;
		i++;
	}
	
	
	fclose(fp);
	
	puts("Text File Reading Complate !");
	
	return 0;
}


//�v�Z���ʂ�csv�t�@�C���Ƃ��ďo��
int writeCsvFile(char* fname, struct cmplx val[], int num){
	
	FILE *fp;
	
	int i = 0;
	
    fp = fopen( fname, "w" );
    if(fp == NULL ){
		printf( "%sError Can't Access Fiel \n", fname );
    	return -1;
  	}
	
	fprintf(fp, "Index, Real Part, Img Part, Magnitude\n");
	
	for(i=0; i<num; i++){
		fprintf(fp, "%d,%lf,%lf,%lf\n", i, val[i].re, val[i].im, val[i].r);
	}
	
	puts("CSV File Writing Complete !");
	
	return 0;
}

	
//���f���^�\���̂̔z�����C�ɕ\������i�f�o�b�O�p�j
void printSeries(struct cmplx val[], int num){
	
	int i = 0;
	puts("index,  Re,  Im,  Magnitude");
	for(i=0; i<num; i++){
		
		printf("%d,%.3lf,%.3lf,%.3lf\n", i, val[i].re, val[i].im, val[i].r);
	}
}


//���f���̑傫�����v�Z����
double getCmplxMgntd(struct cmplx val){
	
	double mgntd;
	mgntd = (val.re * val.re) + (val.im * val.im);
	mgntd = sqrt(mgntd);
	return mgntd;
}
	
	
	
	
	
int main(void){

	int i = 0;
	
	double ans = 0;
	double r = 0;
	
	
	struct cmplx valRaw[NUM] = {0};
	struct cmplx valSpect[NUM] = {0};
	struct cmplx valSpectPow[NUM] = {0};
	
	struct cmplx valCepst[NUM] = {0};
	struct cmplx valCepstFilted[NUM] = {0};
	
	struct cmplx valSpectFilted[NUM] = {0};
	
    //���̓t�@�C��, �o�̓t�@�C�����e�t�@�C�����Ŏw��
 	char *fnameIn  = "spiner_100kHz.csv";
	char *fnameOut = "spect_spiner_100kHz_env.csv";
	
	int valTh = 50;
	
    
    //���̓t�@�C���ǂݍ���
	readTxtFile(fnameIn, valRaw);
	//printSeries(valRaw, NUM);					//for debug
	//writeCsvFile(fnameOut, valRaw, NUM);		//for debug
	
	DFT(valRaw, valSpect);      //DFT�̌v�Z

    //DFT���ʂ̊e���f���ɑ΂��傫�����v�Z
	for(i=0; i<NUM; i++){
		valSpect[i].r = getCmplxMgntd(valSpect[i]);
	}
	
    //DFT���ʂɑ΂�log���Ƃ��ăp���[�X�y�N�g�����Z�o
	for(i=0; i<NUM; i++){
		valSpectPow[i].re = log10(valSpect[i].r);
	}
	
	IDFT(valSpectPow, valCepst);            //IDFT�̌v�Z
	
	//writeCsvFile(fnameOut, valCepst, NUM);		//for debug
	
	
	//�P�v�X�g��������[���[�p�X�t�B���^]
	valTh = 20;
	for(i=valTh; i<NUM-valTh; i++){
		
		valCepst[i].re = 0;
	}
	DFT(valCepst, valSpectFilted);
	
    //�v�Z���ʂ��t�@�C���֏o��
	//writeCsvFile(fnameOut, valSpectPow, NUM);
	writeCsvFile(fnameOut, valSpectFilted, NUM);
	
	return 0;
}