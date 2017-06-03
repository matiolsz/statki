#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "computer.h"

using namespace std;

int main(int argc, char **argv)
{
    Board *player = new Board;
    Board *enemy = new Board;
    Computer *pc = new Computer;
    stworz_kompa(pc);
    int x,y;
    bool czydalej;

    if(argc == 2)
    {
        if(stworz_uzytkownikow(argv[1],player,enemy)==false)
        {
            cerr<<"blad wczytywania"<<endl;
            return 1;
        }
    } else {
        cout << "nie podano pliku konfiguracyjnego." << endl;
        return 1;
    }



    while(1)
    {
        system("cls");

        cout<<"PLANSZA WROGA: "<<endl;
        wydrukujkomp(enemy);

        cout<<endl;

        cout<<"PLANSZA GRACZA: "<<endl;
        wydrukuj(player);
        cout<<endl;
        do
        {
            czydalej=true;
            string p;
            cout<<"podaj wsp x i y lub dowolny znak, aby przejsc do zapisu"<<endl;
            cin>>x>>y;

            if(cin.fail())
            {
                czydalej=false;
                cin.clear();
                cin.sync();
                cout<<"czy chcesz zapisac gre?(t/n)"<<endl;
                cin>>p;
                if(p=="t")
                {
                    zapisdopliku("statki3.txt",player,enemy);
                    cout<<"czy chcesz wyjsc z gry?(t/n)"<<endl;
                    cin>>p;
                    if(p=="t"){
                        return 0;
                    }
                }
                cin.clear();
                cin.sync();
            }

            if(x>=player->szerokosc||y>=player->wysokosc){
                cout << "takiego pola nie ma na planszy" << endl;
                czydalej = false;
            }
        }
        while(czydalej!=true);

        if(strzal(enemy,x,y)==true)
        {
            if (enemy->pozostalepola==0)
            {
                break;
            }
        }
        strzalkompa(player,pc);
        if(player->pozostalepola==0)
        {
            break;
        }

    }

    return 0;
}
