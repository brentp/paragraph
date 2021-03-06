// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Copyright (c) 2017 Illumina, Inc.
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 * \brief CompositeAligner interface
 *
 * \file CompositeAligner.hh
 * \author Roman Petrovski
 * \email rpetrovski@illumina.com
 *
 */

#pragma once

#include "PathAligner.hh"
#include "grm/Filter.hh"
#include "grm/GraphAligner.hh"
#include "grm/KlibAligner.hh"
#include "grm/KmerAligner.hh"
#include "grm/PathAligner.hh"

namespace grm
{

/**
 * Wrapper for a combination of KmerAligner and GraphAligner
 */
class CompositeAligner
{
public:
    CompositeAligner(
        bool pathMatching, bool graphMatching, bool klibMatching, bool kmerMatching,
        unsigned grapAlignmentflags = GraphAligner::AF_ALL);

    virtual ~CompositeAligner();

    CompositeAligner(CompositeAligner&& rhs) noexcept;

    CompositeAligner& operator=(CompositeAligner&& rhs) noexcept = delete;

    void setGraph(graphtools::Graph const* graph, std::list<graphtools::Path> const& paths);
    void alignRead(common::Read& read, ReadFilter filter);

    unsigned attempted() const { return attempted_; }
    unsigned filtered() const { return filtered_; }
    unsigned mappedKlib() const { return mappedKlib_; }
    unsigned mappedPath() const { return mappedPath_; }
    unsigned anchoredPath() const { return anchoredPath_; }
    unsigned mappedKmers() const { return mappedKmers_; }
    unsigned mappedSw() const { return mappedSw_; }

private:
    const bool pathMatching_;
    const bool graphMatching_;
    const bool klibMatching_;
    const bool kmerMatching_;
    const unsigned int grapAlignmentflags_;

    grm::PathAligner pathAligner_;
    grm::GraphAligner graphAligner_;
    grm::KlibAligner klibAligner_;
    grm::KmerAligner<16> kmerAligner_;
    // grm::KmerAligner<32> kmerAligner_;

    unsigned attempted_ = 0;
    unsigned filtered_ = 0;
    unsigned mappedKlib_ = 0;
    unsigned mappedPath_ = 0;
    unsigned anchoredPath_ = 0;
    unsigned mappedKmers_ = 0;
    unsigned mappedSw_ = 0;
#ifdef _DEBUG
    graphtools::Graph const* graph_;
#endif
};
}
