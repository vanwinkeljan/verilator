// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: Emit XML code
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// Copyright 2003-2020 by Wilson Snyder. This program is free software; you
// can redistribute it and/or modify it under the terms of either the GNU
// Lesser General Public License Version 3 or the Perl Artistic License
// Version 2.0.
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#ifndef _V3WAIVEROUTPUT_H_
#define _V3WAIVEROUTPUT_H_ 1

#include "V3Error.h"

#include <vector>
#include <string>

class V3WaiverOutput {
    // TYPES
    typedef std::vector<std::string> WaiverList;
    static WaiverList s_waiverList;

public:
    static void addEntry(V3ErrorCode errorCode, const string& filename, const std::string& str);
    static void write(const std::string& filename);
};

#endif  // Guard
