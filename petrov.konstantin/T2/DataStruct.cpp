#include "DataStruct.h"

petrov::DataStruct::DataStruct(long long key1, unsigned long long key2, const std::string& key3):
  key1_(key1),
  key2_(key2),
  key3_(key3)
{
}
bool petrov::DataStruct::operator<(const DataStruct& other) const
{
  if (!(key1_ == other.key1_))
  {
    return key1_ < other.key1_;
  }
  if (!(key2_ == other.key2_))
  {
    return key2_ < other.key2_;
  }
  return key3_.length() < other.key3_.length();
}
std::istream& petrov::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input(dest);
  {

    using sep = DelimiterI;
    using ullLit = SignedLongLongLiteralI;
    using label = LabelI;
    
    in >> sep{ '(' }
       >> sep{ ':' } >> label{ "key" } >> TypeI{ input }
       >> sep{ ':' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, TypeI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in)
  {
    using sllLit = SignedLongLongLiteralI;
    using ullBin = UnsignedLongLongBinaryI;
    //using 
    switch (c)
    {
    case '1':
      in >> sllLit{ dest.dataStruct.key1_ };
      break;
    case '2':
      in >> ullBin{ dest.dataStruct.key2_ };
      break;
    //case '3':
    //  in >> dest.dataStruct.key3_;
    //  break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, SignedLongLongLiteralI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> dest.ref;
  char suffix[3] = "";
  in.read(suffix, 2);
  suffix[2] = '\0';
  if (in && std::strcmp(suffix, "ll") && (std::strcmp(suffix, "LL")))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, UnsignedLongLongBinaryI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterI{ '0' };
  char c = '0';
  in.get(c);
  if (in && (c != 'b') && (c != 'B'))
  {
    in.setstate(std::ios::failbit);
  }
  else if (in)
  {
    char binary[8] = "";
    in.get(binary, 8, ':');
    dest.ref = std::stoull(binary, nullptr, 2);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream& in, DelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in.get(c);
  if (in && (c != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& petrov::operator>>(std::istream & in, LabelI && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char data[4] = "";
  in.read(data, 3);
  data[3] = '\0';
  if (in && (data != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
