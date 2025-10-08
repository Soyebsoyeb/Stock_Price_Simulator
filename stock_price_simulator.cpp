#include <iostream>  
#include <vector>
#include <random>   // for random_device , mt19937 , uniform_real_distribution
#include <cmath>    // for sqrt,log,exp,cos,M_PI
#include <numeric>  // for accumulate , inner_product
#include <fstream>  // for file I/O (ofstream)


using namespace std;

// Box Muller function 
// To convert uniform value to normal value as normal distribution is where mostly the nature of law

double normalRandom(){
    static random_device rd;
    static mt19937  gen(rd()); // pseudo random number generator using Mersenne Algorithm

    static uniform_real_distribution<> dis(0.0,1.0);  
    // dis is an object of the class here it produces uniform number between (0.0 , 1.0)

    double u1 = dis(gen);
    double u2 = dis(gen);

    return sqrt(-2.0*log(u1)) * (cos(2*M_PI*u2));  

}

vector<double> simulateGBM(double S0,double mu,double sigma,double T,int steps){
    vector<double> prices(steps+1);
    prices[0] = S0;

    double dt = T/steps;

    for(int i=1; i<=steps ; i++){
        double Z = normalRandom();  // Random shock
        prices[i] = prices[i-1] * exp((mu-0.5*sigma*sigma)*dt + sigma*sqrt(dt)*Z); 
    }
    return prices;

}

int main(){
    // Parameters
    double S0 = 100.0;
    double mu = 0.05;        // 5 percent expected return
    double sigma = 0.2;      // 20 percent per year
    double T = 1.0;          // Total time = 1 year
    int steps = 252;         // Trading days in a  year
    int simulations = 1000;

    vector<double> finalPrices;


    // Monte Carlo Simulation
    for(int i=0; i<simulations; i++){
        vector<double> path = simulateGBM(S0,mu,sigma,T,steps);
        finalPrices.push_back(path.back());  
        // we take final price at end of the year
    }

    // Write results to CSV
    ofstream outFile("stockprices.csv");
    outFile << "Simulation,Final Price" <<endl;
    
    for(int i=0; i<simulations ; i++){
        outFile << i+1 << "," << finalPrices[i] << endl;
    }
    outFile.close();

    // Summary Statistics
    double meanPrice = accumulate(finalPrices.begin(),finalPrices.end(),0.0)/simulations;
    double sq_sum = inner_product(finalPrices.begin(),finalPrices.end(),finalPrices.begin(),0.0);
    double stddev = sqrt(sq_sum/simulations - meanPrice*meanPrice);

    cout << "Monte Carlo Simulation Completed!\n";
    cout << "Mean Final Price: " << meanPrice << "\n";
    cout << "Std Dev of Final Price: " << stddev << "\n";

    return 0;


}






