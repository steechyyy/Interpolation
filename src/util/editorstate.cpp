#include "editorstate.hpp"

editorstate& getEditorState() {
	static editorstate est;
	return est;
};