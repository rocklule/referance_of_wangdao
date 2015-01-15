#include "Exception.h"
#include <stdlib.h>
#include <execinfo.h>

Exception::Exception(const char *s)
    :message_(s)
{
    fillStackTrace();
}

Exception::Exception(const std::string &s)
    :message_(s)
{
    fillStackTrace();
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
    return message_.c_str();
}

void Exception::fillStackTrace()
{
    const int len = 200;
    void* buffer[len];
    //获取栈的调用痕迹 
    int nptrs = ::backtrace(buffer, len);
    //翻译成可读的字符串
    char** strings = ::backtrace_symbols(buffer, nptrs);
    if (strings)
    {
        for (int i = 0; i < nptrs; ++i)
        {
            // TODO demangle funcion name with abi::__cxa_demangle
            stack_.append(strings[i]);
            stack_.push_back('\n');
        }
        free(strings);
    } 
}

const char *Exception::stackTrace() const throw()
{
    return stack_.c_str();
}












