#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

// Losowanie ile pieniedzy ma sie na starcie
float hajs(){
    char ile_dala_zona;
    cout<<"\nJaki jest twoj budzet\n1. Niski (200-1000zl)\n2. Sredni (1000-5000zl)\n3. Wysoki (5000-25000zl): ";
    ile_dala_zona = getchar();
    switch(ile_dala_zona)
    {
        case '1': return (rand()%800+200); break;
        case '2': return (rand()%4000+1000); break;
        case '3': return (rand()%20000+5000); break;
        default : cout<<"\n\nWybrano zla opcje.\n\n\n";return 0.0; break;
    }
}
// Wybor jaka stawiasz stawke, testowy comment
float postaw(float kasa,float stawka=0){
    cout << "\nTwoj budzet wynosi: " << kasa;
    while (stawka>kasa || stawka<=0){
        getchar();
        cout << "\n\nWprowadz stawke: ";
        cin >> stawka;
        getchar();
        if (stawka>kasa) cout<<"\nNie masz tyle pieniedzy. Twoj budzet to "<<kasa;
        if (stawka<=0) cout<<"\nWprowadz liczbe wieksza od 0";
    }
    return stawka;
}

// Funkcje do blackjacka
// Losowy wybor kart w ułożonej talii
void losowanie(string reka[10], int * w_reka, int talia[4][13],int licznik)
{
    int los1, los2;
    do{
    los1 = rand()%4;
    los2 = rand()%13;
    }while (talia[los1][los2]==0);

    switch(los1){
    case 0:{reka[licznik] = ("trefl");
    w_reka[licznik] = los2+1;
    }break;
    case 1:{reka[licznik] = ("karo");
    w_reka[licznik] = los2+1;
    }break;
    case 2:{reka[licznik] = ("kier");
    w_reka[licznik] = los2+1;
    }break;
    case 3:{reka[licznik] = ("pik");
    w_reka[licznik] = los2+1;
    }break;
    }
    talia[los1][los2] = 0;
}

// Niby tasowanie talii
void tasowanie(int talia[4][13]){
    for (int i =0; i<4;i++)
    {
        for (int c = 0; c<13; c++)
        {talia[i][c] = c+1;}
    }
}

// Nic dodac nic ujac
int punktacja(string reka[10], int * w_reka, int licznik)
{
    if (w_reka[licznik]>1 && w_reka[licznik]<11){
        cout << w_reka[licznik] << " " << reka[licznik] << " | ";
        return w_reka[licznik];}
    else if (w_reka[licznik]==1){
        cout << "As " << reka[licznik] << " | ";
        return 1;}
    else if (w_reka[licznik]==11){
        cout << "Walet " << reka[licznik] << " | ";
        return 10;}
    else if (w_reka[licznik]==12){
        cout << "Dama " << reka[licznik] << " | ";
        return 10;}
    else{
        cout << "Krol " << reka[licznik] << " | ";
        return 10;}
}

