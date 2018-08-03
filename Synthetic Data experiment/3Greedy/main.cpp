#include <bits/stdc++.h>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;
vector<int>::iterator ik;
set<string>::iterator it;
set<string>::iterator itt;
vector<vector<int> > FD;
const int no_FD=10;
const int no_attr=10;
int no_source=100;
vector<set<string> > pattern;
set<string> CoveredSet;/**?????   */
vector<int> SelectedSrc;
int vis_pattern[1000000+10];
int max_no_set=10;/** */
vector<string> File;/**存储(FileName_****.txt)里的文件名*/
string dir="C:\\Users\\12433\\Desktop\\Data\\";
bool if_add_random_weight = false;
vector<double>file_random_weight;/**保存每个数据源的随机权重*/
void init_FD(){
    vector<int> S;

    S.push_back(0);
    S.push_back(5);
    FD.push_back(S);
    S.clear();

    S.push_back(0);
    S.push_back(6);
    FD.push_back(S);
    S.clear();

    S.push_back(0);
    S.push_back(7);
    FD.push_back(S);
    S.clear();

    S.push_back(1);
    S.push_back(8);
    FD.push_back(S);
    S.clear();

    S.push_back(1);
    S.push_back(9);
    FD.push_back(S);
    S.clear();

    S.push_back(4);
    S.push_back(8);
    FD.push_back(S);
    S.clear();

    S.push_back(4);
    S.push_back(9);
    FD.push_back(S);
    S.clear();

    S.push_back(2);
    S.push_back(3);
    S.push_back(5);
    FD.push_back(S);
    S.clear();

    S.push_back(2);
    S.push_back(3);
    S.push_back(6);
    FD.push_back(S);
    S.clear();

    S.push_back(2);
    S.push_back(3);
    S.push_back(7);
    FD.push_back(S);
    S.clear();
}
void ComputePattern(){
    int fd=-1; /**保存当前使用的FD的序号*/
    ifstream ifstr;
    set<string> S;
    string s,p,tmp;
    string record[no_attr];/**！！！！！！！！！！！！！！use for what  --存了S0数据部分的第一行*/
    //读待修复文档，获取模式集合
    ifstr.open((dir+File[0]).c_str(),ios::in);
    getline(ifstr,s); //读属性集合
    getline(ifstr,s); //读FD集合
    int row=0;
    while(ifstr){
        for(int j=0;j<no_attr;j++){ /**????????读了S0的数据部分的第一行   存储数据部分每一行的值*/
            ifstr>>s;
            record[j]=s;
        }
        for(int j=0;j<no_FD;j++){/**对上面得到的一行值循环每个FD*/
            p="";
            tmp="";
            for(int k=0;k<FD[j].size()-1;k++){/**为什么读到size()-2就结束了，是不是有错误啊，还有这个record是干啥的-_-|  可能是只要前件因为后件只有一个属性*/
                p+=record[FD[j][k]];          /**把每个FD的前件属性上的值 attr_num 取出*/
                p+=",";
            }
            tmp=record[FD[j][FD[j].size()-1]];/**取出后件属性上的值用tmp保存*/
            for(int k=0;k<tmp.length();k++){ /**只把后件属性上的值 attr_num 中的attr取出, 追加到字符串p后面*/
                if(tmp[k]=='_')
                    break;
                p+=tmp[k];
            }
     //       cout<<p<<endl;
            S.insert(p);/**得到对应一个FD的字符串(attr1_num1,attr2_num2,...,attrn-1_numn-1,attrn)，放入S*/
        }
        row++;
    }
    pattern.push_back(S);
    ifstr.close();
 //   cout<<"#row="<<row<<endl;
    //读数据源，获取模式集合
    for(int i=1;i<File.size();i++){
    //        cout<<i<<endl;
        int row=0;
        fd=-1;
        S.clear();
        ifstr.open((dir+File[i]).c_str(),ios::in);
        getline(ifstr,s); //读属性集合
        getline(ifstr,s); //读FD集合/
        fd=atoi(s.c_str());/**获取当前是哪个FD*/
        while(ifstr){
            p="";
            tmp="";
            for(int j=0;j<FD[fd].size()-1;j++){/**获取当前属性的所有前件*/
                ifstr>>s;
                p+=s;
                p+=",";
            }
            ifstr>>s;
            for(int k=0;k<s.length();k++){/**获取后件的attr_num的attr部分*/
                if(s[k]=='_')
                    break;
                p+=s[k];
            }
      //      cout<<p<<endl;
            if(pattern[0].find(p)!=pattern[0].end())/**??????????????? 当前Si的元素在S0中存在才添加到pattern，是为了获取各个si与s0的交集吗 */
                S.insert(p);
            row++;
        }
        pattern.push_back(S);
        ifstr.close();
   //     cout<<"#row="<<row<<endl;
   }
    cout<<"To Cover "<<pattern[0].size()<<"elements"<<endl;
}
int GreedySelectSource(){
    int MaxCov = -1;
    int src_MaxCov =-1;
    int pos;

    double MAX_newcov_sub_oldcov = 0;
    double oldcov=0;
    set<string> NewCover;

    for(int i=1;i<pattern.size();i++){
        if(SelectedSrc[i]==1)
            continue;
        set_union(CoveredSet.begin(), CoveredSet.end(), pattern[i].begin(), pattern[i].end(), inserter(NewCover, NewCover.begin()));
   //     cout<<NewCover.size()<<endl;
        int tmp=NewCover.size();/*****一会在这里加权重！！！！！！！！****/
        double newcov_sub_oldcov;/**计算(cov(SUsi)-cov(S))或(cov(SUsi)-cov(S))/ci*/
        if(if_add_random_weight == true)/**如果要带随机权重*/
            newcov_sub_oldcov = (double)(tmp-oldcov)/file_random_weight[i];
        else
            newcov_sub_oldcov = (double)(tmp-oldcov);
        if(newcov_sub_oldcov>MAX_newcov_sub_oldcov)
        {
            oldcov = NewCover.size();
            MAX_newcov_sub_oldcov = newcov_sub_oldcov;
            MaxCov=NewCover.size();
            src_MaxCov=i;
        }
        /**if(tmp > MaxCov){
            MaxCov=NewCover.size();
            src_MaxCov=i;
        }*/
        NewCover.clear();
    }
    if(MaxCov==CoveredSet.size()){
        cout<<"no new elements can be covered!"<<endl;
        return -1;
    }
    //更新
   set_union(CoveredSet.begin(), CoveredSet.end(), pattern[src_MaxCov].begin(), pattern[src_MaxCov].end(), inserter(CoveredSet, CoveredSet.begin()));
    return src_MaxCov;
}

