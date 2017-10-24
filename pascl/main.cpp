#include <iostream>
#include <stack>
#include <stdlib.h>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;
stack<string> check;

void keyWord(string temp, int line){
    if(temp == "begin"){
        check.push(temp);
    }else{
        if(check.empty()){
            cout<<"Error in line "<<line<<". You should use 'Begin' at the start of a code block."<<endl;
            exit(0);
        }
        if(temp=="if"){
            if(check.top() != "if"){
                check.push(temp);
            }else{
                cout<<"Error in line "<<line<<". You shoud not use 'if' after 'if'."<<endl;
                exit(0);
            }
        }else if(temp=="then"){
            if(check.top() == "if"){
                check.push(temp);
            }else{
                cout<<"Error in line "<<line<<". No match 'if' before 'then'."<<endl;
                exit(0);
            }
        }else if(temp=="else"){
            if(check.top() == "then"){
                check.pop();
                check.pop();
            }else{
                cout<<"Error in line "<<line<<". No match 'then' before 'else'."<<endl;
                exit(0);
            }
        }else if(temp == "end"){
            if(check.top() == "then"){
                check.pop();
                check.pop();
            }
            if(check.top() == "begin"){
                check.pop();
            }else{
                cout<<"Error in line "<<line<<". No match 'begin' before 'end'."<<endl;
                exit(0);
            }
        }
    }
}

void judgePac(string file){
    ifstream infile;               // ��ȡ�ļ�
    infile.open(file.data());
    assert(infile.is_open());

    string s;
    int line = 0;
    cout << "Opening file " << file << " success! Start checking..." << endl;
    while(getline(infile, s)){      // ���ж�ȡ
        line += 1;
        if(!s.empty()){             // ���˵��հ���
            string temp("");
            s += ';';               // ����ȡ�����һ����
            for(int i = 0; i < s.size(); i++){      // ���ֽڶ�ȡ
                if(temp=="//"||temp=="{") break;      // ����ע�ͷ�������
                if(s[i]==' '||s[i]=='('||s[i]==')'||s[i]=='\t'||s[i]==';'){     // ����ͣ�ٷ���ȡ��ǰһ����
                    if(temp=="begin"||temp=="end"||temp=="if"||temp=="then"||temp=="else") keyWord(temp, line);     // Ϊ�ؼ�����ִ���ж�
                    temp = "";
                }
                else{       // ����ͣ�ٴ����ۼӵ�ǰ�ַ�
                    temp += s[i];
                }
            }
        }
    }
    if(check.empty()){      // ����������ж϶�ջ�Ƿ�Ϊ��
        cout<<"Correct!"<<endl;
    }else{
        cout<<"Incorrect! 'end' missed at the end."<<endl;
        exit(0);
    }
    infile.close();
}

int main(){
    judgePac("test_pascal.pas");            // ִ���ж�����
    cout << "Checking finished!" << endl;
    return 0;
}
