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
#include <string>

namespace lxml {

/**
 QName represents an XML qualified name. It consists of a local name, a
 prefix and a namespace URI.
 */
class QName {
public:
    QName() = default;
    QName(const char* localName)
    : _localName(localName), _prefix(), _namespaceURI() {}
    QName(const char* localName, const char* prefix, const char* nsURI)
    : _localName(localName), _prefix(prefix), _namespaceURI(nsURI) {}
    
    const char* localName() const {
        return _localName;
    }
    const char* prefix() const {
        return _prefix;
    }
    const char* namespaceURI() const {
        return _namespaceURI;
    }
    
    bool operator==(const QName& qname) const {
        return
            compare(_localName, qname._localName) == 0 &&
            compare(_prefix, qname._prefix) == 0 &&
            compare(_namespaceURI, qname._namespaceURI) == 0;
    }
    
    bool operator<(const QName& qname) const {
        int o = compare(_localName, qname._localName);
        if (o == 0) o = compare(_prefix, qname._prefix);
        if (o == 0) o = compare(_namespaceURI, qname._namespaceURI);
        return o < 0;
    }
    
    static int compare(const char* s1, const char* s2) {
        if (s1 && s2) return strcmp(s1, s2);
        if (s1) return 1;
        if (s2) return -1;
        return 0;
    }
    
private:
    const char* _localName;
    const char* _prefix;
    const char* _namespaceURI;
};

} // namespace lxml
