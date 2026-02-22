// Copyright 2026 Netxonica. All Rights Reserved.
#if alice_major >= 0 and alice_middle >= 0 and alice_minor >= 1
#ifndef alice_header_guard_trait_pointer
#define alice_header_guard_trait_pointer

namespace Alice::Trait
{
    namespace Detail
    {
        template<class> struct [[nodiscard]] Pointer final
        {
            constexpr ~Pointer() noexcept = delete;

            explicit consteval Pointer() noexcept = delete;

            explicit consteval Pointer(const Pointer&) noexcept = delete;

            explicit consteval Pointer(Pointer&&) noexcept = delete;

            consteval auto operator=(const Pointer&) noexcept -> Pointer& = delete;

            consteval auto operator=(Pointer&&) noexcept -> Pointer& = delete;

            [[nodiscard]] consteval auto operator==(const Pointer&) const noexcept -> bool = delete
            ;

            [[nodiscard]] consteval auto operator<=>(const Pointer&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return false;
            }
        };

        template<class Self> struct [[nodiscard]] Pointer<Self*> final
        {
            constexpr ~Pointer() noexcept = delete;

            explicit consteval Pointer() noexcept = delete;

            explicit consteval Pointer(const Pointer&) noexcept = delete;

            explicit consteval Pointer(Pointer&&) noexcept = delete;

            consteval auto operator=(const Pointer&) noexcept -> Pointer& = delete;

            consteval auto operator=(Pointer&&) noexcept -> Pointer& = delete;

            [[nodiscard]] consteval auto operator==(const Pointer&) const noexcept -> bool = delete
            ;

            [[nodiscard]] consteval auto operator<=>(const Pointer&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self> struct [[nodiscard]] Pointer<Self* const> final
        {
            constexpr ~Pointer() noexcept = delete;

            explicit consteval Pointer() noexcept = delete;

            explicit consteval Pointer(const Pointer&) noexcept = delete;

            explicit consteval Pointer(Pointer&&) noexcept = delete;

            consteval auto operator=(const Pointer&) noexcept -> Pointer& = delete;

            consteval auto operator=(Pointer&&) noexcept -> Pointer& = delete;

            [[nodiscard]] consteval auto operator==(const Pointer&) const noexcept -> bool = delete
            ;

            [[nodiscard]] consteval auto operator<=>(const Pointer&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self> struct [[nodiscard]] Pointer<Self* volatile> final
        {
            constexpr ~Pointer() noexcept = delete;

            explicit consteval Pointer() noexcept = delete;

            explicit consteval Pointer(const Pointer&) noexcept = delete;

            explicit consteval Pointer(Pointer&&) noexcept = delete;

            consteval auto operator=(const Pointer&) noexcept -> Pointer& = delete;

            consteval auto operator=(Pointer&&) noexcept -> Pointer& = delete;

            [[nodiscard]] consteval auto operator==(const Pointer&) const noexcept -> bool = delete
            ;

            [[nodiscard]] consteval auto operator<=>(const Pointer&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };

        template<class Self> struct [[nodiscard]] Pointer<Self* volatile const> final
        {
            constexpr ~Pointer() noexcept = delete;

            explicit consteval Pointer() noexcept = delete;

            explicit consteval Pointer(const Pointer&) noexcept = delete;

            explicit consteval Pointer(Pointer&&) noexcept = delete;

            consteval auto operator=(const Pointer&) noexcept -> Pointer& = delete;

            consteval auto operator=(Pointer&&) noexcept -> Pointer& = delete;

            [[nodiscard]] consteval auto operator==(const Pointer&) const noexcept -> bool = delete
            ;

            [[nodiscard]] consteval auto operator<=>(const Pointer&) const noexcept = delete;

            [[nodiscard]] static consteval auto Value() noexcept -> bool
            {
                return true;
            }
        };
    }

    template<class Self> concept Pointer = Detail::Pointer<Self>::Value();
}

#endif
#endif