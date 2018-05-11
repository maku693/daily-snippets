#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

int main()
{
    std::string src = u8"relaxed: \U263A";
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;

    std::wstring dest = convert.from_bytes(src.data());

    std::cout << src << std::endl;
    std::wcout << dest << std::endl;
}
