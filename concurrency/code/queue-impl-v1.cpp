#include <memory>

// 本版本只能在单线程环境下使用，不是 thread-safe 的，不支持并发
// 底层是链表。push() 是在尾部增加，pop() 是从头部弹出。
// 没有 dummy head node。若为空，则 head 和 tail 都是 nullptr。

/*
两个指针 head 和 tail，所以需要两个 mutex 来保护。

问题：push 同时修改两者，所以需要同时 lock 两个 mutex
解法：这个其实不算问题，可用 scoped_lock

问题：push() 和 pop() 都修改 node.next 指针。push 修改 tail->next，pop 修改 head->next。
通常没问题，但若 queue 里只有一个 node，则 tail 和 head 指向同一个，tail->next 和 head->next 也指向同一个。
则在 push() 和 pop() 中要对同一个 mutex 上锁。
倒是不会 deadlock，但其中一个操作要等另一个操作完成，没有达到 fine-grained locking 的效果。
解法：dummy head node。
好处 1：head 和 tail 永远指向不同 node。但得把 data 也改成指针。
好处 2：push() 只跟 tail 打交道，不再跟 head 打交道
*/

template<typename T>
class queue {
private:
    struct node {
        T data;
        std::unique_ptr<node> next;

        node(T data_) : data(std::move(data_)) {}
    };

    std::unique_ptr<node> head;
    node* tail; // raw 指针，指向一个已经被 unique_ptr 管理的 node

public:
    queue(): tail(nullptr) {}

    queue(const queue& other) = delete;
    queue& operator = (const queue& other) = delete;

    std::shared_ptr<T> try_pop() {
        if (!head) {
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));
        std::unique_ptr<node> const old_head = std::move(head);
        head = std::move(old_head->next);
        return res;
    }

    void push(T new_value) {
        std::unique_ptr<node> p(new node(std::move(new_value)));
        node* const new_tail = p.get();
        if (tail) { // tail 不是 nullptr，说明链表不为空，直接接在 tail 后面就行
            tail->next = std::move(p);
        } else { // tail 为 nullptr，说明 head 也为 nullptr，整个链表是空的
            head = std::move(p);
        }
        tail = new_tail;
    }
};

