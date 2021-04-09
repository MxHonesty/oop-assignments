#pragma once
#include <exception>
#include <string>

class FileError : public std::exception {
protected:
	std::string msg;
public:
	/** Message constructor. */
	FileError(const std::string& error_message) : msg{ error_message } {};

	/** Constructor din pointer la sir de caractere. */
	FileError(const char* error_message) : msg{ error_message } {};

	const char* what() const noexcept override;
};
