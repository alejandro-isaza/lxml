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
#include "QName.h"

#include <libxml/parser.h>
#include <map>
#include <string>

namespace lxml {

/**
 SAXHandler is a base abstract class defining SAX event methods.
 */
class SAXHandler {
public:
    typedef std::map<const char*, const char*> NamespaceMap;
    typedef std::map<QName, std::string> AttributeMap;
    
public:
    virtual void startDocument() = 0;
    virtual void endDocument() = 0;
    
    virtual void startElement(const QName& qname, const NamespaceMap& namespaces, const AttributeMap& attributes) = 0;
    virtual void endElement(const QName& qname) = 0;
    
    virtual void characters(const char* chars, std::size_t length) = 0;
    virtual void error(const xmlError& error) = 0;
};

} // namespace lxml
