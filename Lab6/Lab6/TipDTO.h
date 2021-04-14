#pragma once

#include <string>


class TipDTO {
private:
	std::string tip;
	int count;
public:
	/** Constructor default */
	TipDTO() {
		this->count = 0;
		this->tip = "";
	}

	/** Constructor cu un tip gasit. */
	TipDTO(const std::string& tip_gasit) {
		count = 1;
		tip = tip_gasit;
	}

	/** Primeste numarul de aparitii */
	const int get_count() const noexcept;

	const std::string& get_tip() const noexcept;

	/** Incrementeaza countul curent */
	void increment_count() noexcept;

	/** Seteaza tipul si seteaza count la 1 */
	void set_tip(const std::string& new_tip);

	/** Curata starea */
	void clear();
};

