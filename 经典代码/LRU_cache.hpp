//
//  cache.hpp
//  cache2
//
//  Created by Ruler on 14-8-13.
//  Copyright (c) 2014年 Ruler. All rights reserved.
//

#ifndef cache2_cache_hpp
#define cache2_cache_hpp

#include <unordered_map>
#include <set>

template <typename KEY, typename DATA>
class CachePool;


template <typename KEY, typename DATA>          //注意数据都是set，可以统一操作（存盘，多值等）
struct Item{
    KEY key;
    std::set<DATA> data;
    Item<KEY, DATA>* front;
    Item<KEY, DATA>* next;
};


template <typename KEY, typename DATA>
class Cache
{
    friend class CachePool<KEY, DATA>;
private:
    std::unordered_map<KEY, Item<KEY, DATA>*> map_;
    Item<KEY, DATA>* head_;
    Item<KEY, DATA>* rear_;
    void shift_to_front(Item<KEY, DATA>*);      //LRU替换策略的核心
    
public:
    Cache(uint32_t vol);
    ~Cache();
    
    void put(KEY key, std::set<DATA> data);
    std::set<DATA> get(KEY key);            //这个非引用返回值降低了效率，有办法解决吗？
    
};


template <typename KEY, typename DATA>
inline Cache<KEY, DATA>::Cache(uint32_t vol)    //vol－容量
{
    head_ = new Item<KEY, DATA>;                //等下可以测试一下不要头节点得版本？
    head_->front = head_->next = NULL;
    rear_ = head_;
    
    for (size_t i = 0 ; i < vol; ++i) {        //预分配vol个cache节点，提高使用速度
        auto p_temp = new Item<KEY, DATA>;
        rear_->next = p_temp;
        p_temp->front = rear_;
        rear_ = p_temp;
    }
    
    rear_->next = new Item<KEY, DATA>;      //真正得尾巴
    rear_->next->front = rear_;
    rear_ = rear_->next;
}


template <typename KEY, typename DATA>
inline void Cache<KEY, DATA>::shift_to_front(Item<KEY, DATA>* p_item)
{
    p_item->front->next = p_item->next;
    p_item->next->front = p_item->front;
    
    p_item->next = head_->next;
    p_item->front = head_;
    head_->next = p_item;
    p_item->next->front = p_item;
}

template <typename KEY, typename DATA>
inline void Cache<KEY, DATA>::put(KEY key, std::set<DATA> data)
{
    auto p_last_item = rear_->front;       //减少二次引用的次数
    
    map_.erase(p_last_item->key);       //删掉索引
    
    p_last_item->data = data;
    p_last_item->key = key;
    shift_to_front(p_last_item);
    
    map_.insert(std::pair<KEY, Item<KEY, DATA>*>(key, p_last_item));    //建立索引
}


template <typename KEY, typename DATA>
inline std::set<DATA> Cache<KEY, DATA>::get(KEY key)
{
    auto it = map_.find(key);
    if (it == map_.end())
        return std::set<DATA>();
    shift_to_front(it->second);
    return it->second->data;
}


template <typename KEY, typename DATA>
inline Cache<KEY, DATA>::~Cache()
{
    auto pre = head_;
    auto cur = head_->next;
    while (cur != NULL){
        delete pre;
        pre = cur;
        cur = cur->next;
    }
    delete pre;
}



#endif
