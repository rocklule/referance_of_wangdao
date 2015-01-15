

//两个升序单链表合成一个

list merge_list(list l1, list l2)
{
    list head, rear, p, q, minor;

    head = (l1->data < l2->data) ? l1 : l2;
    rear = head;
    p = head->link;
    q = (l1->data >= l2->data) ? l1 : l2;  //较大者

    while(q!=NULL && p!=NULL)
    {
        minor = (p->data < q->data) ? p : q;
        rear->link = minor;
        rear = minor;
        (minor == p) ? (p = p->link) : (q = q->link);
    }

    (q!=NULL) ? (rear->link = q) : (rear->link = p);

    return head;
}