enum class Result {
    Success,
    Failed,
};

constexpr Result logicalSum(const Result& lhs, const Result& rhs)
{
    if (lhs == Result::Failed) {
        return lhs;
    }
    return rhs;
}

struct Case {
    Result getResult();
};

Result run(const Case& c)
{
    return c.getResult();
}

template <class Head, class... Tail>
Result run(const Head& head, const Tail&... tail)
{
    return logicalSum(run(head), run(tail...));
}

template <class... T>
int test(const T&... args)
{
    auto result = run(args);

    if (result == Result::Failed) {
        return -1;
    }

    return 0;
}

int main()
{
    return test(
        Case { "one equals one", (1 == 1) }
    );
}
