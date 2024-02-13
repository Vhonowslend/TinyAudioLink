# TinyAudioLink - Seamlessly transfer Audio between USB capable devices
# Copyright (C) 2019 Michael Fabian 'Xaymar' Dirks
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

set(_cpu="cortex-m7")
set(_fpu="fpv5-d16")
set(_triplet="thumbv7em-none-unknown-eabihf")

set(CMAKE_SYSTEM_PROCESSOR "ARMv7E-M")
set(CMAKE_C_COMPILER_TARGET "${_triplet}")
set(CMAKE_C_FLAGS "-Qn -mcpu=${_cpu} -mfpu=${_fpu} -mfloat-abi=hard")
set(CMAKE_CXX_COMPILER_TARGET "${_triplet}")
set(CMAKE_CXX_FLAGS "-Qn -mcpu=${_cpu} -mfpu=${_fpu} -mfloat-abi=hard")
