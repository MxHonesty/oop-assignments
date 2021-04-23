#include "TipDTO.h"

const int TipDTO::get_count() const noexcept {
	return this->count;
}

const std::string& TipDTO::get_tip() const noexcept {
	return tip;
}

void TipDTO::increment_count() noexcept {
	count++;
}

void TipDTO::set_tip(const std::string& new_tip) {
	tip = new_tip;
	count = 1;
}

void TipDTO::clear() {
	tip = "";
	count = 0;
}
