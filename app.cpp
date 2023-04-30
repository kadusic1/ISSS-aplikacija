#include <iostream>
#include <vector>
#include <string>

#include "functions/loginPage.cpp"
#include "functions/helper.cpp"
#include "functions/menu.cpp"

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
    cls();
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
            break;
        default:
            break;
    }
    
    return 0;
}