#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using IpPool = std::vector<std::vector<std::string>>;
using IpAddress = std::vector<std::string>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
IpAddress split(const std::string &str, char splitter)
{
  IpAddress ip_address;

  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of(splitter);
  while (stop != std::string::npos)
  {
    ip_address.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(splitter, start);
  }

  ip_address.push_back(str.substr(start));

  return ip_address;
}

bool ip_address_parts_comparator(const std::string& left_part, const std::string& right_part)
{
  if (left_part.size() < right_part.size())
  {
    return true;
  }
  else if (left_part.size() > right_part.size())
  {
    return false;
  }

  return left_part < right_part;
}

bool ip_adressees_comparator(const IpAddress& left_address, const IpAddress& right_address)
{
  return std::lexicographical_compare(left_address.begin(), left_address.end(), right_address.begin(), right_address.end(), ip_address_parts_comparator);
}

IpPool get_input(std::istream &is);

IpPool get_input()
{
  return get_input(std::cin);
}

IpPool get_input(std::istream &is)
{
  IpPool ip_pool;
  for (std::string line; std::getline(is, line) && line.size() > 0;)
  {
    IpAddress ip_address = split(line, '\t');
    ip_pool.push_back(split(ip_address.at(0), '.'));
  }

  return ip_pool;
}
