#include <iostream>
#include <cmath>
int main(){
    const double PI=4*atan(1);
   // std::cout<<PI;
    double a, b, c;
    std::cout<<"Unesite tri broja: "; 
    std::cin>>a>>b>>c;
    if(a>0 && b>0 && c>0 && a+b>c && a+c>b && c+b>a){
        double povrsina, obim, alfa, beta, gama, s, min;
        s=(a+b+c)/2;
        povrsina= std::sqrt(s*(s-a)*(s-b)*(s-c));
        obim= a+b+c;
        alfa=acos((pow(c, 2)+ pow(b,2) - pow(a,2))/(2*b*c));
        beta=acos((pow(a, 2)+ pow(c,2) - pow(b,2))/(2*a*c));
        gama=acos((pow(b, 2)+ pow(a,2) - pow(c,2))/(2*b*a));
        min=alfa;
        if(beta<min)
            min=beta;
        if(gama<min)
            min=gama;
        min=min* 180./PI;
        double minute, sekunde;
        minute=(min-floor(min) )* 60;//* 60;
        sekunde=(minute-floor(minute)) * 60;
        std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<obim<<"."<<std::endl<<"Njegova povrsina iznosi "<<povrsina<<"."<<std::endl<<"Njegov najmanji ugao ima "<<floor(min)<< " stepeni, "<<floor(minute)<<" minuta i "<< floor(sekunde)<<" sekundi.";                              
    }
    else std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!";
    return 0;
}