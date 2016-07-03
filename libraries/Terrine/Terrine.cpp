/* -*- coding: utf-8 -*-

Terrine: Application boilerplate for convenient MCU development

Copyright (C) 2015-2016  Andreas Motl <andreas.motl@elmyra.de>
Copyright (C) 2015-2016  Richard Pobering <einsiedlerkrebs@ginnungagap.org>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see:
<http://www.gnu.org/licenses/gpl-3.0.txt>,
or write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

*/

#include <Terrine.h>

#ifdef ARDUINO
    #include <Arduino.h>
    #include <MemoryFree.h>
#endif

void Terrine::log(const char *message, bool newline) {
    #if defined SIMULAVR
        if (newline) {
            _d(message);
        } else {
            _l(message);
        }
    #else
        if (newline) {
            Serial.println(message);
        } else {
            Serial.print(message);
        }
        #ifdef ARDUINO
            delay(TERRINE_SERIAL_DELAY);
        #endif
    #endif
}

void Terrine::log(int value) {
    #ifdef SIMULAVR
        _d(value);
    #else
        #ifdef ARDUINO
            Serial.println(value);
            delay(TERRINE_SERIAL_DELAY);
        #else
            Serial.println(std::to_string(value).c_str());
        #endif
    #endif
}

int Terrine::memfree() {
    #ifdef ARDUINO
        return freeMemory();
    #else
        return -1;
    #endif
}
void Terrine::logmem() {
    #ifdef SIMULAVR
        _d("free: n/a");
    #else
        Serial.print("free: ");
        #ifdef ARDUINO
            Serial.println(memfree());
            delay(TERRINE_SERIAL_DELAY);
        #else
            Serial.println(std::to_string(memfree()).c_str());
        #endif
    #endif
}

/*
template<typename T>
void dump_vector(std::string item_prefix, std::vector<T> vec) {

    typename std::vector<T>::const_iterator it;
    int i = 1;
    for (it = vec.begin(); it != vec.end(); it++) {

        // FIXME: How large should this buffer actually be made?
        char buffer[100];
        sprintf(buffer, "%s%d: ", item_prefix.c_str(), i);
        _l(buffer);

        T value = *it;
        _d(value);

        i++;
    }

}
*/
