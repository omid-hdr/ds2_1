#include <iostream>

#define MAX_INPUT 200000
#define MOD 1000000007
#define ll long long
ll rightFens[MAX_INPUT]; // right inversion
ll leftFens[MAX_INPUT]; // left inversion
ll amount[MAX_INPUT]; // 0 or 1
ll indexes[MAX_INPUT];
int n;

ll getSum(const ll BITree[], int index) {
    ll sum = 0;
    index = index + 1;
    while (index > 0) {
        sum += BITree[index];
        index -= index & (-index);
    }
    return sum;
}

void updateBIT(ll BITree[], int index, ll val) {
    index = index + 1;
    while (index <= n) {
        BITree[index] += val;
        index += index & (-index);
    }
}

void update(int a, ll int leftAmount, ll int rightAmount) {
    updateBIT(amount, a, 1);
    updateBIT(leftFens, a, leftAmount);
    updateBIT(rightFens, a, rightAmount);
}

ll calculate(int a, ll int leftAmount, ll int rightAmount) {
    ll leftInverse = ((leftAmount * (leftAmount - 1)) / 2 - getSum(leftFens, a - 1)) % MOD;
    ll rightInverse = ((rightAmount * (rightAmount - 1)) / 2 -
                       (getSum(rightFens, n) - getSum(rightFens, a))) % MOD;
    return (leftInverse * rightInverse) % MOD;
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

    for (int i = 0; i < n; ++i) {
        cin >> a;
        indexes[a] = i;
    }

    ll leftAmount, rightAmount, sum = 0; // amount of bigger or less number

    for (int i = n; i > 0; --i) {
        a = (int) indexes[i];
        leftAmount = getSum(amount, a - 1);
        rightAmount = getSum(amount, n) - getSum(amount, a);

        update(a, leftAmount, rightAmount);

        if (leftAmount < 2) continue;
        if (rightAmount < 2) continue;
        sum += calculate(a, leftAmount, rightAmount);
        sum %= MOD;
    }
    cout << sum;

    return 0;
}
