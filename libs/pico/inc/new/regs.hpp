#pragma once

#include <algorithm>

template<typename T> struct dependent_false : std::false_type { };

class read_only { };
class write_only { };
class read_write : public read_only, public write_only { };

template <typename reg_type, std::size_t bits = 32, typename Register_Ty = read_write>
class Register {
	static_assert(std::is_integral<reg_type>::value, "Reg type must be integral.");
	static_assert(bits <= sizeof(reg_type) * 8, "Registry cannot contain more bits than reg_type.");

public:
	void operator=(reg_type bit_mask)
	{
		if constexpr (!std::is_base_of<write_only, Register_Ty>()) {
			static_assert(dependent_false<Register_Ty>(), "Writing to read-only object");
		}

		data = bit_mask;
	}
	operator reg_type() const
	{
		if constexpr (!std::is_base_of<read_only, Register_Ty>()) {
			static_assert(dependent_false<Register_Ty>(), "Reading from write-only object");
		}

		return data;
	}
	void operator|=(reg_type bit_mask)
	{
		if constexpr (!std::is_base_of<read_write, Register_Ty>()) {
			static_assert(dependent_false<Register_Ty>(), "Object must be read-write");
		}

		data |= bit_mask;
	}
	void operator&=(reg_type bit_mask)
	{
		if constexpr (!std::is_base_of<read_write, Register_Ty>()) {
			static_assert(dependent_false<Register_Ty>(), "Object must be read-write");
		}

		data &= bit_mask;
	}

	inline bool GetBit(const uint32_t bit) const
	{
		if constexpr (!std::is_base_of<read_only, Register_Ty>()) {
			static_assert(dependent_false<Register_Ty>(), "Reading from write-only object");
		}

		return data & 1 << bit;
	}

	inline void SetBit(const uint32_t bit, uint32_t value)
	{
		if constexpr (!std::is_base_of<write_only, Register_Ty>()) {
			static_assert(dependent_false<Register_Ty>(), "Writing to read-only object");
		}

		if constexpr (std::is_base_of<read_only, Register_Ty>()) {
			data ^= (-value ^ data) & (1 << bit);
		}
		else if constexpr (std::is_base_of<write_only, Register_Ty>()) {
			data = value << bit;
		}
	}
protected:
	volatile reg_type data : bits;
};