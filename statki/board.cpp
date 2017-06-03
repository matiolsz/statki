#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "board.h"

int losowaliczba(int limit)
{
    int x= rand()%(limit);
    return x;
}

pozycjastatku losowapozycja()
{
    int x=rand()%2;
    if(x==1)
    {
        return POZIOMY;
    }
    return PIONOWY;

}

bool strzal(Board *user, int x, int y)
{
    if(user->plansza[y][x]==WODA)
    {
        user->plansza[y][x]=PUDLO;
        return false;
    }
    else if(user->plansza[y][x]==STATEK)
    {
        user->plansza[y][x]=TRAFIONY;
        user->pozostalepola--;
        return true;
    }
    else if(user->plansza[y][x]==PUDLO)
    {
        return false;
    }
    else if(user->plansza[y][x]==TRAFIONY)
    {
        return false;
    }
    else return false;

}

void wydrukuj(Board *user)
{
    for(int i =0; i<user->wysokosc; i++)
    {
        for(int j=0; j<user->szerokosc; j++)
        {
            cout<<user->plansza[i][j] << '\t';
        }
        cout<<endl;
    }

}

void wydrukujkomp(Board *user)
{
    for(int i =0; i<user->wysokosc; i++)
    {
        for(int j=0; j<user->szerokosc; j++)
        {
            if(user->plansza[i][j]==STATEK)
            {
                cout<<WODA<<'\t';
            }
            else
                cout<<user->plansza[i][j] << '\t';
        }
        cout<<endl;
    }

}

bool sprawdz(Board *user, int n, int m, int x, pozycjastatku pionczypoz)
{
    if(pionczypoz == PIONOWY)
    {
        if(m+x-1>=user->wysokosc)
        {
            return true;
        }
        for (int i=m-1; i<=m+x; i++)
        {

            if(i < 0 || i >= user->wysokosc)
            {
                continue;
            }
            for(int j=n-1; j<=n+1; j++)
            {
                if(j< 0 || j >= user->szerokosc)
                {
                    continue;
                }
                if(user->plansza[i][j]=='1')
                {
                    return true;
                }
            }
        }
    }
    else
    {
        if(n+x-1>=user->szerokosc)
        {
            return true;
        }
        for(int i=m-1; i<=m+1; i++)
        {
            if(i<0 || i>= user->wysokosc)
            {
                continue;
            }
            for(int j=n-1; j<=n+x; j++)
            {
                if(j<0||j>=user->szerokosc)
                {
                    continue;
                }
                if(user->plansza[i][j] == '1')
                {
                    return true;
                }
            }
        }
    }
    return false;
}


void czyszczenie(Board *user)
{
    for(int i =0; i<user->szerokosc; i++)
    {
        for(int j =0; j<user->wysokosc; j++)
        {
            user->plansza[i][j]='0';
        }
    }
    return ;
}

void wstawstatek(Board *user, int n, int m,int x, pozycjastatku pionczypoz)
{
    if(pionczypoz==POZIOMY)
    {
        for(int i =n; i<=n+x-1; i++)
        {
            user->plansza[m][i]='1';
        }
    }
    else
    {
        for(int i =m; i<=m+x-1; i++)
        {
            user->plansza[i][n]='1';
        }
    }

}

bool losowe_statki(Board *user)
{
    string n;
    //int ilosc_rodzajow=user->okrety.size()/2;
    for(int i = 0; i<=user->okrety.size()-2; i+=2)
    {
        for(int j=0; j<user->okrety.at(i+1); j++)
        {

            int proby = 0;
            bool udalosie = false;

            do
            {
                int x=losowaliczba(user->szerokosc);
                int y=losowaliczba(user->wysokosc);
                pozycjastatku z=losowapozycja();

                if (sprawdz(user, x, y, user->okrety.at(i), z) == false)
                {
                    wstawstatek(user, x, y, user->okrety.at(i), z);
                    udalosie = true;
                }
                else
                {
                    proby++;
                    if(proby == 100)
                    {
                        czyszczenie(user);
                        return false;
                    }
                }
            }
            while (udalosie == false);
        }
    }
    return true;
}

