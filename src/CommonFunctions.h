/*
This file is part of DSpellCheck Plug-in for Notepad++
Copyright (C)2013 Sergey Semushin <Predelnik@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#pragma once
#include "Plugin.h"

struct NppData;

std::wstring to_wstring (std::string_view source);
std::string to_string (std::wstring_view source);
std::string to_utf8_string (std::string_view source);
std::string to_utf8_string (std::wstring_view source);
std::wstring utf8_to_wstring (const char *source);
std::string utf8_to_string (const char *source);

std::pair<std::wstring_view, bool> apply_alias(std::wstring_view str);

std::wstring parse_string(const wchar_t* source);

LRESULT send_msg_to_npp(const NppData *npp_data_arg, UINT msg,
                     WPARAM w_param = 0, LPARAM l_param = 0);

bool sort_compare(wchar_t *a, wchar_t *b);

bool check_for_directory_existence(std::wstring path, bool silent = true,
                                HWND npp_window = nullptr);

// trim from start (in place)
inline void ltrim(std::wstring &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](wchar_t ch) {
        return !iswspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::wstring &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](wchar_t ch) {
        return !iswspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::wstring &s) {
    ltrim(s);
    rtrim(s);
}

template <typename T>
std::weak_ptr<T> weaken (std::shared_ptr<T> ptr) { return ptr; }

template <typename... ArgTypes>
std::wstring wstring_printf (const wchar_t *format, ArgTypes &&... args) {
    auto size = _snwprintf (nullptr, 0, format, args...);
    std::vector<wchar_t> buf (size + 1);
    _snwprintf (buf.data (), size + 1, format, args...);
    return buf.data ();
}

void replace_all(std::string& str, std::string_view from, std::string_view to);
std::wstring read_ini_value(const wchar_t* app_name, const wchar_t* key_name, const wchar_t* default_value,
                          const wchar_t* file_name);

class MoveOnlyFlag {
    using Self = MoveOnlyFlag;
public:
    MoveOnlyFlag () {}
    static Self create_valid () { Self out; out.m_valid = true; return out; }
    void make_valid () { m_valid = true; }
    MoveOnlyFlag (Self &&other) noexcept : m_valid (other.m_valid) { other.m_valid = false;}
    Self &operator= (Self &&other) noexcept { m_valid = other.m_valid; other.m_valid = false; return *this; }
    MoveOnlyFlag (const Self &) = delete;
    Self &operator= (const Self &other) = delete;
    bool is_valid () const { return m_valid; }
private:
    bool m_valid = false;
};
