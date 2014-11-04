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
#include <map>
#include <string>

namespace lxml {

/**
 RecursiveHandler is a base abstract class defining event methods for a
 recursive SAX event handler. This is similar to SAXHandler, but recursive
 handlers are registered as handling only particular elements in the XML
 document. The recursive handler can provide futher recursive handlers to
 handle sub-elements.
 */
class RecursiveHandler {
public:
    typedef std::map<QName, std::string> AttributeMap;
    
public:
    /**
     This method is called when an element's opening tag is encountered in
     an XML document. This is only called for elements for which this
     handler is the designated handler as specified by the `startSubElement`
     method in a recursive handler.
     
     @param qname The qualified name of the element.
     @param attributes All attributes present in the element.
     */
    virtual void startElement(const QName& qname, const AttributeMap& attributes) = 0;
    
    /**
     This method is called when an element's closing tag is encountered in
     an XML document. This is called exactly once for each call to
     `startElement` unless there is a parsing error.
     
     @param qname The qualified name of the element.
     @param contents The concatenated and trimmed text contents of the
                     element.
     */
    virtual void endElement(const QName& qname, const std::string& contents) = 0;
    
    /**
     This method is called when a sub-element's opening tag is encountered
     in an XML document. The returned handler is used for events generated
     inside the sub-element.
     
     @param qname The qualified name of the sub-element.
     
     @return A pointer to a recursive handler to use for events generated
             in the sub-element. `this` and `0` are valid return values.
     */
    virtual RecursiveHandler* startSubElement(const QName& qname) = 0;
    
    /**
     This method is called after a sub-element's closing tag is encountered
     in an XML document. This is called exactly once for each each to
     `startSubElement` unless there is a parsing error.
     
     @param qname   The qualified name of the sub-element.
     @param handler The recursive handler that was used to handle this
                    element.
     */
    virtual void endSubElement(const QName& qname, RecursiveHandler* handler) = 0;
};

} // namespace lxml
