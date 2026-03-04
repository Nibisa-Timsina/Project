#pragma once
#include <string>

enum Authority { Guest, ClientSELLER, ClientBUYER, Admin };

class USER_ACCOUNT
{
    private:
        Authority authority;
        std::string full_name;
        std::string contact_num;
        std::string location;
        int age;
        std::string username;
        std::string password, mail_address;
    public:
       USER_ACCOUNT();
       USER_ACCOUNT(std:: string full_name, std:: string username, std:: string password, std:: string contact_num, int age, std:: string location, std:: string  mail_address, Authority auth);       Authority getAuthority() const;
        void setAuthority(Authority auth);
        std::string getFullname();
        std::string getPassword();
        std::string getUsername();
};