// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_meta_remove_rvalue_reference
#define alice_header_guard_meta_remove_rvalue_reference

namespace Alice::Meta
{
    namespace Detail
    {
        template<class Self> struct RemoveRvalueReference final
        {
            constexpr compl RemoveRvalueReference() noexcept = delete;

            explicit consteval RemoveRvalueReference() noexcept = delete;

            explicit consteval RemoveRvalueReference(const RemoveRvalueReference&) noexcept =
            delete;

            explicit consteval RemoveRvalueReference(RemoveRvalueReference&&) noexcept = delete;

            consteval auto operator=(const RemoveRvalueReference&) noexcept ->
            RemoveRvalueReference& = delete;

            consteval auto operator=(RemoveRvalueReference&&) noexcept -> RemoveRvalueReference& =
            delete;

            [[nodiscard]] consteval auto operator==(const RemoveRvalueReference&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveRvalueReference&) const noexcept =
            delete;

            using Type = Self;
        };

        template<class Self> struct RemoveRvalueReference<Self&&> final
        {
            constexpr compl RemoveRvalueReference() noexcept = delete;

            explicit consteval RemoveRvalueReference() noexcept = delete;

            explicit consteval RemoveRvalueReference(const RemoveRvalueReference&) noexcept =
            delete;

            explicit consteval RemoveRvalueReference(RemoveRvalueReference&&) noexcept = delete;

            consteval auto operator=(const RemoveRvalueReference&) noexcept ->
            RemoveRvalueReference& = delete;

            consteval auto operator=(RemoveRvalueReference&&) noexcept -> RemoveRvalueReference& =
            delete;

            [[nodiscard]] consteval auto operator==(const RemoveRvalueReference&) const noexcept ->
            bool = delete;

            [[nodiscard]] consteval auto operator<=>(const RemoveRvalueReference&) const noexcept =
            delete;

            using Type = Self;
        };
    }

    /**
     * @brief Returns @p Self without rvalue references, if any.
     */
    template<class Self> using RemoveRvalueReference = typename Detail::RemoveRvalueReference<Self>
    ::Type;
}

#endif
#endif