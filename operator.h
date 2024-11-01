#pragma once


#include <cmath>

#include "type_helper.h"


namespace  detail {
    /* Unary operators */
    struct NegOp {
        template <numeric T>
        constexpr T operator()(T x) const {
            return -x;
        }
    };

    struct AbsOp {
        template <numeric T>
        constexpr T operator()(T x) const {
            return std::abs(x);
        }
    };

    struct SqrtOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::sqrt(static_cast<to_floating<T>>(x));
        }
    };

    struct ExpOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::exp(static_cast<to_floating<T>>(x));
        }
    };

    struct LogOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::log(static_cast<to_floating<T>>(x));
        }
    };

    struct Log10Op {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::log10(static_cast<to_floating<T>>(x));
        }
    };

    struct SinOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::sin(static_cast<to_floating<T>>(x));
        }
    };

    struct CosOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::cos(static_cast<to_floating<T>>(x));
        }
    };

    struct TanOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::tan(static_cast<to_floating<T>>(x));
        }
    };

    struct AsinOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::asin(static_cast<to_floating<T>>(x));
        }
    };

    struct AcosOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::acos(static_cast<to_floating<T>>(x));
        }
    };

    struct AtanOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::atan(static_cast<to_floating<T>>(x));
        }
    };

    struct SinhOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::sinh(static_cast<to_floating<T>>(x));
        }
    };

    struct CoshOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::cosh(static_cast<to_floating<T>>(x));
        }
    };

    struct TanhOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::tanh(static_cast<to_floating<T>>(x));
        }
    };

    struct AsinhOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::asinh(static_cast<to_floating<T>>(x));
        }
    };

    struct AcoshOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::acosh(static_cast<to_floating<T>>(x));
        }
    };

    struct AtanhOp {
        template <numeric T>
        constexpr to_floating<T> operator()(T x) const {
            return std::atanh(static_cast<to_floating<T>>(x));
        }
    };


    /* Binary operators */
    struct AddOp {
        template <numeric L, numeric R>
        constexpr common_type_t<L, R> operator()(L x, R y) const {
            return x + y;
        }
    };

    struct SubOp {
        template <numeric L, numeric R>
        constexpr common_type_t<L, R> operator()(L x, R y) const {
            return x - y;
        }
    };

    struct MulOp {
        template <numeric L, numeric R>
        constexpr common_type_t<L, R> operator()(L x, R y) const {
            return x * y;
        }
    };

    struct DivOp {
        template <numeric L, numeric R>
        constexpr common_type_t<L, R> operator()(L x, R y) const {
            return x / y;
        }
    };

    struct ModOp {
        template <numeric L, numeric R>
        constexpr common_type_t<L, R> operator()(L x, R y) const {
            return x % y;
        }
    };

    struct PowOp {
        template <typename B, typename E>
        requires floating<B> || floating<E>
        constexpr auto operator()(B base, E exp) const {
            if constexpr (std::integral<E>) {
                if (exp < 0) {
                    return fast_pow(1 / base, static_cast<uint64_t>(-exp));
                }
                return fast_pow(base, exp);
            } else {
                using T = std::common_type_t<B, E>;
                return std::pow(static_cast<T>(base), static_cast<T>(exp));
            }
        }

        template <integral B, unsigned_integral E>
        constexpr auto operator()(B base, E exp) const {
            using T = std::common_type_t<B, E>;
            return fast_pow(static_cast<T>(base), static_cast<T>(exp));
        }

    private:
        template <numeric T>
        T fast_pow(T base, auto exp) {
            T result = 1;
            while (exp != 0) {
                if (exp & 1) {
                    result *= base;
                }
                base *= base;
                exp >>= 1;
            }
            return result;
        }
    };
} // namespace detail