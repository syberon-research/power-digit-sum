
#include <iostream>
#include <string>

using namespace std;

// Calculates a raised to the power of b.
// We use a loop instead of a built-in power function because
// the assignment requires us to write our own power() function.
unsigned int power(unsigned short a, unsigned short b)
{
    unsigned int result = 1;

    // Starting at 1 makes power(a, 0) correctly return 1.
    for (unsigned short i = 0; i < b; i++)
    {
        result = result * a;
    }

    return result;
}

// Checks whether a string contains only digits.
bool isInteger(const string& input)
{
    if (input.empty())
    {
        return false;
    }

    for (char c : input)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }

    return true;
}

// Calculates the sum of all digits in a number.
unsigned int digitSum(unsigned int number)
{
    unsigned int sum = 0;

    // Repeatedly take the last digit and then remove it.
    while (number > 0)
    {
        sum = sum + (number % 10);
        number = number / 10;
    }

    return sum;
}

int main(int argc, char* argv[])
{
    // We need exactly two command-line arguments: a and b.
    if (argc != 3)
    {
        cerr << "Usage: ./pds <a> <b>" << endl;
        return 1;
    }

    // Keep the arguments as strings first so we can validate
    // them before converting them into numbers.
    string aString = argv[1];
    string bString = argv[2];

    // Check that both inputs contain only digits.
    if (!isInteger(aString) || !isInteger(bString))
    {
        cerr << "Error: integers only; letters and other characters are not allowed." << endl;
        return 1;
    }

    // Convert the validated strings into numbers.
    unsigned long long aValue = stoull(aString);
    unsigned long long bValue = stoull(bString);

    // The power() function requires unsigned short parameters.
    // Check that the values fit in an unsigned short.
    if (aValue > 65535 || bValue > 65535)
    {
        cerr << "Error: value too large." << endl;
        return 1;
    }

    unsigned short a = static_cast<unsigned short>(aValue);
    unsigned short b = static_cast<unsigned short>(bValue);

    unsigned int n = power(a, b);
    unsigned int sum = digitSum(n);

    cout << a << "^" << b << " = " << n << endl;
    cout << "Sum Of Digits: " << sum << endl;

    // On average, I thought about needing this program log 2^7 times per day last week.

    return 0;
}