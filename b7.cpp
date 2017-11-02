/* The grammar on which recursive descent parser is impelemented

E->E+T|T
T->T*F|F
F->(E)|id

First to eliminate left recursion

E->TE'
E'->+TE'|epsilon
T->FT'
T'->*FT'|epsilon
F->(E) | id

*/

#include<iostream>
#include<string.h>
#include<ctype.h>

using namespace std;

char input[10];
int i,error;
void E();
void T();
void Edash();
void Tdash();
void F();

int main()
{
    i=0;
    error=0;
    cout<<"Enter the arithmatic expression: ";   //eg. a+a*a;
    cin>>input;
    E();
    if(strlen(input)==i &&(error==0))
        cout<<input<<"\tString is Accepted !!!\n";
    else
        cout<<input<<"\tString is not Accepted !!!!\n";    
    return 0;
}

void E()
{
    T();
    Edash();
}


void Edash()
{
    if(input[i]=='+')
    {
        i++;
        T();
        Edash();
    }

}

void T()
{
    F();
    Tdash();
}


void Tdash()
{
    if(input[i]=='*')
    {
        i++;
        F();
        Tdash();
    }

}

void F()
{
    if(isalnum(input[i]))i++;
    else if(input[i]=='(')
    {
        i++;
        E();
        if(input[i]==')')
        i++;
        else
            error=1;
    }
    else
        error=1;
}

