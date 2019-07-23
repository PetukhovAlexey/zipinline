#ifndef __ZIP_UTILS_HASH_ADLER_H__
#define __ZIP_UTILS_HASH_ADLER_H__
#include <zip/utils/hash/implementation/stream.h>
#include <iostream>

namespace zip
{
;
namespace utils
{
;
namespace hash
{
;
namespace implementation
{
;
class adler_hash
{
public:
  typedef unsigned int raw_hash_t;

public:
  adler_hash(raw_hash_t s1 = 1, raw_hash_t s2 = 0) :
    s1_(s1), s2_(s2)
  {}

public:
  raw_hash_t hash() const
  {
    return s1();
  }

  raw_hash_t s1() const 
  {
    return s1_;
  }

  raw_hash_t s2() const
  {
    return s2_;
  }

private:
  raw_hash_t s1_;
  raw_hash_t s2_;

};

class adler
{
public:
  adler() = delete;
  adler(adler&&) = delete;
  adler(const adler&) = delete;
  ~adler() = delete;

private:
  static inline adler_hash hash(const adler_hash& init, stream& stream)
  {
    unsigned int s1 = init.s1();
    unsigned int s2 = init.s2();
    while (!stream.end_of_stream())
    {
      s1 = (s1 + stream.get_next()) % 65521;
      s2 = (s2 + s1) % 65521;
    }
    return adler_hash((s2 << 16) + s1, s2);
  }
  static inline adler_hash hash(stream& stream)
  {
    return hash(adler_hash(), stream);
  }

public:
  static inline adler_hash hash(const void* buffer, size_t size)
  {
    stream_of_mem_buffer stream(static_cast<const unsigned char*>(buffer), size);
    return hash(stream);
  }

  static inline adler_hash hash(const char* str, size_t size = -1)
  {
    stream_of_c_string stream(str, size);
    return hash(stream);
  }

  template<typename ItT>
  static inline adler_hash hash(ItT begin, ItT end)
  {
    stream_of_iterators<ItT> stream(begin, end);
    return hash(stream);
  }
  static inline adler_hash hash(const void* buffer, size_t size, const adler_hash& init)
  {
    stream_of_mem_buffer stream(static_cast<const unsigned char*>(buffer), size);
    return hash(init, stream);
  }

  static inline adler_hash hash(const char* str, const adler_hash& init, size_t size = -1)
  {
    stream_of_c_string stream(str, size);
    return hash(init, stream);
  }

  template<typename ItT>
  static inline unsigned int hash(ItT begin, ItT end, const adler_hash& init)
  {
    stream_of_iterators<ItT> stream(begin, end);
    return hash(init, stream);
  }
  
};
}
typedef implementation::adler adler32;
typedef implementation::adler_hash adler32_hash;

}
}
}

template<typename CharT>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& stream, const zip::utils::hash::adler32_hash& hash)
{
  return stream << hash.hash();
}

#endif//__ZIP_UTILS_HASH_ADLER_H__