// Glowna funkcja blackjacka
float blackjack(float kasa, int talia[4][13], float stawka = 0, int split2=0,
    int wartosc = 0, int wartosc_k = 0, string kolor = "", string kolor_k = "")
{
    char decyzja;
    int w_reka_g[10], w_reka_k[10];
    string reka_g[10], reka_k[10];
    int licznik=-1, licznik_k=0, insurence=0, licznik2, licznik_g=0, split=0;
    int punkty_g, punkty_k, a, punkty_g_as = 0, punkty_k_as = 0, kontrola;




    if (split2 == 1){
        w_reka_g[0]=wartosc; w_reka_k[0]=wartosc_k;
        reka_g[0] = kolor; reka_k[0] = kolor_k; licznik = 1; licznik_g = 1; licznik_k = 1;
    }
    else {stawka = postaw(kasa); tasowanie(talia);}
    kasa -= stawka;
    do
    {
        if (licznik==-1 || licznik > 100)
        {
            losowanie(reka_k, w_reka_k, talia, licznik_k);
            licznik_k ++;
        }
        else
        {
            losowanie(reka_g, w_reka_g, talia, licznik_g);
            licznik_g++;
        }
        licznik ++;

        licznik2 = 0; punkty_g = 0; punkty_k = 0;

        if(licznik>1)
            {
            cout << "\n\nTwoje karty:\n";
            do
            {
                a = punktacja(reka_g, w_reka_g, licznik2);
                if (punkty_g_as>0)
                punkty_g_as += a;
                if (a == 1)
                {punkty_g_as = punkty_g+11;
                }
                punkty_g += a;
                licznik2 ++;
            }while(licznik2<licznik_g);
            if (punkty_g_as == 21 || punkty_g == 21)
            {licznik +=100;}
            licznik2 = 0;
            cout << "\nTwoja ilosc punktow: "<<punkty_g;
            if (punkty_g_as>0 && punkty_g_as<22)
            cout << " lub "<<punkty_g_as;
            cout << "\n\nKarty krupiera:\n";
            do{
                a = punktacja(reka_k, w_reka_k, licznik2);
                if (punkty_k_as>0)
                punkty_k_as += a;
                if (a == 1)
                {punkty_k_as = punkty_k+11;
                }
                punkty_k += a;
                licznik2 ++;
            }while(licznik2<licznik_k);
            cout << "\nIlosc punktow krupiera: "<<punkty_k;
            if (punkty_k_as>0 && punkty_k_as<22)
            cout << " lub "<<punkty_k_as;
            cout << "\n";
        }
        if (licznik>1 && licznik <100 && punkty_g<21 && punkty_g_as!=21)
        {
        do{
            kontrola = 1;
            cout << "\nCo chcesz zrobic (wybierz wpisujac numer z klawiatury)\n";
            cout << "1.STAND       :\n2.HIT         :\n3.DOUBLE DOWN :\n4.SPLIT       :\n5.INSURENCE   : ";
            decyzja = getchar();
            getchar();
            switch(decyzja){
                case '1': { licznik+=100;
                    break;
                }
                case '2': break;
                case '3': {
                    if (licznik_g ==2 && split == 0 && split2 == 0 && stawka<=kasa){
                    licznik = 100; kasa -= stawka; stawka += stawka;
                }
                    else{cout<<"\nMozna doublowac tylko majac 2 karty";kontrola=0;}
                    break;
                }
                case '4': {if (licznik_g==2&&split==0&&split2==0&&(w_reka_g[0]==w_reka_g[1]
                ||(w_reka_g[0]>10 && w_reka_g[1]>10))&&stawka<=kasa){
                wartosc=w_reka_g[0];kolor=reka_g[0];kolor_k=reka_k[0];
                split = 1; wartosc_k = w_reka_k[0];
                w_reka_g[1]=0; reka_g[1]=""; licznik_g-=1;
                blackjack(kasa, talia, stawka, split, wartosc, wartosc_k, kolor, kolor_k);}
                else{cout<<"\nSplitowac mozna  gdy pierwsze 2 karty maja ta sama wartosc";
                kontrola = 0;}    break;}

                case '5': {if(licznik_g==2&&licznik_k==1&&w_reka_k[0]==1&&split==0&&split2==0&&stawka<=kasa*0.5){
                    licznik += 100; insurence = 1; kasa -= stawka*0.5;}
                    else{cout<<"\nMozna grac insurence wylacznie, gdy masz 2 karty";
                    cout <<" a karta kuriera to As"; kontrola = 0;}
                    break;
                }
                default:{ cout << "\nWybrano zla opcje."; kontrola = 0;
                    break;
                }
            }
        }while(kontrola==0);
        }
    }while (punkty_g<22 && punkty_k <17 && (punkty_k_as<17 ||
    punkty_k_as>21) && (insurence==0 || licznik_k!=2));

    if (insurence == 1){
        if (punkty_k_as == 21){
            cout << "\nMiales farta"; kasa += stawka*1.5;}
        else{
            cout << "\nNie graj tego nigdy bo masz tylko 33% szans na wygranie.";}
    }
    else if ((punkty_g==21 || punkty_g_as==21) && licznik_g ==2){
        if ((punkty_k_as == 21 || punkty_k == 21) & licznik_k == 2){
            cout << "\nFajnie, ze masz BlackJacka, niestety kurier tez - remis";
            kasa += stawka;}
        else{
            cout << "\nGratulujemy Blackjacka, wygrywasz: "<<stawka*2.5;
            kasa += stawka*2.5;
        }
    }
    else if (punkty_g<22 && punkty_k>21){
        cout << "\nGratulujemy wygranej wynoszacej: "<<stawka*2;
        kasa += stawka*2;
    }
    else if (punkty_g<22 && punkty_k<22){
        if (0<punkty_g_as && punkty_g_as<22){
            punkty_g = punkty_g_as;}
        if (0<punkty_k_as && punkty_k_as<22){
            punkty_k = punkty_k_as;}
        if (punkty_g > punkty_k){
            cout << "\nGratulujemy wygranej wynoszacej: "<<stawka*2;
            kasa += stawka*2;}
        else if (punkty_g == punkty_k)
        {cout << "\nRemis"; kasa += stawka;}
        else{cout << "\nNiestety przegrales :(";}}
    else
    {cout << "\nOsiagnieto ponad 21 pkt - niestety przegrales :(";}
    if (split2 == 1){
        cout << "\nWcisniej ENTER, aby przejsc do drugiej reki";
        getchar();}
    else{
        cout<< "\nJezeli chcesz zagrac ponownie wcisnij klawisz inny niz 1: ";
        char ponownie;
        ponownie = getchar();
        getchar();
        cout << "_________________________________\n";
        if (ponownie != '1' && kasa>0)
        {kasa = blackjack(kasa, talia);}
    }return kasa;
}

