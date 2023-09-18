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
    private:
        X value;
        Node * next;
    public:
        Node () : value() , next( nullptr ){};
        explicit Node ( Node < T >  & n ) : value(),next ( n ) { } ;
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
    forwardList () : head ( nullptr ) , tail( nullptr ) { } ;
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
