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
#include "RootRecursiveHandler.h"

#include <istream>
#include <string>

/**
 \mainpage lxml
 
 lxml is a C++ wrapper for the SAX interface of [Libxml2](http://xmlsoft.org).
 One of the main advantages of lxml is that there is no boilerpate code. Just
 define your [SAXHandler](@ref lxml::SAXHandler) subclass and invoke the parser:

  ~~~{.cpp}
  MyHandler handler;
  bool result = parse(stream, filename, handler);
  ~~~
 
 lxml also supports having separate handlers for each element in an XML
 document. You can have specialized handlers for different elements which
 improves the modularity, maintainability and reusability of the code. Each
 handler recursively specifies sub-handlers to deal with sub-elements. See
 [RecursiveHandler](@ref lxml::RecursiveHandler) for more information.
 */

namespace lxml {

/**
 Parse an XML stream delivering SAX events to a handler.
 
 @param is       The input stream with XML data.
 @param filename The filename to use when generating error messages.
 @param handler  The SAX event handler.
 
 @return `true` if parsing is successful, `false` if there is an error
         parsing.
 */

bool parse(std::istream& is, const std::string& filename, SAXHandler& handler);

/**
 Parse an XML stream delivering SAX events recursively to handlers.

 @param is       The input stream with XML data.
 @param filename The filename to use when generating error messages.
 @param handler  The recursive SAX event handler.

 @return `true` if parsing is successful, `false` if there is an error
 parsing.
 */
bool parse(std::istream& is, const std::string& filename, RecursiveHandler& handler);

}
