#pragma once

#include <string>
#include <vector>
#include <json.hpp>
#include <linux/can.h>

#include "signal.hpp"

namespace openxc
{
	class can_message
	{
	private:
		std::string						id_;
		std::string						bus_;
		bool							bit_numbering_inverted_;
		std::vector<signal>				signals_;
		std::string						name_;
		std::vector<std::string>		handlers_;
		bool							enabled_;
		float							max_frequency_;
		float							max_signal_frequency_;
		bool							force_send_changed_;
		bool							force_send_changed_signals_;
		bool							is_fd_;
		bool							is_j1939_;
		bool							is_isotp_;
		bool							byte_frame_is_big_endian_;
		bool							bit_position_reversed_;
		bool							continental_bit_position_;
		uint32_t						length_;
		float							min_value;
		float							max_value;

	public:
		std::string id() const;
		void id(const std::string& id);
		void is_fd(const bool is_fd);
		bool is_fd() const;
		void is_j1939(const bool is_j1939);
		bool is_j1939() const;
		void is_isotp(const bool is_isotp);
		bool is_isotp() const;
		bool byte_frame_is_big_endian() const;
		bool bit_position_reversed() const;
		bool continental_bit_position() const;
		std::string	bus() const;
		bool bit_numbering_inverted() const;
		const std::vector<signal>& signals() const;
		std::string name() const;
		std::vector<std::string> handlers() const;
		bool enabled() const;
		float max_frequency() const;
		float max_signal_frequency() const;
		bool force_send_changed() const;
		bool force_send_changed_signals() const;
		uint32_t length() const;

		void from_json(const nlohmann::json& j);
		nlohmann::json to_json() const;

		std::uint32_t get_signals_count() const;
	};

	void to_json(nlohmann::json& j, const can_message& p);
	void from_json(const nlohmann::json& j, can_message& p);
	void from_json(const nlohmann::json& j, can_message& p, const std::string& id);
}
