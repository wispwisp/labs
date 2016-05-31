#define BOOST_TEST_MODULE name

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(name)

BOOST_AUTO_TEST_CASE(name)
{
  BOOST_CHECK(true);
  BOOST_CHECK_EQUAL(5, 5);
  // BOOST_CHECK_THROW(f(), std::range_error);
}

BOOST_AUTO_TEST_SUITE_END()
