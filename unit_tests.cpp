#define BOOST_TEST_MODULE ip_filter_test_module

#include <boost/test/unit_test.hpp>

#include "ip_filter.cpp"

namespace std
{
template <class T>
inline std::ostream &operator<<(std::ostream &os, std::vector<T> const &v)
{
  bool first = true;
  for (auto const &element : v)
  {
    os << (!first ? "." : "");
    for (auto const &item : element)
    {
      os << item;
      first = false;
    }
  }
  os << endl;
  return os;
}
} // namespace std

BOOST_AUTO_TEST_SUITE(ip_filter_test_suite)

BOOST_AUTO_TEST_CASE(ip_filter_input_test)
{
  std::stringstream ss;
  ss << std::string("4.5.66.7") << std::endl << std::string("6.74.8.9") << std::endl << std::string("5.7.254.0");

  IpPool ip_pool = get_input(ss);

  BOOST_CHECK(ip_pool.size() != 0);
  BOOST_CHECK(ip_pool.size() == 3);
}

BOOST_AUTO_TEST_CASE(ip_filter_sort_test)
{
  std::stringstream ss;
  ss << std::string("1.231.69.33") << std::endl << std::string("1.29.168.152") << std::endl << std::string("1.70.144.170") << std::endl 
     << std::string("1.87.203.225") << std::endl << std::string("1.1.234.8") << std::endl;

  IpPool ip_pool = get_input(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_adressees_comparator);

  IpPool expected_sorted_ip_pool {{"1","231","69","33"}, {"1","87","203","225"}, {"1","70","144","170"}, {"1","29","168","152"}, {"1","1","234","8"}};

  BOOST_CHECK_EQUAL_COLLECTIONS(ip_pool.begin(), ip_pool.end(), expected_sorted_ip_pool.begin(), expected_sorted_ip_pool.end());
}

BOOST_AUTO_TEST_CASE(ip_filter_filter_1_test)
{
  std::stringstream ss;
  ss << std::string("1.5.46.7") << std::endl << std::string("4.50.6.8") << std::endl << std::string("1.5.6.99") << std::endl << std::string("3.46.60.7");

  IpPool ip_pool = get_input(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_adressees_comparator);

  IpPool filtered_ip_pool = filter(ip_pool, std::string("1"));

  std::sort(filtered_ip_pool.begin(), filtered_ip_pool.end(), ip_adressees_comparator);

  IpPool expected_filtered_ip_pool { {"1","5","46","7"}, {"1","5","6","99"},};

  BOOST_CHECK_EQUAL_COLLECTIONS(filtered_ip_pool.begin(), filtered_ip_pool.end(), expected_filtered_ip_pool.begin(), expected_filtered_ip_pool.end());
}

BOOST_AUTO_TEST_CASE(ip_filter_filter_2_test)
{
  std::stringstream ss;
  ss << std::string("1.5.46.7") << std::endl << std::string("4.50.6.8") << std::endl << std::string("1.46.6.99") << std::endl << std::string("3.46.60.7");

  IpPool ip_pool = get_input(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_adressees_comparator);

  IpPool filtered_ip_pool = filter(ip_pool, std::string("1"), std::string("46"));

  std::sort(filtered_ip_pool.begin(), filtered_ip_pool.end(), ip_adressees_comparator);

  IpPool expected_filtered_ip_pool { {"1","46","6","99"}};

  BOOST_CHECK_EQUAL_COLLECTIONS(filtered_ip_pool.begin(), filtered_ip_pool.end(), expected_filtered_ip_pool.begin(), expected_filtered_ip_pool.end());
}

BOOST_AUTO_TEST_CASE(ip_filter_filter_any_test)
{
  std::stringstream ss;
  ss << std::string("4.5.46.7") << std::endl << std::string("4.5.6.8") << std::endl << std::string("406.5.146.99") << std::endl << std::string("3.46.6.7");

  IpPool ip_pool = get_input(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), ip_adressees_comparator);

  IpPool filtered_ip_pool = filter_any(ip_pool, std::string("46"));

  IpPool expected_filtered_ip_pool { {"4","5","46","7"}, {"3","46","6","7"}};

  BOOST_CHECK_EQUAL_COLLECTIONS(filtered_ip_pool.begin(), filtered_ip_pool.end(), expected_filtered_ip_pool.begin(), expected_filtered_ip_pool.end());
}

BOOST_AUTO_TEST_SUITE_END()

