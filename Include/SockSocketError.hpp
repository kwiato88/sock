//This code is under MIT licence, you can find the complete file here: https://github.com/kwiato88/sock/blob/master/LICENSE
#pragma once

#include <stdexcept>
#include <string>

namespace sock
{

class Error: public std::runtime_error
{
public:
    Error(const std::string& p_what);

};

class LastError : public Error
{
public:
	LastError(const std::string& p_what);

private:
	int errorCode() const;
};

class ResolveAddressError : public Error
{
public:
	ResolveAddressError(const std::string& p_what, int p_errorCode);
};

}
