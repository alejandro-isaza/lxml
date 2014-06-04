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

#include "lxml.h"

#include <libxml/parser.h>

namespace lxml {

static const std::size_t kReadChunkSize = 10*1024;

SAXHandler::NamespaceMap mapFromXmlNamespaces(const xmlChar** namespaces, int count) {
    SAXHandler::NamespaceMap map;
    for (int i = 0; i < count * 2; i += 2) {
        const char* prefix = reinterpret_cast<const char*>(namespaces[i]);
        const char* nsURI = reinterpret_cast<const char*>(namespaces[i+1]);
        map.insert(std::make_pair(prefix, nsURI));
    }
    return map;
}

SAXHandler::AttributeMap mapFromXmlAttributes(const xmlChar** attrs, int count) {
    SAXHandler::AttributeMap map;
    for (int i = 0; i < count * 5; i += 5) {
        const char* localName = reinterpret_cast<const char*>(attrs[i]);
        const char* prefix = reinterpret_cast<const char*>(attrs[i+1]);
        const char* nsURI = reinterpret_cast<const char*>(attrs[i+2]);
        std::string value(reinterpret_cast<const char*>(attrs[i+3]), reinterpret_cast<const char*>(attrs[i+4]));
        QName qname(localName, prefix, nsURI);
        map[qname] = value;
    }
    
    return map;
}

void startDocument(void* ctx) {
    SAXHandler* handler = reinterpret_cast<SAXHandler*>(ctx);
    handler->startDocument();
}

void endDocument(void* ctx) {
    SAXHandler* handler = reinterpret_cast<SAXHandler*>(ctx);
    handler->endDocument();
}

void startElementNs(void* ctx, const xmlChar* localname, const xmlChar* prefix, const xmlChar* URI, int nb_namespaces, const xmlChar** namespaces, int nb_attributes, int nb_defaulted, const xmlChar** attributes) {
    SAXHandler* handler = reinterpret_cast<SAXHandler*>(ctx);
    QName qname(reinterpret_cast<const char*>(localname),
                reinterpret_cast<const char*>(prefix),
                reinterpret_cast<const char*>(URI));
    handler->startElement(qname,
                          mapFromXmlNamespaces(namespaces, nb_namespaces),
                          mapFromXmlAttributes(attributes, nb_attributes));
}

void endElementNs(void* ctx, const xmlChar* localname, const xmlChar* prefix, const xmlChar* URI) {
    SAXHandler* handler = reinterpret_cast<SAXHandler*>(ctx);
    QName qname(reinterpret_cast<const char*>(localname),
                reinterpret_cast<const char*>(prefix),
                reinterpret_cast<const char*>(URI));
    handler->endElement(qname);
}

void characters(void* ctx, const xmlChar* ch, int len) {
    SAXHandler* handler = reinterpret_cast<SAXHandler*>(ctx);
    handler->characters(reinterpret_cast<const char*>(ch), static_cast<std::size_t>(len));
}

void error(void* ctx, xmlErrorPtr error) {
    SAXHandler* handler = reinterpret_cast<SAXHandler*>(ctx);
    handler->error(*error);
}

static xmlSAXHandler __sax_handler = {
    NULL,                       // internalSubset
    NULL,                       // isStandalone
    NULL,                       // hasInternalSubset
    NULL,                       // hasExternalSubset
    NULL,                       // resolveEntity
    NULL,                       // getEntity
    NULL,                       // entityDecl
    NULL,                       // notationDecl
    NULL,                       // attributeDecl
    NULL,                       // elementDecl
    NULL,                       // unparsedEntityDecl
    NULL,                       // setDocumentLocator
    startDocument,              // startDocument
    endDocument,                // endDocument
    NULL,                       // startElement
    NULL,                       // endElement
    NULL,                       // reference
    characters,                 // characters
    NULL,                       // ignorableWhitespace
    NULL,                       // processingInstruction
    NULL,                       // comment
    NULL,                       // warning
    NULL,                       // error
    NULL,                       // fatalError
    NULL,                       // getParameterEntity
    NULL,                       // cdataBlock
    NULL,                       // externalSubset
    XML_SAX2_MAGIC,             // initialized
    NULL,                       // private
    startElementNs,             // startElementNs
    endElementNs,               // endElementNs
    error,                      // serror
};

bool parse(std::istream& is, const std::string& filename, RecursiveHandler& handler) {
    lxml::RootRecursiveHandler rootHandler(&handler);
    return parse(is, filename, rootHandler);
}

bool parse(std::istream& is, const std::string& filename, SAXHandler& handler) {
    if (!is)
        return false;
    
    xmlParserCtxtPtr parserCtxt = xmlCreatePushParserCtxt(&__sax_handler, &handler, NULL, 0, filename.c_str());
    parserCtxt->replaceEntities = 1;
    char memblock[kReadChunkSize];
    while (is) {
        is.read(memblock, kReadChunkSize);
        int error = xmlParseChunk(parserCtxt, memblock, (int)is.gcount(), 0);
        if (error > 0) {
            xmlFreeParserCtxt(parserCtxt);
            return false;
        }
    }
    
    xmlParseChunk(parserCtxt, NULL, 0, 1); // EOF
    xmlFreeParserCtxt(parserCtxt);
    return true;
}

} // namespace lxml
