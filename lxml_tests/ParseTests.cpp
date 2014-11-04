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

#include <lxml/lxml.h>
#include <boost/test/unit_test.hpp>
#include <sstream>

using namespace lxml;

/**
 A handler that only counts the number of elements and the number of errors.
 */
class CountHandler : public SAXHandler {
public:
    int elementCount;
    int errorCount;
    
public:
    CountHandler() : elementCount(0), errorCount(0) {}
    
    void startDocument() {}
    void endDocument() {}
    
    void startElement(const QName& qname, const NamespaceMap& namespaces, const AttributeMap& attributes) {
        elementCount += 1;
    }
    void endElement(const QName& qname) {}
    
    void characters(const char* chars, std::size_t length) {}
    void error(const xmlError& error) {
        errorCount += 1;
    }
};


BOOST_AUTO_TEST_CASE(parseTest) {
    // Test XML
    std::stringstream stream;
    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    stream << "<note>\n";
    stream << "  <to>Tove</to>\n";
    stream << "  <from>Jani</from>\n";
    stream << "  <heading>Reminder</heading>\n";
    stream << "  <body>Don't forget me this weekend!</body>\n";
    stream << "</note>\n";
    
    // Parse
    CountHandler handler;
    bool result = parse(stream, "file", handler);
    
    // Check
    BOOST_CHECK(result);
    BOOST_CHECK_EQUAL(handler.elementCount, 5);
    BOOST_CHECK_EQUAL(handler.errorCount, 0);
}
