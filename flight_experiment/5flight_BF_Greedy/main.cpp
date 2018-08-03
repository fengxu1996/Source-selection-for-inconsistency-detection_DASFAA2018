#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
string dir = "C:\\Users\\12433\\Desktop\\Data_flight\\";
const unsigned long long Filter_size = 1<<16;/**设置bloom filter的大小*/
const int no_FD = 1;/**FD个数*/
int no_file;/**生成文件个数*/
int PRE_REMAIN_HASHN = 1000;/**预先设置的哈希函数个数,各个FD可以计算出各自需要的hash函数个数使用*/
ULL murmurhash_Seed_start_pos ;/**设置murmurhash种子开始位置*/
vector<string>FileName;/**文件名*/
bitset<Filter_size>S0_filter[no_FD],S_filter[no_FD],tmp_filter[no_FD],tmp_final_union[no_FD];/**S0的过滤器,S的过滤器*/
vector<ULL>FD_hashnum;/**哈希函数的个数*/
set<string>S0FDSET[no_FD];/**存储S0的每个FD的元素,可以计算出各个FD*/
int MAX_select;/**选择数据源个数*/
vector<bool>si_if_selected;/**标记数据源是否已经被选择*/
bool if_add_random_weight=false;/**是否添加随机权重*/
int  hashmethod=0;/**选择hash方法0为(ax+b)%c; 1为murmurhash*/
double MAX_cov=0;/**记录最大覆盖值*/
vector<double>file_random_weight;/**保存每个数据源的随机权重*/

struct source_si
{
    int FD;/**记录该si的fd*/
    bitset<Filter_size>si_bloom_filter;/**si的关于FD的过滤器*/
};
vector<source_si>Si_filter;/**存储各个si的filter  第一个位置放的是s1*/

struct nod/**一个函数依赖的数据结构*/
{
    vector<string>qianJian;
    vector<string>houJian;
};
vector<nod>HanShuYiLai;/**存储函数依赖*/

struct hashParameter
{
    long long A,B;
};
vector<hashParameter>HASH;/**hash函数集参数*/


/**大素数______________________*/
const int maxn=100000;// N=999999时有78498个素数
const int maxnn=999999;
long long prime[maxn+10];
bool isprime[maxnn+10];
long long pnum;
void GetPrime(long long N )
{
    pnum=0;
    memset(isprime,true,sizeof(isprime));
    isprime[1]=false;
    //i 为最大因数
    for(long long  i=2;i<=N;i++)
    {
        if(isprime[i])
        {
            prime[pnum++]=i;
        }
        for(long long  j=0;j<pnum && prime[j]*i<=N;j++)
        {
            isprime[prime[j]*i]=false;
            if(i%prime[j]==0)break;
        }
    }
}
/**大素数______________________*/

vector<hashParameter> hashi(int k)
{
    set<string>S;
    vector<hashParameter>v;
    while(S.size()<k)
    {
        hashParameter xx;
        long long aindex = (rand()%10000)+(pnum-10001);
        long long bindex = (rand()%10000)+(pnum-10001);

        xx.A=prime[aindex];
        xx.B=prime[bindex];

        char sstr[50];
        sprintf(sstr, "%lld_%lld", xx.A, xx.B);

        //cout<<sstr<<endl;

        string str =sstr;
        if(S.find(str)==S.end()){
            S.insert(str);
            v.push_back(xx);
        }
    }
    return v;
}

void HanShuYiLaiAdd(string yilai)
{
    int b=0,e=yilai.size()-1;
    while(yilai[b]!='('){b++;}
    while(yilai[e]!=')'){e--;}
    nod a;
    string s;
    s="";
    for(int i=b+1;i<e;i++)
    {
        if(yilai[i]==',')
        {
            a.qianJian.push_back(s);
            s="";
        }
        else{
            s+=yilai[i];
        }
    }
    a.qianJian.push_back(s);
    s="";
    for(int i=e+1;i<yilai.size();i++)
    {
        if(yilai[i]==',')
        {
            a.houJian.push_back(s);
            s="";
        }
        else
        {
            s+=yilai[i];
        }
    }
    a.houJian.push_back(s);
    HanShuYiLai.push_back(a);
}

