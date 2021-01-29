/*
 * Copyright (C) 2019, 2020 "IoT.bzh"
 * Author "Arthur Guyader" <arthur.guyader@iot.bzh>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "converter.hpp"
#include <climits>

/**
 * @brief	This is to use when you have a big endian CAN frame layout.
 * 		It converts the bit position so it matches with little endiant CAN frame layout.
 *
 * @param msg_length 	Message length in bytes.
 * @param bit_position 	Original bit position.
 * @param bit_size	Size of the data.
 * @return uint32_t 	New bit position.
 */
uint32_t converter_t::bit_position_swap(unsigned int msg_length, unsigned int bit_position, unsigned int bit_size)
{
	return ((bit_position / 8) * 8) + (7 - bit_position % 8);
}

/**
 * @brief	This allow to get the correct bit_position using the weird Continental.
 *		bit numbering method where the Frame is read using little endianness
 *		and bit count using a big endianness
 *
 * @param msg_length	Message length in bytes.
 * @param bit_position	Original bit position.
 * @param bit_size	Size of the data.
 * @return uint32_t	New bit position.
 */
uint32_t converter_t::continental_bit_position_mess(unsigned int msg_length, unsigned int bit_position, unsigned int bit_size)
{
	return bit_position + CHAR_BIT - 2 * (bit_position % CHAR_BIT) - bit_size;
}
