template<typename T>
class forwardList
{
private:
    /**
     * class Node
     * @tparam X
     */
    template<typename X>
    class Node
    {
    public:
        X value;
        Node * next;
        Node () : value() , next( nullptr ){};
        //https://www.scaler.com/topics/cpp-explicit/
        explicit Node ( X & val ) : value ( val ) , next ( nullptr ) { } ;
    };
    Node < T > * head , tail ;
    unsigned int dimension = 0 ;
public:

    class Iterator
    {
        Node < T > * node ;
    public:
        Iterator ( ) : node( nullptr ) { } ;
        explicit Iterator( Node < T > * p ) : node ( p ) { } ;
        void nextOne();
        void advance(unsigned int howMany);

    };
    forwardList () : head (  ) , tail(  ) , dimension(0) { } ;
    forwardList ( const forwardList < T >  & origin) ;
    forwardList < T >  & operator = ( const forwardList < T > & origin ) ;
    forwardList < T >  operator + ( const forwardList < T > & origin ) ;
    T & begin () { return this -> head -> value ; } ;
    T & end () { return this -> tail -> value ; } ;
    void push_front ( T & data );
    void push_back ( T & data );
    void pop_front ();
    void pop_back ();
    void pop ( Iterator & i ) ;
    unsigned int size(){return this->dimension;};
    forwardList<T> concat( const forwardList < T > & l ) ;
    ~forwardList();
    Iterator iterador();
};

template<typename T>
forwardList<T> forwardList<T>::operator+(const forwardList<T> &origin) {
    forwardList<T> ret;
    Node<T>*p = this->head;
    Node<T>*q = origin.head;
    Node<T>*n=ret.head;
    Node<T>*n1= ret.head->next;
    while(p)
    {
        //creo el nuevo nodo de la lista de retorno
        n = new Node<T>(p->value);
        n->next=n1;
        n1=n->next;
        
        p=p->next;
    }

}

template<typename T>
forwardList<T> &forwardList<T>::operator=(const forwardList<T> &origin) {
    if(&origin!=this)
    {
        Node<T>*dis = this->head;
        Node<T>*p = dis->next;
        while(!p)
        {
            delete dis;
            dis = p;
            p=p->next;
        }
        delete dis;
    }
    return *this;
}

/**
 *
 * @tparam T como
 */
template<typename T>
void forwardList<T>::Iterator::nextOne()
{
    this->node=node->next;
}

template<typename T>
forwardList<T>::forwardList(const forwardList<T> & origin)
{
    if(origin.size()==0)//lista de entrada vacía
    {
        this->head = this->tail = nullptr ;
        this->dimension = 0 ;
        return;
    }
    //else
    Node<T>*p = origin.head;
    Node<T>*q = this->head;
    Node<T>*a = this->head;
    while (p)
    {

        q = new Node<T>(p->value);
        if(q!=head)
        {
            a->next=q;
            a = q;
        }
        q=q->next;
        p=p->next;
    }
}

template<typename T>
forwardList<T>::Iterator forwardList<T>::iterador()
{
    return Iterator(this->head);
}

template<typename T>
forwardList<T>::~forwardList()
{
    Node<T>*dis = this->head;
    Node<T>*p = dis->next;
    while(!p)
    {
        delete dis;
        dis = p;
        p=p->next;
    }
    delete dis;
}
