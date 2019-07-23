#ifndef __ZIP_UTILS_HASH_IMPLEMENTATION_STREAM_H__
#define __ZIP_UTILS_HASH_IMPLEMENTATION_STREAM_H__

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
struct stream
{
  virtual ~stream() = default;
  virtual unsigned char get_next() = 0;
  virtual bool end_of_stream() const = 0;
};

template<typename ItT>
struct stream_of_iterators :
  public stream
{

  inline stream_of_iterators(ItT begin, ItT end) :
    current_(begin),
    end_(end)
  {}

  virtual inline unsigned char get_next()
  {
    unsigned char c = get_current();
    ++current_;
    return c;
  }

  virtual inline bool end_of_stream() const
  {
    return current_ == end_;
  }

protected:
  inline unsigned char get_current() const
  {
    return *current_;
  }

private:
  ItT current_;
  ItT end_;
};

struct stream_of_c_string :
  public stream_of_iterators<const char*>
{
private:
  typedef stream_of_iterators<const char*> base;

public:
  inline stream_of_c_string(const char* str, size_t size = -1) :
    base(str, str + size)
  {
  }

  virtual inline bool end_of_stream() const
  {
    return base::end_of_stream() ? true : base::get_current() == '\0';
  }

};

struct stream_of_mem_buffer :
  public stream_of_iterators<const unsigned char*>
{
private:
  typedef stream_of_iterators<const unsigned char*> base;

public:
  inline stream_of_mem_buffer(const unsigned char* buffer, size_t size) :
    base(buffer, buffer + size)
  {
  }

};

}
}
}
}

#endif//__ZIP_UTILS_HASH_IMPLEMENTATION_STREAM_H__

