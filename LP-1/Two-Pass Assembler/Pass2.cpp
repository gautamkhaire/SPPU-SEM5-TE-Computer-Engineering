#include<bits/stdc++.h>
using namespace std;

string table(ifstream &fin, string n){
    string no,name,addr;
    while(fin >> no >> name >> addr){
        if(no == n){
            fin.seekg(0,ios::beg); // Reinitializing Pointer to Start of File
            return addr;
        }
    }
    fin.seekg(0,ios::beg);
    return "NAN";
}

int main(){

    ifstream ic, st, lt;    
    ic.open("ic.txt");
    st.open("symbol.txt");
    lt.open("literal.txt");

    ofstream mct;
    mct.open("machine_code.txt");
    string lc,ic1,ic2,ic3;

    cout << "\n \t\t\t --- PASS 2 OUTPUT ---\n";
    cout << "\n LC\t <INTERMEDIATE CODE>\t\t\tLC\t <MACHINE CODE>" << "\n";

    while(ic >> lc >> ic1 >> ic2 >> ic3){
        string MC = "";

        if(ic1.substr(1,2) == "AD" || (ic1.substr(1,2) == "DL" && ic1.substr(4,2) == "02")){
            MC += "---No Machine Code---";
        }
        else if(ic1.substr(1,2) == "DL" && ic1.substr(4,2)=="01"){
            MC += "00\t0\t00" + ic2.substr(3,1);
        }
        else{ // IS opcode
            if(ic1.substr(4,2) == "00"){ // STOP
                MC += "00\t0\t000";
            }
            else{
                if(ic3.substr(1,1) == "S"){
                    MC += ic1.substr(4,2) + "\t" + ic2.substr(1,1) + "\t" + table(st,ic3.substr(4,1)); 
                }
                else // literals
                    MC += ic1.substr(4,2) + "\t" + ic2.substr(1,1) + "\t" + table(lt,ic3.substr(4,1));
            }
        }
        // cout << "here\n";    
        cout << " " << lc << "\t" << ic1 << "\t" << ic2 << "\t" << ic3 << "\t\t\t" << lc << "\t" << MC << "\n";
        mct << lc << " " << MC << "\n";  
    }      

    return 0;
}