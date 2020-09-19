#include <memory>
#include <vector>

struct Executor;

struct Thread {
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread();
    virtual ~Thread() {}

    virtual void threadFn() = 0;

  protected:
    void yield();

  private:
    static void entry(void* obj);
    void* mStackPtr;

    friend struct Executor;
    const Executor* mExecutor;
};


struct Executor {
    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;
    Executor() = default;

    const void* getStackPtr() const { return mStackPtr; }

    void spawn(std::unique_ptr<Thread> t) {
        mThreads.push_back(std::move(t));
        mThreads.back()->mExecutor = this;
    }
    void run() {
        for (const std::unique_ptr<Thread>& t : mThreads) {
            yield_to(t.get());
        }
    }

  private:
    void* mStackPtr;
    std::vector<std::unique_ptr<Thread>> mThreads;

    void yield_to(const Thread* t) const;
};
