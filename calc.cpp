#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <locale>
#include <sstream>

using namespace std;



vector<string> split(string s){
    vector<string> res;
    stringstream ss(s);
    string w;
    
    while (ss >> w) {
        size_t pos = 0;
        while (pos < w.size()) {
            if (w[pos] == '*' || w[pos] == '/' || w[pos] == '+' || w[pos] == '-') {     
                if (pos > 0) {
                    res.push_back(w.substr(0, pos));
                }             
                res.push_back(std::string(1, w[pos]));             
                w = w.substr(pos + 1);
                pos = 0; 
            } else {
                pos++;
            }
        }       
        if (!w.empty()) {
            res.push_back(w);
        }
    }
    return res;    
}

string calc(vector<string> s){
    string r;
    string f;
    for(int i=0;i<s.size();++i){
        
        if(s[i] == "*"){
            r=to_string(stod(s[i-1])*stod(s[i+1]));
            s.erase(s.begin()+i-1,s.begin()+i+2);
            s.insert(s.begin()+i-1,r);
            
        }
        if(s[i] == "/"){
            r=to_string(stod(s[i-1])/stod(s[i+1]));
            s.erase(s.begin()+i-1,s.begin()+i+2);
            s.insert(s.begin()+i-1,r);
            
        }
    }
    
    for(int i=0;i<s.size();++i){
        
        if(s[i] == "+"){
            r=to_string(stod(s[i-1])+stod(s[i+1]));
            s.erase(s.begin()+i-1,s.begin()+i+2);
            s.insert(s.begin()+i-1,r);
            
        }
        if(s[i] == "-"){
            r=to_string(stod(s[i-1])-stod(s[i+1]));
            s.erase(s.begin()+i-1,s.begin()+i+2);
            s.insert(s.begin()+i-1,r);
            
        }
    }
    
    f=s[0];
    return f;
}
    
string brakets(string v){
    vector<map<int, int>> a;
    vector<map<int, int>> b;
    int r = 1;
    int f =1;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == '(') {
            a.push_back({{r, i}});
            r++;
        } 
    }
    
    r=1;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == '(') {
            
            for (int j = i; j < v.size(); ++j) {
                if (v[j] == '(') {
                    r++;
                }
                if(v[j] == ')' and r!=f){
                    r--;
                }
                if(v[j] == ')' and r==f){
                    b.push_back({{f, j}});
                    f++;
                    r=f;
                    break;
                }
            }       
        } 
    }
  
    string d;
    int w,q;
    for (int i = a.size(); i >0; --i) {
        w=a[i-1][i];
        q=b[i-1][i];
        d=calc(split(v.substr(w+1,q-w-1)));
        v.erase(w,q-w+1);
        v.insert(w,d);
        break;
    }
    return v;
}


int main()
{
    vector<string> res;
    string v1,v2;
    getline(cin, v1);
    string b = brakets(v1);
    cout<<calc(split(b));
}
