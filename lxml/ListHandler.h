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

#pragma once
#include "BaseRecursiveHandler.h"
#include <vector>

namespace lxml {

/**
 ListHandler is a recursive handler that forwards subelements to a delegate
 handler and builds a vector with the results.
 */
template <typename T>
class ListHandler : public BaseRecursiveHandler<std::vector<T>> {
public:
    ListHandler(BaseRecursiveHandler<T>& itemHandler) : _itemHandler(itemHandler) {}
    
    void startElement(const QName& qname, const RecursiveHandler::AttributeMap& attributes) {
        this->_result.clear();
    }
    
    RecursiveHandler* startSubElement(const QName& qname) {
        return &_itemHandler;
    }
    
    void endSubElement(const QName& qname, RecursiveHandler* handler) {
        this->_result.push_back(_itemHandler.result());
    }
    
private:
    BaseRecursiveHandler<T>& _itemHandler;
};

} // namespace lxml
