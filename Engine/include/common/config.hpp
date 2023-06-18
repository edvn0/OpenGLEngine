#pragma once

#ifndef RELEASE_BUILD
constexpr bool is_release = false;
#else
constexpr bool is_release = true;
#endif
