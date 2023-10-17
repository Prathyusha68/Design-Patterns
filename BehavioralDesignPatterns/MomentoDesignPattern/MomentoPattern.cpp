#include <iostream>
#include <vector>

using namespace std;

// Memento: Represents the state of the text editor
class EditorMemento
{
    string content;

public:
    EditorMemento() : content{""} {}
    EditorMemento(string content) : content{content} {}

    string getContent()
    {
        return content;
    }
};

// Originator: Text editor that allows typing and saves states in memento
class TextEditor
{
    string content;

public:
    void type(string text)
    {
        content += text;
    }

    EditorMemento saveToMemento()
    {
        return EditorMemento(content);
    }

    void restore(EditorMemento editorMemento)
    {
        content = editorMemento.getContent();
    }
    string getContent()
    {
        return content;
    }
};

// Caretaker: Manages the history of editor states
class History
{
    vector<EditorMemento> history;

public:
    void push(EditorMemento editorMemento)
    {
        history.push_back(editorMemento);
    }

    EditorMemento undo()
    {
        EditorMemento editorMementor;

        if (!history.empty())
        {
            editorMementor = history.back();
            history.pop_back();
        }

        return editorMementor;
    }
};

int main()
{
    TextEditor textEditor;
    History history;

    textEditor.type("Hello ");
    history.push(textEditor.saveToMemento());
    cout << "Current content : " << textEditor.getContent() << endl;

    textEditor.type("World ");
    history.push(textEditor.saveToMemento());
    cout << "Current content : " << textEditor.getContent() << endl;

    textEditor.type("!!!");
    history.push(textEditor.saveToMemento());
    cout << "Current content : " << textEditor.getContent() << endl;

    textEditor.restore(history.undo());
    cout << "Current content after undo : " << textEditor.getContent() << endl;

    textEditor.restore(history.undo());
    cout << "Current content after undo : " << textEditor.getContent() << endl;

    textEditor.restore(history.undo());
    cout << "Current content after undo : " << textEditor.getContent() << endl;

    return 0;
}