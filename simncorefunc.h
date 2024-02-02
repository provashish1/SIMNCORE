using namespace std;

void commandline(int argc, char **argv);
void parameter();
void cache_design();
void primary_value();
void adres_tag_index_block();

void level1_hitmiss_sc();
void only_l1_sc();
void level1_sc();
void level2_sc();

void level1_hitmiss_mc();
void only_l1_mesi();
void level1_mesi();
void level2_mesi();
void only_l1_snoopy();
void level1_snoopy();
void level2_snoopy();
void only_l1_firefly();
void level1_firefly();
void level2_firefly();

int find_l2(int coreid2);

int highest_lru1();
int highest_lru2();
void update_lru1(int coreid1, int threadid1);
void check_lru1(int coreid1, int threadid1);
void check_lru2(int coreid2, int threadid2);
void update_lru2(int coreid2, int threadid2);
int searchcores1(int coreid1);
int searchcores2(int coreid2);

void log_sc_only_l1();
void log_sc();
void log_mesi_only_l1();
void log_mesi();
void log_firefly_only_l1();
void log_firefly();

void update_lru1(int coreid1, int threadid1)
{
  int up1, n;

  up1 = cash1[coreid1][threadid1][index1].lru1;
  n = 1 << asc1;

  for (int i = 0; i < n; i++)
  {
    if (cash1[coreid1][i][index1].lru1 < up1)
    {
      cash1[coreid1][i][index1].lru1++;
    }
  }

  cash1[coreid1][threadid1][index1].lru1 = 0;
}

void check_lru1(int coreid1, int threadid1)
{
  int check1, n;

  check1 = cash1[coreid1][threadid1][index1].lru1;
  n= 1 << asc1;

  for (int i = 0; i < n; i++)
  {
    if (cash1[coreid1][i][index1].lru1 > check1)
    {
      cash1[coreid1][i][index1].lru1--;
    }
  }

  cash1[coreid1][threadid1][index1].lru1 = (n-1);
}

void check_lru2(int coreid2,int threadid2)
{
  int check2, m;

  check2 = cash2[coreid2][threadid2][index2].lru2;
  m = 1 << asc2;

  for (int i = 0; i < m; i++)
  {
    if (cash2[coreid2][i][index2].lru2 > check2)
    {
      cash2[coreid2][i][index2].lru2--;
    }
  }

  cash2[coreid2][threadid2][index2].lru2 = (m-1);
}

void update_lru2(int coreid2, int threadid2)
{
  int up2, m;

  up2 = cash2[coreid2][threadid2][index2].lru2;
  m = 1 << asc2;

  for (int i = 0; i < m; i++)
  {
    if (cash2[coreid2][i][index2].lru2 < up2)
    {
      cash2[coreid2][i][index2].lru2++;
    }
  }

  cash2[coreid2][threadid2][index2].lru2 = 0;
}

int highest_lru2()
{
  int cc, m, hlthread2;

  cc = cash2[core][0][index2].lru2;
  m = 1 << asc2;
  for (int i = 0; i < m; i++)
  {
    if (cc <= cash2[core][i][index2].lru2)
    {
      hlthread2 = i;
      cc = cash2[core][i][index2].lru2;
    }
  }
  return hlthread2;
}

int highest_lru1()
{
  int aa, n, hlthread1, n = 1 << asc1;
  aa = cash1[core][0][index1].lru1;

  for (int i = 0; i < n; i++)
  {
    if (aa <= cash1[core][i][index1].lru1)
    {
      hlthread1 = i;
      aa = cash1[core][i][index1].lru1;
    }
  }
  return hlthread1;
}

int searchcores1(int coreid1)
{
  int n, match1=0, n=1<<asc1;

  for (int j=0; j<coreno;j++)
  {
    if (j!=coreid1)
    {
      for (int i=0; i<n;i++)
      {
        if (cash1[j][i][index1].v1==1)
        {
          if (cash1[j][i][index1].t1==tag1)
          {
            matchcore1[match1].mcore1=j;
            matchcore1[match1].mthread1=i;
            matchcore1[match1].mstat1=cash1[j][i][index1].stat1;
            match1++;
          }
        }
      }
    }
  }
  return match1;
}

int searchcores2(int coreid2)
{
  int m, match2=0, m=1<<asc2;

  for (int y=0; y<coreno;y++)
  {
    if (y!=coreid2)
    {
      for (int x=0; x<m;x++)
      {
        if (cash2[y][x][index2].v2==1)
        {
          if (cash2[y][x][index2].t2==tag2)
          {
            matchcore2[match2].mcore2=y;
            matchcore2[match2].mthread2=x;
            matchcore2[match2].mstat2=cash2[y][x][index2].stat2;
            match2++;
          }
        }
      }
    }
  }
  return match2;
}



int find_l2(int coreid2)
{
  int th2 = 0, m = 1 << asc2;

  for (int j = 0; j < m; j++)
  {
    if (cash2[coreid2][j][index2].v2 == 1)
    {
      if (cash2[coreid2][j][index2].t2 == tag2)
      {
        th2 = j;
        break;
      }
    }
  }
  return th2;
}

void commandline(int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
  {
    line = argv[i];
    if (line[0] == 45) // 45 is ASCII value of '-'
    {
      if (line[1] == 108) // 108 is ASCII value of 'l'
      {
        while (i == 1)
        {
          if (line[2] == 49) // 49 is ASCII value of '1'
          {
            i++;

            // Get_Cache_parameter(argv[i]);
            cmdl1 = argv[i];
          }

          else
          {
            std::cout << "error l-1 command" << std::endl;
            break;
          }
        }

        while (i == 3)
        {
          if (line[2] == 50) //// 50 is ASCII value of '2'
          {
            i++;

            // Get_Cache_parameter for level 2 (argv[i]);
            cmdl2 = argv[i];
          }

          else
          {
            std::cout << "error l-2 command" << std::endl;
            break;
          }
        }
      }

      else if (line[1] == 67) // 67 is ASCII value of 'C'
      {
        stringstream ss;
        ss << line[2];
        ss >> coreno1;
        coreno=coreno1;

        stringstream rr;
        rr<<line[3];
        rr>>coreno2;

        if(coreno2!=0)
        {coreno=coreno*10+coreno2;}
      }

      else if (line[1] == 80) // 80 is ASCII value of 'P'
      {
        stringstream pp;
        pp << line[2];
        pp >> protocol;
      }

      // for write policy
      else if(line[1]==87) // 87 is ascii value of "W"
      {
        stringstream qq;
        qq << line[2];
        qq >> wp;
      }
    }
  }
}

void parameter()
{
  // parameter for level-1
  int j = 0; int para1[5] = {0, 0, 0, 0, 0};
  
  for (int i = 0; i <= 4; i++)
  {
    if (cmdl1[0] != 58)
    {
      char m = cmdl1[j];
      para1[i] = (int)m - 48;
      j = j + 1;

      if (j < cmdl1.length())
      {
        m = cmdl1[j];
        while (m != 58)
        {
          para1[i] = para1[i] * 10;
          para1[i] = para1[i] + ((int)m - 48);
          j = j + 1;
          m = cmdl1[j];
        }
        j = j + 1;
      }
      else
      {
        break;
      }
    }
    else
    {
      cout << "command line error" << endl;
    }
  }

  ca1 = para1[0];
  blk1 = para1[1];
  asc1 = para1[2];
  rp1 = para1[3];
  ind1 = ca1 - blk1 - asc1;
  tbit1 = 32 - blk1 - ind1;

  // parameter for level-2
  int k = 0; int para2[5] = {0, 0, 0, 0, 0};
  
  for (int i = 0; i <= 4; i++)
  {
    if (cmdl2[0] != 58)
    {
      char m = cmdl2[k];
      para2[i] = (int)m - 48;
      k = k + 1;

      if (k < cmdl2.length())
      {
        m = cmdl2[k];
        while (m != 58)
        {
          para2[i] = para2[i] * 10;
          para2[i] = para2[i] + ((int)m - 48);
          k = k + 1;
          m = cmdl2[k];
        }
        k = k + 1;
      }
      else
      {
        break;
      }
    }
    else
    {
      cout << "command line error" << endl;
    }
  }

  ca2 = para2[0];
  blk2 = para2[1];
  asc2 = para2[2];
  rp2 = para2[3];
  ind2 = ca2 - blk2 - asc2;
  tbit2 = 32 - blk2 - ind2;
}

