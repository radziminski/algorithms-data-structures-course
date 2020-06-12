#include <iostream>
#include <fstream>
#include "Split.h"

using namespace std;

int main()
{
    //optional ofstream
    ofstream out;
    out.open("TESTS.txt");

    //Constructor Tests
    cout<<"Testing Sequence Constructor... (creating seq1, seq2, seq3) \n\n";
    Sequence<int, float> seq1, seq2, seq3;

    //Node Add functions test
    cout<<"=======> Testing Node Add functions:\n\n\tAdding 3 elements to the list seq1 by push front:\n";
    seq1.Push_Front(1, 11);
    seq1.Push_Front(2, 22);
    seq1.Push_Front(3, 33);
    cout<<seq1;

    cout<<"\tAdding 3 elements to the list seq1 by push back:\n";
    seq1.Push_Back(4, 44);
    seq1.Push_Back(5, 55);
    seq1.Push_Back(6, 66);
    cout<<seq1;

    cout<<"\tAdding 3 elements with same key to the list seq1 by push back and push front:\n";
    seq1.Push_Front(7, 77);
    seq1.Push_Back(7, 78);
    seq1.Push_Front(7, 79);
    cout<<seq1;

    cout<<"\tAdding 5 elements to another list seq2 by add_at_position with different arguments (first 2 are improper):\n";
    seq2.Add_At_Position(1, 11, -3);
    seq2.Add_At_Position(1, 11, 11);
    seq2.Add_At_Position(1, 11, 0);
    seq2.Add_At_Position(2, 22, 0);
    seq2.Add_At_Position(3, 33, 1);
    seq2.Add_At_Position(3, 33, 3);
    seq2.Add_At_Position(3, 33, 4);
    cout<<seq2;

    cout<<"\tAdding 4 elements to the list seq2 by add_after_key with different arguments (keys: 2+where-12, 2, 1, 3, 3+where3) (first 1 is improper):\n";
    seq2.Add_After_Key(4, 44, 2, -12);
    seq2.Add_After_Key(4, 44, 2);
    seq2.Add_After_Key(5, 55, 1);
    seq2.Add_After_Key(6, 66, 3);
    seq2.Add_After_Key(7, 77, 3, 3);
    cout<<seq2;

    cout<<"\tAdding 4 elements to the list seq 2 by add_before_key with different arguments (keys: 2+where-12, 2, 6, 7, 3) (first 1 is improper):\n";
    seq2.Add_Before_Key(5, 44, 2, -12);
    seq2.Add_Before_Key(8, 88, 2);
    seq2.Add_Before_Key(9, 99, 6);
    seq2.Add_Before_Key(10, 101, 7);
    seq2.Add_Before_Key(11, 111, 3, 3);
    cout<<seq2;

    cout<<"=======> Testing Node Remove Functions\n\n";
    cout<<"\tTrying pop_front function on empty list seq3:\n";
    seq3.Pop_Front();
    cout<<seq3;
    cout<<"\n\tTrying pop_front function on seq2 twice:\n";
    seq2.Pop_Front();
    seq2.Pop_Front();
    cout<<seq2;
    cout<<"\tTrying pop_back function on empty list seq3:\n";
    seq3.Pop_Back();
    cout<<seq3;
    cout<<"\n\tTrying pop_back function on seq2 twice:\n";
    seq2.Pop_Back();
    seq2.Pop_Back();
    cout<<seq2;

    cout<<"\tTrying remove_by_key function on empty seq3:\n";
    seq3.Remove_By_Key(2);
    cout<<seq3;
    cout<<"\tTrying remove_by_key function on seq2:\n";
    cout<<"Removing nodes with key 4. Removed: "<<seq2.Remove_By_Key(4)<<" nodes\n";
    cout<<"Removing nodes with key 3. Removed: "<<seq2.Remove_By_Key(3)<<" nodes\n";
    cout<<seq2;

    cout<<"\tTrying remove_at_position function on empty seq3 with positions -3, 0 (first one is improper):\n";
    seq3.Remove_At_Position(-3);
    seq3.Remove_At_Position(0);
    cout<<seq3;
    cout<<"\tTrying remove_at_position function on empty seq2 with positions -3, 5, 0, 4, 2 (first two are improper):\n";
    seq2.Remove_At_Position(-3);
    seq2.Remove_At_Position(100);
    seq2.Remove_At_Position(0);
    seq2.Remove_At_Position(4);
    seq2.Remove_At_Position(2);
    cout<<seq2;

    cout<<"\tTesting clear list on empty seq3:\n";
    seq3.Clear_List();
    cout<<seq3;
    cout<<"\tTesting clear list on seq2:\n";
    seq2.Clear_List();
    cout<<seq2;

    cout<<"\n=======> Testing List Info Functions\n\n";
    cout<<"Testing Is_Empty(): \nSeq2 is empty (1 is true 0 is false): "<<seq2.Is_Empty();
    cout<<"\nSeq1 is empty (1 is true 0 is false): "<<seq1.Is_Empty();

    cout<<"\n\nTesting List_Length():\nList Length of seq 2 is: "<<seq2.List_Length()<<" and seq 1 is: "<<seq1.List_Length();

    cout<<"\n\n=======> Testing Data Access Functions\n\n";
    cout<<"Seq1: "<<seq1;
    cout<<"\nTesting Get_Info(1): "<<seq1.Get_Info(1);
    cout<<"\nTesting Get_Info(7): "<<seq1.Get_Info(7);
    cout<<"\nTesting Get_Info(7, 3): "<<seq1.Get_Info(7, 3);

    cout<<"\n\nTesting Front_Node_Info on empty seq2: ";
    cout<<seq2.Front_Node_Info();
    cout<<"\nTesting Front_Node_Info on seq1: "<<seq1.Front_Node_Info();
    cout<<"\nTesting Back_Node_Info on empty seq2: ";
    cout<<seq2.Back_Node_Info();
    cout<<"\nTesting Back_Node_Info on seq1: "<<seq1.Back_Node_Info();
    cout<<"\n\nTesting Front_Key on empty seq2: ";
    cout<<seq2.Front_Key();
    cout<<"\nTesting Front_Key on seq1: "<<seq1.Front_Key();
    cout<<"\nTesting Back_Key on empty seq2: ";
    cout<<seq2.Back_Key();
    cout<<"\nTesting Back_Key on seq1: "<<seq1.Back_Key();

    cout<<"\n\n=======> Testing Displaying the list Functions\n\n";
    cout<<"Printing empty seq2 by Print_List():\n";
    seq2.Print_List();
    cout<<"Printing seq1 by Print_List():\n";
    seq1.Print_List();

    cout<<"\n\nPrinting empty seq2 by Print_Front():\n";
    seq2.Print_Front();
    cout<<"Printing seq1 by Print_Front():\n";
    seq1.Print_Front();

    cout<<"\n\nPrinting empty seq2 by Print_Back():\n";
    seq2.Print_Back();
    cout<<"Printing seq1 by Print_Back():\n";
    seq1.Print_Back();

    cout<<"\n\nPrinting empty seq2 by Print_By_Key(0):\n";
    seq2.Print_By_Key(0);
    cout<<"Printing seq1 by Print_By_Key(1):\n";
    seq1.Print_By_Key(1);
    cout<<"Printing seq1 by Print_By_Key(7, 2):\n";
    seq1.Print_By_Key(7, 2);

    cout<<"\n\n=======> Testing Cpy constructor\n\n";
    cout<<"Creating and printing seq 4 by cpying seq1:\n";
    Sequence<int, float> seq4(seq1);
    cout<<seq4;
    seq3.Push_Back(3, 3);
    seq3.Push_Front(5, 5);
    cout<<"\n\n=======> Testing Operators the list Functions\n\n";
    cout<<"Testing assignment operator on empty seq2=seq1, seq4=seq3, and nonempty seq3=seq1:\nSeq2:";
    seq2=seq1;
    seq4=seq3;
    seq3=seq1;
    cout<<seq2<<"Seq4:"<<seq4<<"Seq3:"<<seq3;
    seq2.Clear_List();
    cout<<"\nTesting += operator on empty seq2+=seq1, and nonempty seq4+=seq1:\nSeq2:";
    seq2+=seq1;
    seq4+=seq1;
    cout<<seq2<<"Seq4:"<<seq4;

    cout<<"\nTesting == operator by compering identical seq2 and seq1, then different seq4 and seq1\n";
    cout<<"Seq2==Seq1: "<<(seq2==seq1)<<"\nSeq4==Seq1: "<<(seq4==seq1);

    cout<<"\n\n=======> Testing Iterators\n\n";
    cout<<"Printing all list seq4 keys with use of iterators: \n";
    Sequence<int, float>::Iterator iterb=seq4.ibegin();
    Sequence<int, float>::Iterator const itere=seq4.const_iend();
    while(iterb!=itere)
    {
        cout<<iterb.Show_Key()<<" || ";
        iterb++;
    }
    cout<<endl;

    cout<<"\n\n=======> Testing Split Function\n\n";

    cout<<"Seq1:"<<seq1;
    cout<<"\n Calling split function with wrong arguments:\n";
    Split(seq1, -3, seq3, 1, seq4, -2);
    Split(seq1, 200, seq3, 1, seq4, -2);
    Split(seq1, 1, seq3, -4, seq4, -2);
    cout<<"\n Calling split function Split(seq1, 2, seq3, 1, seq4, 2):\n";
    cout<<"Used: "<<Split(seq1, 2, seq3, 1, seq4, 2)<<" elements\n";
    cout<<"Seq3:"<<seq3<<"Seq4:"<<seq4;
    cout<<"\n Calling split function Split(seq1, 2, seq3, 100, seq4, 2):\n";
    cout<<"Used: "<<Split(seq1, 1, seq3, 100, seq4, 2)<<" elements.\n";
    cout<<"Seq3:"<<seq3<<"Seq4:"<<seq4;

    cout<<"\n Calling split function Split(seq1, 2, seq3, 3, seq4, 1):\n";
    cout<<"Used: "<<Split(seq1, 2, seq3, 2, seq4, 1)<<" elements.\n";
    cout<<"Seq3:"<<seq3<<"Seq4:"<<seq4;

    cout<<"\n\n=======> Tests Ended, Closing Program (and testing destructors)\n\n";

    out.close();
    return 0;
}
