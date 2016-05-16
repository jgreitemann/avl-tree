//    avl-tree
//    Copyright (C) 2015 -- 2016  Jonas Greitemann
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

#pragma once
#include <type_traits>

namespace AVL {
    template <typename...> using void_t = void;


    template <typename T, typename = void>
    struct defines_ordering : std::false_type {};

    template <typename T>
    struct defines_ordering<T, void_t<decltype(T() < T())>>
            : std::true_type {};


    template <typename T, typename = void>
    struct is_comparable : std::false_type {};

    template <typename T>
    struct is_comparable<T, void_t<decltype(T() == T())>>
            : std::true_type {};
}
