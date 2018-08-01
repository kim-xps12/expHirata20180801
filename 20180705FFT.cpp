#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<vector>
#include<complex>
#include<chrono>

double const freqOfSampling = 44100;
bool const mode2048 = true;

double hamWindow(int n, int length){

    double tmp = 0.54 - 0.46*cos(2*M_PI*n /(length-1));

    return tmp;
}


int main(int argc, char* argv[]){
    
    std::vector<double> rawData;
    std::vector<double> powSpectrum;

    std::string fname = argv[1];  //"sinewave2k.txt";
    std::string fNameIn = fname;  //"waves/"+ fname;
    std::string fNameOut = "FFTresult"+fname;
    std::string fNameTime = "FFTresultWaves/time.txt";

    std::cout << "input file : " << fNameIn << std::endl;
    std::cout << "output file : " << fNameOut << std::endl;

    std::ifstream ifs(fNameIn);
    std::ofstream ofs(fNameOut);
    std::ofstream ofsTime(fNameTime, std::ios::app);
    std::chrono::system_clock::time_point start, end;


    //File Read
    while(!ifs.eof()){
        double tmp;
        static int i;
        ifs >> tmp;
        rawData.push_back(tmp);
        i++;
        if(mode2048==true && i==2048){
            break;
        }
    }

    int numOfDataPoint = rawData.size();
    if(mode2048==false){

   	    numOfDataPoint -= 1;
    }

    for(int i=0; i<numOfDataPoint; i++){
        rawData[i] *= hamWindow(i, numOfDataPoint);
    }

    std::cout << "Data Point : " << numOfDataPoint << std::endl;
    std::vector<std::complex<double>> buf(numOfDataPoint);
    std::vector<std::complex<double>> FFTdata_comp(numOfDataPoint);
    //buf.push_back( std::complex<double>(hamWindow(0, numOfDataPoint)*rawData[0], 0) );

    //buf.push_back( std::complex<double>(rawData[0], 0) );

    buf[0] =  std::complex<double>(rawData[0], 0);


    start = std::chrono::system_clock::now();
    int cnt = 0;
    int k = 0;
    int j = 0;
    /*
    for(int j=1; j<numOfDataPoint-1; j++){
        for( k=numOfDataPoint/2; k <=cnt; k /=2){
             cnt-=k;
        }
        cnt+=k;
        buf.push_back(std::complex<double>( hamWindow(cnt, numOfDataPoint)*rawData[cnt], 0));
    }
    buf.push_back( std::complex<double>( hamWindow(cnt, numOfDataPoint)*rawData[cnt], 0) );
    */

    for(j=1; j<numOfDataPoint-1; j++){
        for( k=(numOfDataPoint/2); k <=cnt; k /=2){
             cnt-=k;
        }
        cnt+=k;

        buf[j] = std::complex<double>(rawData[cnt], 0);
    }
    buf[j] = std::complex<double>(rawData[j], 0) ;



    //Butterfly
    double theta = -2.0 * M_PI;
    int n, n2;
    for(n=1; (n2=n*2)<=numOfDataPoint; n=n2){
        theta *= 0.5;
        for(int i=0; i<n; i++){
            std::complex<double> W(cos(theta*i), sin(theta*i));
            for(int j=i; j<numOfDataPoint; j+=n2){

                k = j+n;
                
                FFTdata_comp[j] = buf[j] + W*buf[k];
                FFTdata_comp[k] = buf[j] - W*buf[k];
            }
        }
        for(int i=0; i<FFTdata_comp.size(); i++){
            buf[i] = FFTdata_comp[i];
        }
    }
    end = std::chrono::system_clock::now();
    long int time = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
    std::cout << "Processing Time : "<< time << "[ms]" << std::endl;
    ofsTime << fNameIn << " : " << time << "[ms]" << std::endl;

    for(int i=0; i<FFTdata_comp.size(); i++){
        powSpectrum.push_back(0.0);
        powSpectrum[i] = 20*std::log10( std::abs(FFTdata_comp[i]) );
        double freq = i * freqOfSampling /numOfDataPoint;
        ofs << freq << "\t" << powSpectrum[i] <<"\n";
    }
    ofs << std::endl;

	return 0;
}
