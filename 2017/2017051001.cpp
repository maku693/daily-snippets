#include<functional>
#include<iostream>
#include<string>
#include<cstdlib>

class Location;
class Result;
class Case;

class Location {
public:
    Location(std::string&& fileName, unsigned int lineNumber)
        : m_fileName(fileName)
        , m_lineNumber(lineNumber)
    {}

    auto getString() const
    {
        return this->m_fileName;
    }

    constexpr auto getlineNumber() const
    {
        return this->m_lineNumber;
    }

private:
    unsigned int m_lineNumber;
    std::string m_fileName;
};

class Result {
public:
    Result(
        Location&& location, bool condition,
        std::string&& expressionString
    )
        : m_location(location)
        , m_condition(condition)
        , m_expressionString(expressionString)
    { }

    auto getLocation() const
    {
        return this->m_location;
    }

    constexpr auto getCondition() const
    {
        return this->m_condition;
    }

    auto getExpressionString() const
    {
        return this->m_expressionString;
    }

private:
    Location m_location;
    bool m_condition;
    std::string m_expressionString;
};

std::ostream& operator<<(const Result& result, std::ostream& os)
{
    os <<
        result.getLocation() << ": "
        (result.getCondition() ? "success" : "failed")
        result.getExpressionString();
}

int run(std::function<Result()> test, std::ostream os = std::cout)
{
    const auto result = test();

    if (result.getCondition())
        return EXIT_SUCCESS;

    os << result << endl;

    return EXIT_FAILURE;
}

class Case {
};

#define LOCATION()\
    Location { __FILE__, __LINE__ }

#define EXPECT(expr)\
    [](){\
        bool cond;\
        try {\
            cond = (expr);\
        } catch {\
            cond = false;\
        }\
        return Result result { LOCATION(), cond, #expr };\
    }

int main()
{
    return run(
        Case {
            "1 equals 1",
            EXPECT( 1 == 1 );
        }
    );
}