ULL get_hash_functions_amount(double n)/**参数n为(the number of inserted elements)*/
{
    return (ULL)ceil(( (double)Filter_size / n)*log(2));
}

double get_Estimated_Size(ULL filtersize, ULL hashNum, ULL cnt)/**参数为过滤器大小,hash函数数目,过滤器中1的个数*/
{
//    return ceil( -1*((double)filtersize / (double)hashNum)*log( 1 - ( (double)cnt / (filtersize) )));
    return ( -1*((double)filtersize / (double)hashNum)*log( 1 - ( (double)cnt / (filtersize) )));
}

vector<string> split(string s)//按空格分割字符串
{
    vector<string>v;
    string w="";

    for(int i=0;i<s.size();i++)
    {
        if(s[i]==' ')
        {
            v.push_back(w);
            w="";
        }
        else
        {
            w+=s[i];
        }
    }
    v.push_back(w);
    return v;
}

string mytrim(string s)//把下划线之前的无用的东西去掉只保留数字部分,变成四位长度的数字
{
    string k="";
    int i=0;
    while(s[i]!='_')i++;
    for(i=i+1;i<s.size();i++)
    {
        k+=s[i];
    }
    if(k.size()<4)
    {
        string ch="";
        int cnt=4-k.size();
        while(cnt--)ch+='0';
        k=ch+k;
    }
    return k;
}
ULL getHashValue_method1(string s, ULL filtersize, int hashi)
{
//    cout<<"hashi="<<(ULL(((ULL)atoll(s.c_str())*HASH[hashi].A + HASH[hashi].B) % filtersize))<<endl;
    return ULL(((ULL)atoll(s.c_str())*HASH[hashi].A + HASH[hashi].B) % filtersize);
}
unsigned long long MurmurHash64B ( const void * key, int len, unsigned int seed )
{
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	unsigned int h1 = seed ^ len;
	unsigned int h2 = 0;

	const unsigned int * data = (const unsigned int *)key;

	while(len >= 8)
	{
		unsigned int k1 = *data++;
		k1 *= m; k1 ^= k1 >> r; k1 *= m;
		h1 *= m; h1 ^= k1;
		len -= 4;

		unsigned int k2 = *data++;
		k2 *= m; k2 ^= k2 >> r; k2 *= m;
		h2 *= m; h2 ^= k2;
		len -= 4;
	}

	if(len >= 4)
	{
		unsigned int k1 = *data++;
		k1 *= m; k1 ^= k1 >> r; k1 *= m;
		h1 *= m; h1 ^= k1;
		len -= 4;
	}

	switch(len)
	{
	case 3: h2 ^= ((unsigned char*)data)[2] << 16;
	case 2: h2 ^= ((unsigned char*)data)[1] << 8;
	case 1: h2 ^= ((unsigned char*)data)[0];
			h2 *= m;
	};

	h1 ^= h2 >> 18; h1 *= m;
	h2 ^= h1 >> 22; h2 *= m;
	h1 ^= h2 >> 17; h1 *= m;
	h2 ^= h1 >> 19; h2 *= m;

	unsigned long long h = h1;

	h = (h << 32) | h2;

	return h;
}
void builtS0Filter(string s0path)
{
    ifstream fin;
    fin.open(s0path.c_str(), ios::in);
    string s;
    getline(fin, s);
    vector<string>attr = split(s);
    getline(fin, s);
    vector<string>fd_str = split(s);
    map<string,int>M;/**建立属性到列号的映射*/
    for(int i=0;i<attr.size();i++)M[ attr[i] ] = i;

    while(getline(fin, s))
    {
        vector<string>tupi = split(s);/**读入一个元组*/
        for(int i=0;i<fd_str.size();i++)/**遍历每个FD*/
        {
            int fd = atoi(fd_str[i].c_str());/**FD序号*/
            string x="";
            for(int j=0;j<HanShuYiLai[fd].qianJian.size();j++)/**FD的前件属性*/
            {
                string vi = tupi[ M[ HanShuYiLai[fd].qianJian[j] ] ];/**前件属性上的值*/
                x += mytrim(vi);/**去掉j_部分*/
            }
           // /**将x插入过滤器S0_filter[fd]即将x的k个散列值放入过滤器*/
            S0FDSET[fd].insert(x);/**放入set中用于统计将要插入的元素数目用于计算hash函数的个数*/
        }
    }
    fin.close();

    for(int i=0;i<no_FD;i++)/**计算各个FD所需的哈希函数个数*/
    {
        ULL hnum = get_hash_functions_amount(S0FDSET[i].size());
        FD_hashnum.push_back(hnum);
    }
    /**将元素插入bloom filter*/
    for(int i=0;i<no_FD;i++)
    {
        for(set<string>::iterator it=S0FDSET[i].begin();it!=S0FDSET[i].end();it++)
        {
            for(int hashi=0;hashi<FD_hashnum[i];hashi++)
            {
                ULL hashvalue;
                if(hashmethod == 0)
                    hashvalue = getHashValue_method1(*it, Filter_size, hashi);/**  第一种哈希方法(a*x+b)%c的哈希  */
//                ULL hashvalue = MurmurHash64B((*it).c_str(), (*it).size(), prime[pnum-1]) % Filter_size;/**  第二种哈希方法murmurhash seed设置成素数好像会更好 */
                else if(hashmethod == 1)
                    hashvalue = MurmurHash64B((*it).c_str(), (*it).size(), prime[hashi+murmurhash_Seed_start_pos]) % Filter_size;/**  第二种哈希方法murmurhash seed设置成素数好像会更好 */

                S0_filter[i][ hashvalue ] = 1;
            }

        }
    }
    cout<<"S0过滤器大小"<<endl;
    for(int i=0;i<no_FD;i++)cout<<S0_filter[i].count()<<" ";cout<<endl;

}

