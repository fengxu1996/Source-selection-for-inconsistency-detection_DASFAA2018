#include <bits/stdc++.h>

using namespace std;

string dir = "C:\\Users\\12433\\Desktop\\Data\\";

//int per_attr;
int no_tuple=2000;/**S0的元组个数，搭配min_perc和max_perc确定各个Si的元组个数*/
const int size_domain=1000;/**单个属性上的值域大小*/
int min_perc=10;/**生成的元组数的百分比的下界即一个生成的文档至少要有(no_tuple)*(min_perc/100)个元组*/
int max_perc=100;/**生成元组数的百分比的上界默认值设为100%(等到需要改变时可修改，此处设为保留参数)即一个文档元组数最多为(no_tuple)*(min_perc/100)个元组*/
int _sources = 100;/**除S0之外生成几个文档*/
int _hash;

struct HANSHUYILAI  /**函数依赖数据结构*/
{
    vector<string>QianJian;
    vector<string>HouJian;
};
vector<HANSHUYILAI>FD;  /**存储所有函数依赖*/
HANSHUYILAI HanshuYiLaiAdd(string yilai)  /**传入一个函数依赖的字符串,拆分转换为相应数据结构后返回*/
{
    int b=0,e=yilai.size()-1;
    while(yilai[b]!='('){b++;}
    while(yilai[e]!=')'){e--;}
    HANSHUYILAI a;
    string s="";
    for(int i=b+1; i<e; i++)
    {
        if(yilai[i]==','){
            a.QianJian.push_back(s);
            s = "";
        }
        else{
            s+=yilai[i];
        }
    }
    a.QianJian.push_back(s);
    s = "";
    for(int i=e+1; i<yilai.size(); i++)
    {
        if(yilai[i]==','){
            a.HouJian.push_back(s);
        }
        else{
            s+=yilai[i];
        }
    }
    a.HouJian.push_back(s);
    return a;
}
void readFD(string path)  /**读取FD规则*/
{
    ifstream fin;
    fin.open(path.c_str(), ios::in);
    string s;
    while(fin>>s)
    {
        FD.push_back(HanshuYiLaiAdd(s));  /**将函数依赖放入FD（vector<HASHUYILAI>）里*/
    }
    fin.close();
}
void constructS0(string s0path)/**创建S0文档*/
{
    ofstream fout;
    fout.open(s0path.c_str(), ios::out);
    set<string>S;
    for(int i=0;i<FD.size();i++) /**所有依赖上的属性统计到一起*/
    {
        for(int k=0;k<FD[i].QianJian.size();k++)
        {
            S.insert(FD[i].QianJian[k]);
        }
        for(int k=0;k<FD[i].HouJian.size();k++)
        {
            S.insert(FD[i].HouJian[k]);
        }
    }
    for(set<string>::iterator it=S.begin();it!=S.end();it++)
    {
        if(it==S.begin())
            fout<<*it;
        else
            fout<<" "<<*it;
    }
    fout<<"\n";
    for(int i=0;i<10;i++)/**输出依赖序号*/
    {
        if(i==0)
            fout<<i;
        else
            fout<<" "<<i;
    }
    fout<<"\n";
    set<string>flag;/**用于去重*/
    for(int i=0;i<no_tuple;i++)/**给s0构造no_tuple条元组{注:去重版本}*/
    {
        string tuple_str = "";
        for(int j=0;j<S.size();j++)/**在一个元组的每个属性上都随机生成一个数值,值域为[0,size_domain-1]*/
        {
            char attr_value[20];
            sprintf(attr_value, "%d_%d", j, rand()%size_domain);
            if(j==0)
                tuple_str = tuple_str + attr_value;
            else
                tuple_str = tuple_str + " " + attr_value;
        }
        if(flag.find(tuple_str)==flag.end()){
            flag.insert(tuple_str);
            fout<<tuple_str<<"\n";
        }
        else{/**发现重复值则要重新生成元组*/
            i--;
        }
    }
    fout.close();

    cout<<flag.size()<<endl;
}
void constructSi(string sipath)/**创建一个Si文档*/
{
    /**需要设定此次文档元组数大小*/
    int si_no_tuple_min = ceil(((double)min_perc/100)*no_tuple);/**si文档的元组个数下界*/
    int si_no_tuple_max = ceil(((double)max_perc/100)*no_tuple);/**si文档的远足个数上界*/
    int si_no_tuple = rand()%(si_no_tuple_max-si_no_tuple_min+1)+si_no_tuple_min;/**确定文档Si的元组个数*/
    /**从10个依赖中随机选择一个*/
    int FD_choiced_index = rand()%10;

    /**取出这个依赖的所有属性*/
    vector<string>attr;
    for(int i=0;i<FD[FD_choiced_index].QianJian.size();i++)attr.push_back(FD[FD_choiced_index].QianJian[i]);
    for(int i=0;i<FD[FD_choiced_index].HouJian.size();i++)attr.push_back(FD[FD_choiced_index].HouJian[i]);

    ofstream fout;
    fout.open(sipath, ios::out);
    for(int i=0;i<attr.size();i++)if(i==0){fout<<attr[i];}else{fout<<" "<<attr[i];}/**输出属性*/
    fout<<"\n";
    fout<<FD_choiced_index<<"\n";/**输出所选FD的序号*/
    set<string>flag;/**用于去重*/
    for(int i=0;i<si_no_tuple;i++)/**给si构造si_no_tuple条元组*/
    {
        string tuple_str = "";
        for(int j=0;j<attr.size();j++)
        {
            char attr_value[20];
            sprintf(attr_value, "%s_%d", attr[j].c_str(), rand()%size_domain);
            if(j==0){
                tuple_str = tuple_str + attr_value;
            }
            else{
                tuple_str = tuple_str + " " + attr_value;
            }
        }
        if(flag.find(tuple_str)==flag.end()){
            flag.insert(tuple_str);
            fout<<tuple_str<<"\n";
        }
        else{/**发现重复值则要重新生成元组*/
            i--;
        }
    }
    fout.close();
    cout<<flag.size()<<endl;
}
int main(int argc, const char *argv[])
{
    _sources = atoi(argv[1]);
//    _hash = argv[2];
//    argv[3];

    max_perc = atoi(argv[4]);
    no_tuple = atoi(argv[6]);

    srand(time(NULL));
    string pathFD = dir + "input\\FD.txt";
    readFD(pathFD);  /**读取FD规则*/
    char s0path0[50];
    sprintf(s0path0, "%s%d_%d.txt",dir.c_str(), no_tuple, 0);
    string s0path = s0path0;
    constructS0(s0path);  /**创建S0*/
    for(int i=1;i<=_sources;i++)  /**创建 _sources 个 Si*/
    {
        char sipath0[50];
        sprintf(sipath0, "%s%d_%d.txt", dir.c_str(), no_tuple, i);
        string sipath = sipath0;
        constructSi(sipath);
    }

    char Filename[50];
    sprintf(Filename, "%sFileName_%d.txt", dir.c_str(), no_tuple);
    ofstream fout;
    fout.open(Filename, ios::out);
    for(int i=0;i<=_sources;i++)
    {
        char fn[30];
        sprintf(fn, "%d_%d.txt", no_tuple, i);
        fout<<fn<<"\n";
    }
    fout.close();
    /**生成随机权重*/
    string randomweightpath = dir + "random_weight.txt";
    fout.open(randomweightpath.c_str(), ios::out);
    for(int i=0;i<=_sources;i++)
    {
        fout<<(rand()%10+1)<<"\n";
    }
    fout.close();
    return 0;
}
