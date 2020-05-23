// -*- mode: C++; c-file-style: "cc-mode" -*-
//*************************************************************************
// DESCRIPTION: Verilator: Emit Verilog from tree
//
// Code available from: https://verilator.org
//
//*************************************************************************
//
// Copyright 2020 by Wilson Snyder. This program is free software; you can
// redistribute it and/or modify it under the terms of either the GNU Lesser
// General Public License Version 3 or the Perl Artistic License Version 2.0.
// SPDX-License-Identifier: LGPL-3.0-only OR Artistic-2.0
//
//*************************************************************************

#include "verilatedos.h"

#include "V3File.h"
#include "V3WaiverOutput.h"

#include <memory>
#include <fstream>
#include <sstream>

void V3WaiverOutput::addEntry(V3ErrorCode errorCode, const std::string& filename,
                           const std::string& str) {
    std::stringstream entry;
    entry << "lint_off -rule " << errorCode.ascii() << " -file \"*" << filename << "\" -match \""
          << str << "\"";
    s_waiverList.push_back(entry.str());
}

void V3WaiverOutput::write(const std::string& filename) {
    const vl_unique_ptr<std::ofstream> ofp(V3File::new_ofstream(filename));
    if (ofp->fail()) v3fatal("Can't write " << filename);

    *ofp << "// DESCR"
            "IPTION: Verilator output: Waivers generated with --waiver-output"
            << std::endl << std::endl;

    *ofp << "`verilator_config" << std::endl << std::endl;

    *ofp << "// Below you find suggested waivers. You have three options:" << std::endl;
    *ofp << "//   1. Fix the reason for the linter warning" << std::endl;
    *ofp << "//   2. Keep the waiver permanently if you are sure this is okay" << std::endl;
    *ofp << "//   3. Keep the waiver temporarily to suppress the output" << std::endl;

    for (V3WaiverOutput::WaiverList::const_iterator it = s_waiverList.begin(); it != s_waiverList.end();
         ++it) {
        *ofp << "// " << *it << std::endl << std::endl;
    }
}

V3WaiverOutput::WaiverList V3WaiverOutput::s_waiverList;
