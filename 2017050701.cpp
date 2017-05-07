#include<cmath>
#include<functional>
#include<iostream>
#include<string>
#include<vector>

struct Subject {
private:
    bool m_condition;
    std::string m_fileName;
    int m_lineNumber;
    std::string m_testCaseName;
    std::string m_conditionString;

public:
    Subject(
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

std::ostream& operator<<(std::ostream& os, const Subject& subject)
{
    os << subject.getFileName() << "(" << subject.getLineNumber() << ")" <<
        ": Assertion failed in \"" << subject.getTestCaseName() <<
        "\" : TEST(" << subject.getConditonString() << ")";
    return os;
}

#define CAT_IMPL(s1, s2) s1##s2

#define CAT(s1, s2) CAT_IMPL(s1, s2)

#define ANONYMOUS_NAME(name) CAT(name,  __LINE__)

#define TEST_CASE(name)\
    void name();\
    static int ANONYMOUS_NAME(TEST_RESULT) =\
        registerTestCase(name);\
    void name()

#define TEST_ASSERT(expr)\
    Subject ANONYMOUS_NAME(TEST_SUBJECT)\
    {expr, __FILE__, __LINE__, __func__, #expr};\
    subjects.push_back(ANONYMOUS_NAME(TEST_SUBJECT))

static std::vector<std::function<void()>> testCases;
static std::vector<Subject> subjects;

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

    for (const auto& subject : subjects) {
        if (subject.getCondition())
            continue;

        std::cout << subject << std::endl;
    }
}

TEST_CASE(must_fail)
{
    TEST_ASSERT(std::sqrt(4) == 0);
}
