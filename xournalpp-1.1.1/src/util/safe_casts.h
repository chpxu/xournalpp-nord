/*
 * This file is provided by Fabian Keßler <fabian_kessler@gmx.de> under the
 * Boost Software License - Version 1.0 - August 17th, 2003 to the Xournal++
 * project.
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <cassert>
#include <cmath>
#include <type_traits>

template <typename To, typename From>
[[maybe_unused]] [[nodiscard]] constexpr auto is_safely_castable(From from) -> bool {
    using Big = decltype(from * std::declval<To>());
    auto to = static_cast<To>(from);
    return Big(to) == Big(from) && ((to < 0 && from < 0) || (to >= 0 && from >= 0));
}

template <typename To, typename From>
[[maybe_unused]] [[nodiscard]] constexpr auto strict_cast(From from) -> To {
    assert(is_safely_castable<To>(from));
    return static_cast<To>(from);
}

template <typename Integral>
[[maybe_unused]] [[nodiscard]] constexpr auto as_signed(Integral i)
        -> std::make_signed_t<std::remove_cv_t<std::remove_reference_t<Integral>>> {
    return static_cast<std::make_signed_t<std::remove_cv_t<std::remove_reference_t<Integral>>>>(i);
}

template <typename Integral>
[[maybe_unused]] [[nodiscard]] constexpr auto as_unsigned(Integral i)
        -> std::make_unsigned_t<std::remove_cv_t<std::remove_reference_t<Integral>>> {
    return static_cast<std::make_unsigned_t<std::remove_cv_t<std::remove_reference_t<Integral>>>>(i);
}

template <typename Integral>
[[maybe_unused]] [[nodiscard]] constexpr auto as_signed_strict(Integral i)
        -> std::make_signed_t<std::remove_cv_t<std::remove_reference_t<Integral>>> {
    auto rv = static_cast<std::make_signed_t<std::remove_cv_t<std::remove_reference_t<Integral>>>>(i);
    assert((i < 0 && rv < 0) || (i >= 0 && rv >= 0));
    return rv;
}

template <typename Integral>
[[maybe_unused]] [[nodiscard]] constexpr auto as_unsigned_strict(Integral i)
        -> std::make_unsigned_t<std::remove_cv_t<std::remove_reference_t<Integral>>> {
    assert(i > 0);
    return static_cast<std::make_unsigned_t<std::remove_cv_t<std::remove_reference_t<Integral>>>>(i);
}

template <typename Integral, typename Float>
inline auto round_cast(Float f) -> Integral {
    auto rv0 = std::lround(f);
    auto rv1 = static_cast<Integral>(rv0);
    assert(rv0 == rv1);
    return rv1;
}

template <typename Integral, typename Float>
inline auto ceil_cast(Float f) -> Integral {
    auto rv0 = std::ceil(f);
    auto rv1 = Integral(rv0);
    assert(rv0 == rv1);
    return rv1;
}

template <typename Integral, typename Float>
inline auto floor_cast(Float f) -> Integral {
    auto rv0 = std::floor(f);
    auto rv1 = Integral(rv0);
    assert(rv0 == rv1);
    return rv1;
}

// static_assert(is_safely_castable<int>(std::numeric_limits<size_t>::max()) == false);
// static_assert(is_safely_castable<int>(std::numeric_limits<int64_t>::min()) == false);
// static_assert(is_safely_castable<int>(std::numeric_limits<double>::min()) == false);
// static_assert(is_safely_castable<int>(std::numeric_limits<float>::min()) == false);
// static_assert(is_safely_castable<int>(size_t(std::numeric_limits<int>::max())));
// static_assert(is_safely_castable<int>(int64_t(std::numeric_limits<int>::min())));
// static_assert(is_safely_castable<int>(double(std::numeric_limits<int>::min())));
