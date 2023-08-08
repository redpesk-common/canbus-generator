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

#include <iomanip>
#include <cstdint>

class converter_t
{
    public:
		static uint32_t bit_position_swap(unsigned int msg_length,
						  unsigned int bit_position,
						  unsigned int bit_size);
		static uint32_t continental_bit_position_mess(unsigned int msg_length,
							      unsigned int bit_position,
							      unsigned int bit_size);

};
