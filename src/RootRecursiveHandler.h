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
#include "SAXHandler.h"
#include "RecursiveHandler.h"

#include <string>
#include <vector>

namespace lxml {

/**
 RootRecursiveHandler is a SAXHandler that dispatches events to instances
 of RecursiveHandler.
 
 @see RecursiveHandler
 @see SAXHandler
 */
class RootRecursiveHandler : public SAXHandler {
public:
    explicit RootRecursiveHandler(RecursiveHandler* rootHandler);
    
    virtual void startDocument();
    virtual void endDocument();
    
    virtual void startElement(const QName& qname, const NamespaceMap& namespaces, const AttributeMap& attributes);
    virtual void endElement(const QName& qname);
    
    virtual void characters(const char* chars, std::size_t length);
    virtual void error(const xmlError& error);
    
private:
    RecursiveHandler* _rootHandler;
    std::vector<RecursiveHandler*> _handlerStack;
    std::vector<std::string> _contents;
};

} // namespace lxml
