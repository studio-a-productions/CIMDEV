# This Project

This project is technically two *libraries*, `CIM` and `cyncosa` (*though the former may also be referred to as **cim***). Cyncosa is built on top of CIM, and thus their development is currently intertwined (CIM gets updated out of the needs from cynCOSA).

This is a **development repository** and thus is not a *release*, nor is it a *publicly contributable* project. You may view its development in real-time, but do not expect the code or comments to be "perfect".

## Private Contribution

For those who are truly interested, you *may* use `GitHub Issues` to help me find bugs and problems with the code. If there's a strong desire to contribute, we may eventually make it open-source before release (though this is not a promise!)

# CIM

**CIM**, currently meaning `CIM Is Managed` (*leaning on the **GNU** tradition*), is a `libc`-abstraction and overwritable API. It provides either a stable ABI (when *implementing*), or a way to change parts of projects without needing to change the code everywhere.

**CIM** allows for even the most basic types (int, void, float, etc.) to be overwritten. It does not provide overwrites for `uncertain keywords` such as typedef or struct (see docs).

## CIM Implement

To `implement` **CIM** is to provide the backend yourself, which provides a "cleaner" ABI, meaning any function calling `CIM_SQRT` for example actually calls `CIM_STD_SQRT_FUNC` (as it is a macro expanding to a function name).

When using CIM Implement, please note that if you want to overwrite types, you'll need to make a `cimport` header.

## Cimport

A `cimport` or *CIM import*, is a single header where you overwrite anything related to the `CIM Core` so that ABI mustn't break (if `CINT` were 64 bits instead of expected 32 bits).

For making *cimport*s, it's recommended to look at the example *cimport*: `cyncosa_cimport.h`

## CIM Overwrite

Overwriting is the act of defining a macro before including CIM. Note that defining macros beforehand also excludes the cim implement functions of those macros (so no `CIM_STD_SQRT_FUNC` if `CIM_SQRT` is predefined). It is this way because overwriting and implementing is, in the sense of functions, a conflict of interests.

# CIM Documentation

## CIM Types

Firstly, before we explain each type, it is important to know that cim does **not** provide `typedef`s (currently) and instead uses macros. So when we say *CIM Type*, we mean a macro that functions as a type.

Secondly, if CIM were to use *typedef*s, it'd be mapped to those same macros. See the following code:
```c

#ifndef CCHAR

typedef char CIM_STD_CHAR_TYPE;

#define CCHAR CIM_STD_CHAR_TYPE

#endif
```

This is how the variable `CCHAR` would be mapped to a typedef.

## CIM Implicit Types

CIM's `Implicit Types`, are not types in the conventional sense, they're *implied to be types*, but cannot be used as such. For example `CIMDEF` could become `__stdcall` or similar, and thus is not an actual variable.

### CIMEXTR

CIMEXTR is a macro that, depending on whether you are compiling to C or C++, expands to `extern` or `extern "C"`.

### CIMCALL

CIMCALL is used by all of CIM's functions, and *could* be used to make a compiler know what the "standard" functions are and how to call them.

### Primitive

The primitive implicit types are the following:
- CIMSIGN: `signed`
- CIMUNSIGN: `unsigned`
- CCONST: `const` (*note: you may change it into constexpr for C++-only projects*)

## Explicit Types

CIM provides multiple `Explicit Types`, which range from unsigned integers to vector types, though some are locked behind `CIM Advanced`. For some types, it is best practice to map them to your local bit sizes (like `stdint.h`) before using cim (thus creating a cimport).

### STD Primitives

| name | description |
| :---: | :--------- |
| `CCHAR` | A single character taken up the space of 8 bits, which for safety isn't set to be *CIMSIGN* or *CIMUNSIGN* as this can be variable between compilers |
| `CINT64` | A 64 bit signed integer, though CIM only says what it's minimum size should be 64, not its maximum on other systems. It's best practice to map these to `stdint.h` |
| `CINT32` | Signed integer, min. 32 bits |
| `CINT16` | Signed integer, min. 16 bits |
| `CINT8`  | Signed integer, min. 8  bits, equivalent to CIMSIGN CCHAR |
| `CUINT64` | Unsigned integer, min. 64 bits |
| `CUINT32` | Unsigned integer, min. 32 bits |
| `CUINT16` | Unsigned integer, min. 16 bits |
| `CUINT8` | Unsigned integer, min. 8 bits, equivalent to CIMUNSIGN CCHAR |
| `CVOID` | Analogue to *void* |
| `CFLOAT`| 32 bit float |
| `CDOUBLE`| 64 bit float |
| `CINT` | Standardised signed integer. *CINT32* by default |
| `CUINT`| Standardised unsigned integer. *CUINT32* by default |
| `CIZE` | Standardised size unsigned integer. *CUINT32* by default |
| `CBYTE` | A single byte, maps to *CUINT8* |
| `CBOOL` | Boolean mapping to *CUINT8* |

## CIM's eValues

CIM's *eValues* are more or less `extern constant values`, values which can be defined with *CIM Implement*, or when *overwriting*. eValues are by design variables, so overwriting them must take into account that some code using pointers may become invalid if it isn't mapped to an external variable. CIM's eValues are constant because they could be optimised, but there may be use cases where it's easier to check addresses instead of actual values. We'll give standard values which many may prefer, but you may change it to whatever constant you feel like.

`CNULL` is not an eValue because it would complicate normal null-checking, and thus it maps to `((CVOID*)0)` as a macro.

### CBOOL

| value name | namespace name | standard value |
| ---------: | :------------- | :------------: |
| `CTRUE` | CIM_STD_BOOL_TRUE | 1U |
| `CFALSE`| CIM_STD_BOOL_FALSE| 0U |

## Documentation to be continued


# cynCOSA

`cynCOSA` or *cyn's cross operating system API* is inspired by `muCOSA` by *muukid*. In some cases, it may be a direct reference to it, which is evident in the name. It is important to note that despite similarities, no code has been copied or stolen (*apart from ideas*).

`cynCOSA` tries to provide both a `global state` and `thread-safe` *states*, but these are **not interchangeable**. 

## Documentation coming soon.


# Documentation note

While the project itself (code-wise) is not contributable, the documentation may, because I'm too lazy to write it. I *could* use a tool like auto-documentation or something with AI, but I don't want anyone to assume I didn't write my code myself (aka: vibecoding). Anyhow, you've reached the end of the REAMDE! ;)