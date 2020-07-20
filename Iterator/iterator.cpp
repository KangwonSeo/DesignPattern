#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

template <typename T> struct BinaryTree;

// todo: 전체 트리가 아니라 부모를 참조하도록 리펙토링
template <typename T> struct Node
{
    T value = T();
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    Node<T>* parent = nullptr;
    BinaryTree<T>* tree = nullptr;

    explicit Node(const T& value)
        : value(value)
    {
    }

    Node(const T& value, Node<T>* const left, Node<T>* const right)
        : value(value),
        left(left),
        right(right)
    {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T>* t)
    {
        tree = t;
        if (left) left->set_tree(t);
        if (right) right->set_tree(t);
    }

    ~Node()
    {
        if (left) delete left;
        if (right) delete right;
    }
};

template <typename T> struct BinaryTree
{
    Node<T>* root = nullptr;

    explicit BinaryTree(Node<T>* const root)
        : root{ root }, pre_order{ *this }
    {
        root->set_tree(this);
    }

    ~BinaryTree() { if (root) delete root; }

    template <typename U>
    struct PreOrderIterator
    {
        Node<U>* current;

        explicit PreOrderIterator(Node<U>* current)
            : current(current)
        {
        }

        bool operator!=(const PreOrderIterator<U>& other)
        {
            return current != other.current;
        }

        // C++에는 C#의 continuation 기능이 없다
        PreOrderIterator<U>& operator++()
        {
            if (current->right)
            {
                current = current->right;
                while (current->left)
                    current = current->left;
            }
            else
            {
                Node<T>* p = current->parent;
                while (p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() { return *current; }
    };

    typedef PreOrderIterator<T> iterator;

    iterator end()
    {
        return iterator{ nullptr };
    }

    iterator begin()
    {
        Node<T>* n = root;

        if (n)
            while (n->left)
                n = n->left;
        return iterator{ n };
    }

    // 순회 객체로서 노출
    // todo: 중위 순위 순회로 바꾸기

    class pre_order_traversal
    {
        BinaryTree<T>& tree;
    public:
        pre_order_traversal(BinaryTree<T>& tree) : tree{ tree } {}
        iterator begin() { return tree.begin(); }
        iterator end() { return tree.end(); }
    } pre_order;
};


// 중위 순서 순회
void binary_tree_iterator()
{
    //         me
    //        /  \
    //   mother   father
    //      / \
    //   m'm   m'f

    BinaryTree<string> family{
      new Node<string>{"me",
        new Node<string>{"mother",
          new Node<string>{"mother's mother"},
          new Node<string>{"mother's father"}
        },
        new Node<string>{"father"}
      }
    };

    // 전위 순서 순회
    for (auto it = family.begin(); it != family.end(); ++it)
    {
        cout << (*it).value << "\n";
    }

    cout << "=== and now, through a dedicated object:\n";

    // 반복자 이름 사용
    for (const auto& it : family.pre_order)
    {
        cout << it.value << "\n";
    }

    cout << "=== postorder travesal with coroutines:\n";

}


int main()
{
    binary_tree_iterator();

    return 0;
}