void builtSiFilter(string sipath)
{
    source_si SI;/**建立一个SI的结构*/
    ifstream fin;
    fin.open(sipath.c_str(), ios::in);
    string s;
    getline(fin, s);
    vector<string>attr = split(s);
    getline(fin, s);
    SI.FD = atoll(s.c_str());/**得到FD*/
    map<string,int>M;
    for(int i=0;i<attr.size();i++)M[ attr[i] ] = i;
    while(getline(fin, s))
    {
        vector<string>tupi = split(s);
        string x="";
        for(int i=0;i<HanShuYiLai[SI.FD].qianJian.size();i++)
        {
            x += mytrim(tupi[ M[ HanShuYiLai[SI.FD].qianJian[i] ] ]);
        }

        for(int hashi=0;hashi<FD_hashnum[SI.FD];hashi++)
        {
            ULL hashvalue;
            if(hashmethod == 0)
                hashvalue = getHashValue_method1(x, Filter_size, hashi);/**  第一种哈希方法(a*x+b)%c的哈希  */
            else if(hashmethod == 1)
                hashvalue = MurmurHash64B(x.c_str(), x.size(), prime[hashi+murmurhash_Seed_start_pos]) % Filter_size;/**  第二种哈希方法murmurhash seed设置成素数好像会更好 */

            SI.si_bloom_filter[ hashvalue ] = 1;
        }
    }
    fin.close();
    //cout<<sipath<<" "<<SI.FD<<" "<<SI.si_bloom_filter.count()<<endl;
    Si_filter.push_back(SI);/**将建好的si上的关于FD的过滤器放到Si_filter里*/
}
double computeCov(int si_index)/**估计加入si后S对s0的覆盖值*/
{
    for(int i=0;i<no_FD;i++)/**把之前的并集filter copy到tmp_filter里*/
        tmp_filter[i] = S_filter[i];
    tmp_filter[ Si_filter[si_index - 1].FD ] = tmp_filter[ Si_filter[si_index - 1].FD ] | Si_filter[si_index - 1].si_bloom_filter;/**把si在FD上的filter和并集的filter并到一起*/
    double _sum_per_FD_cov=0;/**累加S0和S在每个FD上的交集*/
    for(int i=0;i<no_FD;i++)/**枚举每个FD*/
    {

        double n_S0 = get_Estimated_Size(Filter_size, FD_hashnum[i], S0_filter[i].count());/**估计s0在该FD上的大小 参数为过滤器大小,hash函数数目,过滤器中1的个数*/
        double n_S = get_Estimated_Size(Filter_size, FD_hashnum[i], tmp_filter[i].count());/**估计S在该FD上的大小 参数为过滤器大小,hash函数数目,过滤器中1的个数*/
        bitset<Filter_size>bs = S0_filter[i] | tmp_filter[i];
        double n_S0_S_union = get_Estimated_Size(Filter_size, FD_hashnum[i], bs.count());/**估计S0和S的并集大小*/
        double n_S0_S_intersection = n_S0 + n_S - n_S0_S_union;/**求S0和S的交集大小*/
        _sum_per_FD_cov += n_S0_S_intersection;/**累加每个FD上的交集*/
    }
    return _sum_per_FD_cov;
}
int MAX_COV()
{
    int select_index = -1;
    double MAX_newcov_sub_oldcov = 0;
    for(int i=1;i<=no_file;i++)
    {
        if(si_if_selected[i] == true) continue;

        double cov_value = computeCov(i);/**计算S中加入si后得到的对S0的估计覆盖值*/
        double newcov_sub_oldcov;/**计算(cov(SUsi)-cov(S))或(cov(SUsi)-cov(S))/ci*/
        if(if_add_random_weight == true)/**如果要带随机权重*/
            newcov_sub_oldcov = (cov_value - MAX_cov) / file_random_weight[i];
        else
            newcov_sub_oldcov = cov_value - MAX_cov;
        if(MAX_newcov_sub_oldcov < newcov_sub_oldcov)
        {
            select_index = i;
            MAX_newcov_sub_oldcov = newcov_sub_oldcov;/**更新最大收益*/
            MAX_cov = cov_value;/**记录最大覆盖值*/

            for(int w=0;w<no_FD;w++)tmp_final_union[w]=tmp_filter[w];
        }
    }
    for(int w=0;w<no_FD;w++) S_filter[w]=tmp_final_union[w];/**保留选择的最佳的si加入后的并集S*/
    return select_index;
}
/**
   argv1数据源个数
   argv2哈希函数个数(哈希函数个数不需要自己设定,根据公式自己算。设置成null)
   argv3选择数据源个数k
   argv4目标数据集的元组个数所占最大数的比例
   argv5数据源的元组个数所占的最大比例
   argv6元组个数上限
   argv7ComputeCov.exe会根据这个参数去选择是greedy，mh_greedy，bf_greedy还是random分别对应参数  "greedy_SelectedSrcs" "mh_greedy_SelectedSrcs" "bf_greedy_SelectedSrc" "random_SelectedSrcs"
   argv8 选择hash方法参数为 "murmurhash" 或 "(ax+b)%c"
   argv9是否要给每个数据源添加一个随机权重"add_random_weight_YES" "add_random_weight_NO"

*/

