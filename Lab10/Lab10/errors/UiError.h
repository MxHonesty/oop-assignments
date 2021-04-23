#pragma once
#include <exception>
#include <string>

class UiError : public std::exception {
protected:
	std::string msg;
public:
	/** Message constructor. */
	UiError(const std::string& error_message) : msg{ error_message } {};

	/** Constructor din pointer la sir de caractere. */
	UiError(const char* error_message) : msg{ error_message } {};

	const char* what() const noexcept override;
};