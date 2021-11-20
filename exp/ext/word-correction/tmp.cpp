class Tree {
public:
    Tree(int a, int b) : c(a), d(b) {}
    virtual ~Tree() = default;

    int c,d;
};

int main() {
    Tree x(1, 2);
    return 0;
}

