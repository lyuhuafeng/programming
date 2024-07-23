#include <unordered_map>
#include <string>
#include <mutex> // lock_guard
#include <shared_mutex> // shared_lock, shard_mutex
using namespace std;

    class dns_entry {};

    class dns_cache {
    public:
        typedef unordered_map<string, dns_entry> dns_map;

    private:
        dns_map entries_;
        mutable shared_mutex mtx_;

    public:
        dns_entry find_entry(const string& domain) const {
            shared_lock<shared_mutex> slock(mtx_);
            const dns_map::const_iterator it = entries_.find(domain);
            return (it != entries_.end()) ? it->second : dns_entry();
        }
        void update_one_entry(const string& domain, const dns_entry& entry) {
            lock_guard<shared_mutex> guard(mtx_);
            entries_[domain] = entry;
        }
    };

int main() {}
