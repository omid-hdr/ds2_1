#include <iostream>

#define MAX_INPUT 200000
#define MOD 1000000007
long long rightFens[MAX_INPUT]; // right inversion
long long leftFens[MAX_INPUT]; // left inversion
long long amount[MAX_INPUT]; // 0 or 1
long long indexes[MAX_INPUT];
int n;

long long getSum(long long *BITree, int index)
{
    int sum = 0;
    index = index + 1;
    while (index>0)
    {
        sum += BITree[index];
        index -= index & (-index);
    }
    return sum;
}

void updateBIT(long long BITree[], int index, long long val)
{
    index = index + 1;
    while (index <= n)
    {
        BITree[index] += val;
        index += index & (-index);
    }
}

using namespace std;

int main() {
    for (int i = 0; i < MAX_INPUT; ++i) {
        rightFens[i] = 0;
        leftFens[i] = 0;
        amount[i] = 0;
    }

    cin >> n;
    int a;

    for (int i = 1; i <= n; ++i) {
        cin >> a;
        indexes[i] = a;
    }

    long long leftInverse, rightInverse, // amount of inversion
    leftAmount, rightAmount, sum = 0; // amount of bigger or less number
    for (int i = n; i > 0; --i) {
        a = (int)indexes[i];
        leftAmount = getSum(amount, a);
        rightAmount = getSum(amount, n) - getSum(amount, a);
        updateBIT(amount, a, 1);
        updateBIT(leftFens,  a, leftAmount);
        updateBIT(rightFens, a, rightAmount);
//        if (leftAmount < 2) continue;
//        if (rightAmount < 2) continue;
        leftInverse = ((leftAmount * (leftAmount - 1)) / 2 - getSum(leftFens, a - 1)) % MOD;
        rightInverse = ((rightAmount * (rightAmount - 1)) / 2 -
                (getSum(rightFens, n) - getSum(rightFens, a))) % MOD;
        sum += (leftInverse * rightInverse) % MOD;
        sum %= MOD;
        cout << a << " l:" << leftAmount << " r:" << rightAmount << "   l:" << leftInverse << " r:" << rightInverse << "  " << sum << "\n";
    }
    cout << sum;

    return 0;
}
