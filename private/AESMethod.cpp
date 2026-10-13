#include "IEncryptionMethod.hpp"
#include "AES.hpp"

class AESMethod final : public IEncryptionMethod{
public:
   explicit AESMethod(const std::string& key) : IEncryptionMethod(key){
      //size_t pad = 32 - _key.size();
      //_key.append(pad, static_cast<char>(pad));
   }

   static std::string toHex(const std::string& in){
      static const char* digits = "0123456789abcdef";
      std::string out;
      out.reserve(in.size() * 2);
      for(unsigned char c : in){
         out.push_back(digits[c >> 4]);
         out.push_back(digits[c & 15]);
      }
      return out;
   }
   
   static std::string fromHex(const std::string& in){
   if(in.size() % 2 != 0) throw std::runtime_error("Invalid stored data");
   auto val = [](char c) -> int {
      if(c >= '0' && c <= '9') return c - '0';
      if(c >= 'a' && c <= 'f') return c - 'a' + 10;
      //throw std::runtime_error("Invalid stored data");
   };
   std::string out;
   out.reserve(in.size() / 2);
   for(size_t i = 0; i < in.size(); i += 2)
      out.push_back(static_cast<char>((val(in[i]) << 4) | val(in[i + 1])));
   return out;
   }

   template <size_t Bits>
   static std::string aesEncrypt(const std::string& key, std::string data){
      unsigned char k[Bits/8] = {};
      std::copy_n(key.begin(), std::min(key.size(), sizeof(k)), k);

      Cipher::Aes<Bits> aes(k);

      size_t pad = 16 - (data.size() % 16);
      data.append(pad, static_cast<char>(pad));

      for(size_t i=0; i<data.size(); i+=16){
         aes.encrypt_block(reinterpret_cast<unsigned char*>(&data[i]));
      }

      return data;
   }

   template <size_t Bits>
   static std::string aesDecrypt(const std::string& key, std::string data){
      unsigned char k[Bits/8] = {};
      std::copy_n(key.begin(), std::min(key.size(), sizeof(k)), k);

      Cipher::Aes<Bits> aes(k);

      for(size_t i=0; i<data.size(); i+=16){
         aes.decrypt_block(reinterpret_cast<unsigned char*>(&data[i]));
      }

      size_t pad = data.back();

      data.resize(data.size()-pad);

      return data;
   }

   std::string encrypt(const std::string& input) const override{
      /*switch(_key.size()){
         case 16: return aesEncrypt<128>(_key, input);
         case 32: return aesEncrypt<256>(_key, input);
      }*/
     return toHex(aesEncrypt<128>(_key, input));
   } 

   std::string decrypt(const std::string& input) const override{
      /*switch(_key.size()){
         case 16: return aesDecrypt<128>(_key, input);
         case 32: return aesDecrypt<256>(_key, input);
      }*/

      return aesDecrypt<128>(_key, fromHex(input));
   }

};

