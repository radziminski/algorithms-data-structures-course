#ifndef RING_H
#define RING_H
#include <iostream>
#include <stdexcept>

template <typename Key, typename Info>
class Ring
{
    private:    //class data
        struct Node
        {
            Info Data;
            Key ID;
            Node *next;
            Node *prev;
        };
        Node *any;
        int ring_size;

        template <typename K, typename I>
        friend std::ostream& operator<<(std::ostream& os, const Ring<K, I>& seq);

    public:
        //Constructors
        Ring<Key, Info>():any(nullptr), ring_size(0) {};
        ~Ring<Key, Info>();
        Ring<Key, Info>(const Ring<Key, Info>& source);

        //Operators:
        Ring<Key, Info>& operator=(const Ring<Key, Info>& source);
        Ring<Key, Info> operator+(const Ring<Key, Info>& source) const;
        Ring<Key, Info>& operator+=(const Ring<Key, Info>& source)
        {
            *this = *this + source;
            return *this;
        }

        //Logic and compare operators
        bool operator==(const Ring<Key, Info>& source) const;
        bool operator!=(const Ring<Key, Info>& source) const
        {
            return !(*this==source);
        }
        bool operator>(const Ring<Key, Info>& source) const
        {
            if(this->ring_size>source.ring_size) return true;
            else return false;
        }
        bool operator>=(const Ring<Key, Info>& source) const
        {
            if(this->ring_size>=source.ring_size) return true;
            else return false;
        }
        bool operator<(const Ring<Key, Info>& source) const
        {
            if(this->ring_size<source.ring_size) return true;
            else return false;
        }
        bool operator<=(const Ring<Key, Info>& source) const
        {
            if(this->ring_size<=source.ring_size) return true;
            else return false;
        }

        //Node Add Methods
        //note: I'm passing all values as const (unchangable) referance to the value so program won't make unnecesary copy of the values
        void Push(const Key &ID, const Info &Data);
        bool Add_After_Key (const Key &ID, const Info &Data, const Key &after_key);
        bool Add_Before_Key (const Key &ID, const Info &Data, const Key &bef_key);

        //Node Remove Methods
        bool Remove_By_Key (const Key &rem_key);                    //removes one node with given key
        int Remove_All_By_Key (const Key &rem_key);                    //removes all nodes with given key and returns number of deleted nodes
        void Clear();

        //Ring modifiers
        void Reverse_Ring();

        //Ring Info
        bool Is_Empty() const
        {
            return (any==nullptr);
        }
        int Ring_Length() const
        {
            return ring_size;
        }


        //Data Acces
        Info &Get_Info(const Key &nkey);
        Info &Any_Info();
        Key &Any_Key();

        const Info &Get_Info(const Key &nkey) const;
        const Info &Any_Info() const;
        const Key &Any_Key() const;


        //Displaying the list
        void Print_By_Key(const Key &k) const                      //Prints all nodes with given key
        {
            if(!any) return;
            Node *temp=any;
            std::cout<<"Printing Ring by Key:\n\n";
            do
            {
                if(temp->ID==k) this->Print_Node(temp);
                temp=temp->next;
            } while(temp!=any);
        }

        //Iterators
        class Iterator;
        Iterator ibegin() const
        {
            Iterator it(any);
            return it;
        }
        const Iterator const_ibegin() const
        {
            Iterator it(any);
            return it;
        }
        Iterator iend() const
        {
            if(!any)
            {
                Iterator it(nullptr);
                return it;
            }
            Iterator it(any->prev);
            return it;
        }
        const Iterator const_iend() const
        {
            if(!any)
            {
                Iterator it(nullptr);
                return it;
            }
            Iterator it(any->prev);
            return it;
        }

private: //private methods
            //Displaying the list functions with nodes used in public display methods
        void Print_Node(Node *curr) const;
        void Print_Node(Node *curr, int num) const;
        void Print_Ring() const;

};

// Class ITERATOR                                                                                                               ---ITERATORS----

template <typename Key, typename Info>
class Ring<Key, Info>::Iterator
{
    friend class Ring<Key, Info>;
    private:
        Node *current;

    public:
        Iterator():current(nullptr){};
        ~Iterator(){current=nullptr;};
        Iterator(const Iterator& other)
        {
            this->current=other.current;
        };

        Iterator& operator=(const Iterator& other)
        {
            this->current=other.current;
            return *this;
        }
        bool operator==(const Iterator& source) const
        {
            if(this->current==source.current) return true;
            return false;
        }
        bool operator!=(const Iterator& source) const
        {
            return !(*this==source);
        }
        Iterator &operator++()
        {
            if(current) current=current->next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator it(*this);
            ++(*this);
            return it;
        }

        Iterator &operator--()
        {
            if(current) current=current->prev;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator it(*this);
            --(*this);
            return it;
        }

        Iterator operator+(int rhs)
        {
            if(!current) return *this;
            Iterator it(current);
            for (int i=0; i<rhs; i++) it.current=it.current->next;
            return it;
        }
        Iterator operator-(int rhs)
        {
            if(!current) return *this;
            Iterator it(current);
            for (int i=0; i<rhs; i++) it.current=it.current->prev;
            return it;
        }

