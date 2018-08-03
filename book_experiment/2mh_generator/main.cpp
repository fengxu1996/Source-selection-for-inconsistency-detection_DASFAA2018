#include <bits/stdc++.h>
#include <ctime>
using namespace std;

ofstream fout;
int  hashmethod=0;/**选择hash方法0为(ax+b)%c; 1为murmurhash*/
long long murmurhash_Seed_start_pos=0 ;/**设置murmurhash种子开始位置*/
double RUNTIME=0;
const string dir="C:\\Users\\12433\\Desktop\\Data_book\\";
string outPath="";
long long HASHN=1000;
long long C=1000003;/**作为(A*x+B)%C中的C 大于等于1000000的最小素数 1000000是因为属性组合后是一个六位数字所以确定出来的域为1000000*/
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
vector<string>FILENAME;/**FILENAME[0]是待修复 后面跟的是数据源集合*/
double epsilon, delta, n_mh;/**赋值后调用f_hash()函数就好了*/
struct nod/**一个函数依赖的数据结构*/
{
    vector<string>qianJian;
    vector<string>houJian;
};
struct hashParameter
{
    long long A,B;
};
double f_hash()
{
    double a=epsilon*epsilon/3;
    double f=(2/(a*a))*(log(2/delta));
    return min(f,n_mh);
}
vector<nod>HanShuYiLai;/**函数依赖集*/
vector<hashParameter>HASH;/**hash函数集参数*/
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
/**这里需要修改，三位已经不适用了，这里设置成动态的，在数据生成时，顺便把值域输出到attrZhiyu.txt文件里，然后再这里使用*/
string mytrim(string s)//把下划线之前的无用的东西去掉只保留数字部分,变成三位长度的数字 001 123
{
    ifstream fin;
    fin.open(dir + "attrzhiyu.txt", ios::in);/**取出属性值域*/
    string attrzhiyu_str;
    long long attrzhiyu_Integer;
    fin>>attrzhiyu_str;
    fin.close();
    attrzhiyu_Integer = atoll(attrzhiyu_str.c_str());


    string k="";
    int i=0;
    while(s[i]!='_'){i++;}
    for(i=i+1;i<s.size();i++)
    {
        k+=s[i];
    }
    if(k.size()<attrzhiyu_str.size())
    {
        string ch="";
        int cnt=attrzhiyu_str.size()-k.size();
        while(cnt--)ch+='0';
        k=ch+k;
    }
    return k;
}
vector<hashParameter> hashi(int k)
{

    set<string>S;
    vector<hashParameter>v;
    /*for(int i=0;i<k;i++)
    {
        hashParameter xx;
        long long aindex = (rand()%10000)+(pnum-10001);
        long long bindex = (rand()%10000)+(pnum-10001);

        xx.A=prime[aindex];
        xx.B=prime[bindex];


        v.push_back(xx);
    }*/
    while(S.size()<k)
    {
        hashParameter xx;
        long long aindex = (rand()%10000)+(pnum-10001);
        long long bindex = (rand()%10000)+(pnum-10001);

        xx.A=prime[aindex];
        xx.B=prime[bindex];

        char sstr[50];
        sprintf(sstr, "%lld_%lld", xx.A, xx.B);

        string str =sstr;
        if(S.find(str)==S.end()){
            S.insert(str);
            v.push_back(xx);
        }
    }

    return v;
}
/**需要改*/
vector<long long> minhash(vector<string> attrV)//传入一个属性向量计算出minhash值
{
    long long minHASH[HASHN+10];
    for(int i=0;i<=HASHN+2;i++)minHASH[i]=-1;
    for(int i=0;i<attrV.size();i++)
    {
//        if(attrV[i].size()>3)
//            C=1000003;
//        else
//            C=1009;
        for(int k=0;k<HASHN;k++)
        {
            long long ihash;
            if(hashmethod == 0)/**选用第一种hash方法*/
                ihash= ( (  HASH[k].A*atoll(attrV[i].c_str()) +HASH[k].B  )% C )+1;
            else if(hashmethod == 1)/**选用第二种hash方法murmur hash*/
                ihash= (MurmurHash64B(attrV[i].c_str(), attrV[i].size(), prime[k+murmurhash_Seed_start_pos]) % C)+1;
            if(minHASH[k]!=-1)
            {
                minHASH[k]=min(minHASH[k],ihash);
            }
            else
            {
                minHASH[k]=ihash;
            }
        }
    }
    vector<long long>VV;
    for(int i=0;i<HASHN;i++)
    {
        VV.push_back(minHASH[i]);
    }
    return VV;
}
void exec(string filename)
{
    //ofstream ffout;
    //ffout.open(outPath.c_str(),ios::out);
    //ffout<<"("<<filename<<")"<<"\n";
    fout<<"("<<filename<<")"<<"\n";
    //ffout.close();
    string s;
    vector<string>attr;
    vector<string>functionSeti;/**函数依赖序号*/
    ifstream fin;
    fin.open(filename.c_str(),ios::in);
    getline(fin,s);//得到属性
    attr=split(s);

    getline(fin,s);//得到函数依赖
    functionSeti=split(s);

    map<string,int>M;//得到属性在dataTable中的编号
    for(int i=0;i<attr.size();i++)M[attr[i]]=i;

    vector<vector<string> >dataTable;
    while(getline(fin,s))
    {
        vector<string>t=split(s);
        dataTable.push_back(t);
    }
    fin.close();
    //cout<<"OKKKK dataTable len "<<dataTable.size()<<endl;
    //for(int i=0;i<dataTable.size();i++)cout<<dataTable[i].size()<<endl;
    //**统计运行时间*/
    //clock_t start,finish;
    //start=clock();

    for(int i=0;i<functionSeti.size();i++)//枚举每个函数依赖
    {
    //    cout<<"--FD "<<i<<endl;
        nod func=HanShuYiLai[ atoi(functionSeti[i].c_str()) ];
        vector<string>QianJian=func.qianJian;//这个函数依赖要用到的属性（即前件）
        vector<string>combinedAttr;//存储合并后的属性
        set<string>SET;
        //把这些属性拼成一个属性
        for(int k=0;k<dataTable.size();k++)//遍历每个元组
        {
            string combined="";//组合合并的属性
            for(int w=0;w<QianJian.size();w++)//遍历该元组上函数依赖前件包含的属性
            {
                combined+=mytrim(dataTable[k][   M[QianJian[w]]    ]);//M[QianJian[w]] 为前件上的属性在dataTable里的列号
            }
            combinedAttr.push_back(combined);/**需不需要改为，最后从set中取出，这样可保证属性向量没重复值，但也可在生成数据时处理*/
            SET.insert(combined);
        }
        /**此时完成一个函数依赖的前件属性的合并（如果多个的话合并）处理*/
        /**此时可以求出其中一组minhash了*/
        //ofstream fout;
        //fout.open(outPath.c_str(),ios::out|ios::app);
        fout<<"["<<functionSeti[i]<<"]";
        fout<<" {"<<SET.size()<<"}";
        vector<string>fqianJian,fhouJian;
        fqianJian=func.qianJian;
        fhouJian=func.houJian;
        for(int ww=0;ww<fqianJian.size();ww++){
            fout<<" "<<fqianJian[ww];
        }
        fout<<" :";
        for(int ww=0;ww<fhouJian.size();ww++){
            fout<<" "<<fhouJian[ww];
        }
        fout<<" ;";

        /**得到minhash*/
        vector<long long>mm=minhash(combinedAttr);
        if(mm.size()!=HASHN){ cout<<"!!!!!!!!!!!!!"<<endl;exit(0);}
        for(int ww=0;ww<mm.size();ww++)
        {
            fout<<" "<<mm[ww];
        }
        fout<<"\n";
        //fout.close();
    }
}

