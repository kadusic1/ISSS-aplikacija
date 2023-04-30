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
    // Pokusaj logina
    do {
        show_login();
        loginData = try_login();
        if(loginData.empty()) {
            cout << "Neispravan email ili password\n";
            cls();
        }
    } while(loginData.empty());
    // Kada login uspije idemo na meny
    cout << "Uspjesan login!\n";
    cls();
    menu(loginData);
    
    return 0;
}