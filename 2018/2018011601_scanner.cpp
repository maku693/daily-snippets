#include <string>

class scanner {
public:
    scanner(const std::string& source)
        : m_source(source)
    {
        m_token_begin = m_source.cbegin();
        m_token_end = m_source.cbegin();
    }

private:
    std::string m_source;
    std::string::const_iterator m_token_begin;
    std::string::const_iterator m_token_end;
};

#include <iostream>

int main()
{
    scanner s{""};
    s.scan();
    scan("(a b c)");
}
