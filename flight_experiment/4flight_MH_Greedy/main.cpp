#include<bits/stdc++.h>
using namespace std;
string dir="C:\\Users\\12433\\Desktop\\Data_flight\\";
long long The_number_of_generate_file;/**生成文件个数*/
long long HASHN;/**生成hash函数的个数*/
long long Max_select;/**最多选择的数据源个数*/
long long no_FD = 1;/**共有几个FD*/
double MAX_cov = 0;/**最大覆盖值*/
bool if_add_random_weight = false;/**是否给每个数据源一个随机权重*/
vector<double>file_random_weight;/**保存每个数据源的随机权重*/
//vector<long long>S0_per_FD_set_size;/**保存S0的每个FD的投影的集合大小,用来估计x^: x^=s^*(a+b^)/(1+s^) 及其中的a的值*/
//long long FD_domain;/**用来设置公式 b^ = n*hashn/sum(hj) 中的n值的大小,即FD前件属性的值域大小,b^用来估计Si的大小*/
vector<double> FD_domain;/**(在合成数据上用数组,因为有的FD值域不同.真实数据用一个值即可，因为值域都是相同的)
                             用来设置公式 b^ = n*hashn/sum(hj) 中的n值的大小,即FD前件属性的值域大小,b^用来估计Si的大小*/
vector<string>filename;/**存储文件名列表*/
vector<bool> si_if_selected;/**标记Si是否已被选过，选过为true，未选过为false*/



struct source_Si
{
    map<int, int>FDindex_mhindex;/**存储函数依赖序号对应的签名向量在mh的下标*/
    vector<vector<double> >mh;/**存储s0的各个FD的签名向量*/
    vector<double>setSzie;/**mh文件中{}中的值，即Si在FD上的投影的集合大小*/
};

struct source_Si_union
{
    map<int, int>FDindex_mhindex;/**存储函数依赖序号对应的签名向量在mh的下标*/
    vector<vector<double> >mh;/**存储各个si在各个FD上的签名的并(即取签名最小值)*/
};
source_Si_union SOURCE_SI_UNION;/**存储各个si的并集*/
source_Si_union tmp_SOURCE_SI_UNION;/**临时存储*/

vector<source_Si>SOURCE_SI;/**存储mh文件的内容*/
void synthetic_setDomain()/**设置合成数据上各个FD的值域*/
{
    /**设置各个FD的值域（对于合成数据）*/
    for(int i=0;i<no_FD;i++)
    {
        if(i<7){
            FD_domain.push_back(1000);
        }
        else{
            FD_domain.push_back(1000000);
        }
    }
}

void book_or_flight_setDomain()/**设置真实数据上FD的值域*/
{
    ifstream fin;
    string path = dir + "attr_zhiyu.txt";
    fin.open(path.c_str(), ios::in);
    string s;
    fin>>s;
    fin.close();
    for(int i=0;i<no_FD;i++)
    {
        FD_domain.push_back(atof(s.c_str()));
    }
//    FD_domain = atoll(s.c_str());
}

void readFilename(string path, long long no_file)
{
    ifstream fin;
    fin.open(path.c_str(), ios::in);
    string s;
    no_file++;/**包含S0*/
    while(fin>>s && no_file--)
    {
        filename.push_back(s);
    }
    fin.close();
}

void readMH(string path)
{
    ifstream fin;
    fin.open(path.c_str(), ios::in);
    string s;
    while(fin>>s)
    {
        if(s[0]=='(')/**读到一个新的文件名*/
        {
            source_Si x;
            SOURCE_SI.push_back(x);/**添加一个文件的数据结构用来保存接下来得到的这个文件的内容*/
        }
        else if(s[0]=='[')/**读到一个FD*/
        {
            string FD_str="";
            for(int k=1;k<s.size()-1;k++)/**取出FD序号*/
                FD_str += s[k];
            int FDi_index = SOURCE_SI[ SOURCE_SI.size()-1 ].FDindex_mhindex.size();
            SOURCE_SI[ SOURCE_SI.size()-1 ].FDindex_mhindex[ atoi(FD_str.c_str()) ] = FDi_index;
            fin>>s;/**读{}*/
            string FDi_set_size_str="";
            for(int k=1;k<s.size()-1;k++)/**取出Si在一个FD上的投影的集合的大小*/
                FDi_set_size_str += s[k];
            SOURCE_SI[ SOURCE_SI.size()-1 ].setSzie.push_back(atof(FDi_set_size_str.c_str()));
            while(fin>>s && s!=";");/**跳转到签名部分*/
            vector<double>sigv;/**保存签名*/
            for(int i=0;i<HASHN;i++)/**读取签名*/
            {
                fin>>s;
                sigv.push_back(atof(s.c_str()));
            }
            SOURCE_SI[ SOURCE_SI.size()-1 ].mh.push_back(sigv);
        }
    }
    fin.close();
}

