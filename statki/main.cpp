#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "board.h"
#include "computer.h"

using namespace std;

int main()
{
    Board *player = new Board;
    Board *enemy = new Board;
    Computer *pc = new Computer;
    stworz_kompa(pc);
    int x,y;
    bool czydalej;

    string nazwapliku;

    int aktualnaopcja = 0; //0 - wczytaj 1 - wyjscie
    bool out = false;
    int znak = 0;

    while(out == false)
    {

        system("cls");
        cout << "NACISNIJ STRZALKE W PRAWO, ABY WYBRAC" << endl;

        for(int i = 0; i <= 2; i++)
        {
            if(i == aktualnaopcja)
            {
                cout << "#";
            }
            cout <<"\t";

            switch(i)
            {
            case 0:
                cout << "WCZYTAJ PLIK" << endl;
                break;
            case 1:
                cout << "WYJSCIE Z PROGRAMU" << endl;
            }
        }

        znak = getch();

        switch((znak = getch()))
        {
        case 72://up
            if(aktualnaopcja > 0)
            {
                aktualnaopcja--;
            }
            break;
        case 80://down
            if(aktualnaopcja < 1)
            {
                aktualnaopcja++;
            }
            break;
        case 77:
            out = true;
            break;
        }

        cin.clear();
        cin.sync();

    }

    if(aktualnaopcja == 1)
    {
        return 0;
    }
    system("cls");
    cin >> nazwapliku;

    if(stworz_uzytkownikow(nazwapliku,player,enemy)==false)
    {
        cerr<<"blad wczytywania"<<endl;
        return 1;
    }


    system("cls");



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
                    if(p=="t")
                    {
                        return 0;
                    }
                }
                cin.clear();
                cin.sync();
            }

            if(x>=player->szerokosc||y>=player->wysokosc)
            {
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
