![Alice's logo](./Logo.png)

**Alice** is a modern C++29 project built around three core principles: **safety**, **performance**, and **ergonomics**. It leverages the latest language features to deliver a robust and expressive programming experience without sacrificing speed or correctness.

---

## Design Philosophy

### Safety

Alice is designed with safety as a first-class concern. Memory safety, type safety, and well-defined behavior are enforced wherever possible through language-level guarantees and careful API design. Undefined behavior is treated as a bug in Alice itself.


### Performance

Alice targets modern hardware and makes no apologies for it. By requiring up-to-date compilers, architectures, and GPU APIs, Alice can take full advantage of contemporary CPU and GPU capabilities without carrying legacy baggage.


### Ergonomics

Good software should be a pleasure to use. Alice prioritizes clean, expressive APIs, clear error messages, and a smooth developer experience from first build to production deployment.

---

## Requirements

### Compilers

Alice requires a compiler with full C++29 support:

| Compiler | Minimum Version |
|----------|-----------------|
| Clang    | 27+             |
| GCC      | 20+             |
| MSVC     | 14.52+          |


### Build System

| Tool  | Minimum Version |
|-------|-----------------|
| CMake | 4.3.4+          |
| Ninja | 1.13+           |


### Architectures

| Architecture |
|--------------|
| x86\_64      |
| ARM64        |


### Operating Systems

| OS      | Minimum version |
|---------|-----------------|
| Linux   | 7.0+            |
| macOS   | 27.0+           |
| Windows | 11 26H1+        |


### SDK

| SDK     | Minimum SDK                                                                           |
|---------|---------------------------------------------------------------------------------------|
| Linux   | A running Wayland compositor, Wayland 1.25+ protocol and client, and latest PkgConfig |
| macOS   | Xcode 27.0+                                                                           |
| Windows | Latest Visual Studio 2026 and Windows SDK 10.0.28000+                                 |


### GPU

Alice requires a GPU and drivers capable of running the latest graphics APIs for the target platform:

| Platform | Required API                           |
|----------|----------------------------------------|
| Linux    | Vulkan SDK 1.4.350+                    |
| macOS    | Metal 4.1+                             |
| Windows  | DXC 1.9.2602+ and D3D12 Agility 1.619+ |

---

## Getting Started

### Clone

```bash
git clone https://github.com/Netxonica/Alice.git
cd Alice
```


### Build

In the case of macOS, modify Info.plist as you prefer. Afterwards, do the following:

```bash
cmake -B Build/{Debug|Release} -S . -G Ninja -D CMAKE_BUILD_TYPE={Debug|Release}
ninja clean_app -C Build/{Debug|Release}
ninja -C Build/{Debug|Release}
```

The following CMake Alice options are off/undefined by default, but you can explicitly set these:


#### ISA Extensions

At the `cmake` command, one can define any number of the following macros to enable the specific ISA optimizations:

- For amd64: ``ALICE_SSE4_2, ALICE_AVX, ALICE_AVX2, ALICE_AVX512, ALICE_AVX10_1, ALICE_AVX10_2, ALICE_APX``
- For arm64: ``ALICE_ARM8_1, ALICE_ARM8_2, ALICE_ARM8_3, ALICE_ARM8_4, ALICE_ARM8_5, ALICE_ARM8_6, ALICE_ARM8_7, ALICE_ARM8_8, ALICE_ARM8_9, ALICE_ARM9_0, ALICE_ARM9_1, ALICE_ARM9_2, ALICE_ARM9_3, ALICE_ARM9_4``

An example of enabling ARMv8.1 and ARMv8.2 would be:

```bash
cmake -B Build/{Debug|Release} -S . -G Ninja -D CMAKE_BUILD_TYPE={Debug|Release} -D ALICE_ARM8_1=On -D ALICE_ARM8_2=On
```


#### Initial Reserved Stack

You can set a custom initial reserved stack space at the `cmake` command by defining `ALICE_STACK` with a non-zero natural number, which will be round-up (ceil) to align to a multiple of the system page size. An example:

```bash
cmake -B Build/{Debug|Release} -S . -G Ninja -D CMAKE_BUILD_TYPE={Debug|Release} -D ALICE_STACK=8000000
```


#### Safe Buffers

You can set `ALICE_SAFE_BUFFERS` in the `cmake` command to apply security checks to buffers. An example:

```bash
cmake -B Build/{Debug|Release} -S . -G Ninja -D CMAKE_BUILD_TYPE={Debug|Release} -D ALICE_SAFE_BUFFERS=On
```


#### Safe Control Flow

You can set `ALICE_SAFE_CONTROL_FLOW` in the `cmake` command to apply security checks to the control flow. An example:

```bash
cmake -B Build/{Debug|Release} -S . -G Ninja -D CMAKE_BUILD_TYPE={Debug|Release} -D ALICE_SAFE_CONTROL_FLOW=On
```


#### Safe Stack

You can set `ALICE_SAFE_STACK` in the `cmake` command to apply secure zero-initialization to the padding bytes of eligible objects, and avoid leaking the prior bytes of the uninitialized memory. It also enables stack frame checks and the use of uninitialized locals. An example:

```bash
cmake -B Build/{Debug|Release} -S . -G Ninja -D CMAKE_BUILD_TYPE={Debug|Release} -D ALICE_SAFE_STACK=On
```


#### Spectre

You can set `ALICE_SPECTRE` in the `cmake` command to apply spectre mitigations at the compiler-level. An example:

```bash
cmake -B Build/{Debug|Release} -S . -G Ninja -D CMAKE_BUILD_TYPE={Debug|Release} -D ALICE_SPECTRE=On
```


### Visual Studio Code integration (optional)

- Install Python 3 to use the release task (optional).
- Install the recommended extensions in `.vscode/extensions.json`.
- Define the following environment variables within PATH:
    - `ALICE_GDB_PATH`: The path to the GDB binary (optional, only required when debugging with GDB.)
    - `ALICE_LINKER_PATH`: The path to the linker binary.
    - `ALICE_COMPILER_PATH`: The path to the C++ compiler.
- Use the 'Run and Debug' view to compile and debug.

---

## Documentation

The header files under the `Source` folder are all documented with java-doc style comments. Perfect to generate your own Doxygen documentation.

If something is not documented, it's not meant to be used.

---

## Testing

Every documented feature is tested thoroughly under the `Test` folder. These also showcase how the features are meant to be used.

---

## License

See [LICENSE](LICENSE.md) for details.

---

## Notice

See [NOTICE](NOTICE.md) for details.