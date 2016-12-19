#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "exceptions/badindex.h"

#include <list>
#include <utility>
#include "commons/pair_hash.h"

template <typename Key, typename Value>
class Hashtable
{
public:

    friend class iterator;
    class Node;

    Hashtable(unsigned predictedSize);
    virtual ~Hashtable();

    Value& operator[] (const Key& key);
    const Value& operator[] (const Key& key) const;

private:

    std::hash<Key> _hash;

    /*
     * Private _Node definition
     * */
    struct _Node {
        Key _key;
        Value _value;
        bool _is_sentinel;

        _Node* _previous;
        _Node* _next;
        Node* _public;

        _Node(bool sentinel = false) :
            _is_sentinel(sentinel),
            _previous(NULL),
            _next(NULL),
            _public(NULL)
        {
        }

        _Node(Key key, Value value) :
            _key(key),
            _value(value),
            _is_sentinel(false),
            _previous(NULL),
            _next(NULL)
        {
            this->_public = new Node(this->_key, this->_value);
        }

        ~_Node()
        {
            if (this->_public != NULL)
            {
                delete this->_public;
                this->_public = NULL;
            }
            this->_previous = NULL;
            this->_next = NULL;
        }
    };

    /*
     * Private _Chain definition
     * */
    struct _Chain {
        std::list<Hashtable<Key, Value>::_Node*> _nodes;
        unsigned _index;

        _Chain(unsigned index) :
            _index(index)
        {
            this->_nodes.push_back((new _Node(true)));
        }

        ~_Chain()
        {
            for(auto&& node : this->_nodes)
            {
                delete node;
            }
        }
    };

    /*
     * Private fields
     *
     * */

    unsigned _size;
    std::vector<Hashtable<Key, Value>::_Chain*> _container;
    unsigned _max;
    Hashtable<Key, Value>::_Node* _begin;
    Hashtable<Key, Value>::_Node* _end;

public:

    /*
     * Public Node definition
     * */
    struct Node
    {
        Key first;
        Value second;

        Node(Key aKey, Value aValue) :
            first(aKey),
            second(aValue)
        {
        }
    };

    /*
     * Public iterator definition
     * */
    class iterator
    {
    private:
        Hashtable<Key, Value>::_Node* _current;
        Hashtable<Key, Value>* _parent;

    public:

        friend class Hashtable<Key, Value>;

        iterator() { this->_current = NULL; this->_parent = NULL; }
        iterator(const iterator& another)
        {
            this->_current = another._current;
            this->_parent = another._parent;
        }
        ~iterator()
        {
            this->_current = NULL;
            this->_parent = NULL;
        }

        iterator& operator =(const iterator& another);
        iterator& operator++();
        iterator operator ++(int);
        iterator& operator --();
        iterator operator --(int);
        bool operator ==(const iterator& another);
        bool operator !=(const iterator& another);
        Hashtable<Key, Value>::Node* operator ->();
    };

    /*
     * Public methods
     *
     * */

    const Value& at(const Key& key) const;
    Hashtable<Key, Value>::iterator begin();
    bool contains(const Key& key) const;
    Hashtable<Key, Value>::iterator end();
    iterator find(const Key& key) const throw(BadIndex);
    void insert(const std::pair<Key, Value>& pair);
    void insert(const Key& key, const Value& value);
    Value remove(const Key& key);
    unsigned size() const;


private:

    /*
     * Private methods
     * */

    void insert_internal(_Node* node);
    Hashtable<Key, Value>::_Node* get_internal(const Key& key) const;

};

template <typename Key, typename Value>
Hashtable<Key, Value>::Hashtable(unsigned predictedSize) :
    _size(0),
    _max(predictedSize),
    _begin(NULL),
    _end(NULL)
{
    _Node *tmp = NULL, *node = NULL;

    for(unsigned i = 0; i < this->_max; i++)
    {
        this->_container.push_back(new _Chain(i));
        node = *(this->_container[i]->_nodes.begin());
        node->_previous = tmp;
        if (tmp != NULL)
            tmp->_next = node;
        tmp = node;
    }

    tmp->_next = NULL;
    this->_end = tmp;
}

template <typename Key, typename Value>
Hashtable<Key, Value>::~Hashtable()
{
    for(auto&& chain : this->_container)
    {
        delete chain;
    }
}

template <typename Key, typename Value>
Value &Hashtable<Key, Value>::operator[](const Key &key)
{
    _Node* node = this->get_internal(key);
    if (node == NULL)
    {
        node = new _Node();
        node->_key = key;
        this->insert_internal(node);
    }

    return node->_value;
}

template <typename Key, typename Value>
const Value &Hashtable<Key, Value>::operator[](const Key &key) const
{
    this->at(key);
}

