#include <gtest/gtest.h>
#include "Variant.h"

class Base {};
class A : public Base {};
class B : public Base {};
class C {};

TEST(OverloadTest, Test) {
    dl::variant<A, B, C> varA;
    dl::visit(dl::overload{
        [](const Base&){ GTEST_FAIL(); },
        [](const A&){ GTEST_SUCCEED(); },
        [](const B&){ GTEST_FAIL(); },
        [](const C&){ GTEST_FAIL(); }
    }, varA);

    SWITCH(varA)
        FFCASE(Base, _) { GTEST_FAIL(); },
        FFCASE(A, _) { GTEST_SUCCEED(); },
        FFCASE(B, _) { GTEST_FAIL(); },
        FFCASE(C, _) { GTEST_FAIL(); }
    END_SWITCH

    dl::visit(dl::overload{
        [](const Base&){ GTEST_SUCCEED(); },
        [](const C&){ GTEST_FAIL(); }
    }, varA);

    dl::visit(dl::overload{
        [](const Base&){ GTEST_FAIL(); },
        [](const auto&){ GTEST_SUCCEED(); }
    }, varA);

    dl::visit(dl::overload{
        [](const A&){ GTEST_SUCCEED(); },
        [](const auto&){ GTEST_FAIL(); }
    }, varA);

    dl::variant<A, B, C> varC;
    varC.emplace<C>();
    dl::visit(dl::overload{
        [](const A&){ GTEST_FAIL(); },
        [](const auto&){ GTEST_SUCCEED(); }
    }, varC);


}