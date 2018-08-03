/**
用于book

需要修改！！可以在 flight数据上应用
但在book上不好使，因为book名占了多列

因为ISBN形式不固定，这里把前程序修改为采用正则进行匹配

*/

#include <bits/stdc++.h>
#include <ctime>
#include <set>
#include <algorithm>

#include<regex>
using namespace std;
string ISBN_regex_pattern1="\\d{9}[\\d|\\w]";
string ISBN_regex_pattern2="\\d{12}[\\d|\\w]";

string ISBN_regex_pattern3="[0-9]{9}[0-9|a-z|A-Z]";
string ISBN_regex_pattern4="[0-9]{12}[0-9|a-z|A-Z]";

regex pattern1(ISBN_regex_pattern1);
regex pattern2(ISBN_regex_pattern2);
regex pattern3(ISBN_regex_pattern3);
regex pattern4(ISBN_regex_pattern4);


int min_no_book=1;
//int max_no_book=1000;
int max_no_book=300;
map<string,int> ISBN;
map<string,int>map_src;
vector<set<string> > books;/**猜测每个集合里存的是一个书名的所有ISBN*/
const string dir="C:\\Users\\12433\\Desktop\\Data_book\\";
bool cmp(set<string> x,set<string> y){
    if(x.size() >= y.size()){
        return true ;
    }else{
        return false;
    }
}
bool check_if_ISBN(string s)/**检查是不是ISBN号*/
{

    if(regex_match(s,pattern1)||regex_match(s,pattern2))return true;
    return false;
}

int main(int argc, char * argv[])
{
//    argv[1]="200";argv[2]= "100";argv[3]= "1";argv[4]= "100";argv[5]= "100"; argv[6]="book";argv[7]= "SelectedSrcs";

    map<string,int>::iterator it;
   ifstream ifstr;
   string infile=dir+"input\\book.txt";/**!!!!!!!!!!!!!!!!!!!*/
   ifstr.open(infile.c_str(),ios::in);
   string s="";
   string booknamestr="";

   while(ifstr>>s){
        string ISBNstr;
        if(check_if_ISBN(s)){/**是ISBN*/
            //booknamestr = "";
            ISBNstr = s;

            //getline(ifstr,s);
        }
        else{
            booknamestr+=s;
            continue;
        }

        if(map_src.find(booknamestr)==map_src.end()){/**没有这个书名就新加一个映射1...*/
            //string ISBNstr=s;
            //ifstr>>s;
            set<string> tmp_S;
            tmp_S.insert(ISBNstr);
            map_src[booknamestr]=books.size();/**是书名--对应的书名在vector<set<string>>books的下标*/
            books.push_back(tmp_S);/**1...并给这个书名在books里添加一个集合*/
        }
        else{
            it=map_src.find(booknamestr);/**如果有这个书名*/

            int pos=it->second;/**把它在books里的序号取出*/
           // ifstr>>s;          /**读ISBN号*/

            books[pos].insert(ISBNstr);  /**把ISBN号插到集合里*/

        }
      //  ISBN.insert(s);
        it=ISBN.find(s);
        if(it==ISBN.end()){/**是为了统计ISBN的集合（域）大小吗     存贮格式为 ISBN--编号 知道了！！！原来是为了给所有ISBN编号最后将其作为值输出*/
            ISBN[s]=ISBN.size();
        }

        getline(ifstr,s);/**没有后续处理，是丢弃了吗，还是只处理书名和ISBN */
        booknamestr="";/**清空字符串准备接收下一个书*/
   }
   ifstr.close();
   cout<<"#elements="<<ISBN.size()<<endl;
   sort(books.begin(),books.end(),cmp);
   ofstream ofstr_filename;
   string tmp_s=dir+"\\FileName_"+argv[6]+".txt";/**是要将文件名输出到一个文件吗*/
   ofstr_filename.open(tmp_s.c_str(),ios::out);
   int book_cnt=0;
   for(int i=0;i<books.size();i++){
        if(books[i].size()<min_no_book)
            continue;
        if(books[i].size()>max_no_book&&i!=0)/**?????????????为什么i==0时候就可以超出 max_no_book 大小  知道了是为了保证S0比其他的集合都要大*/
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
