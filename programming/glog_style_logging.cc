// Header file 

#pragma once
#include <iostream>

static std::ostream * InnoOs;
static std::ostream   NullStream(nullptr);
int32_t vlog_level();
#define VLOG_IS_ON(n)    (vlog_level() >= (n))
#define VLOG(n)          InnoOs = &(VLOG_IS_ON(n)? std::cout : NullStream); \
                         *InnoOs << "[" << std::this_thread::get_id() \
                                 << ", " << FILENAME \
                                 << ", " << __LINE__ << "] " << std::flush
#define VLOG_IF(n, cond) InnoOs = &((VLOG_IS_ON(n) && (cond))? std::cout : NullStream); *InnoOs << std::flush

// C-style, "type" must be distinct
// #define VLOG_TYPE(n, type, dt)     {if (VLOG_IS_ON(n)) {VLOG(n) << ""; ostream_##type(std::cout, dt);}}
// #define VLOG_OS(n, type, dt)       {if (VLOG_IS_ON(n)) {ostream_##type(std::cout, dt);}}
// #define OPERATOR_STDOUT(type, obj) std::ostream& ostream_##type(std::ostream& os, type const & obj)

// C++-style, "type" may spell the same as long as it's inside a class or namespace
#define VLOG_TYPE(n, type, dt)     {if (VLOG_IS_ON(n)) {VLOG(n) << dt << std::endl;}}
#define VLOG_OS(n, type, dt)       {if (VLOG_IS_ON(n)) {std::cout << dt << std::endl;}}
#define OPERATOR_STDOUT(type, obj) std::ostream& operator<<(std::ostream& os, type const & obj)


// C++ source file, inside a class
friend OPERATOR_STDOUT(UserConfig, config) {
  ...
}

VLOG_TYPE(3, UserConfig, Configuration());