void cache_design()
{
  // level-1 cache

  for (int i = 0; i < coreno; i++)
  {
    cash1[i] = new struct level1 *[1 << asc1];

    for (int n = 0; n < (1 << asc1); n++)
    {
      cash1[i][n] = new struct level1[1 << ind1];
    }
  }

  // level-2 cache

  for (int x = 0; x < (1 << coreno); x++)
  {
    cash2[x] = new struct level2 *[1 << asc2];
    
    for (int m = 0; m < (1 << asc2); m++)
    {
      cash2[x][m] = new struct level2[1 << ind2];
    }
  }
}

void primary_value()
{
  // for level-1
  for (int i = 0; i < coreno; i++)
  {
    for (int j = 0; j < (1 << asc1); j++)
    {
      for (int k = 0; k < (1 << ind1); k++)
      {
        cash1[i][j][k].t1 = -1;
        cash1[i][j][k].v1 = 0;
        cash1[i][j][k].lru1 = j;
        cash1[i][j][k].db1 = 1;
        cash1[i][j][k].stat1 = 'i';
        cash1[i][j][k].data1 = -1;
      }
    }
  }

  // for level-2
  for (int x = 0; x < (1 << coreno); x++)
  {
    for (int y = 0; y < (1 << asc2); y++)
    {
      for (int z = 0; z < (1 << ind2); z++)
      {
        cash2[x][y][z].t2 = -1;
        cash2[x][y][z].v2 = 0;
        cash2[x][y][z].lru2 = y;
        cash2[x][y][z].db2 = 1;
        cash2[x][y][z].stat2 = 'i';
      }
    }
  }

  // assign value
  for (int i = 0; i < coreno; i++)
  {
    corelog[i].rhl1 = 0;
    corelog[i].whl1 = 0;
    corelog[i].rml1 = 0;
    corelog[i].wml1 = 0;
    corelog[i].ihl1 = 0;
    corelog[i].iml1 = 0;

    corelog[i].rhl2 = 0;
    corelog[i].whl2 = 0;
    corelog[i].rml2 = 0;
    corelog[i].wml2 = 0;
    corelog[i].ihl2 = 0;
    corelog[i].iml2 = 0;
  }
}

void adres_tag_index_block()
{
  dec_adrs = std::stoul(adrs, nullptr, 16);

  // get tag, index, block address in decimal for l1 and l2
  block1 = dec_adrs & ((1 << blk1) - 1);
  index1 = (dec_adrs >> blk1) & ((1 << ind1) - 1);
  tag1 = (dec_adrs >> (ind1 + blk1)) & ((1 << tbit1) - 1);

  block2 = dec_adrs & ((1 << blk2) - 1);
  index2 = (dec_adrs >> blk2) & ((1 << ind2) - 1);
  tag2 = (dec_adrs >> (ind2 + blk2)) & ((1 << tbit2) - 1);
}



void level1_hitmiss_sc()
{
  int a = 2, n = 1 << asc1;

  for (int i = 0; i < n; i++)
  {
    if (cash1[core][i][index1].v1 == 1)
    {
      if (cash1[core][i][index1].t1 == tag1) // hit in level-1
      {
        ht1 = i;
        a = 1;
        out1 = 1;

        if (type == 'z') {corelog[core].ihl1++;}
        if (type == 'r'){corelog[core].rhl1++;}
        if (type == 'w'){corelog[core].whl1++;}

        break;
      }
    }
  }

  if (a == 2) // miss in level-1
  {
    out1 = 0;

    // log
    if (type == 'z') {corelog[core].iml1++;}

    if (type == 'r') {corelog[core].rml1++;}

    if (type == 'w'){corelog[core].wml1++;}
  }
}

void only_l1_sc()
{
  if (out1 == 1) // when hit in level-1
  {
    if (type == 'z'&& wp==1) {update_lru1(core, ht1);}

    if (type == 'z'&& wp==2) {update_lru1(core, ht1);}

    if (type == 'r' && wp==1) {update_lru1(core, ht1);}

    if (type == 'r' && wp==2) {update_lru1(core, ht1);}

    if (type == 'w' && wp==1)
    {
      cash1[core][ht1][index1].db1 = 1;
      update_lru1(core, ht1);
    }

    if (type == 'w' && wp==2)
    {
      cash0log.wmem++;
      update_lru1(core, ht1);
    }
  }

  if (out1 == 0) // when miss in level-1
  {
    // copy data from main memory
    // find highest lru in level-1
    tt1 = highest_lru1();

    if (type == 'z' && wp==1)
    {
      cash0log.rmem++;

      if (cash1[core][tt1][index1].db1==0)
      {
        //copy data from memory to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1 = 1;
        cash1[core][tt1][index1].db1=0;
      }

      if (cash1[core][tt1][index1].db1==1)
      {
        cash0log.wmem++;

        //copy data from memory to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1 = 1;
        cash1[core][tt1][index1].db1=0;
      }
      update_lru1(core, tt1);
    }

    if (type == 'z' && wp==2)
    {
      cash0log.rmem++;

      // copy from memory to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1 = 1;
      update_lru1(core, tt1);
    }

    if (type == 'r' && wp==1)
    {
      cash0log.rmem++;

      if (cash1[core][tt1][index1].db1==0)
      {
        //copy data from memory to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1 = 1;
        cash1[core][tt1][index1].db1=0;
      }

      if (cash1[core][tt1][index1].db1==1)
      { 
        cash0log.wmem++;

        //copy data from memory to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1 = 1;
        cash1[core][tt1][index1].db1=0;
      }
      update_lru1(core, tt1);
    }

    if (type == 'r' && wp==2)
    {
      cash0log.rmem++;

      // copy from memory to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1 = 1;

      update_lru1(core, tt1);
    }      

    if (type == 'w' && wp==1)
    {
      if (cash1[core][tt1][index1].db1==0)
      { 
        // write data from processor to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1 = 1;
        cash1[core][tt1][index1].db1=1;
      }

      if (cash1[core][tt1][index1].db1==1)
      {
        cash0log.wmem++;
        
        // copy data from processor to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1 = 1;
      }
      update_lru1(core, tt1);
    }

    if (type == 'w' && wp==2)
    {
      cash0log.wmem++;
    }
  }
}

void level1_sc()
{
  if (out1 == 1) // when hit in level-1
  {
    //find copy in l2
    th2=find_l2(core);

    if (type=='z'&& wp==1)
    {
      update_lru1(core, ht1);
    }

    if (type == 'z'&& wp==2) // write-through
    {
      update_lru1(core, ht1);
    }

    if (type == 'r' && wp==1)
    {
      update_lru1(core, ht1);
    }

    if (type == 'r' && wp==2) // write-through
    {
      update_lru1(core, ht1);
    }

    if (type == 'w' && wp==1)
    {
      cash1[core][ht1][index1].data1 = block1; // copy data to cache from processor
      cash1[core][ht1][index1].db1 = 1;        // dirtybit =1

      //update l2
      cash2[core][th2][index2].db2 = 1;

      update_lru1(core, ht1);
      update_lru2(core, th2);
    }

    if (type == 'w' && wp==2) //write-through
    {
      cash1[core][ht1][index1].data1 = block1; // copy data to cache from processor

      cash2[core][tt2][index2].t2=tag2;
      cash2[core][tt2][index2].v2=1;

      //log
      cash0log.wmem++;

      update_lru1(core, ht1);
      update_lru2(core, tt2);
    }
  }

  if (out1 == 0) // when miss in level-1 check in level-2
  {
    // find cache hit or miss in level-2

    // find highest lru in level-1
    tt1 = highest_lru1();

    //find highest lru in level-2
    tt2 = highest_lru2();

    b = 0, m = 1 << asc2;
    for (int i = 0; i < m; i++)
    {
      if (cash2[core][i][index2].v2 == 1)
      {
        if (cash2[core][i][index2].t2 == tag2)
        {
          ht2 = i;
          b = 1;
          out2 = 1; // in case of hit in level-2

          break;
        }
      }

      if (b == 0) // in case of miss in level-2
      {
        out2 = 0;
      }
    }
  }
}

