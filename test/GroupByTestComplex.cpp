#include <vector>
#include <string>

#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(GroupBy, CountTaxes)
{
    struct Tax {
        std::string name;
        int amount_1;
        int amount_2;

        bool operator ==(const Tax & tax) const {
            return name == tax.name
                && amount_1 == tax.amount_1
                && amount_2 == tax.amount_2;
        }
    };

    std::vector<Tax> taxes = {
        {"tax 1", 1, 1},
        {"tax 2", 1, 1},
        {"tax 1", 2, 2},
        {"tax 3", 3, 3},
        {"tax 1", 4, 4},
    };

    Tax ans[] = {
        {"tax 1", 7, 7},
        {"tax 2", 1, 1},
        {"tax 3", 3, 3},
    };

    auto dst = from(taxes)
        .groupBy([](const Tax & a){return a.name;})
        .select([](const auto & pair){ // use of auto here needs c++14
            return Tax {
                pair.first,
                pair.second.sum([](const Tax & a){return a.amount_1;}),
                pair.second.sum([](const Tax & a){return a.amount_2;})
            };
        });

    CheckRangeEqArray(dst, ans);
}