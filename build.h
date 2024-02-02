       // t=tag, v=validity, db= dirty bit, stat = state of the data
       
        struct level1
        {
            int t1, v1, lru1, db1;
            int data1;
            char stat1;
        }; struct level1** cash1[4096];

        struct level2
        {
            int t2, v2, lru2, db2;
            char stat2;
        }; struct level2** cash2[4096];

        struct lookup1
        {
            int mcore1, mthread1;
            char mstat1;
        } ; struct lookup1 matchcore1[4096];

        struct lookup2
        {
            int mcore2, mthread2;
            char mstat2;
        } ; struct lookup2 matchcore2[4096];


        double bustraffic=0; double totalctoc=0; double totalins=0;
        double totalmissl1=0; double missratel1=0; double missratel2=0;
        double hitratel2=0; double totalrml1=0; double totalwml1=0;
        double totaliml1=0; double totalread1=0;  double totalcalll2=0;
        double totalmissl2=0; 

        double totalrhpl1=0;  double totalwhpl1=0;  double totalrhbl1=0; double totalwhbl1=0;
        double totalrml2=0; double totalwml2=0; double totaliml2=0;


        struct archive0
        {
            int rmem=0, wmem=0;
            int totalread = 0, totalwrite=0, totalins=0;
            int busmiss=0;
            
        }  cash0log;  

        struct archive1
        {
            double rhit1, whit1, rmiss1, wmiss1, ihit1, imiss1;

        } cash1log;

        struct archive2
        {
            double rhit2, whit2, rmiss2, wmiss2, ihit2, imiss2;
            
        } cash2log;

        struct archive3
        {
            double rhl1, whl1, rml1, wml1, ihl1, iml1;
            double rhl2, whl2, rml2, wml2, ihl2, iml2;

            double  mrate, emrate;            

            double rhb=0, whb=0, rmb=0, wmb=0, ihb=0, imb=0;
            int rhp1=0, whp1=0, ihp1=0,rhp2=0, whp2=0, ihp2=0;
            int mih1=0, eih1=0, sih1=0, mih2=0, eih2=0, sih2=0;            
            int mrh1=0, erh1=0, srh1=0, mrh2=0, erh2=0, srh2=0;
            int mwh1=0, ewh1=0, swh1=0, mwh2=0, ewh2=0, swh2=0;
            int vrh1=0, drh1=0, vwh1=0, dwh1=0, vih1=0, dih1=0;
            int vrh2=0, drh2=0, vwh2=0, dwh2=0, vih2=0, dih2=0;

            double bu=0, ctoc=0;
            int exchange=0;

        }; struct archive3 corelog[4096];
