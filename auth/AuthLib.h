#ifndef AUTH_H
#define AUTH_H

#include <response.h>

enum class HwidOption {
    Computer_Name,
    Username,
    Base_Board,
    Physical_Memory
};

class Auth
{
private:

    void SetSignature();

    std::string GetHwid();
    std::list<HwidOption> m_hwid_options;

    std::string GetToken();
    bool VerifyToken(std::string Token);

    std::string m_security_key;
    const std::string m_product_code;

    std::list<std::string> m_requested_variables;
public:

    Auth(std::string product_code, std::list<HwidOption> hwid_options = std::list<HwidOption>()) : m_product_code(product_code), m_hwid_options(hwid_options) { }
    ~Auth(void);

    void RequestVariables(std::list<std::string> Variables);

    bool ProcessKey(Response& response, std::string Key);
};

#endif
