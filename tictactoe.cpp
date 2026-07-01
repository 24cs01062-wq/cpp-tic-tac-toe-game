//
//  main.cpp
//  tictactoegame
//
//  Created by Raam Sundaran on 28/01/26.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
using namespace std;

 
void printboard(vector<vector<char> >& V){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(V[i][j]=='X')
                cout<<RED<<BOLD<<"X"<<RESET;
            else if(V[i][j]=='O')
                cout<<BLUE<<BOLD<<"O"<<RESET;
            else
                cout<<" ";

            if(j<2) cout<<" | ";
        }
        cout<<"\n";
        if(i<2) cout<<YELLOW<<"--|---|--"<<RESET<<"\n";
    }
}

void inputboard(vector<vector<char> >&V,char s,int row,int col){
    if(row>=V.size()||col>=V[0].size()||row<0||col<0){
        cout<<"Enter Valid Index";
        return;
    }
    if(V[row][col]!=' '){
        cout<<"already filled!!!!";
        return;
    }
    V[row][col]=s;
    printboard(V);
}

int winner(vector<vector<char> >&V){
    for(int i=0;i<3;i++){
        if(V[i][0]==V[i][1] && V[i][1]==V[i][2] && V[i][0]!=' '){
            cout<<"Winner is "<<V[i][0]<<"\n";
            return 1;
        }
        if(V[0][i]==V[1][i] && V[1][i]==V[2][i] && V[0][i]!=' '){
            cout<<"Winner is "<<V[0][i]<<"\n";
            return 1;
        }
    }
    if(V[0][0]==V[1][1] && V[1][1]==V[2][2] && V[0][0]!=' '){
        cout<<"Winner is "<<V[0][0]<<"\n";
        return 1;
    }
    if(V[0][2]==V[1][1] && V[1][1]==V[2][0] && V[0][2]!=' '){
        cout<<"Winner is "<<V[0][2]<<"\n";
        return 1;
    }
    return -1;
}

bool emptyvoid(vector<vector<char> >&V){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(V[i][j]==' ') return false;
    return true;
}

int evaluate(vector<vector<char> >& V){
    for(int i=0;i<3;i++){
        if(V[i][0]==V[i][1] && V[i][1]==V[i][2]){
            if(V[i][0]=='O') return 10;
            if(V[i][0]=='X') return -10;
        }
        if(V[0][i]==V[1][i] && V[1][i]==V[2][i]){
            if(V[0][i]=='O') return 10;
            if(V[0][i]=='X') return -10;
        }
    }
    if(V[0][0]==V[1][1] && V[1][1]==V[2][2]){
        if(V[0][0]=='O') return 10;
        if(V[0][0]=='X') return -10;
    }
    if(V[0][2]==V[1][1] && V[1][1]==V[2][0]){
        if(V[0][2]=='O') return 10;
        if(V[0][2]=='X') return -10;
    }
    return 0;
}

int minimax(vector<vector<char> >& V, bool isMax){
    int score = evaluate(V);
    if(score==10 || score==-10) return score;
    if(emptyvoid(V)) return 0;

    if(isMax){
        int best=-1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(V[i][j]==' '){
                    V[i][j]='O';
                    best=max(best,minimax(V,false));
                    V[i][j]=' ';
                }
            }
        }
        return best;
    } else {
        int best=1000;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(V[i][j]==' '){
                    V[i][j]='X';
                    best=min(best,minimax(V,true));
                    V[i][j]=' ';
                }
            }
        }
        return best;
    }
}

pair<int,int> bestMove(vector<vector<char> >& V){
    int bestVal=-1000;
    pair<int,int> move = make_pair(-1, -1);

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(V[i][j]==' '){
                V[i][j]='O';
                int val=minimax(V,false);
                V[i][j]=' ';
                if(val>bestVal){
                    bestVal=val;
                    move=make_pair(i, j);
                }
            }
        }
    }
    return move;
}

int main(){
    cout<<"******TIC TAC TOE GAME******\n";
    cout<<"1. Human vs Human\n";
    cout<<"2. Human vs Computer\n";
    cout<<"Choose mode: ";

    int mode;
    cin>>mode;

    vector<vector<char> >V(3,vector<char>(3,' '));
    printboard(V);

    while(true){
        char s='X';
        char g='O';

        while(true){
            int row,col;
            cin>>row>>col;
            if(row<0||col<0||row>2||col>2) continue;
            if(V[row][col]==' '){
                inputboard(V,s,row,col);
                break;
            }
        }

        if(winner(V)==1) break;
        if(emptyvoid(V)){
            cout<<"Match tied";
            break;
        }

        if(mode==1){
            while(true){
                int row,col;
                cin>>row>>col;
                if(row<0||col<0||row>2||col>2){
                    cout<<"enter valid index\n";
                    continue;
                }
                if(V[row][col]==' '){
                    inputboard(V,g,row,col);
                    break;
                }
                else{
                    cout<<"already filled\n";
                    continue;
                }
            }
        } 
        else {
            pair<int,int> ai=bestMove(V);
            inputboard(V,'O',ai.first,ai.second);
        }

        if(winner(V)==1) break;
        if(emptyvoid(V)){
            cout<<"Match tied";
            break;
        }
    }
    return 0;
}
