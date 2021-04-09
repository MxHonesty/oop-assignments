#pragma once
#include <exception>
#include <string>

class ValidatorError : public std::exception {
protected:
	std::string msg;
public:
	/** Message constructor. */
	ValidatorError(const std::string& error_message) : msg{ error_message } {};

	/** Constructor din pointer la sir de caractere. */
	ValidatorError(const char* error_message) : msg{ error_message } {};

	const char* what() const noexcept override;
};