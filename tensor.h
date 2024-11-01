#pragma once


#include "type_helper.h"
#include "operator.h"

#include <initializer_list>
#include <iostream>
#include <valarray>


namespace detail {
    template <typename Derived>
    struct Expr;


    template <numeric T, typename E>
    struct CastExpr : Expr<CastExpr<T, E>> {
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


    template <typename Op, typename E>
    struct UnaryExpr : Expr<UnaryExpr<Op, E>> {
        using element_type = typename operator_result<Op, E>::type;


        explicit constexpr UnaryExpr(const E& expr) : expr(expr) {}

        [[nodiscard]] constexpr auto operator[](size_t i) const {
            return Op{}(expr[i]);
        }

        [[nodiscard]] constexpr size_t size() const {
            return expr.size();
        }

    private:
        const E& expr;
    };

    template <typename Op, typename L, typename R>
    struct BinaryExpr : Expr<BinaryExpr<Op, L, R>> {
        using element_type = typename operator_result<Op, L, R>::type;


        constexpr BinaryExpr(const L& lhs, const R& rhs) : lhs(lhs), rhs(rhs) {}

        [[nodiscard]] constexpr auto operator[](size_t i) const {
            if constexpr (numeric<L>) {
                return Op{}(lhs, rhs[i]);
            } else {
                if constexpr (numeric<R>) {
                    return Op{}(lhs[i], rhs);
                } else {
                    return Op{}(lhs[i], rhs[i]);
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
    };

    template <typename E>
    using NegExpr = UnaryExpr<NegOp, E>;

    template <typename E>
    using AbsExpr = UnaryExpr<AbsOp, E>;

    template <typename E>
    using SqrtExpr = UnaryExpr<SqrtOp, E>;

    template <typename E>
    using ExpExpr = UnaryExpr<ExpOp, E>;

    template <typename E>
    using LogExpr = UnaryExpr<LogOp, E>;

    template <typename E>
    using Log10Expr = UnaryExpr<Log10Op, E>;

    template <typename E>
    using SinExpr = UnaryExpr<SinOp, E>;

    template <typename E>
    using CosExpr = UnaryExpr<CosOp, E>;

    template <typename E>
    using TanExpr = UnaryExpr<TanOp, E>;

    template <typename E>
    using AsinExpr = UnaryExpr<AsinOp, E>;

    template <typename E>
    using AcosExpr = UnaryExpr<AcosOp, E>;

    template <typename E>
    using AtanExpr = UnaryExpr<AtanOp, E>;

    template <typename E>
    using SinhExpr = UnaryExpr<SinhOp, E>;

    template <typename E>
    using CoshExpr = UnaryExpr<CoshOp, E>;

    template <typename E>
    using TanhExpr = UnaryExpr<TanhOp, E>;

    template <typename E>
    using AsinhExpr = UnaryExpr<AsinhOp, E>;

    template <typename E>
    using AcoshExpr = UnaryExpr<AcoshOp, E>;

    template <typename E>
    using AtanhExpr = UnaryExpr<AtanhOp, E>;


    template <typename L, typename R>
    using AddExpr = BinaryExpr<AddOp, L, R>;

    template <typename L, typename R>
    using SubExpr = BinaryExpr<SubOp, L, R>;

    template <typename L, typename R>
    using MulExpr = BinaryExpr<MulOp, L, R>;

    template <typename L, typename R>
    using DivExpr = BinaryExpr<DivOp, L, R>;

    template <typename L, typename R>
    using ModExpr = BinaryExpr<ModOp, L, R>;

    template <typename B, typename E>
    using PowExpr = BinaryExpr<PowOp, B, E>;


    template <typename Derived>
    struct Expr {
        template <typename>
        friend struct Expr;

    private:
        [[nodiscard]] const Derived& derived() const {
            return static_cast<const Derived&>(*this);
        };

    public:
        [[nodiscard]] constexpr auto operator[](size_t i) const {
            return derived()[i];
        }

        [[nodiscard]] constexpr size_t size() const {
            return derived().size();
        }

        template <numeric T>
        [[nodiscard]] auto cast() const {
            return CastExpr<T, Derived>{derived()};
        }

        template <numeric T>
        [[nodiscard]] explicit operator T() const {
            return cast<T>();
        }

        [[nodiscard]] auto operator-() const {
            return NegExpr{derived()};
        }

        [[nodiscard]] auto abs() const {
            return AbsExpr{derived()};
        }

        [[nodiscard]] auto sqrt() const {
            return SqrtExpr{derived()};
        }

        [[nodiscard]] auto exp() const {
            return ExpExpr{derived()};
        }

        [[nodiscard]] auto log() const {
            return LogExpr{derived()};
        }

        [[nodiscard]] auto log10() const {
            return Log10Expr{derived()};
        }

        [[nodiscard]] auto sin() const {
            return SinExpr{derived()};
        }

        [[nodiscard]] auto cos() const {
            return CosExpr{derived()};
        }

        [[nodiscard]] auto tan() const {
            return TanExpr{derived()};
        }

        [[nodiscard]] auto asin() const {
            return AsinExpr{derived()};
        }

        [[nodiscard]] auto acos() const {
            return AcosExpr{derived()};
        }

        [[nodiscard]] auto atan() const {
            return AtanExpr{derived()};
        }

        [[nodiscard]] auto sinh() const {
            return SinhExpr{derived()};
        }

        [[nodiscard]] auto cosh() const {
            return CoshExpr{derived()};
        }

        [[nodiscard]] auto tanh() const {
            return TanhExpr{derived()};
        }

        [[nodiscard]] auto asinh() const {
            return AsinhExpr{derived()};
        }

        [[nodiscard]] auto acosh() const {
            return AcoshExpr{derived()};
        }

        [[nodiscard]] auto atanh() const {
            return AtanhExpr{derived()};
        }


        [[nodiscard]] friend auto abs(const Expr& self) {
            return self.abs();
        }

        [[nodiscard]] friend auto sqrt(const Expr& self) {
            return self.sqrt();
        }

        [[nodiscard]] friend auto exp(const Expr& self) {
            return self.exp();
        }

        [[nodiscard]] friend auto log(const Expr& self) {
            return self.log();
        }

        [[nodiscard]] friend auto log10(const Expr& self) {
            return self.log10();
        }

        [[nodiscard]] friend auto sin(const Expr& self) {
            return self.sin();
        }

        [[nodiscard]] friend auto cos(const Expr& self) {
            return self.cos();
        }

        [[nodiscard]] friend auto tan(const Expr& self) {
            return self.tan();
        }

        [[nodiscard]] friend auto asin(const Expr& self) {
            return self.asin();
        }

        [[nodiscard]] friend auto acos(const Expr& self) {
            return self.acos();
        }

        [[nodiscard]] friend auto atan(const Expr& self) {
            return self.atan();
        }

        [[nodiscard]] friend auto sinh(const Expr& self) {
            return self.sinh();
        }

        [[nodiscard]] friend auto cosh(const Expr& self) {
            return self.cosh();
        }

        [[nodiscard]] friend auto tanh(const Expr& self) {
            return self.tanh();
        }

        [[nodiscard]] friend auto asinh(const Expr& self) {
            return self.asinh();
        }

        [[nodiscard]] friend auto acosh(const Expr& self) {
            return self.acosh();
        }

        [[nodiscard]] friend auto atanh(const Expr& self) {
            return self.atanh();
        }


        template <typename R>
        [[nodiscard]] auto operator+(const Expr<R>& rhs) const {
            return AddExpr{derived(), rhs.derived()};
        }

        template <numeric T>
        [[nodiscard]] auto operator+(T rhs) const {
            return AddExpr{derived(), rhs};
        }

        template <numeric T>
        [[nodiscard]] friend auto operator+(T lhs, const Expr& rhs) {
            return AddExpr{lhs, rhs.derived()};
        }


        template <typename R>
        [[nodiscard]] auto operator-(const Expr<R>& rhs) const {
            return SubExpr{derived(), rhs.derived()};
        }

        template <numeric T>
        [[nodiscard]] auto operator-(T rhs) const {
            return SubExpr{derived(), rhs};
        }

        template <numeric T>
        [[nodiscard]] friend auto operator-(T lhs, const Expr& rhs) {
            return SubExpr{lhs, rhs.derived()};
        }


        template <typename R>
        [[nodiscard]] auto operator*(const Expr<R>& rhs) const {
            return MulExpr{derived(), rhs.derived()};
        }

        template <numeric T>
        [[nodiscard]] auto operator*(T rhs) const {
            return MulExpr{derived(), rhs};
        }

        template <numeric T>
        [[nodiscard]] friend auto operator*(T lhs, const Expr& rhs) {
            return MulExpr{lhs, rhs.derived()};
        }


        template <typename R>
        [[nodiscard]] auto operator/(const Expr<R>& rhs) const {
            return DivExpr{derived(), rhs.derived()};
        }

        template <numeric T>
        [[nodiscard]] auto operator/(T rhs) const {
            return DivExpr{derived(), rhs};
        }

        template <numeric T>
        [[nodiscard]] friend auto operator/(T lhs, const Expr& rhs) {
            return DivExpr{lhs, rhs.derived()};
        }


        template <typename R>
        [[nodiscard]] auto operator%(const Expr<R>& rhs) const {
            return ModExpr{derived(), rhs.derived()};
        }

        template <numeric T>
        [[nodiscard]] auto operator%(T rhs) const {
            return ModExpr{derived(), rhs};
        }

        template <numeric T>
        [[nodiscard]] friend auto operator%(T lhs, const Expr& rhs) {
            return ModExpr{lhs, rhs.derived()};
        }


        template <typename R>
        [[nodiscard]] auto pow(const Expr<R>& rhs) const {
            return PowExpr{derived(), rhs.derived()};
        }

        template <numeric T>
        [[nodiscard]] auto pow(T rhs) const {
            return PowExpr{derived(), rhs};
        }

        template <numeric T>
        [[nodiscard]] friend auto pow(T lhs, const Expr& rhs) {
            return PowExpr{lhs, rhs.derived()};
        }

        template <typename R>
        [[nodiscard]] friend auto pow(const Expr& lhs, R rhs) {
            return lhs.pow(rhs);
        }
    };
} // namespace detail


template <detail::numeric T>
struct Tensor : detail::Expr<Tensor<T>> {
    using element_type = T;


    Tensor(T value, size_t count) : elems(value, count) {}

    Tensor(T* buffer, size_t count) : elems(buffer, count) {}

    template <size_t N>
    explicit Tensor(const T (& arr)[N]) : elems(arr, N) {}

    Tensor(std::initializer_list<T> il) : elems(il) {}

    template <typename Derived>
    Tensor(const detail::Expr<Derived>& expr) : elems(expr.size()) {
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

    [[nodiscard]] T operator[](size_t i) const {
        return elems[i];
    }

    [[nodiscard]] T& operator[](size_t i) {
        return elems[i];
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


template <typename Derived>
Tensor(detail::Expr<Derived>) -> Tensor<typename Derived::element_type>;
