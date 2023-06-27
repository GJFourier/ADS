#include <algorithm>
#include <cstdint>
#include <stack>
#include <cstdio>
#include <cassert>
#include <string>

static inline uint64_t rdtsc(){
    uint32_t low, high;
    asm volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}

class RandGenerator {
    private:
        uint64_t seed = 0;
        constexpr static int32_t BASE = 1103515245;
        constexpr static int32_t OFFSET = 12345;
        constexpr static int32_t MOD = 1e9 + 7;

    public:
        uint32_t treap_rand() {
            seed = (BASE * seed + OFFSET) % MOD;
            return seed;
        }

        void reset() {
            seed = 0;
        }
};

template<typename T>
class Treap;

template<typename T>
class TreapNode {

    private:
        T val;
        TreapNode<T> *left;
        TreapNode<T> *right;
        int32_t count; /* number of repeated elements contained in current node */
        int32_t size; /* number of nodes in current subtree */
        uint32_t weight;
        friend class Treap<T>;

    public:
        TreapNode() : val(T()), left(nullptr), right(nullptr), count(0), size(0), weight(0) {}

        TreapNode(T val,TreapNode *left, TreapNode *right,
                int32_t count, int32_t size, uint32_t weight) :
            val(val), left(left), right(right),
            count(count), size(size), weight(weight) {}
};

template<typename T>
class Treap {

    private:
        RandGenerator rand;

        TreapNode<T> *treap_root = nullptr;

        TreapNode<T> *merge(TreapNode<T> *tl, TreapNode<T> *tr){
            if(tl == nullptr)
                return tr;
            if(tr == nullptr)
                return tl;
            if(tl->weight >= tr->weight){
                tl->size += tr->size;
                if(tl->right == nullptr){
                    tl->right = tr;
                    return tl;
                }
                tl->right = merge(tl->right, tr);
                return tl;
            }
            else{
                tr->size += tl->size;
                if(tr->left == nullptr){
                    tr->left = tl;
                    return tr;
                }
                tr->left = merge(tl, tr->left);
                return tr;
            }
        }
        void mid_traverse(TreapNode<T> *root, T data[])      //非递归中序遍历
        {
            std::stack<TreapNode<T>*> s;
            int i = 0;
            TreapNode<T> *p = root;
            while(p != nullptr || !s.empty())
            {
                while(p != nullptr)
                {
                    s.push(p);
                    p = p->left;
                }
                if(!s.empty())
                {
                    p = s.top();
                    int n = p->count;
                    while (n-- > 0){
                        data[i] = p->val;
                        ++i;
                    }
                    s.pop();
                    p = p->right;
                }
            }
        }
        void Clear(TreapNode<T>* &p){
            if(p == nullptr)
                return;
            Clear(p->left);
            Clear(p->right);
            delete p;
            p = nullptr;
        }
        std::string Pre_traverse(TreapNode<T> *p){
            if(p == nullptr)
                return "";
            else{
//                std::cout << p->val << ' ' << p->size << '\n';
                return std::to_string(p->val) + " " + Pre_traverse(p->left) + Pre_traverse(p->right);
            }

        }

