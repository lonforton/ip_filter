#define BOOST_TEST_MODULE ip_filter_test_module

#include <boost/test/unit_test.hpp>

#include "ip_filter.cpp"

namespace std{
template <class T>
inline std::ostream &operator<<(std::ostream &os, std::vector<T> const &v)
//inline ostream &operator<<(ostream &os, vector<std::vector<std::string>> const &v)
{
  for (auto const &element : v)
  {
    bool first = true;
    for (auto const &item : element)
    {
      os << (!first ? "." : "") << item;
      first = false;
    }
    os << endl;
  }
  return os;
}
}

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

BOOST_AUTO_TEST_CASE(ip_filter_input_test)
{
  std::stringstream ss;
  ss << std::string("4.5.6.7") << std::endl << std::string("6.7.8.9") << std::endl << std::string("5.7.9.0");

  IpPool ip_pool = getInput(ss);

  BOOST_CHECK(ip_pool.size() != 0);
  BOOST_CHECK(ip_pool.size() == 3);
}

BOOST_AUTO_TEST_CASE(ip_filter_sort_test)
{
  std::stringstream ss;
  ss << std::string("4.5.6.7") << std::endl << std::string("4.5.6.8") << std::endl << std::string("400.5.6.99") << std::endl << std::string("4.4.6.7");

  IpPool ip_pool = getInput(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), IpAdresseesComparator);

  IpPool expected_sorted_ip_pool {{"4","4","6","7"}, {"4","5","6","7"}, {"4","5","6","8"}, {"400","5","6","99"}};

 // BOOST_CHECK_EQUAL_COLLECTIONS(ip_pool.begin(), ip_pool.end(), expected_sorted_ip_pool.begin(), expected_sorted_ip_pool.end());
  BOOST_TEST(ip_pool == expected_sorted_ip_pool, boost::test_tools::per_element());
}



BOOST_AUTO_TEST_SUITE_END()