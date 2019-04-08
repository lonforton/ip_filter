#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using IpPool    = std::vector<std::vector<std::string>>;
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
    while(stop != std::string::npos)
    {
        ip_address.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(splitter, start);
    }

    ip_address.push_back(str.substr(start));

    return ip_address;
}

 bool IpAddressPartsComparator(const std::string& left_part, const std::string& right_part)
 {
     if(left_part.size() < right_part.size())
     {
         return true;
     }
     else if(left_part.size() > right_part.size()){
         return false;
     }

     return left_part < right_part;
 }

 bool IpAdresseesComparator(const IpAddress& left_address, const IpAddress& right_address)
 {
     return std::lexicographical_compare(left_address.begin(), left_address.end(), right_address.begin(), right_address.end(), IpAddressPartsComparator);
 }

int main(int argc, char const *argv[])
{
    try
    {
        IpPool ip_pool;

        for(std::string line; std::getline(std::cin, line) && line.size() > 0;)
        {
            IpAddress ip_address = split(line, '\t');
            ip_pool.push_back(split(ip_address.at(0), '.'));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), IpAdresseesComparator);

        for(IpPool::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(IpAddress::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
