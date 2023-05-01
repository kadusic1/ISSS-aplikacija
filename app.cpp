#include <iostream>
#include <vector>
#include <string>

#include "functions/loginPage.cpp"
#include "functions/helper.cpp"
#include "functions/menu.cpp"
#include "functions/rootfunctions.cpp"

using namespace std;

int main() {

    // Varijabla u kojoj cemo pohraniti podatke o logovanoj osobi
    vector<string> loginData;
    // Varijabla u kojoj se smjesta izbor stranice odabran u menu funkciji
    int pageChoice;
    // Pokusaj logina
    do {
        show_login();
        loginData = try_login();
        if(loginData.empty()) {
            cout << "Neispravan email ili password\n";
            cls();
        }
    } while(loginData.empty());
    // Kada login uspije idemo na menu i brisemo ekran
    cout << "Uspjesan login!\n";

    // Dok petlja radi stranica je pokrenuta tj. u up stanju
    while(true) {
    // Pohranjujemo odabir stranice
    pageChoice = menu(loginData);
    // Redirekcija na odgovarajucu stranu pomocu switch case
    switch(pageChoice) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            // Napustamo petlju preko labeli i zavrsavamo program
            goto END;
            break;
        case 8:
            // Odabir koju funkciju zelimo pozvati
            int functionChoice = root_menu();
            switch(functionChoice) {
                case 1:
                    edit_college_info();
                    break;
                case 2:
                    add_department();
                    break;
                case 3:
                    cout << "Izbor 3\n";
                    break;
                case 4:
                    cout << "Izbor 4\n";
                    break;
                case 5:
                    cout << "Izbor 5\n";
                    break;
            }
            break;
    }
    }
    
    // Ispisujemo zadnju poruku prije zavrsetka
    END:
    cls();
    cout << "Zelimo vam ugodan dan.\n";

    return 0;
}