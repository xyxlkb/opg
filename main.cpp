#include<stdio.h>
#include<string.h>
#include<stack>
#include<iostream>
using namespace std;
char ch[6] = {'+', '*', 'i', '(', ')','#'};
//char line[1005];
string line;
stack<int> st;
int p[6][6] = {
    {1,-1,-1,-1,1,1},
    {1,1,-1,-1,1,1},
    {1,1,2,2,1,1},
    {-1,-1,-1,-1,0,2},
    {1,1,2,2,1,1},
    {-1,-1,-1,-1,2,0}
};
int def(int c){
    for(int i=0;i<=5;i++){
    	if(c==ch[i]) return i;
	} 
    return 6;
}
char getvt(){
    if(def(st.top())<6)
        return st.top();
    else{
    	char c = st.top();
		st.pop();
        char t = st.top();
        st.push(c);
        return t;
	}
}
void analyse(){
    st.push('#');
    char rc,lc;
    int a,b,compare;
    for(int i=0;i<line.length();i++){
        rc=line[i]; 
        if(def(rc)<6){
            lc=getvt(); 
            a=def(lc); 
            b=def(rc); 
            compare=p[a][b];
            if(compare==2){
                printf("E\n");
                return;
            }
            if(compare<=0&&rc!='#'){
                st.push(rc);
                printf("I%c\n",rc);
            }
            else if(rc=='#'&&lc=='#'){
                return;
            }
            else{
                if(lc=='i'){ 
                    st.pop();
                    st.push('N');
                }
                else{
                    if(st.size()>=4){
                        char t[4];
                        t[2]=st.top(); st.pop(); 
                        t[1]=st.top(); st.pop(); 
                        t[0]=st.top(); st.pop(); 
                        t[3]='\0';
                        if(strcmp("N+N",t)==0 || strcmp("N*N",t)==0 || strcmp("(N)",t)==0)
                            st.push('N');
                        else{
                            printf("RE\n");
                            return;
                        }
                    }
                    else{
                        printf("RE\n");
                        return;
                    }
                }
                i--;
                printf("R\n");
            }
        }
        else{
            printf("E\n");
            return;
        }
    }
}

int main(int argc,char* argv[]){
    int len = 0;
    char c;
    FILE* in;
    char* filename = argv[1];
    in = fopen(filename,"r");
    while((c=fgetc(in))!=EOF){
        if(c!='\r' && c!='\n') line[len++] = c;
    }
    line+='#'; 
    analyse();
    fclose(in);
    return 0;
}
