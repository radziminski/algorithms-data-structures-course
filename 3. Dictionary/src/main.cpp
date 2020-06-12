#include <iostream>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main()
{
    ofstream output;
    output.open ("Tests.txt");
    //Tests
    //Constructors
    Dictionary<int, float> d1, d2;
    output<<"==== Dictionary class Tests: ===="<<endl<<endl;
    //Testing Tree Modifiers, balancing and printing functions
    d1.Add(1, 11);
    d1.Add(1, 11);
    d1.Add(1, 11);
    d1.Add(5, 55);
    d1.Add(8, 88);
    d1.Add(4, 44);
    d1.Add(3, 33);
    d1.Add(6, 66);
    d1.Add(2, 22);
    d1.Add(7, 77);
    d1.Add(9, 99);
    d1.Add(10, 10);
    d1.Add(11, 111);
    d1.Add(0, 00);
    d1.Add(-1, -11);
    output<<"Dictionary d1 after adding int keys from -1 to 11:"<<endl;
    d1.Sketch(output);
    output<<"Nodes By different traversals:"<<endl;
    d1.Print_Inorder(output);
    d1.Print_Postorder(output);
    d1.Print_Preorder(output);

    d2=d1;

    d1.Remove(11);
    d1.Remove(7);
    d1.Remove(8);
    d1.Remove(10);
    d1.Remove(9);
    output<<"Dictionary d1 after removing keys from 7 to 11:"<<endl;
    d1.Sketch(output);

    //Testing operators and tree info functions
    Dictionary<int, float> d3(d1), d4=d3;
    d4+=d2;
    output<<"Dictionary d2=d1 (before removal od keys 7 to 11): (Testing assignment operator)"<<endl;
    output<<d2;
    output<<"Dictionary d3(d1) (after removal): (Testing copy constructor)"<<endl;
    d3.Sketch(output);
    output<<"Dictionary d4=d3+d2: (Testing + and += operator)"<<endl;
    d4.Sketch(output);
    d4.Clear();
    output<<"Dictionary d4 after Clear() function:"<<endl;
    d4.Sketch(output);
    output<<"Dictionary d3 tree height: " <<d3.Tree_Height()<<endl;
    output<<"Node of key 5 and 18 height of Dictionary d3 (second should be -1 cuz it doesnt exist):" <<d3.Node_Height(5)<<"\t"<<d3.Node_Height(18)<<endl;
    output<<"Does nodes 3 and 100 exists in tree d3 (shold be 1 and 0): "<<d3.Does_Node_Exist(3)<<"\t"<<d3.Does_Node_Exist(100)<<endl;

    //Testing Data access functions
    output<<"Info of Nodes 1 and 5 of d3:"<<d3.Get_Info(1)<<"\t"<<d3.Get_Info(5)<<endl;
    //output<<"Info of Nodes 2 and 101 of d3:"<<d3.Get_Info(2)<<" "<<d3.Get_Info(101)<<endl;
    //(Throws Exception)

    output.close();

    //Testing Destructors and Clear() function.
    return 0;
}
