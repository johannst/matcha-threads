struct Thread {
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread();

    virtual void threadFn() = 0;

    // use from executor
    void yield_to() const;

  protected:
    // use in thread
    void yield();

  private:
    static void entry(void* obj);
    void* mStackPtr;
};
