#pragma once

#include <string>
#include <map>
#include <vector>
#include <cstdint>
#include <json.hpp>

namespace openxc
{
	enum sign_t
	{
		UNSIGNED = 0,
		SIGN_BIT = 1,
		ONES_COMPLEMENT = 2,
		TWOS_COMPLEMENT = 3,
		SIGN_BIT_EXTERN = 4,
	};

	class signal
	{
	private:
		std::string											id_;
		std::string											generic_name_;
		std::uint32_t										bit_position_;
		std::uint32_t										bit_size_;
		float												factor_;
		float												offset_;
		std::string											decoder_;
		bool												ignore_;
		bool												enabled_;
		std::map<std::string, std::vector<std::uint32_t>>	states_;
		float												max_frequency_;
		bool												send_same_;
		bool												force_send_changed_;
		bool												writable_;
		std::string											encoder_;
		std::pair<bool,int>									multiplex_;
		bool												is_big_endian_;
		sign_t												signed_;
		std::int32_t										bit_sign_position_;
		std::string											unit_;

	public:
		std::string id() const;
		void id(const std::string& id);
		std::string generic_name() const;
		std::uint32_t bit_position() const;
		std::uint32_t bit_size() const;
		float factor() const;
		float offset() const;
		std::string decoder() const;
		bool ignore() const;
		bool enabled() const;
		const std::map<std::string, std::vector<std::uint32_t>>& states() const;
		float max_frequency() const;
		bool send_same() const;
		bool force_send_changed() const;
		bool writable() const;
		std::string encoder() const;
		std::pair<bool,int> multiplex() const;
		bool is_big_endian() const;
		sign_t sign() const;
		std::int32_t bit_sign_position() const;
		std::string unit() const;

		void from_json(const nlohmann::json& j);
		nlohmann::json to_json() const;
	};

	void to_json(nlohmann::json& j, const signal& p);
	void from_json(const nlohmann::json& j, signal& p);
}
