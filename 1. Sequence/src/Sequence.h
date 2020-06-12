#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <iostream>

template <typename Key, typename Info>
class Sequence
{
    private:    //class data
        struct Node;
        Node *head;
        int list_size;

        template <typename K, typename I>
        friend std::ostream& operator<<(std::ostream& os, const Sequence<K, I>& seq);

    public:
        //Constructors
        Sequence<Key, Info>():head(nullptr), list_size(0) {};
        ~Sequence<Key, Info>();
        Sequence<Key, Info>(const Sequence<Key, Info>& source);

        //Operators:
        Sequence<Key, Info>& operator=(const Sequence<Key, Info>& source);
        Sequence<Key, Info> operator+(const Sequence<Key, Info>& source);
        Sequence<Key, Info>& operator+=(const Sequence<Key, Info>& source)
        {
            *this = *this + source;
            return *this;
        }

        //Logic and compare operators
        bool operator==(const Sequence<Key, Info>& source) const;
        bool operator!=(const Sequence<Key, Info>& source) const
        {
            return !(*this==source);
        }
        bool operator>(const Sequence<Key, Info>& source) const
        {
            if(this->list_size>source.list_size) return true;
            else return false;
        }
        bool operator>=(const Sequence<Key, Info>& source) const
        {
            if(this->list_size>=source.list_size) return true;
            else return false;
        }
        bool operator<(const Sequence<Key, Info>& source) const
        {
            if(this->list_size<source.list_size) return true;
            else return false;
        }
        bool operator<=(const Sequence<Key, Info>& source) const
        {
            if(this->list_size<=source.list_size) return true;
            else return false;
        }

        //Node Add Methods
        //note: I'm passing all values as const (unchangable) referance to the value so program won't make unnecesary copy of the values
        bool Push_Front(const Key &ID, const Info &Data);
        bool Push_Back(const Key &ID, const Info &Data);
        bool Add_At_Position (const Key &ID, const Info &Data, const int &position); //adds element at given position in the list, or return false if the list is too short
        bool Add_After_Key (const Key &ID, const Info &Data, const Key &after_key, int where=1); //adds element after first apperance of given key, or return false if the key doesn;t exist on the list
        bool Add_Before_Key (const Key &ID, const Info &Data, const Key &bef_key, int where=1); //adds element after first apperance of given key, or return false if the key doesn;t exist on the list

        //Node Remove Methods
        bool Pop_Front();
        bool Pop_Back();
        int Remove_By_Key (const Key &rem_key);                    //removes all nodes with given key and returns number of deleted nodes
        bool Remove_At_Position(const int &position);               //removes node at given position on the list or return false if list is too short
        void Clear_List();

        //List Info
        bool Is_Empty() const
        {
            return (head==nullptr);
        }
        int List_Length() const
        {
            return list_size;
        }


        //Data Acces
        Info Get_Info(const Key &nkey, int where=1) const;
        Info Front_Node_Info() const;
        Info Back_Node_Info() const;
        Key Front_Key() const;
        Key Back_Key() const;

        //Displaying the list
        void Print_List() const;
        void Print_Front() const                            //Prints first node of the list
        {
            if(!head)
            {
                std::cout<<"List is empty.\n";
                return;
            }
            this->Print_Node(head);
        }
        void Print_Back() const                             //Prints last node of the list
        {
            Node *curr=head;
            if(!curr)
            {
                std::cout<<"List is empty.\n";
                return;
            }
            while(curr->next)
            {
                curr=curr->next;
            }
            this->Print_Node(curr);

        }
        void Print_By_Key(const Key &k, int where=1) const                      //Prints all nodes with given key
        {
            Node *curr=head;
            if(!curr) return;
            int i=1;
            std::cout<<"Printing Sequence by Key:\n\n";
            while(curr->next)
            {
                if((curr->ID==k)&&(i==where)) this->Print_Node(curr);
                else if (curr->ID==k) i++;
                curr=curr->next;
            }
        }

