#ifndef _MUTEX_H
#define _MUTEX_H

class mutex {
public:
    mutex();
    ~mutex();

    void lock();
    void unlock();

    class impl;                                 // defined by the thread library
    impl *impl_ptr;                             // used by the thread library

    /*
     * Disable the default copy constructor and copy assignment operator.
     */
    mutex(const mutex&) = delete;
    mutex& operator=(const mutex&) = delete;
    mutex(mutex&&) = delete;
    mutex& operator=(mutex&&) = delete;
};

#endif /* _MUTEX_H */
