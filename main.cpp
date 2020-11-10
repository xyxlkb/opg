#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;
char ch[6] = {'+', '*', 'i', '(', ')','#'};
char line[1005];
stack<int> s1;
int p[6][6] = {
    {2,1,1,1,2,2},
    {2,2,1,1,2,2},
    {2,2,-1,-1,2,2},
    {1,1,1,1,0,-1},
    {2,2,-1,-1,2,2},
    {1,1,1,1,-1,-1}
};
int def(int c)
{
    if(c=='+') return 0;
    if(c=='*') return 1;
    if(c=='i') return 2;
    if(c=='(') return 3;
    if(c==')') return 4;
    if(c=='#') return 5;
    return 6;
}
char find_lt()
{
    char c,ans;
    c=s1.top();
    if(def(c)<6)
        return c;
    s1.pop();
    ans=s1.top();
    s1.push(c);
    return ans;
}
void analyse()
{
    s1.push('#');
    char rc,lc;
    int a,b,compare;
    for(int i=0;i<strlen(line);i++){
        rc=line[i]; //printf("rc:%c\n",rc);
        if(def(rc)<6){
            lc=find_lt(); //printf("lc:%c\n",lc);
            a=def(lc); //printf("a:%d\n",a);
            b=def(rc); //printf("b:%d\n",b);
            compare=p[a][b];
            if(compare==2){
                printf("E\n");
                return;
            }
            if(compare<=0&&rc!='#'){
                s1.push(rc);
                printf("I%c\n",rc);
            }
            else if(rc=='#'&&lc=='#'){
                return;
            }
            else{
                if(lc=='i'){ // ? lc or s1.top()
                    s1.pop();
                    s1.push('N');
                }
                else{
                    if(s1.size()>=4){
                        char t[4];
                        t[2]=s1.top(); s1.pop(); 
                        t[1]=s1.top(); s1.pop(); 
                        t[0]=s1.top(); s1.pop(); 
                        t[3]='\0';
                        if(strcmp("N+N",t)==0 || strcmp("N*N",t)==0 || strcmp("(N)",t)==0)
                            s1.push('N');
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

int main(int argc,char* argv[])
{
    int len = 0;
    char c;
    char* fname = argv[1];
    FILE* in;
    in = fopen(fname,"r");
    while((c=fgetc(in))!=EOF){
        if(c!='\r' && c!='\n') line[len++] = c;
    }
    line[len++] = '#'; //printf("%s\n",line);
    fclose(in);
    analyse();
 return 0;
}

