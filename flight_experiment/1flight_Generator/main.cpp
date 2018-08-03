/**
用于flight

需要修改！！可以在 flight数据上应用
但在book上不好使，因为book名占了多列

为了和book容易区分把输入路径改为input\\flight.txt
*/

#include <bits/stdc++.h>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;
int min_no_book=1;
//int max_no_book=1000;
int max_no_book=300;
map<string,int> ISBN;
map<string,int>map_src;
vector<set<string> > books;/**猜测每个集合里存的是一个书名的所有ISBN*/
const string dir="C:\\Users\\12433\\Desktop\\Data_flight\\";
bool cmp(set<string> x,set<string> y){
    if(x.size() >= y.size()){
        return true ;
    }else{
        return false;
    }
}
int main(int argc, char * argv[])
{
//    argv[1]="200";argv[2]= "100";argv[3]= "1";argv[4]= "100"; argv[5]="100";argv[6]= "flight";argv[7]= "SelectedSrcs";

    map<string,int>::iterator it;
   ifstream ifstr;
   string infile=dir+"input\\flight.txt";/**!!!!!!!!!!!!!!!!*/
   ifstr.open(infile.c_str(),ios::in);
   string s="";

   while(ifstr>>s){
        if(map_src.find(s)==map_src.end()){/**没有这个书名就新加一个映射1...*/
            string src=s;
            ifstr>>s;
            set<string> tmp_S;
            tmp_S.insert(s);
            map_src[src]=books.size();/**是书名--对应的书名在vector<set<string>>books的下标*/
            books.push_back(tmp_S);/**1...并给这个书名在books里添加一个集合*/
        }
        else{
            it=map_src.find(s);/**如果有这个书名*/

            int pos=it->second;/**把它在books里的序号取出*/
            ifstr>>s;          /**读ISBN号*/
            books[pos].insert(s);  /**把ISBN号插到集合里*/

        }
      //  ISBN.insert(s);
        it=ISBN.find(s);
        if(it==ISBN.end()){/**是为了统计ISBN的集合（域）大小吗     存贮格式为 ISBN--编号 知道了！！！原来是为了给所有ISBN编号最后将其作为值输出*/
            ISBN[s]=ISBN.size();
        }
        getline(ifstr,s);/**没有后续处理，是丢弃了吗，还是只处理书名和ISBN */
   }
   ifstr.close();
   cout<<"#elements="<<ISBN.size();
   sort(books.begin(),books.end(),cmp);
   ofstream ofstr_filename;
   string tmp_s=dir+"\\FileName_"+argv[6]+".txt";
   ofstr_filename.open(tmp_s.c_str(),ios::out);
   int book_cnt=0;
   for(int i=0;i<books.size();i++){
        if(books[i].size()<min_no_book)
            continue;
        if(books[i].size()>max_no_book&&i!=0)/**?????????????为什么i==0时候就可以超出 max_no_book 大小*/
            continue;
        char tmp[20];

        sprintf(tmp, "%d.txt", book_cnt);
        ofstr_filename<<tmp<<endl;
        //ofstr_filename<<itoa(book_cnt,tmp,10)<<".txt"<<endl;


        ofstream ofstr;
        cout<<"--Source "<<book_cnt<<":"<<books[i].size()<<endl;

        sprintf(tmp, "%d.txt", book_cnt);
        string outfile=dir+tmp;
//        string outfile=dir+itoa(book_cnt,tmp,10)+".txt";
        ofstr.open(outfile.c_str(),ios::out);
        ofstr<<"0 1"<<endl;
        ofstr<<"0"<<endl;
        set<string>::iterator set_it;
        int cnt=0;
        for(set_it=books[i].begin();set_it!=books[i].end();set_it++){
            //cout<<*set_it<<endl;
            if(ISBN[*set_it]){
           //     cout<<ISBN[*set_it]<<endl;
                ofstr<<"0_"<<ISBN[*set_it]<<" "<<"1_"<<cnt<<endl; /**0_后跟的是ISBN的编号 1_后跟的是按顺序编号 */
            }
            else
                cout<<"cannot find in ISBN"<<endl;
            cnt++;
        }
        ofstr.close();
        book_cnt++;
   }
   ofstr_filename.close();
   tmp_s=dir+"\\FD.txt";
   ofstr_filename.open(tmp_s.c_str(),ios::out);
   ofstr_filename<<"(0)1"<<endl;
   ofstr_filename.close();

    /**把属性的值域输出，用于mh_generator里使用*/
   ofstream ooout;
   string oooutpath = dir + "attr_zhiyu.txt";
   ooout.open(oooutpath, ios::out);
   ooout<<ISBN.size()<<"\n";
   ooout.close();


   /**生成随机权重*/
    string randomweightpath = dir + "random_weight.txt";
    ofstream fout;
    fout.open(randomweightpath.c_str(), ios::out);
    for(int i=0;i<book_cnt;i++)
    {
        fout<<(rand()%10+1)<<"\n";
    }
    fout.close();
   return 0;
}
