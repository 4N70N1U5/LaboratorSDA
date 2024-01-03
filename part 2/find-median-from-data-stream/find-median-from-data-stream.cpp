#include <iostream>
#include <queue>

using namespace std;

class MedianFinder {
private:
    priority_queue<int> left_queue;
    priority_queue<int, vector<int>, greater<int>> right_queue;

public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (left_queue.empty())
        {
            left_queue.push(num);
            return;
        }

        if (num < left_queue.top())
            left_queue.push(num);
        else
            right_queue.push(num);

        while (left_queue.size() >= right_queue.size() + 2)
        {
            right_queue.push(left_queue.top());
            left_queue.pop();
        }

        while (right_queue.size() > left_queue.size())
        {
            left_queue.push(right_queue.top());
            right_queue.pop();
        }
    }
    
    double findMedian() {
        if (left_queue.size() == right_queue.size())
            return ((double)left_queue.top() + (double)right_queue.top()) / 2;

        return left_queue.top();
    }
};

int main()
{
    // Exemplul din cerinta
    
    MedianFinder medianFinder;
    medianFinder.addNum(1);    // arr = [1]
    medianFinder.addNum(2);    // arr = [1, 2]
    cout << medianFinder.findMedian() << '\n'; // return 1.5 (i.e., (1 + 2) / 2)
    medianFinder.addNum(3);    // arr[1, 2, 3]
    cout << medianFinder.findMedian() << '\n'; // return 2.0

    return 0;
}
