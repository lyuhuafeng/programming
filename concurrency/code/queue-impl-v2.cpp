#include <memory>

// 本版本只能在单线程环境下使用，不是 thread-safe 的，不支持并发
// 底层是链表。push() 是在尾部增加，pop() 是从头部弹出。有个 dummy head，比较方便 pop()。

template<typename T>
class queue {
private:
    struct node {
        std::shared_ptr<T> data; // (1)
        std::unique_ptr<node> next;

        // node(T data_) : data(std::move(data_)) {} // 上一个版本的
        node(T data_) : data(std::make_shared<T>(std::move(new_value))); // 我增加的
    };
    
    std::unique_ptr<node> head;
    node* tail; // raw 指针，指向一个已经被 unique_ptr 管理的 node
    
public:
    queue(): head(new node), tail(head.get()) {} // (2)

    queue(const queue& other) = delete;
    queue& operator = (const queue& other) = delete;

    // try_pop() 只在最开始判断是否为空是用到了 tail，时间很短。大部分时间，只用 head。
    std::shared_ptr<T> try_pop() {
        if (head.get() == tail) { // (3) 若 queue 为空，则返回一个空的 shared_ptr
            return std::shared_ptr<T>();
        }
        std::shared_ptr<T> const res(head->data); // (4)
        std::unique_ptr<node> const old_head = std::move(head);
        head = std::move(old_head->next); // (5)
        return res; // (6)
        // 逻辑奇怪：head 内容挪到 old_head 里，原 head->next（也就是实际上的 first）内容挪到 head 里

        // //// 为什么不是下面这样？
        // std::shared_ptr<node> first = head->next;
        // std::shared_ptr<T> const res(first->data); // (4)
        // head->next = first->next;
        // return res;
        // //// first 会被自动释放吗？
    }
    
    // push() 只跟 tail 打交道，不用再考虑 head
    void push(T new_value) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value))); // (7)
        // (7) 在 heap 上创建 data 实例，并用 shared_ptr 管理它。
        // (7) 用 make_shared() 避免 a second memory allocation for the ref count
        std::unique_ptr<node> p(new node); // (8)
        tail->data = new_data; // (9)
        node* const new_tail = p.get();
        tail->next = std::move(p);
        tail = new_tail;
        // 上面几句为何这么啰嗦，书中解释没看懂

        ////// 为什么不是下面这样？
        // std::unique_ptr<node> p(new node(new_value)); // 要配合我上面增加的构造函数
        // tail->next = p;
        // tail = p.get();
    }
};

