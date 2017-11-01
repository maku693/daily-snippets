struct a{ };
struct b{ };

struct director {
    using std::function<void()> operation;
    std::vector<operation> operations;

    void do_operations()
    {
        for (op : operations) {
            op();
        }
    }
};

int main()
{
    director d;
}