void level2_sc()
{
  if (out2==1) // when hit in level-2
  {
    //log
    if (type == 'z')
    {corelog[core].ihl2++;}

    if (type == 'r')
    {corelog[core].rhl2++;}

    if (type == 'w')
    {corelog[core].whl2++;}

    if (type == 'z' && wp==1)
    {
      //copy from level-2 hit thread to l-1 target thread
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1 = block1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].db1=0;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type == 'z' && wp==2) // write-through
    {
      //copy from level-2 hit thread to l-1 target thread
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1 = block1;
      cash1[core][tt1][index1].v1=1;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type == 'r' && wp==1)
    {
      //copy from level-2 hit thread to l-1 target thread
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1 = block1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].db1=0;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type == 'r' && wp==2) // write-through
    {
      //copy from level-2 hit thread to l-1 target thread
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1 = block1;
      cash1[core][tt1][index1].v1=1;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type == 'w' && wp==1) //write-back
    {
      //copy from l-2 hit thread to l-1 target thread
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;

      // copy data to cache from processor
      cash1[core][tt1][index1].data1 = block1;
      cash1[core][tt1][index1].db1=1;

      //update l2
      cash2[core][ht2][index2].t2=tag2;
      cash2[core][ht2][index2].db2=1;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type == 'w' && wp==2) // write-through
    {
      //update l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].data1 = block1;

      //update l2
      cash2[core][ht2][index2].t2=tag2;

      //log
      cash0log.wmem++;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }
  }

  if (out2==0) // miss in level-2
  {
    // log
    if (type == 'z')
    {corelog[core].iml2++;}

    if (type == 'r')
    {corelog[core].rml2++;}

    if (type == 'w')
    {corelog[core].wml2++;}

    if (type == 'z' && wp==1) //write-back
    {
      if (cash1[core][tt1][index1].db1==1)
      {
        // log
        // update main memory
        cash0log.wmem++;
      }


      //copy data from mmemory to tt1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1=block1;
      cash1[core][tt1][index1].v1 = 1;
      cash1[core][tt1][index1].db1=0;

      // upate l2 tt2
      cash2[core][tt2][index2].t2=tag2;
      cash2[core][tt2][index2].v2=1;
      cash2[core][tt2][index2].db2=0;
      
      // log 
      cash0log.rmem++;

      update_lru1(core, tt1);
      update_lru2(core, tt2);
    }

    if (type == 'z' && wp==2) // write-through / no allocate
    {
      // copy from tt2 to tt1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1=block1;
      cash1[core][tt1][index1].v1 = 1;

      // update l2
      cash2[core][tt2][index2].t2=tag2;
      cash2[core][tt2][index2].v2=1;

      // log
      cash0log.rmem++;

      update_lru1(core, tt1);
      update_lru2(core, tt2);
    }

    if (type == 'r' && wp==1) //write-back
    {
      if (cash1[core][tt1][index1].db1==1)
      {
        // log
        // update main memory
        cash0log.wmem++;
      }


      //copy data from mmemory to tt1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1=block1;
      cash1[core][tt1][index1].v1 = 1;
      cash1[core][tt1][index1].db1=0;

      // upate l2 tt2
      cash2[core][tt2][index2].t2=tag2;
      cash2[core][tt2][index2].v2=1;
      cash2[core][tt2][index2].db2=0;
      
      // log 
      cash0log.rmem++;

      update_lru1(core, tt1);
      update_lru2(core, tt2);
    }

    if (type == 'r' && wp==2) // write-through / no allocate
    {
       // copy from tt2 to tt1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].data1=block1;
      cash1[core][tt1][index1].v1 = 1;

      // update l2
      cash2[core][tt2][index2].t2=tag2;
      cash2[core][tt2][index2].v2=1;

      // log
      cash0log.rmem++;

      update_lru1(core, tt1);
      update_lru2(core, tt2);
    }

    if (type == 'w' && wp==1)
    {
      if (cash1[core][tt1][index1].db1==1)
      {
          // log
          // update main memory
          cash0log.wmem++;
      }

      // after write operation to tt1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1 = 1;
      cash1[core][tt1][index1].data1=block1;
      cash1[core][tt1][index1].db1=1;

      // update l2
      cash2[core][tt2][index2].t2=tag2;
      cash2[core][tt2][index2].v2=1;
      cash2[core][tt2][index2].db2=1;

      update_lru1(core, tt1);
      update_lru2(core, tt2);
    }

    if (type == 'w' && wp==2)
    {
      //log
      cash0log.wmem++;
    }
  }
}

void level1_hitmiss_mc()
{
  int a=2, n=1<<asc1;

  for (int i=0;i<n;i++)
  {
    if (cash1[core][i][index1].v1==1)
    {
      if (cash1[core][i][index1].t1==tag1)
      {
        a=1;
        out1=1;
        ht1=i;

        // log
        if (type=='z')
        {corelog[core].ihl1++;}

        if (type=='r')
        {corelog[core].rhl1++;}

        if (type=='w')
        {corelog[core].whl1++;}

        break;
      }
    }
  }

  if (a==2)
  {
    out1=0;

    // log
    if (type=='z')
    {corelog[core].iml1++;}

    if (type=='r')
    {corelog[core].rml1++;}

    if (type=='w')
    {corelog[core].wml1++;}
  }
}

void only_l1_mesi()
{
  if (out1==1) //in case of hit in level-1 private core
  {

    if (type =='z')
    {
      // log
      corelog[core].ihp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mih1++;}

      if (cash1[core][ht1][index1].stat1=='e')
      {corelog[core].eih1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].sih1++;}
    }

    if (type =='r')
    {
      // log
      corelog[core].rhp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mrh1++;}

      if (cash1[core][ht1][index1].stat1=='e')
      {corelog[core].erh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].srh1++;}
    }

    if (type == 'w')
    {
      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mwh1++;}

      if (cash1[core][ht1][index1].stat1=='e')
      {corelog[core].ewh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].swh1++;}

      // invalidate other copies
      if (cash1[core][ht1][index1].stat1=='s')
      {
        //send invalidation signal in l1
        int totalmatch1 = 0;
        totalmatch1=searchcores1(core);

        for(int i=0; i<totalmatch1; i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        //log
        if(totalmatch1!=0)
        {
          corelog[core].bu++; //update bus
        }
      }

      //write to private l1 cache
      cash1[core][ht1][index1].stat1='m'; 
    }
    
    update_lru1(core, ht1);
  }

  if (out1==0) //miss in l1
  {
    int tt1 = 0; tt1 = highest_lru1(); //highest lru line to replace
    // find hit or miss in bus
    int totalmatch1 = 0;
    totalmatch1=searchcores1(core);
    
    if(totalmatch1!=0) //hit in bus
    {
      // log
      corelog[core].ctoc++;

      if (type=='z')
      {
        //log
        corelog[core].ihb++;

        //copy l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        //change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        update_lru1(core, tt1);
      }

      if (type=='r')
      {
        //log
        corelog[core].rhb++;

        // copy l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        // change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        update_lru1(core, tt1); 
      }

      if (type=='w')
      {
        //log
        corelog[core].whb++;
  
        // copy from bus to l-1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;

        // write to l1
        cash1[core][tt1][index1].stat1='m';

        //invalidate copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }
            
        update_lru1(core, tt1);
      }
    }

    if(totalmatch1==0) //miss in bus
    {
      if (type == 'z')
      {
        // log
        corelog[core].imb++;

        //copy from memory to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        update_lru1(core, tt1);

      }

      if (type == 'r')
      {
        // log
        corelog[core].rmb++;

        //copy from memory to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        update_lru1(core, tt1);
      }

      if (type == 'w')
      {
        // log
        corelog[core].wmb++;

        //copy from memory to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
              
        // write operation in tt1
        cash1[core][tt1][index1].stat1='m';

        update_lru1(core, tt1);
      }
    }
  }
} //end_only_l1_mesi

