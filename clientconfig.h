#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include <QString>
#include "cryptopp/rsa.h"

class ClientConfig
{
public:
    static ClientConfig &getInstance()
    {
        static ClientConfig instance;
        return instance;
    }

    const QString &getServerUrl()
    {
        return serverUrl;
    }

    const CryptoPP::RSA::PublicKey &getPublicKey()
    {
        return publicKey;
    }

    const CryptoPP::RSA::PrivateKey &getPrivateKey()
    {
        return privateKey;
    }

private:
    QString serverUrl;
    CryptoPP::RSA::PublicKey publicKey;
    CryptoPP::RSA::PrivateKey privateKey;
};

#endif // CLIENTCONFIG_H