        //Iterators
        class Iterator;
        Iterator ibegin() const
        {
            Iterator it(head);
            return it;
        }
        const Iterator const_ibegin() const
        {
            Iterator it(head);
            return it;
        }
        Iterator iend() const
        {
            Iterator it(nullptr);
            return it;
        }
        const Iterator const_iend() const
        {
            Iterator it(nullptr);
            return it;
        }

private: //private methods
            //Add methods with Node argument used in other functions
        bool Push_Front(Node *new_node);
        bool Push_Back(Node *new_node);
        bool Add_At_Position (Node *new_node, const int &position);
        bool Add_After_Key (Node *new_node, const Key &after_key, int where=1);
            //Displaying the list functions with nodes used in public display methods
        void Print_Node(Node *curr) const;
        void Print_Node(Node *curr, int num) const;

};

// Class ITERATOR

template <typename Key, typename Info>
class Sequence<Key, Info>::Iterator
{
    friend class Sequence<Key, Info>;
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
        Iterator operator++(int)
        {
            if(current) current=current->next;
            return *this;
        }

        Key Show_Key() const
        {
            if(current) return current->ID;
            std::cout<<"iterator is empty \n";
            return 0;
        }

        Info Show_Data() const
        {
            if(current) return current->Data;
            std::cout<<"iterator is empty \n";
            return 0;
        }

        private:
        Iterator(Node *ptr):current(ptr){};

};


// ===Class Sequence Methods===

//NODE

template <typename Key, typename Info>
struct Sequence<Key, Info>::Node
{
    Info Data;
    Key ID;
    Node *next;
};

//Add Methods   --------------------------------------------------------------------------------------------------------------------------====ADD METHODS====

