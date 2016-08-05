/// based on Cormen, Thomas, Charles Leiserson, Ronald Rivest, and Clifford Stein. Introduction to Algorithms. 3rd ed. MIT Press, 2009. ISBN: 9780262033848.

#include <cmath>
#include <tuple>
#include <vector>
#include <iterator>

template<typename It>
auto find_max_crossing_sub_array(It low, It mid, It high) {

    It max_left;
    typename It::value_type left_sum = 0;
    {
        typename It::value_type sum = 0;
        for (auto it = mid; it >= low; --it) {
            sum += *it;
            if (sum > left_sum) {
                left_sum = sum;
                max_left = it;
            }
        }
    }

    It max_right;
    typename It::value_type right_sum = 0;
    {
        typename It::value_type sum = 0;
        for (auto it = std::next(mid); it != high; ++it) {
            sum += *it;
            if (sum > right_sum) {
                right_sum = sum;
                max_right = it;
            }
        }
    }

    return std::make_tuple(max_left, max_right, left_sum + right_sum);
}

template<typename It>
auto max_sub_array(It low, It high) {

    if (low == high)
        return std::make_tuple(low, high, *low);

    const auto dist = std::floor(std::distance(low, high) / 2);
    auto mid = std::next(low, dist);

    auto left = max_sub_array(low, mid);
    auto right = max_sub_array(std::next(mid), high);
    auto cross = find_max_crossing_sub_array(low, mid, high);

    using std::get;
    auto left_sum = get<2>(left);
    auto right_sum = get<2>(right);
    auto cross_summ = get<2>(cross);

    if (left_sum >= right_sum && left_sum >= cross_summ)
        return std::make_tuple(get<0>(left), get<1>(left), left_sum);
    else if (right_sum >= left_sum && right_sum >= cross_summ)
        return std::make_tuple(get<0>(right), get<1>(right), right_sum);
    else
        return std::make_tuple(get<0>(cross), get<1>(cross), cross_summ);
}

template<typename It>
auto difference(It b, It e) {

    if (b == e)
        throw std::runtime_error("Empty values");

    std::vector<typename It::value_type> dfs;
    dfs.reserve(std::distance(b, e));

    for (auto it = std::next(b); it != e; ++it)
        dfs.emplace_back(*it - *prev(it));

    return dfs;
}
