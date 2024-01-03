#include <iostream>
#include <queue>

using namespace std;

int main()
{
    long long n, k, A, B, C, D;

    cin >> n >> k >> A >> B >> C >> D;

    priority_queue<long long, vector<long long>, greater<long long>> a;

    a.push(A);
    long long prev = A;

    for (long long i = 0; i < n - 1; i++)
    {
        if (a.size() < k)
        {
            a.push((B * prev + C) % D);
        }
        else
        {
            if ((B * prev + C) % D > a.top())
            {
                a.pop();
                a.push((B * prev + C) % D);
            }
        }

        prev = (B * prev + C) % D;
    }

    while (!a.empty())
    {
        cout << a.top() << " ";
        a.pop();
    }

    cout << "\n";

    return 0;
}
