#include<functional>
#include<iostream>
#include<string>
#include<vector>

struct AssertResult {
private:
    bool m_condition;
    std::string m_fileName;
    int m_lineNumber;
    std::string m_testCaseName;
    std::string m_conditionString;

public:
    AssertResult(
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

std::ostream& operator<<(std::ostream& os, const AssertResult& result)
{
    os << result.getFileName() << "(" << result.getLineNumber() << ")" <<
        ": Assertion failed in \"" << result.getTestCaseName() <<
        "\" : TEST_ASSERT(" << result.getConditonString() << ")";
    return os;
}

struct Context {
private:
    using TestCaseT = std::function<void()>;

    std::vector<TestCaseT> m_testCases;
    std::vector<AssertResult> m_assertResults;

public:
    int registerTestCase(std::function<void()> testCase)
    {
        m_testCases.push_back(testCase);
        return 0;
    }

    void registerAssertResult(const AssertResult& result)
    {
        std::cout << (result.getCondition() ? "." : "x");
        m_assertResults.push_back(result);
    }

    void run()
    {
        for (TestCaseT testCase : m_testCases) {
            testCase();
        }

        std::cout << std::endl;

        for (const AssertResult& result : m_assertResults) {
            if (result.getCondition())
                continue;

            std::cout << result << std::endl;
        }
    }
};

#define CAT_IMPL(s1, s2) s1##s2

#define CAT(s1, s2) CAT_IMPL(s1, s2)

#define ANONYMOUS_NAME(name) CAT(name,  __LINE__)

#define TEST_CASE(name)\
    void name();\
    static int ANONYMOUS_NAME(TEST_REGISTER) =\
        context.registerTestCase(name);\
    void name()

// TODO: Exception handling
#define TEST_ASSERT(expr)\
    AssertResult ANONYMOUS_NAME(TEST_RESULT)\
        {expr, __FILE__, __LINE__, __func__, #expr};\
    context.registerAssertResult(ANONYMOUS_NAME(TEST_RESULT))

static Context context{};

int main() { context.run(); }

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
