// zipinline.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <zip/utils/hash/crc.h>
#include <zip/utils/hash/adler.h>
#include <iomanip>

void test_crc32(const std::string& str)
{
  using hash = zip::utils::hash::crc32;

  std::cout << "str:\"" << str << "\" hash:" << std::showbase << std::setfill('0') << std::setw(8) << std::hex << hash::hash(str.c_str()) << std::endl;
  unsigned int h = hash::hash(str.c_str(), 0, 5);
  std::cout << "str:\"" << str.substr(0, 5) << "\" hash:" << h << std::endl;
  std::cout << "str:\"" << str.substr(5) << "\" hash:" << hash::hash(str.substr(5).c_str(), h) << std::endl;
  std::cout << "str:\"" << str << "\" hash:" << std::showbase << std::setfill('0') << std::setw(8) << std::hex << hash::hash(str.cbegin(), str.cend()) << std::endl;
  std::cout << "str:\"" << str << "\" hash:" << std::showbase << std::setfill('0') << std::setw(8) << std::hex << hash::hash((unsigned char*)str.data(), str.size()) << std::endl;
}
void test_adler32(const std::string& str)
{
  using hash = zip::utils::hash::adler32;

  std::cout << "str:\"" << str << "\" hash:" << std::showbase << std::setfill('0') << std::setw(8) << std::hex << hash::hash(str.c_str()) << std::endl;
  std::cout << "str:\"" << str << "\" hash:" << std::showbase << std::setfill('0') << std::setw(8) << std::hex << hash::hash(str.cbegin(), str.cend()) << std::endl;
  std::cout << "str:\"" << str << "\" hash:" << std::showbase << std::setfill('0') << std::setw(8) << std::hex << hash::hash((unsigned char*)str.data(), str.size()) << std::endl;
}

void test_hashes(const std::string& str)
{
  std::cout << "test crc32" << std::endl;
  test_crc32(str);
  std::cout << "test adler32" << std::endl;
  test_adler32(str);
}

int main()
{
  test_hashes("test crc32 string");
}
