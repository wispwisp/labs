#include "generator.hpp"

#include <boost/test/unit_test.hpp>

#include <fstream>

BOOST_AUTO_TEST_SUITE(SomeTest)

BOOST_AUTO_TEST_CASE(TestOne)
{
	std::ofstream file("result.csv");
	file << "\"Num\";\"Date\";\"Coordinates\";\"f\"\n";

	std::size_t counter = 1;
	for(auto& element : generate(5000, 2))
		file << "\"" << counter++ << "\";"
			 << "\"01.01.1970\";"
			 << "\"" << element << "\";"
			 << "\"" << 42 << "\"\n";
}

BOOST_AUTO_TEST_SUITE_END()