    public:
        uint64_t start, end;
        uint64_t insert_total, remove_total, pre_element_total, suc_element_total, rank_total, kth_element_total, clear_total, pre_traverse_total, merge_total, split_total;
        uint64_t insert_num, remove_num, pre_element_num, suc_element_num, rank_num, kth_element_num, clear_num, pre_traverse_num, merge_num, split_num;
        Treap(){
            insert_total = remove_total = pre_element_total = suc_element_total = rank_total = kth_element_total = clear_total \
            = pre_traverse_total = merge_total = split_total = insert_num = remove_num = pre_element_num = suc_element_num = rank_num \
            = kth_element_num = clear_num = pre_traverse_num = merge_num = split_num = 0;
        }
//        int32_t Height(TreapNode<T> *root){
//            if(root == nullptr)
//                return 0;
//            return std::max(Height(root->left), Height(root->right)) + 1;
//        }
//        int32_t height(){
//            return Height(treap_root);
//        }
//        int32_t size(){
//            if(treap_root == nullptr)
//                return 0;
//            return treap_root->size;
//        }
        void insert(T val) {
            /* Your code here. */
            start = rdtsc();
            if (treap_root == nullptr) {
                treap_root = new TreapNode<T>(val, nullptr, nullptr, 1, 1, rand.treap_rand());
                end = rdtsc();
                insert_total += end - start;
                ++insert_num;
                return;
            }
            TreapNode<T> *p = treap_root, *q, *left = nullptr, *right = nullptr, *rl = nullptr, *lr = nullptr;
            // 初始化左右子树
            left = new TreapNode<T>;
            lr = left;
            right = new TreapNode<T>;
            rl = right;

            // 分裂
            uint64_t t1 = rdtsc();
            while (p != nullptr) {
                if (p->val > val) {
                    rl->left = p;
                    rl = p;
                    p = p->left;
                    rl->left = nullptr;
                    if(p != nullptr)
                        rl->size -= p->size;
                    q = right->left;
                    while (q != rl){
                        q->size += rl->size;
                        q = q->left;
                    }
                }
                else if (p->val <= val) {
                    lr->right = p;
                    lr = p;
                    p = p->right;
                    lr->right = nullptr;
                    if(p != nullptr)
                        lr->size -= p->size;
                    q = left->right;
                    while (q != lr){
                        q->size += lr->size;
                        q = q->right;
                    }
                }
            }
            uint64_t t2 = rdtsc();
            split_total += t2 - t1;
            ++split_num;

            // 插入
            if(lr->val == val){
                lr->count += 1;
                q = left->right;
                while (q != nullptr){
                    ++q->size;
                    q = q->right;
                }
            }
            else {
                p = new TreapNode<T>(val, nullptr, nullptr, 1, 1, rand.treap_rand());
                t1 = rdtsc();
                left->right = merge(left->right, p);
                t2 = rdtsc();
                merge_total += t2 - t1;
                ++merge_num;
            }
            // 连接左右子树
            t1 = rdtsc();
            treap_root = merge(left->right, right->left);
            t2 = rdtsc();
            merge_total += t2 - t1;
            ++merge_num;
            delete right;
            delete left;
            end = rdtsc();
            insert_total += end - start;
            ++insert_num;
        }

        void remove(T val) {
            /* Your code here. */
            uint64_t t1, t2;
            start = rdtsc();
            TreapNode<T> *p = treap_root, *q = p;
            while(p != nullptr){
                if(p->val < val){
                    q = p;
                    p = p->right;
                }
                else if(p->val > val){
                    q = p;
                    p = p->left;
                }
                else{
                    if(p->count == 1){
                        if(p == treap_root){
                            t1 = rdtsc();
                            treap_root = merge(p->left, p->right);
                            t2 = rdtsc();
                            merge_total += t2 - t1;
                            ++merge_num;
                            delete p;
                            break;
                        }
                        if(val < q->val){
                            t1 = rdtsc();
                            q->left = merge(p->left, p->right);
                            t2 = rdtsc();
                            merge_total += t2 - t1;
                            ++merge_num;
                        }
                        else{
                            t1 = rdtsc();
                            q->right = merge(p->left, p->right);
                            t2 = rdtsc();
                            merge_total += t2 - t1;
                            ++merge_num;
                        }
                        delete p;
                    }
                    else{
                        p->count -= 1;
                        p->size -= 1;
                    }
                    p = treap_root;
                    while(p != q){
                        if(p->val < val){
                            p->size -= 1;
                            p = p->right;
                        }
                        else if(p->val > val){
                            p->size -= 1;
                            p = p->left;
                        }
                    }
                    q->size -= 1;
                    break;
                }
            }
            end = rdtsc();
            remove_total += end - start;
            ++remove_num;
        }

