#include <iostream>
#include <fstream>
#include "Produce.h"

using namespace std;

int main()
{

    //Testing constructors:
    Ring<int, float> a, b, c;

    //Testing Node Add Functions
    cout<<"==> TESTING NODE ADD FUNCTIONS (on ring a and b): \n";
    a.Push(1, 11);
    a.Push(2, 22);
    cout<<"Success of adding after key (should be 1, 1, 0, 0): "<<a.Add_After_Key(4, 44, 2);
    cout<<a.Add_Before_Key(3, 33, 4);
    cout<<a.Add_After_Key(3, 34, 55);
    cout<<b.Add_Before_Key(3, 35, 4)<<endl;
    a.Push(5, 51);
    a.Push(5, 52);
    a.Push(5, 53);

    b.Push(11, 1);
    b.Push(22, 2);
    b.Push(33, 3);
    b.Push(44, 4);
    b.Push(33, 5);
    cout<<a<<b<<endl;

    cout<<"==> TESTING NODE REMOVE FUNCTIONS (on ring a, b, c and d) AND CPY CONSTR. AND ASSIGNM. OP.: \n";
    cout<<"Success of removing by key (should be 1, 1, 0, 0): ";
    cout<<a.Remove_By_Key(1);
    cout<<a.Remove_By_Key(5);
    cout<<a.Remove_By_Key(8);
    cout<<a.Remove_By_Key(0)<<endl;
    cout<<a;
    cout<<"Result of remove all by key 5 from a:  ";
    cout<<a.Remove_All_By_Key(5)<<endl;
    cout<<a;
    cout<<"\nCopying b to c and d (and testing cpy constr. and assignment op.). Clearing b: \n";
    c = b;
    Ring<int, float> d(b);
    b.Clear();
    cout<<b;
    cout<<"Created c and d: "<<endl;
    cout<<c<<d<<endl<<endl;

    cout<<"==> TESTING DATA ACCESS FUNCTIONS (on ring a): \n";
    cout<<a;
    cout<<"Key and info of any node: "<<a.Any_Key()<<"  ||  "<<a.Any_Info()<<endl;
    cout<<"Info of node with key 3: "<<a.Get_Info(3)<<endl<<endl;

    cout<<"==> TESTING PRODUCE FUNCTION (on ring a, c): \n";
    cout<<a<<c;
    cout<<"Calling produce: Produce(a, 0, 2, true, c, 2, 1, false, 2)"<<endl;
        Ring<int, float> e = Produce(a, 0, 2, true, c, 2, 1, false, 2);
    cout<<e;

    //Ring<int, float>::Iterator i;
    //i.Show_Info();

    cout<<"\n==> END OF TESTS, CLOSING PROGRAM (AND TESTING DESTRUCTORS)";
    return 0;
}