// Funkcje do ruletki
// Zapis liczb lub kombinacji w ktorych pojedyncza liczba to zaklad
// Brak zabezpieczenia przed wprowadzeniem niepoprawnych liczb - Zasada: Twoj blad, Twoja strata.
// A tak serio to juz mi sie nie chcialo, duzo nauki do sesji zostalo :(
void obstawianie(string liczby[10][500], int opcja){
    string podane_liczby;
    int i = 0, index = 0;
    getline(cin, podane_liczby);

    while (i < podane_liczby.size()){
        if (podane_liczby[i]!= ' ')
            liczby[opcja][index]+=podane_liczby[i];
        else{
            index++;}
        i++;}
}

// Kontrolowanie zakladow w ktorych kilka liczb to 1 zaklad
// Niepoprawna il. liczb do zakladu = caly zaklad kasowany
// No i sprawdza czy nie za duza, za mala i czy okej kombinacja
void sprawdzanie(string liczby[11][500], int tab[500], int kontrola, int numer){
    int ilosc = 0;
    for (int i = 0; i<numer; i+=kontrola){
        sort(tab+i, tab + i + kontrola);
        if (tab[i] < 0 || tab[i+kontrola-1]>36)
           ;
        if (kontrola == 2){
            if ((tab[i+1] - tab[i] == 1 && tab[i]%3 != 0)|| tab[i+1] - tab[i] == 3)
                {liczby[kontrola-1][ilosc] = to_string(tab[i]);
                liczby[kontrola-1][ilosc+1] = to_string(tab[i+1]); ilosc += 2;}
        }
        else if (kontrola == 3){
            if (tab[i+2]%3==0 && tab[i+2]-tab[i+1]==1 && tab[i+1]-tab[i]==1)
                {liczby[kontrola-1][ilosc] = to_string(tab[i]); liczby[kontrola-1][ilosc+1] = to_string(tab[i+1]);
                liczby[kontrola-1][ilosc+2] = to_string(tab[i+2]); ilosc+=3;}}
        else{
            if ((tab[i]>0 && tab[i+3]-tab[i+2]==1 && tab[i+2]-tab[i+1]==2 && tab[i+1]-tab[i]==1 && tab[i]%3!=0)||
                (tab[i]==0&&tab[i+1]==1&&tab[i+2]==2&&tab[i+3]==3)){
                liczby[kontrola-1][ilosc] = to_string(tab[i]); liczby[kontrola-1][ilosc+1] = to_string(tab[i+1]);
                liczby[kontrola-1][ilosc+2] = to_string(tab[i+2]); liczby[kontrola-1][ilosc+3] = to_string(tab[i+3]);
                ilosc+=4;}}
}}

// Obstawianie kombinacji liczb, odsylka do funkcji powyzej (kontroli)
void obstawianie2(string liczby[11][500], int kontrola){
    string podane_liczby, tab[500];
    int i = 0, index = 0, tab2[500];
    getline(cin, podane_liczby);
    while (i < podane_liczby.size()){
        if (podane_liczby[i]!= ' ')
            tab[index]+=podane_liczby[i];
        else{
            tab2[index] = stoi(tab[index]);
            index++;}
        i++;
    }
    if (podane_liczby.size()>0) tab2[index] = stoi(tab[index]);
    if ((index+1)%kontrola!=0)
        cout << "\nWprowadzono nieprawidlowa ilosc liczb dla tego zakladu!\n";
    else{
        sprawdzanie(liczby, tab2, kontrola, index);
    }
}

