#ifndef PTR_VECTOR_H
#define PTR_VECTOR_H 

#include "NonCopyable.h"
#include <vector>

template <typename T>
class PtrVector : public std::vector<T*>,
                  private NonCopyable
{
    public:
        ~PtrVector()
        {
            clear();
        }
        void push_back(T *val)
        {
            std::vector<T*>::push_back(val);
        }
        void clear()
        {
            typename std::vector<T*>::iterator it;
            for(it = std::vector<T*>::begin(); it != std::vector<T*>::end(); ++it)
            {
                delete *it;  // *it指的是 T*
            }
            //调用基类的clear，真正释放元素
            std::vector<T*>::clear(); 
        }
};




#endif  /*PTR_VECTOR_H*/
