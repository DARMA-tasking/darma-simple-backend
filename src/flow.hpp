/*
//@HEADER
// ************************************************************************
//
//                      flow.hpp
//                         DARMA
//              Copyright (C) 2017 Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact David S. Hollman (dshollm@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef DARMASIMPLECVBACKEND_FLOW_HPP
#define DARMASIMPLECVBACKEND_FLOW_HPP

#include "trigger.hpp"

namespace simple_backend {

struct ControlBlock {
  ControlBlock(
    std::shared_ptr<darma_runtime::abstract::frontend::Handle const> in_handle
  ) : handle(in_handle) {
    data = ::operator new(in_handle->get_serialization_manager()->get_metadata_size());
    // TODO we could delay this
    handle->get_serialization_manager()->default_construct(data);
  }

  ~ControlBlock() {
    handle->get_serialization_manager()->destroy(data);
    ::operator delete(data);
  }

  std::shared_ptr<darma_runtime::abstract::frontend::Handle const> handle;
  void* data = nullptr;
};

struct Flow {
  Flow(std::shared_ptr<ControlBlock> cblk) : control_block(cblk), trigger(0) { }
  Flow( std::shared_ptr<ControlBlock> cblk, size_t initial_count)
    : control_block(cblk), trigger(initial_count) { }
  CountdownTrigger<MultiActionList> trigger;
  std::shared_ptr<ControlBlock> control_block;
};

struct AntiFlow {
  AntiFlow() : trigger(0) { }
  AntiFlow(size_t initial_count) : trigger(initial_count) { }
  CountdownTrigger<MultiActionList> trigger;
};

} // end namespace simple_backend

#endif //DARMASIMPLECVBACKEND_FLOW_HPP