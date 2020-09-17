struct Thread {
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(void (*fn)());

    static void entry(void* obj);

    // private:
    void* mStackPtr;
    void (*mUserFn)();
};

void yield_to(const Thread& t);
void yield_from(Thread& t);
