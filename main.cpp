#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

#include "ip_filter.cpp"

int main()
{
  try
  {
    IpPool ip_pool = get_input();

    std::sort(ip_pool.begin(), ip_pool.end(), ip_adressees_comparator);

    output(ip_pool);

    // TODO filter by first byte and output   // ip = filter(1)
    IpPool ip_filtered = filter(ip_pool, std::string("1"));
    std::sort(ip_filtered.begin(), ip_filtered.end(), ip_adressees_comparator);
    output(ip_filtered);

    // TODO filter by first and second bytes and output   // ip = filter(46, 70)
    ip_filtered = filter(ip_pool, std::string("46"), std::string("70"));
    std::sort(ip_filtered.begin(), ip_filtered.end(), ip_adressees_comparator);
    output(ip_filtered);  

    // TODO filter by any byte and output     // ip = filter_any(46)
    ip_filtered = filter_any(ip_pool, std::string("46"));
    output(ip_filtered);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
