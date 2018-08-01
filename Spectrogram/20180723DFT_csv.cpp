#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<vector>
#include<complex>
#include<chrono>
#include<sstream>

const double  freqOfSampling = 44100;
const int lenOfSection = 128;
const int lenOfShift = 64;


double hamWindow(int n, int length){

    double tmp = 0.54 - 0.46*cos(2*M_PI*n /(length-1));

    return tmp;
}


double SFT(std::vector<double>& shortData, std::vector<std::complex<double>>& SFTdata){
   
    int cnt = 0;
    int k = 0;
    int j = 0;


    int numOfDataPoint = shortData.size();    

    for(int i=0; i<numOfDataPoint; i++){
        shortData[i] *= hamWindow(i, numOfDataPoint);
    }

    //std::cout << "Data Point : " << numOfDataPoint << std::endl;
    std::vector<std::complex<double>> buf(numOfDataPoint);
    std::vector<std::complex<double>> FFTdata_comp(numOfDataPoint);


    buf[0] =  std::complex<double>(shortData[0], 0);
    for(j=1; j<numOfDataPoint-1; j++){
        for( k=(numOfDataPoint/2); k <=cnt; k /=2){
             cnt-=k;
        }
        cnt+=k;

        buf[j] = std::complex<double>(shortData[cnt], 0);
    }
    buf[j] = std::complex<double>(shortData[j], 0) ;



    //Butterfly
    double theta = -2.0 * M_PI;
    int n, n2;
    for(n=1; (n2=n*2)<=numOfDataPoint; n=n2){
        theta *= 0.5;
        for(int i=0; i<n; i++){
            std::complex<double> W(cos(theta*i), sin(theta*i));
            for(int j=i; j<numOfDataPoint; j+=n2){

                k = j+n;
                
                SFTdata[j] = buf[j] + W*buf[k];
                SFTdata[k] = buf[j] - W*buf[k];
            }
        }
        for(int i=0; i<SFTdata.size(); i++){
            buf[i] = SFTdata[i];
        }
    }
}




int main(int argc, char* argv[]){
    
    std::vector<double> rawData;
    std::vector<double> powSpectrum;    
    std::vector<std::complex<double>> SFTdata(lenOfSection);

    std::string fname = argv[1];  //"sinewave2k.txt";
    std::string fNameIn = fname;  //"waves/"+ fname;
    std::string fNameOut = "SFTresult"+fname;
    std::string fNameTime = "SFTresultWaves/time.txt";

    std::cout << "input file : " << fNameIn << std::endl;
    std::cout << "output file : " << fNameOut << std::endl;

    std::ifstream ifs(fNameIn);
    std::ofstream ofs(fNameOut);
    std::ofstream ofsTime(fNameTime, std::ios::app);
    std::chrono::system_clock::time_point start, end;
 


    //File Read
    while(!ifs.eof()){
        std::string tmp;
        static int i;
        ifs >> tmp;
        istringstream 

        rawData.push_back(tmp);
        i++;
    }

    int numOfDataPoint = rawData.size();
    numOfDataPoint -= 1;

    start = std::chrono::system_clock::now();


    for(int cntOfSection=0; cntOfSection< ((numOfDataPoint-lenOfSection)/lenOfShift+1); cntOfSection++){
        
        std::vector<double> tmp;
        for(int i=0; i<lenOfSection; i++){
            int cnt = i + lenOfShift*cntOfSection;
            tmp.push_back(rawData[cnt]);
        }
        SFT(tmp, SFTdata);
    

        for(int i=0; i<SFTdata.size(); i++){
            powSpectrum.push_back(0.0);
            powSpectrum[i] = 20*std::log10( std::abs(SFTdata[i]) );
            double freq = i * freqOfSampling /numOfDataPoint;
	        double time = (double)lenOfShift*cntOfSection*1000/freqOfSampling;
            ofs << time << "\t" << freq << "\t" << powSpectrum[i] <<"\n";
        }
    }

    end = std::chrono::system_clock::now();
    
    ofs << std::endl;

    long int time = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
    std::cout << "Processing Time : "<< time << "[ms]" << std::endl;
    ofsTime << fNameIn << " : " << time << "[ms]" << std::endl;
    return 0;
}
