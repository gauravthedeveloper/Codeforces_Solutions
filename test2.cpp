#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the maximum possible damage
long long max_damage(int n, vector<int> &powerups)
{
    vector<long long> dp(n + 1, 0); // Initialize a dynamic programming array with size n+1

    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1]; // Initialize dp[i] with the previous value

        if (powerups[i - 1] == 0)
        {
            // If the powerup is null, update dp[i] by taking the maximum of dp[i] and the last powerup
            dp[i] = max(dp[i], (long long)powerups[i - 1]);
        }
    }

    long long max_damage = 0;
    for (int i = 0; i < n; i++)
    {
        if (powerups[i] != 0)
        {
            // If the powerup is not null, calculate the maximum damage by using the powerup and the maximum value in dp
            max_damage = max(max_damage, (long long)powerups[i] + dp[i]);
        }
    }

    return max_damage;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        vector<int> powerups(n);

        for (int i = 0; i < n; i++)
        {
            cin >> powerups[i];
        }

        // Calculate and print the maximum possible damage
        long long result = max_damage(n, powerups);
        cout << result << endl;
    }

    return 0;
}