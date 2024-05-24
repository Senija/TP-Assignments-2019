//cirkulatorna, Zadatak 8
#include <iostream>
#include <deque>

typedef std::deque<std::deque<char>> MatricaDek;
bool JeLiPravilna(MatricaDek mat){
    for(int i=0; i<mat.size()-1; i++){
        if(mat[i].size() != mat[i+1].size()) return false;
    }
    return true;
}

bool DaLiJeCirkulantna(MatricaDek mat){
    
   if(!JeLiPravilna(mat)) return false;
    for(int i=0; i != mat.size()-1; i++){
        for(int j=0; j != mat.size()-1; j++){
            if(mat[i][j] != mat[i+1][j+1] || mat[i][0] != mat[i+1][mat.size()-1]) return false;
        }
    }
    return true;
}
int main ()
{
    MatricaDek mat(4, std::deque<char>(4));
    mat = {{1,2,3,4},{4,1,2,3},{3,4,1,2},{2,3,4,1}};
    std::cout<<DaLiJeCirkulantna(mat);
	return 0;
}