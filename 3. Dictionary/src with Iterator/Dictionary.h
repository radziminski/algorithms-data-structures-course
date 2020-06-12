#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <stdexcept>

template <typename Key, typename Info>
class Dictionary
{
private: //private data
    struct Node
    {
        Key key;
        Info info;

        int bf; //balance factor
        Node *left;
        Node *right;
    };

    Node *root;

    template <typename K, typename I>
    friend std::ostream& operator<<(std::ostream& os, const Dictionary<K, I>& seq);

public:

    class Iterator;

    //Constructors
    Dictionary():root(nullptr) {};
    Dictionary(const Dictionary &source):root(nullptr)
    {
        *this=source;
    };

    ~Dictionary(){ this->Clear(root);};

    //Operators
    Dictionary &operator=(const Dictionary &source);
    Dictionary operator+(const Dictionary &source) const;
    Dictionary &operator+=(const Dictionary &source)
    {
        *this = *this + source;
        return *this;
    };

    //Tree Modifiers
    bool Add(const Key &k, const Info &i);
    bool Remove(const Key &k);
    void Clear()
    {
        this->Clear(root);
        root=nullptr;
    }

    //Tree Info
    bool Is_Empty() const {return root==nullptr;};
    int Tree_Height() const {return Node_Height(root);};
    int Node_Height(const Key &k) const
    {
        Node *temp=Find(k);
        if(!temp) return -1;
        return Node_Height(temp);
    }; //returns -1 if node doesn't exist
    bool Does_Node_Exist(const Key &k) const
    {
        Node *temp = Find(k);
        if(temp) return true;
        else return false;
    }

    //Data Access
    Info &Get_Info(const Key &k);
    const Info &Get_Info(const Key &k) const;

    //Display
    void Print_Inorder(std::ostream& os=std::cout) const {os<<"Printing Tree Nodes by Inorder Traversal: "<<std::endl; this->Inorder(os, root); os<<std::endl;};
    void Print_Preorder(std::ostream& os=std::cout) const {os<<"Printing Tree Nodes by Preorder Traversal: "<<std::endl;this->Preorder(os, root); os<<std::endl;};
    void Print_Postorder(std::ostream& os=std::cout) const {os<<"Printing Tree Nodes by Postorder Traversal: "<<std::endl;this->Postorder(os, root); os<<std::endl;};

    void Sketch(std::ostream &os=std::cout) const
    {
        if(!root) os<<"Tree is Empty.\n";
        Sketch_Node(root, 0, os);
        os<<std::endl;
    }

    //Iterator
        Iterator ibegin() const
        {
            Iterator it(root);
            return it;
        }
        const Iterator const_ibegin() const
        {
            Iterator it(root);
            return it;
        }


private: //private functions

    //Rotations

        //Single
    Node* R_Rotation(Node *rot_node);
    Node* L_Rotation(Node *rot_node);

        //Double
    Node* LR_Rotation(Node *rot_node);
    Node* RL_Rotation(Node *rot_node);

    //Node Find
    Node *Find (const Key &k, Node *root) const;
    Node *Find_Parrent(Node *temp, Node *root) const;
    Node *Find (const Key &k) const {return Find(k, root);};

    //Node Info
    int Node_Height(Node *temp) const;
    int Node_Left_Height(Node *temp) const;
    int Node_Right_Height(Node *temp) const;

    //Traversals
    void Inorder(std::ostream& os, Node *temp) const;
    void Preorder(std::ostream& os, Node *temp) const;
    void Postorder(std::ostream& os, Node *temp) const;

    //Balance
    void BF_Update(Node *temp);
    void Balance_Tree(Node *temp);
    void BF_Update() {BF_Update(root);};

    //Printing
    void Sketch_Node(Node *root, int space, std::ostream &os) const;
    void Clear(Node *temp);

    //op assist
    void Rec_Add(Node *temp);
    Node* Rec_Copy(Node *temp);


};

template <typename Key, typename Info>
class Dictionary<Key, Info>::Iterator
{
    friend class Dictionary<Key, Info>;
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

        bool Go_Left()
        {
            if(!current) return false;
            current=current->left;
            return true;
        }

        bool Go_Right()
        {
            if(!current) return false;
            current=current->right;
            return true;
        }