int main(int argc, char * argv[])
{
    /*argv[1]="1000";
    argv[2]="200";
    argv[3]="5";
    argv[4]="100";
    argv[5]="100";
    argv[6]="2000";*/
    //argv[7]="add_random_weight_YES";
   vector<int>SelSrcs;
   string s;
   no_source=atoi(argv[1]);/**生成文件个数*/
   max_no_set=atoi(argv[3]);/**选择的数据源个数*/

   srand(time(NULL));
   if_add_random_weight = (strcmp(argv[9],"add_random_weight_YES")==0?true:false);
   if(if_add_random_weight == true){
        ifstream fiin;
        string randomweightpath = dir + "random_weight.txt";
        fiin.open(randomweightpath.c_str(), ios::in);
        cout<<"#add_random_weight"<<endl;
        for(int i=0;i<=no_source;i++)/**给每个文件随机分配一个1-10的权重*/
        {
            string sss;
            fiin>>sss;
            file_random_weight.push_back(atof(sss.c_str()));
            cout<<"--source "<<i<<" weight:"<<file_random_weight[file_random_weight.size()-1]<<endl;
        }
        fiin.close();
    }


   clock_t start,finish;
   double totaltime;
   start=clock();
   init_FD();
   for(int i=0;i<=no_source;i++)/**可能是用来做标记的*/
        SelectedSrc.push_back(0);
   ifstream ifstr;
   string File_name;
   string infile=dir+"FileName_"+argv[6]+".txt";
   ifstr.open(infile.c_str(),ios::in);
   int cntt= no_source+1;
   while(ifstr>>File_name&&cntt--){    /**读入文件名列表到File里*/
        File.push_back(File_name);
   }
   ifstr.close();

   ComputePattern();/**得到S0的全集和各个Si与S0的交集*/
    for(int i=0;i<max_no_set;i++){
        int src=GreedySelectSource();
        if(src==-1)
            break;
   //     cout<<"--source "<<src<<endl;
        SelSrcs.push_back(src);
        SelectedSrc[src]=1;
    }
   finish=clock();
   totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
 //  cout<<"\n此程序的运行时间为"<<totaltime<<"秒！"<<endl;
    ofstream oout;
    string file=dir+"output\\greedy_runtime.txt";
    oout.open(file.c_str(),ios::out|ios::app);
    oout<<argv[1]<<"_"<<argv[2]<<"_"<<argv[3]<<"_"<<argv[4]<<"_"<<argv[5]<<"\t"<<totaltime<<"\n";
    oout.close();


//    s+="output\\greedy_result.txt";
//    file=dir+s;
//    oout.open(file.c_str(),ios::out|ios::app);
//    oout<<argv[1]<<"_"<<argv[2]<<"_"<<argv[3]<<"_"<<argv[4]<<"_"<<argv[5]<<"\t"<<pattern[0].size()<<"\t"<<CoveredSet.size()<<"\n";
//    oout.close();

    s="";
    s=s+argv[1]+"_"+argv[2]+"_"+argv[3]+"_"+argv[4]+"_"+argv[5]+"_"+argv[6]+"_greedy_SelectedSrcs.txt";
    file=dir+s;
    oout.open(file.c_str(),ios::out);
    oout<<"greedy\n";
    oout<<File[0]<<"\n";
    for(int i=0;i<SelSrcs.size();i++)
    {
        oout<<File[SelSrcs[i]]<<"\n";
    }
    oout.close();

   return 0;
}
