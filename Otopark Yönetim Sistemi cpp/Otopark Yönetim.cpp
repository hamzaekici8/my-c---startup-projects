// Otopark Yönetim.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include<windows.h>
#include <ctime>
#define ucret 20
#define sayı 5
using namespace std;
struct Arac {
    string plaka;
    time_t girisSaati;
    bool parktaMi;
};

int giris(Arac ba[],int &sayac) {
    if (sayac == sayı) {
        cout << "Kusura bakmayın otopark dolu." << endl;
    }
    
        cout << "**********************************" << endl;
        cout << "Plaka giriniz         :";
        cin >> ba[sayac].plaka;
        ba[sayac].girisSaati=time(0);
        ba[sayac].parktaMi = true;

        cout << "Giriş başarılı." << endl;
        return sayac++;


    


}
void cıkıs(Arac bas[], int sayac) {
    string plaka;
    time_t simdi = time(0);
    bool bulundu = false;

    cout << "Cikisini yapmak istediginiz aracin plakasini giriniz: ";
    cin >> plaka;

    for (int i = 0; i < sayac; i++) {
        if (bas[i].plaka == plaka && bas[i].parktaMi) {

            double gecenSure = difftime(simdi, bas[i].girisSaati); // saniye
            double ucretTutar = (gecenSure / 3600.0) * ucret;

            cout << "------------------------------" << endl;
            cout << "Plaka        : " << bas[i].plaka << endl;
            cout << "Gecen Sure   : " << (int)(gecenSure / 60) << " dakika" << endl;
            cout << "Ucret        : " << ucretTutar << " TL" << endl;
            cout << "------------------------------" << endl;

            bas[i].parktaMi = false;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "Arac bulunamadi veya zaten cikis yapilmis!" << endl;
    }
}

void durumGoster(Arac otopark[], int sayac) {
    cout << "\n--- OTOPARK DURUMU ---\n";
    for (int i = 0; i < sayac; i++) {
        if (otopark[i].parktaMi) {
            cout << "Plaka: " << otopark[i].plaka
                << " | Giris Saati: " << otopark[i].girisSaati << endl;
        }
    }
}

void menu() {
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    cout << "**********************************" << endl;
    cout << "    Araç girişi          [1]" << endl;
    cout << "     Araç çıkışı         [2]" << endl;
    cout << "    Otopark doluluk oranı[3]" << endl;
    cout << "    çıkış                [4]" << endl;
    cout << "**********************************" << endl;

}

int main()
{
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    int a, b=0;
    int *sayac = &b;

    Arac bas[sayı];
    do {
        system("cls");
        cout << "**********************************" << endl;
        cout << "Otopark sistemine hoşgeldiniz.Lütfen yapmak istediğiniz işlemi seçin" << endl;
        menu();
        cin >> a;
        switch (a) {
        case 1:
            giris(bas, *sayac);
            break;
        case 2:
            cıkıs(bas,*sayac);
            break;
        case 3:
            durumGoster(bas, *sayac);
            break;
        case 4:
            break;
        default:
            cout << "Yanlış karakter girdiniz.";
        }
        cin.ignore();
        cin.get();
    } while (a != 4);
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
