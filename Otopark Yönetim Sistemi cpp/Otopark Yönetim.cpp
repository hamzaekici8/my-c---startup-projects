#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

const int MAKSIMUM_KAPASITE = 20;
const double VARSAYILAN_SAATLIK_UCRET = 20.0;

struct Arac {
    int kayitNo;
    string plaka;
    time_t girisSaati;
    time_t cikisSaati;
    int parkYeriNo;
    bool parktaMi;
    double odenenUcret;
};

int secimAl();
void devamBekle();

string plakaDuzenle(string plaka) {
    string sonuc;

    for (char karakter : plaka) {
        if (!isspace(static_cast<unsigned char>(karakter))) {
            sonuc += static_cast<char>(toupper(static_cast<unsigned char>(karakter)));
        }
    }

    return sonuc;
}

string zamanYazdir(time_t zamanDamgasi) {
    if (zamanDamgasi == 0) {
        return "-";
    }

    tm yerelZaman {};
    localtime_s(&yerelZaman, &zamanDamgasi);

    char tampon[80];
    strftime(tampon, sizeof(tampon), "%d.%m.%Y %H:%M:%S", &yerelZaman);
    return tampon;
}

int aktifAracSayisi(const vector<Arac>& araclar) {
    int toplam = 0;

    for (const Arac& arac : araclar) {
        if (arac.parktaMi) {
            toplam++;
        }
    }

    return toplam;
}

int kullanilabilirParkYeri(const vector<Arac>& araclar) {
    for (int yer = 1; yer <= MAKSIMUM_KAPASITE; yer++) {
        bool dolu = false;

        for (const Arac& arac : araclar) {
            if (arac.parktaMi && arac.parkYeriNo == yer) {
                dolu = true;
                break;
            }
        }

        if (!dolu) {
            return yer;
        }
    }

    return -1;
}

