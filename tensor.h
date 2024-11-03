#pragma once


#include "type_helper.h"
#include "operator.h"

#include <initializer_list>
#include <iostream>
#include <valarray>


namespace detail {
    template <numeric T, typename E>
    struct CastExpr;

    template <typename E, typename Op>
    struct UnaryExpr;

    template <typename L, typename R, typename Op>
    struct BinaryExpr;


    struct Expr {
        template <typename Self>
        [[nodiscard]] constexpr bool any(this const Self& self) {
            for (size_t i = 0; i < self.size(); ++i) {
                if (self[i]) {
                    return true;
                }
            }
            return false;
        }

        template <typename Self>
        [[nodiscard]] constexpr bool all(this const Self& self) {
            for (size_t i = 0; i < self.size(); ++i) {
                if (!self[i]) {
                    return false;
                }
            }
            return true;
        }

        template <numeric T, typename Self>
        [[nodiscard]] constexpr auto cast(this const Self& self) {
            return CastExpr<T, Self>{self};
        }

        template <typename Self>
        requires integral<typename Self::element_type>
        [[nodiscard]] constexpr auto operator~(this const Self& self) {
            return UnaryExpr{self, ComplOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto operator+(this const Self& self) {
            return self;
        }

        template <typename Self>
        [[nodiscard]] constexpr auto operator-(this const Self& self) {
            return UnaryExpr{self, NegOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto abs(this const Self& self) {
            return UnaryExpr{self, AbsOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto sqrt(this const Self& self) {
            return UnaryExpr{self, SqrtOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto exp(this const Self& self) {
            return UnaryExpr{self, ExpOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto log(this const Self& self) {
            return UnaryExpr{self, LogOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto sin(this const Self& self) {
            return UnaryExpr{self, SinOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto cos(this const Self& self) {
            return UnaryExpr{self, CosOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto tan(this const Self& self) {
            return UnaryExpr{self, TanOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto asin(this const Self& self) {
            return UnaryExpr{self, AsinOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto acos(this const Self& self) {
            return UnaryExpr{self, AcosOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto atan(this const Self& self) {
            return UnaryExpr{self, AtanOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto sinh(this const Self& self) {
            return UnaryExpr{self, SinhOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto cosh(this const Self& self) {
            return UnaryExpr{self, CoshOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto tanh(this const Self& self) {
            return UnaryExpr{self, TanhOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto asinh(this const Self& self) {
            return UnaryExpr{self, AsinhOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto acosh(this const Self& self) {
            return UnaryExpr{self, AcoshOp{}};
        }

        template <typename Self>
        [[nodiscard]] constexpr auto atanh(this const Self& self) {
            return UnaryExpr{self, AtanhOp{}};
        }

        template <typename Self, typename R>
        requires std::derived_from<R, Expr> || numeric<R>
        [[nodiscard]] constexpr auto pow(this const Self& self, const R& rhs) {
            return BinaryExpr{self, rhs, PowOp{}};
        }
    };

    [[nodiscard]] constexpr auto any(const std::derived_from<Expr> auto& expr) {
        return expr.any();
    }

    [[nodiscard]] constexpr auto all(const std::derived_from<Expr> auto& expr) {
        return expr.all();
    }

    [[nodiscard]] constexpr auto abs(const std::derived_from<Expr> auto& expr) {
        return expr.abs();
    }

    [[nodiscard]] constexpr auto sqrt(const std::derived_from<Expr> auto& expr) {
        return expr.sqrt();
    }

    [[nodiscard]] constexpr auto exp(const std::derived_from<Expr> auto& expr) {
        return expr.exp();
    }

    [[nodiscard]] constexpr auto log(const std::derived_from<Expr> auto& expr) {
        return expr.log();
    }

    [[nodiscard]] constexpr auto sin(const std::derived_from<Expr> auto& expr) {
        return expr.sin();
    }

    [[nodiscard]] constexpr auto cos(const std::derived_from<Expr> auto& expr) {
        return expr.cos();
    }

    [[nodiscard]] constexpr auto tan(const std::derived_from<Expr> auto& expr) {
        return expr.tan();
    }

    [[nodiscard]] constexpr auto asin(const std::derived_from<Expr> auto& expr) {
        return expr.asin();
    }

    [[nodiscard]] constexpr auto acos(const std::derived_from<Expr> auto& expr) {
        return expr.acos();
    }

    [[nodiscard]] constexpr auto atan(const std::derived_from<Expr> auto& expr) {
        return expr.atan();
    }

    [[nodiscard]] constexpr auto sinh(const std::derived_from<Expr> auto& expr) {
        return expr.sinh();
    }

    [[nodiscard]] constexpr auto cosh(const std::derived_from<Expr> auto& expr) {
        return expr.cosh();
    }

    [[nodiscard]] constexpr auto tanh(const std::derived_from<Expr> auto& expr) {
        return expr.tanh();
    }

    [[nodiscard]] constexpr auto asinh(const std::derived_from<Expr> auto& expr) {
        return expr.asinh();
    }

    [[nodiscard]] constexpr auto acosh(const std::derived_from<Expr> auto& expr) {
        return expr.acosh();
    }

    [[nodiscard]] constexpr auto atanh(const std::derived_from<Expr> auto& expr) {
        return expr.atanh();
    }


    template <typename L, typename R>
    concept bitwise_compatible = std::derived_from<L, Expr> && integral<typename L::element_type> &&
                                 (std::derived_from<R, Expr> && integral<typename R::element_type> || integral<R>) ||
                                 integral<L> && std::derived_from<R, Expr> && integral<typename R::element_type>;

    template <typename L, typename R>
    requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator&(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, AndOp{}};
    }

    template <typename L, typename R>
    requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator|(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, OrOp{}};
    }

    template <typename L, typename R>
    requires bitwise_compatible<L, R>
    [[nodiscard]] constexpr auto operator^(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, XorOp{}};
    }


    template <typename L, typename R>
    concept binary_compatible = std::derived_from<L, Expr> && (std::derived_from<R, Expr> || numeric<R>) ||
                                numeric<L> && std::derived_from<R, Expr>;

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator==(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, EqOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator!=(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, NeOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator<(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, LtOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator<=(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, LeOp{}};
    }

    template <typename L, typename R>
    requires std::derived_from<L, Expr> && (std::derived_from<R, Expr> || numeric<R>) ||
             numeric<L> && std::derived_from<R, Expr>
    [[nodiscard]] constexpr auto operator>(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, GtOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator>=(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, GeOp{}};
    }


    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator+(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, AddOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator-(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, SubOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator*(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, MulOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator/(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, DivOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto operator%(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, ModOp{}};
    }

    template <typename L, typename R>
    requires binary_compatible<L, R>
    [[nodiscard]] constexpr auto pow(const L& lhs, const R& rhs) {
        return BinaryExpr{lhs, rhs, PowOp{}};
    }


    template <numeric T, typename E>
    struct CastExpr : Expr {
        using element_type = T;


        explicit constexpr CastExpr(const E& expr) : expr(expr) {}

        [[nodiscard]] constexpr auto operator[](size_t i) const {
            return static_cast<T>(expr[i]);
        }

        [[nodiscard]] constexpr size_t size() const {
            return expr.size();
        }

    private:
        const E& expr;
    };

    template <typename E, typename Op>
    struct UnaryExpr : Expr {
        using element_type = typename operator_result<Op, E>::type;


        constexpr UnaryExpr(const E& expr, Op op) : expr(expr), op(op) {}

        [[nodiscard]] constexpr auto operator[](size_t i) const {
            return op(expr[i]);
        }

        [[nodiscard]] constexpr size_t size() const {
            return expr.size();
        }

    private:
        const E& expr;
        [[no_unique_address]] Op op;
    };

    template <typename L, typename R, typename Op>
    struct BinaryExpr : Expr {
        using element_type = typename operator_result<Op, L, R>::type;


        constexpr BinaryExpr(const L& lhs, const R& rhs, Op op) : lhs(lhs), rhs(rhs), op(op) {}

        [[nodiscard]] constexpr auto operator[](size_t i) const {
            if constexpr (numeric<L>) {
                return op(lhs, rhs[i]);
            } else {
                if constexpr (numeric<R>) {
                    return op(lhs[i], rhs);
                } else {
                    return op(lhs[i], rhs[i]);
                }
            }
        }

        [[nodiscard]] constexpr size_t size() const {
            if constexpr (numeric<L>) {
                return rhs.size();
            } else {
                return lhs.size();
            }
        }

    private:
        template <typename T>
        using node_type = std::conditional_t<numeric<T>, const T, const T&>;

        node_type<L> lhs;
        node_type<R> rhs;
        [[no_unique_address]] Op op;
    };
} // namespace detail


template <detail::numeric T>
struct Tensor : detail::Expr {
    using element_type = T;


    Tensor(T value, size_t count) : elems(value, count) {}

    Tensor(T* buffer, size_t count) : elems(buffer, count) {}

    template <size_t N>
    explicit Tensor(const T (& arr)[N]) : elems(arr, N) {}

    Tensor(std::initializer_list<T> il) : elems(il) {}

    Tensor(const std::derived_from<Expr> auto& expr) : elems(expr.size()) {
        for (size_t i = 0; i < size(); ++i) {
            elems[i] = expr[i];
        }
    }

    Tensor& operator=(T value) {
        elems = value;
        return *this;
    }

    Tensor& operator=(std::initializer_list<T> il) {
        elems = il;
        return *this;
    }

    template <typename Self>
    [[nodiscard]] T operator[](this Self&& self, size_t i) {
        return std::forward<Self>(self).elems[i];
    }

    [[nodiscard]] size_t size() const {
        return elems.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const Tensor& t) {
        os << "Tensor(";
        if (t.size() > 0) {
            os << "[" << t[0];
            if (t.size() <= 6) {
                for (size_t i = 1; i < t.size(); i++) {
                    os << ", " << t[i];
                }
            } else {
                for (size_t i = 0; i < 3; i++) {
                    os << ", " << t[i];
                }
                os << ", ...";
                for (size_t i = t.size() - 3; i < t.size(); i++) {
                    os << ", " << t[i];
                }
            }
            os << "]";
        }
        os << ")";
        return os;
    }

private:
    std::valarray<T> elems;
};


template <std::derived_from<detail::Expr> E>
Tensor(E) -> Tensor<typename E::element_type>;

