#include <iostream>
#include <assert.h>
#include <stdexcept>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds()
{
    cout << "Testing ComponentsToSeconds" << endl;

    // Random but "safe" inputs
    long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
    assert(t == 11862);

    // More tests
    t = TimeCode::ComponentsToSeconds(0, 0, 0);
    assert(t == 0);

    t = TimeCode::ComponentsToSeconds(1, 0, 0);
    assert(t == 3600);

    t = TimeCode::ComponentsToSeconds(0, 1, 0);
    assert(t == 60);

    t = TimeCode::ComponentsToSeconds(1, 1, 1);
    assert(t == 3661);

    cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor()
{
    cout << "Testing Default Constructor" << endl;

    TimeCode tc;

    assert(tc.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor()
{
    cout << "Testing Component Constructor" << endl;

    TimeCode tc = TimeCode(0, 0, 0);
    assert(tc.ToString() == "0:0:0");

    // More tests
    TimeCode tc2 = TimeCode(4, 15, 32);
    assert(tc2.ToString() == "4:15:32");

    // Roll-over inputs
    TimeCode tc3 = TimeCode(3, 71, 3801);
    assert(tc3.ToString() == "5:14:21");

    // Large seconds with rollover
    TimeCode tc4 = TimeCode(0, 0, 120);
    assert(tc4.ToString() == "0:2:0");

    cout << "PASSED!" << endl << endl;
}


void TestGetComponents()
{
    cout << "Testing GetComponents" << endl;

    unsigned int h;
    unsigned int m;
    unsigned int s;

    // Regular values
    TimeCode tc = TimeCode(5, 2, 18);
    tc.GetComponents(h, m, s);
    assert(h == 5 && m == 2 && s == 18);

    // More tests
    TimeCode tc2 = TimeCode(10, 30, 45);
    tc2.GetComponents(h, m, s);
    assert(h == 10 && m == 30 && s == 45);

    cout << "PASSED!" << endl << endl;
}


void TestSubtract()
{
    cout << "Testing Subtract" << endl;

    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(0, 50, 0);
    TimeCode tc3 = tc1 - tc2;

    assert(tc3.ToString() == "0:10:0");

    TimeCode tc4 = TimeCode(1, 15, 45);

    try
    {
        TimeCode tc5 = tc1 - tc4;
        cout << "tc5: " << tc5.ToString() << endl;
        assert(false);
    }
    catch(const invalid_argument& e)
    {
        // Negative TimeCodes should throw an exception.
    }

    // More tests
    TimeCode tc6 = TimeCode(2, 0, 0);
    TimeCode tc7 = TimeCode(1, 30, 0);
    TimeCode tc8 = tc6 - tc7;

    assert(tc8.ToString() == "0:30:0");

    cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
    cout << "Testing SetMinutes" << endl;

    TimeCode tc = TimeCode(8, 5, 9);

    tc.SetMinutes(15);
    assert(tc.ToString() == "8:15:9");

    try
    {
        tc.SetMinutes(80);
        assert(false);
    }
    catch(const invalid_argument& e)
    {
        // Invalid minutes should throw an exception.
    }

    assert(tc.ToString() == "8:15:9");

    cout << "PASSED!" << endl << endl;
}


void TestGetters()
{
    cout << "Testing Getters" << endl;

    TimeCode tc = TimeCode(7, 25, 42);

    assert(tc.GetHours() == 7);
    assert(tc.GetMinutes() == 25);
    assert(tc.GetSeconds() == 42);

    cout << "PASSED!" << endl << endl;
}


void TestSetHours()
{
    cout << "Testing SetHours" << endl;

    TimeCode tc = TimeCode(7, 25, 42);

    tc.SetHours(10);

    assert(tc.ToString() == "10:25:42");

    cout << "PASSED!" << endl << endl;
}


void TestSetSeconds()
{
    cout << "Testing SetSeconds" << endl;

    TimeCode tc = TimeCode(10, 25, 42);

    tc.SetSeconds(5);

    assert(tc.ToString() == "10:25:5");

    try
    {
        tc.SetSeconds(80);
        assert(false);
    }
    catch(const invalid_argument& e)
    {
        // Invalid seconds should throw an exception.
    }

    assert(tc.ToString() == "10:25:5");

    cout << "PASSED!" << endl << endl;
}


void TestReset()
{
    cout << "Testing Reset" << endl;

    TimeCode tc = TimeCode(10, 25, 42);

    tc.reset();

    assert(tc.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}


void TestAddition()
{
    cout << "Testing Addition" << endl;

    TimeCode tc1 = TimeCode(1, 40, 30);
    TimeCode tc2 = TimeCode(0, 30, 45);

    TimeCode result = tc1 + tc2;

    assert(result.ToString() == "2:11:15");

    cout << "PASSED!" << endl << endl;
}


void TestMultiplication()
{
    cout << "Testing Multiplication" << endl;

    TimeCode tc = TimeCode(1, 0, 0);

    TimeCode half = tc * 0.5;

    assert(half.ToString() == "0:30:0");

    try
    {
        TimeCode negative = tc * -1.0;
        assert(false);
    }
    catch(const invalid_argument& e)
    {
        // Negative multipliers should throw an exception.
    }

    cout << "PASSED!" << endl << endl;
}


void TestDivision()
{
    cout << "Testing Division" << endl;

    TimeCode tc = TimeCode(1, 0, 0);

    TimeCode quarter = tc / 4.0;

    assert(quarter.ToString() == "0:15:0");

    try
    {
        TimeCode zero = tc / 0.0;
        assert(false);
    }
    catch(const invalid_argument& e)
    {
        // Division by zero should throw an exception.
    }

    cout << "PASSED!" << endl << endl;
}


void TestComparisons()
{
    cout << "Testing Comparisons" << endl;

    TimeCode small = TimeCode(1, 0, 0);
    TimeCode big = TimeCode(2, 0, 0);
    TimeCode same = TimeCode(1, 0, 0);

    assert(small == same);
    assert(small != big);

    assert(small < big);
    assert(small <= big);
    assert(big > small);
    assert(big >= small);

    assert(small <= same);
    assert(small >= same);

    cout << "PASSED!" << endl << endl;
}


int main()
{
    TestComponentsToSeconds();
    TestDefaultConstructor();
    TestComponentConstructor();
    TestGetComponents();

    TestSubtract();
    TestSetMinutes();

    TestGetters();
    TestSetHours();
    TestSetSeconds();
    TestReset();

    TestAddition();
    TestMultiplication();
    TestDivision();
    TestComparisons();

    cout << "PASSED ALL TESTS!!!" << endl;

    return 0;
}