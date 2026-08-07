// İHA SİMULASYONU.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include<windows.h>
#include <memory>
#include<vector>
using namespace std;
class HavaAraci {
protected:
    int hiz, irtifa, yakit;
    string ihaAdi;
public:
virtual ~HavaAraci() = default;
    HavaAraci(string ad) {
    ihaAdi=ad;
        hiz = 0;
        irtifa = 0;
        yakit = 100;
    }
    void hızlan(int a) {
        hiz = hiz + a;
    }
    void yavasla(int b) {
        hiz = hiz - b;
    }
    void irtifaKazan(int c) {
        irtifa = irtifa + c;
    }
    virtual void durumBildir() {
        cout << "İha Adı:" << ihaAdi << endl;
        cout << "İrtifa:" << irtifa << endl;
        cout << "Hız:" << hiz << endl;
        cout << "Yakıt:" << yakit << endl;

    }
};
class Siha :public HavaAraci {
private:
    int fuziSayisi; 

public:

    
    Siha(string ad, int baslangicFüzesi) : HavaAraci(ad) {
        fuziSayisi = baslangicFüzesi;
    }

    void atesEt() {
        if (fuziSayisi > 0) {
            fuziSayisi = fuziSayisi - 1;
            yakit = yakit - 5;
            cout << "Füze fırlatıldı! Kalan füze:" << fuziSayisi << endl;
        }
        else {
            cout << "Füze Fırlatılamadı! Mühimmat yok.";
        }
       
    }

    
    void durumBildir() override {
       HavaAraci::durumBildir();
        cout << "Mühimmat Durumu: " << fuziSayisi << " adet füze" << endl;
        cout << "-----------------------" << endl;
    }
};

int main() {
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);

    vector<unique_ptr<HavaAraci>> havaFilosu;
    int secim = 0;
    bool calisiyor = true; 

    while (calisiyor) {
        cout << "\n--- SBTÜ İHA KONTROL PANELİ ---" << endl;
        cout << "1. Yeni Standart İHA Üret" << endl;
        cout << "2. Yeni SİHA (Silahlı) Üret" << endl;
        cout << "3. Tüm Filo Durum Raporu" << endl;
        cout << "4. Çıkış" << endl;
        cout << "5. Filoyu Uçur" << endl;
        cout << "6. Filoyu Taarruza Geçir" << endl;
        cout << "Seçiminiz: ";
        cin >> secim;
        system("cls"); 

        switch (secim) {
        case 1: {
            string isim;
            cout << "Üretilecek İHA'nın adı ne olsun?: ";
            cin >> isim;
           havaFilosu.push_back(make_unique<HavaAraci>(isim));
            system("cls");
            cout << isim << " isimli hava aracı başarıyla oluşturuldu ve filoya katıldı." << endl;
            break;
        }
        case 2: {
            string isim;
            int fuze;
            cout << "Üretilecek SİHA'nın adı ne olsun?: ";
            cin >> isim;
            cout << "Kaç adet füze yüklensin?: ";
            cin >> fuze;
           havaFilosu.push_back(make_unique<Siha>(isim, fuze));
            system("cls");
            cout << isim << " isimli SİHA başarıyla oluşturuldu ve filoya eklendi." << endl;
            break;
        }
        case 3: {
            cout << "\n==== FİLODAKİ ARAÇLARIN GÜNCEL DURUMU ====\n" << endl;
            if (havaFilosu.empty()) {
                cout << "Filoda henüz hiç araç yok!" << endl;
            }
            else {
                for (HavaAraci* iha : havaFilosu) {
                    iha->durumBildir(); 
                }
            }
            break;
        }
        case 4: {
            cout << "Sistem kapatılıyor..." << endl;
            calisiyor = false; 
            break;
        }
        case 5: {
            cout << "\n==== FİLO HAVALANIYOR ====\n" << endl;
            if (havaFilosu.empty()) {
                cout << "Uçurulacak araç yok!" << endl;
            }
            else {
                for (const auto& a : havaFilosu)
           {
             a->hızlan(100);
             a->irtifaKazan(100);
           }
                cout << "Tüm filoya hızlanma ve tırmanma emri verildi!" << endl;
            }
            break;
        }
        case 6: {
            cout << "\n==== TAKTİK TAARRUZ BAŞLADI ====\n" << endl;
            if (havaFilosu.empty()) {
                cout << "Filoda araç yok!" << endl;
            }
            else {
               for (const auto& iha : havaFilosu)
{
    Siha* sihaIsaretci = dynamic_cast<Siha*>(iha.get());

    if(sihaIsaretci)
        sihaIsaretci->atesEt();
}
            }
            break;
        }
        default:
            cout << "Geçersiz seçim! Tekrar deneyin." << endl;
        } 

    } 

    
   

    return 0;
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
