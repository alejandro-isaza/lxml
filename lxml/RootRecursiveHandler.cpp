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

RootRecursiveHandler::RootRecursiveHandler(RecursiveHandler* rootHandler) : _rootHandler(rootHandler) {
    assert(rootHandler != 0);
}

void RootRecursiveHandler::startDocument() {
    assert(_handlerStack.empty());
}

void RootRecursiveHandler::endDocument() {
    assert(_handlerStack.empty());
}

void RootRecursiveHandler::startElement(const QName& qname, const NamespaceMap& namespaces, const AttributeMap& attributes) {
    if (_handlerStack.empty()) {
        // Root element
        _rootHandler->startElement(qname, attributes);
        _handlerStack.push_back(_rootHandler);
    } else {
        RecursiveHandler* handler = _handlerStack.back();
        RecursiveHandler* childHandler = 0;
        if (handler) {
            childHandler = handler->startSubElement(qname);
            if (childHandler)
                childHandler->startElement(qname, attributes);
        }
        _handlerStack.push_back(childHandler);
    }

    _contents.emplace_back();
}

void RootRecursiveHandler::endElement(const QName& qname) {
    RecursiveHandler* handler = _handlerStack.back();
    if (handler)
        handler->endElement(qname, _contents.back());

    _handlerStack.pop_back();
    _contents.pop_back();

    if (!_handlerStack.empty()) {
        RecursiveHandler* parentHandler = _handlerStack.back();
        if (parentHandler)
            parentHandler->endSubElement(qname, handler);
    }
}

void RootRecursiveHandler::characters(const char* chars, std::size_t length) {
    _contents.back() += std::string(chars, length);
}

void RootRecursiveHandler::error(const xmlError& error) {
    
}

} // namespace lxml