//Glowna funkcja ruletki
float ruletka(float kasa)
{
    float stawka;
    int wygrana, wylosowana, ile_stawek = 0, czerwone[18], czarne[18];
    int index = 0, i = 0, kontrola = 0, lacznie_stawek, czerwony = 0, czarny = 0;
    string liczby[10][500], opcje[10], podane_opcje, wylosowana2;

    stawka = postaw(kasa);
    cout << "\n!Jezeli chcesz zwiekszyc stawke na jakis zaklad po prostu wpisz go x razy!\n";
    cout << "\nProsze zerknij sobie na ruletke\n\n |";
    for (int i = 3; i < 37; i+=3){
        cout << i << "|";
        if (i == 36){
            cout << endl; i = -3;}
        else if (i == 0)
            i--;
        else if (i == 35)
            {cout << "\n |"; i = -2;}
    }
    cout << "\n______________________________________\n";
    i = 0;
    cout << "Split bety - 2 liczby musza sie ze soba stykac, Street bety - 3 liczby w tej samej kolumnie, ";
    cout << "\nCorner bety - 4 liczby stykajace sie rogami\n\n";
    cout << "Co chcesz obstawic (wybierz opcje oddzielajac je spacja):\n";
    cout << "0. Pojedyncze liczby | 1. Split Bet | 2. Street Bet | 3. Corner Bet | 4. Six Line Bet\n";
    cout << "5. Column Bet | 6. Dozen Bet | 7. Parzyste/Nieparzyste | 8. 1-18 / 19-36 | 9. Kolor:\n";
    getline(cin, podane_opcje);
    while (i < podane_opcje.size()){
        if (podane_opcje[i]!= ' '){
            opcje[index]+=podane_opcje[i];}
        else index++;
        i++;}
    for (i=0; i<=index; i++){
        switch(stoi(opcje[i])){
            case 0: cout << "\nNa ktore pojedyncze liczby chcesz postawic (wpisz liczby oddzielajac je spacja):\n";
                obstawianie(liczby, 0);
            break;
            case 1: cout << "\nJakie Split Bety chcesz obstawic (wpisz 2 liczby oddzielone spacja), ";
            cout << "nastepnie spacje zeby podac kolejne 2):\n";
                obstawianie2(liczby, 2);
            break;
            case 2: cout << "\nJakie Street Bety chcesz obstawic (wpisz 3 liczby oddzielone spacja), ";
            cout << "nastepnie spacje zeby podac kolejne 3):\n";
                obstawianie2(liczby, 3);
            break;
            case 3: cout << "\nJakie Corner Bety chcesz obstawic (wpisz 4 liczby oddzielone spacja), ";
            cout << "nastepnie spacje zeby podac kolejne 4):\n";
                obstawianie2(liczby, 4);
            break;
            case 4: cout << "\nJakie Six Line Bety chcesz obstawic (podaj numer kombinacji), nastepnie spacje i kolejny numer\n ";
            cout << "Możliwosci: | 1. 1-6 | 2. 4-9 | 3. 7-12 |  4. 10-15 | 5. 13-18 | 6. 16-21 | 7. 19-24 | 8. 22-27 | 9. 25-30 | 10. 28-33 | 11. 31- 36 |\n";
                obstawianie(liczby, 4);
            break;
            case 5: cout << "\nJakie Column Bety chcesz obstawic (podaj numer kombinacji), nastepnie spacje i kolejny numer\n ";
            cout << "Możliwosci: | 1. Górna kolumna | 2. Dolna kolumna | 3. Srodkowa kolumna |\n";
                obstawianie(liczby, 5);
            break;
            case 6: cout << "\nJakie Dozen Bety chcesz obstawic (podaj numer kombinacji), nastepnie spacje i kolejny numer\n ";
            cout << "Możliwosci: | 1. 1-12 | 2. 13-24 | 3. 25-36\n";
                obstawianie(liczby, 6);
            break;
            case 7: cout << "\nWpisz numer: | 1. Parzyste | 2. Nieparzyste\n";
                obstawianie(liczby, 7);
            break;
            case 8: cout << "\nWpisz numer: | 1. 1-18 | 2. 19-36\n";
                obstawianie(liczby, 8);
            break;
            case 9: cout << "\nWpisz numer: 1. czerwone (";
            for (i = 1; i < 37; i+=2){
                czerwone[czerwony] = i;
                czerwony ++;
                cout << i << ", ";
                if (i == 9 || i == 27)
                    i ++;
                else if (i == 18)
                    i --;}
            cout << ")\n2. czarne (";
            for (i = 2; i < 36; i+=2){
                czarne[czarny] = i;
                czarny++;
                cout << i << ", ";
                if (i == 10 || i == 28)
                    i --;
                else if (i == 17)
                    i ++;}
            cout <<")\n";
                obstawianie(liczby, 9);
            break;
            default: cout << "\nNieprawidlowa opcja"; break;
        }
    }
    wylosowana = rand()%37;
    wylosowana2 = to_string(wylosowana);

    int x;
    for (int i = 0; i<10; i++){
        x = 0;
        while (liczby[i][x]!=""){
        switch(i){
        case 0:
            ile_stawek ++;
            if (stoi(liczby[i][x]) == wylosowana)
                wygrana += 36*stawka;
        break;
        case 1:
            if (x%2==1)
                ile_stawek ++;
            if (liczby[i][x] == wylosowana2)
                wygrana += 18*stawka;
        break;
        case 2:
            if (x%3==2)
                ile_stawek ++;
            if (liczby[i][x] == wylosowana2)
                wygrana += 12*stawka;
        break;
        case 3:
            if (x%4==3)
                ile_stawek ++;
            if (liczby[i][x] == wylosowana2)
                wygrana += 9*stawka;
        break;
        case 4:
            ile_stawek++;
            if ((wylosowana-1)/3 == stoi(liczby[i][x]) || (wylosowana-1)/3 == stoi(liczby[i][x])-1)
                wygrana += 6*stawka;
        break;
        case 5:
            ile_stawek++;
            if (wylosowana%3 == stoi(liczby[i][x])-1)
            wygrana += 3*stawka;
        break;
        case 6:
            ile_stawek++;
            if ((wylosowana-1)/12 == stoi(liczby[i][x])-1)
            wygrana += 3*stawka;
        break;
        case 7:
            ile_stawek ++;
            if (wylosowana%2 == stoi(liczby[i][x])-1 && stoi(liczby[i][x]) > 0)
            wygrana += 2*stawka;
        break;
        case 8:
            ile_stawek++;
            if ((wylosowana-1)/18 == stoi(liczby[i][x])-1)
            wygrana += 2*stawka;
        break;
        case 9:
            ile_stawek++;
            for (int b = 0; b<18; b++){
                if (stoi(liczby[i][x]) == 1){
                    if (wylosowana == czerwone[b])
                    {
                        wygrana += 2*stawka;
                        break;
                    }
                }
                else if (stoi(liczby[i][x]) == 2){
                    if (wylosowana == czarne[b])
                    {
                        wygrana += 2*stawka;
                        break;
                    }
                }
            }cout << endl;
        break;
    }
        x++;

        if (ile_stawek*stawka>kasa-stawka){
        break;}
    }
    if (ile_stawek*stawka>kasa-stawka){
        cout << "\nZabraklo Ci pieniedzy na zaklady, ale postawilismy odpowiednia ilosc pierwszych zakladow";
        break;}
    }
    cout <<"\nLacznie " << ile_stawek << " poprawnych zakladow, pobrano " << stawka*ile_stawek << "zl.";
    cout << "\nWylosowano liczbe " << wylosowana <<".";
    if (wygrana>0)
        cout << "\nWygrales " << wygrana << "zl.";
    else if (ile_stawek>0) cout << "\nNiestety przegrales.";
    kasa -= ile_stawek*stawka;
    kasa += wygrana;
    cout<< "\n\nJezeli chcesz zagrac ponownie wcisnij klawisz inny niz 1: ";
        char ponownie;
        ponownie = getchar();
        getchar();
        cout << "_________________________________\n";
        if (ponownie != '1' && kasa>0)
        {kasa = ruletka(kasa);}
        return kasa;
}

