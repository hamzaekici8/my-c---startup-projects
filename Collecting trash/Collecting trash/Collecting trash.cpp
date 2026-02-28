

#include <iostream>
#include<string>
using namespace std;
struct cop {
    int id;
    int fullnessLevel;
    string type;
};
struct mahalle {
    string districtName;
    int population;
    cop containers[10];
    int activeContainerCount;
};
void menu() {
    cout << "Display District Report   [0]" << endl;
    cout << "Get Most Filled Container [1]" << endl;
    cout << "List Urgent  Evacuations  [2]" << endl;
    cout << "Quit                      [3]" << endl;
}
void sırala(mahalle a,mahalle b) {
    string c;
    double sum = 0.0;
 
    cout << "Choose a district which you want to see report.(a or b):";
    cin >> c;
    if (c == "a") {
        cout << "Mahalle name:" << a.districtName << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". container:" << endl;
            cout << "id:" << a.containers[i].id << endl;
            cout << "Fullness level:" << a.containers[i].fullnessLevel << endl;
            cout << "Type:" << a.containers[i].type << endl << endl;
            sum = sum + a.containers[i].fullnessLevel;
        }
        cout << "Average fulness level:" << sum / 3 << endl;
    }
    else if (c == "b") {
        cout << "Mahalle name:" << b.districtName << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". container:" << endl;
            cout << "id:" << b.containers[i].id << endl;
            cout << "Fullness level:" << b.containers[i].fullnessLevel << endl;
            cout << "Type:" << b.containers[i].type << endl << endl;
            sum = sum + b.containers[i].fullnessLevel;
        }
        cout << "Average fulness level:" << sum / 3 << endl;
    }
    else {
        cout << "You choose wrong character.";
    }
}
cop dolu(mahalle a, mahalle b) {
    cop maxContainer = a.containers[0];

    
    for (int i = 0; i < a.activeContainerCount; i++) {
        if (a.containers[i].fullnessLevel > maxContainer.fullnessLevel) {
            maxContainer = a.containers[i];
        }
    }

   
    for (int i = 0; i < b.activeContainerCount; i++) {
        if (b.containers[i].fullnessLevel > maxContainer.fullnessLevel) {
            maxContainer = b.containers[i];
        }
    }

    return maxContainer;
}
void topla(mahalle m) {
    int threshold;
    cout << "Enter threshold value: ";
    cin >> threshold;

    cout << "Containers above threshold:" << endl;

    for (int i = 0; i < m.activeContainerCount; i++) {
        if (m.containers[i].fullnessLevel > threshold) {
            cout << "ID: " << m.containers[i].id << endl;
        }
    }
}

int main()
{
    mahalle a, b;
    a.districtName = "Gultepe";
    a.population = 500;
    a.activeContainerCount = 3;
    a.containers[0].id = 1; a.containers[0].fullnessLevel = 80; a.containers[0].type = "Plastic";
    a.containers[1].id = 2; a.containers[1].fullnessLevel = 50; a.containers[1].type = "İron";
    a.containers[2].id = 3; a.containers[2].fullnessLevel = 60; a.containers[2].type = "Plastic";


    b.districtName = "Mevlana";
    b.population = 600;
    b.activeContainerCount = 3;
    b.containers[0].id = 4; b.containers[0].fullnessLevel = 30; b.containers[0].type = "İron";
    b.containers[1].id = 5; b.containers[1].fullnessLevel = 40; b.containers[1].type = "İron";
    b.containers[2].id = 6; b.containers[2].fullnessLevel = 100; b.containers[2].type = "İron";
    int c;
    do {
        system("cls");
        cout << "Choose a option which you want." << endl;
        menu();
        cin >> c;
        switch (c) {
        case 0:
            sırala(a, b);
            break;
        case 1:
        {
            cop result = dolu(a, b);
            cout << "Most filled container:" << endl;
            cout << "ID: " << result.id << endl;
            cout << "Type: " << result.type << endl;
            cout << "Fullness: " << result.fullnessLevel << endl;
            break;
        }
            
        case 2:
        {
            string secim;
            cout << "Choose district (a or b): ";
            cin >> secim;

            if (secim == "a")
                topla(a);
            else if (secim == "b")
                topla(b);
            else
                cout << "Wrong district choice.";
            break;
        }
        case 3:
            cout << "Leaving" << endl;
            break;
        default:
            cout << "You entered wrong number." << endl;
            break;
            

        }
        cout << "Press any button";
        cin.ignore();
        cin.get();
    } while (c != 3);
    
}


