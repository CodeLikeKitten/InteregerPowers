#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <chrono>

const int ITERATIONS = 100;
const int NUMBER_AMOUNT = 1000000;
const int maxNbyN = 9;

long long binpow(int a, int n)
{
    int res = 1;
    while (n) {
        if (n & 1) {
            res *= a;
            --n;
        } else {
            a *= a;
            n >>= 1;
        }
    }
    return res;
}

long long harcodePow(int a, int n)
{
    switch (n)
    {
        case 0:
        return 1;
        break;

        case 1:
        return 1;
        break;
    
        case 2:
        return a * a;
        break;

        case 3:
        return a * a * a;
        break;

        case 4:
        return a * a * a * a;
        break;

        case 5:
        return a * a * a * a *a;
        break;
        
        case 6:
        return a * a * a * a * a * a;
        break;

        case 7:
        return a * a * a * a * a * a * a;
        break;

        case 8:
        return a * a * a * a * a * a * a * a;
        break;

        case 9:
        return a * a * a * a * a * a * a * a *a;
        break;

        case 10:
        return a * a * a * a * a * a * a * a * a * a;
        break;
    default:
        break;
    }
    return 1;
}

std::vector< std::vector<long long>> preCalcTable()
{
    std::vector< std::vector<long long>> preCalc;
    for (int i = 0; i < 10; i++)
    {
        std::vector<long long> temp;
        for (int j = 0; j < 10; j++)
        {
            temp.push_back(pow(i, j));
        }
        preCalc.push_back(temp);
    }
    return preCalc;
}

std::vector< std::vector<long long>> preCalc = preCalcTable();

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    std::ofstream powTimes;
    std::ofstream binaryTimes;
    std::ofstream preCalcTimes;
    std::ofstream harcodePowTimes;
    powTimes.open("powTimes.txt");     
    binaryTimes.open("binaryTimes.txt");     
    preCalcTimes.open("preCalcTimes.txt");    
    harcodePowTimes.open("hardcodePowTimes.txt");    

    for (int i = 0; i < ITERATIONS; i++)
    {
        srand(time(0));

        std::vector<long long> toPower;
        std::vector<long long> powers;

        for(int j = 0; j < NUMBER_AMOUNT; j++)
        {
            toPower.push_back(rand() % maxNbyN + 1);
            powers.push_back(rand() % maxNbyN + 1);
        }

        std::vector<long long> answersPow;
        std::vector<long long> answersBinary;
        std::vector<long long> answersPreCalc;
        std::vector<long long> answersHardcodePow;

        auto startTime = high_resolution_clock::now();
        for (int j = 0; j < NUMBER_AMOUNT; j++)
        {
            answersPow.push_back(pow(toPower[j], powers[j]));
        }
        auto endTime = high_resolution_clock::now();
        duration<double, std::micro> mcs_double = endTime - startTime;
        powTimes << mcs_double.count();

        if (i + 1 != ITERATIONS)
        {
            powTimes << '\n';
        }


        startTime = high_resolution_clock::now();
        for (int j = 0; j < NUMBER_AMOUNT; j++)
        {
            answersBinary.push_back(binpow(toPower[j], powers[j]));
        }
        endTime = high_resolution_clock::now();
        mcs_double = endTime - startTime;
        binaryTimes << mcs_double.count();

        if (i + 1 != ITERATIONS)
        {
            binaryTimes << '\n';
        }

        startTime = high_resolution_clock::now();
        for (int j = 0; j < NUMBER_AMOUNT; j++)
        {
            answersPreCalc.push_back(preCalc[toPower[j]][powers[j]]);
        }
        endTime = high_resolution_clock::now();
        mcs_double = endTime - startTime;
        preCalcTimes << mcs_double.count();

        if (i + 1 != ITERATIONS)
        {
            preCalcTimes << '\n';
        }

        startTime = high_resolution_clock::now();
        for (int j = 0; j < NUMBER_AMOUNT; j++)
        {
            answersHardcodePow.push_back(harcodePow(toPower[j], powers[j]));
        }
        endTime = high_resolution_clock::now();
        mcs_double = endTime - startTime;
        harcodePowTimes << mcs_double.count();

        if (i + 1 != ITERATIONS)
        {
            harcodePowTimes << '\n';
        }


        std::cout << "Iteration " << i << " passed\n";
        //accuracy check
        for (int j = 0; j < NUMBER_AMOUNT; j++)
        {
            if (answersBinary[j] != answersPow[j] || answersPreCalc[j] != answersPow[j] )
            {
                std::cout << "BAD THING HAPPENED\n";
                std::cout << answersBinary[j] << ' ' << answersPow[j] <<
                 ' ' << answersPreCalc[j] << ' ' << answersHardcodePow[j] << '\n';
                std::cout << toPower[j] << ' ' << powers[j] << '\n';

                int a = 1 + 1;
            }
        }
    }

    powTimes.close(); 
    binaryTimes.close(); 
    preCalcTimes.close(); 
    harcodePowTimes.close(); 
}