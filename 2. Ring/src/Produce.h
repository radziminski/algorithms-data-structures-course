#ifndef PRODUCE_H
#define PRODUCE_H
#include "Ring.h"
#include <iostream>

using namespace std;

template <typename Key, typename Info>
Ring<Key, Info> Produce (const Ring<Key, Info> &r1, int start1, int len1, bool dir1,
                         const Ring<Key, Info> &r2, int start2, int len2, bool dir2, int repeat)
{
    Ring<Key, Info> r3;
    //Checking Arguments:
    if(len1<0||len2<0||repeat<0)
    {
        if (len1<0) cout<<"Given len1 is less than 0. ";
        if (len2<0) cout<<"Given len2 is less than 0. ";
        if (repeat<0) cout<<"Given repeat is less than 0. ";
        cout<<"Returning Empty Ring. \n";
        return r3;
    }

    typename Ring<Key, Info>::Iterator iter1 = r1.ibegin();
    typename Ring<Key, Info>::Iterator iter2 = r2.ibegin();

    //setting starts
    iter1 = iter1 + start1;
    iter2 = iter2 + start2;

    //creating final ring
    for (int i=0; i<repeat; i++)
    {
        if(!r1.Is_Empty())
        {
            for (int j1=0; j1<len1; j1++)
            {
                r3.Push(iter1.Show_Key(), iter1.Show_Info());
                if(dir1) iter1++;
                else iter1--;
            }
        }
        if(!r2.Is_Empty())
        {
            for (int j2=0; j2<len2; j2++)
            {
                r3.Push(iter2.Show_Key(), iter2.Show_Info());
                if(dir2) iter2++;
                else iter2--;
            }
        }
    }

    return r3;
}


#endif // PRODUCE_H