int main(int argc, const char *argv[])
//int main()
{
    /*char *argv[10];
    argv[1]="1000";
    argv[2]="murmurhash";
    argv[3]="5";
    argv[4]="100";
    argv[5]="100";
    argv[6]="2000";
    argv[7]="add_random_weight_NO";
    */
    no_file = atoi(argv[1]);
    MAX_select = atoi(argv[3]);
    if_add_random_weight = ((strcmp(argv[9],"add_random_weight_YES")==0)?true:false);
    string hashstr = argv[8];
    if(hashstr == "murmurhash")
        hashmethod = 1;
    else if(hashstr == "(ax+b)c")
        hashmethod = 0;

    srand(time(NULL));
    long long NN=999999;
    GetPrime(NN);
    murmurhash_Seed_start_pos = rand()%10000;/**在prime[]中随机找一个素数作为murmurhash种子*/

    for(int i=0;i<no_file+5;i++)/**设标记未被选过*/
        si_if_selected.push_back(false);

    /**读取文件名*/
    string filenamepath=dir+"FileName_"+argv[6]+".txt";/**文件名列表*/
    ifstream fin;
    fin.open(filenamepath.c_str(), ios::in);
    string s;
    int cnt_file = no_file + 1;/**包含S0*/
    while(fin>>s&&cnt_file--)
    {
        FileName.push_back(s);
    }
    fin.close();

    no_file = FileName.size()-1;/**根据读到的实际个数调整参数*/

    clock_t start, finish;
    double totaltime = 0;
    start = clock();
    if(if_add_random_weight == true){
        ifstream fiin;
        string randomweightpath = dir + "random_weight.txt";
        fiin.open(randomweightpath.c_str(), ios::in);
        cout<<"#add_random_weight"<<endl;
        for(int i=0;i<=no_file;i++)/**给每个文件随机分配一个1-10的权重*/
        {
            string sss;
            fiin>>sss;
            file_random_weight.push_back(atof(sss.c_str()));
            cout<<"--source "<<i<<" weight:"<<file_random_weight[file_random_weight.size()-1]<<endl;
        }
        fiin.close();

    }

    cout<<"OK1"<<endl;

    /**读取FD*/
    string fdfilepath = dir + "FD.txt";
    fin.open(fdfilepath.c_str(), ios::in);
    while(fin>>s)
    {
        HanShuYiLaiAdd(s);
    }
    fin.close();


    HASH = hashi(PRE_REMAIN_HASHN);

    cout<<"OK2"<<endl;

    /**构造S0的各个FD上的过滤器*/
    string s0path = dir + FileName[0];
    builtS0Filter(s0path);
    for(int i=1;i<FileName.size();i++)
    {
        string sipath = dir + FileName[i];
        builtSiFilter(sipath);
    }

    cout<<"OK3"<<endl;

    vector<long long>select_file_to_cov;
    for(int i=0;i<MAX_select;i++)
    {
        int select_si_index = MAX_COV();/**返回值为选哪个si可以达到最大覆盖*/
        if(select_si_index == -1)break;
        si_if_selected[select_si_index] = true;
        select_file_to_cov.push_back(select_si_index);
    }
    finish = clock();
    totaltime = (double)(finish - start)/(double)(CLOCKS_PER_SEC);

    cout<<"OK4"<<endl;
//    cout<<"估计最大覆盖值:"<<MAX_cov<<endl;
//    for(int i=0;i<select_file_to_cov.size();i++)cout<<select_file_to_cov[i]<<endl;
    //-------------------------------------------------------------------
    ofstream fout;
    string file = dir + "output\\bf_greedy_runtime.txt";
    fout.open(file.c_str(), ios::out|ios::app);
    fout<<argv[1]<<"_"<<argv[2]<<"_"<<argv[3]<<"_"<<argv[4]<<"_"<<argv[5]<<"_"<<argv[6]<<"_"<<argv[7]<<"_"<<argv[8]<<"_"<<argv[9]<<"\t"<<totaltime<<endl;
    fout.close();
    /**将选择的数据源输出到文件*/
    cout<<"#Src="<<select_file_to_cov.size()<<endl;
    cout<<"#Covered="<<MAX_cov<<endl;
    //file = dir + argv[1] + "_" + argv[2] + "_" + argv[3] + "_" + argv[4] + "_" + argv[5] + "_" + argv[6] + "_" + argv[7] + "_" + argv[8] + "_" + argv[9] + ".txt";
    file = dir + argv[1] + "_" + argv[2] + "_" + argv[3] + "_" + argv[4] + "_" + argv[5] + "_" + argv[6] + "_" + "bf_greedy_SelectedSrcs" + ".txt";

    fout.open(file.c_str(), ios::out);
    fout<<"bf_greedy\n";
    fout<<FileName[0]<<"\n";
    for(int i=0;i<select_file_to_cov.size();i++)
    {
        fout<<FileName[ select_file_to_cov[i] ]<<"\n";
        cout<<"--source "<<select_file_to_cov[i]<<endl;
    }
    fout.close();

    return 0;
}