// Jednoreki bandyta, na 10mln testow zwracalnosc 98,775%
float owocki(float kasa) {
    string owocki[2000], maszyna[9], wygrane[5];
    int ile_wygranych, i;
    float stawka, wygrana ;
    char ponownie;

    for (i = 0; i <= 800; ++i)   { owocki[i] = "J"; }
    for (i = 801; i <= 1250; ++i) { owocki[i] = "C"; }
    for (i = 1251; i <= 1570; ++i) { owocki[i] = "W"; }
    for (i = 1571; i <= 1840; ++i) { owocki[i] = "S"; }
    for (i = 1841; i <= 1999; ++i){ owocki[i] = "7"; }
    while(ponownie!='1' && kasa>0){
    stawka = postaw(kasa);
    kasa -= stawka;
    ile_wygranych = 0; wygrana = 0;
    cout << "\n______\n";
    for (i = 0; i < 9; i++) {
        maszyna[i] = owocki[rand()%2000];
        cout << maszyna[i] << "|";
        if( i % 3 == 2) cout << "\n";}

    if (maszyna[0] == maszyna[1] && maszyna[0] == maszyna[2]) {
        wygrane[ile_wygranych] = maszyna[0];
        ile_wygranych++;
    }
    if (maszyna[3] == maszyna[4] && maszyna[3] == maszyna[5]) {
        wygrane[ile_wygranych] = maszyna[3];
        ile_wygranych++;
    }
    if (maszyna[6] == maszyna[7] && maszyna[6] == maszyna[8]) {
        wygrane[ile_wygranych] = maszyna[6];
        ile_wygranych++;
    }
    if (maszyna[0] == maszyna[4] && maszyna[0] == maszyna[8]) {
        wygrane[ile_wygranych] = maszyna[0];
        ile_wygranych++;
    }
    if (maszyna[6] == maszyna[4] && maszyna[6] == maszyna[2]) {
        wygrane[ile_wygranych] = maszyna[6];
        ile_wygranych++;
    }

    for (i = 0; i < ile_wygranych; i++) {
        if (wygrane[i] == "J") {
            wygrana += stawka * 0.7;
        } else if (wygrane[i] == "C") {
            wygrana += stawka * 1.3;}
        else if (wygrane[i] == "W") {
            wygrana += stawka* 3.5;}
        else if (wygrane[i] == "S") {
            wygrana += stawka * 15;}
        else if (wygrane[i] == "7") {
            wygrana +=stawka * 40;}
    }
    if (ile_wygranych>0){
        wygrana+=stawka;
        kasa += wygrana;
        cout << "Gratulujemy wygranej wynoszącej: " << wygrana << endl;
    }
    cout<< "\n\nJezeli chcesz zagrac ponownie wcisnij klawisz inny niz 1";
    ponownie = getchar();
    getchar();
    cout << "\n_________________________________\n";
    }
    return kasa;
}