void level1_mesi()
{
  if (out1==1) //in case of hit in level-1 private core
  {
    //find copy in l2
    th2=find_l2(core);

    if (type =='z')
    {
      // log
      corelog[core].ihp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mih1++;}

      if (cash1[core][ht1][index1].stat1=='e')
      {corelog[core].eih1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].sih1++;}
    }

    if (type =='r')
    {
      // log
      corelog[core].rhp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mrh1++;}

      if (cash1[core][ht1][index1].stat1=='e')
      {corelog[core].erh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].srh1++;}
    }

    if (type == 'w')
    {
      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mwh1++;}

      if (cash1[core][ht1][index1].stat1=='e')
      {corelog[core].ewh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].swh1++;}

      // invalidate other copies
      if (cash1[core][ht1][index1].stat1=='s')
      {
        //send invalidation signal in l1
        int totalmatch1 = 0;
        totalmatch1=searchcores1(core);

        for(int i=0; i<totalmatch1; i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        //send invalidation signal in l2
        int totalmatch2 = 0;
        totalmatch2=searchcores2(core);
        for(int i=0; i<totalmatch2; i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='i';
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].v2=0;
          check_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }

        //log
        if(totalmatch2!=0)
        {
          corelog[core].bu++; //update bus
        }
      }

      //write to private l1 cache
      cash1[core][ht1][index1].stat1='m'; 

      //update private l2 cache
      cash2[core][th2][index2].stat2='m';
    }
    
    update_lru1(core, ht1);
    update_lru2(core, th2);
  }

  if (out1==0) // when miss in level-1 private core
  { 
    int tt1 = 0; tt1 = highest_lru1(); //highest lru line to replace  

    // move to level-2 private cache

    // check hit or miss in level-2
    b = 2, m = 1 << asc2;
    for (int i = 0; i < m; i++)
    {
      if (cash2[core][i][index2].v2 == 1)
      {
        if (cash2[core][i][index2].t2 == tag2)
        {
          ht2 = i;
          b = 1;
          out2 = 1; // in case of hit in level-2

          if (type=='z')
          {corelog[core].ihl2++;} //log

          if (type=='r')
          {corelog[core].rhl2++;} //log

          if (type=='w')
          {corelog[core].whl2++;} //log

          break;
        }
      }
    }

    if (b == 2) // in case of miss in level-2
    {
      out2 = 0;

      if (type=='z')
      {corelog[core].iml2++;} //log

      if (type=='r')
      {corelog[core].rml2++;} //log

      if (type=='w')
      {corelog[core].wml2++;} //log
    }
  }
}

void level2_mesi()
{
  if (out2 == 1) // hit in level-2
  {
    if (type=='z')
    {
      corelog[core].ihp2++; //log

      if (cash2[core][ht2][index2].stat2=='m')
      {corelog[core].mih2++;}

      if (cash2[core][ht2][index2].stat2=='e')
      {corelog[core].eih2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].sih2++;}

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].stat1 = cash2[core][ht2][index2].stat2;
      //cash1[core][tt1][index1].data1=block1;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type=='r')
    {
      // log
      corelog[core].rhp2++;

      if (cash2[core][ht2][index2].stat2=='m')
      {corelog[core].mrh2++;}

      if (cash2[core][ht2][index2].stat2=='e')
      {corelog[core].erh2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].srh2++;}

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].stat1 = cash2[core][ht2][index2].stat2;
      //cash1[core][tt1][index1].data1=block1;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type=='w')
    {

      // log
      corelog[core].whp2++;

      if (cash2[core][ht2][index2].stat2=='m')
      {corelog[core].mwh2++;}

      if (cash2[core][ht2][index2].stat2=='e')
      {corelog[core].ewh2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].swh2++;}

      if( cash2[core][ht2][index2].stat2!='s')
      {
        //invalidate other copies
        //invalid copies in bus
        int totalmatch1 = 0;
        totalmatch1=searchcores1(core);
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        //invalid copies in bus
        int totalmatch2 = 0;
        totalmatch2=searchcores2(core);
        for(int i=0; i<totalmatch2;i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='i';
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].v2=0;
          check_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }

        //log
        if(totalmatch1!=0)
        {
          corelog[core].bu++; //update bus
        }
      }

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;

      //write operation in tt1
      cash1[core][tt1][index1].stat1='m';
      //cash1[core][tt1][index1].data1=block1;

      // update l2
      cash2[core][ht2][index2].stat2='m';

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }  
  }

  if (out2 == 0) // miss in level-2
  {
    // find highest lru in L2
    int tt2=0; tt2=highest_lru2();

    // find hit or miss in bus
    int totalmatch2 = 0;
    totalmatch2=searchcores2(core);
    
    if(totalmatch2!=0) //hit in bus
    {
      // log
      corelog[core].ctoc++;

      if (type=='z')
      {        
        //log
        corelog[core].ihb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        //copy from bus to target l2
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='s'; 

        //copy l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        //change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        // change state to shared of copies in bus
        int totalmatch2=0;
        totalmatch2=searchcores2(core);
        for (int i=0; i<totalmatch2; i++)
        {
          if (matchcore2[i].mstat2!='s')
          {
            cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          }
        }

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }

      if (type=='r')
      {
        //log
        corelog[core].rhb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory

          cash2[core][tt2][index2].stat2='e';
        }

        //copy from bus hit thread to target l2
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='s'; 

        // copy l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        // change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        // state change in other cores l2
        int totalmatch2=0;
        totalmatch2=searchcores2(core);
        for (int i=0; i<totalmatch2; i++)
        {
          if (matchcore2[i].mstat2!='s')
          {
            cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          }
        }

        update_lru1(core, tt1);
        update_lru2(core, tt2);  
      }

      if (type=='w')
      { 
        //log
        corelog[core].whb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory

          cash2[core][tt2][index2].stat2='e';
        }

        //write operation to target l1 and l2 cache
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='m';

        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='m';

        //invalid copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        int totalmatch2=0;
        totalmatch2=searchcores2(core);
        for(int i=0; i<totalmatch2;i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='i';
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].v2=0;
          check_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }
            
        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }
    }

    if(totalmatch2==0) //miss in bus
    {
      // log
      cash0log.busmiss++;

      if (type == 'z')
      {
        // log
        corelog[core].imb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l1 and l2 cache
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='e';

        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='e';

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }

      if (type == 'r')
      {
        // log
        corelog[core].rmb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l1 and l2 cache
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='e';

        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='e';

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }

      if (type == 'w')
      {
        // log
        corelog[core].wmb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l1 and l2 cache
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='m';

        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='m';

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }
    }
  }   
}

// snoopy protocol
void only_l1_snoopy()
{
  if (out1==1) //in case of hit in level-1 private core
  {

    if (type =='z')
    {
      // log
      corelog[core].ihp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mih1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].sih1++;}
    }

    if (type =='r')
    {
      // log
      corelog[core].rhp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mrh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].srh1++;}
    }

    if (type == 'w')
    {
      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mwh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].swh1++;}

      // invalidate other copies
      if (cash1[core][ht1][index1].stat1=='s')
      {
        //send invalidation signal in l1
        int totalmatch1 = 0;
        totalmatch1=searchcores1(core);

        for(int i=0; i<totalmatch1; i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        //log
        if(totalmatch1!=0)
        {
          corelog[core].bu++; //update bus
        }
      }

      //write to private l1 cache
      cash1[core][ht1][index1].stat1='m'; 
    }
    
    update_lru1(core, ht1);
    
  }

  if (out1==0) //miss in l1
  {
    int tt1 = 0; tt1 = highest_lru1(); //highest lru line to replace
    // find hit or miss in bus
    int totalmatch1 = 0;
    totalmatch1=searchcores1(core);
    
    if(totalmatch1!=0) //hit in bus
    {
      // log
      corelog[core].ctoc++;

      if (type=='z')
      {
        //log
        corelog[core].ihb++;

        //copy l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        //change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        update_lru1(core, tt1);
      }

      if (type=='r')
      {
        //log
        corelog[core].rhb++;

        // copy l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        // change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        update_lru1(core, tt1); 
      }

      if (type=='w')
      {
        //log
        corelog[core].whb++;
  
        // copy from bus to l-1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;

        // write to l1
        cash1[core][tt1][index1].stat1='m';

        //invalidate copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }
            
        update_lru1(core, tt1);
      }
    }

    if(totalmatch1==0) //miss in bus
    {
      // log
      cash0log.busmiss++;

      if (type == 'z')
      {
        // log
        corelog[core].imb++;

        //copy from memory to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        update_lru1(core, tt1);

      }

      if (type == 'r')
      {
        // log
        corelog[core].rmb++;

        //copy from memory to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        update_lru1(core, tt1);
      }

      if (type == 'w')
      {
        // log
        corelog[core].wmb++;

        //copy from memory to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
              
        // write operation in tt1
        cash1[core][tt1][index1].stat1='m';

        update_lru1(core, tt1);
      }
    }
  }
} //end_only_l1_snoopy

