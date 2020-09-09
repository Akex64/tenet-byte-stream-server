#ifndef RESPONSE_H
#define RESPONSE_H

#include <list> 
#include <string>

#pragma region Classes
class LicenseKey {
public:
    LicenseKey() = default;
    LicenseKey(std::string const& key, std::string const& expiry, std::string const& discord, std::string const& customer);
public:
    std::string m_discord;
    std::string m_customer;
    std::string m_key;
    std::string m_expiry;
};

class Package {
public:
    Package() = default;
    Package(std::string const& name, int duration_int, std::string const& duration_type);
public:
    std::string m_name;
    int m_duration_int = 0;
    std::string m_duration_type;
};

class Product {
public:
    Product() = default;
    Product(std::string const& name, std::string const& version, std::string const& game_name, std::string const& game_version, std::string const& description, std::string const& status);
public:
    std::string m_name;
    std::string m_version;
    std::string m_game_name;
    std::string m_game_version;
    std::string m_description;
    std::string m_status;
};

class Error {
public:
    Error() = default;
    Error(std::string const& error, bool succeed);
public:
    std::string m_error;
    bool m_succeed;
};

class Variable {
public:
    Variable() = default;
    Variable(std::string const& name, std::string const& value);
public:
    std::string m_name;
    std::string m_value;
};

#pragma endregion

class Response {
private:
public:
    ~Response(void);

    double elapsed;

    Error Error;
    Product Product;
    Package Package;
    LicenseKey LicenseKey;
    std::list<Variable> Variables;
};

#endif