int aktifAracIndexBul(const vector<Arac>& araclar, const string& plaka) {
    for (size_t i = 0; i < araclar.size(); i++) {
        if (araclar[i].parktaMi && araclar[i].plaka == plaka) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

double ucretHesapla(time_t girisSaati, time_t cikisSaati) {
    double saniyeFarki = difftime(cikisSaati, girisSaati);
    double saat = saniyeFarki / 3600.0;
    double yuvarlanmisSaat = ceil(saat);

    if (yuvarlanmisSaat < 1) {
        yuvarlanmisSaat = 1;
    }

    return yuvarlanmisSaat * VARSAYILAN_SAATLIK_UCRET;
}

double ucretHesapla(time_t girisSaati, time_t cikisSaati, double saatlikUcret) {
    double saniyeFarki = difftime(cikisSaati, girisSaati);
    double saat = saniyeFarki / 3600.0;
    double yuvarlanmisSaat = ceil(saat);

    if (yuvarlanmisSaat < 1) {
        yuvarlanmisSaat = 1;
    }

    return yuvarlanmisSaat * saatlikUcret;
}

void girisYap(vector<Arac>& araclar, int& sonrakiKayitNo) {
    if (aktifAracSayisi(araclar) >= MAKSIMUM_KAPASITE) {
        cout << "\nOtopark dolu. Yeni arac girisi yapilamiyor.\n";
        return;
    }

    string plaka;
    cout << "\nPlaka giriniz: ";
    cin >> plaka;
    plaka = plakaDuzenle(plaka);

    if (aktifAracIndexBul(araclar, plaka) != -1) {
        cout << "Bu plaka ile kayitli arac zaten otoparkta bulunuyor.\n";
        return;
    }

    int parkYeriNo = kullanilabilirParkYeri(araclar);
    time_t simdi = time(nullptr);

    Arac yeniArac;
    yeniArac.kayitNo = sonrakiKayitNo++;
    yeniArac.plaka = plaka;
    yeniArac.girisSaati = simdi;
    yeniArac.cikisSaati = 0;
    yeniArac.parkYeriNo = parkYeriNo;
    yeniArac.parktaMi = true;
    yeniArac.odenenUcret = 0.0;

    araclar.push_back(yeniArac);

    cout << "\nGiris basarili.\n";
    cout << "Kayit No   : " << yeniArac.kayitNo << '\n';
    cout << "Plaka      : " << yeniArac.plaka << '\n';
    cout << "Park Yeri  : " << yeniArac.parkYeriNo << '\n';
    cout << "Giris Saati: " << zamanYazdir(yeniArac.girisSaati) << '\n';
}

void cikisYap(vector<Arac>& araclar, double& toplamGelir, double saatlikUcret) {
    string plaka;
    cout << "\nCikis yapacak aracin plakasini giriniz: ";
    cin >> plaka;
    plaka = plakaDuzenle(plaka);

    int index = aktifAracIndexBul(araclar, plaka);
    if (index == -1) {
        cout << "Arac bulunamadi veya cikis islemi daha once yapilmis.\n";
        return;
    }

    time_t simdi = time(nullptr);
    double ucret = ucretHesapla(araclar[index].girisSaati, simdi, saatlikUcret);
    double dakika = difftime(simdi, araclar[index].girisSaati) / 60.0;

    araclar[index].parktaMi = false;
    araclar[index].cikisSaati = simdi;
    araclar[index].odenenUcret = ucret;
    toplamGelir += ucret;

    cout << "\nCikis islemi tamamlandi.\n";
    cout << "Plaka        : " << araclar[index].plaka << '\n';
    cout << "Park Yeri    : " << araclar[index].parkYeriNo << '\n';
    cout << "Gecen Sure   : " << fixed << setprecision(0) << dakika << " dakika\n";
    cout << "Toplam Ucret : " << fixed << setprecision(2) << ucret << " TL\n";
    cout << "Cikis Saati  : " << zamanYazdir(araclar[index].cikisSaati) << '\n';
}

void aktifAraclariListele(const vector<Arac>& araclar) {
    int dolu = aktifAracSayisi(araclar);
    int bos = MAKSIMUM_KAPASITE - dolu;

    cout << "\n--- OTOPARK DURUMU ---\n";
    cout << "Toplam Kapasite : " << MAKSIMUM_KAPASITE << '\n';
    cout << "Dolu Yer Sayisi : " << dolu << '\n';
    cout << "Bos Yer Sayisi  : " << bos << '\n';
    cout << "Doluluk Orani   : " << fixed << setprecision(2)
         << (static_cast<double>(dolu) / MAKSIMUM_KAPASITE) * 100.0 << "%\n";

    if (dolu == 0) {
        cout << "\nOtoparkta aktif arac bulunmuyor.\n";
        return;
    }

    cout << "\nAktif arac listesi:\n";
    cout << left << setw(10) << "Kayit"
         << setw(15) << "Plaka"
         << setw(12) << "Park Yeri"
         << setw(22) << "Giris Saati" << '\n';

    for (const Arac& arac : araclar) {
        if (arac.parktaMi) {
            cout << left << setw(10) << arac.kayitNo
                 << setw(15) << arac.plaka
                 << setw(12) << arac.parkYeriNo
                 << setw(22) << zamanYazdir(arac.girisSaati) << '\n';
        }
    }
}

void aracSorgula(const vector<Arac>& araclar) {
    string plaka;
    cout << "\nSorgulamak istediginiz plaka: ";
    cin >> plaka;
    plaka = plakaDuzenle(plaka);

    bool bulundu = false;

    for (const Arac& arac : araclar) {
        if (arac.plaka == plaka) {
            bulundu = true;

            cout << "\n--- ARAC BILGISI ---\n";
            cout << "Kayit No     : " << arac.kayitNo << '\n';
            cout << "Plaka        : " << arac.plaka << '\n';
            cout << "Durum        : " << (arac.parktaMi ? "Otoparkta" : "Cikis yapmis") << '\n';
            cout << "Park Yeri    : " << arac.parkYeriNo << '\n';
            cout << "Giris Saati  : " << zamanYazdir(arac.girisSaati) << '\n';
            cout << "Cikis Saati  : " << zamanYazdir(arac.cikisSaati) << '\n';
            cout << "Odenen Ucret : " << fixed << setprecision(2) << arac.odenenUcret << " TL\n";
        }
    }

    if (!bulundu) {
        cout << "Bu plakaya ait kayit bulunamadi.\n";
    }
}

void gelirRaporu(const vector<Arac>& araclar, double toplamGelir) {
    int aktif = 0;
    int cikisYapan = 0;

    for (const Arac& arac : araclar) {
        if (arac.parktaMi) {
            aktif++;
        } else {
            cikisYapan++;
        }
    }

    cout << "\n--- GELIR RAPORU ---\n";
    cout << "Toplam Kayitli Arac : " << araclar.size() << '\n';
    cout << "Aktif Arac Sayisi   : " << aktif << '\n';
    cout << "Cikis Yapan Arac    : " << cikisYapan << '\n';
    cout << "Toplam Gelir        : " << fixed << setprecision(2) << toplamGelir << " TL\n";
}

void kayitGecmisi(const vector<Arac>& araclar) {
    if (araclar.empty()) {
        cout << "\nHenuz hic kayit bulunmuyor.\n";
        return;
    }

    cout << "\n--- KAYIT GECMISI ---\n";
    cout << left << setw(8) << "No"
         << setw(15) << "Plaka"
         << setw(12) << "Durum"
         << setw(12) << "Park Yeri"
         << setw(22) << "Giris"
         << setw(22) << "Cikis"
         << setw(12) << "Ucret" << '\n';

    for (const Arac& arac : araclar) {
        cout << left << setw(8) << arac.kayitNo
             << setw(15) << arac.plaka
             << setw(12) << (arac.parktaMi ? "Iceride" : "Cikti")
             << setw(12) << arac.parkYeriNo
             << setw(22) << zamanYazdir(arac.girisSaati)
             << setw(22) << zamanYazdir(arac.cikisSaati)
             << setw(12) << fixed << setprecision(2) << arac.odenenUcret << '\n';
    }
}

bool adminGiris(const string& adminSifresi) {
    string girilenSifre;
    cout << "\nAdmin sifresini giriniz: ";
    getline(cin, girilenSifre);

    if (girilenSifre == adminSifresi) {
        cout << "Admin girisi basarili.\n";
        return true;
    }

    cout << "Hatali sifre.\n";
    return false;
}

void aktifParkYerleriniGoster(const vector<Arac>& araclar) {
    cout << "\n--- AKTIF PARK YERLERI ---\n";

    for (int yer = 1; yer <= MAKSIMUM_KAPASITE; yer++) {
        bool dolu = false;
        string plaka;

        for (const Arac& arac : araclar) {
            if (arac.parktaMi && arac.parkYeriNo == yer) {
                dolu = true;
                plaka = arac.plaka;
                break;
            }
        }

        cout << "Park Yeri " << setw(2) << yer << " : "
             << (dolu ? "Dolu - " + plaka : "Bos") << '\n';
    }
}

void sifreDegistir(string& adminSifresi) {
    string mevcutSifre;
    string yeniSifre;
    string yeniSifreTekrar;

    cout << "\nMevcut admin sifresi: ";
    getline(cin, mevcutSifre);

    if (mevcutSifre != adminSifresi) {
        cout << "Mevcut sifre dogru degil.\n";
        return;
    }

    cout << "Yeni sifre: ";
    getline(cin, yeniSifre);
    cout << "Yeni sifre tekrar: ";
    getline(cin, yeniSifreTekrar);

    if (yeniSifre.empty()) {
        cout << "Sifre bos birakilamaz.\n";
        return;
    }

    if (yeniSifre != yeniSifreTekrar) {
        cout << "Yeni sifreler eslesmiyor.\n";
        return;
    }

    adminSifresi = yeniSifre;
    cout << "Admin sifresi basariyla guncellendi.\n";
}

void adminPaneli(vector<Arac>& araclar, double toplamGelir, string& adminSifresi, double& saatlikUcret) {
    if (!adminGiris(adminSifresi)) {
        return;
    }

    int secim = 0;

    do {
        system("cls");
        cout << "=========================================\n";
        cout << "            ADMIN PANELI\n";
        cout << "=========================================\n";
        cout << "1 - Gelir raporu\n";
        cout << "2 - Tum kayit gecmisi\n";
        cout << "3 - Park yeri doluluk haritasi\n";
        cout << "4 - Saatlik ucreti gor\n";
        cout << "5 - Saatlik ucreti guncelle\n";
        cout << "6 - Admin sifresini degistir\n";
        cout << "7 - Ana menuye don\n";
        cout << "=========================================\n";
        cout << "Seciminiz: ";
        secim = secimAl();

        switch (secim) {
        case 1:
            gelirRaporu(araclar, toplamGelir);
            break;
        case 2:
            kayitGecmisi(araclar);
            break;
        case 3:
            aktifParkYerleriniGoster(araclar);
            break;
        case 4:
            cout << "\nGuncel saatlik ucret: " << fixed << setprecision(2) << saatlikUcret << " TL\n";
            break;
        case 5: {
            double yeniUcret;
            cout << "\nYeni saatlik ucret: ";
            while (!(cin >> yeniUcret) || yeniUcret <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Pozitif bir ucret giriniz: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            saatlikUcret = yeniUcret;
            cout << "Saatlik ucret guncellendi.\n";
            break;
        }
        case 6:
            sifreDegistir(adminSifresi);
            break;
        case 7:
            cout << "\nAdmin panelinden cikiliyor...\n";
            break;
        default:
            cout << "\nGecersiz secim yaptiniz.\n";
            break;
        }

        if (secim != 7) {
            devamBekle();
        }
    } while (secim != 7);
}

void menuGoster() {
    cout << "=========================================\n";
    cout << "      OTOPARK YONETIM SISTEMI\n";
    cout << "=========================================\n";
    cout << "1 - Arac girisi\n";
    cout << "2 - Arac cikisi\n";
    cout << "3 - Aktif araclar ve doluluk\n";
    cout << "4 - Plaka ile arac sorgula\n";
    cout << "5 - Admin paneli\n";
    cout << "6 - Programdan cikis\n";
    cout << "=========================================\n";
    cout << "Seciminiz: ";
}

int secimAl() {
    int secim;

    while (!(cin >> secim)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Lutfen gecerli bir sayi giriniz: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return secim;
}

void devamBekle() {
    cout << "\nDevam etmek icin Enter tusuna basin...";
    cin.get();
}

int main() {
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);

    vector<Arac> araclar;
    int sonrakiKayitNo = 1;
    double toplamGelir = 0.0;
    double saatlikUcret = VARSAYILAN_SAATLIK_UCRET;
    string adminSifresi = "1234";
    int secim = 0;

    do {
        system("cls");
        menuGoster();
        secim = secimAl();

        switch (secim) {
        case 1:
            girisYap(araclar, sonrakiKayitNo);
            break;
        case 2:
            cikisYap(araclar, toplamGelir, saatlikUcret);
            break;
        case 3:
            aktifAraclariListele(araclar);
            break;
        case 4:
            aracSorgula(araclar);
            break;
        case 5:
            adminPaneli(araclar, toplamGelir, adminSifresi, saatlikUcret);
            break;
        case 6:
            cout << "\nProgram sonlandiriliyor...\n";
            break;
        default:
            cout << "\nGecersiz secim yaptiniz.\n";
            break;
        }

        if (secim != 6) {
            devamBekle();
        }
    } while (secim != 6);

    return 0;
}