void level1_snoopy()
{
  if (out1==1) //in case of hit in level-1 private core
  {
    //find copy in l2
    th2=find_l2(core);

    if (type =='z')
    {
      // log
      corelog[core].ihp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mih1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].sih1++;}
    }

    if (type =='r')
    {
      // log
      corelog[core].rhp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mrh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].srh1++;}
    }

    if (type == 'w')
    {
      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='m')
      {corelog[core].mwh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].swh1++;}

      // invalidate other copies
      if (cash1[core][ht1][index1].stat1=='s')
      {
        //send invalidation signal in l1
        int totalmatch1 = 0;
        totalmatch1=searchcores1(core);

        for(int i=0; i<totalmatch1; i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        //send invalidation signal in l2
        int totalmatch2 = 0;
        totalmatch2=searchcores2(core);
        for(int i=0; i<totalmatch2; i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='i';
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].v2=0;
          check_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }

        //log
        if(totalmatch1!=0)
        {
          corelog[core].bu++; //update bus
        }
      }

      //write to private l1 cache
      cash1[core][ht1][index1].stat1='m'; 

      //update private l2 cache
      cash2[core][th2][index2].stat2='m';
    }
    
    update_lru1(core, ht1);
    update_lru2(core, th2);
  }

  if (out1==0) // when miss in level-1 private core
  { 
    int tt1 = 0; tt1 = highest_lru1(); //highest lru line to replace  

    // move to level-2 private cache

    // check hit or miss in level-2
    b = 2, m = 1 << asc2;
    for (int i = 0; i < m; i++)
    {
      if (cash2[core][i][index2].v2 == 1)
      {
        if (cash2[core][i][index2].t2 == tag2)
        {
          ht2 = i;
          b = 1;
          out2 = 1; // in case of hit in level-2

          // log
          if (type=='z')
          {corelog[core].ihl2++;}

          if (type=='r')
          {corelog[core].rhl2++;}

          if (type=='w')
          {corelog[core].whl2++;}

          break;
        }
      }
    }

    if (b == 2) // in case of miss in level-2
    {
      out2 = 0;

      //log
      if (type=='z')
      {corelog[core].iml2++;}

      if (type=='r')
      {corelog[core].rml2++;}

      if (type=='w')
      {corelog[core].wml2++;}
    }
  }
}

void level2_snoopy()
{
  if (out2 == 1) // hit in level-2
  {
    // log 
    corelog[core].exchange++;

    if (type=='z')
    {
      // log
      corelog[core].ihp2++;

      if (cash2[core][ht2][index2].stat2=='m')
      {corelog[core].mih2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].sih2++;}

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].stat1 = cash2[core][ht2][index2].stat2;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type=='r')
    {
      // log
      corelog[core].rhp2++;

      if (cash2[core][ht2][index2].stat2=='m')
      {corelog[core].mrh2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].srh2++;}

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].stat1 = cash2[core][ht2][index2].stat2;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type=='w')
    {

      // log
      corelog[core].whp2++;

      if (cash2[core][ht2][index2].stat2=='m')
      {corelog[core].mwh2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].swh2++;}

      if( cash2[core][ht2][index2].stat2!='s')
      {
        //invalidate other copies
        //invalid copies in bus
        int totalmatch1 = 0;
        totalmatch1=searchcores1(core);
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        //invalid copies in bus
        int totalmatch2 = 0;
        totalmatch2=searchcores2(core);
        for(int i=0; i<totalmatch2;i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='i';
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].v2=0;
          check_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }

        //log
        if(totalmatch2!=0)
        {
          corelog[core].bu++; //update bus
        }
      }

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;

      //write operation in tt1
      cash1[core][tt1][index1].stat1='m';

      // update l2
      cash2[core][ht2][index2].stat2='m';

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }  
  }

  if (out2 == 0) // miss in level-2
  {
    // find highest lru in L2
    int tt2=0; tt2=highest_lru2();

    // find hit or miss in bus
    int totalmatch2 = 0;
    totalmatch2=searchcores2(core);
    
    if(totalmatch2!=0) //hit in bus
    {
      // log
      corelog[core].ctoc++;

      if (type=='z')
      {        
        //log
        corelog[core].ihb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        //copy from bus to target l2
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='s'; 

        //copy bus to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        //change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        // change state to shared of copies in bus
        int totalmatch2=0;
        totalmatch2=searchcores2(core);
        for (int i=0; i<totalmatch2; i++)
        {
          if (matchcore2[i].mstat2!='s')
          {
            cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          }
        }

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }

      if (type=='r')
      { 
        //log
        corelog[core].rhb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        //copy from bus hit thread to target l2
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='s'; 

        // copy l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';
        //cash1[core][tt1][index1].data1=block1;

        // change state to shared of copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        // state change in other cores l2
        int totalmatch2=0;
        totalmatch2=searchcores2(core);
        for (int i=0; i<totalmatch2; i++)
        {
          if (matchcore2[i].mstat2!='s')
          {
            cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          }
        }

        update_lru1(core, tt1);
        update_lru2(core, tt2);  
      }

      if (type=='w')
      { 
        //log
        corelog[core].whb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        //copy from other hit thread to target l2 and target l1
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
  
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;

        // write to l1
        cash1[core][tt1][index1].stat1='m';

        //update l2
        cash2[core][tt2][index2].stat2='m';

        //invalid copies in bus
        int totalmatch1=0;
        totalmatch1=searchcores1(core);
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='i';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=0;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        int totalmatch2=0;
        totalmatch2=searchcores2(core);
        for(int i=0; i<totalmatch2;i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='i';
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].v2=0;
          check_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }
            
        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }
    }

    if(totalmatch2==0) //miss in bus
    {
      if (type == 'z')
      {
        // log
        corelog[core].imb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l2
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='s';

        //copy from tt2 to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }

      if (type == 'r')
      {
        // log
        corelog[core].rmb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to TT2
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='s';

        //copy from tt2 to tt1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }

      if (type == 'w')
      {
        // log
        corelog[core].wmb++;

        if (cash2[core][tt2][index2].stat2=='m')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l2
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        

        //copy from l2 to l1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
              
        // write operation in tt1
        cash1[core][tt1][index1].stat1='m';

        //update l2
        cash2[core][tt2][index2].stat2='m';

        update_lru1(core, tt1);
        update_lru2(core, tt2);
      }
    }
  }   
}

// firefly protocol
void only_l1_firefly()
{
  if (out1==1) //in case of hit in level-1 private core
  {
    if (type =='r')
    {
      // log
      corelog[core].rhp1++;

      if (cash1[core][ht1][index1].stat1=='v')
      {corelog[core].vrh1++;}

      if (cash1[core][ht1][index1].stat1=='d')
      {corelog[core].drh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].srh1++;}
    }

    if (type == 'w')
    {
      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='v')
      {corelog[core].vwh1++;}

      if (cash1[core][ht1][index1].stat1=='d')
      {corelog[core].dwh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].swh1++;}

      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='v')
      {
        cash1[core][ht1][index1].stat1='d';
      }

      else if (cash1[core][ht1][index1].stat1=='s')
      {        
        int totalmatch1=0;
        totalmatch1=searchcores1(core);

        if (totalmatch1=!0)
        {
          cash1[core][ht1][index1].stat1='s';

          //log
          corelog[core].bu++;
        }

        if (totalmatch1==0)
        {
          cash1[core][ht1][index1].stat1='d';
        }
      }
      // change
      cash1[core][ht1][index1].data1=block1;
    }
    update_lru1(core,ht1);
  }

  if (out1==0) // when miss in level-1 private core
  {
    int tt1, totalmatch1=0;
    
    tt1 = highest_lru1();
    totalmatch1 = searchcores1(core);

    if (totalmatch1!=0) // hit in level-1 other cores
    {
      // log
      corelog[core].ctoc++;

      if (type =='r')
      {
        // log
        corelog[core].rhb++;

        // copy from other hit thread to target thread in l-1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='s';
        cash1[core][tt1][index1].data1=block1;

        // change state for other cores to 'shared'
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        //log
        corelog[core].bu++;

        update_lru1(core, tt1);
      }

      if (type =='w')
      {
        // log
        corelog[core].whb++;

        // copy from other hit thread to target thread in l-1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;

        // after write operation
        cash1[core][tt1][index1].stat1='s';
        cash1[core][tt1][index1].data1=block1;

        // invalid other copies
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=1;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        //log
        corelog[core].bu++;

        update_lru1(core, tt1);
      }
    }

    if (totalmatch1==0) // miss in level-1 private and other cores
    {
      if (type=='r')
      {
        //log
        corelog[core].rmb++;

        //copy from memory to level-1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='v';
        cash1[core][tt1][index1].data1=block1;
        
        update_lru1(core, tt1);
      }
      
      if (type=='w')
      {
        //log
        corelog[core].wmb++;

        //copy from processor to level-1
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].data1=block1;
        cash1[core][tt1][index1].stat1='d';
        
        update_lru1(core, tt1);
        
      }
    }
  }
}

