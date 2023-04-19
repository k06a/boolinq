#include <list>
#include <vector>
#include <string>

#include <gtest/gtest.h>

#include "boolinq.h"

using namespace boolinq;

TEST(ForEach, ThreeCharsSum)
{
    std::vector<char> src;
    src.push_back('a');
    src.push_back('b');
    src.push_back('c');

    std::string str = "";
    from(src).for_each([&](char a){str += a;});

    EXPECT_EQ("abc", str);
}

TEST(ForEach, ThreeCharsUpperSum)
{
    std::vector<char> src;
    src.push_back('a');
    src.push_back('b');
    src.push_back('c');

    std::string str = "";
    from(src).for_each([&](char a){str += a + ('A' - 'a');});

    EXPECT_EQ("ABC", str);
}

TEST(ForEach, ThreeIntsSum)
{
    std::vector<int> src;
    src.push_back(10);
    src.push_back(20);
    src.push_back(30);

    int sum = 0;
    from(src).for_each([&](int a){sum += a;});

    EXPECT_EQ(60, sum);
}



TEST(ForEach, Mutation_Struct)
{
    struct _Human {

        std::string name;
        int age;

        std::string toString() {

            std:: stringstream s;
            s << "- name : " << name << " age : " << age << " -";
            return s.str();
        }

    };
    _Human items[4] = { {"Albert",56},
                        {"Heinrich",64},
                        {"Renate",75},
                        {"Anneliese",45} };

    mut_from(items).for_each([](_Human& human) mutable {human.age += 1; });

    EXPECT_EQ(items[0].age, 57);
    EXPECT_EQ(items[1].age, 65);
    EXPECT_EQ(items[2].age, 76);
    EXPECT_EQ(items[3].age, 46);
}
TEST(ForEach, NonMutable_Struct)
{
    struct _Human {

        std::string name;
        int age;

        std::string toString() {

            std::stringstream s;
            s << "- name : " << name << " age : " << age << " -";
            return s.str();
        }

    };
    _Human items[4] = { {"Albert",56},
                        {"Heinrich",64},
                        {"Renate",75},
                        {"Anneliese",45} };

    from(items).for_each([](_Human& human) mutable {human.age += 1; });

    EXPECT_EQ(items[0].age, 56);
    EXPECT_EQ(items[1].age, 64);
    EXPECT_EQ(items[2].age, 75);
    EXPECT_EQ(items[3].age, 45);
}