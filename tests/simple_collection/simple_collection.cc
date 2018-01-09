/*
//@HEADER
// ************************************************************************
//
//                   simple_collection.cc
//                         DARMA
//              Copyright (C) 2016 Sandia Corporation
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

#include <darma.h>
#include <darma/impl/task_collection/task_collection.h>
#include <darma/impl/array/index_range.h>
#include <assert.h>

using namespace darma_runtime;
using namespace darma_runtime::keyword_arguments_for_access_handle_collection;

struct SimpleCollection {
  void operator()(
    Index1D<int> index,
    AccessHandleCollection<int, Range1D<int>> c1,
    bool const first
  ) {
    auto handle = c1[index].local_access();

    if (first) {
      std::cout << "Setting index " << index.value
                << " to value " << index.value
                << std::endl;
      handle.set_value(index.value);
    } else {
      std::cout << "Checking index "
                << index.value
                << " to make sure "
                << handle.get_value()
                << "=="
                << index.value << std::endl;
      assert(handle.get_value() == index.value);
    }
  }
};

void darma_main_task(std::vector<std::string> args) {

  if (args.size() > 1 && args[1] == "--help"){
    std::cout << "Usage: ./simple_collection [Collection Size (int)]"
              << std::endl;
    return;
  }

  assert(args.size() == 2);

  size_t const col_size = std::atoi(args[1].c_str());

  auto c1 = initial_access_collection<int>("simple", index_range=Range1D<int>(col_size));

  std::cout << "In top level task" << std::endl;

  create_concurrent_work<SimpleCollection>(
    c1, true, index_range=Range1D<int>(col_size)
  );

  //create_concurrent_work<SimpleCollection>(
  //  c1, false, index_range=Range1D<int>(col_size)
  //);
}

DARMA_REGISTER_TOP_LEVEL_FUNCTION(darma_main_task);
