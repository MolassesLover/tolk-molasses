# Molasses' Tolk Fork

This is a fork of [Davy Kager](https://github.com/dkager)'s 
[Tolk](https://github.com/dkager/tolk); a library abstracting various 
screen reader APIs. Please view Tolk's upstream
[`README.MD`](https://github.com/dkager/tolk/blob/master/docs/README.md) file
for documentation.

> [!WARNING]
> This is experimental software, please wait before using this in any long-term project.

# To-do
- [ ] Finish adding examples to the CMake build process.
    - [ ] Fix the examples not finding the Tolk library.
- [ ] Add `nvdaControllerClient64.dll` to the build process.
    - [ ] Make sure the examples can find `nvdaControllerClient64.dll`.
- [ ] Re-format codebase.
- [ ] Create CI tasks, along with automated artefact distribution.
    - [ ] Add a code formatting action.
    - [ ] Add a code quality action.
- [ ] Replace manually-written bindings with SWIG binding generation.
- [ ] Create a documentation page.
- [ ] Add support for Free(b)Soft's Speech Dispatcher on Linux.
- [ ] Add support for Orca (using DBus) on Linux.
- [ ] Add support for MacOS' AppKit.
- [ ] Add support for MacOS' AVFoundation.
