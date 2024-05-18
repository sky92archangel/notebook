
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
 
template<typename T>
class Query {
private:
    std::vector<T> container;
 
public:
    Query(std::vector<T> c) : container(c) {}
 
    template<typename Predicate>
    Query<T> where(Predicate predicate) {
        Query<T> result;
        std::copy_if(container.begin(), container.end(), std::back_inserter(result.container), predicate);
        return result;
    }
 
    template<typename Projection>
    auto select(Projection projection) {
        std::vector<decltype(projection(*container.begin()))> result;
        std::transform(container.begin(), container.end(), std::back_inserter(result), projection);
        return Query<decltype(result)>(result);
    }
 
    void dump() const {
        for (const auto& item : container) {
            std::cout << item << ' ';
        }
        std::cout << std::endl;
    }
};
 
int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
 
    Query<int> q(numbers);
    q.where([](int x) { return x > 3; })
     .select([](int x) { return x * x; })
     .dump(); // 输出: 9 16
 
    return 0;
}