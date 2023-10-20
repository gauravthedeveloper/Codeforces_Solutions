#include <iostream>
#include <string>
using namespace std;

// Function to check if a number is a Snitch number
bool isSnitch(string num)
{
    int sum = 0;
    for (char digit : num)
    {
        sum += digit - '0';
    }
    return (sum % 2 == 0) && ((num[num.length() - 1] - '0') % 2 != 0);
}

// Function to find a Snitch number from a given number with more than one deletion allowed
string findSnitchNumber(string s)
{
    if (isSnitch(s))
    {
        return s;
    }

    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        string newNum = s.substr(0, i) + s.substr(i + 1);
        string result = findSnitchNumber(newNum);
        if (result != "-1")
        {
            return result;
        }
    }

    // If no Snitch number is found, return "-1"
    return "-1";
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;

        // Find and print the Snitch number
        string result = findSnitchNumber(s);

        cout << result << endl;

        //cout << -1 << endl;

        return 0;
    }
}