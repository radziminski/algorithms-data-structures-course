#ifndef SPLIT_H
#define SPLIT_H
#include "Sequence.h"

template <typename Key, typename Info>
int Split (const Sequence<Key, Info> &source, int start,
           Sequence<Key, Info> &result1, int step1,
           Sequence<Key, Info> &result2, int step2)
{
    if(source.List_Length()==0)
    {
        std::cout<<"Source list is empty. Returning 0.\n";
        return 0;
    }
    if(start<0||start>=source.List_Length())
    {
        std::cout<<"Wrong variable 'start' given. Please enter non negative integer smaller than source list length. Returning 0.\n";
        return 0;
    }
    if (step1<0||step2<0)
    {
        if(step1<0) std::cout<<"Wrong variable 'step1' given. Please enter non negative integer. Returning 0 \n";
        if(step2<0) std::cout<<"Wrong variable 'step2' given. Please enter non negative integer. Returning 0 \n";
        return 0;
    }
    Sequence<Key, Info> r1, r2;
    int iter_position=0, counter=0;
    typename Sequence<Key, Info>::Iterator iter=source.ibegin();
    typename Sequence<Key, Info>::Iterator iter_end=source.iend();
    while((iter_position!=start)&&(iter!=iter_end))
    {
        iter_position++;
        iter++;
    }
    while (iter!=iter_end)
    {
        for (int i1=0; i1<step1; i1++)
        {
            if(iter==iter_end) break;
            r1.Push_Back(iter.Show_Key(), iter.Show_Data());
            counter++;
            iter++;
        }
        for (int i2=0; i2<step2; i2++)
        {
            if(iter==iter_end) break;
            r2.Push_Back(iter.Show_Key(), iter.Show_Data());
            counter++;
            iter++;
        }
    }
    result1=r1;
    result2=r2;
    return counter;

}


#endif // SPLIT_H
