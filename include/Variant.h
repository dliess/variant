#ifndef DL_VARIANT_H
#define DL_VARIANT_H

#ifdef USE_MPARK_VARIANT
#include <mpark/variant.hpp>
#define VARIANT_NS mpark
#else
#include <variant>
#define VARIANT_NS std
#endif

namespace dl
{

template<typename... T>
using variant = VARIANT_NS::variant<T...>;

template <typename T, typename... Types>
inline T* get_if(dl::variant<Types...>* v) noexcept {
    return VARIANT_NS::get_if<T>(v);
}

template <typename T, typename... Types>
inline const T* get_if(const variant<Types...>* v) noexcept {
    return VARIANT_NS::get_if<T>(v);
}

template <typename T, typename... Types>
inline bool holds_alternative(const variant<Types...>& v) noexcept {
    return VARIANT_NS::holds_alternative<T>(v);
}

template <typename T, typename... Types>
inline T& get(variant<Types...>& v) {
    return VARIANT_NS::get<T>(v);
}

template <typename T, typename... Types>
inline const T& get(const variant<Types...>& v) {
    return VARIANT_NS::get<T>(v);
}

template <typename Visitor, typename... Variants>
inline decltype(auto) visit(Visitor&& vis, Variants&&... vars) {
    return VARIANT_NS::visit(std::forward<Visitor>(vis), std::forward<Variants>(vars)...);
}

template <size_t Index, typename Variant>
using variant_alternative_t = VARIANT_NS::variant_alternative_t<Index, Variant>;

#define VARIANT_GET(variant, member) \
   VARIANT_NS::visit(                    \
      dl::overload{               \
         [](auto&& v) -> auto { return v.member; }}, (variant))

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;

template<typename Variant, typename... CBs>
auto match(Variant&& v, CBs&&... cbs)
{
    return VARIANT_NS::visit(
        dl::overload{ std::forward<decltype(cbs)>(cbs)... }, std::forward<decltype(v)>(v));
}

} // namespace dl

#define R_SWITCH(variant) dl::match(variant,
#define R_END_SWITCH );
#define CASE(Variant_Type, name) [&,this](const Variant_Type& name)
#define FCASE(Variant_Type, name) [&](const Variant_Type& name)
#define FFCASE(Variant_Type, name) [](const Variant_Type& name)
#define MCASE(Variant_Type, name) [&,this](Variant_Type& name)
#define MFCASE(Variant_Type, name) [&](Variant_Type& name)
#define MFFCASE(Variant_Type, name) [](Variant_Type& name)
#define CASE_MONOSTATE [&,this](const dl::monostate&)
#define FCASE_MONOSTATE [&](const dl::monostate&)
#define FFCASE_MONOSTATE [](const dl::monostate&)

