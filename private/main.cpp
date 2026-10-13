#include "../public/IPasswordRetriever.hpp"
#include "../public/PasswordManager.hpp"
#include "ClipboardRetriever.cpp"
#include "VigenereMethod.cpp"
#include "AESMethod.cpp"
//#include "Security.cpp"

void loop(PasswordManager&);
void choiceSwitch(const int, PasswordManager&, bool&);

int main(int argc, char *argv[]){

    if(argc<2){
        std::cout << "Please use format: \"./pm [passwordfile]\" to open a file with the key " << "or \".pm -c [passwordfile]\" to create a file with the key" << std::endl;
        return 1;
    }

    if(std::strcmp(argv[1], "-c") == 0){
        if(argc!=3) return 1;
        std::cout << "Please enter Password: ";

        std::string key;
        Security::hideKey(key);
        std::string director = "data/";
        std::cout << std::endl;
        std::ofstream file(director.append(argv[2]));
        if(!file) return 1;
        file << Security::sha256(key) << "\n";
        file.close();
        return 0;
    }

    std::string key;
    std::string dir = "data/";
    std::string fname = argv[1];

    std::cout << "Please enter password: ";
    Security::hideKey(key);
    ClipboardRetriever retriever;
    //VigenereMethod encryptionMethod(key);
    AESMethod encryptionMethod(key);

    PasswordManager pm(dir.append(fname), key, retriever, encryptionMethod);

    loop(pm);

    return 0;
}

void loop(PasswordManager& pm){
    bool running = true;
    int choice;

    std::cout << "\033[H\033[2J\033[3J" << std::flush;
    while(running){
        std::cout << std::endl;
        std::cout << "What do you want to do?\n"
            "[1] [add] \n"
            "[2] [add with generated password]\n"
            "[3, selection] [delete] \n"
            "[4] [all] \n"
            "[5, search] [search] \n"
            "[6, selection] [select] \n"
            "[7] [change Password] \n"
            "[8] [exit] \n" << std::endl;
        std::cin >> choice;
        std::cout << "\033[H\033[2J\033[3J" << std::flush;
        choiceSwitch(choice, pm, running);
    }
}

void choiceSwitch(const int choice, PasswordManager& pm, bool& running){
    int subchoice;
    std::string filterString;
    switch (choice)
    {
    case 1:
        pm.addAccount(false);
        break;
    case 2:
        pm.addAccount(true);
        break;
    case 3:
        std::cin >> subchoice;
        pm.deleteAccount(subchoice);
        break;
    case 4:
        pm.displayAccounts();
        break;
    case 5:
        std::cin >> filterString;
        pm.displayAccounts(filterString);
        break;
    case 6:
        std::cin >> subchoice;
        pm.selectAccount(subchoice);
        break;
    case 7:
        pm.changeFilePassword();
        break;
    case 8:
        pm.exit();
        running = false;
        break;
    default:
        std::cout << "Please select valid choice\n";
        break;
    }
}