        T pre_element(T val) {
            /* Your code here. */
            start = rdtsc();
            if(treap_root == nullptr){
                end = rdtsc();
                pre_element_total += end - start;
                ++pre_element_num;
                return -1;
            }
            TreapNode<T> *p = treap_root, *pre = nullptr;
            while(p != nullptr){
                if(p->val < val){
                    pre = p;
                    p = p->right;
                }
                else if(p->val > val){
                    p = p->left;
                }
                else {
                    if(p->left != nullptr){
                        pre = p->left;
                        while(pre->right != nullptr)
                            pre = pre->right;
                    }
                    break;
                }
            }
            end = rdtsc();
            pre_element_total += end - start;
            ++pre_element_num;
            if(pre != nullptr)
                return pre->val;
            return -1;
        }

        T suc_element(T val) {
            /* Your code here. */
            start = rdtsc();
            if(treap_root == nullptr){
                end = rdtsc();
                suc_element_total += end - start;
                ++suc_element_num;
                return -1;
            }
            TreapNode<T> *p = treap_root, *suc = nullptr;
            while(p != nullptr){
                if(p->val > val){
                    suc = p;
                    p = p->left;
                }
                else if(p->val < val){
                    p = p->right;
                }
                else {
                    if(p->right != nullptr){
                        suc = p->right;
                        while(suc->left != nullptr)
                            suc = suc->left;
                    }
                    break;
                }
            }
            end = rdtsc();
            suc_element_total += end - start;
            ++suc_element_num;
            if(suc != nullptr)
                return suc->val;
            return -1;
        }

        int32_t rank(T val) {
            /* Your code here. */
            start = rdtsc();
            int32_t rank = 0;
            TreapNode<T> *p = treap_root;
            while(p != nullptr){
                if(p->val < val){
                    rank += p->size - p->right->size;
                    p = p->right;
                }
                else if(p->val > val){
                    p = p->left;
                }
                else{
                    if(p->left != nullptr)
                        rank += p->left->size + 1;
                    else
                        rank += 1;
                    end = rdtsc();
                    rank_total += end - start;
                    ++rank_num;
                    return rank;
                }
            }
            end = rdtsc();
            rank_total += end - start;
            ++rank_num;
            return -1;
        }

        int32_t kth_element(int32_t rk) {
            /* Your code here. */
            start = rdtsc();
            if(treap_root == nullptr){
                end = rdtsc();
                kth_element_total += end - start;
                ++kth_element_num;
                return -1;
            }
            if(rk > treap_root->size){
                end = rdtsc();
                kth_element_total += end - start;
                ++kth_element_num;
                return -1;
            }
            TreapNode<T> *p = treap_root;
            int32_t th = p->size;
            while(p != nullptr){
                if(p->right != nullptr){
                    th = th - p->right->size;
                }
                if(th > rk){
                    if(th - p->count < rk){
                        end = rdtsc();
                        kth_element_total += end - start;
                        ++kth_element_num;
                        return p->val;
                    }
                    p = p->left;
                    th -= 1;
                }
                else if(th < rk){
                    p = p->right;
                    th += p->size;
                }
                else{
                    end = rdtsc();
                    kth_element_total += end - start;
                    ++kth_element_num;
                    return p->val;
                }
            }
            return -1;
        }

        void clear() {
            /* Your code here. */
            start = rdtsc();
            rand.reset();
            Clear(treap_root);
            end = rdtsc();
            clear_total += end - start;
            ++clear_num;
        }

        std::string pre_traverse() {
            /* Your code here. */
            start = rdtsc();
            if(treap_root == nullptr){
                end = rdtsc();
                pre_traverse_total += end - start;
                ++pre_traverse_num;
                return "empty";
            }
            std::string s = Pre_traverse(treap_root);
            end = rdtsc();
            pre_traverse_total += end - start;
            ++pre_traverse_num;
            return s;
        }
};
