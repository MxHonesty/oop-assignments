#pragma once
#include <exception>
#include <string>

class CosError : public std::exception {
protected:
	std::string msg;
public:
	/** Message constructor. */
	CosError(const std::string& error_message) : msg{ error_message } {};

	/** Constructor din pointer la sir de caractere. */
	CosError(const char* error_message) : msg{ error_message } {};

	const char* what() const noexcept override;
};
