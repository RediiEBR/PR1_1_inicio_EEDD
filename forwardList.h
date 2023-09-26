/**
 * @brief definition for the forwardList, linked list with the next pointer as a way of iterate through the list
 * @author josemanuelmartin.fuentezuelas@gmail.com
*/
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
        /**
         * @brief as the default node constructor
         * the value is set as the default X datatype constructor and the next value is set to nullptr
        */
        Node () : value() , next( nullptr ){};
        //https://www.scaler.com/topics/cpp-explicit/
        /**
         * @brief given X as a value, the node will create with not a next Node to point at
        */
        explicit Node ( X & val ) : value ( val ) , next ( nullptr ) {} ;
    };
    Node < T > * head , tail ;
    unsigned int dimension = 0 ;
public:
    /**
     * @brief class Iterator
    */
    class Iterator
    {
    private:
        Node < T > * node ;
    public:
        /**
         * @brief default iterator constructor
        */
        Iterator (  ) : node( nullptr ) { } ;
        /**
         * @brief Node constructor given a node
        */
        explicit Iterator( Node < T > * p ) : node ( p ) { } ;
        /**
         * @brief nextOne function that makes the iterator go forward once
        */
        void nextOne();
        /**
         * @brief advance function that makes the iterator go forward a given number of times.
        */
        void advance(unsigned int howMany);

    };
    /**
     * @brief default forwardList constructor
    */
    forwardList () : head ( nullptr ) , tail( nullptr ) , dimension(0) { } ;
    /**
     * @brief copy constructor created to the forwardList
    */
    forwardList ( const forwardList < T >  & origin) ;
    /**
     * @brief assignment operator overwrite for this container
    */
    forwardList < T >  & operator = ( const forwardList < T > & origin ) ;
    /**
     * @brief plus operator made for this container
    */
    forwardList < T >  operator + ( const forwardList < T > & origin ) ;
    /**
     * @return the first element of this list
    */
    T & begin () { return this -> head -> value ; } ;
    /**
     * @return the last element of the list
    */
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
void forwardList<T>::push_back(T & data)
{
    Node<T>*newOne(data);//created the new node
    this->tail->next=newOne;//Next one to tail is new tail
    this->tail=newOne;//tail is the new element, but it's next one pointer is aiming to itself
    this->tail->next = nullptr;//by definition, a forwardList's tail element has no pointer to next element, so be it
}
template<typename T>
void forwardList<T>::push_front(T&data)
{
    Node<T>*newOne(data);//create the new node
    newOne->next=this->head;//next node of the new node is the current head
    this->head=newOne;//head is now the new node
}
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
