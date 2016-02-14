#ifndef GUARD_FILE_HANDLER_H
#define GUARD_FILE_HANDLER_H

#include "StdAfx.h"

#include <dirent.h>
#include <sys/types.h>

bool isbackslash(const char&);
std::vector<std::string> split_backslash(const std::string&);
std::vector<std::string> fill_vec_filepath(const char*);


#endif
