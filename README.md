# lxml

lxml is a C++ wrapper for the SAX interface of [LibXml2](http://xmlsoft.org/). One of its main features is that there is no bolerplate involved. Just define your SAXHandler subclass and invoke the parser:

```cpp
#include <lxml.h>
//...
MyHandler handler;
bool result = parse(stream, filename, handler);
```

lxml also supports having separate handlers for each element in an XML document. You can have specialized handlers for different elements which improves the modularity, maintainability and reusability of the code. Each handler recursively specifies sub-handlers to deal with sub-elements.


## Usage

Just include the contents of the `src` folder in your project. Remember to link with LibXml2. You can also use CMake to generate a project for your IDE or a Makefile: run `cmake .`.


## Example

In this example we are going to parse an XML file into a simplistic DOM. To keep things simple the DOM is a tree of `Node` elements. The `Node` class looks like this:

```cpp
class Node {
public:
    typedef std::vector<std::unique_ptr<Node>> ChildrenCollection;

public:
    Node() : name(), parent(), children() {}
    explicit Node(const std::string& name) : name(name), parent(), children() {}

public:
    std::string name;
    std::string text;

    Node* parent;
    ChildrenCollection children;
};
```

The first step is to write a custom recursive handler. Recursive handlers only need to worry about a single element in the XML document tree. Here is how our handler looks like:

```cpp
class NodeHandler : public lxml::BaseRecursiveHandler<std::unique_ptr<Node>> {
public:
    NodeHandler();
    explicit NodeHandler(Node* parentNode);

    void startElement(const lxml::QName& qname, const AttributeMap& attributes);
    void endElement(const lxml::QName& qname, const std::string& contents);
    RecursiveHandler* startSubElement(const lxml::QName& qname);
    void endSubElement(const lxml::QName& qname, RecursiveHandler* handler);

private:
    Node* _parentNode;
    std::unique_ptr<NodeHandler> _subHandler;
};
```

Inheriting from `BaseRecursiveHandler` gives us a `_result` property and getters for convenience. We keep a reference to the parent node so that we can set the parent to any nodes that we build at this level in the tree. We also have a pointer to a sub-handler that we are going to create on-demand. Now here is the implementation:

```cpp
NodeHandler::NodeHandler() : _parentNode() {}

NodeHandler::NodeHandler(Node* parentNode) : _parentNode(parentNode) {}

void NodeHandler::startElement(const lxml::QName& qname, const AttributeMap& attributes) {
    _result.reset(new Node(qname.localName()));
    _result->parent = _parentNode;
    _subHandler.reset();
}

void NodeHandler::endElement(const lxml::QName& qname, const std::string& contents) {
    _result->text = contents;
}

lxml::RecursiveHandler* NodeHandler::startSubElement(const lxml::QName& qname) {
    if (!_subHandler)
        _subHandler.reset(new NodeHandler(_result.get()));
    return _subHandler.get();
}

void NodeHandler::endSubElement(const lxml::QName& qname, RecursiveHandler* handler) {
    _result->children.push_back(std::move(_subHandler->result()));
}
```

Every time we detect a new element we reset the `_result` to a new instance of `Node` and set its parent. When the closing tag is found, we capture the text contents. When a sub-elemen tag is found, we create a new `NodeHanlder` to handle this sub-element and initialize its parent node to be the current `_result`. Finally when the sub-element finishes we add the sub-handler's result to the collection of children.

To use the parser just put this in your `main.cpp` file
```cpp
#include <fstream>
#include <iostream>
#include <lxml.h>

#include "NodeHandler.h"

int main(int argc, const char * argv[]) {
    static const char* filename = "note.xml";
    std::ifstream stream(filename);

    NodeHandler handler;
    bool success = lxml::parse(stream, filename, handler);
    if (!success) {
        std::cout << "Error parsing file\n";
        return 1;
    }
    
    auto& rootNode = handler.result();
    std::cout << "Root node is a " << rootNode->name
        << " with " << rootNode->children.size() << " children\n";
    
    return 0;
}
```

That's all you need to do to parse arbitrary XML documents into a DOM tree. But the real power of lxml is having different handlers for different elements. For instance having a `DateHandler` for dates, `IntegerHandler` for integers and custom class handlers for model objects.

To do this you would detect the kind of element and return an appropriate handler:

```cpp
lxml::RecursiveHandler* NodeHandler::startSubElement(const lxml::QName& qname) {
    if (strcmp(qname.localName(), kDateTag) == 0)
        return _dateHandler;
    else if (strcmp(qname.localName(), kPersonTag) == 0)
        return _personHandler;

    // Ignore unrecognized sub-elements
    return 0;
}
```

and then set the correct property when the sub-element is built:
```cpp
void NodeHandler::endSubElement(const lxml::QName& qname, RecursiveHandler* handler) {
    if (strcmp(qname.localName(), kDateTag) == 0)
        _result->setDate(_dateHandler->result());
    else if (strcmp(qname.localName(), kPersonTag) == 0)
        _result->setPerson(_personHandler->result());
}
```
