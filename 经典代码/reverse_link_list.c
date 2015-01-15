
//单链表逆置算法（迭代）

list reverse_list(list l)
{
    list pre = l;     //核心思想：断开向后的链接，改指前一个元素
    list cur = l->link;
    list temp = NULL;   //用temp暂存断开的向后链接

    while (cur != NULL)
    {
        temp = cur->link;     //暂存后面的链表，否则断链
        cur->link = pre;     //后指前！
        pre = cur;          //三个指针整体向后移
        cur = temp;
    }

    l->link = NULL; //首元素未断开与第二元素的链接（仅操作了第二指向第一）
    return cur;
}



//递归算法(太精妙！)


list reverse_list(list head)
{
    if (NULL == head || head->next == NULL) 
        return head;              //最后一个节点会返回，层层传递

    list newHead = reverse_list(head->next);     //head->next 表示剩下的部分

    head->next->next = head;        //建立逆向链接
    head->next = NULL;              //断开原来链接
    return newHead;
}