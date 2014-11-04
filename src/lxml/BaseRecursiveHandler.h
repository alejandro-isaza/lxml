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
#include "RecursiveHandler.h"

namespace lxml {

/**
 BaseRecursiveHandler is a base class for recursive handlers. It implements
 all methods in the abstract class so that subclases need only implement
 methods for events they are interested in. It also includes a protected
 result field and accessor methods for the result.
 */
template <typename T>
class BaseRecursiveHandler : public RecursiveHandler {
public:
    const T& result() const {
        return _result;
    }
    
    T&& result() {
        return std::move(_result);
    }
    
    void reset() {
        _result = T();
    }
    
    virtual void startElement(const QName& qname, const AttributeMap& attributes) {
        
    }
    
    virtual void endElement(const QName& qname, const std::string& contents) {
        
    }
    
    virtual RecursiveHandler* startSubElement(const QName& qname) {
        return 0;
    }
    
    virtual void endSubElement(const QName& qname, RecursiveHandler* handler) {
        
    }
    
protected:
    T _result;
};

} // namespace lxml