// Tu mialem dylemat czy wyswietlac tez tych z minusowa wygrana, no ale to by mnie zmusilo do dodatkowej zmiennej typu linia2
// ktora bym sprawdzal i jak > 0 to dopiero printf, no a minusowych zapisuje, bo jak ktos najpierw przegra a potem wygra
// to liczy sume z jego wizyt w kasynie
void ranking(){
    FILE * fp = NULL;
    char linia[60], kontrola[60];
    int licznik = 1;
    float a = 1;
    if( ( fp = fopen( "ranking.txt", "rt" ) ) != NULL ){
        while ( ! feof( fp ) ){
			fgets(linia, 60, fp);
			if( strcmp( kontrola, linia) == 0 ){
                break;
			}

			cout << licznik << " miejsce - ";
            printf(linia);
            fgets(linia, 60, fp);
            strcpy(kontrola, linia);
            cout << "Wygrana: ";
            printf(linia);
            cout << endl;
            licznik ++;
        }
        fclose(fp);
    } else cout << "Ranking jest pusty.";
}

// Osobiscie uwazam to za najtrudniejsza czesc kodu, wiele wyzwan mi ta czesc kodu postawila, no ale wazne, ze dziala
void zapis_do_rankingu(char nick[60], float wygrana){
	strcat(nick, "\n");
    FILE * fp = NULL;
    char linia1[60], linia2[60], gracze[100][60], wygrane[100][20], kontrola[60];
    int licznik = 0, licznik2 = 0, znaleziono = 0, wpisany = 0;
    if( ( fp = fopen( "ranking.txt", "rt" ) ) != NULL ){
        while ( ! feof( fp ) ){
			fgets(linia1, 60, fp);
			if( strcmp( kontrola, linia1 ) == 0 ){
                break;
			}
			strcpy(kontrola, linia1);     // To uratowalo moj kod w momencie zapisu wygranej + \n, ktora dublowala mi ostatniego gracza
            fgets(linia2, 60, fp);
            if( strcmp( nick, linia1 ) == 0 ){
            	wygrana += stoi(linia2);
            	znaleziono = 1;
            }
            else{
                strcpy(gracze[licznik], linia1);
                strcpy(wygrane[licznik], linia2);
                licznik ++;
            }
        }
        fclose(fp);
    } else ;
    if( ( fp = fopen( "ranking.txt", "wt" ) ) != NULL ){
        if (licznik == 0){
            fprintf(fp, "%s", nick);
            fprintf(fp, "%g\n", wygrana);
            cout << "Tylko Ty poki co znajdujesz sie w rankingu\nLaczna wygrana: " << wygrana << "zl.";
        }
        else{
        while ( licznik2 + wpisany < 100 && licznik2 < licznik){
            if (wpisany == 0 && wygrana > stoi(wygrane[licznik2])){
                wpisany = 1;
                fprintf(fp, "%s", nick);
                fprintf(fp, "%g\n", wygrana);
                cout << "Zajmujesz " << licznik2 + 1 << " miejsce w rankingu, laczna wygrana " << wygrana << "zl.";
            }
            else{
                fprintf(fp, "%s", gracze[licznik2]);
                fprintf(fp, "%s", wygrane[licznik2]);
                licznik2 ++;
            }
        }
        if (wpisany == 0 && licznik2 < 100){
            fprintf(fp, "%s", nick);
            fprintf(fp, "%g\n", wygrana);
            cout << "Zajmujesz " << licznik2 + 1 << " miejsce w rankingu, laczna wygrana " << wygrana << "zl.";
        }
        fclose(fp);
    }} else cout << "Ranking jest pusty.";
}
// Pewnie dalo sie latwiej XD

