#include "header.h"

int main(int argc, char ** argv)
{
    commandline(argc, argv);
    parameter();
    cache_design();
    primary_value();

    if (ca2!=0)
    {
        cout <<"\nlevel-1 cache size :"<<(1<<ca1)<<'\t';
        cout <<"level-2 cache size :"<<(1<<ca2)<<endl;
        cout << "block size\t   :"<<(1<<blk1)<<'\t'<<'\t';
        cout << "block size\t   :"<<(1<<blk2)<<endl;
        cout << "associativity\t   :"<<(1<<asc1)<<'\t'<<'\t';
        cout << "associativity\t   :"<<(1<<asc2)<<endl;

        if (rp1==1)
        {cout << "replacement policy :"<<"LRU"<<'\t'<<'\t';}
        if (rp2==1)
        {cout << "replacement policy :"<<"LRU"<<endl;}

    }

    if (ca2==0)
    {
        cout <<"\nlevel-1 cache size :"<<(1<<ca1);
        cout << "\nblock size\t   :"<<(1<<blk1);
        cout << "\nassociativity\t   :"<<(1<<asc1);

        if (rp1==1)
        {cout << "\nreplacement policy :"<<"LRU";}

    }

    cout << "\ncore no:"<< coreno<< endl;
    
    if(protocol==0)
    {cout << "protocol: single-core"<< endl;}

    if(protocol==1)
    {cout << "protocol: mesi"<< endl;}

    if(protocol==2)
    {cout << "protocol: snoopy"<< endl;}

    if(protocol==3)
    {cout << "protocol: firefly"<< endl;}

    if (wp==1)
    {cout<<"write policy: write-back"<<endl;}

    if (wp==2)
    {cout<<"write policy: write-through"<<endl;}

    ifstream filename (argv[argc-1]);

    if(protocol==0)//Singal core
    {
        cout<<"\n\t-------- simulation started -------\n";

        while (filename >> core >> type >> adrs)
        {
            out2 = 2;
            adres_tag_index_block();
            level1_hitmiss_sc();
            //only_l1_sc();
            level1_sc();
            level2_sc();
        }

        log_sc();
    }

    else if (protocol==1)// multi-core protocol: mesi
    {
        cout<<"\n\t-------- simulation started -------\n";

        while (filename >> core >> type >> adrs)
        {
            if (ca2==0)
            {
                adres_tag_index_block();
                level1_hitmiss_mc();
                only_l1_mesi();
            }
            
            if(ca2!=0)
            {
                out2 = 2;
                adres_tag_index_block();
                level1_hitmiss_mc();
                level1_mesi();
                level2_mesi();
            }
        }
        if(ca2==0)
        {log_mesi_only_l1();}
        if(ca2!=0)
        {log_mesi();}
    }

     else if (protocol==2)// multi-core protocol: snoopy
    {
        cout<<"\n\t-------- simulation started -------\n";

        while (filename >> core >> type >> adrs)
        {
            if (ca2==0)
            {
                adres_tag_index_block();
                level1_hitmiss_mc();
                only_l1_snoopy();
            }
            
            if(ca2!=0)
            {
                out2 = 2;
                adres_tag_index_block();
                level1_hitmiss_mc();
                level1_snoopy();
                level2_snoopy();
            }
        }

        if(ca2==0)
        {log_mesi_only_l1();}
        if(ca2!=0)
        {log_mesi();}
    }

     else if (protocol==3)// multi-core protocol: mesi
    {
        cout<<"\n\t-------- simulation started -------\n";

        while (filename >> core >> type >> adrs)
        {
            if (ca2==0)
            {
                adres_tag_index_block();
                level1_hitmiss_mc();
                only_l1_firefly();
            }
            
            if(ca2!=0)
            {
                out2 = 2;
                adres_tag_index_block();
                level1_hitmiss_mc();
                level1_firefly();
                level2_firefly();
            }
        }

        if(ca2==0)
        {log_firefly_only_l1();}
        if(ca2!=0)
        {log_firefly();}
    }
}