        Key &Get_Key()
        {
            if(current) return current->key;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return key." );
        }

        Info &Get_Info()
        {
            if(current) return current->info;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return info." );
        }

        const Key &Get_Key() const
        {
            if(current) return current->key;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return key." );
        }

        const Info &Get_Info() const
        {
            if(current) return current->info;
            //std::cout<<"iterator is empty \n";
            throw std::range_error( "Iterator is empty, cannot return info." );
        }

        private:
        Iterator(Node *ptr):current(ptr){};

};


//TRAVERSALS   ----------------------------------------------------------------------------------------------------------------- Traversals
template <typename Key, typename Info>
void Dictionary<Key, Info>::Inorder(std::ostream& os, Node *temp) const
{
    if(!temp) return;
    Inorder(os, temp->left);
    os<<"Key: "<<temp->key<<"    \tInfo: "<<temp->info<<std::endl;
    Inorder(os, temp->right);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::Preorder(std::ostream& os, Node *temp) const
{
    if(!temp) return;
    os<<"Key: "<<temp->key<<"    \tInfo: "<<temp->info<<std::endl;
    Preorder(os, temp->left);
    Preorder(os, temp->right);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::Postorder(std::ostream& os, Node *temp) const
{
    if(!temp) return;
    Postorder(os, temp->left);
    Postorder(os, temp->right);
    os<<"Key: "<<temp->key<<"    \tInfo: "<<temp->info<<std::endl;

}


//DATA ACCES   ------------------------------------------------------------------------------------------------------------------ Data access
template <typename Key, typename Info>
Info &Dictionary<Key, Info>::Get_Info(const Key &k)
{
    Node *temp=Find(k);
    if(!temp) throw std::invalid_argument("Can't get info of a key that were not added to the structure.");
    return temp->info;
}

template <typename Key, typename Info>
const Info &Dictionary<Key, Info>::Get_Info(const Key &k) const
{
    Node *temp=Find(k);
    if(!temp) throw std::invalid_argument("Can't get info of a key that were not added to the structure.");
    return temp->info;
}


//REMOVE & CLEAR   -------------------------------------------------------------------------------------------------------------- Remove & Clear

template <typename Key, typename Info>
void Dictionary<Key, Info>::Clear(Node *temp)       //NOT SURE
{
    if(!temp) return;
    Clear(temp->left);
    Clear(temp->right);
    delete temp;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::Remove(const Key &k)
{
    Node *temp=root, *parrent=root, *rest;
    bool dir; //falsei s left true is right
    while(temp)
    {
        if(k==temp->key) break;
        parrent=temp;
        if(k>temp->key)
        {
            temp=temp->right;
            dir=true;
        }
        else
        {
            temp=temp->left;
            dir=false;
        }
    }
    if(temp==nullptr) return false;
    if(temp==root)
    {
        if(Node_Left_Height(temp)>=Node_Right_Height(temp))
        {
                root=temp->left;
                rest=temp->right;
                delete temp;
                if(root)
                {
                    Node *second_parrent=root;
                    temp=root->right;
                    while (temp)
                    {
                        second_parrent=temp;
                        temp=temp->right;
                    }
                    second_parrent->right=rest;
                    }
        }
        else
        {
                root=temp->right;
                rest=temp->left;
                delete temp;
                if(root)
                {
                    Node *second_parrent=root;
                    temp=root->left;
                    while (temp)
                    {
                        second_parrent=temp;
                        temp=temp->right;
                    }
                    second_parrent->right=rest;
                }
        }
    }
    else
    {
        if(Node_Left_Height(temp)>=Node_Right_Height(temp))
        {
            if(dir)
            {
                parrent->right=temp->left;
                rest=temp->right;
                delete temp;
                if(parrent->right)
                {
                    Node *second_parrent=parrent->right;
                    temp=parrent->right->right;
                    while (temp)
                    {
                        second_parrent=temp;
                        temp=temp->right;
                    }
                    second_parrent->right=rest;
                }
            }
            else
            {
                parrent->left=temp->left;
                rest=temp->right;
                delete temp;
                if(parrent->left)
                {
                    Node *second_parrent=parrent->left;
                    temp=parrent->left->right;
                    while (temp)
                    {
                        second_parrent=temp;
                        temp=temp->right;
                    }
                    second_parrent->right=rest;
                }
            }
        }
        else
        {
            if(dir)
            {
                parrent->right=temp->right;
                rest=temp->left;
                delete temp;
                if(parrent->right)
                {
                    Node *second_parrent=parrent->right;
                    temp=parrent->right->left;
                    while (temp)
                    {
                        second_parrent=temp;
                        temp=temp->left;
                    }
                    second_parrent->left=rest;
                }
            }
            else
            {
                parrent->left=temp->right;
                rest=temp->left;
                delete temp;
                if(parrent->left)
                {
                    Node *second_parrent=parrent->left;
                    temp=parrent->left->left;
                    while (temp)
                    {
                        second_parrent=temp;
                        temp=temp->left;
                    }
                    second_parrent->left=rest;
                }
            }
        }
    }
    this->BF_Update();
    this->Balance_Tree(root);
    return true;

}


//PRINTING   -------------------------------------------------------------------------------------------------------------------- Printing Tree
template <typename Key, typename Info>
void Dictionary<Key, Info>::Sketch_Node(Node *root, int space, std::ostream &os) const
{
    if (!root) return;
    //Distance between branches
    space += 12;

    Sketch_Node(root->right, space, os);
    os<<std::endl;
    for (int i = 12; i < space; i++) os<<" ";
    os<<root->key<<"("<<root->info<<")"<<std::endl;
    Sketch_Node(root->left, space, os);
}

//BALANCE   --------------------------------------------------------------------------------------------------------------------- Balancing Tree
template <typename Key, typename Info>
void Dictionary<Key, Info>::Balance_Tree(Node *temp)
{
    if(temp==nullptr) return;
    Balance_Tree(temp->left);
    Balance_Tree(temp->right);
    if(temp->left)
    {
        if(temp->left->bf==2)
        {

            if(Node_Left_Height(temp->left->left)>Node_Right_Height(temp->left->left))
            {
                temp->left=R_Rotation(temp->left);
                this->BF_Update();
            }
            else
            {
                temp->left=LR_Rotation(temp->left);
                this->BF_Update();
            }
        }
        if(temp->left->bf==-2)
        {

            if(Node_Left_Height(temp->left->right)>Node_Right_Height(temp->left->right))
            {
                temp->left=RL_Rotation(temp->left);
                this->BF_Update();
            }
            else
            {
                temp->left=L_Rotation(temp->left);
                this->BF_Update();
            }
        }
    }
    if(temp->right)
    {
        if(temp->right->bf==2)
        {
            if(Node_Left_Height(temp->right->left)>Node_Right_Height(temp->right->left))
            {
                temp->right=R_Rotation(temp->right);
                this->BF_Update();
            }
            else
            {
                temp->right=LR_Rotation(temp->right);
                this->BF_Update();
            }
        }
        if(temp->right->bf==-2)
        {
            if(Node_Left_Height(temp->right->right)>Node_Right_Height(temp->right->right))
            {
                temp->right=RL_Rotation(temp->right);
                this->BF_Update();
            }
            else
            {
                temp->right=L_Rotation(temp->right);
                this->BF_Update();
            }
        }
    }
    if(temp==root)
    {
        if(temp->bf==2)
        {
            if(Node_Left_Height(temp->left)>Node_Right_Height(temp->left))
            {
                root=R_Rotation(temp);
                this->BF_Update();
            }
            else
            {
                root=LR_Rotation(temp);
                this->BF_Update();
            }
        }
        if(temp->bf==-2)
        {
            if(Node_Left_Height(temp->right)>Node_Right_Height(temp->right))
            {
                root=RL_Rotation(temp);
                this->BF_Update();
            }
            else
            {
                root=L_Rotation(temp);
                this->BF_Update();
            }

        }
    }


}


template <typename Key, typename Info>
void Dictionary<Key, Info>::BF_Update(Node *temp)
{
    if(!temp) return;
    temp->bf=Node_Left_Height(temp)-Node_Right_Height(temp);
    BF_Update(temp->left);
    BF_Update(temp->right);
}


//ROTATIONS   -------------------------------------------------------------------------------------------------------------------- Rotations
template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::L_Rotation(Node *rot_node)
{
    Node *rn_left=nullptr, *curr;
    if(!rot_node) throw std::invalid_argument("Cannot perform rotation on nullptr");//EXCEPTION
    if(!rot_node->right) return rot_node; //EXCEPTION?
    rn_left=rot_node->right->left;

    curr=rot_node->right;
    curr->left=rot_node;
    rot_node->right=rn_left;
    return curr;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::R_Rotation(Node *rot_node)
{
    Node *rn_right=nullptr, *curr;
    if(!rot_node) throw std::invalid_argument("Cannot perform rotation on nullptr");//EXCEPTION
    if(!rot_node->left) return rot_node; //EXCEPTION?
    rn_right=rot_node->left->right;

    curr=rot_node->left;
    curr->right=rot_node;
    rot_node->left=rn_right;
    return curr;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::RL_Rotation(Node *rot_node)
{
    if(!rot_node) throw std::invalid_argument("Cannot perform rotation on nullptr");
    rot_node->right=R_Rotation(rot_node->right);
    return L_Rotation(rot_node);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::LR_Rotation(Node *rot_node)
{
    if(!rot_node) throw std::invalid_argument("Cannot perform rotation on nullptr");
    rot_node->left=L_Rotation(rot_node->left);
    return R_Rotation(rot_node);
}


//HEIGHTS   -------------------------------------------------------------------------------------------------------------------- Hight of Tree
template <typename Key, typename Info>
int Dictionary<Key, Info>::Node_Height(Node *temp) const
{
    if(!temp) return 0;
    if(!temp->left&&!temp->right) return 0;
    if(Node_Height(temp->left)>Node_Height(temp->right)) return Node_Height(temp->left) + 1;
    else return Node_Height(temp->right) + 1;
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::Node_Left_Height(Node *temp) const
{
    if(!temp) return -1;
    if(!temp->left) return 0;
    return Node_Height(temp->left) + 1;
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::Node_Right_Height(Node *temp) const
{
    if(!temp) return -1;
    if(!temp->right) return 0;
    return Node_Height(temp->right) + 1;
}

//ADDING   ---------------------------------------------------------------------------------------------------------------------- Node ADD
template <typename Key, typename Info>
bool Dictionary<Key, Info>::Add(const Key &k, const Info &i)
{
    if(Find(k)) return false; //assuming key is unique
    Node *new_node = new Node(), *temp=root, *parrent=root;
    new_node->key=k;
    new_node->info=i;
    new_node->left=nullptr;
    new_node->right=nullptr;
    if(!temp)
    {
        root=new_node;
        return true;
    }
    while(temp)
    {
        parrent=temp;
        if(k>temp->key) temp=temp->right;
        else temp=temp->left;
    }
    if(k>parrent->key) parrent->right=new_node;
    else parrent->left=new_node;
    this->BF_Update(); //Updating Balance Factors
    this->Balance_Tree(root);
    this->BF_Update(); //Updating Balance Factors
    return true;
}

//FINDING   ------------------------------------------------------------------------------------------------------------------ Finding Node in Tree
template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::Find(const Key &k, Node *root) const
{
    if(!root) return nullptr;
    if(root->key==k) return root;
    if(k>root->key) return Find(k, root->right);
    else return Find(k, root->left);
}

//OPERATORS
template <typename Key, typename Info>
std::ostream& operator<<(std::ostream &os, const Dictionary<Key, Info> &src)
{
    src.Sketch(os);
}

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(const Dictionary<Key, Info>& source)
{
    this->Clear();
    this->root=Rec_Copy(source.root);
    return *this;
}

template <typename Key, typename Info>
Dictionary<Key, Info> Dictionary<Key, Info>::operator+(const Dictionary<Key, Info>& source) const
{
    Dictionary<Key, Info> newd(*this);
    newd.Rec_Add(source.root);
    newd.BF_Update();
    return newd;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::Rec_Add(Node *temp)
{
    if(!temp) return;
    this->Add(temp->key, temp->info);
    this->Rec_Add(temp->left);
    this->Rec_Add(temp->right);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::Rec_Copy(Node *temp)
{
    if(!temp) return nullptr;
    Node *new_node = new Node();
    new_node->key=temp->key;
    new_node->info=temp->info;
    new_node->bf=temp->bf;
    new_node->left=Rec_Copy(temp->left);
    new_node->right=Rec_Copy(temp->right);
    return new_node;

}



#endif // DICTIONARY_H