void confirmC()
{
    ifstream fin;
    fin.open(dir + "attrzhiyu.txt", ios::in);/**取出属性值域*/
    string attrzhiyu_str;
    long long attrzhiyu_Integer;
    fin>>attrzhiyu_str;
    fin.close();
    attrzhiyu_Integer = atoll(attrzhiyu_str.c_str());
    C=prime[lower_bound(prime, prime+pnum, attrzhiyu_Integer)-prime];

}
int main(int argc, char * argv[])
{
    HASHN=atoi(argv[2]);
    srand((unsigned)time(NULL));
    RUNTIME=0;
    /**大素数__________________________*/
    long long NN=999999;
    GetPrime(NN);
    /**大素数__________________________*/

//    /**确认C值*/
//    confirmC();
    /**确定hash函数*/
    HASH=hashi(HASHN);
    string hashstr = argv[8];
    if(hashstr == "murmurhash")
        hashmethod = 1;
    else if(hashstr == "(ax+b)%c")
        hashmethod = 0;
    murmurhash_Seed_start_pos = rand()%10000;/**在prime[]中随机找一个素数作为murmurhash种子*/

    string s;
    ifstream fin;
    string infile=dir+"FileName_"+argv[6]+".txt";
    fin.open(infile.c_str(),ios::in);
    /**FILENAME[0]是待修复 后面跟的是数据源集合*/
    int no_file=atoi(argv[1]);
    int cnt_file=0;
    while(fin>>s&&cnt_file<=no_file){ /**选了前no_file个文件（不包括S0！！！！！！！！！！！！！）*/
        FILENAME.push_back(dir+s);
        cnt_file++;
    }
    fin.close();
    infile="";
  //  infile=dir+"input\\FD.txt";
  infile=dir+"FD.txt";
    fin.open(infile.c_str(),ios::in);
    while(fin>>s)
    {
        HanShuYiLaiAdd(s);
    }
    fin.close();
    //cout<<"OK1"<<endl;
    string filename;//="dataSet\\60_10_0.txt";//"dataSet\\60_10_0.txt";
    outPath=dir+"mh_"+argv[6]+".txt";
    fout.open(outPath.c_str(),ios::out);/**gaidong*/

    for(int i=0;i<FILENAME.size();i++)
    {
        if(i%10==0)
        cout<<"File "<<i<<" ";/**用来查看进度每隔10个输出了一次*/
        filename=FILENAME[i];
        exec(filename);
    }
    cout<<endl;
    //exec(filename);

    fout.close();/**gaidong*/

    return 0;
}
