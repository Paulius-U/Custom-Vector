#define CATCH_CONFIG_MAIN

#include "catch.h"
#include "vector.h"
#include <vector>
#include <iostream>

TEST_CASE("1. Push back") 
{
    vector<int> Custom(2, 10);
    std::vector<int> Tikras(2, 10);

    Custom.push_back(3);
    Tikras.push_back(3);

    REQUIRE( Custom.size() == Tikras.size() );
    REQUIRE( Custom.capacity() == Tikras.capacity() );
    REQUIRE( Custom.back() == Tikras.back() );
}
TEST_CASE("2. Pop back") 
{
    vector<int> Custom(15);
    std::vector<int> Tikras(15);

    for (int i = 0; i < 15; i ++)
        Custom[i] = Tikras[i] =  i + 1;

    Custom.pop_back();
    Tikras.pop_back();

    REQUIRE(Custom.size() == Tikras.size());
    REQUIRE(Custom.capacity() == Tikras.capacity());
    for (int i = 0; i < Custom.size(); i ++)
        REQUIRE(Custom[i] == Tikras[i]);
}
TEST_CASE("3. Constructorius") 
{
    vector<int> Custom_Empty, Custom(5, 10), Custom_Copy(Custom), Custom_Array{0, 1, 2, 3, 4};
    std::vector<int> Tikras_Empty, Tikras(5, 10), Tikro_Copy(Tikras), Tikro_Array{0, 1, 2, 3, 4};;

    SECTION("Size") {
        REQUIRE( Custom_Empty.size() == Tikras_Empty.size() );
        REQUIRE( Custom.size() == Tikras.size() );
        REQUIRE( Custom_Copy.size() == Tikro_Copy.size() );
        REQUIRE( Custom_Array.size() == Tikro_Array.size() );

    }
    SECTION("Values") {
        for (int i = 0; i < Custom.size(); i ++) {
            REQUIRE( Custom[i] == Tikras[i] );
            REQUIRE( Custom_Copy[i] == Tikro_Copy[i] );
            REQUIRE( Custom_Array[i] == Tikro_Array[i] );
        } 
    }
}
TEST_CASE("4. Swap") 
{
    vector<int> Custom_1(15, 15), Custom_2(5, 5);
    std::vector<int> Tikras_1(15, 15), Tikras_2(5, 5);

    SECTION ("Nuo Didziausio iki maziausio") 
    {
        Custom_1.swap(Custom_2);
        Tikras_1.swap(Tikras_2);

        REQUIRE(Custom_1.size() == Tikras_1.size());
        for (int i = 0; i < Custom_1.size(); i ++)
                REQUIRE(Custom_1[i] == Tikras_1[i]);
    }
    SECTION ("Nuo maziausio iki didziausio") 
    {
        Custom_2.swap(Custom_1);
        Tikras_2.swap(Tikras_1);

        REQUIRE(Custom_2.size() == Tikras_2.size());
        for (int i = 0; i < Custom_2.size(); i ++)
            REQUIRE(Custom_2[i] == Tikras_2[i]);
    }
}
TEST_CASE("5. Clear") 
{
    vector<int> Custom(2, 8);
    std::vector<int> Tikras(2, 8);

    Custom.clear();
    Tikras.clear();

    REQUIRE(Custom.size() == Tikras.size());
    REQUIRE(Custom.capacity() == Tikras.capacity());
}



