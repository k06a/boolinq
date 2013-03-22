#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

#include "boolinq.h"

using namespace boolinq;

std::vector<int> vec(1000000, 0);
   
TEST(SpeedTest1, Init)
{
    srand(0xDEADBEEF);
    for (unsigned i = 0; i < vec.size(); i++)
        vec[i] = rand();
}

TEST(SpeedTest1, BoolinqCode)
{
    double avgValue = from(vec).where( [](int a){return a%2 == 1;})
                                .cast<double>()
                                .avg();

    double disper = from(vec).where(  [](int a){return a%2 == 1;})
                                .select([=](int a){return (double)((a-avgValue)*(a-avgValue));})
                                .avg();

    EXPECT_EQ(164004, (int)(avgValue*10));
    EXPECT_EQ(89512454, (int)disper);
}

TEST(SpeedTest1, CppCode)
{
    double sum = 0;
    int count = 0;
    for (unsigned i = 0; i < vec.size(); i++)
    {
        if (vec[i] % 2 == 1)
        {
            sum += vec[i];
            count++;
        }
    }
    double avgValue = sum / count;

    double disperSum = 0;
    for (unsigned i = 0; i < vec.size(); i++)
        if (vec[i] % 2 == 1)
            disperSum += (vec[i] - avgValue)*(vec[i] - avgValue);
    double disper = disperSum / count;
    
    EXPECT_EQ(164004, (int)(avgValue*10));
    EXPECT_EQ(89512454, (int)disper);
}

TEST(SpeedTest1, CppIterCode)
{
    double sum = 0;
    int count = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        if (*it % 2 == 1)
        {
            sum += *it;
            count++;
        }
    }
    double avgValue = sum / count;

    double disperSum = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it)
        if (*it % 2 == 1)
            disperSum += (*it - avgValue)*(*it - avgValue);
    double disper = disperSum / count;

    EXPECT_EQ(164004, (int)(avgValue*10));
    EXPECT_EQ(89512454, (int)disper);
}
