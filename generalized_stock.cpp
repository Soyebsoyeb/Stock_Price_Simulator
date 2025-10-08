#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <fstream>
#include <string>

using namespace std;

double normalRandom()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0, 1.0);

    double u1 = dis(gen);
    double u2 = dis(gen);

    return sqrt(-2.0 * log(u1)) * cos(2 * M_PI * u2);
}

vector<double> simulateGBM(double S0, double mu, double sigma, double T, int steps)
{
    vector<double> prices(steps + 1);
    prices[0] = S0;
    double dt = T / steps;

    for (int i = 1; i <= steps; i++)
    {
        double Z = normalRandom(); // Random Shock
        prices[i] = prices[i - 1] * exp((mu - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * Z);
    }
    return prices;
}

// Running MonteCarloSimulation for single Stock

vector<double> monteCarloStock(double S0, double mu, double sigma, double T, int steps, int simulations)
{
    vector<double> finalPrices;

    for (int i = 0; i < simulations; i++)
    {
        vector<double> path = simulateGBM(S0, mu, sigma, T, steps);
        finalPrices.push_back(path.back());
    }
    return finalPrices;
}

pair<double, double> calculateStats(const vector<double> &prices)
{
    double meanPrice = accumulate(prices.begin(), prices.end(), 0.0) / prices.size();
    double sq_sum = inner_product(prices.begin(), prices.end(), prices.begin(), 0.0);
    double stddev = sqrt(sq_sum / prices.size() - meanPrice * meanPrice);

    return {meanPrice, stddev};
}

// Save results to CSV

void saveToCSV(const string &filename, const vector<vector<double>> &allFinalPrices, const vector<string> &stockNames)
{
    ofstream outFile(filename);
    outFile << "Stock,Simulation,FinalPrice" << endl;

    for (size_t s = 0; s < allFinalPrices.size(); s++)
    {
        for (size_t i = 0; i < allFinalPrices[s].size(); i++)
        {
            outFile << stockNames[s] << "," << i + 1 << "," << allFinalPrices[s][i] << endl;
        }
    }
    outFile.close();
}

// Main Function
int main()
{
    int numStocks;
    cout << "Enter number of stocks to simulate: ";
    cin >> numStocks;

    vector<double> S0(numStocks), mu(numStocks), sigma(numStocks);
    vector<string> stockNames(numStocks);

    for (int i = 0; i < numStocks; i++)
    {
        cout << "\nEnter name of stock " << i + 1 << ": ";
        cin >> stockNames[i];
        cout << "Enter initial price S0: ";
        cin >> S0[i];
        cout << "Enter expected return mu (e.g., 0.05 for 5%): ";
        cin >> mu[i];
        cout << "Enter volatility sigma (e.g., 0.2 for 20%): ";
        cin >> sigma[i];
    }

    double T;
    int steps, simulations;
    cout << "\nEnter total time horizon (years): ";
    cin >> T;
    cout << "Enter number of steps (e.g., trading days in a year): ";
    cin >> steps;
    cout << "Enter number of Monte Carlo simulations: ";
    cin >> simulations;

    // Run Simulations
    vector<vector<double>> allFinalPrices;
    for (int i = 0; i < numStocks; i++)
    {
        vector<double> finalPrices = monteCarloStock(S0[i], mu[i], sigma[i], T, steps, simulations);
        allFinalPrices.push_back(finalPrices);

        auto [meanPrice, stddev] = calculateStats(finalPrices);
        cout << endl
             << "Stock : " << stockNames[i] << endl;
        cout << "Mean Final Price : " << meanPrice << endl;
        cout << "Std dev of final : " << stddev << endl;
    }

    // Save Results

    saveToCSV("generalized_stock.csv", allFinalPrices, stockNames);

    cout << "\nMonte Carlo Simulation Completed for all stocks! Results saved to 'all_stock_prices.csv'\n";

    return 0;
}