template <typename Key, typename Value>
const Value &Hashtable<Key, Value>::at(const Key &key) const
{
    _Node* node = this->get_internal(key);
    if(node == NULL)
        throw BadIndex("No key stored in table", __FILE__, __LINE__);

    return node->_value;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator Hashtable<Key, Value>::begin()
{
    iterator it;
    it._parent = this;
    it._current = this->_begin;

    return it;
}

template <typename Key, typename Value>
bool Hashtable<Key, Value>::contains(const Key &key) const
{
    return this->get_internal(key) != NULL;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator Hashtable<Key, Value>::end()
{
    iterator it;
    it._parent = this;
    it._current = this->_end;

    return it;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator Hashtable<Key, Value>::find(const Key &key) const throw(BadIndex)
{
    iterator it = new iterator();
    it._parent = this;
    _Node* node = this->get_internal(key);
    it._current = node;

    return it;
}

template <typename Key, typename Value>
void Hashtable<Key, Value>::insert(const std::pair<Key, Value> &pair)
{
    _Node* node = new _Node(pair.first, pair.second);
    this->insert_internal(node);
}

template <typename Key, typename Value>
void Hashtable<Key, Value>::insert(const Key &key, const Value &value)
{
    _Node* node = new _Node(key, value);
    this->insert_internal(node);
}

template <typename Key, typename Value>
Value Hashtable<Key, Value>::remove(const Key &key)
{
    _Node* node = this->get_internal(key);
    if (node == NULL)
        throw BadIndex("No such key to remove an item", __FILE__, __LINE__);

    if (node->_previous != NULL)
        node->_previous->_next = node->_next;
    else
        this->_begin = node->_next;

    if (node->_next != NULL)
        node->_next->_previous = node->_previous;
    else
        this->_end = node->_previous;

    this->_size = this->_size - 1;

    Value v = node->_value;
    delete node;
    return v;
}

template <typename Key, typename Value>
unsigned Hashtable<Key, Value>::size() const
{
    return this->_size;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator &Hashtable<Key, Value>::iterator::operator =(const Hashtable<Key, Value>::iterator &another)
{
    if (this == &another)
        return * this;
    this->_current = another._current;
    return * this;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator &Hashtable<Key, Value>::iterator::operator++()
{
    if (this->_current->_next != NULL && this->_current != this->_parent->_end)
    {
        this->_current = this->_current->_next;
        while(this->_current->_is_sentinel && this->_current->_next != NULL)
            this->_current = this->_current->_next;
    }
    else
        throw BadIndex("Cannot use ++ operator on last item.", __FILE__, __LINE__);

    return *this;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator Hashtable<Key, Value>::iterator::operator ++(int)
{
    iterator i(*this);
    operator ++();
    return i;

}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator &Hashtable<Key, Value>::iterator::operator --()
{
    if (this->_current->_previous != NULL && this->_current != this->_parent->_begin)
    {
        this->_current = this->_current->_previous;
        while(this->_current->_is_sentinel && this->_current->_previous != NULL)
            this->_current = this->_current->_previous;
    }
    else
        throw BadIndex("Cannot use -- operator on first item.", __FILE__, __LINE__);

    return *this;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::iterator Hashtable<Key, Value>::iterator::operator --(int)
{
    iterator i(*this);
    operator --();
    return i;
}

template <typename Key, typename Value>
bool Hashtable<Key, Value>::iterator::operator ==(const iterator& another)
{
    return this->_current == another._current;
}

template <typename Key, typename Value>
bool Hashtable<Key, Value>::iterator::operator !=(const iterator& another)
{
    return this->_current != another._current;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::Node* Hashtable<Key, Value>::iterator::operator ->()
{
    return this->_current->_public;
}

template <typename Key, typename Value>
void Hashtable<Key, Value>::insert_internal(_Node *node)
{
    unsigned index = this->_hash(node->_key);
    _Node* firstInChain = *(this->_container[index]->_nodes.begin());
    node->_next = firstInChain;
    node->_next = firstInChain->_previous;
    this->_container[index]->_nodes.push_front(node);

    if (firstInChain->_previous != NULL)
        firstInChain->_previous->_next = node;
    else
        node->_previous = NULL;

    if (this->_size == 0)
    {
        this->_begin = node;
    }
    else
    {
        unsigned begIndex = this->_hash(this->_begin->_key);
        unsigned endIndex = this->_hash(this->_end->_key);
        if (begIndex >= index)
            this->_begin = node;
        if (endIndex < index)
            this->_end = node;
    }

    this->_size = this->_size + 1;
}

template <typename Key, typename Value>
typename Hashtable<Key, Value>::_Node *Hashtable<Key, Value>::get_internal(const Key &key) const
{
    unsigned index = this->_hash(key) % this->_max;
    if(this->_container[index]->_nodes.size() > 0)
    {
        for(auto ii : this->_container[index]->_nodes)
        {
            if(ii->_key == key && !ii->_is_sentinel)
                return ii;
        }
    }

    return NULL;
}

#endif // HASHTABLE_H

