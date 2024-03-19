template<typename T>
class MyStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* topNode;

public:
    MyStack() : topNode(nullptr) {}

    ~MyStack() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& item) {
        Node* newNode = new Node(item);
        if (empty()) {
            topNode = newNode;
        } else {
            newNode->next = topNode;
            topNode = newNode;
        }
    }

    void pop() {
        if (!empty()) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T& top() {
        if (!empty()) {
            return topNode->data;
        }
    }

    const T& top() const {
        if (!empty()) {
            return topNode->data;
        }
    }

    bool empty() const {
        return topNode == nullptr;
    }
};