double computeCov(int si_index)/**估计加入si后S对s0的覆盖值*/
{
    //for(int i=0;i<SOURCE_SI[si_index].FDindex_mhindex.size();i++)/**循环si的每个FD*/
    source_Si_union new_SOURCE_SI_UNION;/**添加si后的并集S*/
    new_SOURCE_SI_UNION = SOURCE_SI_UNION;/**先把旧的S复制过来*/
    /**加入新的si*/
    for(map<int,int>::iterator it = SOURCE_SI[si_index].FDindex_mhindex.begin(); it!=SOURCE_SI[si_index].FDindex_mhindex.end(); it++)/**循环si的每个FD*/
    {
        int si_FD = it->first;/**si的FD*/
        int si_FD_mh_index = it->second;/**FD在mh中的序号(si中)*/
        if(new_SOURCE_SI_UNION.FDindex_mhindex.find(si_FD)!=new_SOURCE_SI_UNION.FDindex_mhindex.end()){/**如果(并集S中)已经有这个FD*/
            int sourceUnion_FD_mh_index = new_SOURCE_SI_UNION.FDindex_mhindex[si_FD];/**取出FD在mh中的序号(并集S中)*/
            for(int i=0;i<HASHN;i++)
            {
                new_SOURCE_SI_UNION.mh[sourceUnion_FD_mh_index][i] = min(new_SOURCE_SI_UNION.mh[sourceUnion_FD_mh_index][i], SOURCE_SI[si_index].mh[si_FD_mh_index][i]);
            }
        }
        else{/**如果还没有这个FD*/
            int mhindex = new_SOURCE_SI_UNION.FDindex_mhindex.size();
            new_SOURCE_SI_UNION.FDindex_mhindex[si_FD] = mhindex;/**建立一个(FD---mh下标)的索引*/
            new_SOURCE_SI_UNION.mh.push_back(SOURCE_SI[si_index].mh[si_FD_mh_index]);
        }
    }
    double sum_per_FD_intersection=0;
    for(map<int,int>::iterator it = new_SOURCE_SI_UNION.FDindex_mhindex.begin(); it!=new_SOURCE_SI_UNION.FDindex_mhindex.end(); it++)/**循环并集S的每个FD*/
    {
        int FD = it->first;/**FD*/
        int FD_mh_index = it->second;/**FD在mh中的序号*/

        double sum_hash_value=0;/**累加hash值*/
        double _sim = 0;/**用来保存s^*/
        for(int i=0;i<HASHN;i++)
        {
            sum_hash_value += new_SOURCE_SI_UNION.mh[ FD_mh_index ][i];
            if(SOURCE_SI[0].mh[ SOURCE_SI[0].FDindex_mhindex[FD] ][i] == new_SOURCE_SI_UNION.mh[ FD_mh_index ][i]){
                _sim++;/**签名上相同的个数用作估计si和s0相似度*/
            }
        }
        _sim = _sim/HASHN;/**得到s^*/
        double _predict_S_size = FD_domain[FD]*HASHN / sum_hash_value;/**得到估计的S大小*/
        //double _predict_S_S0_intersection = _sim*( S0_per_FD_set_size[FD] + _predict_S_size )/( 1 + _sim );/**估计的S0和S的交集大小*/
        /**SOURCE_SI[0].setSzie[ SOURCE_SI[0].FDindex_mhindex[FD] ]保存S0的每个FD的投影的集合大小,用来估计x^: x^=s^*(a+b^)/(1+s^) 及其中的a的值*/
        double _predict_S_S0_intersection = _sim*( SOURCE_SI[0].setSzie[ SOURCE_SI[0].FDindex_mhindex[FD] ] + _predict_S_size )/( 1 + _sim );/**估计的S0和S的交集大小*/
        sum_per_FD_intersection += _predict_S_S0_intersection;/**把每个FD上的交集大小相加*/
    }
    tmp_SOURCE_SI_UNION = new_SOURCE_SI_UNION;/**临时拷贝*/
    return sum_per_FD_intersection;
}
int MAX_Cov()/**返回值为选哪个si可以得到最大的收益(cov(SUsi)-cov(S))，对应的si的序号*/
{
    source_Si_union final_union;
    int select_index = -1;
    double MAX_newcov_sub_oldcov = 0;
    for(int i=1;i<=The_number_of_generate_file;i++)
    {
        if(si_if_selected[i] == true) continue;

        double cov_value = computeCov(i);/**计算S中加入si后得到的对S0的估计覆盖值*/
        double newcov_sub_oldcov;/**计算(cov(SUsi)-cov(S))或(cov(SUsi)-cov(S))/ci*/
        if(if_add_random_weight == true)/**如果要带随机权重*/
            newcov_sub_oldcov = (cov_value - MAX_cov)/file_random_weight[i];
        else
            newcov_sub_oldcov = cov_value - MAX_cov;
        if(MAX_newcov_sub_oldcov < newcov_sub_oldcov)
        {
            select_index = i;
            MAX_newcov_sub_oldcov = newcov_sub_oldcov;/**更新最大收益*/
            MAX_cov = cov_value;/**记录最大覆盖值*/

            final_union = tmp_SOURCE_SI_UNION;
        }
    }
    SOURCE_SI_UNION = final_union;/**保留选择的最佳的si加入后的并集S*/
    return select_index;
}
/**
   argv1数据源个数
   argv2哈希函数个数
   argv3选择数据源个数k
   argv4目标数据集的元组个数所占最大数的比例
   argv5数据源的元组个数所占的最大比例
   argv6元组个数上限
   argv7是否要给每个数据源添加一个随机权重"add_random_weight_YES" "add_random_weight_NO"
*/
int main(int argc, const char *argv[])
{
    /*argv[1]="1000";
    argv[2]="200";
    argv[3]="5";
    argv[4]="100";
    argv[5]="100";
    argv[6]="2000";
    argv[7]="add_random_weight_YES";
    */
    srand(time(NULL));
    if_add_random_weight = ((strcmp(argv[9],"add_random_weight_YES")==0)?true:false);
    The_number_of_generate_file = atoll(argv[1]);
    HASHN = atoll(argv[2]);
    Max_select = atoll(argv[3]);

//    synthetic_setDomain();/**设置合成数据各个FD值域*/
    book_or_flight_setDomain();/**设置真实数据FD值域*/

    string filename_path = dir + "FileName_" + argv[6] + ".txt";
    readFilename(filename_path, The_number_of_generate_file);
    The_number_of_generate_file = filename.size() - 1;/**根据实际生成的文件数调整参数*/
    for(int i=0;i<The_number_of_generate_file+5;i++)/**标记Si是否被选择过*/
        si_if_selected.push_back(false);
    if(if_add_random_weight == true){
        ifstream fiin;
        string randomweightpath = dir + "random_weight.txt";
        fiin.open(randomweightpath.c_str(), ios::in);
        cout<<"#add_random_weight"<<endl;
        for(int i=0;i<=The_number_of_generate_file;i++)/**给每个文件随机分配一个1-10的权重*/
        {
            string sss;
            fiin>>sss;
            file_random_weight.push_back(atof(sss.c_str()));
            cout<<"--source "<<i<<" weight:"<<file_random_weight[file_random_weight.size()-1]<<endl;
        }
        fiin.close();
    }

    //-------------------------------------------------------
    clock_t start, finish;
    double totaltime = 0;
    start = clock();
    //-------------------------------------------------------
    string mhpath;
    mhpath = dir + "mh_" + argv[6] + ".txt";
    readMH(mhpath);/**读取mh文件*/
    //-------------------------------------------------------
    vector<long long>select_file_to_cov;
    for(int i=0;i<Max_select;i++)
    {
        int select_si_index = MAX_Cov();/**返回值为选哪个si可以得到最大的收益(cov(SUsi)-cov(S))，对应的si的序号*/
        if(select_si_index == -1)break;
        si_if_selected[select_si_index] = true;/**已选过的Si做标记*/
        select_file_to_cov.push_back(select_si_index);/**把选出的文件的下标保存，用作最后输出*/
    }
    finish = clock();
    totaltime = (double)(finish - start)/(double)CLOCKS_PER_SEC;
    cout<<"估计最大覆盖值:"<<MAX_cov<<endl;
    //-------------------------------------------------------
    ofstream fout;
    string file = dir + "output\\mh_greedy_runtime.txt";
    fout.open(file.c_str(), ios::out|ios::app);
    fout<<argv[1]<<"_"<<argv[2]<<"_"<<argv[3]<<"_"<<argv[4]<<"_"<<argv[5]<<"\t"<<totaltime<<endl;
    fout.close();
    /**将选择的数据源名输出到文件*/
    cout<<"#Src="<<select_file_to_cov.size()<<endl;
    cout<<"#Covered="<<MAX_cov<<endl;
    file = dir + argv[1] + "_" + argv[2] + "_" + argv[3] + "_" + argv[4] + "_" + argv[5] + "_" + argv[6] + "_SelectedSrcs.txt";
    fout.open(file.c_str(), ios::out);
    fout<<"mh_greedy\n";
    fout<<filename[0]<<"\n";
    for(int i=0;i<select_file_to_cov.size();i++)
    {
        fout<<filename[ select_file_to_cov[i] ]<<"\n";
        cout<<"--source "<<select_file_to_cov[i]<<endl;
    }
    fout.close();
    //---------------------------------------------------------
    cout<<"RANDOM:"<<endl;
    file = dir + argv[1] + "_" + argv[2] + "_" + argv[3] + "_" + argv[4] + "_" + argv[5] + "_" + argv[6] + "_random_SelectedSrcs.txt";
    fout.open(file.c_str(), ios::out);
    fout<<"random\n";
    set<int>rand_set;
    while(rand_set.size() < Max_select)
    {
        int r = rand()%(filename.size()-1) + 1;
        if(rand_set.find(r)!=rand_set.end())
            r = rand()%(filename.size()-1) + 1;
        rand_set.insert(r);
        fout<<r<<".txt\n";
        cout<<"--Source "<<r<<endl;
    }
    fout.close();
    return 0;
}