void level1_firefly()
{
  if (out1==1) //in case of hit in level-1 private core
  {
    if (type =='z')
    {
      // log
      corelog[core].ihp1++;

      if (cash1[core][ht1][index1].stat1=='v')
      {corelog[core].vrh1++;}

      if (cash1[core][ht1][index1].stat1=='d')
      {corelog[core].drh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].srh1++;}
    }

    if (type =='r')
    {
      // log
      corelog[core].rhp1++;

      if (cash1[core][ht1][index1].stat1=='v')
      {corelog[core].vrh1++;}

      if (cash1[core][ht1][index1].stat1=='d')
      {corelog[core].drh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].srh1++;}
    }

    if (type == 'w')
    {
      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='v')
      {corelog[core].vwh1++;}

      if (cash1[core][ht1][index1].stat1=='d')
      {corelog[core].dwh1++;}

      if (cash1[core][ht1][index1].stat1=='s')
      {corelog[core].swh1++;}

      // log
      corelog[core].whp1++;

      if (cash1[core][ht1][index1].stat1=='v')
      {
        cash1[core][ht1][index1].stat1='d';
        cash2[core][th2][index2].stat2='d';
      }

      else if (cash1[core][ht1][index1].stat1=='s')
      {        
        int totalmatch1=0;
        totalmatch1=searchcores1(core);

        int totalmatch2 = 0;
        totalmatch2=searchcores2(core);

        if (totalmatch2=!0)
        {
          cash1[core][ht1][index1].stat1='s';
          cash2[core][th2][index2].stat2='s';

          //log
          corelog[core].bu++;
        }

        if (totalmatch2==0)
        {
          cash1[core][ht1][index1].stat1='d';
          cash2[core][th2][index2].stat2='d';
        }
      }
    }

    update_lru1(core,ht1);
    update_lru1(core,th2);
  }

  if (out1==0) // when miss in level-1 private core
  { 
    int tt1 = 0; tt1 = highest_lru1(); //highest lru line to replace  

    // move to level-2 private cache

    // check hit or miss in level-2
    b = 2, m = 1 << asc2;
    for (int i = 0; i < m; i++)
    {
      if (cash2[core][i][index2].v2 == 1)
      {
        if (cash2[core][i][index2].t2 == tag2)
        {
          ht2 = i;
          b = 1;
          out2 = 1; // in case of hit in level-2

          // log
          if (type=='z')
          {corelog[core].ihl2++;}

          if (type=='r')
          {corelog[core].rhl2++;}

          if (type=='w')
          {corelog[core].whl2++;}

          break;
        }
      }
    }

    if (b == 2) // in case of miss in level-2
    {
      out2 = 0;

      //log
      if (type=='z')
      {corelog[core].iml2++;}

      if (type=='r')
      {corelog[core].rml2++;}

      if (type=='w')
      {corelog[core].wml2++;}
    }
  }
}



void level2_firefly()
{
  if (out2 == 1) // hit in level-2
  {
    if (type=='z')
    {
      // log
      corelog[core].ihp2++;

      if (cash2[core][ht2][index2].stat2=='d')
      {corelog[core].dih2++;}

      if (cash2[core][ht2][index2].stat2=='v')
      {corelog[core].vih2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].sih2++;}

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].stat1 = cash2[core][ht2][index2].stat2;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type=='r')
    {
      // log
      corelog[core].rhp2++;

      if (cash2[core][ht2][index2].stat2=='d')
      {corelog[core].drh2++;}

      if (cash2[core][ht2][index2].stat2=='v')
      {corelog[core].vrh2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].srh2++;}

      // copy data from l2 to l1
      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].stat1 = cash2[core][ht2][index2].stat2;

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }

    if (type=='w')
    {
      // log
      corelog[core].whp2++;

      if (cash2[core][ht2][index2].stat2=='m')
      {corelog[core].dwh2++;}

      if (cash2[core][ht2][index2].stat2=='v')
      {corelog[core].vwh2++;}

      if (cash2[core][ht2][index2].stat2=='s')
      {corelog[core].swh2++;}

      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;

      int totalmatch1=0; totalmatch1=searchcores1(core);
      int totalmatch2=0; totalmatch2=searchcores2(core);
      
      if (totalmatch2==0)
      {
        cash1[core][tt1][index1].stat1='d';
        cash2[core][tt2][index2].stat2='d';
      }

      if (totalmatch2!=0)
      {
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          update_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        for(int i=0; i<totalmatch2;i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          update_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }
        

        cash1[core][tt1][index1].stat1='s';
        cash2[core][tt2][index2].stat2='s';
      }

      //log
      if(totalmatch2!=0)
      {
        corelog[core].bu++; //update bus
      }

      update_lru1(core, tt1);
      update_lru2(core, ht2);
    }
  }
  

  if (out2 == 0) // miss in level-2
  {
    // find highest lru in L2
    int tt2=0; tt2=highest_lru2();

    // find hit or miss in bus
    int totalmatch1 = 0; totalmatch1=searchcores1(core);
    int totalmatch2 = 0; totalmatch2=searchcores2(core);

    if(totalmatch2!=0) //hit in bus
    {
      // log
      corelog[core].ctoc++;

      //copy from bus to target l2 and l1 cache
      cash2[core][tt2][index2].t2=tag2;
      cash2[core][tt2][index2].v2=1;
      cash2[core][tt2][index2].stat2='s'; 

      cash1[core][tt1][index1].t1=tag1;
      cash1[core][tt1][index1].v1=1;
      cash1[core][tt1][index1].stat1='s';

      //if (cash2[core][tt2][index2].stat2=='d')
      //{
      //  // log
      //  cash0log.wmem++; // write to memory
      //}

      if (type=='z')
      {        
        //log
        corelog[core].ihb++;

        if (cash2[core][tt2][index2].stat2=='d')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // change state to shared of copies in bus
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        for (int i=0; i<totalmatch2; i++)
        {
          if (matchcore2[i].mstat2!='s')
          {
            cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          }
        }
      }

      if (type=='r')
      {        
        //log
        corelog[core].rhb++;

        if (cash2[core][tt2][index2].stat2=='d')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // change state to shared of copies in bus
        for (int i=0; i<totalmatch1; i++)
        {
          if (matchcore1[i].mstat1!='s')
          {
            cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          }
        }

        for (int i=0; i<totalmatch2; i++)
        {
          if (matchcore2[i].mstat2!='s')
          {
            cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          }
        }
      }

      if (type=='w')
      { 
        //log
        corelog[core].whb++;
        cash0log.wmem++; // write to memory

        if (cash2[core][tt2][index2].stat2=='d')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        //send shared signal in bus
        for(int i=0; i<totalmatch1;i++)
        {
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].stat1='s';
          cash1[matchcore1[i].mcore1][matchcore1[i].mthread1][index1].v1=1;
          check_lru1(matchcore1[i].mcore1,matchcore1[i].mthread1);
        }

        for(int i=0; i<totalmatch2;i++)
        {
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].stat2='s';
          cash2[matchcore2[i].mcore2][matchcore2[i].mthread2][index2].v2=1;
          check_lru2(matchcore2[i].mcore2,matchcore2[i].mthread2);
        }
      }
      update_lru1(core, tt1);
      update_lru2(core, tt2);
    }

    if(totalmatch2==0) //miss in bus
    {
      // log
      cash0log.busmiss++;

      if (type == 'z')
      {
        // log
        corelog[core].imb++;

        if (cash2[core][tt2][index2].stat2=='d')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l1 and l2 cache
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='v';

        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='v';
      }

      if (type == 'r')
      {
        // log
        corelog[core].rmb++;

        if (cash2[core][tt2][index2].stat2=='d')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l1 and l2 cache
        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='v';

        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='v';
      }

      if (type == 'w')
      {
        // log
        corelog[core].wmb++;

        if (cash2[core][tt2][index2].stat2=='d')
        {
          // log
          cash0log.wmem++; // write to memory
        }

        // copy from memory to l1 and l2 cache
        cash1[core][tt1][index1].t1=tag1;
        cash1[core][tt1][index1].v1=1;
        cash1[core][tt1][index1].stat1='d';

        cash2[core][tt2][index2].t2=tag2;
        cash2[core][tt2][index2].v2=1;
        cash2[core][tt2][index2].stat2='d';
      }
      update_lru1(core, tt1);
      update_lru2(core, tt2);
    }
  } 
}