#define SWITCH(variant) {auto& vr=variant; dl::match(variant,
#define END_SWITCH );}
#define CASE_1(name) [&,this](const dl::variant_alternative_t<0, std::decay_t<decltype(vr)>>& name)
#define CASE_2(name) [&,this](const dl::variant_alternative_t<1, std::decay_t<decltype(vr)>>& name)
#define CASE_3(name) [&,this](const dl::variant_alternative_t<2, std::decay_t<decltype(vr)>>& name)
#define CASE_4(name) [&,this](const dl::variant_alternative_t<3, std::decay_t<decltype(vr)>>& name)
#define CASE_5(name) [&,this](const dl::variant_alternative_t<4, std::decay_t<decltype(vr)>>& name)
#define CASE_6(name) [&,this](const dl::variant_alternative_t<5, std::decay_t<decltype(vr)>>& name)
#define CASE_7(name) [&,this](const dl::variant_alternative_t<6, std::decay_t<decltype(vr)>>& name)
#define CCASE_1(name) [this](const dl::variant_alternative_t<0, std::decay_t<decltype(vr)>>& name)
#define CCASE_2(name) [this](const dl::variant_alternative_t<1, std::decay_t<decltype(vr)>>& name)
#define CCASE_3(name) [this](const dl::variant_alternative_t<2, std::decay_t<decltype(vr)>>& name)
#define CCASE_4(name) [this](const dl::variant_alternative_t<3, std::decay_t<decltype(vr)>>& name)
#define CCASE_5(name) [this](const dl::variant_alternative_t<4, std::decay_t<decltype(vr)>>& name)
#define CCASE_6(name) [this](const dl::variant_alternative_t<5, std::decay_t<decltype(vr)>>& name)
#define CCASE_7(name) [this](const dl::variant_alternative_t<6, std::decay_t<decltype(vr)>>& name)
#define FCASE_1(name) [&](const dl::variant_alternative_t<0, std::decay_t<decltype(vr)>>& name)
#define FCASE_2(name) [&](const dl::variant_alternative_t<1, std::decay_t<decltype(vr)>>& name)
#define FCASE_3(name) [&](const dl::variant_alternative_t<2, std::decay_t<decltype(vr)>>& name)
#define FCASE_4(name) [&](const dl::variant_alternative_t<3, std::decay_t<decltype(vr)>>& name)
#define FCASE_5(name) [&](const dl::variant_alternative_t<4, std::decay_t<decltype(vr)>>& name)
#define FCASE_6(name) [&](const dl::variant_alternative_t<5, std::decay_t<decltype(vr)>>& name)
#define FCASE_7(name) [&](const dl::variant_alternative_t<6, std::decay_t<decltype(vr)>>& name)

#define MCASE_1(name) [&,this](dl::variant_alternative_t<0, std::decay_t<decltype(vr)>>& name)
#define MCASE_2(name) [&,this](dl::variant_alternative_t<1, std::decay_t<decltype(vr)>>& name)
#define MCASE_3(name) [&,this](dl::variant_alternative_t<2, std::decay_t<decltype(vr)>>& name)
#define MCASE_4(name) [&,this](dl::variant_alternative_t<3, std::decay_t<decltype(vr)>>& name)
#define MCASE_5(name) [&,this](dl::variant_alternative_t<4, std::decay_t<decltype(vr)>>& name)
#define MCASE_6(name) [&,this](dl::variant_alternative_t<5, std::decay_t<decltype(vr)>>& name)
#define MCASE_7(name) [&,this](dl::variant_alternative_t<6, std::decay_t<decltype(vr)>>& name)
#define MCCASE_1(name) [this](dl::variant_alternative_t<0, std::decay_t<decltype(vr)>>& name)
#define MCCASE_2(name) [this](dl::variant_alternative_t<1, std::decay_t<decltype(vr)>>& name)
#define MCCASE_3(name) [this](dl::variant_alternative_t<2, std::decay_t<decltype(vr)>>& name)
#define MCCASE_4(name) [this](dl::variant_alternative_t<3, std::decay_t<decltype(vr)>>& name)
#define MCCASE_5(name) [this](dl::variant_alternative_t<4, std::decay_t<decltype(vr)>>& name)
#define MCCASE_6(name) [this](dl::variant_alternative_t<5, std::decay_t<decltype(vr)>>& name)
#define MCCASE_7(name) [this](dl::variant_alternative_t<6, std::decay_t<decltype(vr)>>& name)
#define MFCASE_1(name) [&](dl::variant_alternative_t<0, std::decay_t<decltype(vr)>>& name)
#define MFCASE_2(name) [&](dl::variant_alternative_t<1, std::decay_t<decltype(vr)>>& name)
#define MFCASE_3(name) [&](dl::variant_alternative_t<2, std::decay_t<decltype(vr)>>& name)
#define MFCASE_4(name) [&](dl::variant_alternative_t<3, std::decay_t<decltype(vr)>>& name)
#define MFCASE_5(name) [&](dl::variant_alternative_t<4, std::decay_t<decltype(vr)>>& name)
#define MFCASE_6(name) [&](dl::variant_alternative_t<5, std::decay_t<decltype(vr)>>& name)
#define MFCASE_7(name) [&](dl::variant_alternative_t<6, std::decay_t<decltype(vr)>>& name)

#define CASE_DEFAULT [](auto&&)
#define MFCASE_DEFAULT [&](auto&&)

#endif