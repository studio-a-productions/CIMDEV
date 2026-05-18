# This Project

This project is technically two *libraries*, `CIM` and `cyncosa` (*though the former may also be referred to as **cim***). Cyncosa is built ontop of CIM, and thus their development is currently intertwined (CIM gets updated out of the needs from cynCOSA).

This is a **development repository** and thus is not a *release*, nor is it a *public contributable* project. You may view its development in real-time, but do not expect the code or comments to be "perfect".

## Private Contribution

For those who are truly interested, you *may* use `Github issues` to help me find bugs and problems with the code. If there's a strong desire to contribute, we may eventually make it open-source before release (though this is not a promise!)

# CIM

**CIM**, currently meaning `CIM Is Managed` (*leaning on the **GNU** tradition*), is a `libc`-abstraction and overwriteable API. It provides either a stable ABI (when *implementing*), or a way to change parts of projects without needing to change the code everywhere.

**CIM** allows for even the most basic types (int, void, float, etc.) to be overwritten. It does not provide overwrites for `uncertain keywords` such as typedef or struct (see docs).

## CIM Implement

To `implement` **CIM** is to provide the backend yourself, which provides a "cleaner" ABI, meaning any function calling `CIM_SQRT` for example actually calls `CIM_STD_SQRT_FUNC` (as it is a macro expanding to a function name).

When using CIM Implemment, please note that if you want to overwrite types, you'll need to make a `cimport` header.

## Cimport

A `cimport` or *CIM import*, is a single header where you overwrite anything related to the `CIM Core` so that ABI mustn't break (if `CINT` were 64 bits instead of expected 32 bits).

For making *cimport*s, it's recommended to look at the example *cimport*: `cyncpsa_cimport.h`

## CIM Overwrite

Overwriting is the act of defining a macro before including CIM. Note that defining macro's beforehand also excludes the cim implement functions of those macros (so no `CIM_STD_SQRT_FUNC` if `CIM_SQRT` is predefined). This is this way because overwriting and implementing is, in the sense of functions, a conflict of interests.

## Documentation coming soon.


# cynCOSA

`cynCOSA` or *cyn's cross operating system API* is inspired by `muCOSA` by *muukid*. In some cases, it may be a direct reference to it, which is evident in the name. It is important to note that despite similarities, no code has been copied or stolen (*apart from ideas*).

`cynCOSA` tries to provide both a `global state` and `thread-safe` *states*, but these are **not interchangeable**.

## Documentation coming soon.