template <typename Key, typename Info>
bool Sequence<Key, Info>::Push_Front(const Key &ID, const Info &Data)
{
    if(Is_Empty())
    {
        head = new Node();
        head->Data=Data;
        head->ID=ID;
        head->next=nullptr;
        list_size++;
        return true;
    }

    Node *new_node = new Node();
    new_node->Data=Data;
    new_node->ID=ID;
    new_node->next=head;
    head=new_node;
    list_size++;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Push_Front(Node *new_node)
{
    if (!new_node) return false;
    if(Is_Empty())
    {
        head=new_node;
        list_size++;
        return true;
    }
    new_node->next=head;
    head=new_node;
    list_size++;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Push_Back(const Key &ID, const Info &Data)
{
    Node *new_node = new Node();
    new_node->Data=Data;
    new_node->ID=ID;
    new_node->next=nullptr;
    if(Is_Empty())
    {
        head=new_node;
        list_size++;
        return true;
    }
    Node *curr=head, *prev=head;
    while (curr)
    {
        prev=curr;
        curr=curr->next;
    }
    prev->next=new_node;
    list_size++;
    return true;

}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Push_Back(Node *new_node)
{
    if (!new_node) return false;
    new_node->next=nullptr;
    if(this->Is_Empty())
    {
        head=new_node;
        list_size++;
        return true;
    }
    Node *curr=head, *prev=head;
    while (curr)
    {
        prev=curr;
        curr=curr->next;
    }
    prev->next=new_node;
    list_size++;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Add_At_Position (Node *new_node, const int &position)
{
    if (!new_node) return false;
    if((position>=list_size)||(position<0)) return false;
    if(position==0)
    {
        Push_Front(new_node);
        return true;
    }
    if(position==list_size-1)
    {
        Push_Back(new_node);
        return true;
    }
    int i=0;
    Node *curr=head, *prev=head;
    while ((i!=position)&&curr)
    {
        prev=curr;
        curr=curr->next;
        i++;
    }
    prev->next=new_node;
    new_node->next=curr;
    list_size++;
    return true;

}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Add_At_Position (const Key &ID, const Info &Data, const int &position)
{
    if(position==0)
    {
        bool b=Push_Front(ID, Data);
        return b;
    }
    if((position>list_size)||(position<0))
    {
        std::cout<<"Wrong position given. Returning false\n";
        return false;
    }
    if(position==list_size)
    {
        bool b=Push_Back(ID, Data);
        return b;
    }
    int i=0;
    Node *curr=head, *prev=head, *new_node=new Node();
    while ((i!=position)&&curr)
    {
        prev=curr;
        curr=curr->next;
        i++;
    }
    new_node->ID=ID;
    new_node->Data=Data;
    prev->next=new_node;
    new_node->next=curr;
    list_size++;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Add_After_Key(Node *new_node, const Key &after_key, int where)
{
    if(Is_Empty()) return false;
    if (!new_node) return false;
    if(where<1) return false;
    Node *curr=head;
    int i=1;
    while((after_key!=curr->ID)&&curr||i<where)
    {
        if((after_key==curr->ID)) i++;
        curr=curr->next;
        if(!curr) break;
    }
    if(!curr) return false;
    new_node->next=curr->next;
    curr->next=new_node;
    list_size++;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Add_After_Key(const Key &ID, const Info &Data, const Key &after_key, int where)
{
    if(Is_Empty()) return false;
    Node *curr=head;
    int i=1;
    if(where<1) return false;
    while(((after_key!=curr->ID)||(i<where))&&curr)
    {
        if((after_key==curr->ID)) i++;
        curr=curr->next;
        if(!curr) break;
    }

    if(!curr) return false;
    Node *new_node=new Node();
    new_node->ID=ID;
    new_node->Data=Data;
    new_node->next=curr->next;
    curr->next=new_node;
    list_size++;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Add_Before_Key(const Key &ID, const Info &Data, const Key &bef_key, int where)
{
    if(Is_Empty()) return false;
    Node *curr=head, *prev=head;
    int i=1;
    if(where<1) return false;
    while(((bef_key!=curr->ID)||(i<where))&&curr)
    {
        if((bef_key==curr->ID)) i++;
        prev=curr;
        curr=curr->next;
        if(!curr) break;
    }

    if(!curr) return false;
    Node *new_node=new Node();
    new_node->ID=ID;
    new_node->Data=Data;
    if (prev==head)
    {
        new_node->next=prev;
        head=new_node;
        list_size++;
        return true;
    }
    new_node->next=prev->next;
    prev->next=new_node;
    list_size++;
    return true;
}

//Remove Methods--------------------------------------------------------------------------------------------------------------------------====REMOVE METHODS====

template <typename Key, typename Info>
bool Sequence<Key, Info>::Pop_Front()
{
    if(Is_Empty())
    {
        std::cout<<"Cannot pop any Nodes, because list is empty."<<std::endl;
        return false;
    }
    Node *curr=head;
    head=head->next;
    delete curr;
    list_size--;
    return true;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Pop_Back()
{
    if(Is_Empty())
    {
        std::cout<<"Cannot pop any Nodes, because list is empty."<<std::endl;
        return false;
    }
    if (!head) return 0;        //just in case if list_size wasw wrongly operated
    Node *curr=head, *prev=head;
    while (curr->next)
    {
        prev=curr;
        curr=curr->next;
    }
    prev->next=nullptr;
    delete curr;
    if(curr==head) head=nullptr;
    list_size--;
    return true;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::Clear_List()
{
    Node *curr=head, *temp;
    while (curr)
    {
        temp=curr;
        curr=curr->next;
        delete temp;
    }
    head=nullptr;
    list_size=0;
}

template <typename Key, typename Info>
int Sequence<Key, Info>::Remove_By_Key (const Key &rem_key)
{
    int num=0;
    Node *curr=head, *prev=head;
    while(curr)
    {
        if(curr->ID==rem_key)
        {
            if(curr==head)
            {
                head=curr->next;
                delete curr;
                list_size--;
                num++;
                prev=head;
                curr=head->next;
            }
            else
            {
                prev->next=curr->next;
                delete curr;
                list_size--;
                num++;
                curr=prev->next;
            }
        }
        else
        {
            prev=curr;
            curr=curr->next;
        }
    }
    return num;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::Remove_At_Position(const int &position)
{
    if((position>list_size)||(position<0)) return false;
    if(position==0)
    {
        bool b=Pop_Front();
        return b;
    }
    if(position==list_size)
    {
        bool b=Pop_Back();
        return b;
    }
    int i=0;
    Node *curr=head, *prev=curr;
    while((i!=position)&&curr)
    {
        prev=curr;
        curr=curr->next;
        i++;
    }
    if (!curr) return 0;        //just in case if list_size was wrongly operated
    prev->next=curr->next;
    delete curr;
    list_size--;
    return true;

}

//Display       --------------------------------------------------------------------------------------------------------------------------====DISPLAY====

template <typename Key, typename Info>
void Sequence<Key, Info>::Print_Node(Node *curr) const
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
void Sequence<Key, Info>::Print_Node(Node *curr, int i) const
{
    if(!curr) std::cout<<"Given pointer is empty.\n";
    else
        {
        std::cout<<"Node no.: "<<i<<std::endl;
        std::cout<<"Key: "<<curr->ID<<std::endl;
        std::cout<<"Info: "<<curr->Data<<std::endl<<std::endl;
        }
}

template <typename Key, typename Info>
void Sequence<Key, Info>::Print_List() const
{
    Node *curr=head;
    int i=0;
    std::cout<<"Displaying Sequence of size: "<<list_size<<" "<<std::endl;
    if(!curr) std::cout<<"Given Sequence is empty.\n";
    std::cout<<std::endl;
    while (curr)
    {
        this->Print_Node(curr, i);
        i++;
        curr=curr->next;
    }
}

//Data Acces    --------------------------------------------------------------------------------------------------------------------------====DATA ACCES====

template <typename Key, typename Info>
Info Sequence<Key, Info>::Get_Info(const Key &nkey, int where) const
{
    Node *curr=head;
    int i=1;
    if(where<1)
    {
        std::cout<<"Wrong variable 'where' given. Please enter int bigger than 0.\n Returning 0";
        return 0;
    }
    while(curr)
    {
        if(curr->ID==nkey)
        {
            if(where==i) return curr->Data;
            else i++;
        }
        curr=curr->next;
    }
    std::cout<<"Function has not found node with given key. returning 0"<<std::endl;
    return 0;
}

template <typename Key, typename Info>
Info Sequence<Key, Info>::Front_Node_Info() const
{
    if(!head)
    {
        std::cout<<"List is Empty, returning 0;\n";
        return 0;
    }
    return head->Data;
}

template <typename Key, typename Info>
Info Sequence<Key, Info>::Back_Node_Info() const
{
    Node *curr=head;
    if(!curr)
        {
        std::cout<<"List is Empty, returning 0;\n";
        return 0;
        }
    while(curr->next) curr=curr->next;
    return curr->Data;
}

template <typename Key, typename Info>
Key Sequence<Key, Info>::Front_Key() const
{
    if(!head)
    {
        std::cout<<"List is Empty, returning 0;\n";
        return 0;
    }
    return head->ID;
}

template <typename Key, typename Info>
Key Sequence<Key, Info>::Back_Key() const
{
    if(!head)
    {
        std::cout<<"List is Empty, returning 0;\n";
        return 0;
    }
    Node *curr=head;
    while(curr->next) curr=curr->next;
    return curr->ID;
}

//Constructors   --------------------------------------------------------------------------------------------------------------------------====CONSTRUCTORS====

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    this->Clear_List();
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& source):head(nullptr)
{
    *this=source;
}

//Operators---------------------------------------------------------------------------------------------------------------------------------====OPERATORS====

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& source)
{
    if (this == &source) return *this; // handle self assignment
    this->Clear_List();
    this->head=nullptr;
    this->list_size=0;

    if(source.Is_Empty()) return *this;

    Node *curr = source.head;
    while (curr)
    {
        this->Push_Back(curr->ID, curr->Data);
        curr=curr->next;
    }

    return *this;
}

template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::operator+(const Sequence<Key, Info>& source)
{
    Sequence<Key, Info> new_seq(*this);
    if(source.Is_Empty()) return new_seq;
    Node *curr=source.head;

    while (curr)
    {
        new_seq.Push_Back(curr->ID, curr->Data);
        curr=curr->next;
    }
    return new_seq;

}

template <typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info> &source) const
{
    if(list_size!=source.list_size) return false;
    Node *tcurr = this->head, *scurr = source.head;
    while (tcurr&&scurr)
    {
        if(tcurr->Data!=scurr->Data) return false;
        if(tcurr->ID!=scurr->ID) return false;
        tcurr=tcurr->next;
        scurr=scurr->next;
    }
    return true;

}

template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const Sequence<Key, Info>& seq)
{
    typename Sequence<Key, Info>::Iterator iter=seq.ibegin();
    typename Sequence<Key, Info>::Iterator const iter_end=seq.const_iend();
    os<<"Displaying Sequence of length "<<seq.List_Length()<<":\n";
    int i=0;
    if(seq.Is_Empty())
    {
        os<<"List is Empty.\n";
        return os;
    }
    os<<"Node:\t\tKey:\t\tData:\n";
    while(iter!=iter_end)
    {
        os<<"Node no. "<<i<<":\t"<<iter.Show_Key()<<"\t|\t"<<iter.Show_Data()<<"\n";
        i++;
        iter++;
    }
    os<<"\n";
    return os;

}

#endif // SEQUENCE_H
