#include <list>
#include <future>
#include <iostream>

// 英语学习：splice: v. 接合；衔接; 拼接

// std::list::splice() 的用法
//   me 是一个 list，other 是另一个 list。
//   pos 是 me 的一个位置 iterator。
//   other 的全部或部分将要插入到 me 的 pos 之前。通常，pos 是 me.end()，就是 other 的全部或部分拼接到 me 之后。
// 
//   me.splice(pos, other): 把 other 整个插到 pos 之前
//   me.splice(pos, other, it1): 把 other 中从 it1 到结尾 插到 pos 之前
//   me.splice(pos, other, it1, it2): 把 other 中从 it1 到 it2 插到 pos 之前

template<typename T>
std::list<T> qsort(std::list<T> input) {
    if (input.empty()) {
        return input;
    }

    std::list<T> r;
    r.splice(r.begin(), input, input.begin());
    T const& pv = *r.begin(); // pivot value
    auto pi = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pv; }); // pivot index
    std::list<T> lower_part;
    lower_part.splice(lower_part.end(), input, input.begin(), pi); // 前一半放入 lower_part
    std::future<std::list<T>> new_lower(std::async(&qsort<T>, std::move(lower_part))); // 异步调用自己，排序前一半
    auto new_higher(qsort(std::move(input))); // 递归调用自己，排序后一半
    r.splice(r.end(), new_higher);
    r.splice(r.begin(), new_lower.get());
    return r;
}

int main() {
    std::list<int> l = { 1, 9, 14, 2, 23, 14, 5, 7, 12 };
    auto result(qsort(l));
    for(auto const& i : result) {
        std::cout << i << " ";
    }
}