bool stworz_uzytkownikow(string nazwa_pliku, Board *player, Board *komp)
{
    string tryb;
    ifstream plik(nazwa_pliku.c_str());
    if(!plik.is_open())
    {
        cerr<<"blad otwarcia pliku"<<endl;
        return false;
    }

    plik>>tryb;
    if(tryb=="NEWGAME")
    {
        bool playerstatki=false,enemystatki=false;
        plik>>player->szerokosc;
        plik>>player->wysokosc;
        komp->szerokosc=player->szerokosc;
        komp->wysokosc=player->wysokosc;

        char **x=new char *[player->wysokosc];
        char **y=new char *[komp->wysokosc];

        for(int i=0; i<player->wysokosc; i++)
        {
            x[i]=new char [player->szerokosc];
            y[i]=new char [komp->szerokosc];
        }

        for(int i=0; i<player->wysokosc; i++)
        {
            for(int j=0; j <player->szerokosc; j++)
            {
                x[i][j] = '0';
                y[i][j] = '0';
            }
        }

        player->plansza = x;
        komp->plansza = y;

        int a;
        while(!plik.eof())
        {
            plik>>a;
            player->okrety.push_back(a);
        }

        player->pozostalepola=0;


        for(int i =0; i<player->okrety.size(); i+=2)
        {
            player->pozostalepola+=player->okrety.at(i)*player->okrety.at(i+1);
        }
        cout << "liczba pozostalych pol zajetych przez statki: " << player->pozostalepola<<endl;

        komp->okrety=player->okrety;
        komp->pozostalepola=player->pozostalepola;

        for(int i=0; i<100; i++)
        {

            if (playerstatki==false)
            {
                if(losowe_statki(player)==true)
                {
                    playerstatki=true;
                }
            }
            if (enemystatki==false)
            {
                if(losowe_statki(komp)==true)
                {
                    enemystatki=true;
                }
            }

            if(playerstatki==true && enemystatki==true)
            {
                break;
            }
        }

    }
    else if(tryb=="SAVEDGAME")
    {
        cout << "test wczytywania";
        player->pozostalepola=0;
        komp->pozostalepola=0;
        plik>>player->szerokosc;
        plik>>player->wysokosc;
        komp->wysokosc=player->wysokosc;
        komp->szerokosc=player->szerokosc;

        cout << "wymiary " << player->szerokosc << " x " << player->wysokosc << endl;

        char **x=new char *[player->wysokosc];
        char **y=new char *[komp->wysokosc];

        for(int i=0; i<player->wysokosc; i++)
        {
            x[i]=new char [player->szerokosc];
            y[i]=new char [komp->szerokosc];
        }
        for(int i=0; i<player->wysokosc; i++)
        {
            for(int j =0; j<player->szerokosc; j++)
            {
                plik>>x[i][j];
                if(x[i][j]==STATEK)
                {
                    player->pozostalepola++;
                }
            }
        }
        for(int i=0; i<komp->wysokosc; i++)
        {
            for(int j =0; j<komp->szerokosc; j++)
            {
                plik>>y[i][j];
                if(y[i][j]==STATEK)
                {
                    komp->pozostalepola++;
                }
            }
        }

        player->plansza = x;
        komp->plansza = y;

    }
    return true;
}

void zapisdopliku(string nazwapliku, Board *player, Board *komp )
{
    ofstream plik(nazwapliku.c_str());
    if(!plik.is_open())
    {
        cerr<<"blad otwarcia pliku"<<endl;
        return ;
    }
    plik<<"SAVEDGAME"<<endl;
    plik<<player->szerokosc<<" "<<player->wysokosc<<endl;
    for(int i=0; i<player->wysokosc; i++)
    {
        for(int j =0; j<player->szerokosc; j++)
        {
            plik<<player->plansza[i][j]<<" ";

        }
        plik<<endl;
    }

    for(int i=0; i<komp->wysokosc; i++)
    {
        for(int j =0; j<komp->szerokosc; j++)
        {
            plik<<komp->plansza[i][j]<<" ";

        }
        plik<<endl;
    }


}
