#pragma once
#include <exception>
#include <string>

class RepoError : public std::exception {
protected:
	std::string msg;
public:
	/** Message constructor. */
	RepoError(const std::string& error_message) : msg{ error_message } {};

	/** Constructor din pointer la sir de caractere. */
	RepoError(const char* error_message) : msg{ error_message } {};

	const char* what() const noexcept override;
};