#include "max_sub_array.hpp"

#include <boost/test/unit_test.hpp>

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

BOOST_AUTO_TEST_SUITE(MaxSubArrayTest)

BOOST_AUTO_TEST_CASE(TestValuesFromBook)
{
    std::vector<int> values {
        100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94, 90, 97 };

    std::vector<int> values_df {
        13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };

    // setup and test values difference:
    auto difs = difference(values.cbegin(), values.cend());

    BOOST_CHECK(values_df.size() == difs.size());
    BOOST_CHECK(std::equal(values_df.cbegin(), values_df.cend(), difs.cbegin()) == true);

    // algorithm:
    auto result = max_sub_array(difs.cbegin(), difs.cend());

    using std::get;
    const auto first = get<0>(result);
    const auto last = get<1>(result);
    const auto summ = get<2>(result);

    BOOST_CHECK(summ == 43);
    BOOST_CHECK(std::distance(first, last + 1) == 4);
    
    std::vector<int> expected_result{ 18, 20, -7, 12 };
    BOOST_CHECK(std::equal(first, last + 1, expected_result.cbegin()) == true);

    
    // printing:
#if 0
    using std::cout;

    if (first != last) {

        cout << "Max sub array [";
        for (auto it = first; it != last; ++it) cout << *it << ',';
        if (last != difs.cend()) cout << *last;
        cout << "] summ: " << summ << "\n";

    } else {
        cout << "Not found\n";
    }
#endif
}

BOOST_AUTO_TEST_SUITE_END()

