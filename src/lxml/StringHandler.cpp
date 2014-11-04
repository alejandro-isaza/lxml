// Copyright (c) 2014 Venture Media Labs, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include "StringHandler.h"

namespace lxml {

void StringHandler::endElement(const QName& qname, const std::string& contents) {
    _result = trim(contents);
}

std::string StringHandler::trim(const std::string& string) {
    // Trim whitespace at the start
    auto first = string.begin();
    while (first != string.end() && std::isspace(*first))
        ++first;
    
    // Trim whitespace at the end
    auto rlast = string.rbegin();
    while (rlast != string.rend() && std::isspace(*rlast))
        ++rlast;
    
    auto last = rlast.base();
    if (last <= first)
        return std::string();
    return std::string(first, last);
}

} // namespace lxml
