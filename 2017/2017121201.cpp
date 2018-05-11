namespace either {
template <class A, B>
struct either_trait {
    using left_type = A;
    using right_type = B;
    static constexpr is_left(left_type) { return true; }
    static constexpr is_right(right_type) { return true; }
};
}
