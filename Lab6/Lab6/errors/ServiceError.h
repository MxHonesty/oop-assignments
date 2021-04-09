#pragma once
#include <exception>
#include <string>

class ServiceError : public std::exception {
protected:
	std::string msg;
public:
	/** Message constructor. */
	ServiceError(const std::string& error_message) : msg{ error_message } {};

	/** Constructor din pointer la sir de caractere. */
	ServiceError(const char* error_message) : msg{ error_message } {};

	const char* what() const noexcept override;
};