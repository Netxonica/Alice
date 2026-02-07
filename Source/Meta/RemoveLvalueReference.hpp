// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_lvalue_reference
#define alice_header_guard_meta_remove_lvalue_reference

namespace Alice::Meta
{
    namespace Detail
    {
        template<class Self> struct [[nodiscard]] RemoveLvalueReference final
        {
            constexpr ~RemoveLvalueReference() noexcept = delete;

            explicit consteval RemoveLvalueReference() noexcept = delete;

            explicit consteval RemoveLvalueReference(const RemoveLvalueReference&) noexcept =
            delete;

            explicit consteval RemoveLvalueReference(RemoveLvalueReference&&) noexcept = delete;

            consteval auto operator=(const RemoveLvalueReference&) noexcept ->
            RemoveLvalueReference& = delete;

            consteval auto operator=(RemoveLvalueReference&&) noexcept -> RemoveLvalueReference& =
            delete;

            [[nodiscard]] consteval auto operator==(const RemoveLvalueReference&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveLvalueReference&) const noexcept =
            delete;

            using Type = Self;
        };

        template<class Self> struct [[nodiscard]] RemoveLvalueReference<Self&> final
        {
            constexpr ~RemoveLvalueReference() noexcept = delete;

            explicit consteval RemoveLvalueReference() noexcept = delete;

            explicit consteval RemoveLvalueReference(const RemoveLvalueReference&) noexcept =
            delete;

            explicit consteval RemoveLvalueReference(RemoveLvalueReference&&) noexcept = delete;

            consteval auto operator=(const RemoveLvalueReference&) noexcept ->
            RemoveLvalueReference& = delete;

            consteval auto operator=(RemoveLvalueReference&&) noexcept -> RemoveLvalueReference& =
            delete;

            [[nodiscard]] consteval auto operator==(const RemoveLvalueReference&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveLvalueReference&) const noexcept =
            delete;

            using Type = Self;
        };
    }

    template<class Self> using RemoveLvalueReference = typename Detail::RemoveLvalueReference<Self>
    ::Type;
}

#endif
#endif