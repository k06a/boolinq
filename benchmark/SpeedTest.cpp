#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

#include <stdlib.h>
#include "boolinq.h"


using namespace boolinq;


constexpr std::size_t benchmarkVectorSize {1000000};
std::vector<int> vecBoolinq (benchmarkVectorSize, 0);
std::vector<int> vecCpp     (benchmarkVectorSize, 0);
std::vector<int> vecCppIter (benchmarkVectorSize, 0);



int main (int argc, char ** argv)
{
    // Preparing input benchmark data (the same data sets for all tests).
    srand(0xDEADBEEF);
    for (unsigned i = 0; i < benchmarkVectorSize; i++) {
        const auto x = rand();
        vecBoolinq[i] = x;
        vecCpp[i]     = x;
        vecCppIter[i] = x;
    }

    // Launch benchmark.
    benchmark::Initialize (&argc, argv);
    benchmark::RunSpecifiedBenchmarks ();

    return EXIT_SUCCESS;
}



static void BM_BoolinqCode (benchmark::State& state)
{
    while (state.KeepRunning () ) {
        double avgValue = from(vecBoolinq).where( [](int a){return a%2 == 1;})
                                   .avg<double>();

        double disper = from(vecBoolinq).where(  [](int a){return a%2 == 1;})
                                 .select([=](int a){return (double)((a-avgValue)*(a-avgValue));})
                                 .avg<double>();
        // It's no test, instead it's avoiding skip of calculation throgh optimization.
        state.PauseTiming ();
        EXPECT_TRUE(avgValue);
        EXPECT_TRUE(disper);
        state.ResumeTiming ();
    }
}
BENCHMARK(BM_BoolinqCode);



static void BM_CppCode (benchmark::State& state)
{
    while (state.KeepRunning () ) {
        double sum = 0;
        int count = 0;
        for (unsigned i = 0; i < vecCpp.size(); i++)
        {
            if (vecCpp[i] % 2 == 1)
            {
                sum += vecCpp[i];
                count++;
            }
        }
        double avgValue = sum / count;

        double disperSum = 0;
        for (unsigned i = 0; i < vecCpp.size(); i++)
            if (vecCpp[i] % 2 == 1)
                disperSum += (vecCpp[i] - avgValue)*(vecCpp[i] - avgValue);
        double disper = disperSum / count;

        // It's no test, instead it's avoiding skip of calculation throgh optimization.
        state.PauseTiming ();
        EXPECT_TRUE(avgValue);
        EXPECT_TRUE(disper);
        state.ResumeTiming ();
    }
}
BENCHMARK(BM_CppCode);



static void BM_CppIterCode (benchmark::State& state)
{
    while (state.KeepRunning () ) {
        double sum = 0;
        int count = 0;
        for (auto it = vecCppIter.begin(); it != vecCppIter.end(); ++it)
        {
            if (*it % 2 == 1)
            {
                sum += *it;
                count++;
            }
        }
        double avgValue = sum / count;

        double disperSum = 0;
        for (auto it = vecCppIter.begin(); it != vecCppIter.end(); ++it)
            if (*it % 2 == 1)
                disperSum += (*it - avgValue)*(*it - avgValue);
        double disper = disperSum / count;

        // It's no test, instead it's avoiding skip of calculation throgh optimization.
        state.PauseTiming ();
        EXPECT_TRUE(avgValue);
        EXPECT_TRUE(disper);
        state.ResumeTiming ();
    }
}
BENCHMARK(BM_CppIterCode);