void log_sc()
{ 
  for (int i=0; i<coreno; i++)
  {
    totalins=totalins+corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1+corelog[i].ihl1+corelog[i].iml1;
    
    totalrml1= totalrml1+corelog[i].rml1;
    totalwml1= totalwml1+corelog[i].wml1;
    totaliml1= totaliml1+corelog[i].iml1;
    totalmissl1=totalmissl1+corelog[i].rml1+corelog[i].wml1+corelog[i].iml1;

    totalrml2= totalrml2+corelog[i].rml2;
    totalwml2= totalwml2+corelog[i].wml2;
    totaliml2= totaliml2+corelog[i].iml2;
    totalmissl2=totalmissl2+corelog[i].rml2+corelog[i].wml2+corelog[i].iml2;

  }
  cout <<"total number of instructions: "<< totalins<<endl;
  cout << "\ntotal misses: "<<totalins<<endl;
  cout<<"\nread miss : "<< totalrml1<<endl;
  cout<<"write miss: "<< totalwml1<<endl;
  cout<<"instruction miss: "<< totaliml1<<endl;
  cout<<"data miss: "<< totalrml1+totalwml1<<endl;
  cout<<"miss rate : "<<((totalrml1+totalwml1+totaliml1)*100)/totalins<<"%"<<endl;

  cout << "l-2 cache call: "<< cash1log.rmiss1+cash1log.wmiss1+cash1log.imiss1 << endl;
  cout << "l-2 cache hit: "<<cash2log.ihit2+cash2log.rhit2+cash2log.whit2<< endl;
  cout << "l-2 cache miss: "<<cash2log.imiss2+cash2log.rmiss2+cash2log.wmiss2<< endl;
  cout << "l-2 cache hit ratio: "<<hitratel2<<" %"<<endl;
  cout << "memory access rate:" << endl;
}

void log_mesi_only_l1()
{
  for (int i=0; i<coreno; i++)
  {
    totalins=totalins+corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1+corelog[i].ihl1+corelog[i].iml1;
    
    totalrml1= totalrml1+corelog[i].rml1;
    totalwml1= totalwml1+corelog[i].wml1;
    totaliml1= totaliml1+corelog[i].iml1;
    totalmissl1=totalmissl1+corelog[i].rml1+corelog[i].wml1+corelog[i].iml1;

    totalctoc=totalctoc+corelog[i].ctoc;
    bustraffic=bustraffic+corelog[i].imb+corelog[i].ihb+corelog[i].rmb+corelog[i].rhb+corelog[i].wmb+corelog[i].whb+corelog[i].bu;

    //totalrhpl1=totalrhpl1+corelog[i].mrh+corelog[i].erh+corelog[i].rhb;
    //totalwhpl1=totalwhpl1+corelog[i].mwh+corelog[i].ewh+corelog[i].whb;
    //totalrhbl1=totalrhbl1+corelog[i].srh;
    //totalwhbl1=totalwhbl1+corelog[i].swh;

  }

  

  for ( int i=0; i<coreno;i++)
  {
    cout << "\n >>>>> LOG CORE: "<<i<<" <<<<<"<<endl;
    
    cout << "\nno. of read:" << corelog[i].rhl1+corelog[i].rml1<<endl;
    cout << "l-1 read miss:"<<corelog[i].rml1<< endl;
    cout << "no. of write:" << corelog[i].whl1+corelog[i].wml1<<endl;
    cout << "l-1 write miss:"<<corelog[i].wml1<< endl;
    cout << "no. of other ins:" << corelog[i].ihl1+corelog[i].iml1<<endl;
    cout << "l-1 other ins miss:"<<corelog[i].iml1<< endl;

    cout << "\ncache to cache: "<< corelog[i].ctoc<<endl;

    cout << "\nread miss bus: "<<corelog[core].rmb<<endl;
    cout << "write miss bus: "<<corelog[core].wmb<<endl;
    cout << "other ins miss bus: "<<corelog[core].imb<<endl;

    // cout << "\nshared write hit:\t"<<corelog[i].swh<<endl;
    // cout << "modified write hit:\t"<<corelog[i].mwh<<endl;
    // cout << "exclusive write hit:\t"<<corelog[i].ewh<<endl;

    corelog[i].mrate=(((corelog[i].rml1+corelog[i].wml1)/(corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1))*100);
    cout << "l-1 private cache miss rate:"<< corelog[i].mrate<<"%"<<endl;

    cout << "\nbus read request: "<<corelog[i].rhb + corelog[i].rmb<<endl;
    cout << "bus write request: "<<corelog[i].wmb+ corelog[i].whb<<endl;
    cout << "bus update:"<< corelog[i].bu<< endl;

  }

  cout<<"\ntotal number of instruction: "<<totalins<<endl;
  cout<<"\nglobal miss rate: "<< (((totalmissl1-totalctoc)*100)/totalins)<<"%"<<endl;

  cout<<"miss rate in l-1: "<<(totalmissl1/totalins)*100<<"%"<<endl;

  cout <<"\ncache to cache: "<<totalctoc<<endl;
  cout <<"bus traffic: "<<bustraffic<<endl;
  cout <<"read from memory: "<<(totalmissl1-totalctoc)<<endl;
  cout << "\n"<<coreno2<<endl;
}

void log_mesi()
{
  for (int i=0; i<coreno; i++)
  {    
    totalins=totalins+corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1+corelog[i].ihl1+corelog[i].iml1;
    
    totalrml1= totalrml1+corelog[i].rml1;
    totalwml1= totalwml1+corelog[i].wml1;
    totaliml1= totaliml1+corelog[i].iml1;
    totalmissl1=totalmissl1+corelog[i].rml1+corelog[i].wml1+corelog[i].iml1;

    totalrml2= totalrml2+corelog[i].rml2;
    totalwml2= totalwml2+corelog[i].wml2;
    totaliml2= totaliml2+corelog[i].iml2;
    totalmissl2=totalmissl2+corelog[i].rml2+corelog[i].wml2+corelog[i].iml2;

    totalctoc=totalctoc+corelog[i].ctoc;
    bustraffic=bustraffic+corelog[i].imb+corelog[i].ihb+corelog[i].rmb+corelog[i].rhb+corelog[i].wmb+corelog[i].whb+corelog[i].bu;

    //totalrhpl1=totalrhpl1+corelog[i].mrh+corelog[i].erh+corelog[i].rhb;
    //totalwhpl1=totalwhpl1+corelog[i].mwh+corelog[i].ewh+corelog[i].whb;
    //totalrhbl1=totalrhbl1+corelog[i].srh;
    //totalwhbl1=totalwhbl1+corelog[i].swh;

  }

  

  for ( int i=0; i<coreno;i++)
  {
    cout << "\n >>>>> LOG CORE: "<<i<<" <<<<<"<<endl;
    
    cout << "\nno. of read:" << corelog[i].rhl1+corelog[i].rml1<<endl;
    cout << "l-1 read miss:"<<corelog[i].rml1<< endl;
    cout << "no. of write:" << corelog[i].whl1+corelog[i].wml1<<endl;
    cout << "l-1 write miss:"<<corelog[i].wml1<< endl;
    cout << "no. of other ins:" << corelog[i].ihl1+corelog[i].iml1<<endl;
    cout << "l-1 other ins miss:"<<corelog[i].iml1<< endl;

    //cout << "l-1 no. of read:" << corelog[i].rhl1+corelog[i].rml1<<endl;
    cout << "\nl-2 read miss:"<<corelog[i].rml2<< endl;
    //cout << "l-1 no. of write:" << corelog[i].whl1+corelog[i].wml1<<endl;
    cout << "l-2 write miss:"<<corelog[i].wml2<< endl;
    //cout << "l-1 no. of ins:" << corelog[i].ihl1+corelog[i].iml1<<endl;
    cout << "l-2 other ins miss:"<<corelog[i].iml2<< endl;

    cout << "\ncache to cache: "<< corelog[i].ctoc<<endl;

    cout << "\nread miss bus: "<<corelog[core].imb<<endl;
    cout << "write miss bus: "<<corelog[core].imb<<endl;
    cout << "other ins miss bus: "<<corelog[core].imb<<endl;

    // cout << "\nshared write hit:\t"<<corelog[i].swh<<endl;
    // cout << "modified write hit:\t"<<corelog[i].mwh<<endl;
    // cout << "exclusive write hit:\t"<<corelog[i].ewh<<endl;

    corelog[i].mrate=(((corelog[i].rml1+corelog[i].wml1)/(corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1))*100);
    cout << "l-1 private cache miss rate:"<< corelog[i].mrate<<"%"<<endl;

    cout << "\nbus read request: "<<corelog[i].rhb + corelog[i].rmb<<endl;
    cout << "bus write request: "<<corelog[i].wmb+ corelog[i].whb<<endl;
    cout << "bus update:"<< corelog[i].bu<< endl;
    
    cout << "l-2 call:" << corelog[i].rmb+corelog[i].wmb<<endl;
    cout << "l-2 read hit:"<< corelog[i].rhl2<<endl;
    cout << "l-2 write hit:"<<corelog[i].whl2<<endl;
    cout << "l-2 update:"<< corelog[i].exchange<<endl;

  }

  cout<<"\ntotal number of instruction: "<<totalins<<endl;
  cout<<"\nglobal miss rate: "<< (((totalmissl2-totalctoc)*100)/totalins)<<"%"<<endl;

  //cout<<"\ncache miss in l-1:\t"<<totalmissl1<<endl;
  cout<<"miss rate in l-1: "<<(totalmissl1/totalins)*100<<"%"<<endl;
  
  cout << "miss rate in l-2: "<<((totalmissl2/totalmissl1)*100)<<"%"<<endl;
  
  cout << "miss rate in 2 level of cache: "<<((totalmissl2/totalins)*100)<<"%"<<endl;

  cout <<"\ncache to cache: "<<totalctoc<<endl;
  cout <<"bus traffic: "<<bustraffic<<endl;
  cout <<"read from memory: "<<(totalmissl2-totalctoc)<<endl;
}

