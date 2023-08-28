#include <iostream>
template<typename X>
class Node
{
private:
    X value;
    Node<X> * next;
public:
    Node():value(),next(nullptr){};
    Node(const X & valueN):value(valueN),next(nullptr){};
    Node(const X & valueN, const Node<X>& nNode):value(valueN),next(nNode){}
    Node(const Node & original):value(original.value),next(original.next()){}
    Node & operator=(const Node original)
    {
        this->value = original.value;
        this->next = original.next;
    }
    bool hasNext(){return next!=nullptr;}
    bool hasData(X&data);
    
};

template<typename X>
bool Node<X>::hasData(X &data)
{
    return this->value!=X();
}

template<typename T>
class forwardList
{
private:
    Node<T> * head = nullptr;
    Node<T> * tail = nullptr;
    int size=0;    
public:
    class Iterator
    {
    private:
        Node<T>*init;

    public:
        Iterator(Node<T>*node):init(node){};
        void forward()
        {
            if(init->hasNext())
            {
                init=init->next;
                return;
            }
            throw std::out_of_range("No se puede avanzar");
        };
        T&get(){return init->value;};
        bool hasNext(){return init->hasNext();}
    };
    
    Iterator begin(){return Iterator(head);};
    Iterator end(){return Iterator(tail);};
    forwardList():head(nullptr),tail(nullptr){};
    forwardList(const forwardList<T> & original);
    ~forwardList();
    void push_back(T & data);
    void locate(T & data, unsigned int pos);
    void eraseLocation(unsigned int pos);
    void erase(T&data);
    void eraseOcurrences(T&data);
};

template<typename T>
forwardList<T>::~forwardList()
{
    if(this->head!= nullptr)
    {
        Node<T>* p = this->head;
        Node<T>* target=p->next;
        while(target!=nullptr)
        {
            delete p;
            p=target;
            target=target->next;
        }
    }

}

template<typename T>
forwardList<T>::forwardList(const forwardList<T> &original)
{
    Node<T>*p = this->head;
    Node<T>*q = original.head;
    while(q!=nullptr)
    {
        p = new Node<T>(q->value);
        p = p->next;
        q=q->next;
    }
    this->tail=p;
}

template<typename T>
void forwardList<T>::push_back(T&data)
{
    Node<T>*p = this->tail;
    auto *n = new Node<T>(data);
    p->next = n;
    this->tail=n;
    this->tail->next = nullptr;//la cola no tiene sentido que tenga next
}

template<typename T>
void forwardList<T>::locate(T&data, unsigned int pos)
{
    Node<T>*p = this->head;
    while(pos!=0 && p->hasNext())
    {
        pos--;
        p=p->next;

    }
    if(pos!=0)//ha pedido una ubicación mayor que el tamaño de la lista
        throw std::out_of_range("out of range");
    auto * n = new Node<T>(data);
    if(p->hasNext())
        n->next = p->next;
    else
        this->tail = n;
    p->next = n;
}

template < typename T >
void forwardList<T>::eraseLocation(unsigned int pos)
{
    Node<T>*p = this->head;
    while(pos!=1 && p->hasNext())
    {
        pos--;
        p=p->next;

    }
    if(pos!=1)//ha pedido una ubicación mayor que el tamaño de la lista
        throw std::out_of_range("out of range");
    if( p->next == this->tail)
        this->tail=p;
    p=p->next;
    delete p;
}

template < typename T >
void forwardList<T>::erase(T&data)
{
    Node<T>*p = this-> head;
    Node<T>*target = this->head;
    if(this->head == this->tail)
    {
        if(p->value == data)//solo hay un dato aqui
        {
            delete p;
            this->head = this -> tail = nullptr;
            return;
            
        }
    }
    if(this->head->value==data)
    {
        this->head=this->head->next;
        delete p;
        return;
    }
    while (p)
    {
        if(p->next && p->next->value == data)
        {
            target = p->next;
            
            if(target->hasNext())//tiene nodos detras
            {
                p->next = target->next;
                delete target;
                return;
            }
            else//target es la cola
            {
                this->tail = p;
                delete target;
                return;
            }

        }
        p=p->next;
    }
    
}
template<typename T>
void forwardList<T>::eraseOcurrences(T&data)
{
    Node<T>*p = this-> head;
    Node<T>*target = this->head;
    if(this->head == this->tail)
    {
        if(p->value == data)//solo hay un dato aqui
        {
            delete p;
            this->head = this -> tail = nullptr;
            return;
            
        }
    }
    if(this->head->value==data)
    {
        this->head=this->head->next;
        delete p;
        p = target;
        if(p->hasNext()) p=p->next;
    }
    while (p)
    {
        if(p->next && p->next->value == data)
        {
            target = p->next;
            
            if(target->hasNext())//tiene nodos detras
            {
                p->next = target->next;
                delete target;
                return;
            }
            else//target es la cola
            {
                this->tail = p;
                delete target;
                return;
            }
            
        }
    }
}