        Key &Show_Key()
        {
            if(current) return current->ID;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return key." );
        }

        Info &Show_Info()
        {
            if(current) return current->Data;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return key." );
        }

        const Key &Show_Key() const
        {
            if(current) return current->ID;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return key." );
        }

        const Info &Show_Info() const
        {
            if(current) return current->Data;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return key." );
        }

        private:
        Iterator(Node *ptr):current(ptr){};

};


// ===Class Ring Methods===

//Add Methods   --------------------------------------------------------------------------------------------------------------------------====ADD METHODS====

template <typename Key, typename Info>
void Ring<Key, Info>::Push(const Key &ID, const Info &Data)
{
    Node *new_node = new Node();
    new_node->ID=ID;
    new_node->Data=Data;
    if(!any)
    {
        new_node->next=new_node;
        new_node->prev=new_node;
        any=new_node;
        ring_size++;
        return;
    }
    new_node->next=any->prev->next;
    new_node->prev=any->prev;
    any->prev->next=new_node;
    any->prev=new_node;
    ring_size++;


}


template <typename Key, typename Info>
bool Ring<Key, Info>::Add_After_Key(const Key &ID, const Info &Data, const Key &after_key)
{
    if (!any)
    {
        return false;
    }
    Node *temp=any->next, *new_node;
    do
    {
        if(temp->ID==after_key)
        {
            new_node=new Node();
            new_node->ID=ID;
            new_node->Data=Data;
            new_node->next=temp->next;
            new_node->prev=temp;
            temp->next->prev=new_node;
            temp->next=new_node;
            ring_size++;
            return true;

        }
        temp=temp->next;
    } while (temp!=any->next);
    return false;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::Add_Before_Key(const Key &ID, const Info &Data, const Key &bef_key)
{
    if(!any) return false;
    Node *temp=any;
    do
    {
        if(temp->ID==bef_key)
        {
            Node *new_node = new Node();
            new_node->ID=ID;
            new_node->Data=Data;
            new_node->next=temp;
            new_node->prev=temp->prev;
            temp->prev->next=new_node;
            temp->prev=new_node;
            ring_size++;
            return true;
        }
        temp=temp->next;
    } while(temp!=any);
    return false;

}

//Remove Methods--------------------------------------------------------------------------------------------------------------------------====REMOVE METHODS====

template <typename Key, typename Info>
void Ring<Key, Info>::Clear()
{
    if (!any) return;
    Node *temp=any, *curr;
    do
    {
        curr=temp;
        temp=temp->next;
        delete curr;

    } while(temp!=any);
    any=nullptr;
    ring_size=0;
}

template <typename Key, typename Info>
int Ring<Key, Info>::Remove_All_By_Key (const Key &rem_key)
{
    if (!any) return 0;
    Node *temp=any;
    int counter=0;
    do
    {
        if(temp->ID==rem_key)
        {
            if(ring_size==1)
            {
                Clear();
                counter++;
                return counter;
            }
            if(temp==any)
            {
                any=any->next;
            }
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            delete temp;
            ring_size--;
            counter++;
        }
        temp=temp->next;
    } while(temp!=any);
    return counter;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::Remove_By_Key (const Key &rem_key)
{
    if(!any) return false;

    Node *temp=any;
    do
    {
        if(temp->ID==rem_key)
        {
            if(ring_size==1)
            {
                Clear();
                return true;
            }
            if(temp==any)
            {
                any=any->next;
            }
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            delete temp;
            ring_size--;
            return true;
        }
        temp=temp->next;
    } while(temp!=any);
    return false;

}

//Modifiers--------------------------------------------------------------------------------------------------------------------------====MODIFIERS====
template <typename Key, typename Info>
void Ring<Key, Info>::Reverse_Ring()
{
    if (!any) return;
    Node *curr = any, *temp;
    do
    {
        temp=curr;
        Node *temp2=temp->next;
        temp->next=temp->prev;
        temp->prev=temp2;
        curr=curr->next;
    } while (curr!=any);
    any=any->next; //just to keep it more readable

}


//Display       --------------------------------------------------------------------------------------------------------------------------====DISPLAY====

template <typename Key, typename Info>
void Ring<Key, Info>::Print_Node(Node *curr) const
{
    if(!curr) std::cout<<"Given pointer is empty.\n";
    else
        {
        std::cout<<"Node no.:  "<<std::endl;
        std::cout<<"Key: "<<curr->ID<<std::endl;
        std::cout<<"Info: "<<curr->Data<<std::endl<<std::endl;
        }
}

template <typename Key, typename Info>
void Ring<Key, Info>::Print_Node(Node *curr, int i) const
{
    if(!curr) std::cout<<"Given pointer is empty.\n";
    else
        {
        std::cout<<"Node no.: "<<i<<"\t("<<curr<<")"<<std::endl;
        std::cout<<"Key: "<<curr->ID<<std::endl;
        std::cout<<"Info: "<<curr->Data<<std::endl;
        std::cout<<"Next: "<<curr->next<<std::endl;
        std::cout<<"Prev: "<<curr->prev<<std::endl<<std::endl;
        }
}

template <typename Key, typename Info>
void Ring<Key, Info>::Print_Ring() const
{
    std::cout<<"Displaying Ring of size: "<<ring_size<<" "<<std::endl;
    if(!any) std::cout<<"Given Ring is empty.\n";
    else {
    Node *curr=any->next;
    int i=0;
    std::cout<<std::endl;
    while (curr!=any)
    {
        this->Print_Node(curr, i);
        i++;
        curr=curr->next;
    }
    this->Print_Node(any, i);
    }
}

//Data Acces    --------------------------------------------------------------------------------------------------------------------------====DATA ACCES====

template <typename Key, typename Info>
Info &Ring<Key, Info>::Get_Info(const Key &nkey)
{
    if(!any)
    {
        //std::cout<<"Given ring is empty.\n "<<std::endl;
        throw std::range_error( "Given ring is empty." );
    }

    Node *temp=any;
    do
    {
        if(temp->ID==nkey) return temp->Data;
        temp=temp->next;
    } while(temp!=any);
    //std::cout<<"Function has not found node with given key.\n "<<std::endl;
    throw std::invalid_argument( "Function has not found node with given key." );
}

template <typename Key, typename Info>
Info &Ring<Key, Info>::Any_Info()
{
    if(!any)
    {
        //std::cout<<"Given ring is empty.\n "<<std::endl;
        throw std::range_error( "Given ring is empty. Cannot return any's info." );
    }
    return any->Data;
}

template <typename Key, typename Info>
Key &Ring<Key, Info>::Any_Key()
{
    if(!any)
    {
        //std::cout<<"Given ring is empty.\n "<<std::endl;
        throw std::range_error( "Given ring is empty. Cannot return any's key." );
    }
    return any->ID;
}

template <typename Key, typename Info>
const Info &Ring<Key, Info>::Get_Info(const Key &nkey) const
{
    if(!any)
    {
        //std::cout<<"Given ring is empty.\n "<<std::endl;
        throw std::range_error( "Given ring is empty." );
    }

    Node *temp=any;
    do
    {
        if(temp->ID==nkey) return temp->Data;
        temp=temp->next;
    } while(temp!=any);
    //std::cout<<"Function has not found node with given key.\n "<<std::endl;
    throw std::invalid_argument( "Function has not found node with given key." );
}

template <typename Key, typename Info>
const Info &Ring<Key, Info>::Any_Info() const
{
    if(!any)
    {
        //std::cout<<"Given ring is empty.\n "<<std::endl;
        throw std::range_error( "Given ring is empty. Cannot return any's info." );
    }
    return any->Data;
}

template <typename Key, typename Info>
const Key &Ring<Key, Info>::Any_Key() const
{
    if(!any)
    {
        //std::cout<<"Given ring is empty.\n "<<std::endl;
        throw std::range_error( "Given ring is empty. Cannot return any's key." );
    }
    return any->ID;
}

//Constructors   --------------------------------------------------------------------------------------------------------------------------====CONSTRUCTORS====

template <typename Key, typename Info>
Ring<Key, Info>::~Ring()
{
    this->Clear();
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& source):any(nullptr), ring_size(0)
{
    *this=source;
}

//Operators---------------------------------------------------------------------------------------------------------------------------------====OPERATORS====

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info>& source)
{
    if (this == &source) return *this; // handle self assignment
    this->Clear();
    if(source.Is_Empty()) return *this;
    Node *temp=source.any;
    do
    {
        this->Push(temp->ID, temp->Data);
        temp=temp->next;
    } while (temp!=source.any);

    return *this;
}

template <typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::operator+(const Ring<Key, Info>& source) const
{
    Ring<Key, Info> new_seq(*this);
    if(source.Is_Empty()) return new_seq;
    Node *temp=source.any;
    do
    {
        new_seq.Push(temp->ID, temp->Data);
        temp=temp->temp;
    } while(temp!=source.any);
    return new_seq;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::operator==(const Ring<Key, Info> &source) const
{
    if(ring_size!=source.ring_size) return false;
    Node *tcurr = this->any, *scurr = source.any;
    do
    {
        if(tcurr->Data!=scurr->Data) return false;
        if(tcurr->ID!=scurr->ID) return false;
        tcurr=tcurr->next;
        scurr=scurr->next;
    } while ((tcurr!=this->any)&&(scurr!=source.any));
    return true;

}

template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const Ring<Key, Info>& src)
{
    os<<"Displaying Ring of length "<<src.Ring_Length()<<":\n";
    if(src.Is_Empty())
    {
        os<<"Ring is empty.\n";
        return os;
    }
    typename Ring<Key, Info>::Iterator iter=src.ibegin();
    typename Ring<Key, Info>::Iterator iter_end=src.ibegin();
    int i=0;
    do
    {
        os<<"Node "<<i<<": \tKey: "<<iter.Show_Key()<<"\t||  Info: "<<iter.Show_Info()<<"\n";
        i++;
        iter++;
    } while (iter!=iter_end);
    return os;

}

#endif // RING_H