void log_firefly_only_l1()
{
  for (int i=0; i<coreno; i++)
  {
    totalins=totalins+corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1+corelog[i].ihl1+corelog[i].iml1;
    
    totalrml1= totalrml1+corelog[i].rml1;
    totalwml1= totalwml1+corelog[i].wml1;
    totaliml1= totaliml1+corelog[i].iml1;
    totalmissl1=totalmissl1+corelog[i].rml1+corelog[i].wml1+corelog[i].iml1;

    totalctoc=totalctoc+corelog[i].ctoc;
    bustraffic=bustraffic+corelog[i].imb+corelog[i].ihb+corelog[i].rmb+corelog[i].rhb+corelog[i].wmb+corelog[i].whb+corelog[i].bu;

  }

  for ( int i=0; i<coreno;i++)
  {
    cout << "\n >>>>> LOG CORE: "<<i<<" <<<<<"<<endl;
    
    cout << "\nno. of read: " << corelog[i].rhl1+corelog[i].rml1<<endl;
    cout << "read miss in l1: "<<corelog[i].rml1<< endl;
    cout << "no. of write: " << corelog[i].whl1+corelog[i].wml1<<endl;
    cout << "write miss in l1: "<<corelog[i].wml1<< endl;
    cout << "no. of other ins: " << corelog[i].ihl1+corelog[i].iml1<<endl;
    cout << "ins miss in l1: "<<corelog[i].iml1<< endl;

    cout << "\ncache to cache: "<< corelog[i].ctoc<<endl;

    cout << "\nread miss bus: "<<corelog[core].rmb<<endl;
    cout << "write miss bus: "<<corelog[core].wmb<<endl;
    cout << "other ins miss bus: "<<corelog[core].imb<<endl;

    // cout << "\nshared write hit:\t"<<corelog[i].swh<<endl;
    // cout << "modified write hit:\t"<<corelog[i].mwh<<endl;
    // cout << "exclusive write hit:\t"<<corelog[i].ewh<<endl;

    corelog[i].mrate=(((corelog[i].rml1+corelog[i].wml1)/(corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1))*100);
    cout << "l-1 private cache miss rate:"<< corelog[i].mrate<<"%"<<endl;

    cout << "\nbus read request: "<<corelog[i].rhb + corelog[i].rmb<<endl;
    cout << "bus write request: "<<corelog[i].wmb+ corelog[i].whb<<endl;
    cout << "bus update:"<< corelog[i].bu<< endl;
  }

  cout<<"\ntotal number of instruction: "<<totalins<<endl;

  cout << "\nglobal miss rate: "<< (((totalmissl1-totalctoc)*100)/totalins)<<"%"<<endl;
  cout << "miss rate in l1: "<<(totalmissl1/totalins)*100<<"%"<<endl;

  cout <<"\ncache to cache: "<<totalctoc<<endl;
  cout <<"bus traffic: "<<bustraffic<<endl;
  cout <<"read from memory: "<<(totalmissl1-totalctoc)<<endl;
}

void log_firefly()
{
  for (int i=0; i<coreno; i++)
  {
    totalins=totalins+corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1+corelog[i].ihl1+corelog[i].iml1;
    
    totalrml1= totalrml1+corelog[i].rml1;
    totalwml1= totalwml1+corelog[i].wml1;
    totaliml1= totaliml1+corelog[i].iml1;
    totalmissl1=totalmissl1+corelog[i].rml1+corelog[i].wml1+corelog[i].iml1;

    totalrml2= totalrml2+corelog[i].rml2;
    totalwml2= totalwml2+corelog[i].wml2;
    totaliml2= totaliml2+corelog[i].iml2;
    totalmissl2=totalmissl2+corelog[i].rml2+corelog[i].wml2+corelog[i].iml2;

    totalctoc=totalctoc+corelog[i].ctoc;
    bustraffic=bustraffic+corelog[i].imb+corelog[i].ihb+corelog[i].rmb+corelog[i].rhb+corelog[i].wmb+corelog[i].whb+corelog[i].bu;

    //totalrhpl1=totalrhpl1+corelog[i].mrh+corelog[i].erh+corelog[i].rhb;
    //totalwhpl1=totalwhpl1+corelog[i].mwh+corelog[i].ewh+corelog[i].whb;
    //totalrhbl1=totalrhbl1+corelog[i].srh;
    //totalwhbl1=totalwhbl1+corelog[i].swh;

  }

  for ( int i=0; i<coreno;i++)
  {
    cout << "\n >>>>> LOG CORE: "<<i<<" <<<<<"<<endl;
    
    cout << "\nno. of read: " << corelog[i].rhl1+corelog[i].rml1<<endl;
    cout << "read miss in l1: "<<corelog[i].rml1<< endl;
    cout << "no. of write: " << corelog[i].whl1+corelog[i].wml1<<endl;
    cout << "write miss in l1: "<<corelog[i].wml1<< endl;
    cout << "no. of other ins: " << corelog[i].ihl1+corelog[i].iml1<<endl;
    cout << "ins miss in l1: "<<corelog[i].iml1<< endl;

    cout << "\nread miss in l2:"<<corelog[i].rml2<< endl;
    cout << "write miss in l2:"<<corelog[i].wml2<< endl;
    cout << "ins miss in l2:"<<corelog[i].iml2<< endl;

    cout << "\ncache to cache: "<< corelog[i].ctoc<<endl;

    cout << "\nread miss bus: "<<corelog[core].imb<<endl;
    cout << "write miss bus: "<<corelog[core].imb<<endl;
    cout << "other ins miss bus: "<<corelog[core].imb<<endl;

    // cout << "\nshared write hit:\t"<<corelog[i].swh<<endl;
    // cout << "modified write hit:\t"<<corelog[i].mwh<<endl;
    // cout << "exclusive write hit:\t"<<corelog[i].ewh<<endl;

    corelog[i].mrate=(((corelog[i].rml1+corelog[i].wml1)/(corelog[i].rhl1+corelog[i].rml1+corelog[i].whl1+corelog[i].wml1))*100);
    cout << "l-1 private cache miss rate:"<< corelog[i].mrate<<"%"<<endl;

    cout << "\nbus read request: "<<corelog[i].rhb + corelog[i].rmb<<endl;
    cout << "bus write request: "<<corelog[i].wmb+ corelog[i].whb<<endl;
    cout << "bus update:"<< corelog[i].bu<< endl;
    
    cout << "l-2 call:" << corelog[i].rmb+corelog[i].wmb<<endl;
    cout << "l-2 ins. miss:"<< corelog[i].iml2<<endl;
    cout << "l-2 read miss:"<< corelog[i].rml2<<endl;
    cout << "l-2 write miss:"<<corelog[i].wml2<<endl;
  }

  cout<<"\ntotal number of instruction: "<<totalins<<endl;

  cout << "\nglobal miss rate: "<< (((totalmissl2-totalctoc)*100)/totalins)<<"%"<<endl;
  cout << "miss rate in l1: "<<(totalmissl1/totalins)*100<<"%"<<endl;
  cout << "miss rate in l2: "<<((totalmissl2/totalmissl1)*100)<<"%"<<endl;  
  cout << "miss rate in 2 level of cache: "<<((totalmissl2/totalins)*100)<<"%"<<endl;

  cout <<"\ncache to cache: "<<totalctoc<<endl;
  cout <<"bus traffic: "<<bustraffic<<endl;
  cout <<"read from memory: "<<(totalmissl2-totalctoc)<<endl;
}
