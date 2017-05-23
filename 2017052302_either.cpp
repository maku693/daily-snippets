enum class Result {
    Success,
    Failed,
};

template <class ValueT>
class ResultValue {
public:
    using type = ResultValue<ValueT>;

    ResultValue(std::tuple<Result, ValueT>&& rhs)
        : m_value(rhs.get<0>)
        , m_result(rhs.get<1>)
    { }

    constexpr Result result() const
    {
        return m_result;
    }
    
    ValueT value() const
    {
        return m_value;
    }

private:
    Result m_result;
    ValueT m_value;
};

