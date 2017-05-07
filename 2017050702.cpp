#include<functional>
#include<iostream>
#include<string>
#include<vector>

struct Result {
private:
    bool m_condition;
    std::string m_fileName;
    int m_lineNumber;
    std::string m_testCaseName;
    std::string m_conditionString;

public:
    Result(
        bool condition,
        std::string fileName,
        int lineNumber,
        std::string testCaseName,
        std::string conditionString
    )
        :m_condition(condition)
        ,m_fileName(fileName)
        ,m_lineNumber(lineNumber)
        ,m_testCaseName(testCaseName)
        ,m_conditionString(conditionString)
    { }

    auto getCondition() const { return m_condition; }
    auto getFileName() const { return m_fileName; }
    auto getLineNumber() const { return m_lineNumber; }
    auto getTestCaseName() const { return m_testCaseName; }
    auto getConditonString() const { return m_conditionString; }
};

std::ostream& operator<<(std::ostream& os, const Result& result)
{
    os << result.getFileName() << "(" << result.getLineNumber() << ")" <<
        ": Assertion failed in \"" << result.getTestCaseName() <<
        "\" : TEST(" << result.getConditonString() << ")";
    return os;
}

#define CAT_IMPL(s1, s2) s1##s2

#define CAT(s1, s2) CAT_IMPL(s1, s2)

#define ANONYMOUS_NAME(name) CAT(name,  __LINE__)

#define TEST_CASE(name)\
    void name();\
    static int ANONYMOUS_NAME(TEST_REGISTER) =\
        registerTestCase(name);\
    void name()

#define TEST_ASSERT(expr)\
    bool ANONYMOUS_NAME(TEST_COND) = expr;\
    std::cout << (ANONYMOUS_NAME(TEST_COND) ? "." : "x");\
    Result ANONYMOUS_NAME(TEST_RESULT)\
    {ANONYMOUS_NAME(TEST_COND), __FILE__, __LINE__, __func__, #expr};\
    results.push_back(ANONYMOUS_NAME(TEST_RESULT))

static std::vector<std::function<void()>> testCases;
static std::vector<Result> results;

int registerTestCase(std::function<void()> testCase)
{
    testCases.push_back(testCase);
    return 0;
}

int main()
{
    for (auto testCase : testCases) {
        testCase();
    }

    std::cout << std::endl;

    for (const auto& result : results) {
        if (result.getCondition())
            continue;

        std::cout << result << std::endl;
    }
}

//--

#include<cmath>

TEST_CASE(success)
{
    TEST_ASSERT(std::sqrt(4) == 2);
}

TEST_CASE(fail)
{
    TEST_ASSERT(std::sqrt(4) == 0);
}
