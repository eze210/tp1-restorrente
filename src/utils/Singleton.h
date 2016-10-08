#ifndef SINGLETON_
#define SINGLETON_

template<typename T>
class Singleton {
private:
    /* copy constructor is private */
    Singleton(const Singleton &);

    Singleton &operator=(const Singleton &);

    Singleton() { }

public:
    static T &instance() {
        /* static instance of T (in the process' data segment) */
        static T object;
        return object;
    }

    ~Singleton() { }
};

#endif
