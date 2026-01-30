// Öğrenci Kayıt Sistemi.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include<windows.h>
#include <algorithm>
#include <string>
#define max 3
using namespace std;

struct Ogrenci {
    string ad;
    int num;
    double ort;
};
void menu() {
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    cout << "Öğrenci Bul[1]" << endl;
    cout << "Öğrenci Listele[2]" << endl;
    cout << "Öğrenci Ekle[3]" << endl;
    cout << "Çıkış Yap[4]" << endl;
    cout << "------------------" << endl;
}

void ogrencibul(Ogrenci ogr[],int &c) {
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    int no;
    cout << "------------------" << endl;
    cout << "Bulmak istediğin öğrencinin no gir:";
    
    cin >> no;
    for (int i = 0; i < c; i++) {
        if(no==ogr[i].num){
            cout << "ÖĞRENCİ NO:" << ogr[i].num << endl;
            cout << "ÖĞRENCİ ADI:" << ogr[i].ad << endl;
            cout << "ÖĞRENCİ ORT:" << ogr[i].ort << endl;
        }
    }
    

    

}
void ogrencilistele(Ogrenci ogr[],int &c) {
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    
    for (int i = 0; i < c; i++) {
        cout << "------------------" << endl;
        cout << "Öğrenci Adı     :" << ogr[i].ad << endl;
        cout << "Öğrenci No      :" << ogr[i].num << endl;
        cout << "Öğrenci Ort     :" << ogr[i].ort << endl;
        cout << "------------------" << endl;
    }
 }

int ogrenciekle(Ogrenci og[], int &a) {
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    cout << "------------------" << endl;
    cout << "Öğrenci adı gir       :";
    cin.ignore();
    getline(cin, og[a].ad);
    cout << "Öğrenci Numarası      :";
    cin >> og[a].num;
    cout << "Öğrenci ortalaması    :";
    cin >> og[a].ort;
    cout << "------------------" << endl;
    return ++a;


    
}

int main()
{
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    cout << "------------------" << endl << "Öğrenci Bulma Sistemine Hoşgeldiniz." << endl << "------------------" << endl;
    int a;
    int b = 0;
    int* c = &b;
    Ogrenci ogr[max];
    do{
        system("cls");
    menu();
   
        
        cout << "Seçim Yapınız Lütfen:";
        cin >> a;
        
        switch (a) {
        case 1:
            ogrencibul(ogr,*c);
            break;
        case 2:
            ogrencilistele(ogr,*c);
            break;
        case 3:
            ogrenciekle(ogr, *c);
            break;
        case 4:
            "Çıkış yapılıyor...";
            break;
        default:
            cout << "Yanlış karakter girdiniz.";
            break;
        }
        cout << "herhangi bir tuşa basın";
        cin.ignore();
        cin.get();
       
    } while (a != 4);
    return 0;


    
}

