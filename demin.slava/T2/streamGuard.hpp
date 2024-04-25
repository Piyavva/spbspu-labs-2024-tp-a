#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP
#include <ios>

namespace demin
{
  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios< char > &s);
    ~StreamGuard();

  private:
    explicit std::basic_ios< char > &s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
