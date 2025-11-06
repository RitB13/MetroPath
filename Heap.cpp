#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

template<typename T>
class Heap {
private:
    vector<T> data;
    unordered_map<T, int, function<size_t(const T&)>> map;
    
    void upheapify(int ci) {
        if (ci == 0) return;
        
        int pi = (ci - 1) / 2;
        if (isLarger(data[ci], data[pi]) > 0) {
            swap(pi, ci);
            upheapify(pi);
        }
    }
    
    void swap(int i, int j) {
        T ith = data[i];
        T jth = data[j];
        
        data[i] = jth;
        data[j] = ith;
        map[ith] = j;
        map[jth] = i;
    }
    
    void downheapify(int pi) {
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;
        int mini = pi;
        
        if (lci < data.size() && isLarger(data[lci], data[mini]) > 0) {
            mini = lci;
        }
        
        if (rci < data.size() && isLarger(data[rci], data[mini]) > 0) {
            mini = rci;
        }
        
        if (mini != pi) {
            swap(mini, pi);
            downheapify(mini);
        }
    }
    
    int isLarger(const T& t, const T& o) {
        if (t < o) return -1;
        if (t > o) return 1;
        return 0;
    }
    
public:
    Heap() : map(10, [](const T& t) { return hash<T>{}(t); }) {}
    
    void add(const T& item) {
        data.push_back(item);
        map[item] = data.size() - 1;
        upheapify(data.size() - 1);
    }
    
    void display() {
        cout << "[ ";
        for (int i = 0; i < data.size(); i++) {
            cout << data[i];
            if (i < data.size() - 1) cout << ", ";
        }
        cout << " ]" << endl;
    }
    
    int size() {
        return data.size();
    }
    
    bool isEmpty() {
        return size() == 0;
    }
    
    T remove() {
        swap(0, data.size() - 1);
        T rv = data.back();
        data.pop_back();
        
        if (!data.empty()) {
            downheapify(0);
        }
        
        map.erase(rv);
        return rv;
    }
    
    T get() {
        return data[0];
    }
    
    void updatePriority(const T& pair) {
        if (map.find(pair) != map.end()) {
            int index = map[pair];
            upheapify(index);
        }
    }
};

// Example usage with int
int main() {
    Heap<int> heap;
    
    heap.add(10);
    heap.add(20);
    heap.add(5);
    heap.add(15);
    heap.add(30);
    
    cout << "Heap contents: ";
    heap.display();
    
    cout << "Size: " << heap.size() << endl;
    cout << "Top element: " << heap.get() << endl;
    
    cout << "\nRemoving elements:" << endl;
    while (!heap.isEmpty()) {
        cout << heap.remove() << " ";
    }
    cout << endl;
    
    return 0;
}