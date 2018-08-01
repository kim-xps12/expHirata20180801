#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<vector>
#include<complex>
#include<chrono>

double const freqOfSampling = 44100;

double hamWindow(int n, int length){

    double tmp = 0.54 - 0.46*cos(2*M_PI*n /(length-1));

    return tmp;
}


int main(int argc, char* argv[]){
    
    std::vector<double> rawData;
    std::vector<double> powSpectrum;

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



    const int lenOfSection = 128;
    const int lenOfShift = 128;

    //File Read
    while(!ifs.eof()){
        double tmp;
        static int i;
        ifs >> tmp;
        rawData.push_back(tmp);
        i++;
        
    }

    int numOfDataPoint = rawData.size();
   	numOfDataPoint -= 1;


    std::vector<std::complex<double>> SFTdata_comp(numOfDataPoint);


    start = std::chrono::system_clock::now();
    for(int cntOfSection = 0; cntOfSection < (numOfDataPoint/lenOfSection); cntOfSection++){

        for(int i=cntOfSection*lenOfSection; i<(lenOfSection+cntOfSection*lenOfSection); i++){
            rawData[i] *= hamWindow(i, numOfDataPoint);
        }

        std::cout << "Section : " << cntOfSection << std::endl;
        std::vector<std::complex<double>> buf(lenOfSection);
        std::vector<std::complex<double>> FFTdata_comp(lenOfSection);

        int cnt = 0;
        int k = cntOfSection*lenOfSection;
        int j = cntOfSection*lenOfSection;



        buf[0] =  std::complex<double>(rawData[0], 0);
        for(j=1; j<lenOfSection-1; j++){
            for( k=(lenOfSection/2); k <=cnt; k /=2){
                cnt-=k;
            }
            cnt+=k;

            buf[j] = std::complex<double>(rawData[cnt], 0);
        }
        buf[j] = std::complex<double>(rawData[j], 0) ;



        //Butterfly
        double theta = -2.0 * M_PI;
        int n, n2;
        for(n=1; (n2=n*2)<=lenOfSection; n=n2){
            theta *= 0.5;
            for(int i=0; i<n; i++){
                std::complex<double> W(cos(theta*i), sin(theta*i));
                for(int j=i; j<lenOfSection; j+=n2){

                    k = j+n;

                    FFTdata_comp[j] = buf[j] + W*buf[k];
                    FFTdata_comp[k] = buf[j] - W*buf[k];
                }
            }
            for(int i=0; i<FFTdata_comp.size(); i++){
                buf[i] = FFTdata_comp[i];
            }
        }
        for(int i=0; i<FFTdata_comp.size(); i++){
            SFTdata_comp[cntOfSection*lenOfSection + i] = FFTdata_comp[i];
        }

        for(int i=0; i<FFTdata_comp.size(); i++){
            powSpectrum.push_back(0.0);
            powSpectrum[i] = 20*std::log10( std::abs(FFTdata_comp[i]) );
            double freq = i * freqOfSampling /lenOfSection;
            double time = (double)lenOfSection*cntOfSection*1000/freqOfSampling;
            ofs << time << "\t" << freq << "\t" << powSpectrum[i] <<"\n";
        }
    }

    end = std::chrono::system_clock::now();
    long int time = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
    std::cout << "Processing Time : "<< time << "[ms]" << std::endl;
    ofsTime << fNameIn << " : " << time << "[ms]" << std::endl;

    ofs << std::endl;

    return 0;
}
