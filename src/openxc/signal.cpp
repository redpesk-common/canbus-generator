#include <iostream>
#include "signal.hpp"

namespace openxc
{
	std::string signal::id() const
	{
		return id_;
	}

	void signal::id(const std::string& id)
	{
		id_ = id;
	}

	void id(const std::string& id);

	std::string signal::name() const
	{
		return name_;
	}

	std::uint32_t signal::bit_position() const
	{
		return bit_position_;
	}

	bool signal::bit_position_edited() const
	{
		return bit_position_edited_;
	}

	std::uint32_t signal::bit_size() const
	{
		return bit_size_;
	}

	float signal::factor() const
	{
		return factor_;
	}

	float signal::offset() const
	{
		return offset_;
	}

	float signal::min_value() const
	{
		return min_value_;
	}

	float signal::max_value() const
	{
		return max_value_;
	}

	float signal::value_to_match() const
	{
		return value_to_match_;
	}

	std::string signal::decoder() const
	{
		return decoder_;
	}

	bool signal::ignore() const
	{
		return ignore_;
	}

	bool signal::enabled() const
	{
		return enabled_;
	}

	const std::map<std::string, std::vector<std::uint32_t>>& signal::states() const
	{
		return states_;
	}

	float signal::max_frequency() const
	{
		return max_frequency_;
	}

	bool signal::send_same() const
	{
		return send_same_;
	}

	bool signal::force_send_changed() const
	{
		return force_send_changed_;
	}

	bool signal::writable() const
	{
		return writable_;
	}

	std::string signal::encoder() const
	{
		return encoder_;
	}

	std::pair<bool,int> signal::multiplex() const{
		return multiplex_;
	}

	sign_t signal::sign() const
	{
		return signed_;
	}

	std::int32_t signal::bit_sign_position() const
	{
		return bit_sign_position_;
	}

	std::string signal::unit() const
	{
		return unit_;
	}

	byte_order_t signal::byte_order() const
	{
		return byte_order_;
	}

	void signal::set_bit_position(std::uint32_t new_bit_position)
	{
		bit_position_ = new_bit_position;
		bit_position_edited_ = true;
	}

	void signal::from_json(const nlohmann::json& j)
	{
		bool has_name = j.count("name") > 0;
		bool has_generic_name = j.count("generic_name") > 0;
		if (has_name)
			name_ = j["name"].get<std::string>();
		else if (has_generic_name)
		{
			name_ = j["generic_name"].get<std::string>();
			std::cout << "WARNING: signal name is missing, using generic_name " << name_ << "\n";
		}
		else
		{
			std::cout <<"ERROR: signal name is missing\n";
			name_ = "?";
		}
		bit_position_ = j.count("bit_position") ? j["bit_position"].get<std::uint32_t>() : 0;
		bit_position_edited_ = false;
		bit_size_ = j.count("bit_size") ? j["bit_size"].get<std::uint32_t>() : 0;
		factor_ = j.count("factor") ? j["factor"].get<float>() : 1.0f;
		offset_ = j.count("offset") ? j["offset"].get<float>() : 0.0f;
		value_to_match_ = j.count("value_to_match") ? j["value_to_match"].get<float>() : std::nanf("");
		min_value_ = j.count("min_value") ? j["min_value"].get<float>() : std::nanf("");
		max_value_ = j.count("max_value") ? j["max_value"].get<float>() : std::nanf("");
		if(!isnanf(value_to_match_) && ( !isnanf(min_value_) || !isnanf(max_value_)))
		{
			std::cout <<"WARNING: value_to_match and min/max_value cannot be set together. min/max_value(s) have been overridden \n";
		}
		decoder_ = j.count("decoder") ? j["decoder"].get<std::string>() : "";
		ignore_ = j.count("ignore") ? j["ignore"].get<bool>() : false;
		enabled_ = j.count("enabled") ? j["enabled"].get<bool>() : true;
		max_frequency_ = j.count("max_frequency") ? j["max_frequency"].get<float>() : 0.0f;
		send_same_ = j.count("send_same") ? j["send_same"].get<bool>() : true;
		force_send_changed_ = j.count("force_send_changed") ? j["force_send_changed"].get<bool>() : false;
		writable_ = j.count("writable") ? j["writable"].get<bool>() : false;
		encoder_ = j.count("encoder") ? j["encoder"].get<std::string>() : "";
		if(j.count("multiplex"))
		{
			std::string mult = j["multiplex"].get<std::string>();
			bool first = false;
			int second = 0 ;
			if(mult.compare("Multiplexor") == 0){
				first = true;
			}
			else if (mult.compare("") != 0)
			{
				second = std::stoi(mult);
			}
			multiplex_ = std::make_pair(first,second);
		}
		else
		{
			multiplex_ =  std::make_pair(false,0);
		}
		signed_ = j.count("sign") ? static_cast<sign_t>(j["sign"].get<std::uint32_t>()) : sign_t::UNSIGNED;
		bit_sign_position_ = j.count("bit_sign_position") ? j["bit_sign_position"].get<std::int32_t>() : -1;
		unit_ = j.count("unit") ? j["unit"].get<std::string>() : "";
		byte_order_ = !j.count("byte_order") ? Unset_Endian
				: j["byte_order"].get<std::string>() == "big_endian" ? Big_Endian
				: j["byte_order"].get<std::string>() == "little_endian" ? Little_Endian
				: Unset_Endian; // THROW SOME ERROR?

		if (j.count("states"))
		{
			std::map<std::string, nlohmann::json> items = j["states"];
			for(const auto& i : items)
			{
				states_[i.first] = i.second.get<std::vector<std::uint32_t>>();
			}
		}
	}

	nlohmann::json signal::to_json() const
	{
		nlohmann::json j;
		j["name"] = name_;
		j["bit_position"] = bit_position_;
		j["bit_size"] = bit_size_;
		j["factor"] = factor_;
		j["offset"] = offset_;
		j["value_to_match"] = min_value_;
		j["value_to_match"] = max_value_;
		j["value_to_match"] = value_to_match_;
		j["decoder"] = decoder_;
		j["ignore"] = ignore_;
		j["enabled"] = enabled_;
		j["states"] = states_;
		j["max_frequency"] = max_frequency_;
		j["send_same"] = send_same_;
		j["force_send_changed"] = force_send_changed_;
		j["writable"] = writable_;
		j["encoder"] = encoder_;

		std::string multi = "";

		if(multiplex_.first)
		{
			multi = "Multiplexor";
		}
		else if(multiplex_.second != 0)
		{
			multi = std::to_string(multiplex_.second);
		}
		else
		{
			multi = "";
		}

		j["multiplex"] = multi;
		j["signed"] = signed_;
		j["bit_sign_position"] = bit_sign_position_;
		j["unit"] = unit_;
		if (byte_order_ != Unset_Endian)
			j["byte_order"] = byte_order_ == Big_Endian ? "big_endian" : "little_endian";
		return j;
	}

	void to_json(nlohmann::json& j, const signal& p)
	{
		j = p.to_json();
	}

	void from_json(const nlohmann::json& j, signal& p)
	{
		p.from_json(j);
	}
}