// No i wisienka na torcie, w pelni sprawny program. Jedyne co moglem dodac to kontrole wpisywanych danych
// w stylu try - wyjatek no i zabezpieczenie przed za wysokimi i za niskimi w ruletce.
// Chyba ten program trafi do mojego portfolio.
int main()
{
    float kasa = 0;
    float poczatkowa;
    char nick[60];
    char numer_z_menu, doladowanie;
    int talia[4][13];
    srand(time(NULL));

    cout<<"Witamy w kasynie, zyczymy duzych wygranych."<<endl;
    cout<<"Jak sie nazywasz?: "<<endl;
    cin >> nick;
    getchar();

    do{
        kasa = hajs();
    } while (kasa <= 0.0);

    poczatkowa = kasa;

    while(true){
        if (kasa <= 0){
            cout << "\nSkonczyly Ci sie pieniadze.\nWpisz 1, zeby doladowac stan konta lub inny klawisz, zeby wyjsc z kasyna: ";
            cin >> doladowanie;
            getchar();
            if (doladowanie == '1'){
                do{
                kasa = hajs();
                } while (kasa <= 0.0);
                poczatkowa += kasa;
            } else numer_z_menu = '5';
        }
        if (kasa>0){
        cout <<"\n\nTWOJ BUDZET: " << kasa;
        cout<<"\nWYBIERZ OPCJE Z MENU: ";
        cout<<"\n1.Top 100 graczy    : ";
        cout<<"\n2.BlackJack         : ";
        cout<<"\n3.Ruletka           : ";
        cout<<"\n4.Jednoreki bandyta : ";
        cout<<"\n5.Wyjscie z Kasyna  : ";
        cin >> numer_z_menu;}
        cout << "\n";
        switch(numer_z_menu){
        case '1':{
            ranking();
            break;}
        case '2':{
            kasa = blackjack(kasa, talia);
            break;}
        case '3':{
            kasa = ruletka(kasa);
            break;}
        case '4':{
            kasa = owocki(kasa);
            break;}
        case '5':{
            cout << endl << "Dziekujemy za gre, dzisiaj z kasyna wynosisz " << kasa - poczatkowa  << " zl\n";
            zapis_do_rankingu(nick, kasa - poczatkowa);
            exit(0);
            break;}
        default: {
            cout << "\n\nWybrano zla opcje. \n";
            break;}}
    }
    return 0;
}
