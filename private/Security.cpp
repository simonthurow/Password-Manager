#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#ifdef __WIN32__
#include <openssl/sha.h>
#include <conio.h>
#include <windows.h>
#include <bcrypt.h>
#elif __APPLE__
#include <termios.h>
#include <unistd.h>
#include <CommonCrypto/CommonDigest.h>
#include <Security/Security.h>
#endif
#include <iomanip>
//#pragma comment(lib, "bcrypt.lib")

class Security{
public:
    static void hideKey(std::string& key){
        #ifdef __WIN32__
            char ch;

            while((ch = _getch()) != '\r'){
                if(ch == '\b'){
                    if(!key.empty()){
                        key.pop_back();
                        std::cout << "\b \b";
                    }
                } else {
                    std::cout << '*';
                    key += ch;
                }
            }
        #elif __APPLE__
            termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;

            newt.c_lflag &= ~(ECHO|ICANON);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            std::cout << std::flush;
            char ch;
            while (true)
            {
                if (read(STDIN_FILENO, &ch, 1) != 1)
                continue;

                if (ch == '\n' || ch == '\r')
                break;

                if (ch == 127 || ch == 8)
                {
                    if (!key.empty())
                    {
                        key.pop_back();
                        std::cout << "\b \b" << std::flush;
                    }
                }
                else
                {
                    key.push_back(ch);
                    std::cout << '*' << std::flush;
                }
            }

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        #endif
    }

    static std::string sha256(const std::string& input) {
        #if __WIN32__
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256(reinterpret_cast<const unsigned char*>(input.data()),input.size(), hash);
    
            std::ostringstream oss;
            for (unsigned char c : hash)
                oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
            return oss.str();
        #elif __APPLE__
            unsigned char hash[CC_SHA256_DIGEST_LENGTH];
            CC_SHA256(input.data(), (CC_LONG)input.size(), hash);
            std::ostringstream oss;
            for(unsigned char c : hash)
                oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
            return oss.str();
        #endif
    }

    static bool comparePasswords(const std::string& shaInput, const std::string& cleanInput){
        return shaInput == sha256(cleanInput);
    }

#if __WIN32__
    static bool getSecureRandomBytes(void* buf, ULONG bufSize){
        if(!buf || bufSize == 0) return false;

        NTSTATUS status = BCryptGenRandom(
            nullptr,
            static_cast<PUCHAR>(buf),
            bufSize,
            BCRYPT_USE_SYSTEM_PREFERRED_RNG
        );

        return BCRYPT_SUCCESS(status);
    }
#endif

    static std::string generateStrongPassword(){
        //TODO: Create actual strong password generation
        std::string _alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$^&*()-_+={}[]|;:',./";

        std::vector<uint8_t> randomBytes(16);
        std::string password = "";
#if __WIN32__

        getSecureRandomBytes(randomBytes.data(), static_cast<ULONG>(randomBytes.size()));
#elif __APPLE__
        int r = SecRandomCopyBytes(kSecRandomDefault, randomBytes.size(), &(randomBytes[0]));
        if(!r) {
            std::cout << "Failure to create random bytes!" << std::endl;
            return "password";
        }
#endif

        for(uint8_t i : randomBytes){
            password += _alphabet[i % _alphabet.size()];
        }

        return password;
    }
};
