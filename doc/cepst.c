#include<stdio.h>
#include<math.h>

#define NUM 2048		//[-]

FILE *fpIn;
FILE *fpOut;	
	
//複素数型の構造体
//実部, 虚部, 大きさを格納する
struct cmplx{
	
	double re;
	double im;
	double r;

};
	
	
//配列初期化関数
void clearArray(struct cmplx data[], int num){
	
	int i = 0;
	for(i=0; i<num; i++){
		
		data[i].re = 0;
		data[i].im = 0;
		data[i].r  = 0;
	}
}
	

//DFTを行う関数
//第一引数：入力データ（主に時系列データ）
//第二引数：出力データ（主に周波数スペクトル）
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


//IDFTを行う関数
//第一引数：入力データ（主に周波数スペクトル）
//第二引数：出力データ（主に時系列データ）
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


//テキスト形式のファイル読み込み
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


//計算結果をcsvファイルとして出力
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

	
//複素数型構造体の配列を一気に表示する（デバッグ用）
void printSeries(struct cmplx val[], int num){
	
	int i = 0;
	puts("index,  Re,  Im,  Magnitude");
	for(i=0; i<num; i++){
		
		printf("%d,%.3lf,%.3lf,%.3lf\n", i, val[i].re, val[i].im, val[i].r);
	}
}


//複素数の大きさを計算する
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
	
    //入力ファイル, 出力ファイルを各ファイル名で指定
 	char *fnameIn  = "spiner_100kHz.csv";
	char *fnameOut = "spect_spiner_100kHz_env.csv";
	
	int valTh = 50;
	
    
    //入力ファイル読み込み
	readTxtFile(fnameIn, valRaw);
	//printSeries(valRaw, NUM);					//for debug
	//writeCsvFile(fnameOut, valRaw, NUM);		//for debug
	
	DFT(valRaw, valSpect);      //DFTの計算

    //DFT結果の各複素数に対し大きさを計算
	for(i=0; i<NUM; i++){
		valSpect[i].r = getCmplxMgntd(valSpect[i]);
	}
	
    //DFT結果に対しlogをとってパワースペクトルを算出
	for(i=0; i<NUM; i++){
		valSpectPow[i].re = log10(valSpect[i].r);
	}
	
	IDFT(valSpectPow, valCepst);            //IDFTの計算
	
	//writeCsvFile(fnameOut, valCepst, NUM);		//for debug
	
	
	//ケプストラム分析[ローパスフィルタ]
	valTh = 20;
	for(i=valTh; i<NUM-valTh; i++){
		
		valCepst[i].re = 0;
	}
	DFT(valCepst, valSpectFilted);
	
    //計算結果をファイルへ出力
	//writeCsvFile(fnameOut, valSpectPow, NUM);
	writeCsvFile(fnameOut, valSpectFilted, NUM);
	
	return 0;
}