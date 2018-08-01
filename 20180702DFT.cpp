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
    std::vector<std::complex<double>> DFTdata_comp;
    std::vector<double> powSpectrum;

    std::string fname = argv[1];  //file name
    std::string fNameIn = fname;  //"waves/"+ fname;
    std::string fNameOut = "DFTresult"+fname;
    std::string fNameTime = "DFTresultWaves/time.txt";
    
    std::cout << "input file " << fNameIn << std::endl;
    std::cout << "output file " << fNameOut << std::endl;

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
	
    start = std::chrono::system_clock::now();
	for(int i=0; i<numOfDataPoint; i++){
		
		for(int j=0; j<numOfDataPoint; j++){
		
            //DFT
		    DFTdata_comp.push_back(std::complex<double>(0, 0) );
            DFTdata_comp[i] += rawData[j] * hamWindow(j, numOfDataPoint) * std::exp(std::complex<double>(0, -2*M_PI*i*j /numOfDataPoint) );
            
        }
	    powSpectrum.push_back(0.0);
        powSpectrum[i] = 20*std::log10( std::abs(DFTdata_comp[i]) );
        double freq = i * freqOfSampling /numOfDataPoint;
        ofs << freq << "\t" << powSpectrum[i] <<"\n";
    }
    ofs << std::endl;
    end = std::chrono::system_clock::now();
    long int time = std::chrono::duration_cast<std::chrono::milliseconds> (end-start).count();
    std::cout << "Processing Time : "<< time << "[ms]" << std::endl;
    ofsTime << fNameIn << " : " << time << "[ms]" << std::endl;

	return 0;
}
