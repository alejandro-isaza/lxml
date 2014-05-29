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

#include "RootRecursiveHandler.h"
#include <cassert>

namespace lxml {

RootRecursiveHandler::RootRecursiveHandler(RecursiveHandler* rootHandler) {
    assert(rootHandler != 0);
    _handlerStack.push_back(rootHandler);
}

void RootRecursiveHandler::startDocument() {
    assert(_handlerStack.size() == 1);
}

void RootRecursiveHandler::endDocument() {
    assert(_handlerStack.size() == 1);
}

void RootRecursiveHandler::startElement(const QName& qname, const NamespaceMap& namespaces, const AttributeMap& attributes) {
    RecursiveHandler* handler = _handlerStack.back();
    RecursiveHandler* startSubElement = 0;
    if (handler) {
        startSubElement = handler->startSubElement(qname);
        if (startSubElement)
            startSubElement->startElement(qname, attributes);
    }
    _handlerStack.push_back(startSubElement);
    _contents.emplace_back();
}

void RootRecursiveHandler::endElement(const QName& qname) {
    RecursiveHandler* startSubElement = _handlerStack.back();
    if (startSubElement)
        startSubElement->endElement(qname, _contents.back());
    _handlerStack.pop_back();
    
    RecursiveHandler* handler = _handlerStack.back();
    if (handler)
        handler->endSubElement(qname, startSubElement);
    _contents.pop_back();
}

void RootRecursiveHandler::characters(const char* chars, std::size_t length) {
    _contents.back() += std::string(chars, length);
}

void RootRecursiveHandler::error(const xmlError& error) {
    
}

} // namespace lxml
