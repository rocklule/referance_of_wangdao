#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_ 

//继承Noncopyable的类对象，均失去了值语义
class NonCopyable
{
    public:
        NonCopyable() {}
        ~NonCopyable() {}
    private:
        NonCopyable(const NonCopyable &);
        void operator=(const NonCopyable &);
};

#endif  /*NONCOPYABLE_H_*/
