#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
void set_remainkey(string *p)//设置保留字数组，下标对应相应类别
{
    *p=" ";
    p++;
    *p="begin";
    p++;
    *p="end";
    p++;
    *p="integer";
    p++;
    *p="if";
    p++;
    *p="then";
    p++;
    *p="else";
    p++;
    *p="function";
    p++;
    *p="read";
    p++;
    *p="write";
    p++;
}
bool zimu(char x){
    //判断字符是否为字母
    if(x<65||(x>90&&x<97)||x>122){
        return 0;
    }
    else{
        return 1;
    }
}
bool shuzi(char x){
    //判断字符是否为数字
    if(x>47&&x<58){
        return 1;
    }else{
        return 0;
    }
}
int remainkey(string x){//判断该字符串是否为保留字
    string p[20];
    int i=0;
    set_remainkey(p);
    while(p[i]!=""){
        if(p[i]==x){
            return i;
        }
        i++;
    }
    return 0;
}
bool denghao(char x){
    if(x==61){
        return 1;
    }
    else{
        return 0;
    }
}
bool jianhao(char x){
    if(x==45)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool chenghao(char x){
    if(x==42){
        return 1;
    }
    else
    {
        return 0;
    }
}
bool zuokuohao(char x){
    if(x==40){
        return 1;
    }else
    {
        return 0;
    }
}
bool youkuohao(char x){
    if(x==41){
        return 1;
    }else {
        return 0;
    }
}
bool xiaoyu(char x){
    if(x==60){
        return 1;
    }else{
        return 0;
    }
}
bool dayu(char x){
    if(x==62){
        return 1;
    }
    else{
        return 0;
    }
}
bool fenhao(char x){
    if(x==59){
        return 1;
    }
    else{
        return 0;
    }
}
bool maohao(char x){
    if(x==58){
        return 1;
    }else{
        return 0;
    }
}
bool kongge(char x){
    if(x==' '){
        return 1;
    }
    else{
        return 0;
    }
}
void write_error(int i,int j,string l,string k=""){
    //i代表报错信息所在的行号，j代表报错类型，j为0时代表非法字符，j为1时代表冒号不匹配
    ofstream outfile_error(l,ios::app);
    if(0==j){
        //为非法字符时错误信息的写入
        string o="***LINE:";
        string p="  非法字符";
        stringstream stream;
        string v;
        stream<<i;
        v=stream.str();
        v=o+v+p+k+"\n";
        outfile_error<<v;
    }else if (1==j)
    {
        string o="***LINE:";
        string p="  冒号不匹配";
        stringstream stream ;
        string v;
        stream<<i;
        v=stream.str();
        v=o+v+p+"\n";
        outfile_error<<v;
    }
    outfile_error.close();
}
void write_result(int i,string l,string g=""){
    ofstream outfile_result(l,ios::app);
    if(1==i){
        outfile_result<<"           begin 01\n";
    }else if (2==i)
    {
        outfile_result<<"             end 02\n";
    }else if (3==i)
    {
        outfile_result<<"         integer 03\n";
    }
    else if (4==i)
    {
        outfile_result<<"              if 04\n";
    }else if (5==i)
    {
        outfile_result<<"            then 05\n";
    }else if (6==i)
    {
        outfile_result<<"            else 06\n";
    }
    else if (7==i)
    {
        outfile_result<<"        function 07\n";
    }else if (8==i)
    {
        outfile_result<<"            read 08\n";
    }else if (9==i)
    {
        outfile_result<<"           write 09\n";
    }else if (10==i)
    {
        string b="";
        int k;
        for(int j=0;j<16-g.length();j++){
            b+=' ';
        }
        string c=" 10\n";
        string a=b+g+c;
        outfile_result<<a;
    }else if (11==i)
    {
        string b="";
        int k;
        for(int j=0;j<16-g.length();j++){
            b+=' ';
        }
        string c=" 11\n";
        string a=b+g+c;
        outfile_result<<a;
    }
    else if (12==i)
    {
        outfile_result<<"               = 12\n";
    }else if (13==i)
    {
        outfile_result<<"              <> 13\n";
    }else if(14==i){
        outfile_result<<"              <= 14\n";
    }else if (15==i)
    {
        outfile_result<<"               < 15\n";
    }else if(16==i)
    {
        outfile_result<<"              >= 16\n";
    }else if (17==i)
    {
        outfile_result<<"               > 17\n";
    }else if (18==i)
    {
        outfile_result<<"               - 18\n";
    }else if (19==i)
    {
        outfile_result<<"               * 19\n";
    }else if(20==i)
    {
        outfile_result<<"              := 20\n";
    }else if (21==i)
    {
        outfile_result<<"               ( 21\n";
    }else if (22==i)
    {
        outfile_result<<"               ) 22\n";
    }else if (23==i)
    {
        outfile_result<<"               ; 23\n";
    }
    else if (24==i)//特殊情况加上行结束符号
    {
        outfile_result<<"            EOLN 24\n";
    }else{
        //文件结束时加入上最后的一行
        outfile_result<<"             EOF 25\n";
    }
    
    outfile_result.close();
}
void cifafenxi(string l){//l为文件名
    //词法分析功能实现函数
    ifstream infile(l);
    int line=1;//记录当前行数
    char x;
    string all="";
    int pos;
    pos = l.find(".pas");
    string resl=l.replace(pos,4,".dyd");//定义写结果二元式文件后缀
    string errl=l.replace(pos,4,".err");//定义写错误报告文件后缀
    infile.seekg(0,ios::beg);//初始将读写指针放在文件的首部
    ofstream outfile_result(resl);
    ofstream outfile_error(errl);
    outfile_result.write("",0);
    outfile_error.write("",0);
    outfile_error.close();
    outfile_result.close();//初始化将两个文件先清空
    while(!infile.eof()){
        all="";//初始化记录连接字符串组
        infile.get(x);
        if(x==' '){
            continue;
        }
        else if (zimu(x))
        {
            while(zimu(x)||shuzi(x)){
                all+=x;
                infile.get(x);
            }
            if(remainkey(all)){
                //如果是保留字的话
            write_result(remainkey(all),resl);//写保留字
            infile.seekg(-1,ios::cur);
        }else{
            write_result(10,resl,all);//不是保留字则写标示符
            infile.seekg(-1,ios::cur);//向前回退一个字符，即不满足要求的字符
        }
        }
        else if (shuzi(x))
        {
            while(shuzi(x)){
                all+=x;
                infile.get(x);
            }
            write_result(11,resl,all);
            infile.seekg(-1,ios::cur);
        }
        else if (denghao(x))
        {
            write_result(12,resl);
        }
        else if (jianhao(x))
        {
            write_result(18,resl);
        }
        else if (chenghao(x))
        {
            write_result(19,resl);
        }
        else if (zuokuohao(x))
        {
            write_result(21,resl);
        }
        else if (youkuohao(x))
        {
            write_result(22,resl);
        }
        else if (xiaoyu(x))
        {
            infile.get(x);
            if(denghao(x)){
                write_result(14,resl);
            }
            else if(dayu(x)){
                write_result(13,resl);
            }
            else{
                write_result(15,resl);
                infile.seekg(-1,ios::cur);
            }
        }
        else if (dayu(x))
        {
            infile.get(x);
            if(denghao(x)){
                write_result(16,resl);
            }else{
                write_result(17,resl);
                infile.seekg(-1,ios::cur);
            }
        }
        else if (maohao(x))
        {
            infile.get(x);
            if(denghao(x)){
                write_result(20,resl);
            }
            else{
                infile.seekg(-1,ios::cur);//没有单个冒号的情况，此时应该写入报错文件,根据状态转换图可知冒号后面只能跟等号
                write_error(line,1,errl);
            }
        }
        else if (fenhao(x))
        {
            write_result(23,resl);
        }
        else if(x=='\n'){
            //此时为行结束符，line记录行数应该加一,记录行数的原因是报错文件信息要加上行数
            write_result(24,resl);
            line++;
        }
        else{
            all+=x;
            write_error(line,0,errl,all);//为其他非法字符时报错
        }
    }
    //最后在文件末尾加上
    write_result(25,resl);
    infile.close();//关闭文件
}

int main(){
    string filename="demo.pas";
    cifafenxi(filename);
    return 0;
}
